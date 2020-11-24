/*
 * David Rubý
 * fakulta informačních technologií Vysokého učení technického v Brně
 * příklad 2
 *25. 04. 2019
 */

#include"io.h"

int get_word(char *str, int max, FILE *file) {
    int return_value;

    //reading one word
    return_value = fscanf(file, "%s", str);

    //if the word is too long, the length will be edited
    if(strlen(str) >= (unsigned)max)
    {
        str[max] = '\n';
    }

    //if the algorithm reaches end of file, function will return EOF
    if(return_value == EOF)
    {
        return EOF;
    }
    //else it return length of the word
    return strlen(str);
}