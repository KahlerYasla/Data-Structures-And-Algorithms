#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//***Stack and its operations***
typedef struct Stack
{
    int top;
    int capacity;
    int *array;
} Stack;

Stack *createStack(int capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

int is_empty(Stack *stack)
{
    return stack->top == -1;
}

void push(Stack *stack, int value)
{
    if (stack->top == stack->capacity - 1)
    {
        printf("Stack overflow.\n");
        return;
    }
    stack->array[++stack->top] = value;
}

int pop(Stack *stack)
{
    if (is_empty(stack))
    {
        printf("Stack underflow.\n");
        return -1;
    }
    return stack->array[stack->top--];
}
//***End of stack and its operations***

typedef struct Node
{
    int value;
    int hold;
    struct Node *left;
    struct Node *right;
} Node;

// This function creates a new node with the given value and returns a pointer to it.
// The hold is initialized to 1.
// The left and right pointers are initialized to NULL.
// The function returns NULL if the memory allocation fails.
Node *createNode(int value, int hold)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->hold = hold;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// This function inserts a new node with the given value in the tree rooted at the given root.
// If the value already exists in the tree, the hold is incremented by 1.
// The function returns the root of the modified tree.
// The function returns NULL if the memory allocation fails.
// The function returns the root as it is if the value already exists in the tree.
Node *insertNode(Node *root, int value, int hold)
{
    if (root == NULL)
    {
        return createNode(value, hold);
    }
    if (value < root->value)
    {
        root->left = insertNode(root->left, value, hold);
    }
    else if (value > root->value)
    {
        root->right = insertNode(root->right, value, hold);
    }
    else if (value == root->value)
    {
        root->hold += hold;
    }
    return root;
}

Node *findMinValueNode(Node *root)
{
    Node *current = root;
    while (current && current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

// This function deletes a node with a given value from the tree. It returns the root of the modified tree.
// The function first searches for the node to be deleted. If the node is not found, it returns the root as it is.
// If the node is found, it is deleted. There are three cases when a node is found:
// 1. The node to be deleted is a leaf node: It simply removes the node from the tree.
// 2. The node to be deleted has only one child: It replaces the node to be deleted with its child.
// 3. The node to be deleted has two children: It replaces the node to be deleted with the minimum value node in its right subtree.
Node *deleteNode(Node *root, int value)
{
    if (root == NULL)
    {
        return root;
    }
    if (value < root->value)
    {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = deleteNode(root->right, value);
    }
    // If the value is same as root's value, then this is the node to be deleted
    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;

            return temp;
        }
        Node *temp = findMinValueNode(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

// Inorder traversal of the tree is used to print the tree in sorted order (ascending order) of the values.
// LRN (left, right, node) is used to print the tree in descending order of the values.
void printInorder(Node *root)
{
    if (root != NULL)
    {
        printInorder(root->left);
        printf("%d(%d) ", root->value, root->hold);
        printInorder(root->right);
    }
}

int main()
{
    int N, M, k, p;
    printf("Enter N (maximum fruit weight) and M (number of fruits): ");
    scanf("%d %d", &N, &M);

    srand(time(0));
    Node *root = NULL;
    Stack *bucket = createStack(M);

    // Insert M random values in the tree.
    // The hold of each node is initialized to a random value between 1 and N/2.
    // The hold of a node is decremented by p when a fruit with value k is shot.
    for (int i = 0; i < M; i++)
    {
        int value = rand() % N + 1;
        int hold = rand() % (N / 2) + 1;
        root = insertNode(root, value, hold);
    }

    printf("Initial tree:\n");
    printInorder(root);
    printf("\n");

    int bucket_index = 0;

    // The loop continues until the bucket is full.
    // The user enters the value of k and the power of the shot p.
    // The hold of the node with value k is decremented by p.
    // If the hold of the node becomes 0 or less, the node is deleted from the tree.
    // The value of k is added to the bucket.
    while (bucket_index < M)
    {
        printf("Enter k (fruit value) and p (shot power): ");
        scanf("%d %d", &k, &p);

        Node *current = root;
        while (current != NULL)
        {
            if (k == current->value)
            {
                current->hold -= p;
                if (current->hold <= 0)
                {
                    push(bucket, k);
                    root = deleteNode(root, k);
                }
                break;
            }
            else if (k < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        printf("Current tree:\n");
        printInorder(root);
        printf("\n");
    }

    // Print the contents of the bucket.
    printf("Bucket: ");
    while (!is_empty(bucket))
    {
        printf("%d ", pop(bucket));
    }
    printf("\n");

    return 0;
}