/*116998604*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "command.h"
#include "executor.h"
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <err.h>
#include <sysexits.h>
#include <sys/wait.h>

/*static void print_tree(struct tree *t);*/
static int execute_2(struct tree *t, int fd_input, int fd_ouput);

int execute(struct tree *t) {
   execute_2(t, STDIN_FILENO ,STDOUT_FILENO);

  /* print_tree(t);*/

   return 0;
}

static int execute_2(struct tree *t, int fd_input, int fd_ouput){
  int child, value, status;
  
  value = 0;
  
  
   if (t->conjunction == NONE) {
     
     if( strncmp(t->argv[0], "exit", 4) == 0){

       exit(0);
    }
    else if(strncmp(t->argv[0], "cd", 2) == 0){
      if(t->argv[1] == NULL){
	t->argv[1] = getenv("HOME");
      }
     
      value = chdir(t->argv[1]);
      if(value == -1){
      
      perror(t->argv[1]);
      }
      
    }
    else{
      
      child = fork();

      if(child == -1){
      
      perror("fork error"); 
      
      }
      else if( child > 0){  /*parent*/
      
     wait(&status);
     if( WIFEXITED(status)){
       if(WEXITSTATUS(status)==0){
       }
       else{

	 value = -1;
       }
     }
     
     
     
 
      }
      else{    /*child*/
	int fd1, fd2;
	
	if(t->input != NULL){ /* checking for input redirection*/

	  if( (fd1 = open(t->input, O_CREAT | O_RDONLY, 0664)) < 0){
	    perror("File opening error");
	  }

	  if( (dup2(fd1, fd_input)) < 0){
	    perror("dup2 error");
	  }

	  close(fd1);
	}

	if(t->output != NULL){ /* checking for output redirection*/
	  if( (fd2 = open(t->output, O_CREAT | O_WRONLY, 0664))< 0){
	    perror("File openning error");
	  }

	  if( (dup2(fd2, fd_ouput)) < 0){
	    perror("dup2 error");
	  }
	  
	  close(fd2);
	}
	  
	
	value = execvp(t->argv[0], t->argv);

	if(value == -1){
	  fprintf(stderr,"Failed to execute %s\n", t->argv[0]);
	  exit(value);
	}
      }
    }
   }
   else if(t->conjunction == AND) { /*AND*/
     int fd1, fd2;

     if(t->input != NULL){ /* checking for input redirection*/

       if( (fd1 = open(t->input, O_CREAT | O_RDONLY, 0664)) < 0){
	 perror("File opening error");
       }

       if( (dup2(fd1, fd_input)) < 0){
	 perror("dup2 error");
       }

       close(fd1);
     }

     if(t->output != NULL){ /* checking for output redirection*/

       if( (fd2 = open(t->output, O_CREAT | O_WRONLY, 0664))< 0){
	 perror("File openning error");
       }
       if( (dup2(fd2, fd_ouput)) < 0){
	 perror("dup2 error");
       }
       close(fd2);
     }

     value = execute_2(t->left, fd_input, fd_ouput);

     if( value != -1){
    
       execute_2(t->right, fd_input, fd_ouput);
     }
     
     
   }
   else if(t->conjunction == PIPE) { /*PIPE*/
     int pipe_fd[2], child2;

     if (pipe(pipe_fd) < 0) {
       perror("pipe error");
     }

     if ((child2 = fork()) < 0) {
      perror("fork error");
     }

     if(child2 == 0){ /*child*/ /*deal with left*/
       close( pipe_fd[0]); /* closing read end */

       if(t->left->output != NULL){
	 
	 printf("Ambiguous output redirect.\n");
       }
       else{
	 if (dup2(pipe_fd[1], fd_ouput) < 0) {

	   perror("dup2 error");
	 }
	 close(pipe_fd[1]);

	 execute_2(t->left, fd_input, fd_ouput);
       }
       
       
     }
     else{ /*parent deal with the right*/
       close(pipe_fd[1]);
       

       if(t->right->input != NULL){
	 
	 if(t->left->output == NULL){
	   printf("Ambiguous input redirect.\n");
	 }
   else{
   wait(NULL);
   }
	 
       }
       else{

	 if (dup2(pipe_fd[0], fd_input) < 0) {
	   perror("dup2 error");
	 }

	 close(pipe_fd[0]);

	 execute_2(t->right, fd_input, fd_ouput);
	 wait(NULL);
       }
             
       
     }
     
   }
   else if(t->conjunction == SUBSHELL){
     int child3;

     if ((child3 = fork()) < 0) {
      perror("fork error");
     }

     if( child3 == 0){ /*child*/
       int fd1, fd2;

       if(t->input != NULL){ /* checking for input redirection*/

	 if( (fd1 = open(t->input, O_CREAT | O_RDONLY, 0664)) < 0){
	   perror("File opening error");
	 }

	 if( (dup2(fd1, fd_input)) < 0){
	   perror("dup2 error");
	 }
	 close(fd1);
       }

       if(t->output != NULL){ /* checking for output redirection*/

	 if( (fd2 = open(t->output, O_CREAT | O_WRONLY, 0664))< 0){
	   perror("File openning error");
	 }
	 if( (dup2(fd2, fd_ouput)) < 0){
	   perror("dup2 error");
	 }
	 close(fd2);
       }
       
       execute_2(t->left, fd_input, fd_ouput); 
       exit(0);
       
     }
     else{ /*parent*/

       wait(NULL);
	
       
     }
     
   }/*SUBSHELL END*/
     
   
     return value;
}
/*
static void print_tree(struct tree *t) {
   if (t != NULL) {
      print_tree(t->left);

      if (t->conjunction == NONE) {
         printf("NONE: %s, ", t->argv[0]);
      } else {
         printf("%s, ", conj[t->conjunction]);
      }
      printf("IR: %s, ", t->input);
      printf("OR: %s\n", t->output);

      print_tree(t->right);
   }
}

*/
