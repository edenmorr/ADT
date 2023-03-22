#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "AdptArray.h"
#include "Person.h"
#include "book.h"




typedef struct AdptArray_
{
    COPY_FUNC copyf_;
    PRINT_FUNC printf_;
	int size;
	PElement* element;
	DEL_FUNC delf_;
	
}AdptArray;



PAdptArray CreateAdptArray(COPY_FUNC copyf, DEL_FUNC delf, PRINT_FUNC printf)
{
	PAdptArray array = (PAdptArray)malloc(sizeof(AdptArray));
	if (array == NULL)
		return NULL;
    array->element = NULL;
	array->size = 0;
    array->copyf_ = copyf;
    array->printf_ = printf;
	array->delf_ = delf;
	

	return array;
}


int GetAdptArraySize(PAdptArray array){

        return array!=NULL? array->size : -1;
        
} 


void DeleteAdptArray(PAdptArray array)
{
	
	if (array == NULL)
		return;
        
	for(int j = 0; j < array->size; j++)
	{
        if ((array->element)[j]!=NULL)
        {

            array->delf_((array->element)[j]);

        }
        
	}

	free(array->element);
	free(array);
}

void PrintDB(PAdptArray array){

    int i;
    for (i = 0; i <array->size; i++)
    {
        if (((array->element)[i] != NULL))
        {
           
            array->printf_(((array->element)[i]));
            

        }
        
    }
    
}

Result SetAdptArrayAt(PAdptArray array, int idx, PElement pn)
{

	PElement* p;
	if (array == NULL)
		return FAIL; 

	if (idx >= array->size) 
	{ 
		

		if ((p = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL; 

		memcpy(p, array->element, (array->size) * sizeof(PElement)); 

		free(array->element); 

		array->element = p; 

	}


    if ((array->element)[idx]!=NULL){
    
        	array->delf_((array->element)[idx]);  

    }
    

	(array->element)[idx] = array->copyf_(pn);


    if (idx >= array->size)
    {
        array->size = idx + 1;
    }
    else{
                array->size = array->size ; 

    }
    
	return SUCCESS;
}




PElement GetAdptArrayAt(PAdptArray array, int idx){
   
   return (array->element)[idx]==NULL ?  NULL : 
                array->copyf_((array->element)[idx]); 
        
}












