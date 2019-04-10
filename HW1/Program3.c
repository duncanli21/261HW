/* CS261- HW1 - Program3.c*/
/* Name: Liam Duncan
 * Date: 4/3/19
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

void sort(int* number, int n){
     /*Sort the array of integeres of length n*/     

      /* insertion sort */ 

     int q, w, key; 

     for(q=1; q<n; q++)
     {
          w=q; 

          while(w>0 && number[w-1] > number[w])
          {
               key = number[w];
               number[w] = number[w-1]; 
               number[w-1] = key; 
               w--; 
          }
     }
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/

    int n = 20, i; 
    
    /*Allocate memory for an array of n integers using malloc.*/

    int* array; 
    
    array = (int*)malloc(n * sizeof(int)); 

    /* Check for errors */ 

    if(array == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0); 
    }
    
    
    /*Fill this array with random numbers, using rand().*/

    for(i=0; i<n; ++i)
    {
        array[i] = rand(); 
    }
    
    /*Print the contents of the array.*/

    for(i=0; i<n; ++i)
    {
        printf("%d\n", array[i]);
    }

    /*Pass this array along with n to the sort() function of part a.*/
    
    sort(array, n);

    /*Print the contents of the array.*/ 

    printf("\nThe sorted array:\n");

    for(i=0; i<n; i++)
    {
        printf("%d\n", array[i]); 
    }
    
    return 0;
}
