#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "calendar.h"
#include "my_memory_checker_216.h"

/*****************************************************/
/* In this file you will provide tests for your      */
/* calendar application.  Each test should be named  */
/* test1(), test2(), etc. Each test must have a      */
/* brief description of what it is testing (this     */
/* description is important).                        */
/*                                                   */
/* You can tell whether any test failed if after     */
/* executing the students tests, you executed        */
/* "echo $?" on the command line and you get a value */
/* other than 0.  "echo $?" prints the status of     */
/* the last command executed by the shell.           */ 
/*                                                   */
/* Notice that main just calls test1(), test2(), etc.*/
/* and once one fails, the program eventually        */
/* return EXIT_FAILURE; otherwise EXIT_SUCCESS will  */
/* be returned.                                      */
/*****************************************************/

static int comp_minutes(const void *ptr1, const void *ptr2) {
   return ((Event *)ptr1)->duration_minutes - ((Event *)ptr2)->duration_minutes;
}

/*This test checks if init_calendar, print_calendar, and destroy_calendar 
is working. Also, if print_all is 0 */

static int test1() {
   int days = 3;
   Calendar *calendar;
   printf("-------------------TEST 1 STARTS------------------\n");

   if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      add_event(calendar, "task1", 300, 50 , NULL, 2);
      add_event(calendar, "task2", 1000, 30 , NULL, 2);
      
      if (print_calendar(calendar, stdout, 0) == SUCCESS) {
         return destroy_calendar(calendar);
      }      
   }
   
   return SUCCESS;
}

/* This test checks for when adding the same event */

static int test2() {
   int days = 4;
   Calendar *calendar;
   
   printf("\n-------------------TEST 2 STARTS------------------\n");
   if (init_calendar("2029", days, comp_minutes, NULL, &calendar) == SUCCESS) {
     
     add_event(calendar, "plan2", 200, 50 , NULL, 2);
     print_calendar(calendar, stdout, 1);
     /*try adding the same event again */
     
     if(add_event(calendar, "plan2", 200, 50 , NULL, 2)==FAILURE){
       destroy_calendar(calendar);
       return SUCCESS;
       }
   }

   return FAILURE;
}

/*This test checks if clear_day and Clear_calendar
are working correctly */

static int test3() {
  int days = 5;
  Calendar *calendar;
   
   printf("\n-------------------TEST 3 STARTS------------------\n");
   init_calendar("best year", days, comp_minutes, NULL, &calendar); 
   add_event(calendar, "task1", 300, 50 , NULL, 2);  
   add_event(calendar, "task2", 1000, 30 , NULL, 2); 
   add_event(calendar, "task3", 20, 40 , NULL, 3); 
  
   print_calendar(calendar, stdout, 1);
   
   if(clear_day(calendar, 2)== FAILURE){

     return FAILURE;
   }
   
   print_calendar(calendar, stdout, 1);
   
   
   if(clear_calendar(calendar)== FAILURE){

     return FAILURE;
   }
      
   print_calendar(calendar, stdout, 1);
   destroy_calendar(calendar);
   
   return SUCCESS;
    
}

/*This test tries to remove an event that doesn't exist*/

static int test4() {
   int days = 4;
   Calendar *calendar;
   
   printf("\n-------------------TEST 4 STARTS------------------\n");
   init_calendar("2030", days, comp_minutes, NULL, &calendar);
   
   add_event(calendar, "plan1", 200, 50 , NULL, 1);
   add_event(calendar, "plan2", 200, 50 , NULL, 1);
   add_event(calendar, "plan3", 200, 50 , NULL, 3);
   print_calendar(calendar, stdout, 1);
   
   remove_event(calendar, "plan3");
   if(remove_event(calendar, "plannnnn1")==FAILURE){
     print_calendar(calendar, stdout, 1);
     destroy_calendar(calendar);
     return SUCCESS;
   }
        
   

   return FAILURE;
}

/* This test checks finding an event
   with an invalid */

static int test5() {
   int days = 4;
   Calendar *calendar;
   Event *event;
   
   printf("\n-------------------TEST 5 STARTS------------------\n");
   init_calendar("2030", days, comp_minutes, NULL, &calendar);
   
   add_event(calendar, "plan1", 200, 50 , NULL, 1);
   add_event(calendar, "plan2", 200, 50 , NULL, 1);
   add_event(calendar, "plan3", 200, 50 , NULL, 3);
   print_calendar(calendar, stdout, 1);
   
   if(find_event_in_day(calendar, "plan2", 5, &event) == FAILURE){
     printf("\nThe day is invalid\n");
     destroy_calendar(calendar);
     return SUCCESS;
   }
       
   

   return FAILURE;
}

/* This test checks if get_event_info fails 
   if info is not found */ 

static int test6() {
   int days = 3;
   Calendar *calendar;
   
   printf("\n-------------------TEST 6 STARTS------------------\n");
   init_calendar("2030", days, comp_minutes, NULL, &calendar);
   
   add_event(calendar, "workout", 1000, 7 , NULL, 1);
   add_event(calendar, "play", 200, 60 , NULL, 1);
   add_event(calendar, "work", 400, 72 , NULL, 3);
   print_calendar(calendar, stdout, 1);
   
   if((!get_event_info(calendar, "workout"))){

     printf("\nEvent \"workout\" does not have an info\n");
     return destroy_calendar(calendar);
   }
       
   

   return FAILURE;
}

int main() {
   int result = SUCCESS;

   /***** Starting memory checking *****/
   start_memory_check();
   /***** Starting memory checking *****/

   if (test1() == FAILURE) result = FAILURE;
   if (test2() == FAILURE) result = FAILURE;
   if (test3() == FAILURE) result = FAILURE;
   if (test4() == FAILURE) result = FAILURE;
   if (test5() == FAILURE) result = FAILURE;
   if (test6() == FAILURE) result = FAILURE;
   

   /****** Gathering memory checking info *****/
   stop_memory_check();
   /****** Gathering memory checking info *****/
   
   if (result == FAILURE) {
      exit(EXIT_FAILURE);
   }

   return EXIT_SUCCESS;
}
