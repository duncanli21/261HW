/* CS261- HW1 - Program2.c*/
/* Name:Liam Duncan
 * Date: 4/2/19
 * Solution description:
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	char initials[2];
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/

     struct student* students;

     int n = 10; 

     students = (struct student*)malloc(n * sizeof(struct student));

      if (students == NULL) { 
        printf("Memory not allocated.\n"); 
        exit(0); 
    }
     
     /*return the pointer*/

     return students; 
}

void generate(struct student* students){
     /*Generate random initials and scores for ten students.
	The two initial letters must be capital and must be between A and Z. 
	The scores must be between 0 and 100*/

     int i =0;

     while( i < 10)
     {
          students[i].score = rand()%101; 

          students[i].initials[0] = 'A' + (rand()%26);

          students[i].initials[1] = 'A' + (rand()%26);

          i++; 
     }
     
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              1. Initials  Score
              2. Initials  Score
              ...
              10. Initials Score*/

     int i = 0;

     while(i < 10)
     {

          printf("%d. ", i+1);

          int j = 0; 
          while(j < 2)
          {
               printf("%c", students[i].initials[j]);

               j++;
          }

          printf(" %d\n", students[i].score);

          i++; 
     }
     
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     
     int total, i=0; 

     while(i < 10)
     {
         total += students[i].score; 

          ++i;
     }

     int avg = total/10; 

     printf("\nThe average score is: %d\n", avg); 


}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/

     free(stud); 
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/

    stud = allocate(); 
    
    /*call generate*/

    generate(stud); 
    
    /*call output*/

     output(stud);
    
    /*call summary*/

     summary(stud); 
    
    /*call deallocate*/

    deallocate(stud); 

    return 0;
}
