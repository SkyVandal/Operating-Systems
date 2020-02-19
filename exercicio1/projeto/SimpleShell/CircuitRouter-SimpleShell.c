/* =============================================================================
 * Bruno Codinha        90707
 * Catarina Gonçalves   90709
 * =============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "../lib/commandlinereader.h"
#include "../lib/vector.h"

typedef struct {
  pid_t pid;
  int status;
} Child;

int children_counter = 0;
int MAXCHILDREN = 0;
int vectorSize = 3;
int bufferSize = 1024;
char **argVector;
vector_t* children_vec;


/* =============================================================================
 * run_p
 * =============================================================================
 */

 int file_access(char * filename) {
     FILE *fp;

     if ((fp = fopen(filename, "r"))){
         fclose(fp);
         return 1;
     }
     return 0;
 }

void run_p() {
  pid_t pid;

  pid = fork();

  if ( pid < 0){
    fprintf(stderr, "Nao foi possivel criar processo filho!");
    exit(-1);
  }
  if (pid == 0) {
    children_counter++;
    execl("../SeqSolver/CircuitRouter-SeqSolver", "../SeqSolver/CircuitRouter-SeqSolver", "-b", argVector[1], (char*)NULL);
  }
}

/* =============================================================================
 * exit_p
 * =============================================================================
 */

 void exit_p() {
   int status, i;
   pid_t pid;
   Child *child;

  while ((pid = wait(&status)) != -1) {
    if ( WIFEXITED(status) == 0 && WEXITSTATUS(status) == 0 ) {
      printf("CHILD EXITED  (PID=%d; return OK)\n", pid);
    } else {
      printf("CHILD EXITED  (PID=%d; return NOK)\n", pid);
    }
  }
  for (i = 0; i < vector_getSize(children_vec); i++) {
    child = vector_at(children_vec, i);

    if ( WIFEXITED(child->status) == 0 && WEXITSTATUS(child->status) == 0 ) {
      printf("CHILD EXITED  (PID=%d; return OK)\n", child->pid);
    } else {
      printf("CHILD EXITED  (PID=%d; return NOK)\n", child->pid);
    }
  }
  puts("END.");
  exit(0);
}


/* =============================================================================
 * main
 * =============================================================================
 */

int main(int argc, char **argv) {
  int nTokens, status;
  pid_t pid;
  char buffer[bufferSize];

  if (argc == 2){
    MAXCHILDREN = atoi(argv[1]);
  }

  argVector = (char**)malloc(sizeof(char*)*vectorSize);
  children_vec = vector_alloc(20);

  while(1){
    nTokens = readLineArguments(argVector, vectorSize, buffer, bufferSize);

    if (nTokens == -1) {
      fprintf(stderr, "Argumentos invalidos!\n");
      exit(-1);
    }

    if (nTokens == 1) {
      if(strcmp(argVector[0], "exit") == 0) {
        exit_p();
      } else {
        fprintf(stderr, "Argumentos invalidos!\n");
        exit(-1);
      }
    }

    if ( nTokens == 2)
      if(strcmp(argVector[0], "run") == 0) {

        if (file_access(argVector[1])) {

          if(MAXCHILDREN == 0 || children_counter < MAXCHILDREN)
          run_p();
          else {
            pid = wait(&status);
            Child* child = malloc(sizeof(Child));
            child->pid = pid;
            child->status = status;
            vector_pushBack(children_vec, (void*)child);
            children_counter--;
            run_p();
          }
        } else fprintf(stderr, "Ficheiro invalido!\n");

      } else
          fprintf(stderr, "Argumentos invalidos!\n");
  }

  free(argVector);
  vector_free(children_vec);

  return 0;
}
/* =============================================================================
 * end of CircuitRouter-SimpleShell.c
 * =============================================================================
 */
