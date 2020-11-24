/*
 * David Rubý
 * fakulta informačních technologií Vysokého učení technického v Brně
 * příklad 2
 *25. 04. 2019
 */

#include<stdlib.h>
#include<string.h>
#include"io.h"
#include"htab.h"

int main()
{
    char word[1024];
    htab_t *table = htab_init(10);

    //reads file word by word
    while(get_word(word, 1024, stdin) != EOF)
    {
        //adds every word to the table if not found, else will increment value of the word
        htab_iterator_t iter = htab_lookup_add(table, word);
        htab_iterator_set_value(iter, htab_iterator_get_value(iter) + 1);
    }


    htab_iterator_t iterator = htab_begin(table);
    htab_iterator_t iterator_end = htab_end(table);

    //prints out every record
    while(!htab_iterator_equal(iterator, iterator_end))
    {
        printf("%s\t%d\n", htab_iterator_get_key(iterator), htab_iterator_get_value(iterator));
        iterator = htab_iterator_next(iterator);
    }
    printf("%s\t%d\n", htab_iterator_get_key(iterator_end), htab_iterator_get_value(iterator_end));

    //clears the table and frees the memory of table
    htab_free(table);

    return 0;
}