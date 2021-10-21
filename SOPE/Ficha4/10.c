#include <stdio.h>
#include <string.h>

int func() {
    char buff[15];
    gets(buff);
    if (strcmp(buff, "thegeekstuff"))
    {
        printf("\n Wrong Password. \n");
        return 0;
    }
    else
    {
        printf("\n Correct Password.\n");
        return 1;
    }
}

int main(void)
{
    int pass = 0;

    printf("\n Enter the password : \n");
    
    if (func()) pass = 1;

    if (pass)
    { // do somelhing priviledged stuff
        printf("\n Root privileges given to the user.\n");
    }
    return 0;
}