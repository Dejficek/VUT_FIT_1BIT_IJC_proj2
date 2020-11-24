/*
 * David Rubý
 * fakulta informačních technologií Vysokého učení technického v Brně
 * příklad 1a
 *25. 04. 2019
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


/* ===== error codes =====
    1 - invalid arguments
    2 - file couldn't be opened
    3 - file couldn't be closed
*/

//function to print all lines but skipp first N...
void from_line(char input[260], int skipped_lines)
{
    int line = 0;
    
    char tmp[5000];

    bool warned = false;

    FILE *file;

    if((strcmp(input, "stdin")))
    {
        file = fopen(input, "r");
        if(file == NULL)
        {
            fprintf(stderr, "ERROR: the file couldn't be opened\n");
            exit(2);
        }
    }

    while(fgets(tmp, 5000, (!strcmp(input, "stdin")) ? stdin : file))
    {
        if(strlen(tmp) >= 1022)
        {
            tmp[1023] = '\0';
            if(!(warned))
            {
                fprintf(stderr, "WARNING: The maximum length of line was over exceeded.\n");
                warned = true;
            }
        }
        if(line + 1 >= skipped_lines)
        {
            printf("%s", tmp);
        }
        line++;
    }
    if(fclose(file) != 0)
    {
            fprintf(stderr, "ERROR: file couldn't be closed.\n");
            exit(3);
    }
}

int main (int argc, char *argv[])
{
    int number_of_lines = 10;

    char filename[260];

    bool warned = false;

    FILE *file;

    if(argc == 1)
    {
        ;
    }
    //if there is one argument (not counting te name of the program) and the argument is a name of a file, it make a variable file
    else if (argc == 2)
    {     
        //here, only the name of the file can be
        if(!strcmp(argv[1], "-n"))
        {
            fprintf(stderr, "ERROR: invalid positioning of arguments\n");
            return 1;
        }
        strcpy(filename, argv[1]);

            
    }
    //if there are two arguments (not includeing the name of the program, it will make a variable file and a variable storing the number of lines to be printed)
    else if (argc == 3)
    {
        if(strcmp(argv[1], "-n"))
        {
            fprintf(stderr, "ERROR: Invalid positioning of arguments\n");
            return 1;
        }

        //if there's a "+" in argument of "-n", all lines but first N lines will be printed
        if(argv[2][0] == 43)
        {
            from_line("stdin", atoi(argv[2]));
            return 0;
        }
        //error if argument for number of lines is not a number
        for(unsigned int i = 0; i < strlen(argv[2]); i++)
        {
            if((argv[2][i] < 48) || (argv[2][i] > 57))
            {
                //if the first character is a "-", then no error will be printed...
                if((i == 0) && (argv[2][i] == 45))
                {
                    ;
                }
                else{
                    fprintf(stderr, "ERROR: number of lines isn't a number\n");
                    return 1;
                }
                
            }
        }        
        number_of_lines = abs(atoi(argv[2]));
    }
    else if(argc == 4)
    {
        if(strcmp(argv[1], "-n")){
            fprintf(stderr, "ERROR: invalid positioning of arguments\n");
            return 1;
        }
        //if there's a "+" in argument of "-n", all lines but first N lines will be printed
        if(argv[2][0] == 43)
        {
            from_line(argv[3], atoi(argv[2]));
            return 0;
        }

        //error if argument for number of lines is not a number
        for(unsigned int i = 0; i < strlen(argv[2]); i++)
        {
            if((argv[2][i] < 48) || (argv[2][i] > 57))
            {
                if((i == 0) && (argv[2][i] == 45))
                {
                    ;
                }
                else
                {
                    fprintf(stderr, "ERROR: number of lines isn't a number\n");
                    return 1;
                }
            }
        }

        number_of_lines = abs(atoi(argv[2]));
        strcpy(filename, argv[3]);
    }
    //if there is a different number of arguments, the program will terminate and print an error messege to standart error output
    else
    {
        fprintf(stderr, "ERROR: Invalid number of arguments\n");
        return 1;
    }


    //an error will ocure, when the file can't be opened
    if((argc == 2) || (argc == 4))
    {
        file = fopen(filename, "r");
        if (file == NULL)
        {
            fprintf(stderr, "ERROR: the file couldn't be opened\n");
            return 2;
        }
    }

    char lines[number_of_lines][5000];
    char tmp[5000];

    //storing the lines from the file to 2D char array
    //reading line by line to temporary variable
    while(fgets(tmp, 5000, ((argc == 2) || (argc == 4)) ? file : stdin))
    {
        if(strlen(tmp) >= 1022)
        {
            tmp[1023] = '\0';
            if(!(warned))
            {
                fprintf(stderr, "WARNING: The maximum length of line was over exceeded.\n");
                warned = true;
            }
        }

        //moving lines in array up, so i dont have to use two loops... one for counting the lines and other for printing the last n lines
        for(int j = 0; j < (number_of_lines - 1); j++)
        {
            strcpy(lines[j], lines[j + 1]);
        }
        strcpy(lines[number_of_lines - 1], tmp);
    }

    //closing the file up
    if((argc == 2) || (argc == 4))
    {
        if(fclose(file) != 0)
        {
            fprintf(stderr, "ERROR: file couldn't be closed.\n");
            return 3;
        }    
    }

    //printing out the content of the array
    for(int loop = 0; loop < number_of_lines; loop++)
    {
        printf("%s", lines[loop]);
    }
    return 0;
}
