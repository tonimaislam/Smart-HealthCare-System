#include<windows.h>
#include<process.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#define ENTER 13 // macro definition;
#define TAB 9
#define BKSP 8
#define SPACE 32
//------------------------FIle pointer declare ---------------------------------------------------------------------------
FILE *reg_info;
FILE *admin_file, *payment,*pattern_matching;
//---------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------Global variable -------------------------------------------------------------------------
char admin_user_name[30], admin_password[30],admin_email[30],admin_gender[10],admin_ph[15],update_user_profile[120],back_button[30];;
int age, systolic, diastolic, heart_rate,admin_age, driver_age;
float height, weight, body_temperature, blood_sugar,bmi_value ;
char hoospital_name[30],hospital_location[30],number_of_doctors[150],Provide_Service_List[300],hospital_ph[20],folder_name_bmi[30];
char  user_name[20],gender[10], regu_disease[500], password[20], ph_number[15], Being_a_smoker[100],location[100],file_name[20], other_problem[500];
char ambulance_name[50],licence_number[50],driver_name[20],ambulance_ph[15],driviing_licence_number[50],temp[50],temp_for_read[120];
//---------------------------for welcome screen----------------------------------
void welcome()
{
    printf("\n\n\t\t___________________________________________________\n\n\n");
    printf("\t\t\tWelcome to Smart Healthcare System\n\n");
    printf("\t\t___________________________________________________\n\t\t\t");
}
//------------------------------------------------------end of welcome screen---------------------------------------
void SetColor(int ForgC) // text color function
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
//------------------------------------for loading animation-----------------------------
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X= x;
    coord.Y =y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
//--------------------------------------------end of loading animation--------------------------------------------


//-------------------------------------------------date adding------------------------------------------------------------------
int isLeap(int y)
{
    if (y%100 != 0 && y%4 == 0 || y %400 == 0)
        return 1;

    return 0;
}
int offsetDays(int d, int m, int y)
{
    int offset = d;

    switch (m - 1)
    {
    case 11:
        offset += 30;
    case 10:
        offset += 31;
    case 9:
        offset += 30;
    case 8:
        offset += 31;
    case 7:
        offset += 31;
    case 6:
        offset += 30;
    case 5:
        offset += 31;
    case 4:
        offset += 30;
    case 3:
        offset += 31;
    case 2:
        offset += 28;
    case 1:
        offset += 31;
    }

    if (isLeap(y) && m > 2)
        offset += 1;

    return offset;
}
void revoffsetDays(int offset, int y, int *d, int *m)
{
    int month[13] = { 0, 31, 28, 31, 30, 31, 30,
                      31, 31, 30, 31, 30, 31
                    };

    if (isLeap(y))
        month[2] = 29;

    int i;
    for (i = 1; i <= 12; i++)
    {
        if (offset <= month[i])
            break;
        offset = offset - month[i];
    }

    *d = offset;
    *m = i;
}
int addDays(int d1, int m1, int y1, int x)
{
    int offset1 = offsetDays(d1, m1, y1);
    int remDays = isLeap(y1)?(366-offset1):(365-offset1);
    int y2, offset2;
    if (x <= remDays)
    {
        y2 = y1;
        offset2 = offset1 + x;
    }

    else
    {
        x -= remDays;
        y2 = y1 + 1;
        int y2days = isLeap(y2)?366:365;
        while (x >= y2days)
        {
            x -= y2days;
            y2++;
            y2days = isLeap(y2)?366:365;
        }
        offset2 = x;
    }
    int m2, d2;
    revoffsetDays(offset2, y2, &d2, &m2);
    fprintf(admin_file,"%d-%d-%d\n",d2,m2,y2);
    fprintf(admin_file,"------------------------------------------------------------------\n");
    fprintf(reg_info,"%d\n%d\n%d\n",d2,m2,y2);
}
struct date
{
    int dd, mm, yy;
};
int date_cmp(struct date d1, struct date d2)
{
    if (d1.dd == d2.dd && d1.mm == d2.mm && d1.yy ==d2.yy)
        return 0;
    else if (d1.yy > d2.yy || d1.yy == d2.yy && d1.mm > d2.mm ||
             d1.yy == d2.yy && d1.mm == d2.mm && d1.dd > d2.dd)
        return 1;
    else return -1;
}
//-------------------------------------date adding-------------------------------------------------------------------------


//-----------------------------------------Sign Up function start----------------------------------------------------
void sign_up(char planame[],int days)
{
    //--------------get current time-----------------------------------
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    //---------------------------------------------------------------------------
    char folder[]="Users List/a_";
    printf("\t\t\tUser name = ");
    gets(user_name);
    strcpy(temp,user_name);
    strcat(user_name,".txt");
    strcat(folder,user_name);
    reg_info = fopen(folder,"w");
    admin_file = fopen("users_list.txt","a");
    pattern_matching = fopen("username_pattern_matching.txt","a");
    if(reg_info == NULL)
    {
        printf("File does not exist !!\n");
    }
    else
    {

        printf("\t\t\tPassword = ");
        gets(password);

        printf("\t\t\tEnter your age:");
        scanf("%d",&age);

        printf("\t\t\tGender(male/female) = ");
        scanf("%s",&gender);

        printf("\t\t\tHeight(cm) = ");
        scanf("%f",&height);

        printf("\t\t\tWeight(kg) = ");
        scanf("%f",&weight);

        printf("\t\t\tRegular disease Name & Details = ");
        getchar();
        gets(regu_disease);

        printf("\t\t\tBeing a smoker, Alcoholic , Drug Addicted(yes,yes,yes) : ");
        gets(Being_a_smoker);

        printf("\t\t\tContact Number = ");
        getchar();
        scanf("%s",&ph_number);
        printf("\t\t\t---------------------------------------------\n");
        payment = fopen("payment.txt","a");
        fprintf(payment,"Username = %s\n",temp);
        fprintf(payment,"------------------------------------------------------------\n");
        fclose(payment);
        fprintf(reg_info,"%s\n",temp);
        fprintf(pattern_matching,"%s  ",temp);
        fprintf(admin_file,"%s\t\t",temp);
        fprintf(reg_info,"%s\n",password);
        fprintf(admin_file,"%s\t\t%s   %d-%02d-%02d\t",password,planame,tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        fprintf(reg_info,"%d\n%s\n%0.2f \n%0.2f\n",age,gender,height,weight);
        fprintf(reg_info, "%s\n",regu_disease);
        fprintf(reg_info,"%s\n",Being_a_smoker);
        fprintf(reg_info,"%s\n",ph_number);
    }
    printf("\t\t\tRegistration Successfully !\n");

    addDays( tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900, days);
    fclose(admin_file);
    fclose(reg_info);
    fclose(pattern_matching);
    system("cls");
    int number2,r,q,j,i;
    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=30000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    //-----------------------end of loading animation-----------------------------------------
    printf("\n\n\t\t\t=================================\n\t\t\t=\t\t\t\t=\n\t\t\t=\tLogin to User Panel\t= \t\t\n\t\t\t=\t\t\t\t=\n\t\t\t=================================\n\n\n");
    log_in();
}
void user_basic_sign_up(char planame[],int days)
{

    //--------------get current time-----------------------------------
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    //---------------------------------------------------------------------------
    char folder[]="Users List/a_";
    printf("\t\t\tUser name = ");
    getchar();
    gets(user_name);
    strcpy(temp,user_name);
    strcat(user_name,".txt");
    strcat(folder,user_name);
    reg_info = fopen(folder,"w");
    admin_file = fopen("users_list.txt","a");
    pattern_matching = fopen("username_pattern_matching.txt","a");
    if(reg_info == NULL)
    {
        printf("File does not exist !!\n");
    }
    else
    {

        printf("\t\t\tPassword = ");
        gets(password);

        printf("\t\t\tEnter your age:");
        scanf("%d",&age);

        printf("\t\t\tGender(male/female) = ");
        scanf("%s",&gender);

        printf("\t\t\tHeight(cm) = ");
        scanf("%f",&height);

        printf("\t\t\tWeight(kg) = ");
        scanf("%f",&weight);

        printf("\t\t\tRegular disease Name & Details = ");
        getchar();
        gets(regu_disease);

        printf("\t\t\tBeing a smoker, Alcoholic , Drug Addicted(yes,yes,yes) : ");
        gets(Being_a_smoker);

        printf("\t\t\tContact Number = ");
        getchar();
        scanf("%s",&ph_number);
        printf("\t\t\t---------------------------------------------\n");
        payment = fopen("payment.txt","a");
        fprintf(payment,"Username = %s  =>  ",temp);
        fprintf(payment,"Plan name = %s\n",planame);
        fprintf(payment,"------------------------------------------------------------\n");
        fclose(payment);
        fprintf(reg_info,"%s\n",temp);
        fprintf(pattern_matching,"%s  ",temp);
        fprintf(admin_file,"%s\t\t",temp);
        fprintf(reg_info,"%s\n",password);
        fprintf(admin_file,"%s\t\t%s   %d-%02d-%02d\t",password,planame,tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        fprintf(reg_info,"%d\n%s\n%0.2f \n%0.2f\n",age,gender,height,weight);
        fprintf(reg_info, "%s\n",regu_disease);
        fprintf(reg_info,"%s\n",Being_a_smoker);
        fprintf(reg_info,"%s\n",ph_number);
    }
    printf("\t\t\tRegistration Successfully !\n");

    addDays( tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900, days);
    fclose(admin_file);
    fclose(reg_info);
    fclose(pattern_matching);
    system("cls");
    int number2,r,q,j,i;
    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=30000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    //-----------------------end of loading animation-----------------------------------------
    printf("\n\n\t\t\t=================================\n\t\t\t=\t\t\t\t=\n\t\t\t=\tLogin to User Panel\t= \t\t\n\t\t\t=\t\t\t\t=\n\t\t\t=================================\n\n\n");
    log_in();
}
//------------------------------------------End of Sign up function-----------------------------------------------
void admin_add_user(char planame[],int days)
{
    //--------------get current time-----------------------------------
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    //---------------------------------------------------------------------------
    char folder[]="Users List/a_";
    printf("\t\t\tUser name = ");
    getchar();
    gets(user_name);
    strcpy(temp,user_name);
    strcat(user_name,".txt");
    strcat(folder,user_name);
    reg_info = fopen(folder,"w");
    admin_file = fopen("users_list.txt","a");
    pattern_matching = fopen("username_pattern_matching.txt","a");
    if(reg_info == NULL)
    {
        printf("File does not exist !!\n");
    }
    else
    {

        printf("\t\t\tPassword = ");
        gets(password);

        printf("\t\t\tEnter your age:");
        scanf("%d",&age);

        printf("\t\t\tGender(male/female) = ");
        scanf("%s",&gender);

        printf("\t\t\tHeight(cm) = ");
        scanf("%f",&height);

        printf("\t\t\tWeight(kg) = ");
        scanf("%f",&weight);

        printf("\t\t\tRegular disease Name & Details = ");
        getchar();
        gets(regu_disease);

        printf("\t\t\tBeing a smoker, Alcoholic , Drug Addicted(yes,yes,yes) : ");
        gets(Being_a_smoker);

        printf("\t\t\tContact Number = ");
        getchar();
        scanf("%s",&ph_number);
        printf("\t\t\t---------------------------------------------\n");
        payment = fopen("payment.txt","a");
        fprintf(payment,"Username = %s  =>  ",temp);
        fprintf(payment,"Plan name = %s  => Added by Admin\n",planame);
        fprintf(payment,"------------------------------------------------------------\n");
        fclose(payment);
        fprintf(reg_info,"%s\n",temp);
        fprintf(pattern_matching,"%s  ",temp);
        fprintf(admin_file,"%s\t\t",temp);
        fprintf(reg_info,"%s\n",password);
        fprintf(admin_file,"%s\t\t%s   %d-%02d-%02d\t",password,planame,tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        fprintf(reg_info,"%d\n%s\n%0.2f \n%0.2f\n",age,gender,height,weight);
        fprintf(reg_info, "%s\n",regu_disease);
        fprintf(reg_info,"%s\n",Being_a_smoker);
        fprintf(reg_info,"%s\n",ph_number);
    }
    printf("\t\t\tRegistration Successfully !\n");

    addDays( tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900, days);
    fclose(admin_file);
    fclose(reg_info);
    fclose(pattern_matching);
    system("cls");
    int number2,r,q,j,i;
    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=30000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    //-----------------------end of loading animation-----------------------------------------
    printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
    admin_login_part2();
}
void admin_basic_add_user(char planame[],int days)
{
    //--------------get current time-----------------------------------
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    //---------------------------------------------------------------------------
    char folder[]="Users List/a_";
    printf("\t\t\tUser name = ");
    getchar();
    gets(user_name);
    strcpy(temp,user_name);
    strcat(user_name,".txt");
    strcat(folder,user_name);
    reg_info = fopen(folder,"w");
    admin_file = fopen("users_list.txt","a");
    pattern_matching = fopen("username_pattern_matching.txt","a");
    if(reg_info == NULL)
    {
        printf("File does not exist !!\n");
    }
    else
    {

        printf("\t\t\tPassword = ");
        gets(password);

        printf("\t\t\tEnter your age:");
        scanf("%d",&age);

        printf("\t\t\tGender(male/female) = ");
        scanf("%s",&gender);

        printf("\t\t\tHeight(cm) = ");
        scanf("%f",&height);

        printf("\t\t\tWeight(kg) = ");
        scanf("%f",&weight);

        printf("\t\t\tRegular disease Name & Details = ");
        getchar();
        gets(regu_disease);

        printf("\t\t\tBeing a smoker, Alcoholic , Drug Addicted(yes,yes,yes) : ");
        gets(Being_a_smoker);

        printf("\t\t\tContact Number = ");
        getchar();
        scanf("%s",&ph_number);
        printf("\t\t\t---------------------------------------------\n");
        payment = fopen("payment.txt","a");
        fprintf(payment,"Username = %s  =>  ",temp);
        fprintf(payment,"Plan name = %s => Added by Admin\n",planame);
        fprintf(payment,"------------------------------------------------------------\n");
        fclose(payment);
        fprintf(reg_info,"%s\n",temp);
        fprintf(pattern_matching,"%s  ",temp);
        fprintf(admin_file,"%s\t\t",temp);
        fprintf(reg_info,"%s\n",password);
        fprintf(admin_file,"%s\t\t%s   %d-%02d-%02d\t",password,planame,tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        fprintf(reg_info,"%d\n%s\n%0.2f \n%0.2f\n",age,gender,height,weight);
        fprintf(reg_info, "%s\n",regu_disease);
        fprintf(reg_info,"%s\n",Being_a_smoker);
        fprintf(reg_info,"%s\n",ph_number);
    }
    printf("\t\t\tRegistration Successfully !\n");

    addDays( tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900, days);
    fclose(admin_file);
    fclose(reg_info);
    fclose(pattern_matching);
    system("cls");
    int number2,r,q,j,i;
    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=30000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    //-----------------------end of loading animation-----------------------------------------
    printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
    admin_login_part2();
}
//--------------------------------------------location tracking function start---------------------------------------------
void location_tracking()
{
    printf("\n\t\t\tEnter your Current Location:");
    gets(location);
}
//---------------------------------------------end of location tracking function---------------------------------


//----------------------------ambulance function start------------------------------------------------------------------
void ambulance(char loc[], char name[],char mess[])
{
    reg_info = fopen("Ambulance_message.txt","a");
    if(reg_info == NULL)
    {
        printf("File does not exist !!\n");
    }
    else
    {
        fprintf(reg_info,"%s ",name);
        fprintf(reg_info,"%s ",mess);
        fprintf(reg_info,"in %s\n",loc);

    }
    fclose(reg_info);
}
//-----------------------------------end of ambulance function-------------------------------------------


//-----------------------------------hospital function start--------------------------------------------------------------
void hospital(char name[],char mess[])
{
    reg_info = fopen("Hospital_message.txt","a");
    if(reg_info == NULL)
    {
        printf("File does not exist !!\n");
    }
    else
    {
        fprintf(reg_info,"%s ",name);
        fprintf(reg_info,"%s, please get ready\n",mess);

    }
    fclose(reg_info);
}
//-------------------------end of hospital function ------------------------------------------------------------------------


//-----------------------------------------Hospital others problem start-------------------------------------------------------
void hospital_others_problem(char name[],char mess[])
{
    reg_info = fopen("Hospital_message.txt","a");
    if(reg_info == NULL)
    {
        printf("File does not exist !!\n");
    }
    else
    {
        fprintf(reg_info,"%s need some advice for this problem: ",name);
        fprintf(reg_info,"%s\n",mess);

    }
    fclose(reg_info);
}
//----------------------------------end of hospital others problem function-----------------------------------------------------------------------


//-------------------------------------------emergency function start -----------------------------------------------------------------------------
void emergency()
{
    int emergency_number ;
    printf("\t\t\t\t1.Heart attack\n");
    printf("\t\t\t\t2.Brain stroke\n");
    printf("\t\t\t\t3.Breathing Problem\n");
    printf("\t\t\t\t4.Fractureor sprain\n");
    printf("\t\t\t\t5.Extreme stomach pain\n");
    printf("\t\t\t\t----------------------------------------\n");
    printf("\t\t\t\twhen you select any option from the list, \n\t\t\t\twe send it nearby  hospital and ambulance service !!\n");
    printf("\t\t\t\t----------------------------------------\n\t\t\t\t");
    scanf("%d",&emergency_number);
    printf("\t\t\t\t----------------------------------------\n");
    if(emergency_number == 1)
    {
        char Heart_attack[50] ="got Heart Attack";
        ambulance(location, user_name, Heart_attack);
        hospital(user_name,Heart_attack);
        printf("\t\t\t\tFor User Menu press Enter!\n\t\t\t\t");
        gets(back_button);
        getchar();
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }
    else if(emergency_number == 2)
    {
        char Brain_stroke[50]="got Brain stoke";
        ambulance(location, user_name,Brain_stroke);
        hospital(user_name,Brain_stroke);
        printf("\t\t\t\tFor User Menu press Enter!\n\t\t\t\t");
        gets(back_button);
        getchar();
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }
    else if(emergency_number == 3)
    {
        char Breathing_Problem[50] ="got Breathing Problem";
        ambulance(location, user_name,Breathing_Problem);
        hospital(user_name,Breathing_Problem);
        printf("\t\t\t\tFor User Menu press Enter!\n\t\t\t\t");
        gets(back_button);
        getchar();
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }
    else if(emergency_number == 4)
    {
        char   Fractureor_sprain[50]="got Fracture Sprain";
        ambulance(location, user_name,Fractureor_sprain);
        hospital(user_name,Fractureor_sprain);
        printf("\t\t\t\tFor User Menu press Enter!\n\t\t\t\t");
        gets(back_button);
        getchar();
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }
    else if(emergency_number == 5)
    {
        char Extreme_stomach_pain[50]="got Extreme stomach pain";
        ambulance(location, user_name,Extreme_stomach_pain);
        hospital(user_name,Extreme_stomach_pain);
        printf("\t\t\t\tFor User Menu press Enter!\n\t\t\t\t");
        gets(back_button);
        getchar();
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }
    else
    {
        printf("\t\t\t\tFor User Menu press Enter!\n\t\t\t\t");
        gets(back_button);
        getchar();
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }
}
//--------------------------------------------------end of emergency function-------------------------------------------------------------

void nurse_message_sender()
{
    reg_info = fopen("Nurse_message.txt","a");
    if(reg_info == NULL)
    {
        printf("file dose not exits !!");
    }
    else
    {
        fprintf(reg_info,"%s calling a Nurse for checking his/her physical condition in %s\n",user_name,location);
        fclose(reg_info);
    }

}

//-------------------------------------Information_Collecting function start-----------------------------------------------------------------
void Information_Collecting()
{

    char nurse_username[30], nurse_password[30];
    int call_a_nurse;
    printf("\t\t\t\tCall a Nurse ?\n");
    printf("\t\t\t\t1. Yes\t 2.NO\n\t\t\t\t");
    printf("----------------------------------\n\t\t\t\t");
    scanf("%d",&call_a_nurse);
    printf("\t\t\t\t------------------------------------------------------\n");
    if(call_a_nurse == 1)
    {
        nurse_message_sender();
        char folder[]="Nurse/";
        printf("\t\t\t\tNurse will come to your house as soon as possible.\n\t\t\t\tPlease wait for few minutes. When the nurse arrives she will\n\t\t\t\tuse her username and Password to send the necessary information to the server.\n");
        printf("\t\t\t\t------------------------------------------------------\n");
        printf("\t\t\t\tUsername: ");
        getchar();
        gets(nurse_username);
        strcat(folder,nurse_username);
        strcat(folder,".txt");
        reg_info = fopen(folder,"r");
        if(reg_info == NULL)
        {
            printf("\t\t\t\tUsername incorrect !\n\n");
            printf("\t\t\t\tFor User Menu press Enter!\n\t\t\t\t");
            gets(back_button);
            system("cls");
            //--------------for loading animation---------------
            int j,i;
            //--------------for loading animation---------------
            gotoxy(46,10);
            printf("Loading...");
            gotoxy(46,12);
            for(i=1; i <= 20 ; i++)
            {
                for(j=0; j<=30000000 ; j++);
                printf("%c",177);
            }
            system("cls");
            printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
            log_in_part2();
        }
        else
        {
            char nurse_f_username[30], nurse_f_pass[30];
            fscanf(reg_info,"%[^\n]%*c %[^\n]%*c",&nurse_f_username,&nurse_f_pass);
            printf("\t\t\t\tPassword: ");
            gets(nurse_password);
            printf("\t\t\t\t------------------------------------------------------\n\n");
            if(strcmp(nurse_username,nurse_f_username) == 0 && strcmp(nurse_password, nurse_f_pass) == 0 )
            {
                printf("\t\t\t\tSystolic pressure(upper):");
                scanf("%d",&systolic);
                printf("\n\t\t\t\tDiastolic pressure(lower):");
                scanf("%d",&diastolic);
                printf("\n\t\t\t\tBlood Sugar(mmol/L):");
                scanf("%f",&blood_sugar);
                printf("\n\t\t\t\tHeart rate at rest(BPM):");
                scanf("%d",&heart_rate);
                printf("\n\t\t\t\tBody Temperature (F):");
                scanf("%f",&body_temperature);
                printf("\t\t\t\tWe successfully collected all the data !");
                printf("\n\t\t\t-----------------------------------------\n");
                float meter = height / 100, bmi;
                bmi = weight / (meter*meter);
                //--------------get current time-----------------------------------
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                //---------------------------------------------------------------------------
                char folder_record[]="Checkup/", record_username[30];
                strcpy(record_username,user_name);
                strcat(record_username,".txt");
                strcat(folder_record,record_username);
                admin_file = fopen(folder_record,"a");
                fprintf(admin_file,"Date: %02d-%02d-%d\n", tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900);
                fprintf(admin_file,"Systolic pressure(upper):%d\n",systolic);
                fprintf(admin_file,"Diastolic pressure(lower):%d\n",diastolic);
                fprintf(admin_file,"BMI:%0.2f\n",bmi);
                fprintf(admin_file,"Blood Sugar(mmol/L):%0.2f\n",blood_sugar);
                fprintf(admin_file,"Heart rate at rest(BPM):%d\n",heart_rate);
                fprintf(admin_file,"Body Temperature (F):%0.2f\n",body_temperature);
                fprintf(admin_file,"---------------------------\n");
                fclose(admin_file);
                strcpy(record_username,"");
                Data_analysis();
            }
            else
            {
                printf("\t\t\t\tUser name or Password incorrect !!\n\n");
                printf("\t\t\t\tFor User Menu press Enter!\n\t\t\t\t");
                gets(back_button);
                system("cls");
                //--------------for loading animation---------------
                int j,i;
                //--------------for loading animation---------------
                gotoxy(46,10);
                printf("Loading...");
                gotoxy(46,12);
                for(i=1; i <= 20 ; i++)
                {
                    for(j=0; j<=30000000 ; j++);
                    printf("%c",177);
                }
                system("cls");
                printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
                log_in_part2();
            }
        }

    }
    else if ( call_a_nurse == 2)
    {
        gets(back_button);
        system("cls");
        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }
    else
    {
        gets(back_button);
        system("cls");
        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }


}
//---------------------------------------end of Information Collecting function------------------------------------------------------


//--------------------------------------Others Problem function start -------------------------------------------------------------------
void Others_Problem()
{

    printf("\t\t\t\tplease write down you problem Details:\n\t\t\t\t");
    getchar();
    gets(other_problem);
    hospital_others_problem(user_name,other_problem);
    system("cls");

    //--------------for loading animation---------------
    int j,i;
    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=30000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
    log_in_part2();
}
//----------------------------------------end of Others Problem-----------------------------------------------------------------------


//---------------------------profile update function start------------------------------------------------------------------------
void profile_update()
{
    char folder[150]="Users List/";
    printf("\t\t\t\tUser name = ");
    getchar();
    gets(user_name);
    strcpy(temp,user_name);
    strcat(user_name,".txt");
    strcat(folder,user_name);
    reg_info = fopen(folder,"w");
    if(reg_info == NULL)
    {
        printf("File does not exist !!\n");
    }
    else
    {

        printf("\t\t\t\tPassword = ");
        gets(password);

        printf("\t\t\t\tEnter your age:");
        scanf("%d",&age);

        printf("\t\t\t\tGender(male/female) = ");
        scanf("%s",&gender);

        printf("\t\t\t\tHeight(cm) = ");
        scanf("%f",&height);

        printf("\t\t\t\tWeight(kg) = ");
        scanf("%f",&weight);

        printf("\t\t\t\tRegular disease Name & Details = ");
        getchar();
        gets(regu_disease);

        printf("\t\t\t\tBeing a smoker, Alcoholic , Drug Addicted(yes,yes,yes) : ");
        gets(Being_a_smoker);

        printf("\t\t\t\tContact Number = ");
        getchar();
        scanf("%s",&ph_number);
        printf("\t\t\t\t---------------------------------------------\n");

        fprintf(reg_info,"%s\n",temp);
        fprintf(admin_file,"%s\t\t",temp);
        fprintf(reg_info,"%s\n",password);
        fprintf(admin_file,"%s\n",password);
        fprintf(reg_info,"%d\n%s\n%0.2f \n%0.2f\n",age,gender,height,weight);
        fprintf(reg_info, "%s\n",regu_disease);
        fprintf(reg_info,"%s\n",Being_a_smoker);
        fprintf(reg_info,"%s\n",ph_number);

    }
    fclose(reg_info);
    remove(temp_for_read);
}
//----------------------------end of profile update function---------------------------------------------------------


//-----------------------------------------profile function start----------------------------------------------------------------
void profile()
{
    int profile_number;
    printf("\t\t\t\t1. View Profile \n");
    printf("\t\t\t\t2. Update Profile \n");
    printf("\t\t\t\t3. Previous Record \n");
    printf("\t\t\t\t4. Log out \n");
    printf("\t\t\t\t5. Delete Account \n");
    printf("\t\t\t\t------------------------------------------\n\t\t\t\t");
    scanf("%d",&profile_number);
    printf("\t\t\t\t------------------------------------------\n");
    if(profile_number == 1)
    {
        reg_info = fopen(temp_for_read,"r");
        if(reg_info == NULL)
        {
            printf("File does not exist !!\n");
        }
        else
        {

            fscanf(reg_info, "%s", &user_name);
            printf("\t\t\t\t\tUser name =  %s\n", user_name);

            fscanf(reg_info, "%s",&password);
            printf("\t\t\t\t\tPassword = %s\n", password);

            fscanf(reg_info,"%d",&age);
            printf("\t\t\t\t\tAge = %d\n",age);

            fscanf(reg_info, "%s", &gender);
            printf("\t\t\t\t\tGender = %s\n",gender);

            fscanf(reg_info, "%f", &height);
            printf("\t\t\t\t\tHeight = %0.2f\n", height);

            fscanf(reg_info, "%f", &weight);
            printf("\t\t\t\t\tWeight = %0.2f\n", weight);

            fscanf(reg_info, "%[^\n]%*c", &regu_disease);
            printf("\t\t\t\t\tRegular disease Name& Details =  %s\n", regu_disease);

            fscanf(reg_info, "%[^\n]%*c", &Being_a_smoker);
            printf("\t\t\t\t\tBeing a smoker, Alcoholic , Drug Addicted(yes,yes,yes) : %s\n",Being_a_smoker);

            fscanf(reg_info, "%[^\n]%*c", &ph_number);
            printf("\t\t\t\t\tPhone Number = %s\n",ph_number);
        }
        fclose(reg_info);
        printf("\n\t\t\t\tFor User Menu press Enter!\n\t\t\t\t");
        getchar();
        getchar();
        system("cls");
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();

    }
    else if(profile_number == 2 )
    {
        profile_update();
        printf("\t\t\t\tProfile update Successfully !!\n");
        printf("\n\t\t\t\tFor User Menu press Enter!\n\t\t\t\t");
        getchar();
        getchar();
        system("cls");
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }
    else if(profile_number == 3)
    {
        char folder[]="Checkup/",record_user_name[30];
        strcpy(record_user_name,user_name);
        strcat(record_user_name,".txt");
        strcat(folder,record_user_name);
        printf("\t\t\t\tPrevious Health Record !!\n");
        strcpy(folder_name_bmi,folder);
        admin_file = fopen(folder,"r");
        char abc[100];
        printf("\t\t\t\t--------------------------\n");
        while(fgets(abc,sizeof(abc),admin_file) != NULL)
        {
            fputs("\t\t\t\t",stdout);
            fputs(abc,stdout);
        }
        fclose(admin_file);
        strcpy(record_user_name,"");
        //-------------------------------------------------------------------------------------------------------------------------------------------------------
        printf("\n\t\t\t\tFor User Menu press Enter!\n\t\t\t\t");
        getchar();
        gets(back_button);
        system("cls");
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }
    else if(profile_number == 4)
    {
        system("cls");
        main();
    }
    else if(profile_number == 5)
    {
        int profile_delete;
        printf("\t\t\t\tAre you sure ?\n");
        printf("\t\t\t\t1. Yes \t2.No\n");
        printf("\t\t\t\t------------------------------------------\n\t\t\t\t");
        scanf("%d",&profile_delete);
        printf("\t\t\t\t------------------------------------------\n");
        if(profile_delete == 1)
        {
            strcpy(user_name,""); // clearing string ;
            strcpy(password,"");// clearing string ;
            reg_info = fopen(temp_for_read,"w");
            fclose(reg_info);
            remove(temp_for_read);
            system("cls");
            main();
        }
        else if(profile_delete == 2)
        {
            printf("\t\t\t\tThanks for Stay With Us !\n");
            printf("\n\t\t\t\tFor User Menu press Enter!\n\t\t\t\t");
            getchar();
            gets(back_button);
            system("cls");
            int j,i;
            //--------------for loading animation---------------
            gotoxy(46,10);
            printf("Loading...");
            gotoxy(46,12);
            for(i=1; i <= 20 ; i++)
            {
                for(j=0; j<=30000000 ; j++);
                printf("%c",177);
            }
            system("cls");
            printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
            log_in_part2();
        }
    }
    else
    {
        printf("\t\t\t\tFor User Menu press Enter!\n\t\t\t\t");
        gets(back_button);
        system("cls");
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }

}
//-----------------------------------------------end of profile function------------------------------------------------------------------------------------


//----------------------------------------log in part 2 start-------------------------------------------------------------------------------------------------
void log_in_part2()
{
    int user_menu;
    printf("\n");
    printf("\t\t\t-----------------------------------------\n");
    printf("\t\t\t1. Emergency\n");
    printf("\t\t\t2. Information Collecting\n");
    printf("\t\t\t3. Others Problem\n");
    printf("\t\t\t4. Profile\n");
    printf("\t\t\t-----------------------------------------\n\t\t\t");
    scanf("%d",&user_menu);
    printf("\t\t\t-----------------------------------------\n");
    if(user_menu == 1)
    {
        emergency();
    }
    else if(user_menu == 2)
    {
        Information_Collecting();
    }
    else if(user_menu == 3)
    {
        Others_Problem();
    }
    else if(user_menu == 4)
    {
        profile();
    }
    else
    {
        system("cls");
        gets(back_button);
        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }
}
//----------------------------------------end of log in part 2--------------------------------------------------------------------------------------------


//-----------------------------------pattern matching algorithm -----------------------------------------------------------------------------------
int patten_match(char *a, char *b)
{
    int c;
    int position = 0;
    char *x, *y;

    x = a;
    y = b;

    while(*a)
    {
        while(*x==*y)
        {
            x++;
            y++;
            if(*x=='\0'||*y=='\0')
                break;
        }
        if(*y=='\0')
            break;

        a++;
        position++;
        x = a;
        y = b;
    }
    if(*a)
        return position;
    else
        return -1;
}
//---------------------------------------en of pattern matching algorithm----------------------------------------------------------------------
//--------------------------------------log in function start-----------------------------------------------------------------------------------------------
void log_in()
{
    //--------------get current time-----------------------------------
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    //---------------------------------------------------------------------------

    int cmp_result1,cmp_result2,ch='a',k=0,day,month,year;
    char log_password[20]="a", log_username[30],log_temp[30], username_cpy[150];
    char folder[130]="Users List/";
    char approve_folder[]="Users List/a_",user_name_matching[1000];
    printf("\t\t\tUsername:");
    scanf("%s",&log_username);
    getchar();
//--------------------------pattern matching algorithm ----------------------------------------------------------------------------------
    pattern_matching = fopen("username_pattern_matching.txt","r");
    fscanf(pattern_matching,"%[^\n]%*c",&user_name_matching);
    int position;
    position = patten_match(user_name_matching,log_username);
//------------------------------------------------------------------------------------------------------------------------
    strcpy(log_temp,log_username);
    strcpy(username_cpy,log_username);
    strcat(log_username,".txt");
    strcat(folder,log_username);
    strcpy(temp_for_read,folder);
    reg_info = fopen(folder,"r");
    fscanf(reg_info, "%s %s %d %s %f %f %[^\n]%*c %[^\n]%*c %[^\n]%*c %d %d %d",&user_name,&password,&age,&gender,&height,&weight,&regu_disease,&Being_a_smoker,&ph_number,&day,&month,&year);
    strcat(username_cpy,".txt");
    strcat(approve_folder,username_cpy);
    payment = fopen(approve_folder,"r");
    if(payment != NULL)
    {
        SetColor(10);
        printf("\n\t\t\tAdmin has not approved you account yet. When Admin approve your account then\n\t\t\tyou can Login into your account , Please wait for approval !!\n");
        SetColor(15);
        fclose(payment);
        printf("\n\t\t\tPress Enter to Welcome Screen !!\n");
        printf("\t\t\t");
        gets(back_button);
        system("cls");
        main();
    }
    else if(position!=-1)
    {
            if(reg_info == NULL)
            {
                SetColor(4);
                printf("\n\t\t\t User name incorrect !!\n");
                SetColor(15);
                printf("\t\t\t");
                gets(back_button);
                users();
            }
            else
            {
                printf("\t\t\tPassword:");

                //--------for password hiding----------------
                while(1)
                {
                    ch = getch();
                    if(ch == ENTER)
                    {
                        break;
                    }
                    else if(ch == BKSP)
                    {
                        k--;
                        printf("\b \b");
                    }
                    else if(ch == TAB || ch == SPACE)
                    {
                        continue;
                    }
                    else
                    {
                        log_password[k] = ch;
                        k++;
                        printf("*");
                    }
                }

                //---------------end of password hiding---------------------
                cmp_result1 = strcmp(user_name,log_temp);
                cmp_result2 = strcmp(password,log_password);
                struct date d1;
                d1.dd =day;
                d1.mm =month;
                d1.yy=year;
                struct date d2;
                d2.dd =tm.tm_mday;
                d2.mm =tm.tm_mon + 1;
                d2.yy=tm.tm_year + 1900;
                int cmp = date_cmp(d1, d2);
                if(user_name == " ")
                {
                    SetColor(10);
                    printf("\t\t\tPlease Registration first , then try to Login your Account!\n\t\t\t");
                    SetColor(15);
                    gets(back_button);
                    users();
                }

                else if(cmp == 0)
                {
                    if(cmp_result1 == 0 && cmp_result2 == 0)
                    {
                        SetColor(2);
                        printf("\n\t\t\tLogin successfully !!!\n");
                        SetColor(15);
                        location_tracking();
                        log_in_part2();

                    }
                    else if(cmp_result1 != 0 && cmp_result2 != 0)
                    {
                        SetColor(4);
                        printf("\n\t\t\tUsername & Password incorrect !!!\n");
                        SetColor(15);
                        printf("\t\t\t");
                        gets(back_button);
                        users();
                    }
                    else if(cmp_result1 != 0)
                    {
                        SetColor(4);
                        printf("\n\t\t\tUsername incorrect !!!\n");
                        SetColor(15);
                        printf("\t\t\t");
                        gets(back_button);
                        users();
                    }
                    else
                    {
                        SetColor(4);
                        printf("\n\t\t\tpassword incorrect !!!\n");
                        SetColor(15);
                        printf("\t\t\t");
                        gets(back_button);
                        users();
                    }
                }
                else if (cmp > 0)
                {
                    if(cmp_result1 == 0 && cmp_result2 == 0)
                    {
                        SetColor(2);
                        printf("\n\t\t\tLogin successfully !!!\n");
                        SetColor(15);
                        location_tracking();
                        log_in_part2();

                    }
                    else if(cmp_result1 != 0 && cmp_result2 != 0)
                    {
                        SetColor(4);
                        printf("\n\t\t\tUsername & Password incorrect !!!\n");
                        SetColor(15);
                        printf("\t\t\t");
                        gets(back_button);
                        users();
                    }
                    else if(cmp_result1 != 0)
                    {
                        SetColor(4);
                        printf("\n\t\t\tUsername incorrect !!!\n");
                        SetColor(15);
                        printf("\t\t\t");
                        gets(back_button);
                        users();
                    }
                    else
                    {
                        printf("\n\t\t\tpassword incorrect !!!\n");
                        printf("\t\t\t");
                        gets(back_button);
                        users();
                    }
                }
                else
                {
                    SetColor(4);
                    printf("\n\t\t\tYour package has expired.  Please Sign Up again with your previous Username.\n");
                    SetColor(15);
                    printf("\t\t\t");
                    gets(back_button);
                    users();
                }

                //----------------password checking --------------------------------

            }
            fclose(reg_info);
    }
    else
    {
        SetColor(4);
        printf("\n\t\t\tUsername not match !!\n");
        SetColor(15);
        printf("\t\t\t");
        gets(back_button);
        users();
    }
    fclose(pattern_matching);
}
//-------------------------------------end of log in function----------------------------------------------------------


//-----------------------------------payment system start----------------------------------------------------------
void bkash(float bill, char method[])
{
    char mobile_number[15], Transaction_Number[50];
    printf("\t\t\tPlease Pay first . when payment is Completed,\n\t\t\tyou will get a Transaction Id . Keep it for next use !\n\n");
    printf("\t\t\tBkash Number:+8801853267838(personal).\n\n");
    printf("\t\t\tAmount : $%0.2f\n\n",bill);
    printf("\t\t\tFill up the sender information.\n");
    printf("\t\t\tMobile Number: ");
    getchar();
    gets(mobile_number);
    printf("\t\t\tTransaction Number: ");
    gets(Transaction_Number);
    payment = fopen("payment.txt","a");
    fprintf(payment,"Payment System: %s => Mobile Number: %s\nTransaction Number: %s  => ",method,mobile_number,Transaction_Number);
    fclose(payment);
}
void rocket(float bill, char method[])
{
    char mobile_number[15], Transaction_Number[50];
    printf("\t\t\tPlease Pay first . when payment is Completed,\n\t\t\tyou will get a Transaction Id . Keep it for next use !\n\n");
    printf("\t\t\tRocket Number:+8801853267838.\n\n");
    printf("\t\t\tAmount : $%0.2f\n\n",bill);
    printf("\t\t\tFill up the sender information.\n");
    printf("\t\t\tMobile Number: ");
    getchar();
    gets(mobile_number);
    printf("\t\t\tTransaction Number: ");
    gets(Transaction_Number);
    payment = fopen("payment.txt","a");
    fprintf(payment,"Payment System: %s => Mobile Number: %s\nTransaction Number: %s => ",method,mobile_number,Transaction_Number);
    fclose(payment);
}
void nagad(float bill, char method[])
{
    char mobile_number[15], Transaction_Number[50];
    printf("\t\t\tPlease Pay first . when payment is Completed,\n\t\t\tyou will get a Transaction Id . Keep it for next use !\n\n");
    printf("\t\t\tNagad Number:+8801853267838.\n\n");
    printf("\t\t\tAmount : $%0.2f\n\n",bill);
    printf("\t\t\tFill up the sender information.\n");
    printf("\t\t\tMobile Number: ");
    getchar();
    gets(mobile_number);
    printf("\t\t\tTransaction Number: ");
    gets(Transaction_Number);
    payment = fopen("payment.txt","a");
    fprintf(payment,"Payment System: %s => Mobile Number: %s\nTransaction Number: %s => ",method,mobile_number,Transaction_Number);
    fclose(payment);
}
//-----------------------------------end of payment system----------------------------------------------------------


//------------------------------users function start-----------------------------------------------------------------------
void users()
{
    int number2,r,q;
    system("cls");
    //--------------for loading animation---------------
    gotoxy(46,10); //from "Rafiqul.h"
    printf("Loading...");
    gotoxy(46,12);
    for(r=1; r <= 20 ; r++)
    {
        for(q=0; q<=32000000 ; q++);
        printf("%c",177);
    }
    system("cls");
    //-----------------------end of loading animation-----------------------------------------
    printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Secion\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
    printf("\t\t\t-------------------------\n");
    printf("\t\t\t1. Sign Up \n");
    printf("\t\t\t2. Log in \n");
    printf("\t\t\t-------------------------\n\t\t\t");
    scanf("%d",&number2);
    printf("\t\t\t-------------------------\n");
    if(number2 == 1)
    {
        printf("\t\t\t=================================================================\n");
        printf("\t\t\t=                                                               =\n");
        printf("\t\t\t=                        Select a Plan.                         =\n");
        printf("\t\t\t=                                                               =\n");
        printf("\t\t\t=================================================================\n\n");
        printf("\t\t\t=================\t=================\t=================\n");
        printf("\t\t\t=     Basic     =\t=    Standard   =\t=    Premium    =\n");
        printf("\t\t\t=================\t=================\t=================\n");
        printf("\t\t\t=               =\t=               =\t=               =\n");
        printf("\t\t\t=     3 Days    =\t=    1 Month    =\t=    1 Year     =\n");
        printf("\t\t\t=               =\t=               =\t=               =\n");
        printf("\t\t\t=     $0.00     =\t=    $ 9.99     =\t=    $ 99.99    =\n");
        printf("\t\t\t=               =\t=               =\t=               =\n");
        printf("\t\t\t=================\t=================\t=================\n");
        printf("\t\t\t=               =\t=               =\t=               =\n");
        printf("\t\t\t=     Enter 1   =\t=    Enter 2    =\t=    Enter 3    =\n");
        printf("\t\t\t=               =\t=               =\t=               =\n");
        printf("\t\t\t=================\t=================\t=================\n\n");
        printf("\t\t\t=================================================================\n");
        printf("\t\t\t");
        int plan;
        scanf("%d",&plan);
        printf("\t\t\t=================================================================\n");
        if(plan == 1)
        {
            char planname[]="Basic";
            int days = 3;
            user_basic_sign_up(planname,days);
        }
        else if(plan == 2)
        {
            int payment_s ;
            float bill =9.99;
            printf("\t\t\tPlease Select a Payment Method .\n");
            printf("\t\t\t   1. Bkash\n");
            printf("\t\t\t   2. Rocket\n");
            printf("\t\t\t   3. Nagad\n");
            printf("\t\t\t---------------------------------------\n\t\t\t   ");
            scanf("%d",&payment_s);
            printf("\t\t\t---------------------------------------\n");
            if(payment_s == 1)
            {
                char method[]="Bkash";
                bkash(bill,method);
            }
            else if(payment_s == 2)
            {
                char method[]="Rocket";
                rocket(bill,method);
            }
            else if(payment_s == 3)
            {
                char method[]="Nagad";
                nagad(bill,method);
            }
            else
            {
                users();
            }
            printf("\t\t\t---------------------------------------\n");
            char planname[]="Standard";
            int days = 30;
            sign_up(planname,days);
        }
        else if(plan == 3)
        {
            int payment_s ;
            float bill =99.99;
            printf("\t\t\tPlease Select a Payment Method .\n");
            printf("\t\t\t   1. Bkash\n");
            printf("\t\t\t   2. Rocket\n");
            printf("\t\t\t   3. Nagad\n");
            printf("\t\t\t---------------------------------------\n\t\t\t   ");
            scanf("%d",&payment_s);
            printf("\t\t\t---------------------------------------\n");
            if(payment_s == 1)
            {
                char method[]="Bkash";
                bkash(bill,method);
            }
            else if(payment_s == 2)
            {
                char method[]="Rocket";
                rocket(bill,method);
            }
            else if(payment_s == 3)
            {
                char method[]="Nagad";
                nagad(bill,method);
            }
            else
            {
                users();
            }
            printf("\t\t\t---------------------------------------\n");
            char planname[]="Premium";
            int days = 365;
            sign_up(planname,days);
        }
        else
        {
            users();
        }
    }
    else if(number2 == 2)
    {
        log_in();
    }

    else
    {
        system("cls");
        gets(back_button);
        users();
    }

}
//----------------------------------------end of users function-----------------------------------------


//------------------------------------blood pressure function start------------------------------------------------
//**********We collected all the information from American Heart Association *********
void blood_pressure()
{
    if(systolic < 90 && diastolic <60)
    {
        printf("\t\t\tLow Blood Pressure (Hypotension)\n");
    }
    if((systolic >= 90 && systolic < 120) && (diastolic >= 60 && diastolic <80))
    {
        printf("\t\t\tyour blood pressure is normal !!\n");
    }
    else if((systolic >= 120 && systolic <= 129) &&(diastolic >= 60 && diastolic < 80))
    {
        printf("\t\t\tEleveted\n");
    }
    else if((systolic >= 130 && systolic <= 139) && (diastolic >= 80 && diastolic <=89))
    {
        printf("\t\t\tHigh Blood Pressure (Hypertension) ,Stage-1\n");
    }
    else if((systolic >= 140 && systolic < 180) && (diastolic >= 90 && diastolic < 120))
    {
        printf("\t\t\tHigh Blood Pressure (Hypertension) ,Stage-2\n");
    }
    else if(systolic >= 180 && diastolic >= 120)
    {
        printf("\t\t\t\tHypertensive crisis ! (Seek Emergency care)\n");
    }
    else
    {
        printf("\t\t\tBlood pressure section doesn't work perfectly. Need to Upgrade !!\n");
    }
}
//------------------------------------end of blood pressure function------------------------------------------------


//-------------------------------------blood sugar function start-------------------------------------------------------
void blood_sugar_function()
{
    if(blood_sugar <3 )
    {
        printf("\t\t\tSevere Hypoglycemia !\n");
    }
    else if(blood_sugar >=3 && blood_sugar <3.9)
    {
        printf("\t\t\tHypoglycemia !\n");
    }
    else if(blood_sugar >=3.9 && blood_sugar <7)
    {
        printf("\t\t\tNormal !\n");
    }
    else if(blood_sugar >=7 && blood_sugar < 10)
    {
        printf("\t\t\tHigh(Take Action)\n");
    }
    else if(blood_sugar >=10 && blood_sugar <= 27.7)
    {
        printf("\t\t\tMetabolic Consequence (Take Action) ! \n");
    }
    else
    {
        printf("\t\t\tBlood Sugar value must be 4 - 27.7 !!\n");
    }
}
//-----------------------------------end of blood sugar function----------------------------------------------------------------------------


//---------------------------------------Heart rate function start-----------------------------------------------------------------------------
//**********We collected all the information from https://www.pinterest.com/pin/627618898053827576/  ********
void Heart_rate()
{
    if(strcmp(gender,"male") == 0)
    {
        if(age >=18 && age <= 25)
        {
            if(heart_rate >= 49 && heart_rate <= 55)
            {
                printf("\t\t\tAthlete !\n");
            }
            else if(heart_rate >= 56 && heart_rate <=61)
            {
                printf("\t\t\tExcellent !\n");
            }
            else if(heart_rate >=  62 && heart_rate <=65)
            {
                printf("\t\t\tGreat !\n");
            }
            else if(heart_rate >= 66 && heart_rate <=69)
            {
                printf("\t\t\tGood !\n");
            }
            else if(heart_rate >= 70 && heart_rate <=73)
            {
                printf("\t\t\tAverage !\n");
            }
            else if(heart_rate >= 74 && heart_rate <=81)
            {
                printf("\t\t\tBelow Average !\n");
            }
            else if(heart_rate >83)
            {
                printf("\t\t\tPoor !");
            }
            else
            {
                printf("\t\t\tPlease Enter normal value !!\n");
            }
        }
        else if(age >= 26 && age >= 35)
        {
            if(heart_rate >= 49 && heart_rate <= 54)
            {
                printf("\t\t\tAthlete !\n");
            }
            else if(heart_rate >= 55 && heart_rate <=61)
            {
                printf("\t\t\tExcellent !\n");
            }
            else if(heart_rate >=  62 && heart_rate <=65)
            {
                printf("\t\t\tGreat !\n");
            }
            else if(heart_rate >= 66 && heart_rate <=70)
            {
                printf("\t\t\tGood !\n");
            }
            else if(heart_rate >= 71 && heart_rate <=74)
            {
                printf("\t\t\tAverage !\n");
            }
            else if(heart_rate >= 75 && heart_rate <=81)
            {
                printf("\t\t\tBelow Average !\n");
            }
            else if(heart_rate >82)
            {
                printf("\t\t\tPoor !\n");
            }
            else
            {
                printf("\t\t\tPlease Enter normal value !!\n");
            }
        }
        else if(age >= 36 && age >= 45)
        {
            if(heart_rate >= 50 && heart_rate <= 56)
            {
                printf("\t\t\tAthlete !\n");
            }
            else if(heart_rate >= 57 && heart_rate <=62)
            {
                printf("\t\t\tExcellent !\n");
            }
            else if(heart_rate >=  63 && heart_rate <=66)
            {
                printf("\t\t\tGreat !\n");
            }
            else if(heart_rate >= 67 && heart_rate <=70)
            {
                printf("\t\t\tGood !\n");
            }
            else if(heart_rate >= 71 && heart_rate <=75)
            {
                printf("\t\t\tAverage !\n");
            }
            else if(heart_rate >= 76 && heart_rate <=82)
            {
                printf("\t\t\tBelow Average !\n");
            }
            else if(heart_rate >83)
            {
                printf("\t\t\tPoor !");
            }
            else
            {
                printf("\t\t\tPlease Enter normal value !!\n");
            }
        }
        else if(age >= 46 && age >= 55)
        {
            if(heart_rate >= 50 && heart_rate <= 57)
            {
                printf("\t\t\tAthlete !\n");
            }
            else if(heart_rate >= 58 && heart_rate <=63)
            {
                printf("\t\t\tExcellent !\n");
            }
            else if(heart_rate >=  64 && heart_rate <=67)
            {
                printf("\t\t\tGreat !\n");
            }
            else if(heart_rate >= 68 && heart_rate <=71)
            {
                printf("\t\t\tGood !\n");
            }
            else if(heart_rate >= 72 && heart_rate <=76)
            {
                printf("\t\t\tAverage !\n");
            }
            else if(heart_rate >= 77 && heart_rate <=83)
            {
                printf("\t\t\tBelow Average !\n");
            }
            else if(heart_rate >84)
            {
                printf("\t\t\tPoor !\n");
            }
            else
            {
                printf("\t\t\tPlease Enter normal value !!\n");
            }
        }
        else if(age >= 56 && age >= 65)
        {
            if(heart_rate >= 51 && heart_rate <= 56)
            {
                printf("\t\t\tAthlete !\n");
            }
            else if(heart_rate >= 57 && heart_rate <=61)
            {
                printf("\t\t\tExcellent !\n");
            }
            else if(heart_rate >=  62 && heart_rate <=67)
            {
                printf("\t\t\tGreat !\n");
            }
            else if(heart_rate >= 68 && heart_rate <=71)
            {
                printf("\t\t\tGood !\n");
            }
            else if(heart_rate >= 72 && heart_rate <=75)
            {
                printf("\t\t\tAverage !\n");
            }
            else if(heart_rate >= 76 && heart_rate <=81)
            {
                printf("\t\t\tBelow Average !\n");
            }
            else if(heart_rate >82)
            {
                printf("\t\t\tPoor !\n");
            }
            else
            {
                printf("\t\t\tPlease Enter normal value !!\n");
            }
        }
        else if(age > 65)
        {
            if(heart_rate >= 50 && heart_rate <= 55)
            {
                printf("\\t\t\tAthlete !\n");
            }
            else if(heart_rate >= 56 && heart_rate <=61)
            {
                printf("\t\t\tExcellent !\n");
            }
            else if(heart_rate >=  62 && heart_rate <=65)
            {
                printf("\t\t\tGreat !\n");
            }
            else if(heart_rate >= 66 && heart_rate <=69)
            {
                printf("\t\t\tGood !\n");
            }
            else if(heart_rate >= 70 && heart_rate <=73)
            {
                printf("\t\t\tAverage !\n");
            }
            else if(heart_rate >= 74 && heart_rate <=79)
            {
                printf("\t\t\tBelow Average !\n");
            }
            else if(heart_rate >=80)
            {
                printf("\t\t\tPoor !\n");
            }
            else
            {
                printf("\t\t\tWe start working at 49-80+ BPM  !!\n");
            }
        }
        else
        {
            printf("\t\t\twe start working at age greater than 17 \n");
        }
    }
    else if(strcmp(gender,"female") == 0)
    {
        if(age >=18 && age <= 25)
        {
            if(heart_rate >= 54 && heart_rate <= 60)
            {
                printf("\t\t\tAthlete !\n");
            }
            else if(heart_rate >= 61 && heart_rate <=65)
            {
                printf("\t\t\tExcellent !\n");
            }
            else if(heart_rate >=  66 && heart_rate <=69)
            {
                printf("\t\t\tGreat !\n");
            }
            else if(heart_rate >= 70 && heart_rate <= 73)
            {
                printf("\t\t\tGood !\n");
            }
            else if(heart_rate >= 74 && heart_rate <=78)
            {
                printf("\t\t\tAverage !\n");
            }
            else if(heart_rate >= 79 && heart_rate <=84)
            {
                printf("\t\t\tBelow Average !\n");
            }
            else if(heart_rate >85)
            {
                printf("\t\t\tPoor !\n");
            }
            else
            {
                printf("\t\t\tPlease Enter normal value !!\n");
            }
        }
        else if(age >= 26 && age >= 35)
        {
            if(heart_rate >= 54 && heart_rate <= 59)
            {
                printf("\t\t\tAthlete !\n");
            }
            else if(heart_rate >= 60 && heart_rate <=64)
            {
                printf("\t\t\tExcellent !\n");
            }
            else if(heart_rate >=  65 && heart_rate <=68)
            {
                printf("\t\t\tGreat !\n");
            }
            else if(heart_rate >= 69 && heart_rate <=72)
            {
                printf("\t\t\tGood !\n");
            }
            else if(heart_rate >= 73 && heart_rate <=76)
            {
                printf("\t\t\tAverage !\n");
            }
            else if(heart_rate >= 77 && heart_rate <=82)
            {
                printf("\t\t\tBelow Average !\n");
            }
            else if(heart_rate >83)
            {
                printf("\t\t\tPoor !\n");
            }
            else
            {
                printf("\t\t\tPlease Enter normal value !!\n");
            }
        }
        else if(age >= 36 && age >= 45)
        {
            if(heart_rate >= 54 && heart_rate <= 59)
            {
                printf("\t\t\tAthlete !\n");
            }
            else if(heart_rate >= 60 && heart_rate <=64)
            {
                printf("\t\t\tExcellent !\n");
            }
            else if(heart_rate >=  65 && heart_rate <=69)
            {
                printf("\t\t\tGreat !\n");
            }
            else if(heart_rate >= 70 && heart_rate <=73)
            {
                printf("\t\t\tGood !\n");
            }
            else if(heart_rate >= 74 && heart_rate <=78)
            {
                printf("\t\t\tAverage !\n");
            }
            else if(heart_rate >= 79 && heart_rate <=84)
            {
                printf("\t\t\tBelow Average !\n");
            }
            else if(heart_rate >85)
            {
                printf("\t\t\tPoor !\n");
            }
            else
            {
                printf("\t\t\tPlease Enter normal value !!\n");
            }
        }
        else if(age >= 46 && age >= 55)
        {
            if(heart_rate >= 54 && heart_rate <= 60)
            {
                printf("\t\t\tAthlete !\n");
            }
            else if(heart_rate >= 61 && heart_rate <=65)
            {
                printf("\t\t\tExcellent !\n");
            }
            else if(heart_rate >=  66 && heart_rate <=69)
            {
                printf("\t\t\tGreat !\n");
            }
            else if(heart_rate >= 70 && heart_rate <=73)
            {
                printf("\t\t\tGood !\n");
            }
            else if(heart_rate >= 74 && heart_rate <=77)
            {
                printf("\t\t\tAverage !\n");
            }
            else if(heart_rate >= 78 && heart_rate <=83)
            {
                printf("\t\t\tBelow Average !\n");
            }
            else if(heart_rate >84)
            {
                printf("\t\t\tPoor !\n");
            }
            else
            {
                printf("\t\t\tPlease Enter normal value !!\n");
            }
        }
        else if(age >= 56 && age >= 65)
        {
            if(heart_rate >= 54 && heart_rate <= 59)
            {
                printf("\t\t\tAthlete !\n");
            }
            else if(heart_rate >= 60 && heart_rate <=64)
            {
                printf("\t\t\tExcellent !\n");
            }
            else if(heart_rate >=  65 && heart_rate <=68)
            {
                printf("\t\t\tGreat !\n");
            }
            else if(heart_rate >= 69 && heart_rate <=73)
            {
                printf("\t\t\tGood !\n");
            }
            else if(heart_rate >= 74 && heart_rate <=77)
            {
                printf("\t\t\tAverage !\n");
            }
            else if(heart_rate >= 78 && heart_rate <=83)
            {
                printf("\t\t\tBelow Average !\n");
            }
            else if(heart_rate >84)
            {
                printf("\t\t\tPoor !\n");
            }
            else
            {
                printf("\t\t\tPlease Enter normal value !!\n");
            }
        }
        else if(age > 65)
        {
            if(heart_rate >= 54 && heart_rate <= 59)
            {
                printf("\t\t\tAthlete !\n");
            }
            else if(heart_rate >= 60 && heart_rate <=64)
            {
                printf("\t\t\tExcellent !\n");
            }
            else if(heart_rate >=  65 && heart_rate <=68)
            {
                printf("\t\t\tGreat !\n");
            }
            else if(heart_rate >= 69 && heart_rate <=72)
            {
                printf("\t\t\tGood !\n");
            }
            else if(heart_rate >= 73 && heart_rate <=76)
            {
                printf("\t\t\tAverage !\n");
            }
            else if(heart_rate >= 77 && heart_rate <=84)
            {
                printf("\t\t\tBelow Average !\n");
            }
            else if(heart_rate >=85)
            {
                printf("\t\t\tPoor !\n");
            }
            else
            {
                printf("\t\t\tWe start working at 54-85+ BPM  !!\n");
            }
        }
        else
        {
            printf("\t\t\twe start working at age greater than 17. \n");
        }
    }
    else
    {
        printf("\n\t\t\t Maybe you can not type (male / female) in registration \n");
    }

}
//----------------------------------end of Heart rate function----------------------------------------------------


//------------------------------------body temperature function start-----------------------------------------
//**********we collected all the information from https://en.wikipedia.org/wiki/Human_body_temperature ******
void body_temperature_function()
{
    if(body_temperature >= 95  && body_temperature <96.8)
    {
        printf("\t\t\tIntense shivering, numbness and bluish/grayness of the skin. There is the possibility of heart irritability.\n");
    }
    else if(body_temperature >= 96.8 && body_temperature <97.7)
    {
        printf("\t\t\tFeeling cold, mild to moderate shivering. Body temperature may drop this low during sleep. May be a normal body temperature.\n");
    }
    else if(body_temperature >= 97.7 && body_temperature <99.5 )
    {
        printf("\t\t\tNormal body temperature\n");
    }
    else if(body_temperature >=99.5 && body_temperature < 100.4)
    {
        printf("\t\t\tFeeling hot, sweating, feeling thirsty, feeling very uncomfortable, slightly hungry. If this is caused by fever, there may also be chills.\n");
    }
    else if(body_temperature >= 100.4 && body_temperature <102.2)
    {
        printf("\t\t\tSevere sweating, flushed and red. Fast heart rate and breathlessness. There may be exhaustion accompanying this. Children and people with epilepsy may be very likely to get convulsions at this point.\n");
    }
    else if(body_temperature >= 102.2 && body_temperature <104)
    {
        printf("\t\t\tFainting, dehydration, weakness, vomiting, headache, breathlessness and dizziness may occur as well as profuse sweating. Starts to be life-threatening.\n");
    }
    else if(body_temperature >= 104 && body_temperature < 105.8)
    {
        printf("\t\t\tFainting, vomiting, severe headache, dizziness, confusion, hallucinations, delirium and drowsiness can occur. There may also be palpitations and breathlessness.\n");
    }
    else if(body_temperature >=105.8 && body_temperature <107.6)
    {
        printf("\t\t\tSubject may turn pale or remain flushed and red. They may become comatose, be in severe delirium, vomiting, and convulsions can occur. Blood pressure may be high or low and heart rate will be very fast.\n");
    }
    else if(body_temperature >= 107.6 && body_temperature <109.4)
    {
        printf("\t\t\tNormally death, or there may be serious brain damage, continuous convulsions and shock. Cardio-respiratory collapse will likely occur.\n");
    }
    else if(body_temperature >=109.4 && body_temperature <=111.2)
    {
        printf("\t\t\tAlmost certainly death will occur\n");
    }
    else
    {
        printf("\t\t\tThe Temperature value must be  95 to 111.2\n");
    }
}
//------------------------------------end of body temperature function -----------------------------------------------------


//---------------------------------BMI start function------------------------------------------------------------------------------------
void BMI()
{
    float meter = height / 100, bmi;
    bmi = weight / (meter*meter);
    printf("\t\t\tBMI = %0.2f",bmi);
    if(bmi < 18.5)
    {
        printf("\n\t\t\t\t\tUnderweight !!\n");
    }
    else if(bmi >= 18.5 && bmi <= 24.9)
    {
        printf("\n\t\t\t\tNormal Weight !\n");
    }
    else if(bmi >=25 && bmi <=29.9)
    {
        printf("\n\t\t\t\t\tpre - obesity !\n");
    }
    else if(bmi >= 30 && bmi <=34.9)
    {
        printf("\n\t\t\t\t\tObesity class - I !\n");
    }
    else if(bmi >=35 && bmi <=39.9)
    {
        printf("\n\t\t\t\t\tObesity class - II !\n");
    }
    else if(bmi >=40)
    {
        printf("\n\t\t\t\tObesity class - III !\n");
    }
    else
    {
        printf("\n\t\t\t\tBMI does't work Perfectly . Need to Upgrade !! \n");
    }
}
//-------------------------------end of BMI function------------------------------------------------------------------------------------


//----------------------------------data analysis function start----------------------------------------------------------------
void Data_analysis()
{
    int advice_value;
    float  body_temperature ;
    printf("\t\t\tBlood pressure result: \n\t");
    blood_pressure();
    printf("\n\t\t\tBMI result: \n\t");
    BMI();
    printf("\n\t\t\tBlood sugar result: \n\t");
    blood_sugar_function();
    printf("\n\t\t\tHeart rate result: \n\t");
    Heart_rate();
    printf("\n\t\t\tBody Temperature result: \n\t");
    body_temperature_function();
    printf("\t\t\t-----------------------------------\n\t\t\t");
    printf("\n\t\t\tNeed Advice !\n");
    printf("\t\t\t1. Yes\t2.No\n");
    printf("\t\t\t-----------------------------------\n\t\t\t");
    scanf("%d",&advice_value);
    if(advice_value == 1)
    {
        system("explorer https://www.mayoclinic.org/diseases-conditions/high-blood-pressure/in-depth/high-blood-pressure/art-20046974");
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }
    else if(advice_value == 2)
    {
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }
    else
    {
        printf("\t\t\tPlease select 1 or 2 !\n\n");
        printf("\t\t\tPress Enter to User Menu !\n\t\t\t");
        gets(back_button);
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tUser Section\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        log_in_part2();
    }


}
//----------------------------------end of data analysis function--------------------------------------------------------------------


//------------------------------------ admin register function start ---------------------------------------------------------------------
void admin_register()
{
    admin_file = fopen("admin_info.txt","w");
    if(admin_file == NULL)
    {
        printf("\t\t\tFile does not exist !!\n");
    }
    else
    {
        printf("\t\t\tUser name = ");
        getchar();
        gets(admin_user_name);

        printf("\t\t\tPassword = ");
        gets(admin_password);

        printf("\t\t\te-mail: ");
        gets(admin_email);

        printf("\t\t\tEnter your age:");
        scanf("%d",&admin_age);

        printf("\t\t\tGender(male/female) = ");
        scanf("%s",&admin_gender);

        printf("\t\t\tContact Number = ");
        getchar();
        scanf("%s",&admin_ph);
        printf("\t\t\t---------------------------------------------\n");

        fprintf(admin_file,"%s\n",admin_user_name);
        fprintf(admin_file,"%s\n",admin_password);
        fprintf(admin_file, "%s\n",admin_email);
        fprintf(admin_file,"%d\n",admin_age);
        fprintf(admin_file,"%s\n",admin_gender);
        fprintf(admin_file,"%s\n",admin_ph);

    }
    fclose(admin_file);
    system("cls");
    int number2,r,q,j,i;

    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=32000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    //-----------------------end of loading animation-----------------------------------------
    printf("\n\n\t\t\t=================================\n\t\t\t=\t\t\t\t=\n\t\t\t=\tLogin to Admin Panel\t= \t\t\n\t\t\t=\t\t\t\t=\n\t\t\t=================================\n\n\n");
    admin_login();
}
//---------------------------------------end of admin register function------------------------------------------------------------------------------------------


//--------------------------------admin update profile function start----------------------------------------------------------------------------------
void admin_update_profile()
{
    admin_file = fopen("admin_info.txt","w");
    if(admin_file == NULL)
    {
        printf("\t\t\tFile does not exist !!\n");
    }
    else
    {
        printf("\t\t\t\tUser name = ");
        getchar();
        gets(admin_user_name);

        printf("\t\t\t\tPassword = ");
        gets(admin_password);

        printf("\t\t\t\te-mail: ");
        gets(admin_email);

        printf("\t\t\t\tEnter your age: ");
        scanf("%d",&admin_age);

        printf("\t\t\t\tGender(male/female) = ");
        scanf("%s",&admin_gender);

        printf("\t\t\t\tContact Number = ");
        getchar();
        scanf("%s",&admin_ph);
        printf("\t\t\t\t---------------------------------------------\n");
        printf("\t\t\t\tProfile Update Successfully !\n");

        fprintf(admin_file,"%s\n",admin_user_name);
        fprintf(admin_file,"%s\n",admin_password);
        fprintf(admin_file, "%s\n",admin_email);
        fprintf(admin_file,"%d\n",admin_age);
        fprintf(admin_file,"%s\n",admin_gender);
        fprintf(admin_file,"%s\n",admin_ph);

    }
    fclose(admin_file);
    printf("\t\t\t\t");
    getchar();
    getchar();
    system("cls");

    //--------------for loading animation---------------
    int j,i;
    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=30000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    printf("\n\n\t\t\t=============================\n\t\t\t=\t\t\t    =\n\t\t\t=   Log in to Admin Panel   = \t\t\n\t\t\t=\t\t\t    =\n\t\t\t=============================\n\n\n");
    admin_login();
}
//------------------------------------------end of admin update profile function-----------------------------------------------------------------


//-----------------------------------------user list function start ------------------------------------------------------------------------------------------
void user_list()
{
    admin_file = fopen("users_list.txt","r");
    char abc[100];
    printf("\t\t\t\tUser name\tPassword\tPackege\t  Reg. Date\tExp. Date\n");
    printf("\t\t\t\t------------------------------------------------------------------\n");
    while(fgets(abc,sizeof(abc),admin_file) != NULL)
    {
        fputs("\t\t\t\t",stdout);
        fputs(abc,stdout);
    }
    fclose(admin_file);
    printf("\t\t\t\t");
    getchar();
    gets(back_button);;
    system("cls");

    //--------------for loading animation---------------
    int j,i;
    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=30000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
    admin_login_part2();
}
//-----------------------------------------end of user list function ------------------------------------------------------------------------------------------


//------------------------------------------------users information function start----------------------------------------------------------------------
void user_information()
{
    int user_information;
    printf("\t\t\t\t1. Users list \n");
    printf("\t\t\t\t2. User Details \n");
    printf("\t\t\t\t3. Users Record \n");
    printf("\t\t\t\t4. Add User \n");
    printf("\t\t\t\t5. Delete User\n");
    printf("\t\t\t\t------------------------------------------\n\t\t\t\t");
    scanf("%d",&user_information);
    printf("\t\t\t\t------------------------------------------\n");
    if(user_information == 1)
    {
        user_list();
    }
    else if(user_information == 2)
    {
        char user_details[30],folder[]="Users List/";;
        strcpy(user_name,""); // clearing string ;
        strcpy(password,"");// clearing string ;

        printf("\t\t\t\tDetails info. for : ");
        getchar();
        gets(user_details);
        strcat(user_details,".txt");
        strcat(folder,user_details);
        reg_info = fopen(folder,"r");
        if(reg_info == NULL)
        {
            printf("\t\t\t\tUsername not found ! \n");
        }
        else
        {
            fscanf(reg_info, "%s %s %d %s %f %f %[^\n]%*c %[^\n]%*c %[^\n]%*c",&user_name,&password,&age,&gender,&height,&weight,&regu_disease,&Being_a_smoker,&ph_number);

            printf("\t\t\t\t\tUser name =  %s\n", user_name);

            printf("\t\t\t\t\tPassword = %s\n", password);

            printf("\t\t\t\t\tAge = %d\n",age);

            printf("\t\t\t\t\tGender = %s\n",gender);

            printf("\t\t\t\t\tHeight = %0.2f\n", height);

            printf("\t\t\t\t\tWeight = %0.2f\n", weight);

            printf("\t\t\t\t\tRegular disease Name& Details =  %s\n", regu_disease);

            printf("\t\t\t\t\tBeing a smoker, Alcoholic , Drug Addicted(yes,yes,yes) : %s\n",Being_a_smoker);

            printf("\t\t\t\t\tPhone Number = %s\n",ph_number);
        }
        printf("\t\t\t\t\t");
        getchar();
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();

    }
    else if(user_information == 3)
    {
        char folder[]="Checkup/", Users_record_name[30];
        printf("\t\t\t\tPrevious Health Record for: ");
        getchar();
        gets(Users_record_name);
        printf("\t\t\t\t--------------------------\n");
        strcat(Users_record_name,".txt");
        strcat(folder,Users_record_name);
        admin_file = fopen(folder,"r");
        if(admin_file == NULL)
        {
            printf("\t\t\t\tUsername not matched !!\n");
            printf("\t\t\t\t\t");
            gets(back_button);
            system("cls");

            //--------------for loading animation---------------
            int j,i;
            //--------------for loading animation---------------
            gotoxy(46,10);
            printf("Loading...");
            gotoxy(46,12);
            for(i=1; i <= 20 ; i++)
            {
                for(j=0; j<=30000000 ; j++);
                printf("%c",177);
            }
            system("cls");
            printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
            admin_login_part2();
        }
        else
        {
            char abc[100];
            printf("\t\t\t\t--------------------------\n");
            while(fgets(abc,sizeof(abc),admin_file) != NULL)
            {
                fputs("\t\t\t\t",stdout);
                fputs(abc,stdout);
            }
            fclose(admin_file);
            printf("\t\t\t\t\t");
            gets(back_button);
            system("cls");

            //--------------for loading animation---------------
            int j,i;
            //--------------for loading animation---------------
            gotoxy(46,10);
            printf("Loading...");
            gotoxy(46,12);
            for(i=1; i <= 20 ; i++)
            {
                for(j=0; j<=30000000 ; j++);
                printf("%c",177);
            }
            system("cls");
            printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
            admin_login_part2();
        }
    }
    else if(user_information == 4)
    {
        printf("\t\t\t=================================================================\n");
        printf("\t\t\t=                                                               =\n");
        printf("\t\t\t=                        Select a Plan.                         =\n");
        printf("\t\t\t=                                                               =\n");
        printf("\t\t\t=================================================================\n\n");
        printf("\t\t\t=================\t=================\t=================\n");
        printf("\t\t\t=     Basic     =\t=    Standard   =\t=    Premium    =\n");
        printf("\t\t\t=================\t=================\t=================\n");
        printf("\t\t\t=               =\t=               =\t=               =\n");
        printf("\t\t\t=     3 Days    =\t=    1 Month    =\t=    1 Year     =\n");
        printf("\t\t\t=               =\t=               =\t=               =\n");
        printf("\t\t\t=     $0.00     =\t=    $ 9.99     =\t=    $ 99.99    =\n");
        printf("\t\t\t=               =\t=               =\t=               =\n");
        printf("\t\t\t=================\t=================\t=================\n");
        printf("\t\t\t=               =\t=               =\t=               =\n");
        printf("\t\t\t=     Enter 1   =\t=    Enter 2    =\t=    Enter 3    =\n");
        printf("\t\t\t=               =\t=               =\t=               =\n");
        printf("\t\t\t=================\t=================\t=================\n\n");
        printf("\t\t\t=================================================================\n");
        printf("\t\t\t");
        int plan;
        scanf("%d",&plan);
        printf("\t\t\t=================================================================\n");
        if(plan == 1)
        {
            char planname[]="Basic";
            int days = 3;
            admin_basic_add_user(planname,days);
        }
        else if(plan == 2)
        {
            char planname[]="Standard";
            int days = 30;
            admin_add_user(planname,days);
        }
        else if(plan == 3)
        {
            char planname[]="Premium";
            int days = 365;
            admin_add_user(planname,days);
        }
        system("cls");
        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
    }
    else if(user_information == 5)
    {

        char delete_user_name[30],temp_delete_user[30],folder[]="Users List/";;
        strcpy(user_name,""); // clearing string ;
        strcpy(password,"");// clearing string ;

        printf("\t\t\t\tUser name for delete: ");
        getchar();
        gets(delete_user_name);
        strcpy(temp_delete_user,delete_user_name);
        strcat(delete_user_name,".txt");
        strcat(folder,delete_user_name);
        int del = remove(folder);
        if (!del)
        {
            SetColor(2);
            printf("\n\t\t\t\tUser Deleted successfully\n\t\t\t\t");
            SetColor(15);
            gets(back_button);
            system("cls");

            //--------------for loading animation---------------
            int j,i;
            //--------------for loading animation---------------
            gotoxy(46,10);
            printf("Loading...");
            gotoxy(46,12);
            for(i=1; i <= 20 ; i++)
            {
                for(j=0; j<=30000000 ; j++);
                printf("%c",177);
            }
            system("cls");
            printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
            admin_login_part2();
        }

        else
        {
            SetColor(4);
            printf("\n\t\t\t\tUser  not available !\n\t\t\t\t");
            SetColor(15);
            gets(back_button);
            system("cls");

            //--------------for loading animation---------------
            int j,i;
            //--------------for loading animation---------------
            gotoxy(46,10);
            printf("Loading...");
            gotoxy(46,12);
            for(i=1; i <= 20 ; i++)
            {
                for(j=0; j<=30000000 ; j++);
                printf("%c",177);
            }
            system("cls");
            printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
            admin_login_part2();
        }
    }

    else
    {
        gets(back_button);
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
    }
}
//--------------------------------------------end of users information function-----------------------------------------------------------------------


//----------------------------------------add ambulance function start ------------------------------------------------------------------------------------
void add_ambulace()
{
    char folder[]="Ambulance List/";
    printf("\t\t\t\tAmbulance Name = ");
    getchar();
    gets( ambulance_name);
    strcpy(temp,ambulance_name);
    strcat(ambulance_name,".txt");
    strcat(folder,ambulance_name);
    reg_info = fopen("ambulance_name_list.txt","a");
    admin_file = fopen(folder,"a");
    if(admin_file == NULL)
    {
        printf("\t\t\tFile does not exist !!\n");
    }
    else
    {

        printf("\t\t\t\tLicence Number = ");
        gets(licence_number);

        printf("\t\t\t\tDriver Name: ");
        gets(driver_name);

        printf("\t\t\t\tDriver age: ");
        scanf("%d",&driver_age);
        getchar();
        printf("\t\t\t\tDriving Licence Number = ");
        gets(driviing_licence_number);

        printf("\t\t\t\tContact Number = ");
        getchar();
        scanf("%s",&ambulance_ph);
        printf("\t\t\t\t---------------------------------------------\n");
        printf("\t\t\t\tAmbulance Added Successfully !\n");

        fprintf(admin_file,"%s\n",temp);
        fprintf(reg_info,"%s\n",temp);
        fprintf(reg_info,"-----------------------------------------------------\n");
        fprintf(admin_file,"%s\n",licence_number);
        fprintf(admin_file, "%s\n",driver_name);
        fprintf(admin_file,"%d\n",driver_age);
        fprintf(admin_file,"%s\n",driviing_licence_number);
        fprintf(admin_file,"%s\n",ambulance_ph);
        fprintf(admin_file,"-----------------------------------------------------\n\n");
    }
    fclose(reg_info);
    fclose(admin_file);
    getchar();
    printf("\t\t\t\t");
    getchar();
    system("cls");

    //--------------for loading animation---------------
    int j,i;
    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=30000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
    admin_login_part2();
}
//----------------------------------------end of add ambulance function ------------------------------------------------------------------------------------


//---------------------------------------ambulance list function start----------------------------------------------------------------------------------
void ambulance_list()
{
    reg_info = fopen("ambulance_name_list.txt","r");
    char abc[100];
    printf("\t\t\t\tAmbulance Name\n");
    printf("\t\t\t\t------------------------------------------\n");
    while(fgets(abc,sizeof(abc),reg_info) != NULL)
    {
        fputs("\t\t\t\t",stdout);
        fputs(abc,stdout);
    }
    fclose(reg_info);
    printf("\t\t\t\t");
    getchar();
    getchar();
    system("cls");

    //--------------for loading animation---------------
    int j,i;
    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=30000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
    admin_login_part2();
}
//---------------------------------------end of ambulance list function----------------------------------------------------------------------------------


//----------------------------------------add hospital function start -----------------------------------------------------------------------------------------------
void add_hospital()
{
    char folder[]="Hospital List/";
    printf("\t\t\t\tHospital Name = ");
    getchar();
    gets( hoospital_name);

    strcpy(temp,hoospital_name);
    strcat(hoospital_name,".txt");
    strcat(folder,hoospital_name);
    reg_info = fopen("hospital_name_list.txt","a");
    admin_file = fopen(folder,"a");
    if(admin_file == NULL)
    {
        printf("\t\t\tFile does not exist !!\n");
    }
    else
    {

        printf("\t\t\t\tHospital Location = ");
        gets(hospital_location);

        printf("\t\t\t\tNumber of Doctors = ");
        gets(number_of_doctors);

        printf("\t\t\t\tProvide Service List = ");
        gets(Provide_Service_List);

        printf("\t\t\t\tContact Number = ");
        getchar();
        scanf("%s",&hospital_ph);
        printf("\t\t\t\t---------------------------------------------\n");
        printf("\t\t\t\tHospital Added Successfully !\n");

        fprintf(admin_file,"%s\n",temp);
        fprintf(reg_info,"%s\n",temp);
        fprintf(reg_info,"-----------------------------------------------------\n");
        fprintf(admin_file,"%s\n",hospital_location);
        fprintf(admin_file, "%s\n",number_of_doctors);
        fprintf(admin_file,"%s\n",Provide_Service_List);
        fprintf(admin_file,"%s\n",hospital_ph);
        fprintf(admin_file,"-----------------------------------------------------\n\n");
    }
    fclose(reg_info);
    fclose(admin_file);
    printf("\t\t\t\t");
    getchar();
    system("cls");

    //--------------for loading animation---------------
    int j,i;
    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=30000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
    admin_login_part2();
}
//----------------------------------------end of add hospital function-----------------------------------------------------------------------------------------------

//----------------------------------------hospital list function start -----------------------------------------------------------------------------------------------
void hospital_list()
{
    reg_info = fopen("hospital_name_list.txt","r");
    char abc[100];
    printf("\t\t\t\tHospital Name\n");
    printf("\t\t\t\t------------------------------------------\n");
    while(fgets(abc,sizeof(abc),reg_info) != NULL)
    {
        fputs("\t\t\t\t",stdout);
        fputs(abc,stdout);
    }
    fclose(reg_info);
    printf("\t\t\t\t");
    getchar();
    getchar();
    system("cls");

    //--------------for loading animation---------------
    int j,i;
    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=30000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
    admin_login_part2();
}
//----------------------------------------end of hospital list function-----------------------------------------------------------------------------------------------


//--------------------------------------admin ambulance function start--------------------------------------------------------------------------------
void admin_ambulance()
{
    int admin_ambulance;
    printf("\t\t\t\t1. Ambulance list \n");
    printf("\t\t\t\t2. Ambulance Details \n");
    printf("\t\t\t\t3. Add Ambulance \n");
    printf("\t\t\t\t4. Delete Ambulance\n");
    printf("\t\t\t\t------------------------------------------\n\t\t\t\t");
    scanf("%d",&admin_ambulance);
    printf("\t\t\t\t------------------------------------------\n");
    if(admin_ambulance == 1)
    {
        ambulance_list();
    }
    else if(admin_ambulance == 2)
    {
        char ambulance_details[30],folder[]="Ambulance List/";
        printf("\t\t\t\tDetails info. for: ");
        getchar();
        gets(ambulance_details);
        strcat(ambulance_details,".txt");
        strcat(folder,ambulance_details);
        admin_file = fopen(folder,"r");
        if(admin_file == NULL)
        {
            printf("\t\t\t\tAmbulance not found ! \n");
        }
        else
        {
            fscanf(admin_file,"%[^\n]%*c  %[^\n]%*c %[^\n]%*c %d %[^\n]%*c",&ambulance_name,&licence_number,&driver_name,&driver_age,&driviing_licence_number);
            printf("\t\t\t\tAmbulance Name =%s\n",ambulance_name);
            printf("\t\t\t\tLicence Number =%s\n",licence_number);
            printf("\t\t\t\tDriver Name: %s\n",driver_name);
            printf("\t\t\t\tDriver age: %d\n",driver_age);
            printf("\t\t\t\tDriving Licence Number = %s\n",driviing_licence_number);

        }
        fclose(admin_file);
        printf("\t\t\t\t\t");
        getchar();
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
    }
    else if(admin_ambulance == 3)
    {
        add_ambulace();
    }
    else if(admin_ambulance == 4)
    {
        char delete_ambulance_name[30],folder[]="Ambulance List/";;
        printf("\t\t\t\tAmbulance name for delete: ");
        getchar();
        gets(delete_ambulance_name);
        strcat(delete_ambulance_name,".txt");
        strcat(folder,delete_ambulance_name);
        int del = remove(folder);
        if (!del)
        {
            printf("\t\t\t\tAmbulance Deleted successfully\n");
        }

        else
        {
            printf("\t\t\t\tWe can not find this Ambulance name !\n");
        }
        printf("\t\t\t\t");
        getchar();
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
    }
    else
    {
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
    }
}
//--------------------------------------end of admin ambulance function-------------------------------------------------------------------------------


//--------------------------------------admin ambulance function start -------------------------------------------------------------------------------
void admin_hospital()
{
    int admin_hospital;
    printf("\t\t\t\t1. Hospital list \n");
    printf("\t\t\t\t2. Hospital Details\n");
    printf("\t\t\t\t3. Add Hospital \n");
    printf("\t\t\t\t4. Delete Hospital\n");
    printf("\t\t\t\t------------------------------------------\n\t\t\t\t");
    scanf("%d",&admin_hospital);
    printf("\t\t\t\t------------------------------------------\n");
    if(admin_hospital == 1)
    {
        hospital_list();
    }
    else if(admin_hospital == 2)
    {
        char hospital_details[30],folder[]="Hospital List/";
        printf("\t\t\t\tDetails info. for: ");
        getchar();
        gets(hospital_details);
        strcat(hospital_details,".txt");
        strcat(folder,hospital_details);
        admin_file = fopen(folder,"r");
        if(admin_file == NULL)
        {
            printf("\t\t\t\tHospital not found ! \n");
        }
        else
        {
            fscanf(admin_file,"%[^\n]%*c  %[^\n]%*c %[^\n]%*c %[^\n]%*c %[^\n]%*c",&hoospital_name,&hospital_location,&number_of_doctors,&Provide_Service_List,&hospital_ph);
            printf("\t\t\t\tHospital Name = %s\n",hoospital_name);
            printf("\t\t\t\tHospital Location = %s\n",hospital_location);
            printf("\t\t\t\tNumber of Doctors = %s\n",number_of_doctors);
            printf("\t\t\t\tProvide Service List = %s\n",Provide_Service_List);
            printf("\t\t\t\tContact Number = %s\n",hospital_ph);

        }
        fclose(admin_file);
        printf("\t\t\t\t\t");
        getchar();
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
    }
    else if(admin_hospital == 3)
    {
        add_hospital();
    }
    else if(admin_hospital == 4)
    {
        char delete_hospital_name[30],folder[]="Hospital List/";;
        strcpy(user_name,""); // clearing string ;
        strcpy(password,"");// clearing string ;

        printf("\t\t\t\tHospital name for delete: ");
        getchar();
        gets(delete_hospital_name);
        strcat(delete_hospital_name,".txt");
        strcat(folder,delete_hospital_name);
        int del = remove(folder);
        if (!del)
        {
            printf("\t\t\t\tHospital Deleted successfully\n\t\t\t\t");
            getchar();
            system("cls");

            //--------------for loading animation---------------
            int j,i;
            //--------------for loading animation---------------
            gotoxy(46,10);
            printf("Loading...");
            gotoxy(46,12);
            for(i=1; i <= 20 ; i++)
            {
                for(j=0; j<=30000000 ; j++);
                printf("%c",177);
            }
            system("cls");
            printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
            admin_login_part2();
        }

        else
        {
            printf("\t\t\t\tWe can not find this Hospital name !\n\t\t\t\t");
            getchar();
            system("cls");

            //--------------for loading animation---------------
            int j,i;
            //--------------for loading animation---------------
            gotoxy(46,10);
            printf("Loading...");
            gotoxy(46,12);
            for(i=1; i <= 20 ; i++)
            {
                for(j=0; j<=30000000 ; j++);
                printf("%c",177);
            }
            system("cls");
            printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
            admin_login_part2();
        }
    }
    else
    {
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
    }
}
//--------------------------------------end of admin Hospital function-------------------------------------------------------------------------------


//-------------------------------------------nurse list function start-------------------------------------------------------------------------------------------------------
void nurse_list()
{
    admin_file = fopen("Nurse_list.txt","r");
    char abc[100];
    printf("\t\t\t\tUser name\tPassword\n");
    printf("\t\t\t\t------------------------------------------\n");
    while(fgets(abc,sizeof(abc),admin_file) != NULL)
    {
        fputs("\t\t\t\t",stdout);
        fputs(abc,stdout);
    }
    fclose(admin_file);
    printf("\t\t\t\t");
    getchar();
    gets(back_button);;
    system("cls");

    //--------------for loading animation---------------
    int j,i;
    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=30000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
    admin_login_part2();
}
//-------------------------------------------end of nurse list function-------------------------------------------------------------------------------------------------------


//----------------------------------------admin nurse function start-----------------------------------------------------------------------------------------------------
void admin_nurse()
{
    char nurse_user_name[30], nurse_password[30], nurse_temp[30], nurse_working_exp[100], nurse_ph_num[15], nurse_hospital_name[100];
    int nurse_option,nurse_age;
    printf("\t\t\t\t1. Nurse list \n");
    printf("\t\t\t\t2. Nurse Details \n");
    printf("\t\t\t\t3. Add Nurse \n");
    printf("\t\t\t\t4. Remove Nurse\n");
    printf("\t\t\t\t------------------------------------------\n\t\t\t\t");
    scanf("%d",&nurse_option);
    printf("\t\t\t\t------------------------------------------\n");
    if(nurse_option == 1)
    {
        nurse_list();
    }
    else if(nurse_option == 2)
    {
        char nurse_details[30],folder[]="Nurse/";;
        printf("\t\t\t\tDetails info. for : ");
        getchar();
        gets(nurse_details);
        printf("\n");
        strcat(nurse_details,".txt");
        strcat(folder,nurse_details);
        reg_info = fopen(folder,"r");
        if(reg_info == NULL)
        {
            printf("\t\t\t\tNurse not found ! \n");
        }
        else
        {
            fscanf(reg_info, "%[^\n]%*c %[^\n]%*c %d %[^\n]%*c %[^\n]%*c %[^\n]%*c",&nurse_user_name,&nurse_password,&nurse_age,&nurse_hospital_name,&nurse_working_exp,&nurse_ph_num);

            printf("\t\t\t\t\tUser name : %s\n", nurse_user_name);

            printf("\t\t\t\t\tPassword : %s\n", nurse_password);

            printf("\t\t\t\t\tAge : %d\n",nurse_age);

            printf("\t\t\t\t\tWorking Experience : %s\n",nurse_working_exp);

            printf("\t\t\t\t\tPhone Number : %s\n", nurse_ph_num);

        }
        printf("\t\t\t\t\t");
        getchar();
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
        fclose(reg_info);

    }
    else if(nurse_option == 3)
    {
        char folder[]="Nurse/";
        printf("\t\t\t\tUser name : ");
        getchar();
        gets(nurse_user_name);
        strcpy(nurse_temp,nurse_user_name);
        strcat(nurse_user_name,".txt");
        strcat(folder,nurse_user_name);
        reg_info = fopen(folder,"w");
        admin_file = fopen("Nurse_list.txt","a");
        if(reg_info == NULL)
        {
            printf("File does not exist !!\n");
        }
        else
        {
            printf("\t\t\t\tPassword : ");
            gets(nurse_password);

            printf("\t\t\t\tEnter your age:");
            scanf("%d",&nurse_age);

            printf("\t\t\t\tHospital Name: ");
            getchar();
            gets(nurse_hospital_name);

            printf("\t\t\t\tWorking Experience : ");
            getchar();
            gets(nurse_working_exp);

            printf("\t\t\t\tContact Number = ");
            getchar();
            gets(nurse_ph_num);
            printf("\t\t\t\t---------------------------------------------\n");

            fprintf(reg_info,"%s\n",nurse_temp);
            fprintf(admin_file,"%s\t\t",nurse_temp);
            fprintf(reg_info,"%s\n",nurse_password);
            fprintf(admin_file,"%s\n",nurse_password);
            fprintf(admin_file,"-----------------------------------------------------\n");
            fprintf(reg_info,"%d\n",nurse_age);
            fprintf(reg_info,"%s\n",nurse_hospital_name);
            fprintf(reg_info, "%s\n",nurse_working_exp);
            fprintf(reg_info,"%s\n",nurse_ph_num);
        }
        fclose(reg_info);
        fclose(admin_file);
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
    }
    else if(nurse_option == 4)
    {

        char delete_nurse_name[30],temp_delete_user[30],folder[]="Nurse/";;
        printf("\t\t\t\tNurse name for remove: ");
        getchar();
        gets(delete_nurse_name);
        strcpy(temp_delete_user,delete_nurse_name);
        strcat(delete_nurse_name,".txt");
        strcat(folder,delete_nurse_name);
        int del = remove(folder);
        if (!del)
        {
            printf("\t\t\t\tNurse remove successfully\n");
            printf("\t\t\t\t");
            gets(back_button);
            system("cls");

            //--------------for loading animation---------------
            int j,i;
            //--------------for loading animation---------------
            gotoxy(46,10);
            printf("Loading...");
            gotoxy(46,12);
            for(i=1; i <= 20 ; i++)
            {
                for(j=0; j<=30000000 ; j++);
                printf("%c",177);
            }
            system("cls");
            printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
            admin_login_part2();
        }

        else
        {
            printf("\t\t\t\tNurse is not available !\n");
            printf("\t\t\t\t");
            gets(back_button);
            system("cls");

            //--------------for loading animation---------------
            int j,i;
            //--------------for loading animation---------------
            gotoxy(46,10);
            printf("Loading...");
            gotoxy(46,12);
            for(i=1; i <= 20 ; i++)
            {
                for(j=0; j<=30000000 ; j++);
                printf("%c",177);
            }
            system("cls");
            printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
            admin_login_part2();
        }
    }

    else
    {
        gets(back_button);
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
    }
}
//----------------------------------------------  end of admin nurse function -----------------------------------------------------------------------------------


//----------------------------------------admin login part 2 function start--------------------------------------------------------------------------
void admin_login_part2()
{
    int admin_menu;
    printf("\t\t\t-----------------------------------------\n");
    printf("\t\t\t1. Account Approval \n");
    printf("\t\t\t2. Users info.\n");
    printf("\t\t\t3. Nurse.\n");
    printf("\t\t\t4. Ambulance\n");
    printf("\t\t\t5. Hospital\n");
    printf("\t\t\t6. Profile\n");
    printf("\t\t\t-----------------------------------------\n\t\t\t");
    scanf("%d",&admin_menu);
    printf("\t\t\t-----------------------------------------\n");
    if(admin_menu == 1)
    {
        payment = fopen("payment.txt","r");
        char abc[100];
        while(fgets(abc,sizeof(abc),payment) != NULL)
        {
            fputs("\t\t\t",stdout);
            fputs(abc,stdout);
        }
        fclose(payment);

        int ret,num_of_ac,clear_list;
        char oldname[30] ;

        char oldname_cpy[30]="a";
        printf("\t\t\tNumber of Account for Approval: ");
        scanf("%d",&num_of_ac);
        printf("\t\t\t----------------------------------------\n");
        for(int i=1; i<=num_of_ac; i++)
        {
            char folder[]="Users List/a_", folder_copy[30];
            char folder1[]="Users List/";
            printf("\t\t\tUser Name for Approval:");
            scanf("%s",&oldname);
            printf("\t\t\t----------------------------------------\n");
            strcat(oldname,".txt");
            strcpy(oldname_cpy,oldname);
            strcat(folder1,oldname_cpy);
            strcat(folder,oldname);
            ret = rename(folder, folder1);
            if(ret == 0)
            {
                SetColor(2);
                printf("\t\t\tUser Approved Successfully !!\n");
                SetColor(15);
                printf("\t\t\t--------------------------------------\n");
                strcpy(folder1,"");
                strcpy(folder,"");

            }
            else
            {
                SetColor(4);
                printf("\t\t\tWe can not find this user for Approval !!\n");
                SetColor(15);
                printf("\t\t\t-------------------------------------------\n");
                strcpy(folder1,"");
                strcpy(folder,"");
            }
        }
        printf("\t\t\tClear approval list ??\n");
        printf("\t\t\t1. Yes\t2.No\n");
        printf("\t\t\t------------------------\n\t\t\t");
        scanf("%d",&clear_list);
        printf("\t\t\t------------------------\n");
        if(clear_list == 1)
        {
            printf("\t\t\tApproval List Cleared Successfully !!\n");
            payment = fopen("payment.txt","w");
            fclose(payment);
        }
        else if(clear_list == 2)
        {
            goto next;
        }
        else
        {
            goto next;
        }
next:
        printf("\n\t\t\tPress Enter for Main Menu !\n\t\t\t");
        getchar();
        gets(back_button);
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
    }
    else if(admin_menu == 2)
    {
        user_information();
    }
    else if(admin_menu == 3)
    {
        admin_nurse();
    }
    else if(admin_menu == 4)
    {
        admin_ambulance();
    }
    else if(admin_menu == 5)
    {
        admin_hospital();
    }
    else if(admin_menu == 6)
    {
        admin_profile();
    }
    else
    {
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
    }
}
//----------------------------------------end of admin login part 2 function--------------------------------------------------------------------------


//-----------------------------------------admin login function start-------------------------------------------------------------------------------
void admin_login()
{
    int cmp_result1,cmp_result2,ch='a',k=0;
    char admin_log_password[20]="a", admin_log_username[20];
    admin_file = fopen("admin_info.txt","r");
    fscanf(admin_file, "%s %s %s %d %s %s",&admin_user_name,&admin_password,&admin_email,&admin_age,&admin_gender,&admin_ph);
    printf("\t\t\tUsername:");
    scanf("%s",&admin_log_username);
    getchar();
    printf("\t\t\tPassword:");

    //--------for password hiding----------------
    while(1)
    {
        ch = getch();
        if(ch == ENTER)
        {
            break;
        }
        else if(ch == BKSP)
        {
            k--;
            printf("\b \b");
        }
        else if(ch == TAB || ch == SPACE)
        {
            continue;
        }
        else
        {
            admin_log_password[k] = ch;
            k++;
            printf("*");
        }
    }

//---------------end of password hiding---------------------

    cmp_result1 = strcmp(admin_user_name, admin_log_username);
    cmp_result2 = strcmp(admin_password,admin_log_password);
    //----------------password checking --------------------------------
    if(cmp_result1 == 0 && cmp_result2 == 0)
    {
        printf("\n\t\t\t-----------------------------------------\n");
        SetColor(2);
        printf("\t\t\tLogin successfully !!!\n");
        SetColor(15);
        admin_login_part2();
    }

    else if(cmp_result1 != 0 && cmp_result2 != 0)
    {
        SetColor(4);
        printf("\n\t\t\tUsername & Password incorrect !!!\n");
        SetColor(15);
        printf("\t\t\t");
        gets(back_button);
        admin();
    }
    else if(cmp_result1 != 0)
    {
        SetColor(4);
        printf("\n\t\t\tUsername incorrect !!!\n");
        SetColor(15);
        printf("\t\t\t");
        gets(back_button);
        admin();
    }
    else
    {
        SetColor(4);
        printf("\n\t\t\tpassword incorrect !!!\n");
        SetColor(15);
        printf("\t\t\t");
        gets(back_button);
        admin();
    }
    fclose(admin_file);
}
//----------------------------end of admin login function---------------------------------------------------------------------------------------------------------------


//------------------------------------admin profile function start -------------------------------------------------------------------------------------------------------
void admin_profile()
{
    int profile_number;
    printf("\t\t\t\t1. View Profile \n");
    printf("\t\t\t\t2. Update Profile \n");
    printf("\t\t\t\t3. Log out \n");
    printf("\t\t\t\t4. Delete Account \n");
    printf("\t\t\t\t------------------------------------------\n\t\t\t\t");
    scanf("%d",&profile_number);
    printf("\t\t\t\t------------------------------------------\n");
    if(profile_number == 1)
    {
        admin_file = fopen("admin_info.txt","r");
        if(admin_file == NULL)
        {
            printf("\t\t\tFile does not exist !!\n");
        }
        else
        {
            fscanf(admin_file, "%s", &admin_user_name);
            printf("\t\t\t\t\tUser name =  %s\n", admin_user_name);

            fscanf(admin_file, "%s",&admin_password);
            printf("\t\t\t\t\tPassword = %s\n", admin_password);

            fscanf(admin_file,"%s",&admin_email);
            printf("\t\t\t\t\temail = %s\n",admin_email);

            fscanf(admin_file, "%d", &admin_age);
            printf("\t\t\t\t\tAge = %d\n",admin_age);

            fscanf(admin_file, "%s", &admin_gender);
            printf("\t\t\t\t\tGender = %s\n", admin_gender);

            fscanf(admin_file, "%s", &admin_ph);
            printf("\t\t\t\t\tPhone = %s\n", admin_ph);
        }
        fclose(admin_file);
        printf("\t\t\t\t\t");
        getchar();
        gets(back_button);
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
    }
    else if(profile_number == 2 )
    {
        admin_update_profile();
    }
    else if(profile_number == 3)
    {
        system("cls");
        main();
    }
    else if(profile_number == 4)
    {
        int profile_delete;
        printf("\t\t\t\tAre you sure ?\n");
        printf("\t\t\t\t1. Yes \t2.No\n");
        printf("\t\t\t\t------------------------------------------\n\t\t\t\t");
        scanf("%d",&profile_delete);
        if(profile_delete == 1)
        {
            strcpy(admin_user_name,""); // clearing string ;
            strcpy(admin_password,"");// clearing string ;
            admin_file = fopen("admin_info.txt","w"); // delete old txt file and create new one;
            fclose(admin_file);
            remove("admin_info.txt");
            system("cls");
            main();
        }
        else if(profile_delete == 2)
        {
            system("cls");
            int j,i;
            //--------------for loading animation---------------
            gotoxy(46,10);
            printf("Loading...");
            gotoxy(46,12);
            for(i=1; i <= 20 ; i++)
            {
                for(j=0; j<=30000000 ; j++);
                printf("%c",177);
            }
            system("cls");
            printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
            admin_login_part2();
        }
    }
    else
    {
        system("cls");

        //--------------for loading animation---------------
        int j,i;
        //--------------for loading animation---------------
        gotoxy(46,10);
        printf("Loading...");
        gotoxy(46,12);
        for(i=1; i <= 20 ; i++)
        {
            for(j=0; j<=30000000 ; j++);
            printf("%c",177);
        }
        system("cls");
        printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
        admin_login_part2();
    }

}
//--------------------------------------end of admin profile function ---------------------------------------------------------------------------


//----------------------------------admin panel start------------------------------------------------------------------------------------------------
void admin()
{
    int admin_number,i,j;
    system("cls");
    //--------------for loading animation---------------
    gotoxy(46,10);
    printf("Loading...");
    gotoxy(46,12);
    for(i=1; i <= 20 ; i++)
    {
        for(j=0; j<=32000000 ; j++);
        printf("%c",177);
    }
    system("cls");
    //-----------------------end of loading animation-----------------------------------------
    printf("\n\n\t\t\t=========================\n\t\t\t=\t\t\t=\n\t\t\t=\tAdmin Panel\t= \t\t\n\t\t\t=\t\t\t=\n\t\t\t=========================\n\n\n");
    printf("\t\t\t-------------------------\n");
    printf("\t\t\t1. Sign Up\n");
    printf("\t\t\t2. Log in \n");
    printf("\t\t\t-------------------------\n\t\t\t");
    scanf("%d",&admin_number);
    printf("\t\t\t-------------------------\n");
    if(admin_number == 1)
    {
        admin_register();
    }
    else if(admin_number == 2)
    {
        admin_login();
    }
    else
    {
        system("cls");
        gets(back_button);
        admin();
    }
}




