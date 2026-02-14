/*
 * Linux Shell Header File
 * Sam Duddy
 * 2/14/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


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
            int pid = fork();
            if (pid == -1) {
                fprintf(stderr, "fork() failed\n");
                _exit(1);
            }
            if (pid == 0) {
                // in the child process
                char* arg_cmd;
                arg_cmd = strtok_r(whole_cmd, " ", &inner_saveptr);
                char* args[10];
                int i = 0;
                while (arg_cmd != NULL) {
                    args[i] = arg_cmd;
                    i++;
                    arg_cmd = strtok_r(NULL, " ", &inner_saveptr);

                }
                args[i] = NULL;
                execvp(args[0], args);
                printf("unable to execute command\n");
                _exit(1);
            } else {
                wait(NULL);
                whole_cmd = strtok_r(NULL, ";", &outer_saveptr);
            }
        }
    }
    return 0;
}

int execute_file(char* cmd, char* file) {
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    while(fgets(cmd, sizeof(cmd), fp) != NULL) {
        printf("%s", cmd);
        execute(cmd);
    }
    return 0;
}
