/*
 * MIT License
 *
 * Copyright (c) 2025 Pedro H C Rigon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
