#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Maximum number of registered queues
#define MAX_QUEUES 100

struct Node
{
    int data;
    struct Node *next;
    struct Node *previous;
};

struct LinkedList
{
    struct Node *head;
    struct Node *tail;
    int size;
    int index;
};

struct LinkedList *queue_create();
void queue_push(struct LinkedList *list, int data);
int queue_pop(struct LinkedList *list);
int queue_search(struct LinkedList *list, int data);
void queue_print(struct LinkedList *list);
void queue_free(struct LinkedList *list);
int queue_size(struct LinkedList *list);
bool queue_peek(struct LinkedList *list, int *out_value);
bool queue_is_empty(struct LinkedList *list);

#endif
