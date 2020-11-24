/*
 * David Rubý
 * fakulta informačních technologií Vysokého učení technického v Brně
 * příklad 2
 *25. 04. 2019
 */


#include"htab_structures.h"


//konstruktor
htab_t *htab_init(size_t n)
{
    //allocs memory for the table
    if(n > 0)
    {
        //memory allocation
        htab_t *tab = (htab_t*)malloc(sizeof(htab_t) + sizeof(struct htab_item) * n);
        if(tab == NULL)
        {
            return NULL;
        }

        //data initialization
        tab->size = 0;
        tab->arr_size = n;

        //blanking pointers
        for (unsigned int i = 0; i < n; i++){
            tab->array[i] = NULL;
        }
        return tab;
    }
    return NULL;
}

//creates new table and moves all data from old table to new table
htab_t *htab_move(size_t n, htab_t *from)
{
    htab_t *new_tab = htab_init(n);
    struct htab_iterator iterator = htab_begin(from);
    struct htab_iterator iterator_end = htab_end(from);
    struct htab_iterator new_iterator;

    //moves between iterators and adds key of the iterator to new table
    while(!htab_iterator_equal(iterator, iterator_end))
    {
        new_iterator = htab_lookup_add(new_tab, htab_iterator_get_key(iterator));
        htab_iterator_set_value(new_iterator, htab_iterator_get_value(new_iterator) + 1);
        iterator = htab_iterator_next(iterator);
    }
    new_iterator = htab_lookup_add(new_tab, htab_iterator_get_key(iterator));
    htab_iterator_set_value(new_iterator, htab_iterator_get_value(new_iterator) + 1);
    new_tab->arr_size = n;

    htab_clear(from);
    return new_tab;
}


//looks for appearance of key in table or adds new record
htab_iterator_t htab_lookup_add(htab_t * t, const char *key)
{
    //setting new empty (NULL) iterator
    htab_iterator_t iterator;
    iterator.idx = 0;
    iterator.ptr = NULL;
    iterator.t = NULL;

    //generates index
    int i = htab_hash_function(key) % t->arr_size;
    struct htab_item *tmp = t->array[i];

    //if there is at least one record on current index
    if(t->array[i] != NULL)
    {
        //continues to loop, if there is more, than one record
        while(tmp->next != NULL)
        {
            //moves between items and if a key of the item matches the key, it will return iterator of the item
            if(strcmp(tmp->key, key) == 0){
                iterator.t = t;
                iterator.idx = i;
                iterator.ptr = tmp;

                return iterator;
            }
            tmp = tmp->next;
        }
        //if there is only one record on current index and the key matches this record, it will return iterator of the item
        if(strcmp(tmp->key, key) == 0) {
            iterator.t = t;
            iterator.idx = i;
            iterator.ptr = tmp;

            return iterator;
        }
        //if it gets here, it means, match was not found and function continues to add a new record
        //so it allocs memory of next item
        tmp->next = (struct htab_item*)malloc(sizeof(struct htab_item));
        tmp = tmp->next;
        if(tmp == NULL)
        {
            return iterator;
        }

        //then it allocs memory for the key
        tmp->key = malloc(strlen(key) + 1);
        if(tmp->key == NULL)
        {
            return iterator;
        }

        //then it sets up the data of the item
        strncpy(tmp->key, key, strlen(key) + 1);
        //printf("%s\n", tmp->key);
        tmp->value = 0;
        tmp->next = NULL;
        t->size++;

        //then it set up the data of the iterator
        iterator.t = t;
        iterator.ptr = tmp;
        iterator.idx = i;
        return iterator;
    }

    //this code will be executed, if there are no records on the current index
    //allocs memory for the item
    t->array[i] = (struct htab_item*)malloc(sizeof(struct htab_item));
    if(t->array[i] == NULL)
    {
        return iterator;
    }

    //allocs memory for the key
    t->array[i]->key = malloc(strlen(key) + 1);
    if(t->array[i]->key == NULL)
    {
        return iterator;
    }

    //setting up the data of the item
    strncpy(t->array[i]->key, key, strlen(key) + 1);
    t->array[i]->value = 0;
    t->size++;              //increments size, because there is one more item in the table
    t->array[i]->next = NULL;

    //setting up the data of the iterator
    iterator.t = t;
    iterator.ptr = t->array[i];
    iterator.idx = i;
    return iterator;
}

//clears the data of the table
void htab_clear(htab_t *t)
{
    struct htab_item *tmp;
    struct htab_item *tmp2;
    t->size = 0;        //sets the size to zero
    int size = t->arr_size;

    //moves through every index
    for (int i = 0; i < size; i++)
    {
        if(t->array[i] != NULL)
        {
            //frees the memory of the key and sets the pointer to NULL and value to 0
            free(t->array[i]->key);
            t->array[i]->key = NULL;
            t->array[i]->value = 0;
            if(t->array[i]->next != NULL)
            {
                //if there are more records on the index
                tmp = t->array[i]->next;
                t->array[i]->next = NULL;
                do
                {
                    //it frees key of every record and frees the memory of the item
                    tmp2 = tmp->next;
                    free(tmp->key);
                    free(tmp);
                    tmp = tmp2;
                }while(tmp != NULL);
            }
            //then it frees the memory of every first record on the index
            free(t->array[i]);
        }
    }
}

//clears data of table and then frees the memory
void htab_free(htab_t * t)
{
    htab_clear(t);
    free(t);
}
