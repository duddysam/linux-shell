# linux-shell
# Sam Duddy
# 2/14/2026

Design Overview: A simple linux shell, programmed in C. The shell can be used for both batch files and interactively in user mode. If being used in batch mode, the file path to the batch file should be referenced as a command line argument. Commands can be separated by semi-colon in both batch mode and interactive mode.

A shell.c file determines what mode to run in, based on the number of command line arguments. If there are more than two command line arguments, it will report that an invalid number of arguments has been made and will exit. Two command line arguments implies that the second arg refers to a batch file, so the program will enter batch mode in this case. One command line argument will place the program in interactive mode. In both batch mode and user mode, the code will call the same 'execute()' function to perform the operations. This function lives in a separate header file and will return either a 1 or 0 based on whether it sees 'quit' as one of the commands. Depending on the mode, the shell will continue to either read from the specified file (in batch mode) or prompt the user for commands until 'quit' is seen or entered, the file ends, or a CTRL-C or CTRL-D command interrupts execution. The program will exit at this point.

The execute() function in the header file uses four system calls, namely fork(), wait(), exec(), and pipe() to create a new process and execute each command. The function that does this is stored in a header file. The character arrays that comprise the commands are parsed by ";" using the strtok_r() function. Then they are parsed again prior to being passed to the exec_v() system call. The pipe() call is used to report 'quit' commands to the parent process without immediately terminating execution for subsequent commands. If a quit command is seen, it acts as a flag so that after all of the other commands (if there are any) have been run, the program knows to quit.

Complete Specification: The first ambiguity that was run into was how to appropriately handle very long command strings. The rubric specified that if a command was greater than 512 characters (including newline) than it could be skipped. The ambiguity here was surrounding how much memory to allocate for commands in general. Should the user be allowed to enter a 10,000 character string, only to be told that it was too long? The design choice was made to declare the 'cmd' array to be up to 1000 characters but to only attempt to run commands that were fewer than 512 characters.

Another ambiguity was around how to handle whitespace in the commands or empty commands. To accomplish this, I used a double parsing loop with strtok_r() functions. The first parsing loop separated individual commands by semicolons. Once done, the inner parse was based on white space - storing each sequence of characters in an array (maximum of length 10). This meant that for empty commands or commands with only white space, this inner loop did not return any values, and thus no fork() or exec() system call was made. It also made the format of the commands more flexible. Whether a command was preceeded or superceeded by some white space was irrelevant. White space could also exist between different command arguments without problem.

Known Bugs: If exceedingly long commands are passed, they will be broken up into chunks of 1000 characters each and not be run due to their size being over the maximum length. This could also result in some weird memory leaks and potential segmentation faults.

Files: shell.c - the actual implementation of the shell executeCommands.h - header file where commands are parsed, separate processes are created, and the commands are executed Makefile - use 'make' to compile and 'make clean' remove executables and object files. README.md - this file

How to Run:

cd into the directory that holds the source code.
run the make command to build the executable.
for, batch mode, run the executable: ./shell [batchFile]. Commands will be echo'd to stdout before being executed.
for interactive mode, run the executable without any additional command line args: ./shell
for interactive mode, type the commands at the prompt and press enter. Separating commands by semi-colon
Resources used:

https://man7.org/linux/man-pages/man3/strncmp.3.html
https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
https://stackoverflow.com/questions/3889992/how-does-strtok-split-the-string-into-tokens-in-c
https://www.ionos.com/digitalguide/websites/web-development/execvp/
https://stackoverflow.com/questions/18686114/cd-command-not-working-with-execvp
https://systems-encyclopedia.cs.illinois.edu/articles/c-strtok/
https://stackoverflow.com/questions/14867621/execvp-not-accepting-user-input?rq=3
https://stackoverflow.com/questions/13022182/header-naming-convention
https://www.w3schools.com/c/c_files_read.php
https://www.unixguide.net/unix/programming/1.1.3.shtml
