/*
 * Linux Shell Header File
 * Sam Duddy
 * 2/14/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int execute(char* cmd) {
    if(strlen(cmd) >= 512) {
        printf("Command exceeds maximum length. Not able to execute\n");
    } else {
        cmd[strlen(cmd)-1] = '\0';
        // now we must parse through the command
        char* outer_saveptr;
        char* inner_saveptr;
        char* whole_cmd;

        whole_cmd = strtok_r(cmd, ";", &outer_saveptr);
        while (whole_cmd != NULL) {
            printf("whole_cmd: %s\n", whole_cmd);

            char* arg_cmd;
            arg_cmd = strtok_r(whole_cmd, " ", &inner_saveptr);
            char* args[10];
            int i = 0;
            while (arg_cmd != NULL) {
                printf("adding %s to index %d\n", arg_cmd, i);
                args[i] = arg_cmd;
                i++;
                arg_cmd = strtok_r(NULL, " ", &inner_saveptr);

            }
            args[i] = NULL;
            whole_cmd = strtok_r(NULL, ";", &outer_saveptr);
        }
    }
    return 0;
}
