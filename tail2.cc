/*
 * David Rubý
 * fakulta informačních technologií Vysokého učení technického v Brně
 * příklad 1b
 *25. 04. 2019
 */


#include<iostream>
#include<fstream>
#include<istream>
#include<sstream>
#include<string>
using namespace std;

/* ===== error codes =====
    1 - invalid arguments
    2 - file couldn't be opened
    3 - file couldn't be closed
*/

void from_line(string input, int skipped_lines)
{
    int line = 0;

    string tmp;

    ifstream input_file;

    //opening the file and checking, if it's opened
    if(input != "stdin")
    {
        input_file.open(input);
        if(!input_file.is_open())
        {
            cerr << "ERROR: the file couldn't be opened" << endl;
            exit(2);
        }
    }

    //printing the lines
    while(getline((input == "stdin") ? std::cin : input_file, tmp))
    {
        if(line + 1 >= skipped_lines)
        {
            cout << tmp << endl;
        }
        line++;
    }

    //closing up the file
    if(input == "stdin")
    {
        input_file.close();
        if(input_file.is_open())
        {
            cerr << "ERROR: the file couldn't be closed" << endl;
            exit(3);
        }
    }
}

int main(int argc, char *argv[]){

    int number_of_lines = 10;

    string filename;


    ifstream input_file;


    string n ("-n");

    if(argc == 1);

    //if there is one argument (not counting te name of the program) and the argument is a name of a file, it make a variable file
    else if(argc == 2)
    {
        if(argv[1] == n)
        {
            cerr << "ERROR: invalid positioning of arguments" << endl;
            return 1;
        }
        filename = argv[1];
    }
    //if there are two arguments (not including the name of the program, it will make a variable file and a variable storing the number of lines to be printed)
    else if (argc == 3)
    {
        if(argv[1] != n)
        {
            cerr << "ERROR: Invalid positioning of arguments" << endl;
            return 1;
        }

        //if there's a "+" in arguments of "-n", all lines but first N lines will be printed
        if(argv[2][0] == '+')
        {
            from_line("stdin", stoi(argv[2]));
            return 0;
        }

        string argv2(argv[2]);
        //error if argument for number of lines is not a number
        for (unsigned int i = 0; i < argv2.length(); i++)
        {
            if((argv[2][i] < 48) || (argv[2][i] > 57))
            {
                //cout << "neni cislo..." << endl;
                //if the first character is a "-", then no error will be printed...
                if((i == 0) && (argv[2][i] == '-'))
                {
                    ;
                }
                else
                {
                    cerr << "ERROR: number of lines isn't a number" << endl;
                    return 1;
                }
            }
        }
        number_of_lines = abs(stoi(argv[2]));
    }
    else if(argc == 4)
    {
        if(argv[1] != n)
        {
            cerr << "ERROR: invalid positioning of arguments" << endl;
            return 1;
        }
        //if there's a "+" in argument of "-n", all lines but first N lines will be printed
        if(argv[2][0] == '+')
        {
            from_line(argv[3], stoi(argv[2]));
            return 0;
        }

        string argv2(argv[2]);
        //error if argument for number of lines is not a number
        for(unsigned int i = 0; i < argv2.length(); i++)
        {
            if((argv[2][i] < 48) || (argv[2][i] > 57))
            {
                if((i == 0) && (argv[2][i] == '-'))
                {
                    ;
                }
                else
                {
                    cerr << "ERROR: number of lines isn't a number" << endl;
                    return 1;
                }
            } 
        }
        number_of_lines = abs(stoi(argv[2]));
        filename = argv[3];
    }

    //if there is a different number of arguments, the program will terminate and print an error message to standart error output
    else
    {
        cerr << "ERROR: invalid number of arguments" << endl;
        return 1;
    }


    //an error will occure, when the file can't be opened
    if((argc == 2) || (argc == 4))
    {
        input_file.open(filename);
        if(!input_file.is_open())
        {
            cerr << "ERROR: the file couldn't be opened" << endl;
            return 2;
        }
    }

    string lines[number_of_lines];
    string tmp;

    //storing the lines from the file to array of strings
    //reading line by line to temporary variable
    while(getline(((argc == 2) || (argc == 4)) ? input_file : std::cin, tmp))
    {
        //moving lines in array up, so I don't have to use two loops... one for counting the lines and other for printing the last n lines
        for(int j = 0; j < (number_of_lines - 1); j++)
        {
            lines[j] = lines[j + 1];
        }
        lines[number_of_lines - 1] = tmp;
    }

    //closing the file up
    if((argc == 2) || (argc == 4))
    {
        input_file.close();
        if(input_file.is_open())
        {
            cerr << "ERROR: the file couldn't be closed" << endl;
            return 3;
        }
    }

    //printing out the content of the array
    for(int loop = 0; loop < number_of_lines; loop++)
    {
        cout << lines[loop] << endl;
    }
    
    return 0;
}
