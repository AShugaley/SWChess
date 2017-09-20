#include "Chess_ArrayList.h"

SPArrayList* spArrayListCreate(int maxSize)
{
    if (maxSize <= 0)
        return NULL;
    
    SPArrayList * gameMovesList = (SPArrayList*)malloc(sizeof(SPArrayList));
    if (gameMovesList == NULL)
        return NULL;
    
	gameMovesList->elements = (SPArrayListNode*)malloc(maxSize * sizeof(SPArrayListNode));
	gameMovesList->maxSize = maxSize;
	gameMovesList->actualSize = 0;
    return gameMovesList;
}


SPArrayList* spArrayListCopy(SPArrayList* src)
{
    int i = 0;
    if (src == NULL)
        return NULL;
    
    SPArrayList * copyList = spArrayListCreate(src->maxSize);
    
    copyList->actualSize = src->actualSize;
    for (i = 0; i < copyList->actualSize; i++)
    {
        (copyList->elements)[i] = (src->elements)[i]; //possible bug
    }
    return copyList;
    
}


void spArrayListDestroy(SPArrayList* src)
{
    if (src != NULL)
    {
       /* for(int i =0; i<src->maxSize; i++){
            free(&(src->elements[i]));
        }*/
        free(src->elements);	//free to int*
        free(src);
    }
}


SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src)
{
    if (src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    else
    {
        src->actualSize = 0;
    }
    return SP_ARRAY_LIST_SUCCESS;
}


SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, int current_pos_row, int current_pos_col, int prev_pos_row, int prev_pos_col, char pre_pos_fig,char moving_fig)
{
    int i = 0;
    if (src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    
    if (spArrayListIsFull(src))
        return SP_ARRAY_LIST_FULL;
    
    for (i = src->actualSize; i > 0; i--)
    {
        src->elements[i] = (src->elements)[i - 1];
    }
    
   // src->elements = (SPArrayListNode*)malloc(maxSize * sizeof(SPArrayListNode));
    
    src->elements[0].current_pos_row = current_pos_row;
	src->elements[0].current_pos_col = current_pos_col;
	src->elements[0].prev_pos_row = prev_pos_row;
	src->elements[0].prev_pos_col = prev_pos_col;
    src->elements[0].prev_pos_fig = pre_pos_fig;
    src->elements[0].moving_figure = moving_fig;
    src->actualSize++;
    
    return SP_ARRAY_LIST_SUCCESS; 
}


SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, int current_pos_row, int current_pos_col, int prev_pos_row, int prev_pos_col, char pre_pos_fig,char moving_fig)
{
    if (src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    
    if (spArrayListIsFull(src))
        return SP_ARRAY_LIST_FULL;
	
	src->elements[src->actualSize].current_pos_row = current_pos_row;
	src->elements[src->actualSize].current_pos_col = current_pos_col;
	src->elements[src->actualSize].prev_pos_row = prev_pos_row;
	src->elements[src->actualSize].prev_pos_col = prev_pos_col;
    src->elements[src->actualSize].prev_pos_fig = pre_pos_fig;
    src->elements[src->actualSize].moving_figure = moving_fig;

    src->actualSize++;
    
    return SP_ARRAY_LIST_SUCCESS;  
}


SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src)
{
    int i = 0;
    if (src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    
    if (spArrayListIsEmpty(src))
        return SP_ARRAY_LIST_EMPTY;
    
    for (i = 0; i<src->actualSize - 1; i++)
    {
        src->elements[i] = src->elements[i + 1];
    }
    
    src->actualSize--;
    
    return SP_ARRAY_LIST_SUCCESS;
    
    
}


SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src)
{
    if (src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    
    if (spArrayListIsEmpty(src))
        return SP_ARRAY_LIST_EMPTY;
    
    (src->actualSize)--;
    
    return SP_ARRAY_LIST_SUCCESS;
    
}


SPArrayListNode* spArrayListGetAt(SPArrayList* src, int index)
{
    if (src == NULL || index >= src->actualSize || index < 0)
        return NULL;				//maybe we should return here node with a field of invalid - Alex what do you think? 
    return &(src->elements[index]);
}


SPArrayListNode* spArrayListGetFirst(SPArrayList* src)
{
    if (src == NULL || src->actualSize == 0)
        return NULL;			//maybe we should return here node with a field of invalid 
    return &(src->elements[0]);
}


SPArrayListNode* spArrayListGetLast(SPArrayList* src)
{
    if (src == NULL || src->actualSize == 0)
        return NULL;			//maybe we should return here node with a field of invalid 
    return &(src->elements[src->actualSize - 1]);   
}


int spArrayListMaxCapacity(SPArrayList* src)
{
    if (src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    return src->maxSize;
}


int spArrayListSize(SPArrayList* src)
{
    if (src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    return src->actualSize;
}


bool spArrayListIsFull(SPArrayList* src)
{
    if ((src->maxSize > src->actualSize) || (src == NULL))
        return false;
    return true;
}


bool spArrayListIsEmpty(SPArrayList* src)
{
    if ((src->actualSize != 0) || (src == NULL))
        return false;
    return true;
}

