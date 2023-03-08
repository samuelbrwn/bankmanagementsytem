/* Project: Bank Management System in C
 * 
 * Author: Samuel Brown
 *
 * Date: 3/7/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Global Declaration of the user struct*/
struct user
{
    int acc_number;
    char fname[20], lname[20];
    char email[30];
    int balance;
};


/*PROTOTYPES*/
void welcome_screen();
int new_user(void);
void divider();
void print_spaces(int x);
void print_walls(int x);
/*PROTOTYPES*/

/*
 * This function creates a new user and then writes
 * this user to a dat file in binary.
 */
int new_user(void) {
    struct user new_user;
    new_user.balance = 0;
    new_user.acc_number = rand()%10000+1;

    FILE* fptr = fopen("user-records.dat", "a");
    if (fptr == NULL) return -1;

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

    fwrite(&new_user, sizeof (struct user), 1, fptr);
    
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
void view_account() {

    system("cls");

    struct user u;

    FILE* fptr = fopen("user-records.dat", "r");
    if (fptr == NULL) {
        fprintf(stderr, "\nError opening user-records.dat\n\n");
        exit(-1);
    }

    while(fread(&u, sizeof(struct user), 1, fptr))
        printf("Account Number: %d\nName: %10s %10s\nUser Email Address: %20s\nYour Balance: %d\n\n", u.acc_number, u.fname, u.lname, u.email, u.balance);

    fclose(fptr);
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

    divider();
    printf("|\t ____    ____  ____   __  _       ___   _____       _____  ____  ___ ___\t|\n");
    printf("|\t|    \\  /    ||    \\ |  |/ ]     /   \\ |     |     / ___/ /    ||   |   |\t|\n");
    printf("|\t|  o  )|  o  ||  _  ||  ' /     |     ||   __|    (   \\_ |  o  || _   _ |\t|\n");
    printf("|\t|     ||     ||  |  ||    \\     |  O  ||  |_       \\__  ||     ||  \\_/  |\t|\n");
    printf("|\t|  O  ||  _  ||  |  ||     \\    |     ||   _]      /  \\ ||  _  ||   |   |\t|\n");
    printf("|\t|     ||  |  ||  |  ||  .  |    |     ||  |        \\    ||  |  ||   |   |\t|\n");
    printf("|\t|_____||__|__||__|__||__|\\_|     \\___/ |__|         \\___||__|__||___|___|\t|\n");
    divider();
    print_walls(2);
    printf("|\t\tPLEASE SELECT AN OPTION\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    print_walls(2);
    printf("|\t\t1. VIEW MY ACCOUNT [Press 1 then ENTER]\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t2. OPEN AN ACCOUNT [Press 2 then ENTER]\t\t\t\t\t\t\t\t\t|\n");
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
    default:
        printf("Invalid choice.\n");
        break;
    }

}

int main () {

    welcome_screen();
    return 0;
}