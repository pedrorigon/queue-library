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
