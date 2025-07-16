#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Op {
    char Action[100];
    char Value[100];
}Op;

typedef struct Stack {
    Op *opr;
    int top;
    int capacity;
}Stack;

typedef struct Document {
    Op *opr;
    int front;
    int rear;
    int capacity;
}Document;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->opr = (Op*)malloc(sizeof(Op) * capacity);
    return stack;
}

void push(Stack *stack, Op op) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack full\n");
        return;
    }
    stack->top++;
    stack->opr[stack->top] = op;
}

Op pop(Stack *stack) {
    Op empty = {"", ""};
    if (stack->top == -1) {
        printf("Empty stack\n");
        return empty;
    }
    return stack->opr[stack->top--];
}

Document *createQueue(int capacity) {
    Document *queue = (Document *) malloc(sizeof(Document));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->opr = (Op*)malloc(sizeof(Op) * capacity);
    return queue;
}

void enqueue(Document *queue, Op op) {
    if (queue->rear == queue->capacity - 1) {
        printf("Queue full\n");
        return;
    }
    queue->rear++;
    queue->opr[queue->rear] = op;
}

void displayQueue(Document *queue) {
    if (queue->rear < 0) {
        printf("Empty queue\n");
        return;
    }
    for (int i = 0; i <= queue->rear; i++) {
        printf("%s ", queue->opr[i].Value);
    }
    printf("\n");
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void printMenu(){
    printf("1. INSERT \n");
    printf("2. UNDO \n");
    printf("3. REDO\n");
    printf("4. HIEN THI \n");
    printf("5. THOAT\n");
    printf("Nhap lua chon cua ban : ");
}

int main() {
    int choice;
    Stack* UNDO = createStack(100);
    Stack* REDO = createStack(100);
    Document* text = createQueue(100);
    do {
        printMenu();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: {
                char x[100];
                printf("Nhap ki tu: ");
                fgets(x, 100, stdin);
                x[strcspn(x, "\n")] = '\0';

                Op op;
                strcpy(op.Action, "INSERT");
                strcpy(op.Value, x);

                push(UNDO, op);
                enqueue(text, op);
                break;
            }
            case 2: {
                if (!isEmpty(UNDO)) {
                    Op last = pop(UNDO);
                    push(REDO, last);
                    if (text->rear >= 0) {
                        text->rear--;
                    }
                } else {
                    printf("Khong co gi de thao tac\n");
                }
                break;
            }
            case 3: {
                if (!isEmpty(REDO)) {
                    Op redo = pop(REDO);
                    push(UNDO, redo);
                    enqueue(text, redo);
                } else {
                    printf("Khong co gi de thao tac \n");
                }
                break;
            }
            case 4:
                displayQueue(text);
                break;
        }
    } while (choice != 5);
    return 0;
}
