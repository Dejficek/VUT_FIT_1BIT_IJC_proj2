/*
 * David Rubý
 * fakulta informačních technologií Vysokého učení technického v Brně
 * příklad 2
 *25. 04. 2019
 */


#include"htab_structures.h"

//if the iterator is NULL, it will return NULL. Else it will return the key of iterator.
const char * htab_iterator_get_key(htab_iterator_t it)
{
    if(it.ptr != NULL)
    {
        return it.ptr->key;
    }
    return NULL;
}

//if the iterator is NULL, it will return NULL. Else it will return the value of iterator.
int htab_iterator_get_value(htab_iterator_t it)
{
    if(it.ptr != NULL)
    {
        return it.ptr->value;
    }
    return -1;
}

//If the iterator is NULL, it will return -1. Else it will update the value and return this value
int htab_iterator_set_value(htab_iterator_t it, int val)
{
    if(it.ptr != NULL)
    {
        it.ptr->value = val;
        return val;
    }
    return -1;
}

//This will return size of the table
size_t htab_size(const htab_t * t)
{
    return t->size;
}

//This will return arr_size of the table
size_t htab_bucket_count(const htab_t * t)
{
    return t->arr_size;
}