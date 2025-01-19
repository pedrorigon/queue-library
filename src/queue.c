#include "queue.h"

static struct LinkedList *registered_queues[MAX_QUEUES] = {NULL};
static int next_index = 0;

struct LinkedList *queue_create()
{
    /**
     * Allocates and initializes a new linked list structure.
     *
     * The function creates a new `LinkedList` instance, assigns it a unique index,
     * and sets all its pointers to NULL. It logs an error message and returns NULL
     * if memory allocation fails or the maximum number of lists (`MAX_QUEUES`) is exceeded.
     *
     * @note The created list must be managed and freed using `queue_free` to avoid memory leaks.
     *
     * @complexity Time complexity: O(1).
     *
     * @return Pointer to the newly created `LinkedList` structure, or NULL if creation fails.
     */
    if (next_index >= MAX_QUEUES)
    {
        fprintf(stderr, "ERROR: Cannot create more than %d lists.\n", MAX_QUEUES);
        return NULL;
    }

    struct LinkedList *list = (struct LinkedList *)malloc(sizeof(struct LinkedList));
    if (!list)
    {
        fprintf(stderr, "ERROR: Memory allocation failed for LinkedList.\n");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->index = next_index;
    next_index++;
#if DEBUG_MODE
    fprintf(stderr, "INFO: Linked list (QUEUE) initialized with index %d.\n", list->index);
#endif
    return list;
}

static void cleanup_linked_list(void)
{
    /**
     * Frees all registered linked lists and resets internal state.
     *
     * This function is automatically registered with `atexit` to be executed at program termination.
     * It iterates over all registered linked lists, frees their memory, and sets their pointers to NULL.
     * If no lists are registered, it exits without performing any operations.
     *
     * @note This function is static and cannot be called directly by external modules.
     *       It ensures that all linked lists created during program execution are safely freed.
     *
     * @complexity Time complexity: O(n * m), where n is the number of lists and m is the number of nodes per list.
     */
#if DEBUG_MODE
    fprintf(stderr, "DEBUG: Starting cleanup_linked_list\n");
#endif
    for (int i = 0; i < next_index; i++)
    {
        if (registered_queues[i] != NULL)
        {
            if ((registered_queues[i]->head != NULL) || (registered_queues[i]->tail != NULL))
            {
                queue_free(registered_queues[i]);
            }
            free(registered_queues[i]);
            registered_queues[i] = NULL;
        }
    }
    next_index = 0;
    fprintf(stderr, "INFO: All QUEUES have been freed.\n");
}

__attribute__((constructor)) static void register_cleanup()
{
    /**
     * Registers the `cleanup_linked_list` function for automatic execution.
     *
     * This function uses the `atexit` mechanism to ensure that `cleanup_linked_list`
     * is called at program termination. It is executed automatically during program
     * initialization due to the `constructor` attribute.
     *
     * @note This function is static and cannot be called directly by external modules.
     *       It is executed automatically before the `main` function.
     *
     * @complexity Time complexity: O(1).
     */
    atexit(cleanup_linked_list);
#if DEBUG_MODE
    fprintf(stderr, "INFO: Automatic cleanup registered. All QUEUES will be freed at program termination.\n");
#endif
}

void queue_print(struct LinkedList *list)
{
    /**
     * Prints the elements of the doubly linked list from head to tail.
     * This is an internal function used for debugging purposes and cannot
     * be accessed directly by external modules or users.
     *
     * The function indicates the head and tail nodes explicitly. If the list
     * is empty, it prints a message stating so.
     *
     * @note This function is declared as `static`, making it accessible only
     *       within `linked_list.c`. It is typically called by other functions
     *       in this file for internal debugging.
     *
     * @complexity Time complexity: O(n), where n is the number of nodes in the list.
     *
     * @param list Pointer to the LinkedList structure.
     */
    if (list->head == NULL)
    {
        fprintf(stderr, "QUEUE is empty.\n");
        return;
    }
    fprintf(stderr, "[QUEUE %d]  --->  ", list->index);
    if (list->head == list->tail)
    {
        fprintf(stderr, "(HEAD) [ %d ] (TAIL)\n", list->head->data);
        return;
    }

    struct Node *iterator = list->head;
    while (iterator != NULL)
    {
        if (iterator == list->head)
        {
            fprintf(stderr, "(HEAD) [ %d ] ---> ", iterator->data);
        }
        else if (iterator == list->tail)
        {
            fprintf(stderr, "[ %d ] (TAIL)\n", iterator->data);
        }
        else
        {
            fprintf(stderr, "[ %d ] ---> ", iterator->data);
        }
        iterator = iterator->next;
    }
}

static void initialize_linked_list(struct LinkedList *list, int data)
{
    /**
     * Initializes a doubly linked list with a single node containing the specified data.
     *
     * This function allocates memory for a new node and sets it as the head and tail of the list.
     * The list is also registered for cleanup during program termination. If the list is already
     * initialized, it logs a message and returns without modifying the existing list.
     *
     * @note The function exits the program with `EXIT_FAILURE` if memory allocation fails.
     *
     * @complexity Time complexity: O(1).
     *
     * @param list Pointer to the `LinkedList` structure to be initialized.
     * @param data The value to store in the newly created node.
     */
    if (list->head != NULL)
    {
#if DEBUG_MODE
        fprintf(stderr, "INFO: QUEUE already initialized.\n");
#endif
        return;
    }
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed in initialize_linked_list(). Exiting...\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->previous = NULL;

    list->head = new_node;
    list->tail = new_node;
    list->size = 1;
    registered_queues[list->index] = list;
}

void queue_push(struct LinkedList *list, int data)
{
    /**
     * Adds a new node with the given data at the end of the doubly linked list.
     * If the list is empty, it initializes the list using `initialize_linked_list`.
     * Otherwise, it appends the new node to the end of the list.
     *
     * @note Exits the program with `EXIT_FAILURE` if memory allocation fails.
     *
     * @complexity Time complexity: O(1).
     *
     * @param list Pointer to the LinkedList structure.
     * @param data The value to store in the newly created node.
     */
    if (!list)
    {
        fprintf(stderr, "ERROR: Attempt to push to a NULL QUEUE.\n");
        return;
    }
    if (list->head == NULL)
    {
        initialize_linked_list(list, data);
    }
    else
    {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        if (new_node == NULL)
        {
            fprintf(stderr, "ERROR: Memory allocation failed in push(). Exiting...\n");
            exit(EXIT_FAILURE);
        }
        new_node->data = data;
        new_node->next = NULL;
        new_node->previous = list->tail;

        list->tail->next = new_node;
        list->tail = new_node;
        list->size++;
    }
#if DEBUG_MODE
    fprintf(stderr, "PUSH %d:   ", data);
    queue_print(list);
#endif
}

int queue_pop(struct LinkedList *list)
{
    /**
     * Removes and returns the value of the first node in the doubly linked list.
     * If the list is empty, it returns -1. The function also updates the `head`
     * and `tail` pointers in the LinkedList structure as necessary.
     *
     * @note Ensure the list is not empty before calling this function.
     *
     * @complexity Time complexity: O(1).
     *
     * @param list Pointer to the LinkedList structure.
     * @return The value of the removed node, or -1 if the list is empty.
     */
    if (!list || list->head == NULL)
    {
#if DEBUG_MODE
        fprintf(stderr, "WARNING: Attempt to pop from an empty or NULL QUEUE.\n");
#endif
        return -1;
    }

    struct Node *temp_head = list->head;
    int data = list->head->data; // perguntar isso

    if (list->head->next == NULL)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        list->head = temp_head->next;
        list->head->previous = NULL;
    }

    free(temp_head);
    list->size--;

#if DEBUG_MODE
    fprintf(stderr, "POP  %d:   ", data);
    queue_print(list);
#endif
    return data;
}

int queue_search(struct LinkedList *list, int data)
{
    /**
     * Searches for a value in the doubly linked list and returns its position (1-based index).
     * If the value is found, the position is returned. Otherwise, it prints a message
     * indicating that the value was not found and returns -1.
     *
     * @note The search is performed sequentially from head to tail.
     *
     * @complexity Time complexity: O(n), where n is the number of nodes in the list.
     *
     * @param list Pointer to the LinkedList structure.
     * @param data The value to search for in the list.
     * @return The position of the value in the list (1-based), or -1 if not found.
     */
    if (list->head == NULL)
    {
#if DEBUG_MODE
        fprintf(stderr, "INFO: QUEUE is empty. Cannot search for data.\n");
#endif
        return -1;
    }

    struct Node *iterator = list->head;
    int position = 1;

    while (iterator != NULL)
    {
        if (iterator->data == data)
        {
#if DEBUG_MODE
            fprintf(stderr, "DEBUG: Data %d found at position %d.\n", data, position);
#endif
            return position;
        }
        iterator = iterator->next;
        position++;
    }
#if DEBUG_MODE
    fprintf(stderr, "DEBUG: Value %d NOT found in the QUEUE after traversing %d elements\n", data, position - 1);
#endif
    return -1;
}

void queue_free(struct LinkedList *list)
{
    /**
     * Frees all memory associated with the doubly linked list and sets
     * the `head` and `tail` pointers in the `LinkedList` structure to NULL.
     *
     * If the list has already been freed or is empty, the function logs a message
     * and skips the operation to prevent errors such as double free. After calling
     * this function, the list will be empty and cannot be used without reinitialization.
     *
     * @note The function ensures that all nodes in the list are freed before resetting the list.
     *
     * @complexity Time complexity: O(n), where n is the number of nodes in the list.
     *
     * @param list Pointer to the `LinkedList` structure. The list must be properly
     *             initialized before being passed to this function.
     */
    if (!list || list->head == NULL)
    {
        fprintf(stderr, "INFO: QUEUE is already empty or NULL. Skipping free.\n");
        return;
    }

#if DEBUG_MODE
    fprintf(stderr, "INFO: Freeing QUEUE at index %d.\n", list->index);
#endif

    struct Node *iterator = list->head;
    while (iterator != NULL)
    {
        struct Node *temp = iterator;
        iterator = iterator->next;
        free(temp);
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

#if DEBUG_MODE
    fprintf(stderr, "INFO: All nodes in the QUEUE %d have been freed.\n", list->index);
#endif
}

int queue_size(struct LinkedList *list)
{
    /**
     * Retrieves the size of the linked list.
     *
     * This function returns the current number of elements in the linked list.
     *
     * @complexity Time complexity: O(1).
     *
     * @param list Pointer to the LinkedList structure.
     * @return The size of the linked list.
     */
    if (!list || list->head == NULL)
    {
#if DEBUG_MODE
        fprintf(stderr, "INFO: Attempt to get size of an empty or NULL QUEUE.\n");
#endif
        return 0;
    }
#if DEBUG_MODE
    fprintf(stderr, "DEBUG: Current size of the [QUEUE %d]: %d.\n", list->index, list->size);
#endif
    return list->size;
}

bool queue_peek(struct LinkedList *list, int *out_value)
{
    /**
     * Retrieves the front element of the queue without removing it.
     *
     * This function checks if the queue is empty and, if not, retrieves
     * the value of the first element (head) without dequeuing it.
     *
     * @complexity Time complexity: O(1).
     *
     * @param list Pointer to the LinkedList structure.
     * @param out_value Pointer to an integer where the front element's value will be stored.
     * @return `true` if the operation is successful and the value is retrieved,
     *         `false` if the queue is empty or the list pointer is NULL.
     */
    if (list == NULL || list->head == NULL)
    {
        fprintf(stderr, "ERROR: QUEUE %d is Empty.\n", list->index);
        return false;
    }
    *out_value = list->head->data;
    return true;
}

bool queue_is_empty(struct LinkedList *list)
{
    /**
     * Checks if the queue is empty.
     *
     * This function determines whether the queue contains any elements.
     *
     * @complexity Time complexity: O(1).
     *
     * @param list Pointer to the LinkedList structure.
     * @return `true` if the queue is empty or the list pointer is NULL, `false` otherwise.
     */
    return (list == NULL || list->size == 0);
}