#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

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
    
}