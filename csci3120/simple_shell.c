#include <stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

void type_prompt(){
  static int first_time = 1;
  if( first_time ){
    const char* CLEAR_SCREEN_ANSI = "\e[1;H\e[2J";
    write(STDOUT_FILENO,CLEAR_SCREEN_ANSI,12);
    first_time = 0;
}
  printf("#");
}
void read_command(char cmd[],char *par[]){
  char line[1024];
  int count = 0, i = 0 , j = 0 ;
  char *array[100],*pch;

  for(;;){
    int c = fgetc( stdin );
    line[count++] = (char) c;
    if( c == '\n') break;
  }
  if( count == 1 ) return;
  pch = strtok(line,"\n");

  while(pch != NULL){
    array[i++] = strdup( pch );
    pch = strtok(NULL, "\n");
  }
  strcpy(cmd, array[0]);

  for(j = 0; j < i ; j++){
    par[j] = array[j];
    par[i] = NULL;
  }
}
int main(){
  char cmd[1000], command[100],*parameters[20];
  //  char *envp[] = {(char *)"PATH=/bin",0};

  while(1) {
    type_prompt();
    read_command(command,parameters);

    if(fork() != 0)
      wait(NULL);
    else{
      // strcpy(cmd,"/bin/");
      // strcat(cmd,command);
      execvp(cmd,parameters);
    }
    if(strcmp(command,"exit") == 0 )
      break;
  }
  return 0;

}
