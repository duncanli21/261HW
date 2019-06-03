#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


/*  Create a task from the description and the priority

    param:  priority    priority of the task
    param:  desc    	pointer to the description string
    pre:    none
    post:   none
	ret: 	a task with description and priority
*/
TYPE createTask (int priority, char *desc) 
{
	TYPE newTask;
	newTask.priority = priority;
	strcpy(newTask.description, desc);
	return newTask;
}

/*  Save the list to a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file to which the list is saved
    pre:    The list is not empty
    post:   The list is saved to the file in tab-delimited format.
			Each line in the file stores a task, starting with the 
			task priority, followed by a tab character (\t), and 
			the task description.
			
			The tasks are not necessarily stored in the file in 
			priority order. 
	
*/
void saveList(DynArr *heap, FILE *fp)
{
  	/* FIX ME */
	int i;
	
	TYPE left, right; 

	assert(heap); 

	assert(fp); 

	
	fp = fopen("answer.txt", "w"); 

	for(i=0; i< heap->size; i++)
	{
		fprintf(fp, "%d\t%s\n", heap->data[i].priority, heap->data[i].description);
	}

/*
	while(i <= heap->size)
	{
		fprintf(fp, "%d %s", heap->data[pos].priority)

		i++; 

		left = heap->data[(pos*2)+1]; 
		right = heap->data[(pos*2)+2]; 

		if(compare(left, right) == 1)
			pos = (pos*2)+1; 
	}*/ 

	fclose(fp); 
	
}

/*  Load the list from a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file
    pre:    none
    post:   The tasks are retrieved from the file and are added to the list.
			Refer to the saveList() function for the format of tasks in the file				
*/
void loadList(DynArr *heap, FILE *fp)
{
  	/* FIX ME */

	int i = 0; 
	char c; 
	int priority; 
	char des[128]; 
	TYPE todo; 
	int j; 


	while((c = fgetc(fp)) != EOF)
	{

		fscanf(fp, "%d", &priority); 

		printf("priority = %d \n", priority); 

			while(c != '\n')
			{

				c = fgetc(fp); 
				des[i] = c; 
				printf("%c", des[i]); 
				++i; 
			}
		
		todo = createTask(priority, des); 

		for(j=0; j<i; j++)
		{
			des[j] = ' '; 
		}

		i=0; 
		j=0; 

		addHeap(heap, todo); 

		/*printList(heap);*/ 
	}
	
}

/*  Print the list

    param:  heap    pointer to the list
    pre:    the list is not empty
    post:   The tasks from the list are printed out in priority order.
			The tasks are not removed from the list.
*/
void printList(DynArr *heap)
{
  	/* FIX ME  */

	int i; 
	int j,z; 
	int a; 

	DynArr* buf = newDynArr(heap->size); 

	for(i=0; i<heap->size; i++)
	{
		buf->data[i] = heap->data[i]; 
		buf->size++; 
	}

	
   for (j = 0; j < heap->size-1; j++)       
  {
       for (z = 0; z < heap->size-j-1; z++)  
           if (compare(buf->data[z], buf->data[z+1]) == 1) 
              swapDynArr(buf, z, z+1); 
  }

  for(a=0; a< heap->size; a++)
  {
	  printf("%d\t%s\n", buf->data[a].priority, buf->data[a].description); 
  }

	freeDynArr(buf); 
}

/*  Compare two tasks by priority

    param:  left    first task
    param:  right 	second task
    pre:    none
    post:   none
	ret: 	-1 if priority of left < priority of right
			1 if priority of left > priority of right
			0 if priority of left = priority of right
*/
int compare(TYPE left, TYPE right)
{
	if (left.priority < right.priority)
		return -1;
	else if (left.priority > right.priority)
		return 1;
	else
		return 0;
}
