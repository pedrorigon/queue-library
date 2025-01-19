# Queue Library in C

A simple and efficient queue implementation using linked lists in C.

## Features

- **Basic operations:** `queue_create`, `queue_push`, `queue_pop`, `queue_peek`, `queue_is_empty`
- **Memory management automation:** Automatically frees all queue structures created, preventing memory leaks.
- **Multi-queue support:** Handles up to 100 queues simultaneously.
- **Print and search utilities:** `queue_print`, `queue_search`
- **Queue size retrieval:** `queue_size`
- **Debug mode:** Activate using the `-DDEBUG_MODE=1` flag to enable detailed logs of queue operations, memory usage, and error diagnostics.

## Installation

To use this library in your project, follow these steps:

### 1. Clone the repository:

```bash
git clone https://github.com/your-username/queue-library.git
cd queue-library
```

### 2. Compile the library:

Use the provided `Makefile` in the root directory to compile the queue library.

```bash
make
```

This will generate the static library `libqueue.a` inside the `build/` directory.

### 3. Include the library in your project:

- Add `include/queue.h` to your source files.
- Link the compiled `libqueue.a` during compilation:

```bash
gcc -o my_program my_program.c -I./include -L./build -lqueue
```

## 4. (Optional) Install the library in your system:

To make the library available globally on your system, follow these steps:

1. Copy the header file to the system include directory:

   ```bash
   sudo cp include/queue.h /usr/local/include/
   ```
2. Copy the compiled library to the system library directory:

   ```bash
   sudo cp build/libqueue.a /usr/local/lib/
   ```
3. Update the system's linker cache:

   ```bash
   sudo ldconfig
   ```

Now you can use the library from any project without specifying the full path:

```bash
gcc -o my_program my_program.c -lqueue
```

If you encounter issues with the linker not finding the library, ensure that `/usr/local/lib` is included in your library search path by adding it to your environment:

```bash
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```

To remove the library from your system, simply delete the installed files:

```bash
sudo rm /usr/local/include/queue.h
sudo rm /usr/local/lib/libqueue.a
```

## Usage

Here's an example of how to use the queue library in C:

### Example Code

```c
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
```

### Expected Output (with `-DDEBUG_MODE=0`):

```
[QUEUE 0]  --->  (HEAD) [ 10 ] ---> [ 20 ] ---> [ 30 ] (TAIL)
Queue contents: Front element: 10
[QUEUE 0]  --->  (HEAD) [ 20 ] ---> [ 30 ] (TAIL)
After pop: Queue is not empty
Element 20 found in queue
Queue size: 2
INFO: All QUEUES have been freed.
```

### Expected Output (with `-DDEBUG_MODE=1`):

```
INFO: Automatic cleanup registered. All QUEUES will be freed at program termination.
INFO: Linked list (QUEUE) initialized with index 0.
PUSH 10:   [QUEUE 0]  --->  (HEAD) [ 10 ] (TAIL)
PUSH 20:   [QUEUE 0]  --->  (HEAD) [ 10 ] ---> [ 20 ] (TAIL)
PUSH 30:   [QUEUE 0]  --->  (HEAD) [ 10 ] ---> [ 20 ] ---> [ 30 ] (TAIL)
[QUEUE 0]  --->  (HEAD) [ 10 ] ---> [ 20 ] ---> [ 30 ] (TAIL)
Queue contents: Front element: 10
POP  10:   [QUEUE 0]  --->  (HEAD) [ 20 ] ---> [ 30 ] (TAIL)
[QUEUE 0]  --->  (HEAD) [ 20 ] ---> [ 30 ] (TAIL)
After pop: Queue is not empty
DEBUG: Data 20 found at position 1.
Element 20 found in queue
DEBUG: Current size of the [QUEUE 0]: 2.
Queue size: 2
INFO: Freeing QUEUE at index 0.
INFO: All nodes in the QUEUE 0 have been freed.
DEBUG: Starting cleanup_linked_list
INFO: All QUEUES have been freed.
```

## API Reference

### 1. Queue Creation

```c
struct LinkedList *queue_create();
```

**Description:**
Allocates and initializes a new linked list structure.

- Creates a new `LinkedList` instance, assigns it a unique index, and initializes pointers.
- Returns `NULL` if memory allocation fails or if the maximum number of lists (`MAX_QUEUES`) is exceeded.

**Complexity:** O(1)

**Returns:** Pointer to the newly created `LinkedList` structure, or `NULL` if creation fails.

### 2. Enqueue an Element

```c
void queue_push(struct LinkedList *list, int data);
```

**Description:**
Adds a new node with the given data at the end of the queue.

- Initializes the list if empty; otherwise, appends to the end.
- Exits with `EXIT_FAILURE` if memory allocation fails.

**Complexity:** O(1)

**Parameters:**

- `list` - Pointer to the queue.
- `data` - The value to store.

### 3. Dequeue an Element

```c
int queue_pop(struct LinkedList *list);
```

**Description:**
Removes and returns the value of the first node.

- If the list is empty, returns `-1`.

**Complexity:** O(1)

**Returns:** The value of the removed node, or `-1` if empty.

### 4. Search for an Element

```c
int queue_search(struct LinkedList *list, int data);
```

**Description:**
Searches for a value in the queue and returns its position (1-based index).

- If not found, returns `-1`.

**Complexity:** O(n)

**Returns:** Position of the value (1-based), or `-1` if not found.

### 5. Print Queue Elements

```c
void queue_print(struct LinkedList *list);
```

**Description:**
Prints the elements of the queue from head to tail.

- If the list is empty, prints a message.

**Complexity:** O(n)

### 6. Free Queue Memory

```c
void queue_free(struct LinkedList *list);
```

**Description:**
Frees all memory associated with the queue and resets pointers.

- Prevents double free errors by checking if the list has already been freed.

**Complexity:** O(n)

### 7. Get Queue Size

```c
int queue_size(struct LinkedList *list);
```

**Description:**
Returns the number of elements in the queue.

**Complexity:** O(1)

**Returns:** The size of the queue.

### 8. Peek Front Element

```c
bool queue_peek(struct LinkedList *list, int *out_value);
```

**Description:**
Retrieves the front element without removing it.

- If the queue is empty, returns `false`.

**Complexity:** O(1)

**Returns:** `true` if successful, `false` if empty.

### 9. Check if Queue is Empty

```c
bool queue_is_empty(struct LinkedList *list);
```

**Description:**
Checks whether the queue is empty.

**Complexity:** O(1)

**Returns:** `true` if empty, `false` otherwise.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

If you have any questions or suggestions, feel free to reach out:

- GitHub: https://github.com/pedrorigon
- Email: phcrigon@inf.ufrgs.br
