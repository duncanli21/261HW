/* CS261- HW1 - Program4.c*/
/* Name: Liam Duncan
 * Date: 4/3/19
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

struct student{
	char initials[2];
	int score;
};

void sort(struct student* students, int n){
     /*Sort n students based on their initials*/     

     int q, w; 
     struct student key; 

     for(q=1; q<n; q++)
     {
          w=q; 

          while(w>0 && students[w-1].initials[0] > students[w].initials[0])
          {
               key = students[w];
               students[w] = students[w-1]; 
               students[w-1] = key; 
               w--; 
          }
     }
}

int main(){
    /*Declare an integer n and assign it a value.*/

    int n = 7; 
    
    /*Allocate memory for n students using malloc.*/

    struct student* students; 

    int i = 0; 

    students = (struct student*)malloc(n * sizeof(struct student));
    
    /*Generate random IDs and scores for the n students, using rand().*/

     while( i < n)
     {
          students[i].score = rand()%101; 

          students[i].initials[0] = 'A' + (rand()%26);

          students[i].initials[1] = 'A' + (rand()%26);

          i++; 
     }
    
    /*Print the contents of the array of n students.*/

    printf("\nList of students before sorting:\n"); 

     int j = 0;

     while(j < n)
     {

          printf("%d. ", j+1);

          int q = 0; 
          while(q < 2)
          {
               printf("%c", students[j].initials[q]);

               q++;
          }

          printf(" %d\n", students[j].score);

          j++; 
     }

    /*Pass this array along with n to the sort() function*/

    sort(students, n);
    
    /*Print the contents of the array of n students.*/

    printf("\nList of students after sorting\n");

    j = 0;

     while(j < n)
     {

          printf("%d. ", j+1);

          int q = 0; 
          while(q < 2)
          {
               printf("%c", students[j].initials[q]);

               q++;
          }

          printf(" %d\n", students[j].score);

          j++; 
     }

     free(students);
    
    return 0;
}
