/*This code will use memeory allocation
to implement a linkedlist, and as well
as apply the knowledge of command-line 
argument
Author:Yangfan Chen Date:April 3rd.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 80

//this will define a node structure.
struct node{
  char name[MAX_LEN+1];
  struct node* next;
};

/*this is the function that we will need to compute
the desired output,the first 5 methods perform the pretty
much the similiar function
the last three function are used to compute output when there
is a command line argument field entered.
*/

struct node* insert(struct node* string);
void print_list(struct node* list);
int search(struct node* list , char arr[]);
void print_line(struct node* line);
int read_line(char line[],int len);
int skip_field(char arr[],int num_skip);
int cmp_skip(char arr[],int skip1,char arr2[],int skip2);
int search_skip(struct node* list,char arr[],int argv1);


int main(int argc,char *argv[]){
  //define a node list to store a linkedlist
  struct  node* list=NULL;
  int i=0;
  int ch;//for argc variable
  if(argc==1)
    ch=0;//if argc is 1, meaning that no fields are concerned
  
  else if(argc>2||strlen(argv[1])>1||argv[1][0]<'0'||argv[1][0]>'9'){
    printf("didnt pass command line argument.\n");
    exit(EXIT_FAILURE);
  }
  else{
    //if the function passes the commandline argument
    //i will covert 
    ch=argv[1][0]-'0';
    //printf("%d",ch);
  }
  
  //create a char arrays to store for temporary data
  char arr[MAX_LEN+1];
  
  //if we haven't reached the end of file yet.
  while(read_line(arr,80)!=EOF){
    //the field can be regarded as 0 if no commandline
    if(ch==0){
      if(search(list,arr)==-1){//if we didn't find the array element
	//manipulate the linked list
	struct node* addToFront=malloc(sizeof(struct node));
	strcpy(addToFront->name,arr);
	addToFront->next=list;
	list=addToFront;
      }
    }


    else{
      if(search_skip(list,arr,ch)!=0){//if haven't find the node
	struct node* addWithField=malloc(sizeof(struct node));
	strcpy(addWithField->name,arr);
	addWithField->next=list;
	list=addWithField;
    }
    }


  }


  //print_list(list);
  struct node* reverse=NULL;
  while(list!=NULL){
    struct node* reve=malloc(sizeof(struct node));
    strcpy(reve->name,list->name);
    reve->next=reverse;
    reverse=reve;
    list=list->next;
  }
  //we no long need the list, so need to free them.
  while(list!=NULL){
    struct node*prev=list;
    list=list->next;
    free(prev);
  }
  print_list(reverse);
  while(reverse!=NULL){
    struct node* prev2=reverse;
    reverse=reverse->next;
    free(prev2);
  }
  return 0;
}

//this is the insertion method that we may need
struct node *insert(struct node* list){
  //dynamically allocate a block of memory space to line
  struct node* line= malloc(sizeof(struct node));
  if(line==NULL){
    //if line is NUL,meaning that we haven't read it successfully
    printf("memeory allocation unsuccessful.\n");
    exit(EXIT_FAILURE);//then exit the function
  }
  printf("Enter name of the String:");
  read_line(line->name,MAX_LEN);
  line->next=list;
  
  return line;

}

void print_line(struct node* line){
  //help function to print out the 
  printf("%s\n",line->name);
}
  //this will print the whole list
void print_list(struct node* list){
  while(list!=NULL){
    print_line(list);
    list=list->next;
  }
}

int search(struct node* list,char arr[]){
  //if index is -1, meaning that 
  //we don't have duplicate item
  int index=-1;
  int i=0;
  while(list!=NULL){
    if((strcmp(list->name,arr))==0){
      index=i;//this will return the index of the node
    }
    list=list->next;
    i++;
  }//if not find,-1
  return index;
}





int read_line(char line[],int len){
  int ch,i=0;
  while((ch=getchar())!='\n'&&ch!=EOF){

    if(i<len){
      line[i++]=ch;
    }
    else{//if it exceeds the maximum length 
      //exit the function immediately
      printf("exceeds maximum length");
      exit(EXIT_FAILURE);
    }
  }
  //if not full,add '\0' to the end of string
  //slight modification of the code given in the class
  line[i]='\0';
  return ch;
}

//skip_field function will return the index of the first
//non-white space character
int skip_field(char arr[MAX_LEN+1],int num_skip){
  int i;
  for( i=0;i<MAX_LEN+1;i++){
    if(num_skip==0&&arr[i]!=' '){
      return i;
    }
    if(arr[i]==' '&&arr[i+1]!=' '){
      --num_skip;
    }
    else if(arr[i]=='\0'){
      return i;
    }

  }
  return -1;
 } 


   
int search_skip(struct node* list,char arr[],int skip){
  //int common=-1;
 while(list!=NULL){
    int index1=skip_field(list->name,skip);
    //compare the array with the string that we wanted
    //and then we can decide whether to add it to
    //the linked list or not
    int index2=skip_field(arr,skip);
    if(cmp_skip(list->name,index1,arr,index2)==0)
      return 0;
    list=list->next;
  }
 return -1;
}


int cmp_skip(char arr[],int skip1,char arr2[],int skip2){
  // int cmp=-1;
  //returns -1 if
  // return 0 means two strings are same, -1 means they are not
  if(arr[skip1]=='\0'&&arr2[skip2]=='\0')
    return 0;
  if(arr[skip1]!='\0'&&arr2[skip2]=='\0')
    return -1;
  while(arr[skip1]!='\0'&&arr[skip2]!='\0'){
    if(arr[skip1++]!=arr2[skip2++])
      return -1;
  }
  return 0;
}
