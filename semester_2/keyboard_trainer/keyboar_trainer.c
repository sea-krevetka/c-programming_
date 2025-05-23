#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <jansson.h>

#define MAX_TEXT_LEN 512
#define MAX_NICK_LEN 64
#define STATS_FILE "stats.json"
#define LEADER_FILE "leaderboard.json"
#define MAX_ENTRIES 100

typedef enum { EASY, MEDIUM, HARD, ASDF, JKL, CUSTOM, MINECRAFT } Diff;

typedef struct {
    char date[20];
    double speed;
    double accuracy;
    double elapsed;
    int correct;
    int wrong;
    Diff difficulty;
} Stat;

typedef struct {
    char nickname[MAX_NICK_LEN];
    Stat *stats;
    size_t count;
} PlayerStats;

typedef struct {
    char nickname[MAX_NICK_LEN];
    double speed;
    char date[20];
} LeaderEntry;


const char *texts_easy[] = {
    "Кот сидит на ковре.",
    "Солнце светит ярко.",
    "Я люблю программировать.",
    "Чай горячий и вкусный.",
    "Книга лежит на столе."
};
const char *texts_medium[] = {
    "Быстрая коричневая лиса прыгает через ленивую собаку.",
    "Сложные задачи требуют внимательного подхода и терпения.",
    "Программирование - это искусство создания полезных вещей из ничего.",
    "Клавиатурный тренажер помогает улучшить скорость печати.",
    "Практика ведет к совершенству, особенно в наборе текста."
};
const char *texts_hard[] = {
    "Философия - это систематическое изучение фундаментальных вопросов бытия, познания, ценностей и языка.",
    "Квантовая механика описывает поведение материи и энергии на атомном и субатомном уровнях.",
    "Алгоритмы и структуры данных являются основой компьютерных наук и программирования.",
    "Нейронные сети имитируют работу человеческого мозга для решения сложных задач машинного обучения.",
    "Теория относительности Эйнштейна изменила наше понимание пространства, времени и гравитации."
};
const char *texts_asdf[] = { "asdf asdf asdf asdf asdf asdf asdf asdf asdf asdf" };
const char *texts_jkl[] = { "jkl; jkl; jkl; jkl; jkl; jkl; jkl; jkl; jkl; jkl;" };
const char *texts_minecraft[] = {
    "/tp a s", "/setblock ~ ~ ~ water", "/tp ~ 100 ~",
    "/gamemode c", "/gamemode su", "/gamemode sp",
    "/gamemode a c", "/gamemode a su", "/gamemode a sp",
    "/give torch 64", "/give beef 64", "/enchant efficiency 5", "/enchant unbreaking 3"
};

char **texts_custom = NULL;
size_t custom_count = 0;

PlayerStats *players = NULL;
size_t player_count = 0;

LeaderEntry leaderboard[MAX_ENTRIES];
size_t leader_count = 0;

Diff current_diff = MEDIUM;

void current_timestamp(char *buf, size_t sz) {
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    strftime(buf, sz, "%Y-%m-%d %H:%M:%S", lt);
}

void load_stats() {
    json_error_t error;
    json_t *root = json_load_file(STATS_FILE, 0, &error);
    
    if (!root) {
        // Файл не существует или поврежден - это нормально при первом запуске
        return;
    }
    
    if (!json_is_object(root)) {
        json_decref(root);
        return;
    }
    
    const char *nickname;
    json_t *stats_array;
    
    json_object_foreach(root, nickname, stats_array) {
        if (!json_is_array(stats_array)) continue;
        
        // Добавляем нового игрока
        players = realloc(players, (player_count + 1) * sizeof(PlayerStats));
        PlayerStats *p = &players[player_count];
        
        strncpy(p->nickname, nickname, MAX_NICK_LEN);
        p->count = json_array_size(stats_array);
        p->stats = malloc(p->count * sizeof(Stat));
        
        for (size_t i = 0; i < p->count; i++) {
            json_t *stat_obj = json_array_get(stats_array, i);
            Stat *s = &p->stats[i];
            
            strncpy(s->date, json_string_value(json_object_get(stat_obj, "date")), sizeof(s->date));
            s->speed = json_number_value(json_object_get(stat_obj, "speed"));
            s->accuracy = json_number_value(json_object_get(stat_obj, "accuracy"));
            s->elapsed = json_number_value(json_object_get(stat_obj, "time"));
            s->correct = json_integer_value(json_object_get(stat_obj, "correct"));
            s->wrong = json_integer_value(json_object_get(stat_obj, "wrong"));
            s->difficulty = json_integer_value(json_object_get(stat_obj, "difficulty"));
        }
        
        player_count++;
    }
    
    json_decref(root);
}

void load_leader() {
    json_error_t error;
    json_t *root = json_load_file(LEADER_FILE, 0, &error);
    
    if (!root) {
        // Файл не существует или поврежден - нормально при первом запуске
        return;
    }
    
    if (!json_is_array(root)) {
        json_decref(root);
        return;
    }
    
    leader_count = json_array_size(root);
    if (leader_count > MAX_ENTRIES) leader_count = MAX_ENTRIES;
    
    for (size_t i = 0; i < leader_count; i++) {
        json_t *entry = json_array_get(root, i);
        LeaderEntry *e = &leaderboard[i];
        
        strncpy(e->nickname, json_string_value(json_object_get(entry, "nickname")), MAX_NICK_LEN);
        e->speed = json_number_value(json_object_get(entry, "speed"));
        strncpy(e->date, json_string_value(json_object_get(entry, "date")), sizeof(e->date));
    }
    
    json_decref(root);
}

void save_stats() {
    json_t *root = json_object();
    
    for (size_t i = 0; i < player_count; i++) {
        PlayerStats *p = &players[i];
        json_t *stats_array = json_array();
        
        for (size_t j = 0; j < p->count; j++) {
            Stat *s = &p->stats[j];
            json_t *stat_obj = json_object();
            
            json_object_set_new(stat_obj, "date", json_string(s->date));
            json_object_set_new(stat_obj, "speed", json_real(s->speed));
            json_object_set_new(stat_obj, "accuracy", json_real(s->accuracy));
            json_object_set_new(stat_obj, "time", json_real(s->elapsed));
            json_object_set_new(stat_obj, "correct", json_integer(s->correct));
            json_object_set_new(stat_obj, "wrong", json_integer(s->wrong));
            json_object_set_new(stat_obj, "difficulty", json_integer(s->difficulty));
            
            json_array_append_new(stats_array, stat_obj);
        }
        
        json_object_set_new(root, p->nickname, stats_array);
    }
    
    if (json_dump_file(root, STATS_FILE, JSON_INDENT(2)) != 0) {
        fprintf(stderr, "Ошибка сохранения статистики в файл\n");
    }
    
    json_decref(root);
}
void save_leader() {
    json_t *root = json_array();
    
    for (size_t i = 0; i < leader_count; i++) {
        LeaderEntry *e = &leaderboard[i];
        json_t *entry = json_object();
        
        json_object_set_new(entry, "nickname", json_string(e->nickname));
        json_object_set_new(entry, "speed", json_real(e->speed));
        json_object_set_new(entry, "date", json_string(e->date));
        
        json_array_append_new(root, entry);
    }
    
    if (json_dump_file(root, LEADER_FILE, JSON_INDENT(2)) != 0) {
        fprintf(stderr, "Ошибка сохранения таблицы рекордов\n");
    }
    
    json_decref(root);
}


void clear_buf() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void show_results(int total, int correct, int wrong, double elapsed) {
    printf("\n=== Результаты ===\n");
    printf("Всего символов: %d\n", total);
    printf("Правильных: %d, Ошибок: %d\n", correct, wrong);
    printf("Время: %.2f сек\n", elapsed);
    double speed = correct / (elapsed/60.0);
    double accuracy = (total>0? correct*100.0/total: 0);
    printf("Скорость: %.1f зн/мин, Точность: %.1f%%\n", speed, accuracy);
    
    char nick[MAX_NICK_LEN];
    printf("Введите ник (Enter чтобы пропустить): ");
    if (!fgets(nick, MAX_NICK_LEN, stdin)) return;
    nick[strcspn(nick, "\r\n")] = '\0';
    if (strlen(nick)==0) return;

    PlayerStats *p = NULL;
    for (size_t i=0; i<player_count; i++) {
        if (strcmp(players[i].nickname, nick)==0) { p=&players[i]; break; }
    }
    if (!p) {
        players = realloc(players, (player_count+1)*sizeof(PlayerStats));
        p = &players[player_count];
        strncpy(p->nickname, nick, MAX_NICK_LEN);
        p->stats = NULL;
        p->count = 0;
        player_count++;
    }
    p->stats = realloc(p->stats, (p->count+1)*sizeof(Stat));
    Stat *s = &p->stats[p->count++];
    current_timestamp(s->date, sizeof(s->date));
    s->speed = speed;
    s->accuracy = accuracy;
    s->elapsed = elapsed;
    s->correct = correct;
    s->wrong = wrong;
    s->difficulty = current_diff;

    int found = 0;
    for (size_t i=0; i<leader_count; i++) {
        if (strcmp(leaderboard[i].nickname, nick)==0) {
            if (speed > leaderboard[i].speed) {
                leaderboard[i].speed = speed;
                current_timestamp(leaderboard[i].date, sizeof(leaderboard[i].date));
            }
            found = 1; break;
        }
    }
    if (!found && leader_count < MAX_ENTRIES) {
        LeaderEntry *e = &leaderboard[leader_count++];
        strncpy(e->nickname, nick, MAX_NICK_LEN);
        e->speed = speed;
        current_timestamp(e->date, sizeof(e->date));
    }
    for (size_t i=0; i<leader_count; i++) {
        for (size_t j=i+1; j<leader_count; j++) {
            if (leaderboard[j].speed > leaderboard[i].speed) {
                LeaderEntry tmp = leaderboard[i]; leaderboard[i] = leaderboard[j]; leaderboard[j] = tmp;
            }
        }
    }
    if (leader_count>10) leader_count = 10;
}

void start_training() {
    const char *text;
    switch (current_diff) {
        case EASY: text = texts_easy[rand()%5]; break;
        case MEDIUM: text = texts_medium[rand()%5]; break;
        case HARD: text = texts_hard[rand()%5]; break;
        case ASDF: text = texts_asdf[0]; break;
        case JKL: text = texts_jkl[0]; break;
        case MINECRAFT: text = texts_minecraft[rand()%13]; break;
        case CUSTOM: text = texts_custom[rand()%custom_count]; break;
    }
    printf("\nТренировка (%d): %s\n", current_diff, text);
    printf("Начинайте ввод: \n");
    char input[MAX_TEXT_LEN];
    clock_t t0 = clock();
    if (!fgets(input, MAX_TEXT_LEN, stdin)) return;
    clock_t t1 = clock();
    double elapsed = (t1 - t0) / (double)CLOCKS_PER_SEC;
    // Strip newline
    input[strcspn(input, "\r\n")] = '\0';
    int len = strlen(text), ulen = strlen(input);
    int correct=0, wrong=0;
    int m = len>ulen? len: ulen;
    for (int i=0; i<m; i++) {
        if (i<len && i<ulen && text[i]==input[i]) correct++; else wrong++;
    }
    show_results(correct+wrong, correct, wrong, elapsed);
}

void select_diff() {
    printf("\n=== difficulty choice ===\n");
    printf("1. EASY\n" );
    printf("2. MEDIUM\n" );
    printf("3. HARD\n" );
    printf("4. ASDF\n" );
    printf("5. JKL;\n" );
    printf("6. Your text\n" );
    printf("m. Minecraft\n");
    char c = getchar(); clear_buf();
    if (c=='1') current_diff=EASY;
    else if (c=='2') current_diff=MEDIUM;
    else if (c=='3') current_diff=HARD;
    else if (c=='4') current_diff=ASDF;
    else if (c=='5') current_diff=JKL;
    else if (c=='6') {
        char tmp[MAX_TEXT_LEN];
        printf("Input text: "); fgets(tmp, MAX_TEXT_LEN, stdin);
        tmp[strcspn(tmp,"\r\n")]='\0';
        if (custom_count>0) free(texts_custom);
        custom_count=1;
        texts_custom = malloc(sizeof(char*));
        texts_custom[0] = strdup(tmp);
        current_diff=CUSTOM;
    } else if (c=='m') { current_diff=MINECRAFT; }
    else { printf("Неверный выбор\n"); }
    printf("Выбран уровень %d\n", current_diff);
}

void show_stats_menu() {
    char nick[MAX_NICK_LEN];
    printf("Введите ник (Enter для всех): ");
    fgets(nick, MAX_NICK_LEN, stdin);
    nick[strcspn(nick,"\r\n")]='\0';
    if (strlen(nick)==0) {
        for (size_t i=0; i<player_count; i++) {
            PlayerStats *p=&players[i];
            double sum_sp=0, sum_acc=0;
            for (size_t j=0; j<p->count; j++) { sum_sp+=p->stats[j].speed; sum_acc+=p->stats[j].accuracy; }
            printf("%s: тестов %zu, средняя скорость %.1f, точность %.1f\n",
                   p->nickname, p->count, sum_sp/p->count, sum_acc/p->count);
        }
    } else {
        for (size_t i=0; i<player_count; i++) {
            if (strcmp(players[i].nickname, nick)==0) {
                for (size_t j=0; j<players[i].count; j++) {
                    Stat *s = &players[i].stats[j];
                    printf("#%zu %s: скорость %.1f, точность %.1f, время %.1f, верно %d, ошиб %d\n",
                           j+1, s->date, s->speed, s->accuracy, s->elapsed, s->correct, s->wrong);
                }
            }
        }
    }
}

void show_leaderboard() {
    printf("=== Рекорды ===\n");
    for (size_t i=0; i<leader_count; i++) {
        printf("%2zu. %s - %.1f зн/мин (%s)\n",
               i+1, leaderboard[i].nickname, leaderboard[i].speed, leaderboard[i].date);
    }
}

void menu() {
    while (1) {
        printf("\n1. Тренировка\n2. Сложность\n3. Статистика\n4. Рекорды\n5. Выход\nВыберите: ");
        char c=getchar(); clear_buf();
        if (c=='1') start_training();
        else if (c=='2') select_diff();
        else if (c=='3') show_stats_menu();
        else if (c=='4') show_leaderboard();
        else if (c=='5') { save_stats(); save_leader(); break; }
        else printf("Неверно\n");
    }
}

int main() {
    srand(time(NULL));
    load_stats();
    load_leader();
    menu();
    return 0;
}
