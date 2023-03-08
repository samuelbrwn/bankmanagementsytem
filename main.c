/* Project: Bank Management System in C
 * 
 * Author: Samuel Brown
 *
 * Date: 3/7/2023
 */

#include <stdio.h>
#include <stdlib.h>

/*PROTOTYPES*/
void welcome_screen();
void divider();
void print_spaces(int x);
void print_walls(int x);
/*PROTOTYPES*/

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

}

int main () {

    welcome_screen();
    return 0;
}