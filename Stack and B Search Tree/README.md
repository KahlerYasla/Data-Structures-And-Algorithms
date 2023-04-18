# Fruits Game Simulation

This C code is a program that simulates a game where a player shoots fruits hanging from a tree. Each fruit has a weight and a hold value, which represents how much force is needed to knock it down. The player shoots at the fruits with a certain power, and if the power is enough to overcome the hold value, the fruit falls into a bucket. The game continues until the bucket is full.

The code uses a binary search tree (BST) to store the fruits, and a stack to store the fruits in the bucket.

## Structs

### Stack

Represents a stack data structure with the following members:

- `top` (int): The index of the top element in the stack.
- `capacity` (int): The maximum number of elements the stack can hold.
- `array` (int*): Pointer to an array of integers, which stores the elements in the stack.

### Node

Represents a node in the binary search tree with the following members:

- `value` (int): The weight of the fruit.
- `hold` (int): The hold value of the fruit.
- `left` (Node*): Pointer to the left child node.
- `right` (Node*): Pointer to the right child node.

## Functions

1. `createStack(int capacity)`: Creates a new stack with the given capacity, initializes its members, and returns a pointer to it.
2. `is_empty(Stack *stack)`: Checks if the given stack is empty, and returns 1 if it is, 0 otherwise.
3. `push(Stack *stack, int value)`: Pushes the given value onto the stack. If the stack is full, it prints "Stack overflow." and returns.
4. `pop(Stack *stack)`: Pops the top element from the stack and returns it. If the stack is empty, it prints "Stack underflow." and returns -1.
5. `createNode(int value, int hold)`: Creates a new BST node with the given value and hold, initializes its members, and returns a pointer to it.
6. `insertNode(Node *root, int value, int hold)`: Inserts a new node with the given value and hold into the BST rooted at the given root. If the value already exists in the tree, the hold is incremented by the given hold.
7. `findMinValueNode(Node *root)`: Finds the node with the minimum value in the BST rooted at the given root, and returns a pointer to it.
8. `deleteNode(Node *root, int value)`: Deletes the node with the given value from the BST rooted at the given root, and returns the root of the modified tree.
9. `printInorder(Node *root)`: Performs an inorder traversal of the BST rooted at the given root, and prints the values and holds of the nodes.
10. `main()`: The main function of the program, which performs the following steps:
    a. Reads the maximum fruit weight (N) and the number of fruits (M) from the user.
    b. Initializes the BST and the bucket stack.
    c. Inserts M random fruits into the BST, with random weights between 1 and N, and random holds between 1 and N/2.
    d. Prints the initial tree.
    e. Repeatedly reads the fruit value (k) and shot power (p) from the user, updates the BST, and adds the shot fruits to the bucket, until the bucket is full.
    f. Prints the contents of the bucket.
