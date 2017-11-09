#include "stackHw.h"
#include "GetNumbers.c"
#include <stdio.h>
#include <stdlib.h>
#include "timing.h"
#include "timing.c"
#include <pthread.h>

int n = 100;

int p = 5;

int perThread;

pthread_mutex_t m1;

pthread_mutex_t m2;

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

void* createStack(void *start)
{
    int i,j;

    int startElement = (int*)start;
    int endElement = startElement + perThread;
    printf("Start element: %d End element: %d\n", startElement,endElement);
    if(endElement - numSize < perThread)
    {
        endElement = numSize;
    }
    for(j = 0; j < n; j++)
    {
        for (i = startElement; i < endElement; i++)
        {
            printf("%d\n",i);
            pthread_mutex_lock(&m1);
            push(numbers[i]);
            pthread_mutex_unlock(&m1);
        }
        printStack();
        //printf("Thread is here!\n");

        for (i = 0; i < numSize; i++)
        {
            pthread_mutex_lock(&m2);
            //printf("Thread is about to pop stuff!\n");
            pop();
            pthread_mutex_unlock(&m2);
        }
    }
    //printStack();
    printf("\n");
}

void pop()
{
    if(head == NULL)
    {
        printf("Stack already empty!\n");
        return;
    }
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
    printf("-->%d\n",current->value);
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

    perThread = numSize/p;
    int i;
    pthread_t thread[p];

    pthread_mutex_init(&m1, NULL);
    pthread_mutex_init(&m2, NULL);

    timing_start();

    int thread_start;
    for(i = 0; i < p; i++) {
        thread_start = i * perThread;
        printf("thread start: %d\n", thread_start);
        pthread_create(&thread[i], NULL, createStack, (void *) thread_start);
        thread_start++;
    }
    for (i = 0; i < p; i++)
    {
        printf("Joining! \n");
        pthread_join(&thread[i], NULL);
    }

    timing_stop();
    print_timing();
    //printStack();


    return 0;
}