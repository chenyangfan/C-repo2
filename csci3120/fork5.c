
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
char *recent[41];//a string pointer to store all commands coresponding to ! type command
char HISTORY[10000];  //a string array to store history command as string 
int commandNum =0;//the number of command enterd
char *HISTORY2[41];//a string pointer to store command as tokens
int  recentFlag = 0;
void main(){
  printf("Before execlp*****\n");
  char *argv[41]={NULL};
  int should_run = 1;
  //int recentFlag = 0;
  //& indicates that the parent wait for the child to terminates
  //by default, parent doesn't wait 
  int hasAmp = 0;
  pid_t pid;
  
  while(should_run){
    printf("CSCI312O>");
    fflush(stdout);
 
    
    //Use this String to store the string to accept user input
    char str[256];
  
    scanf("%[^\n]%*c",str);
    printf("CSCI3120>");
    int len = strlen(str);//check the length of the string
    char ch = str[0]; //To check if there is a ! type ommand
    char ch1 = str[1];//To check if it is !! or !number
    
    if(strcmp(str,"exit")==0){//if the input is exit, programm terminates.
      return 0;
    }
    if(strcmp(str,"history") == 0||(ch=='!'&&len == 2)){//if staement for  the input is history or ! related command 
    
      if(HISTORY[0] =='\0'){//no history
	printf("No command in history!\n");
      }

      if(len == 1)// improper ! commands
	printf("Should have more than one command.\n");
      

      else{//if the input is not history type
	//all commands are stored in HISTORY arrays
	//seperated by "," symbol
	//break string into tokens by space
	//and store tokens in history2
	char *split = strtok(HISTORY,",");    
	int i = 0;
	HISTORY2[i] = split;
	i++;
	while( split != NULL){
	  split = strtok(NULL,",");
	  if (split != NULL ){
	    HISTORY2[i] = split;
	    i++;
	  }
	}//end of while loop
	
      HISTORY2[i] = NULL;
      //a loop to print atmost 10 history command
      //use variable max to count down 
      int max = 10;
      for(int j = i - 1; j >= 0;j--){
	 printf("%d\t",j+1);
	 puts(HISTORY2[j]);
	 printf("\n");
	 if(max<=1){
	   break;
	 }
	 max--;
      }
      //The "recent" variable is used to store !related commands
      if(ch1 == '!'){//if this is a !! command 
        recent[0] = HISTORY2[i-1];
      }else{//if this is a !number command 
	int recentNum = ch1 - 48;
        recent[0] = HISTORY2[recentNum-1];
      }
      }
    }//either history or ! command handler finished here
   
    //if-else to determine recentFlag
    if(str[0]=='!'&&len ==2){
      recentFlag = 1;  
    }else{
      recentFlag = 0;
    }

    if(strcmp(str,"history")!=0&&str[0]!='!'){
    //neither history or !commands here 
      char *word = strtok(str," ");
      int i = 0;
      argv[i] = word;
      //recent[i] = word;
      i++;
    
    //Seperate all the words of the command and put them in the correct order
      while(word != NULL){
	word = strtok(NULL," ");
	argv[i] = word;
	i++;
      }
    
      //indicates the end of commands
      argv[i]=NULL;
      //recent[i]=NULL;
      //printf("recent %s:",recent[0]);
    
      //need to delete the & symbol, since execvp doesn't accept this symbol
      //and set the hasAmp flag equals to one
    if(strcmp(argv[i-2],"&") == 0){
      argv[ i - 2 ] = NULL;
      hasAmp=1;
    }else{
      hasAmp = 0;
    }
    //concatenate to the end of the History to store all the commands
    strcat(HISTORY,str);
    strcat(HISTORY,",");
    }
    
    //forking here
     pid = fork();
    
    if(pid < 0) {
      printf("Fork failed");//fork fails if pid < 0
      exit(EXIT_FAILURE);
    }

    else if(pid > 0 ){
      if(hasAmp){
	wait(NULL);
   
      }
      else{
	printf("Parent doesn't wait for child to finish.\n.");
      }

    }
    else if(pid == 0){
      if(recentFlag){
	int i = 0;
	//handle ! commands
	char *split = strtok(recent[0]," ");
	argv[0] = split;
	i++;
	
	while(split != NULL){
	  split = strtok(NULL," ");
	  if(split != NULL){
	    argv[i] = split;
	  }
	  i++;
	}
	
	recentFlag = 0;
	argv[i] = NULL;
      }

      recentFlag = 0;
      if(execvp(argv[0],argv) == -1){
	should_run = 0;
	recentFlag = 0;
	//printf("Illegal command\n");
      }else{
	//printf("\nCSCI3120>");
	
      }
    }
      
  
    //printf("after execlp****\n");
     // printf("CSCI3120>\n");
  }
  printf("Program finished!.\n");
  exit(0);
}
