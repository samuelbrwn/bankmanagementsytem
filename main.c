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
void deposit(struct user u);
void withdraw(struct user u);
void login();
void new_user(void);
void view_account(void);
int check_acc_number(int x);
void divider();
void print_spaces(int x);
void print_walls(int x);
/*PROTOTYPES*/

void deposit(struct user u) {
    int counter = 0;
    int deposit;
    char deposit_buffer[100];
    struct user u1;
    struct user users_temp[100];
    FILE* fptr = fopen("user-records.dat", "rb");
    if(fptr == NULL){
        fprintf(stderr, "ERROR opening file user-records.dat\n");
        exit(-1);
    }

    system("cls");
    printf("\nEnter Deposit Amount: ");
    if(fgets(deposit_buffer, 100, stdin)) {
        deposit_buffer[strcspn(deposit_buffer, "\r\n")] = 0;
        deposit = atoi(deposit_buffer);
    }
    
    u.balance = deposit;

    while(fread(&u1, sizeof(struct user), 1, fptr)) {
        users_temp[counter] = u1;
        ++counter;
    }
    fclose(fptr);

    for(int i=0; i<(sizeof(users_temp)/sizeof(users_temp[0])); i++) {
        if (users_temp[i].acc_number == u.acc_number) {
            users_temp[i] = u;
            break;
        }
    }
    
    fptr = fopen("user-records.dat", "wb");
    if(fptr == NULL) {
        fprintf(stderr, "ERROR opening user-records.dat\n");
        exit(-1);
    }
    for(int i = 0; i<counter; ++i) {
        fwrite(&users_temp[i],sizeof(struct user), 1, fptr);
    }
    fclose(fptr);
}

void withdraw(struct user u) {

}

/*
 * This function creates a new user and then writes
 * this user to a dat file in binary.
 */
void new_user(void) {
    int choice;
    char choice_buff[100];
    char pass[100];
    char fname[100];
    char lname[100];
    char email[100];
    int next = 0;
    struct user new_user;
    new_user.balance = 0;
    new_user.acc_number = rand()%10000+1;
    int alternate_acc_number = check_acc_number(new_user.acc_number);

    FILE* fptr = fopen("user-records.dat", "a");
    if (fptr == NULL) {
        fprintf(stderr, "ERROR opening user-records.dat\n");
        exit(-1);
    }

    if (alternate_acc_number != 0) new_user.acc_number = alternate_acc_number;

    system("cls");
    printf("Please enter your first name: ");
    if(fgets(fname, sizeof fname, stdin)) {
        fname[strcspn(fname, "\r\n")] = 0;
        sscanf(fname, "%s", &new_user.fname);
    }
    divider();
    printf("Please enter your last name: ");
    if(fgets(lname, sizeof lname, stdin)) {
        lname[strcspn(lname, "\r\n")] = 0;
        sscanf(lname, "%s", &new_user.lname);
    }
    divider();
    printf("Please enter your e-mail: ");
    if(fgets(email, sizeof email, stdin)) {
        email[strcspn(email, "\r\n")] = 0;
        sscanf(email, "%s", &new_user.email);
    }
    divider();
    printf("Please enter a password: ");
    if(fgets(pass, sizeof pass, stdin)) {
        pass[strcspn(pass, "\r\n")] = 0;
        sscanf(pass, "%s", &new_user.password);
    }
    divider();

    fwrite(&new_user, sizeof (struct user), 1, fptr);
    fclose(fptr);
    
    printf("Would you like to return to the main menu? [Press 1 then ENTER for yes || Press 2 then ENTER to exit software.]");
    if(fgets(choice_buff, 100, stdin)) {
        choice_buff[strcspn(choice_buff, "\r\n")] = 0;
        choice = atoi(choice_buff);
        
        switch (choice)
        {
            case 1:
                welcome_screen();
                break;
            default:
                break;
        }
    }
}

/*
 * This function opens the user-records.dat file, and fetches the
 * structs and prints the data.
 * 
 * I have not yet implemented the ability to search for a specific user.
 *
 * */
void view_account(void) {
    int choice;
    char choice_buff[100];

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

    printf("Would you like to return to the main menu? [Press 1 then ENTER for yes || Press 2 then ENTER to exit software.]");
    if(fgets(choice_buff, 100, stdin)) {
        choice_buff[strcspn(choice_buff, "\r\n")] = 0;
        choice = atoi(choice_buff);
        
        switch (choice)
        {
            case 1:
                welcome_screen();
                break;
            default:
                break;
        }
    }
}

/*This function allows you to pull up a specific account based on the user account number*/
void login(void) {
    int account_number;
    int acc_number_exists = 0;
    int counter = 0;
    char buff[1024];
    char pass[100];
    struct user u;
    struct user users[10];

    system("cls");
    FILE* fptr = fopen("user-records.dat", "r");
    if(fptr == NULL) {
        fprintf(stderr, "ERROR opening file user-records.dat\n");
        exit(-1);
    }

    /*
     * Read all users into an array, later allowing us to iterate through the stucts
     * to find the correct user
     */
    while(fread(&u, sizeof(struct user), 1, fptr)) {
        users[counter] = u;
        ++counter;
    }
    
    counter = 0;
    printf("Please enter your unique account number: ");
    if(fgets(buff, 1024, stdin)) {
        buff[strcspn(buff, "\r\n")] = 0;
        account_number = atoi(buff);
    }

    for(int i=0; i<(sizeof(users)/sizeof(users[0])); i++) {
        if (users[i].acc_number == account_number) {
            acc_number_exists = 1;
            u =  users[i];
            break;
        }
    }
    
    if(acc_number_exists) {
        printf("Account located! Please enter your password: ");
        if(fgets(pass, 100, stdin)) {
            pass[strcspn(pass, "\r\n")] = 0;
            sscanf(pass, "%s", pass);
         }

        if(strcmp(u.password, pass) != 0) {
            printf("Password invalid. Press ENTER to try again.");
            fclose(fptr);
            getch();
            login();
        } else {
            int choice;
            char choice_buffer[10];

            printf("Account Number: %d\nName: %10s %10s\nEmail: %40s\nBalance: %d\nPassword: %10s\n", u.acc_number, u.fname, u.lname, u.email, u.balance, u.password);
            divider();
            printf("What would you like to do?\n");
            printf("1. DEPOSIT [Press 1 then ENTER]\n");
            printf("2. WITHDRAWAL [Press 2 then ENTER]\n");
            if(fgets(choice_buffer, 10, stdin)) {
                choice_buffer[strcspn(choice_buffer, "\r\n")] = 0;
                choice = atoi(choice_buffer);
            }

            switch(choice)
            {
                case 1:
                    deposit(u);
                    break;
                case 2:
                    withdraw(u);
                    break;
                default:
                    break;
            }
        }

    } else {
        printf("No account with this Account Number exists. Press ENTER to try again.\n");
        fclose(fptr);
        getch();
        login();
    }
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
        if (x == acc_numbers[i]) {
            x = rand()%10000+1;
        } else return x;
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
    int choice;
    char choice_buff[100];

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
    if(fgets(choice_buff, 100, stdin)) {

        choice_buff[strcspn(choice_buff, "\n")] = 0;
        choice = atoi(choice_buff);

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

}

int main () {

    welcome_screen();
    return 0;
}