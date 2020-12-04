/*
******************************************
Title: draw_figures.c
This program allows the user to draw shape
Author: Stephane Zabayo
******************************************
*/

#include<stdio.h>
int draw_rectangle(int,int,char);
int valid_character (char);
int draw_triangle(int,char);

int main(){
  int choice,width,length,size,return_value;
  char character;
  do{
     printf("Enter 1(rectangle), 2(triangle), 3(other), 0(quit): "); 
     scanf("%d", &choice);   /* reads choice */
     
     if(choice==1){   /* reads character, width, and length for the rectangle */
       
       printf("Enter character, width and length: ");
       scanf(" %c %d %d", &character, &width, &length);

       return_value=draw_rectangle(length,width,character);
       if( return_value==0){
        printf("Invalid data provided.\n");
        }
      
     }
     else if (choice==2){   /* reads size and character for the triangle */
       
       printf("Enter character and size: ");
       scanf(" %c %d", &character, &size);
       return_value=draw_triangle(size, character);
       
       if(return_value==0){
       printf("Invalid data provided.\n");
       }
     }
     else if (choice>2){
       printf("Invalid choice.\n");
     }
     else{
      
     }
    
  }while(choice!=0);

  printf("Bye Bye.\n");
  return 0;
}

/*
This function prints a rectangle
 */

int draw_rectangle(int l,int w,char  character){
  int i,j;
  int validcharacter;

  if(l<=0){
    return 0;
  }
  if(w<=0){
    return 0;
  }

  validcharacter=valid_character (character);
  
  if(validcharacter==0){
    return 0;
  }

  

  for( i=0;i<w;i++){
    for( j=0;j<l;j++){
      printf("%c",character);
    }
    printf("\n");
  }
  return 1;

}

/*
This function checks for valide characters
 */

int valid_character (char charact){
  if(charact=='%'){
    return 1;
  }

  if(charact=='*'){
    return 1;
  }

  if(charact=='#'){
    return 1;
  }
  
  return 0;
  
}
/*
This function prints a triangle
 */

int draw_triangle ( int size, char character){

  int i, j, character_check;
  
  if( size <=0){
  return 0;
  }
  
  character_check=valid_character(character);
  
  if( character_check==0){
  return 0;
  }

 

  for( i=1; i<=size;i++){
    
    for(j=1;j<=size-i;j++){
      printf(" ");
    }
    for(j=1; j<=2*i-1; j++){
      printf("%c", character);
    }
    printf("\n");
  }

  return 1;
  

}
