#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

int i,j;
int main_exit;

void closed();
void fordelay(int j);
void menu();
void new_acc();
void edit();
void transact();
void see();
void erase();
void view_list();

struct date {
    int day,month,year;
};

struct {
    char name[60], address[60], citizenship[15],acc_type[10];
    int acc_no, age;
    double phone;
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
}add, upd, check, rem, transaction;

unsigned int sec=0;
clock_t stopclock = CLOCKS_PER_SEC;

void main() 
{
    char pass[15], password[15]="admin";
    int i=0;
    printf("Enter password to login: ");
    printf("\033[8m");
    scanf("%s", pass);
    printf("\033c");

    if (strcmp(pass, password) == 0)
    {
        printf("Logged in, Loading");
        system("clear");
        fordelay(5);
        menu();
    }
    else
    {
        printf("\033c");
        printf("Wrong Password\n");
        login_try :
        printf("Enter 1 to try again \n Enter 0 to exit");
        scanf("%d", &main_exit);

        if (main_exit==1)
        {
            system("clear");
            menu();
        }
        else if (main_exit==0)
        {
            closed();
        }
    }
}

//funzioni

void menu() 
{

}