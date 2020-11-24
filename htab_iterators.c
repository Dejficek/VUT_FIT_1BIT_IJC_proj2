/*
 * David Rubý
 * fakulta informačních technologií Vysokého učení technického v Brně
 * příklad 2
 *25. 04. 2019
 */


#include"htab_structures.h"

//This will return iterator of the first htab_item
htab_iterator_t htab_begin(const htab_t * t)
{
    //first will create empty (NULL) iterator
    htab_iterator_t tmp;
    tmp.t = t;
    tmp.ptr = NULL;
    tmp.idx = 0;
    for(unsigned int i = 0; i < t->arr_size; i++)
    {
        //looking for the first item
        if(t->array[i] != NULL)
        {
            //setting data of iterator
            tmp.idx = i;
            tmp.ptr = t->array[i];
            return tmp;
        }
    }
    //returning empty (NULL) iterator
    return tmp;
}

//This will return iterator of the last htab_item
htab_iterator_t htab_end(const htab_t * t)
{
    //first will create empty (NULL) iterator
    htab_iterator_t iterator;
    iterator.t = t;
    //looking for the last item... starting from the end
    for(int i = t->arr_size; i >= 0; i--)
    {
        //if the first record on current index is NULL, it moves on previous index
        if(t->array[i] == NULL)
            continue;
        struct htab_item *tmp = t->array[i];
        while(tmp->next != NULL)
        {
            //moving to the last record on current index
            tmp = tmp->next;
        }
        //setting the data of iterator
        iterator.ptr = tmp;
        iterator.idx = i;
        return iterator;
    }
    return iterator;
}

//returns the next iterator
htab_iterator_t htab_iterator_next(htab_iterator_t it)
{
    //argument is iterator and function returns the next used iterator
    //setting up empty (NULL) iterator
    htab_iterator_t iterator;
    iterator.t = it.t;
    //if the next iterator is not NULL, it will return it, because it is next valid iterator
    if(it.ptr->next != NULL)
    {
        iterator.ptr = it.ptr->next;
        iterator.idx = it.idx;
        return iterator;
    }
    //else it moves between indexes to do the same
    for(unsigned int i = it.idx + 1; i < it.t->arr_size; i++)
    {
        if(it.t->array[i] != NULL)
        {
            iterator.ptr = it.t->array[i];
            iterator.idx = i;
            return iterator;
        }
    }
    return htab_end(it.t);
}