#include <stdio.h>
#include <string.h>

int main(void)
{
    char buff[15];
    int pass = 0;

    printf("\n Enter the password : \n");
    //gets(buff);
    fgets(buff, sizeof(buff), stdin);
    strtok(buff, "\n");
    if (strcmp(buff, "thegeekstuff"))
    {
        printf("\n Wrong Password. \n");
    }
    else
    {
        printf("\n Correct Password.\n");
        pass = 1;
    }

    if (pass)
    { // do somelhing priviledged stuff
        printf("\n Root privileges given to the user.\n");
    }
    return 0;
}