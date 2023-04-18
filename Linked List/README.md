# Detailed Explanation of C Code

This C code is a program that simulates a game with three wheels (represented by linked lists), each containing a set of numbers. The goal of the game is to find a common number between the three wheels and then rotate the wheels to align the common number at the same position in each wheel.

The code uses singly linked lists to represent the wheels and contains the following struct and functions:

## Struct

1. `Node`: Represents a node in the singly linked list with the following members:
   - `data` (int): The value of the node.
   - `next` (Node*): Pointer to the next node in the list.

## Functions

1. `insert(Node **head, int data)`: Inserts a new node with the given data at the beginning of the list pointed to by head.

2. `printList(Node *head)`: Prints the elements of the list pointed to by head.

3. `findCommon(Node *head1, Node *head2, Node *head3, int *pos1, int *pos2, int *pos3)`: Finds the first common number between the three lists pointed to by head1, head2, and head3, and stores the positions of the common number in the respective lists in pos1, pos2, and pos3. Returns the common number if found, or -1 if not found.

4. `rotate(Node **head, int steps)`: Rotates the list pointed to by head by the given number of steps. If steps is positive, the rotation is clockwise; if steps is negative, the rotation is counterclockwise.

5. `main()`: The main function of the program, which performs the following steps:
   a. Reads the values of N and M from the user, where N is the maximum number in the wheels and M is the number of elements in each wheel.
   b. Initializes the wheels with random numbers, ensuring that each number (except the common number) appears at most twice across all three wheels.
   c. Rotates the wheels randomly.
   d. Prints the initial state of the wheels.
   e. Finds the common number and its positions in the wheels.
   f. Calculates the number of steps required to align the common number in each wheel.
   g. Rotates the wheels to align the common number.
   h. Prints the final state of the wheels.
   i. Frees the memory allocated for the wheels.

In this program, the wheels are represented as singly linked lists, and the common number is found using a brute-force approach by iterating through all possible combinations of elements from the three lists. The rotation of the wheels is performed by updating the head pointers and connecting the tail of the list to the original head. The program demonstrates the use of linked lists, pointer manipulation, and basic control structures in C.