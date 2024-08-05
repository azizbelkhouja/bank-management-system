#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main_exit;
FILE *ptr;

void closed();
void menu();
void new_acc();
void edit();
void transact();
void see();
void erase();
void view_list();

struct date {
    int day, month, year;
};

struct {
    char name[60], address[60], citizenship[15], acc_type[10];
    int acc_no, age;
    double phone;
    float amt;
    struct date dob;
    struct date deposit;
} add, upd, check, rem, transaction;

unsigned int sec = 0;

int main() {
    char pass[15], password[15] = "admin";
    printf("Enter password to login: ");
    printf("\033[8m");
    scanf("%s", pass);
    printf("\033c");

    if (strcmp(pass, password) == 0) {
        menu();
    } else {
        printf("\033c");
        printf("Wrong Password\n");
        printf("Enter 1 to try again\nEnter 0 to exit\nChoice:  ");
        scanf("%d", &main_exit);

        if (main_exit == 1) {
            system("cls");
            main();
        } else if (main_exit == 0) {
            closed();
        }
    }

    return 0;
}

void menu() {
    int choice;
    
    system("cls");

    printf("\n********** Bank Management System **********\n");
    printf("1. Create Account\n");
    printf("2. Edit Account\n");
    printf("3. Transactions\n");
    printf("4. View Account\n");
    printf("5. Delete Account\n");
    printf("6. View All Accounts\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: new_acc(); break;
        case 2: edit(); break;
        case 3: transact(); break;
        case 4: see(); break;
        case 5: erase(); break;
        case 6: view_list(); break;
        case 7: closed(); break;
        default: 
            printf("Invalid choice\n");
            menu();
            break;
    }
}

void new_acc() {
    int choice;
    FILE *ptr = fopen("record.dat", "a+");
    if (!ptr) {
        perror("Unable to open file");
        return;
    }

    system("cls");

    printf("\n********** New Account **********\n");
    printf("Enter today's date (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &add.deposit.month, &add.deposit.day, &add.deposit.year);

    printf("Enter the account number: ");
    scanf("%d", &check.acc_no);

    while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", 
                   &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                   &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                   &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if (check.acc_no == add.acc_no) {
            printf("Account number already in use\n");
            fclose(ptr);
            new_acc();
            return;
        }
    }

    add.acc_no = check.acc_no;
    printf("Name: ");
    scanf("%s", add.name);
    printf("Birthday (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &add.dob.month, &add.dob.day, &add.dob.year);
    printf("Age: ");
    scanf("%d", &add.age);
    printf("Home address: ");
    scanf("%s", add.address);
    printf("Citizenship number: ");
    scanf("%s", add.citizenship);
    printf("Phone number: ");
    scanf("%lf", &add.phone);
    printf("Account Type (Savings/Current/FixedN): ");
    scanf("%s", add.acc_type);

    fprintf(ptr, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
            add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
            add.age, add.address, add.citizenship, add.phone, add.acc_type, 
            add.amt, add.deposit.month, add.deposit.day, add.deposit.year);

    fclose(ptr);
    printf("\nAccount created successfully\n");

    printf("\nEnter 1 to try again\nEnter 0 to exit\nChoice: ");
    scanf("%d", &main_exit);
    
    if (main_exit == 1) {
        new_acc();
    } else if (main_exit == 0) {
        closed();
    } else {
        printf("Invalid choice\n");
        new_acc();
    }
}

void edit() {
    int choice, test = 0;
    FILE *old = fopen("record.dat", "r");
    FILE *newrec = fopen("new.dat", "w");
    if (!old || !newrec) {
        perror("Unable to open file");
        return;
    }

    system("cls");

    printf("Account no: ");
    scanf("%d", &upd.acc_no);

    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                  &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                  &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                  &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if (add.acc_no == upd.acc_no) {
            test = 1;
            printf("\nChange: \n 1.Address\n 2.Phone\nChoice: ");
            scanf("%d", &choice);
            
            if (choice == 1) {
                system("cls");
                printf("Enter new address: ");
                scanf("%s", upd.address);
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                        add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                        add.age, upd.address, add.citizenship, add.phone, add.acc_type, 
                        add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                
                printf("Changes saved :)\n");
            } else if (choice == 2) {
                system("cls");
                printf("Enter new phone number: ");
                scanf("%lf", &upd.phone);
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                        add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                        add.age, add.address, add.citizenship, upd.phone, add.acc_type,
                        add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                
                printf("Changes saved ;)\n");
            } else {
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                        add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                        add.age, add.address, add.citizenship, add.phone, add.acc_type, 
                        add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
            }
        } else {
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                    add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                    add.age, add.address, add.citizenship, add.phone, add.acc_type,
                    add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");

    if (test != 1) {
        
        printf("\nRecord not found :(\n");
        printf("\nEnter 0 to try again \nEnter 1 for menu \nEnter 2 to exit\nChoice: ");
        scanf("%d", &main_exit);
        if (main_exit == 0) {
            edit();
        } else if (main_exit == 1) {
            menu();
        } else if (main_exit == 2) {
            closed();
        }
    } else {
        printf("\nEnter 1 to continue editing \nEnter 0 for menu\nChoice: ");
        scanf("%d", &main_exit);
        if (main_exit == 1) {
            edit();
        } else if (main_exit == 0) {
            menu();
        }
    }
}

void transact() {
    int choice, test = 0;
    FILE *old = fopen("record.dat", "r");
    FILE *newrec = fopen("new.dat", "w");
    if (!old || !newrec) {
        perror("Unable to open file");
        return;
    }

    printf("\nAccount no: ");
    scanf("%d", &transaction.acc_no);

    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                  &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                  &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                  &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if (add.acc_no == transaction.acc_no) {
            test = 1;
            printf("\nChoose:\n 1. Deposit\n 2. Withdraw\n");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Enter amount to deposit: ");
                scanf("%f", &transaction.amt);
                add.amt += transaction.amt;
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                        add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                        add.age, add.address, add.citizenship, add.phone, add.acc_type,
                        add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                printf("Amount deposited successfully\n");
            } else if (choice == 2) {
                printf("Enter amount to withdraw: ");
                scanf("%f", &transaction.amt);
                if (transaction.amt > add.amt) {
                    printf("Insufficient balance\n");
                } else {
                    add.amt -= transaction.amt;
                    fprintf(newrec, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                            add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                            add.age, add.address, add.citizenship, add.phone, add.acc_type,
                            add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                    printf("Amount withdrawn successfully\n");
                }
            } else {
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                        add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                        add.age, add.address, add.citizenship, add.phone, add.acc_type,
                        add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
            }
        } else {
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                    add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                    add.age, add.address, add.citizenship, add.phone, add.acc_type,
                    add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");

    if (test != 1) {
        
        printf("Account number not found :(\n");
        printf("Enter 0 to try again \nEnter 1 for menu \nEnter 2 to exit: ");
        scanf("%d", &main_exit);
        if (main_exit == 0) {
            transact();
        } else if (main_exit == 1) {
            menu();
        } else if (main_exit == 2) {
            closed();
        }
    } else {
        printf("Enter 1 to continue transactions \nEnter 0 for menu: ");
        scanf("%d", &main_exit);
        if (main_exit == 1) {
            transact();
        } else if (main_exit == 0) {
            menu();
        }
    }
}

void see() {
    int test = 0;
    FILE *ptr = fopen("record.dat", "r");
    if (!ptr) {
        perror("Unable to open file");
        return;
    }

    printf("\n Account no: ");
    scanf("%d", &check.acc_no);

    while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                  &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                  &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                  &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if (add.acc_no == check.acc_no) {
            test = 1;
            printf("\nAccount number: %d\n", add.acc_no);
            printf("Name: %s\n", add.name);
            printf("Date of Birth: %02d/%02d/%d\n", add.dob.month, add.dob.day, add.dob.year);
            printf("Age: %d\n", add.age);
            printf("Address: %s\n", add.address);
            printf("Citizenship: %s\n", add.citizenship);
            printf("Phone: %.0lf\n", add.phone);
            printf("Account Type: %s\n", add.acc_type);
            printf("Balance: %.2f\n", add.amt);
            printf("Date of Deposit: %02d/%02d/%d\n", add.deposit.month, add.deposit.day, add.deposit.year);
            break;
        }
    }
    fclose(ptr);

    if (test != 1) {
        
        printf("Account number not found :(\n");
    }

    printf("Enter 1 to view another account \nEnter 0 for menu: ");
    scanf("%d", &main_exit);
    if (main_exit == 1) {
        see();
    } else if (main_exit == 0) {
        menu();
    }
}

void erase() {
    int test = 0;
    FILE *old = fopen("record.dat", "r");
    FILE *newrec = fopen("new.dat", "w");
    if (!old || !newrec) {
        perror("Unable to open file");
        return;
    }

    printf("\n Enter account no to delete: ");
    scanf("%d", &rem.acc_no);

    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                  &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                  &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                  &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if (add.acc_no == rem.acc_no) {
            test = 1;
            continue;
        }
        fprintf(newrec, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                add.age, add.address, add.citizenship, add.phone, add.acc_type,
                add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");

    if (test != 1) {
        
        printf("Account number not found :(\n");
        printf("Enter 0 to try again \nEnter 1 for menu \nEnter 2 to exit: ");
        scanf("%d", &main_exit);
        if (main_exit == 0) {
            erase();
        } else if (main_exit == 1) {
            menu();
        } else if (main_exit == 2) {
            closed();
        }
    } else {
        printf("Account deleted successfully\n");
        printf("Enter 1 to delete another account \nEnter 0 for menu: ");
        scanf("%d", &main_exit);
        if (main_exit == 1) {
            erase();
        } else if (main_exit == 0) {
            menu();
        }
    }
}

void view_list() {
    FILE *ptr = fopen("record.dat", "r");
    if (!ptr) {
        perror("Unable to open file");
        return;
    }

    printf("\nList of accounts:\n");
    while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                  &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                  &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                  &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        printf("Account number: %d\n", add.acc_no);
        printf("Name: %s\n", add.name);
        printf("Balance: %.2f\n", add.amt);
        printf("Date of Deposit: %02d/%02d/%d\n\n", add.deposit.month, add.deposit.day, add.deposit.year);
    }
    fclose(ptr);

    printf("Enter 0 for menu: ");
    scanf("%d", &main_exit);
    if (main_exit == 0) {
        menu();
    }
}

void closed() {
    printf("Thank you for using the Bank Management System. Goodbye!\n");
    exit(0);
}
