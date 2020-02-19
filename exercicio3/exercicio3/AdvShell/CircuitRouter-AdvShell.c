
/*
// Projeto SO - exercise 1, version 1
// Sistemas Operativos, DEI/IST/ULisboa 2018-19
*/

#include "../lib/commandlinereader.h"
#include "../lib/vector.h"
#include "CircuitRouter-AdvShell.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>

#define COMMAND_EXIT "exit"
#define COMMAND_RUN "run"
#define COMMAND_NOT_SUPPORTED "Command not supported.\n"
#define INVALID_SYNTAX "Error: invalid syntax\n"
#define INVALID_FILE "Error: invalid file\n"

#define MAXARGS 3
#define BUFFER_SIZE 100

#define SEND_ERROR(s) {\
    perror((s));\
    exit(EXIT_FAILURE); }

/*******************************************************************************
 * GLOBALS
 ******************************************************************************/
int runningChildren = 0;
vector_t *children;
/******************************************************************************/


void printChildren(vector_t *children) {
    for (int i = 0; i < vector_getSize(children); ++i) {
        child_t *child = vector_at(children, i);
        int status = child->status;
        pid_t pid = child->pid;
        if (pid != -1) {
            const char* ret = "NOK";
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                ret = "OK";
            }
            printf("CHILD EXITED: (PID=%d; return %s; %lf s)\n", pid, ret,
                TIMER_DIFF_SECONDS(child->startTime, child->stopTime));
        }
    }
    puts("END.");
}

void signal_handler(int signal){
    TIMER_T stopTime;
    TIMER_READ(stopTime);

    pid_t pid;
    int status;

    pid = waitpid(-1, &status, WNOHANG);

    child_t *child;

    for(int i = 0; i < vector_getSize(children); i++){
        child = vector_at(children, i);
        if (child->pid == pid) {
            child->status = status;
            child->stopTime = stopTime;
            break;
        }
    }
    runningChildren--;
}

int sendMessage(char* pipe_name, char *message, char *arg) {
    FILE* pipe;
    if ((pipe = fopen(pipe_name, "r+")) != NULL) {
        if (arg == NULL){
            fprintf(pipe, message);
        } else {
            fprintf(pipe,"Error: could not read %s\n", arg);
        }
        fflush(pipe);
        fclose(pipe);
        return 1;
    }
    return -1;
}

int main (int argc, char** argv) {
    FILE* pipe;
    char *args[MAXARGS + 1];
    char buffer[BUFFER_SIZE];
    int MAXCHILDREN = -1;
    int ORIGIN = 0;
    char *fifoPath = argv[0];

    struct sigaction sig_act;

    sig_act.sa_handler = signal_handler;
    sigemptyset(&sig_act.sa_mask);
    sig_act.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &sig_act, NULL) == -1) {
        SEND_ERROR("Error: sigaction");
    }


    char myfifo[strlen(fifoPath) + strlen(".pipe") + 1];
    sprintf(myfifo, "/tmp/%s.pipe", fifoPath);

    unlink(myfifo);
    if(mkfifo(myfifo, 0777) != 0){
        SEND_ERROR("Failed to create AdvShell fifo");
    }


    if(argv[1] != NULL){
        MAXCHILDREN = atoi(argv[1]);
    }

    children = vector_alloc(MAXCHILDREN);


    printf("Welcome to CircuitRouter-AdvancedShell\n\n");

    if ((pipe = fopen(myfifo, "r+")) == NULL) {
      SEND_ERROR("Error opening AdvShell fifo")
    }

    while (1) {
        int numArgs;
        fd_set set;
        int fd_pipe, filed;
        FILE* to_read = NULL;


        fd_pipe = fileno(pipe);
        filed = fd_pipe + 1;

        FD_ZERO(&set);
        FD_SET(0, &set);
        FD_SET(fd_pipe, &set);

        if (select(filed, &set, NULL, NULL, NULL) == -1) {
            if (errno == EINTR) {
                continue;
            }
            SEND_ERROR("Select Failed");
        }

        if (FD_ISSET(fd_pipe, &set)) {
            ORIGIN = 1;
            to_read = pipe;
        }

        if (FD_ISSET(0, &set)) {
            ORIGIN = 0;
            to_read = stdin;
        }

        numArgs = readLineArgumentsFile(args, MAXARGS+1, buffer, BUFFER_SIZE, to_read);
        //printf("%s %s %s\n", args[0], args[1], args[2]);
        /* EOF (end of file) do stdin ou comando "sair" */


        if (ORIGIN && (args[1] == NULL)) {
            if (sendMessage(args[0], COMMAND_NOT_SUPPORTED, NULL)) {
                continue;
            } else SEND_ERROR("Error opening client pipe");

        }

        if (ORIGIN == 1 && (strcmp(args[1], COMMAND_RUN) != 0)) {
            if (sendMessage(args[0], COMMAND_NOT_SUPPORTED, NULL)) {
                continue;
            } else SEND_ERROR("Error opening client pipe");
        }

        if (numArgs < 0 || (numArgs > 0 && (strcmp(args[0 + ORIGIN], COMMAND_EXIT) == 0))) {
            printf("CircuitRouter-SimpleShell will exit.\n--\n");

            /* Espera pela terminacao de cada filho */
            while (runningChildren > 0) {
                pause();
            }

            printChildren(children);
            printf("--\nCircuitRouter-SimpleShell ended.\n");
            break;
        }

        else if (numArgs > 0 && strcmp(args[0 + ORIGIN], COMMAND_RUN) == 0){
            int pid;

            if (numArgs < 2 || (ORIGIN && numArgs < 3)) {

                if (ORIGIN == 1) {
                    if (sendMessage(args[0], INVALID_SYNTAX, NULL)) {
                        continue;
                    } else SEND_ERROR("Error: could not open client pipe");

                } else {
                    printf("%s: invalid syntax. Try again.\n", COMMAND_RUN);
                    continue;
                }
            }

            if (ORIGIN && access(args[1 + ORIGIN], F_OK) != 0) {
                if(sendMessage(args[0], INVALID_SYNTAX, args[1 + ORIGIN])){
                    continue;
                } else SEND_ERROR("Error: could not open client pipe.");

            }

            if (MAXCHILDREN != -1 && runningChildren >= MAXCHILDREN) {
                pause();
            }

            TIMER_T startTime;
            TIMER_READ(startTime);

            pid = fork();
            if (pid < 0) {
                SEND_ERROR("Failed to create new process.");
            }

            if (pid > 0) {
                runningChildren++;

                child_t *child = malloc(sizeof(child_t));

                if (child == NULL) {
                    SEND_ERROR("Error allocating memory");
                }

                child->startTime = startTime;
                child->pid = pid;
                vector_pushBack(children, child);

                printf("%s: background child started with PID %d.\n\n", COMMAND_RUN, child->pid);
                continue;

            } else {
                char seqsolver[] = "../SeqSolver/CircuitRouter-SeqSolver";
                char *newArgs[4] = {seqsolver, args[1 + ORIGIN], args[0], NULL};

                execv(seqsolver, newArgs);
                SEND_ERROR("Error while executing child process");
            }
        }

        else if (numArgs == 0) {
            /* Nenhum argumento; ignora e volta a pedir */
            continue;
        }
        else {
            printf("Unknown command. Try again.\n");
        }
    }

    for (int i = 0; i < vector_getSize(children); i++) {
        free(vector_at(children, i));
    }
    vector_free(children);

    fclose(pipe);
    return EXIT_SUCCESS;
}
