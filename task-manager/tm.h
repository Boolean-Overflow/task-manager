typedef struct TaskManager TM;
typedef struct Task Task;
typedef struct Queue Queue;
typedef struct Stack Stack;


Task create_task();
Task* create_task();
void print_task(Task task);

TM* tm_init();
TM* tm_insert(TM* tm, Task task);
TM* tm_remove(TM* tm, char* id);

// Matateu
Queue* queue_init();
void queue_print(Queue* queue);
Queue* queue_copy(Queue* source);
Queue* enqueue(Queue* queue, Task task);
Task dequeue(Queue** queue);

// Lukeny
Stack* stack_init();
int stack_empty(Stack* stack);
Stack* stack_push(Stack* stack, Queue* queue);
Queue* stack_pop(Stack** stack);
Queue* stack_peek(Stack* stack);

