/*
 * Linux Shell Implementation
 * Sam Duddy
 * 2/14/2026
 */


#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


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
        read_file(cmd, argv[1]);
    }

    // INTERACTIVE MODE
    if (argc == 1) {
        printf("entering interactive mode\n");
        while(1) {
            printf("prompt>>");
            fgets(cmd, sizeof(cmd), stdin);
            printf("%s", cmd);
        }
    }
    return 0;
    
}
