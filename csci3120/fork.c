#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void main(){
  printf("Before execlp*****\n");
  char *argv[41]={NULL};
  int should_run = 1;
  //int loops;
  int hasAmp = 0;
  char history[8]="history";
  // pid_t pid;
  while(should_run){
    printf("CSCI312O>");
    fflush(stdout);
    //fflush(stdin);
    char str[256];
    scanf("%[^\n]%*c",str);
    char *word = strtok(str," ");
    int i = 0;
    argv[i] = word;
    //printf("%s\n",argv[i]);
    i++;
    
    while(word != NULL){
      word = strtok(NULL," ");
      //int  hasAmp = strcmp(word,"&");
      //printf("%d\n",hasAmp);
      ///if(hasAmp != 0){
      argv[i] = word;
      i++;
      // }
      //printf("%s\n",argv[i]);
    }
    argv[i]=NULL;
    //int ampersand = 0;
    if(strcmp(argv[i-2],"&") == 0){
      argv[ i - 2 ] = NULL;
      hasAmp=1;
    }
    //char *string = argv[
    //if(argv[i-1]=="&")
    /// ampersand = 1;

    int pid = fork();
    //if(strcmp(argv[i-2],"&")==0){
    //	printf("lsadad");
	//}
    if(pid < 0) {
      printf("Fork failed");
    }
    else if(pid == 0){
      
      execvp(argv[0],argv);
	/*for(int j = i-1 ; j>=0 ;j--){
	  argv[j] = NULL;
	*/
	//printf("Invalid command\n");
       for(int j =0 ; j<i; j--){
	argv[j] = NULL;
	}
      //printf("Invalid command");
    }
    else{
      if(hasAmp){
	 wait(NULL);
      }
    }  //return(0);
    
    
    //should_run = 0;
    //exit(EXIT_SUCCESS);

    /*if(pid == 0){
      abort();
      }*/
  printf("after execlp****\n");
  }

}
