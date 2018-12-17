#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
char *recent[41];
char HISTORY[10000];
int commandNum =0;
char *HISTORY2[41];
struct Node{
  int num;
  char *commandName;
  struct Node *next;
};

void printList(struct Node *node){
  while(node != NULL){
    printf("%s->",node->commandName);
    node = node->next;
  }
}

void forking(char* argv){
  pid_t pid = fork();
  if(pid == 0){
    if(execvp(argv[0],argv) == -1)
      exit(EXIT_FAILURE);
  }
  else if(pid > 0){
    wait(NULL);
  }
}

void main(){
  struct Node* head = NULL;
  head = (struct Node*)malloc(sizeof(struct Node));
  printf("Before execlp*****\n");
  char *argv[41]={NULL};
  int should_run = 1;
  
  //& indicates that the parent wait for the child to terminates
  //by default, parent doesn't wait 
  int hasAmp = 0;
  pid_t pid;
  
  while(should_run){
    printf("CSCI312O>");
    //HISTORY2[commandNum] = str;
    //commandNum++;
    //Use this String to store the string to accept user input
    char str[256];
    scanf("%[^\n]%*c",str);
    
    if(strcmp(str,"history") == 0){
      //printf("history;");
      char *split = strtok(HISTORY,",");
      int i = 0;
      HISTORY2[i] = split;
      i++;
      printf("%sLMAO",HISTORY2[0]);
      while( split != NULL){
	split = strtok(NULL,",");
	if (split != NULL ){
	  HISTORY2[i] = split;
	  printf("%s\t",HISTORY2[i]);
	  i++;
	  commandNum++;
	}
      }
      printf("\n");
      HISTORY2[i] = NULL;
      printf("%slksm", HISTORY2[i-1]);
      for(int j = i - 1; j >= 0;j--){
	printf("%d\t%s\n",j+1,HISTORY2[j]);
      }
      //strcat(HISTORY,str);
      //strcat(HISTORY,",");
    }
      strcat(HISTORY,str);
     strcat(HISTORY,",");
    printf("%s\n",HISTORY);
    
    
    if(strcmp(str,"!!")!=0){
    //word equals to the first word of string seperated by space character 
    char *word = strtok(str," ");
    int i = 0;
    argv[i] = word;
    //recent[i] = word;
    i++;
    
    //Seperate all the words of the command and put them in the correct order
    while(word != NULL){
      word = strtok(NULL," ");
      argv[i] = word;
      //recent[i] = word;
      //printf("%skm",recent[i]);
      i++;
    }
    
    //indicates the end of commands
    argv[i]=NULL;
    recent[i]=NULL;
    
    
    //need to delete the & symbol, since execvp doesn't accept this symbol
    //and set the hasAmp flag equals to one
    if(strcmp(argv[i-2],"&") == 0){
      argv[ i - 2 ] = NULL;
      hasAmp=1;
    }
    }else{
      printf("%skmn",HISTORY2[commandNum-1]);
    }
    //forking(*argv);
    //fork here
     pid = fork();
    
    if(pid < 0) {
      printf("Fork failed");//fork fails if pid < 0
      exit(EXIT_FAILURE);
    }

    else if(pid > 0 ){
      // struct Node* command = (struct Node*)malloc(sizeof(struct Node));
      //command->num = ++commandNum;
      // command->commandName = str;
      //command->next = head;
      //head = command;
      if(hasAmp){
	wait(NULL);
	//struct Node* command = (struct Node*)malloc(sizeof(struct Node));
	//command->num = ++commandNum;
	//command->commandName = str;
	//command->next = head;
	//head = command;
	//printList(head);
      }
      else{
	printf("Parent doesn't wait for child to finish.\n.");

      }

    }
    else if(pid == 0){
      //struct Node* command = (struct Node*)malloc(sizeof(struct Node));
      //command->num = ++commandNum; 
      //command->commandName = str;
      //command->next = head;
      //head = command;
      if(execvp(argv[0],argv) == -1)
	should_run = 0;
    }
      
   
  
     printf("after execlp****\n");
  }
  //printList(head);
}
