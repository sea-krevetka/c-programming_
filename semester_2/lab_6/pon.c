void swapwords(char *str){
    char first[MAX_LINE_LENGTH];
    char last[MAX_LINE_LENGTH];

    int i = 0;
    while (str[i] != ' ' && str[i] != '\0') {
        first[i] = str[i];
        i++;
    }
    first[i] = '\0';
    int firstlen = i;

    int j = strlen(str) - 1;
    while (j >= 0 && str[j] != ' ' && str[j] != '\0') {
        j--;
    }
    j++;
    strcpy(last, str + j);

    char temp[MAX_LINE_LENGTH];
    snprintf(temp, MAX_LINE_LENGTH, "%s ", last);
    strncat(temp, str + firstlen, j - firstlen); 
    strcat(temp, " ");
    strcat(temp, first);

    strcpy(str, temp);
}