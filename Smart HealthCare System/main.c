#include<stdio.h>
#include<conio.h>
#include "shs.h"
int main()
{
    int number, number2,r,q;
    char back_button[30];
    //------for welcome screen------------
    welcome();

    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(r=1; r <= 20 ; r++)
    {
        for(q=0; q<=100000000 ; q++);
        printf("%c",177);
    }
    //-----------------------end of loading animation-----------------------------------------

    system("cls"); //for clear the screen

    printf("\n\n\t\t=========================\n\t\t=\t\t\t=\n\t\t=\tMenu\t\t= \t\t\n\t\t=\t\t\t=\n\t\t=========================\n\n\n");
    printf("\t\t1. User \n");
    printf("\t\t2. Admin \n\n");
    printf("\n\t\tSelect a Number: ");
    scanf("%d",&number);
    if(number == 1 )
    {
        users();
    }
    else if(number ==  2)
    {
        admin();
    }
    else
    {
        system("cls");
        gets(back_button);
        main();
    }

}
