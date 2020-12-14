/* 
name:Stephane Zabayo
ID: 116998604
*/

#include <stdio.h>
#include <string.h>
#include "text_manipulation.h"


int remove_spaces(const char *source, char *result, int *num_spaces_removed) {
  
  int size,space=0,i,j=0;

  if(source=='\0'){
    return FAILURE;
  }

  size= strlen(source);

  if(size==0 ){
    return FAILURE;
  }

  for( i=0; i<size; i++){
    if( source[i]==' '){
      if( i!=0 && i!=size-1 && source[i+1]!=' ' && source[i-1]!=' '){
	result[j]=source[i];
	j++;
      }
      else{
	space++;
      }
    }
    else{
      result[j]=source[i];
      j++;
    }
  }
  result[j]='\0';

  if(num_spaces_removed!=NULL){

    *num_spaces_removed=space;
  }

    
  return SUCCESS;
}

int center(const char *source, int width, char *result) {

  int i,size=0,space=0;
  
  if(source=='\0'){
    return FAILURE;
  }

  size=strlen(source);

  if(size==0 || width< size){
    
    return FAILURE;
    
  }

  space=(width-size)/2;
  
  

  for(i=0; i<space; i++){
    result[i]=' ';
  }

  for(i=0; i<size; i++){
    result[space+i]=source[i];
  }

  size= strlen(result);

  for(i=0; i<space; i++){
    result[size+i]=' ';
    
  }
  result[size + i]='\0';

  return SUCCESS;


  
}
