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
    int choice;
    printf("\033c");
    system("clear");
    printf("\n");
    printf("\n\n\t\t\t CUSTOMER ACCOUNT BANKING MANAGEMENT");
    printf("\n\n\n\t\t MAIN MENU");
    printf("\n\n\t\t 1. Create new account \n\t 2. Update information of existing account \n\t 3. Transactions \n\t 4. Account details \n\t 5. Delete account \n\t 6. Customer's list \n\t 7. Exit \n\n\n\n\t\t Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1: new_acc();
        break;
        case 2: edit();
        break;
        case 3: transact();
        break;
        case 4: see();
        break;
        case 5: erase();
        break;
        case 6: view_list();
        break;
        case 7: closed();
        break;
    }
}

void fordelay(int j)
{
    while (sec<j)
    {
        if (clock()>stopclock)
        {
            stopclock +=1000000;
            printf(".");
            fflush(stdout);
            sec++;
        }
    }
}