/*********************
Name: Stephane Zabayo
ID: 116998604
DIrectory ID: szabayo
*********************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "calendar.h"
#include "my_memory_checker_216.h"

int init_calendar(const char *name, int days,
                  int (*comp_func) (const void *ptr1, const void *ptr2),
                  void (*free_info_func) (void *ptr), Calendar ** calendar){

  int size, i;
  
  if((!calendar) || (!name)){
    return FAILURE;
  }
  
  
  *calendar = malloc(sizeof(Calendar));
  if((!calendar)){
    return FAILURE;
  }

  if(days < 1){
    return FAILURE;
  }
  
  size = strlen(name);
  (*calendar)->name = malloc(size + 1);
  if((!(*calendar)->name)){
    return FAILURE;
  }
  
  strcpy((*calendar)->name, name);

  (*calendar)->events = calloc( days, sizeof(Event));

  if((!(*calendar)->events)){
    return FAILURE;
  }


  (*calendar)->days = days;
  (*calendar)->total_events = 0;
  (*calendar)->comp_func = comp_func;
  (*calendar)->free_info_func = free_info_func;
  
  for(i = 1; i <= days; i++){
  (*calendar)->events[i] = NULL;
  }
  
  

  return SUCCESS;                  
                  
}


int print_calendar(Calendar *calendar, FILE *output_stream, int print_all){

  int i;
  Event *current;

  if((!calendar) || (!output_stream)){
    return FAILURE;
  }

  if(output_stream == stdout ){
    if(print_all == 1){
      fprintf(stdout, "Calendar's Name: \"%s\"\n",calendar->name);
      fprintf(stdout, "Days: %d\n", calendar->days);
      fprintf(stdout, "Total Events: %d\n", calendar->total_events);
      fprintf(stdout, "\n");
    }
    fprintf(stdout, "**** Events ****\n");

    if(calendar->total_events > 0){
      for( i = 1; i <= calendar->days; i++){

	fprintf(stdout,"Day %d\n", i);

	if((calendar->events[i])){

	  current = calendar->events[i];

	  while((current)){

	    fprintf(stdout, "Event's Name: \"%s\", ", current->name);
	    fprintf(stdout, "Start_time: %d, ", current->start_time);
	    fprintf(stdout, "Duration: %d\n", current->duration_minutes);

	    current = current->next;
	  }
	}/*if*/

      }/*for*/
      
    }/*if*/
  


  }/*if*/

  
  return 0;
}

int destroy_calendar(Calendar *calendar){

  Event *current, *prev = NULL;
  int i;

  if((!calendar)){
    return FAILURE;
  }

  if(calendar->total_events > 0){
  
    for(i = 1; i <= calendar->days; i++){
    
      if((calendar->events[i])){
	current = calendar->events[i];

	while((current)){
	  prev = current;
	  current = current->next;
	  free(prev->name);
     
	  if((calendar->free_info_func) && (prev->info)){
	    calendar->free_info_func(prev->info);
	  }
	  free(prev);
	}


      }
      
    }
  }
  

  free(calendar->name);
  free(calendar->events);
  free(calendar);
 
return 0;
}

int add_event(Calendar *calendar, const char *name, int start_time,
              int duration_minutes, void *info, int day){

  Event *event, *current = calendar->events[day], *prev = NULL, *find_event2;
  
  int size = 0;

  if((!calendar) || (!name)){
    return FAILURE;
  }

  if(start_time < 0 || start_time > 2400){
    return FAILURE;
  }

  if(duration_minutes <= 0){
    return FAILURE;
  }

  if(day < 1 || day > calendar->days){
    return FAILURE;
  }
  

  event = malloc(sizeof(Event));
  if((!event)){
    return FAILURE;
  }
  
  size = strlen(name);
  event->name = malloc(size + 1);
  if((!event->name)){
  return FAILURE;
  }

  strcpy(event->name, name);
  event->start_time = start_time;
  event->duration_minutes = duration_minutes;
  event->info = info;

  while((current) && (calendar->comp_func(event, current) > 0)){
    prev = current;
    current = current->next;
  }


  if(find_event(calendar, name, &find_event2) == SUCCESS){
    free(event->name);
    free(event);
    return FAILURE;
  }
  

  event->next = current;

  if((!prev)){
    calendar->events[day] = event;
    calendar->total_events++;
  }
  else{
    prev->next = event;
    calendar->total_events++;
  }

  

  

  return SUCCESS;
}


int find_event(Calendar *calendar, const char *name, Event **event){

  int i, find=0;

  if((!calendar)){
    return FAILURE;
  }

  for(i=1; i <= calendar->days; i++){
    
    if(find_event_in_day(calendar, name, i, event) == SUCCESS){
      find = 1;
    }
    
  }/*for end*/

  if(find == 1){
    return SUCCESS;
  }
  else{
    return FAILURE;
  }
  
}


int find_event_in_day(Calendar *calendar, const char *name, int day,
                      Event **event){

  Event *current;
  int find = 0;

  if((!calendar) || (!name)){
    return FAILURE;
  }

  if(day < 1 || day > calendar->days){
    return FAILURE;
  }
  

  if((calendar->events[day])){

    current = calendar->events[day];
    while((current)){

      if( strcmp(current->name, name) == 0){

	if((event)){
	  *event = current;
	  find = 1;
	}
      }

      current = current->next;

    }/*while end*/
  }
  if(find == 1){
    return SUCCESS;
  }
  else{
    return FAILURE;
  }
  
}


int remove_event(Calendar *calendar, const char *name){

  Event *current, *prev;
  int i, find;

  if((!calendar) || (!name)){
    return FAILURE;
  }

  for( i = 1; i <= calendar->days; i++){
    prev = NULL;

    if((calendar->events[i])){

      current = calendar->events[i];
      find = 1;
      while((current) && (strcmp(current->name, name) != 0)){

	prev = current;
	current = current->next;

      }/*while end*/
      

      if((!current)){
	find = 0;
      }

      if((!prev) && (find == 1)){ /*remove first*/

	calendar->events[i] = current->next;
	calendar->total_events--;

	free(current->name);
 
	if((calendar->free_info_func) && (current->info)){
 
	  calendar->free_info_func(current->info);
	}
	free(current);
	
      }
      else if((prev) && (find == 1)){
	prev->next = current->next;
	calendar->total_events--;

	free(current->name);
 
	if((calendar->free_info_func) && (current->info)){
 
	  calendar->free_info_func(current->info);
	}
	free(current);
	
      }
      
      
    }/*if*/
    
  }/*for*/

  if( find == 1){
    return SUCCESS;
  }
  else{
    return FAILURE;
  }
  
}


void *get_event_info(Calendar *calendar, const char *name){

  int i;
  Event *current;

  for(i = 1; i <= calendar->days; i++){
    if((calendar->events[i])){

      current = calendar->events[i];

      while((current)){
	
	if(strcmp(current->name, name) == 0){
	  return current->info;
	}

	current = current->next;
	
      }/*while end*/

      
    }
  }

  return NULL;
}


int clear_calendar(Calendar *calendar){
  int i;

  if((!calendar)){
    return FAILURE;
  }

  for(i = 1; i <= calendar->days; i++){

    if(clear_day(calendar, i) == FAILURE){
	return FAILURE;
      }

  }
    
    return SUCCESS;
}


int clear_day(Calendar *calendar, int day){

  Event *current, *prev = NULL;

  if((!calendar)){
    return FAILURE;
  }
  if(day < 1 || day > calendar->days){
    return FAILURE;
  }

  if((calendar->events[day])){
    current = calendar->events[day];

    while((current)){
      prev = current;
      current = current->next;
      free(prev->name);

      if(calendar->free_info_func != NULL && prev->info != NULL){
	calendar->free_info_func(prev->info);
      }
      free(prev);
      calendar->total_events--;
    }
    calendar->events[day] = NULL;
    
    
  }
  
    
  return SUCCESS; 
  
}
