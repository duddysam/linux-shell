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
    int out = 0;
    if(strlen(cmd) >= 512) {
        printf("Command exceeds maximum length. Not able to execute\n");
        return out;
    } else {
        cmd[strlen(cmd)-1] = '\0';
        // now we must parse through the command
        char* outer_saveptr;
        char* inner_saveptr;
        char* whole_cmd;

        whole_cmd = strtok_r(cmd, ";", &outer_saveptr);
        while (whole_cmd != NULL) {
            int fd[2];
            if(pipe(fd) == -1) {
                fprintf(stderr, "pipe(fd) failed\n");
            }
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
                printf("args[0] == %s and i == %d\n", args[0], i);
                if(strcmp(args[0], "quit") == 0 && i == 1) {
                    printf("in the quit condition\n");
                    close(fd[0]);
                    int x = 1;
                    write(fd[1], &x, sizeof(int));
                    close(fd[1]);
                    _exit(1);
                } else {
                    close(fd[0]);
                    int x = 0;
                    write(fd[1], &x, sizeof(int));
                    close(fd[1]);
                    execvp(args[0], args);
                    printf("unable to execute command\n");
                    _exit(1);
                }
            } else {
                wait(NULL);
                close(fd[1]);
                int z;
                read(fd[0], &z, sizeof(int));
                close(fd[0]);
                printf("adding %d to out\n", z);
                out += z;
                if (out > 1) {out = 1;}
                whole_cmd = strtok_r(NULL, ";", &outer_saveptr);
            }
        }
    }
    return out;
}


