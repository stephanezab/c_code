#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "photoalbum.h"

Photo *create_photo(int id, const char *description){
  Photo *photo;
  int size;

  photo=malloc(sizeof(Photo));
  
  if(photo==NULL){
    return NULL;
  }
  
  if(description!=NULL){
    size=strlen(description);
    photo->description=malloc(size+1);
    strcpy(photo1->description,description);
  }
  else{
    photo->description=NULL;
  }

  photo->id= id;
    
  

  return photo;
  
}
void print_photo(Photo *photo){
  if(photo!=NULL){

    if(photo->description !=NULL){

      printf("Photo Id: %d, Description: %s\n", photo->id, photo->description);
    }
    else{
      printf("Photo Id: %d, Description: None\n", photo->id);
    }
  }
}

void destroy_photo(Photo *photo){
  if(photo!=NULL){
    free(photo->description);
    free(photo);
  }
}

void initialize_album(Album *album){
  if(album!=NULL){
    album->size=0;
  }
}

void print_album(const Album *album){

  int i, size;
  Photo *photo;
  
  if(album!=NULL){
    if(album->size==0){
      printf("Album has no photos.\n");
    }
    else{
      size=album->size;

      for(i=0; i<size; i++){
	photo = album->all_photos[i];
	  
	print_photo(photo);
      }
      
    }
  }
  
}
void destroy_album(Album *album){
  int size,i;
  Photo *photo;

  if(album!=NULL){
    size=album->size;

    for(i=0; i <size; i++){
      photo=album->all_photos[i];

      if(photo!=NULL){
	album->size--;
      }
      
      destroy_photo(photo);

      
    }
  }
    
  
}
void add_photo_to_album(Album *album, int id, const char *description){

  Photo *photo;
  int i;
  if(album!=NULL && album->size < MAX_ALBUM_SIZE){
    i = album->size;
    photo = create_photo(id,description);
    
    if(photo!=NULL){
      album->all_photos[i] = photo;
      album->size++;
    }
    
  }
}
