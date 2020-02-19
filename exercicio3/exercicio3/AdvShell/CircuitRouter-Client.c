#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../lib/commandlinereader.h"

#define MAX_ARGS 3
#define BUFFER_SIZE 100

#define SEND_ERROR(s) {\
    perror((s));\
    exit(EXIT_FAILURE); }

int main(int argc, char **argv) {
    FILE* fifo;
    FILE* client_fifo;
    char args[BUFFER_SIZE];
    char error_message[BUFFER_SIZE];

    char template[] = "/tmp/pipeXXXXXX";
    char* name_temp;
    char this_pipe[strlen(".pipe") + strlen(template) + 1];

    char *myfifo = argv[1];


    if (argc != 2) {
        SEND_ERROR("Two arguments needed");
    }

    if ((name_temp = mkdtemp(template)) != NULL) {
        sprintf(this_pipe, "%s.pipe", name_temp);
        unlink(this_pipe);
        if (mkfifo(this_pipe, 0777) != 0) {
            SEND_ERROR("Failed to create client pipe");
        }
    } else {
        SEND_ERROR("Failed to create a temporary directory");
    }

    if (access(myfifo, X_OK) == 0) {
        if ((fifo = fopen(myfifo, "r+")) != NULL) {
            if((client_fifo = fopen(this_pipe, "r+")) != NULL){
                for(;;){
                    fgets(args, BUFFER_SIZE, stdin);
                    fprintf(fifo, "%s %s", this_pipe, args);
                    fflush(fifo);
                    fgets(error_message, BUFFER_SIZE, client_fifo);
                    printf("%s", error_message);
                }
            } else {
                SEND_ERROR("Error when opening client fifo");
            }
        } else {
            SEND_ERROR("Error when opening AdvShell fifo");
        }
    } else {
        SEND_ERROR("Error 404: fifo not found");
    }

    unlink(this_pipe);
    fclose(client_fifo);
    unlink(myfifo);
    fclose(fifo);

    return 0;
}
