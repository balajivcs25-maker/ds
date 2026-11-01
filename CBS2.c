#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAX 5

void producer();
void consumer();
void display();

int q[MAX], rear = -1, front = -1;

void main() {
    int choice;
    clrscr();
    do {
        printf("\n1.Producer \n2.Consumer \n3.Display \n4.Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                producer();
                break;
            case 2:
                consumer();
                break;
            case 3:
                display();
                break;
            case 4:
                getch();
                break;
            default:
                printf("\nEnter valid choice");
        }
    } while (choice != 4);
}

void producer() {
    int value;
    if (rear == MAX) {
        printf("\nBuffer is full");
    } else {
        printf("\nEnter the piece of data: ");
        scanf("%d", &value);
        q[rear] = value;
        rear++;
    }
}

void consumer() {
    int x, i;
    if (rear == -1) {
        printf("\nBuffer is empty");
        getch();
    } else {
        x = q[front];
        for (i = front; i < rear; i++) {
            q[i] = q[i + 1];
        }
        printf("\nThe consumed data is: %d", x);
        rear--;
        getch();
    }
}

void display() {
    int count;
    if (rear == -1) {
        printf("\nThere are no data");
    } else {
        printf("\nThe data are:");
        for (count = front; count < rear; count++) {
            printf("\n%d", q[count]);
        }
        getch();
    }
}
