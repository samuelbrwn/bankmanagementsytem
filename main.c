/* Project: Bank Management System in C
 * 
 * Author: Samuel Brown
 *
 * Date: 3/7/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

/*Global Declaration of the user struct*/
struct user
{
    int acc_number;
    char fname[20], lname[20], password[8];
    char email[30];
    int balance;
};


/*PROTOTYPES*/
void welcome_screen();
void login();
int new_user(void);
void view_account(void);
int check_acc_number(int x);
void divider();
void print_spaces(int x);
void print_walls(int x);
/*PROTOTYPES*/

/*
 * This function creates a new user and then writes
 * this user to a dat file in binary.
 */
int new_user(void) {
    char pass[20];
    int next = 0;
    struct user new_user;
    new_user.balance = 0;
    new_user.acc_number = rand()%10000+1;
    int alternate_acc_number = check_acc_number(new_user.acc_number);

    FILE* fptr = fopen("user-records.dat", "a");
    if (fptr == NULL) return -1;

    if (alternate_acc_number != 0) new_user.acc_number = alternate_acc_number;

    system("cls");
    printf("Your user number is: %d\n", new_user.acc_number);
    divider();
    printf("\nPlease enter your First Name: ");
    scanf("%s", new_user.fname);
    printf("\n");
    divider();
    printf("\nPlease enter your Last Name: ");
    scanf("%s", new_user.lname);
    printf("\n");
    divider();
    printf("\nPlease enter your email: ");
    scanf("%s", new_user.email);
    printf("\n");
    divider();
    printf("\nPlease enter a password <must be exactly 8 characters>: ");
    scanf("%s", new_user.password);
    printf("\n");

    fwrite(&new_user, sizeof (struct user), 1, fptr);
    
    printf("Return to the Main Menu? [Press 1 then ENTER || 0 then ENTER to close software] ");
    scanf("%d", &next);

    if (next == 1) {
        fclose(fptr);
        welcome_screen();
    }

    fclose(fptr);
    return 0;
}

/*
 * This function opens the user-records.dat file, and fetches the
 * structs and prints the data.
 * 
 * I have not yet implemented the ability to search for a specific user.
 *
 * */
void view_account(void) {

    system("cls");

    struct user u;

    FILE* fptr = fopen("user-records.dat", "r");
    if (fptr == NULL) {
        fprintf(stderr, "\nERROR opening user-records.dat\n\n");
        exit(-1);
    }

    while(fread(&u, sizeof(struct user), 1, fptr))
    {
        printf("Account Number: %d\nName: %10s %10s\nUser Email Address: %20s\nYour Balance: %d\nPassword: %10s\n", u.acc_number, u.fname, u.lname, u.email, u.balance, u.password);
        divider();
        printf("\n");
    }
    fclose(fptr);
}

/*This function allows you to pull up a specific account based on the user account number*/
void login(void) {
    int account_number;
    char pass[8];
    struct user u;

    system("cls");
    FILE* fptr = fopen("user-records.dat", "r");
    if(fptr == NULL) {
        fprintf(stderr, "ERROR opening file user-records.dat\n");
        exit(-1);
    }

    printf("Please enter your unique account number: ");
    scanf("%d", &account_number);

    while(fread(&u, sizeof(struct user), 1, fptr)) {
        if(u.acc_number == account_number) {
            printf("Account Located! Please enter your password: ");
            scanf("%s", &pass);

            if (strcmp(pass, u.password) != 0) {
                printf("Password invalid. Please try again. Press ENTER to continue.");
                getch();
                fclose(fptr);
                login();
            }
            printf("%s's Account Info\n", u.fname);
            divider();
            printf("\n");
            printf("Account Number: %d\nName: %10s %10s\nUser Email Address: %20s\nYour Balance: %d\nPassword: %10s\n", u.acc_number, u.fname, u.lname, u.email, u.balance, u.password);
        }
    }

    fclose(fptr);
}

/*
 * This function checks the user account number generated to make sure it doesn't already exist
 * if it does already exist, it will generate a new account number.
 */
int check_acc_number(int x) {
    struct user u;
    int acc_numbers[20];
    int counter = 0;

    FILE* fptr = fopen("user-records.dat", "a+");
    if (fptr == NULL) {
        fprintf(stderr, "\nERROR opening user-records.dat\n\n");
        exit(-1);
    }

    while (fread(&u, sizeof(struct user), 1, fptr))
    {
        acc_numbers[counter] = u.acc_number;
        ++counter; 
    }

    for (int i = 0; i<20; ++i) {
        if (x == acc_numbers[i]) return rand()%10000+1;
    }

    return 0; 

}

/*Function to create dividing walls of "---" when printing things.*/
void divider() {
    int i = 0;
    for(i = 0;i<80;i++) {
        printf("-");
    }
    printf("\n");
}

void print_spaces(int x) {
    int i = 0;
    for(i = 0;i<x;i++) {
        printf(" ");
    }
}

void print_walls(int x) {
    int i = 0;
    for(i = 0;i<x;i++) {
        printf("|"); print_spaces(79); printf("|\n");
    }
}

void welcome_screen() {
    int choice=0;

    system("cls");

    divider();
    printf("|\t ____    ____  ____   __  _       ___   _____       _____  ____  ___ ___|\n");
    printf("|\t|    \\  /    ||    \\ |  |/ ]     /   \\ |     |     / ___/ /    ||   |   |\t|\n");
    printf("|\t|  o  )|  o  ||  _  ||  ' /     |     ||   __|    (   \\_ |  o  || _   _ |\t|\n");
    printf("|\t|     ||     ||  |  ||    \\     |  O  ||  |_       \\__  ||     ||  \\_/  |\t|\n");
    printf("|\t|  O  ||  _  ||  |  ||     \\    |     ||   _]      /  \\ ||  _  ||   |   |\t|\n");
    printf("|\t|     ||  |  ||  |  ||  .  |    |     ||  |        \\    ||  |  ||   |   |\t|\n");
    printf("|\t|_____||__|__||__|__||__|\\_|     \\___/ |__|         \\___||__|__||___|___|\t|\n");
    divider();
    print_walls(2);
    printf("|\t\tPLEASE SELECT AN OPTION\t\t\t\t\t\t|\n");
    print_walls(2);
    printf("|\t\t1. VIEW ALL ACCOUNTS [Press 1 then ENTER]\t\t\t|\n");
    printf("|\t\t2. OPEN AN ACCOUNT [Press 2 then ENTER]\t\t\t\t|\n");
    printf("|\t\t3. LOGIN TO MY ACCOUNT [Press 3 then ENTER]\t\t\t|\n");
    print_walls(10);
    divider();
    printf("Please enter a selection: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        view_account();
        break;
    case 2:
        new_user();
        break;
    case 3:
        login();
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }

}

int main () {

    welcome_screen();
    return 0;
}