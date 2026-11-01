
#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 
#include <windows.h> 
#include <time.h> 
#define WIDTH 20 
#define HEIGHT 10 
struct Node { 
int x, y; 
struct Node *next; 
}; 
struct Node *head = NULL; 
int foodX, foodY, score = 0, length = 0; 
int dx = 1, dy = 0; 
int gameOver = 0, won = 0; 
void insertHead(int x, int y) { 
struct Node *newNode = (struct Node *)malloc(sizeof(struct Node)); 
newNode->x = x; 
newNode->y = y; 
newNode->next = head; 
   
   
 
    head = newNode; 
    length++; 
} 
 
/* Snake body mela illaadha cell la food podum */ 
void placeFood() { 
    int onSnake; 
    do { 
        foodX = rand() % WIDTH; 
        foodY = rand() % HEIGHT; 
 
        onSnake = 0; 
        struct Node *temp = head; 
        while (temp != NULL) { 
            if (temp->x == foodX && temp->y == foodY) { 
                onSnake = 1; 
                break; 
            } 
            temp = temp->next; 
        } 
    } while (onSnake); 
} 
 
void initialize() { 
    /* FIX: tail first, head last. So head = x=10 */ 
    insertHead(WIDTH / 2 - 2, HEIGHT / 2); 
   
   
 
    insertHead(WIDTH / 2 - 1, HEIGHT / 2); 
    insertHead(WIDTH / 2, HEIGHT / 2); 
 
    srand((unsigned int)time(NULL)); 
    placeFood(); 
 
    /* Cursor hide pannrom (flicker kammi) */ 
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); 
    CONSOLE_CURSOR_INFO ci = {1, FALSE}; 
    SetConsoleCursorInfo(h, &ci); 
    system("cls"); 
} 
 
void draw() { 
    /* system("cls") badhila cursor ah top ku konduvaroom */ 
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); 
    COORD pos = {0, 0}; 
    SetConsoleCursorPosition(h, pos); 
 
    for (int i = 0; i < WIDTH + 2; i++) 
        printf("#"); 
    printf("\n"); 
 
    for (int y = 0; y < HEIGHT; y++) { 
        printf("#"); 
 
   
   
 
        for (int x = 0; x < WIDTH; x++) { 
            int printed = 0; 
            struct Node *temp = head; 
 
            while (temp != NULL) { 
                if (temp->x == x && temp->y == y) { 
                    printf(temp == head ? "O" : "o"); 
                    printed = 1; 
                    break; 
                } 
                temp = temp->next; 
            } 
 
            if (!printed) { 
                if (x == foodX && y == foodY) 
                    printf("*"); 
                else 
                    printf(" "); 
            } 
        } 
        printf("#\n"); 
    } 
 
    for (int i = 0; i < WIDTH + 2; i++) 
        printf("#"); 
 
   
   
 
    printf("\nScore: %d\n", score); 
    printf("Arrow keys: Move | X: Exit\n"); 
} 
 
void moveSnake() { 
    int nx = head->x + dx; 
    int ny = head->y + dy; 
    int grow = (nx == foodX && ny == foodY); 
 
    /* Wall collision */ 
    if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT) { 
        gameOver = 1; 
        return; 
    } 
 
    /* Body collision (tail move aagum, so grow illati tail allowed) */ 
    struct Node *temp = head; 
    while (temp != NULL) { 
        if (temp->x == nx && temp->y == ny) { 
            if (!grow && temp->next == NULL) 
                break; 
 
            gameOver = 1; 
            return; 
        } 
        temp = temp->next; 
   
   
 
    } 
 
    insertHead(nx, ny); 
 
    if (grow) { 
        score += 10; 
        if (length == WIDTH * HEIGHT) {   /* board full = win */ 
            won = 1; 
            gameOver = 1; 
            return; 
        } 
        placeFood(); 
    } else { 
        /* Tail remove */ 
        temp = head; 
        while (temp->next->next != NULL) 
            temp = temp->next; 
 
        free(temp->next); 
        temp->next = NULL; 
        length--; 
    } 
} 
 
int main() { 
    initialize(); 
   
   
 
 
    while (!gameOver) { 
        draw(); 
 
        if (_kbhit()) { 
            int key = _getch(); 
 
            if (key == 0 || key == 224) { 
                key = _getch(); 
 
                if (key == 72 && dy != 1) {          /* Up */ 
                    dx = 0; dy = -1; 
                } else if (key == 80 && dy != -1) {  /* Down */ 
                    dx = 0; dy = 1; 
                } else if (key == 75 && dx != 1) {   /* Left */ 
                    dx = -1; dy = 0; 
                } else if (key == 77 && dx != -1) {  /* Right */ 
                    dx = 1; dy = 0; 
                } 
            } else if (key == 'x' || key == 'X') { 
                break; 
            } 
        } 
 
        moveSnake(); 
        Sleep(150); 
   
   
 
    } 
 
    draw(); 
    if (won) 
        printf("\nYOU WIN!\n"); 
    else 
        printf("\nGAME OVER!\n"); 
    printf("Final Score: %d\n", score); 
 
    /* Memory free */ 
    while (head != NULL) { 
        struct Node *temp = head; 
        head = head->next; 
        free(temp); 
    } 
 
    return 0; 
} 
 
GAME OVER! 
Final Score: 70 
