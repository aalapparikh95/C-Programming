#include "stackHw.h"
#include "GetNumbers.c"
#include <stdio.h>
#include <stdlib.h>
#include "timing.h"
#include "timing.c"

int n = 100;

struct node
{
    int value;
    struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

void push(int);
void printStack();
void pop();

void createStack()
{
    int i,j;
    for(j = 0; j < n; j++)
    {
        for (i = 0; i < numSize; i++)
        {
            //printf("%d\n",i);
            push(numbers[i]);
        }
        //printStack();

        for (i = 0; i < numSize; i++)
        {
            pop();
        }
    }
    //printStack();
    printf("\n");
}

void pop()
{
    printf("Popping %d from stack\n",head->value);
    head = head->next;
}

void push(int value)
{
    printf("Pushing %d to stack\n",value);
    struct node *link = (struct node*) malloc(sizeof(struct node));
    link->value = value;
    link->next = head;

    head = link;
    //printf("Inserted %d", value);
}

void printStack()
{
    if(head == NULL)
    {
        printf("Empty Stack!");
        return;
    }
    current = head;
    printf("%d",current->value);
    current = current->next;
    do
    {
        printf("-->");
        printf("%d",current->value);
        current = current->next;
    }
    while(current->next);
    printf("-->%d",current->value);
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("\nEnter valid Values\n");
        return 0;
    }
    GetNumbers(argv[1]);
    //printf("%d\n", *numbers);
    timing_start();
    createStack();
    timing_stop();
    print_timing();
    //printStack();


    return 0;
}