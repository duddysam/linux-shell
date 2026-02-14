/*
 * Linux Shell Header File
 * Sam Duddy
 * 2/14/2026
 */

int read_file(char* cmd, char* file) {
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    while(fgets(cmd, sizeof(cmd), fp) != NULL) {
        printf("%s", cmd);
    }
    return 0;
}
