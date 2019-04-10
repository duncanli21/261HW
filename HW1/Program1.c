/* CS261- HW1 - Program1.c*/
/* Name: Liam Duncan
 * Date: 4/2/19
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /* Increment a */

    ++*a;
    
    /* Decrement  b */

    --*b; 
    
    /* Assign a-b to c */

    c = (*a)-(*b); 
    
    /* Return c */

    return c; 
}

int main(){
    /* Declare three integers x,y and z and initialize them randomly to values in [0,10] */

    int *x;
    int *y;
    int *z; 


    int q = rand()% 10+1; 

    x = &q; 

    int w = rand()% 10+1;

    y = &w;

    int e = rand()% 10+1; 

    z = &e;

    /* Print the values of x, y and z */

    printf("x = %d", *x); 

    printf("\ny = %d" , *y);

    printf("\nz = %d", *z);

    
    
    /* Call foo() appropriately, passing x,y,z as parameters */

    int a = foo(x, y, *z); 

    printf("\nCall foo function\n");

    
    /* Print the values of x, y and z */

    printf("x = %d", *x); 

    printf("\ny = %d" , *y);

    printf("\nz = %d\n", *z);
    
    /* Print the value returned by foo */

    printf("The value returned by foo is %d\n", a);
 
    /* Is the return value different than the value of z?  Why? */

    /* The return value is different than the value of Z because Z was not passed into the 
    function as a pointer so the function made a copy of z instead of changing z directly. 
    this means that the value returned by the function was a completely different variable 
    than z */ 


    return 0;
}
    
    
