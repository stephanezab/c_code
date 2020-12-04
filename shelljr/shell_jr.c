/* Implement your shell here */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <err.h>
#include <sysexits.h>
#include <sys/wait.h>

#define MAX  1024

int main(){
  FILE* input;
  char line[MAX+1];
  char* argv[3];
  char cmd1[MAX+1], cmd2[MAX+1];
  pid_t child;
  int value;
	    

  input=stdin;
  argv[0] = NULL;
  argv[1]= NULL;
  argv[2]= NULL;
  
  printf("shell_jr: ");
  fflush(stdout);

  while((fgets(line, MAX+1, input))){
   
    value = 0; 
    sscanf(line, "%s%s", cmd1, cmd2);

    argv[0] = cmd1;
    
    argv[1]= cmd2;
    /*argv[2]= NULL;*/

    if( strncmp(argv[0], "exit", 4)==0 ||
	strncmp(argv[0], "hastalavista", 12)==0 ){

      fprintf(stdout,"See you\n");
      exit(0);
    }
    else if(strncmp(argv[0], "cd", 2)==0){
      value = chdir(cmd2);
      if(value == -1){
      
      printf("Cannot change to directory %s\n", cmd2);
      }
    }
    else{
      
      child = fork();

      if(child == -1){
      
      perror("fork error"); 
      
      }
      else if( child > 0){

	wait(NULL);
 
      }
      else{
	
	value = execvp(argv[0], (char * const *) argv);

	if(value == -1){
	  printf("Failed to execute %s", line);
	  fflush(stdout);
	  exit(EX_OSERR);
	}
 
      }
    }
    printf("shell_jr: ");
    fflush(stdout);


  }
    return 0;
}