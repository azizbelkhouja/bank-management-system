#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

int i,j;
int main_exit;
FILE *ptr;

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

void new_acc()
{
    int choice;
    FILE *ptr;
    ptr=fopen("record.dat","a+");
    account_no :
    system("clear");
    printf("\t\t\t ADD RECORD");
    printf("\n\n\n Enter today's date (mm/dd/yyyy): ");
    scanf("%d%d%d", &add.deposit.month,&add.deposit.day, &add.deposit.year);
    printf("Enter the account number: ");
    while(fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d \n", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
    {
        if(check.acc_no==add.acc_no)
        {
            printf("Account no already in use");
            goto account_no;
        }
    }
    add.acc_no = check.acc_no;
    printf("\n Name: ");
    scanf("%s", add.name);
    printf("\n Birthday (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &add.dob.month, &add.dob.day, &add.dob.year);
    printf("\n Age: ");
    scanf("%d", &add.age);
    printf("\n Home address: ");
    scanf("%s", add.address);
    printf("\n Citizenship number: ");
    scanf("%d", &add.citizenship);
    printf("\n Phone number: ");
    scanf("%lf", &add.amt);
    printf("\n Account Type (Savings/Current/FixedN): ");
    scanf("%s", add.acc_type);

    fprintf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d \n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
    fclose(ptr);
    printf("\n Account created successfully");
    add_invalid :
    printf("Enter 1 to try again \n Enter 0 to exit");
    scanf("%d", &main_exit);
    system("clear");
    if(main_exit==1)
    {
        menu();
    }
    else if(main_exit==0)
    {
        closed();
    }
    else
    {
        printf("\n Invalid choice");
        goto add_invalid;
    }
}

void edit()
{
    int choice, test = 0;
    FILE *old, *newrec;

    old=fopen("record.dat", "w");
    newrec=fopen("new.dat", "w");

    printf("\n Account no: ");
    scanf("%d", &upd.acc_no);
    while(fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d \n", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.address, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
    {
        if (add.acc_no == upd.acc_no)
        {
            test=1;
            printf("\n Information to be changed: \n 1.Address\n 2.Phone\n Choice: ");
            scanf("%d", &choice);
            system("clear");
            if (choice == 1)
            {
                printf("Enter new address: ");
                scanf("%s", upd.address);
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d \n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, upd.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                system("clear");
                printf("Changes saved :)");
            }
            else if (choice == 2)
            {
                printf("Enter new phone number: ");
                scanf("%lf", upd.phone);
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d \n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, upd.address, add.citizenship, upd.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                system("clear");
                printf("Changes saved ;)");
            }
            else
            {
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d \n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, upd.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);

            }
        }
        fclose(old);
        fclose(newrec);
        remove("record.dat");
        rename("new.dat", "record.dat");

        if (test != 1)
        {
            system("clear");
            printf("\n record not found :(");
            edit_invalid :
            printf("Enter 0 to try again \n Enter 1 for menu \n Enter 2 to exit");
            scanf("%d", &main_exit);
            system("clear");
            if (main_exit==0)
            {
                edit();
            }
            else if(main_exit==1)
            {
                menu();
            }
            else if(main_exit==2)
            {
                closed();
            }
            else
            {
                printf("\n Invalid choice");
                goto edit_invalid;
            }
        }
        else 
        {
            printf("Enter 1 for menu \n Enter 0 to exit");
            scanf("%d", &main_exit);
            system("clear");
            if(main_exit==1)
            {
                menu();
            }
            else
            {
                closed();
            }
        }
    }
}



