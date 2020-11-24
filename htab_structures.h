/*
 * David Rubý
 * fakulta informačních technologií Vysokého učení technického v Brně
 * příklad 2
 *25. 04. 2019
 */


#include"htab.h"

#ifndef __HTAB_STURCTURES_H__
#define __HTAB_STRUCTURES_H__

//definice datových typů
struct htab_item
{
    char *key;
    int value;
    struct htab_item *next;
};

struct htab
{
    size_t size;
    size_t arr_size;
    struct htab_item *array[];
};

#endif // __HTAB_STRUCTURES_H__