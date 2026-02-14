/*
 * Linux Shell Implementation
 * Sam Duddy
 * 2/14/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char** argv) {

    // TOO MANY ARGUMENTS
    if (argc >= 3) {
        fprintf(stderr, "Usage: %s <batchFile>\n", argv[0]);
        return 0;
    }
    char cmd[1000];
    // BATCH MODE
    if (argc == 2) {
        printf("entering batch mode\n");
        //execute_file(cmd, argv[1]);
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL) {
            perror("Error opening file");
            return 1;
        }
        while(fgets(cmd, sizeof(cmd), fp) != NULL) {
            printf("%s", cmd);
            if(execute(cmd) == 1) {exit(1);}
        }
        return 0;
    }


    // INTERACTIVE MODE
    if (argc == 1) {
        printf("entering interactive mode\n");
        while(1) {
            printf("prompt>>");
            fgets(cmd, sizeof(cmd), stdin);
            printf("%s", cmd);
            execute(cmd);
        }
    }
    return 0;

}
