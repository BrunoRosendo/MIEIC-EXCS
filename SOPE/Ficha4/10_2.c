#include <stdio.h>
#include <string.h>

void func(char buff[]) {
    gets(buff);
}

int main(void)
{
    char buff[15];
    int pass = 0;

    printf("\n Enter the password : \n");
    func(buff);
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