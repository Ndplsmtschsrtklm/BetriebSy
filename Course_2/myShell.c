#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


void print_command_prompt(){
  printf("myShell>");
}

char* read_and_save_command(){
  char temp_command[256];
  char* command = (char*)malloc(256 + 5);
  if(command == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  scanf("%255s", temp_command);
  // '/bin/' hinzufügen, weil ich keine lust drauf habe es zu Tippen
  sprintf(command, "/bin/%s", temp_command); 
  return command;
}

int main(void){
  while(1){
    print_command_prompt();
    char* command = read_and_save_command();

  //Eltern-Prozess
    if (fork() > 0){
      int status;
      wait(&status);
    }
  //Kind-Prozess
    else{
      char *argv[] = {command, NULL};
      char *envp[] = {NULL};
      errno = 0;
      if (execve(command, argv, envp) == -1){
        perror("execve");
        exit(EXIT_FAILURE);
      }
    }
    free(command);
  }
  return 0;
}
//// einfache Shell, die Befehle entgegennimmt, automatisch /bin/ davorpackt und den Befehl dann im Kindprozess ausführt
