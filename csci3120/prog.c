#include<stdio.h>
#include<unistd.h>
#define MAX_LINE 80

/*void read_command(char cmd[],char *par[] ){
  char line[1024];
  int count = 0, i = 0, j= 0;
  char *array[100],*pch;

  //read one line
  for(;;) {
    int c = fgetc( stdin );
    line[ count++ ] = (char) c;
    if( c == '\n') break;
  }
  if(count == 1 ) return;
  pch =strtok(line, " \n");

  while( pch != NULL ) {
    array[i++] = strdup ( pch );
    pch = strtok(NULL, " \n" );
  }

  strcpy(cmd,array[0] );
  
  for( j = 0 ; j < i; j++ )
    par[j] = array[j];
  par[i] = NULL;
  }*/
int main(void){
  char *arg[MAX_LINE/2+1];
  //char cmd[100];
  int should_run = 1;

  while(should_run == 1) {

    printf("osh>");
    fflush(stdout);
    if(1){
      //arg[0] = "ps";
      // arg[1] = NULL;
    //arg[2] = NULL;
      // execvp(arg[0],arg);
    }
  }
  return 0;
}    
