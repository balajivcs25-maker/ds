#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(int data)
{
    struct Node *newNode = createNode(data);
    newNode->next = head;
    head = newNode;
}

void insertAtEnd(int data)
{
    struct Node *newNode = createNode(data);

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void insertAtPosition(int data, int position)
{
    if (position == 1)
    {
        insertAtBeginning(data);
        return;
    }

    struct Node *newNode = createNode(data);
    struct Node *temp = head;

    int count = 1;
    while (count < position - 1 && temp != NULL)
    {
        temp = temp->next;
        count++;
    }

    if (temp == NULL)
        return;

    newNode->next = temp->next;
    temp->next = newNode;
}

void deleteAtBeginning()
{
    if (head == NULL)
        return;

    struct Node *temp = head;
    head = head->next;
    free(temp);
}

void deleteAtEnd()
{
    if (head == NULL)
        return;

    if (head->next == NULL)
    {
        free(head);
        head = NULL;
        return;
    }

    struct Node *temp = head;
    while (temp->next->next != NULL)
        temp = temp->next;

    free(temp->next);
    temp->next = NULL;
}

void deleteAtPosition(int position)
{
    if (position == 1)
    {
        deleteAtBeginning();
        return;
    }

    struct Node *temp = head;
    int count = 1;

    while (count < position - 1 && temp != NULL)
    {
        temp = temp->next;
        count++;
    }

    if (temp == NULL || temp->next == NULL)
        return;

    struct Node *del = temp->next;
    temp->next = del->next;
    free(del);
}

void display()
{
    struct Node *temp = head;

    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

int main()
{
    int choice, data, position;

    while (1)
    {
        printf("\n1.Insert Beginning\n2.Insert End\n3.Insert Position\n4.Delete Beginning\n5.Delete End\n6.Delete Position\n7.Display\n8.Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                scanf("%d", &data);
                insertAtBeginning(data);
                break;

            case 2:
                scanf("%d", &data);
                insertAtEnd(data);
                break;

            case 3:
                scanf("%d%d", &data, &position);
                insertAtPosition(data, position);
                break;

            case 4:
                deleteAtBeginning();
                break;

            case 5:
                deleteAtEnd();
                break;

            case 6:
                scanf("%d", &position);
                deleteAtPosition(position);
                break;

            case 7:
                display();
                break;

            case 8:
                exit(0);
        }
    }
}
