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

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void test_queue_operations()
{
    struct LinkedList *queue = queue_create();

    if (!queue)
    {
        printf("Failed to create queue.\n");
        return;
    }

    // Adding elements
    queue_push(queue, 10);
    queue_push(queue, 20);
    queue_push(queue, 30);

    printf("Queue contents: ");
    queue_print(queue);

    // Peek front element
    int front_value;
    if (queue_peek(queue, &front_value))
    {
        printf("Front element: %d\n", front_value);
    }

    // Remove element and print updated queue
    queue_pop(queue);
    printf("After pop: ");
    queue_print(queue);

    // Check if queue is empty
    printf("Queue is %s\n", queue_is_empty(queue) ? "empty" : "not empty");

    // Search for an element
    int search_value = 20;
    printf("Element %d %s in queue\n", search_value, queue_search(queue, search_value) ? "found" : "not found");

    // Get queue size
    printf("Queue size: %d\n", queue_size(queue));

    queue_free(queue);
}

int main(void)
{
    test_queue_operations();
    return 0;
}
