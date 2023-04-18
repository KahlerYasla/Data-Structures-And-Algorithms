#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void insert(Node **head, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

void printList(Node *head)
{
    Node *temp = head;
    printf("*|");
    while (temp != NULL)
    {
        printf(" %d", temp->data);
        temp = temp->next;
    }
    printf(" |*\n");
}

int findCommon(Node *head1, Node *head2, Node *head3, int *pos1, int *pos2, int *pos3)
{
    Node *temp1 = head1;
    Node *temp2;
    Node *temp3;
    *pos1 = 1;
    while (temp1 != NULL)
    {
        temp2 = head2;
        *pos2 = 1;
        while (temp2 != NULL)
        {
            if (temp1->data == temp2->data)
            {
                temp3 = head3;
                *pos3 = 1;
                while (temp3 != NULL)
                {
                    if (temp1->data == temp3->data)
                    {
                        return temp1->data;
                    }
                    temp3 = temp3->next;
                    (*pos3)++;
                }
            }
            temp2 = temp2->next;
            (*pos2)++;
        }
        temp1 = temp1->next;
        (*pos1)++;
    }
    return -1;
}

void rotate(Node **head, int steps)
{
    if (*head == NULL || steps == 0)
    {
        return;
    }

    Node *temp = *head;
    int len = 1;
    while (temp->next != NULL)
    {
        temp = temp->next;
        len++;
    }

    steps %= len;
    printf("%d \n", steps);
    if (steps < 0)
    {
        steps += len;
    }
    else if (steps == 0)
    {
        return;
    }

    temp->next = *head;
    temp = *head;
    int i;
    for (i = 0; i < len - steps - 1; i++)
    {
        temp = temp->next;
    }
    *head = temp->next;
    temp->next = NULL;
}

int main()
{
    srand(time(NULL));
    int N, M;
    int i, j;

    while (1)
    {
        printf("N ve M degerlerini giriniz (1 < M < N): ");
        scanf("%d %d", &N, &M);

        if (!(N <= 1 || M >= N))
        {
            break;
        }

        printf("Hatali giris yaptiniz. Lutfen tekrar deneyiniz.\n");
    }

    // linked listteki ortak sayı hariç her sayının 3 listede en fazla 2 tane olması için sayıların kaç tane olduğunu tutan dizi
    int count[N];
    for (i = 0; i < N; i++)
    {
        count[i] = 0;
    }

    int common = rand() % N + 1;
    Node *wheels[3] = {NULL, NULL, NULL};
    for (i = 0; i < 3; i++)
    {
        insert(&wheels[i], common);
        for (j = 1; j < M; j++)
        {
            int num;
            do
            {
                num = rand() % N + 1;
            } while (num == common);

            if (count[num] == 2)
            {
                j--;
                continue;
            }
            count[num]++;

            insert(&wheels[i], num);
        }
    }

    // listeleri karıştır
    for (i = 0; i < 3; i++)
    {
        int steps = rand() % 100;
        rotate(&wheels[i], steps);
    }

    printf("\ncarklarin karistirildiktan sonraki ilk Hali:\n");
    for (i = 0; i < 3; i++)
    {
        printList(wheels[i]);
    }

    int pos1, pos2, pos3;
    int foundCommon = findCommon(wheels[0], wheels[1], wheels[2], &pos1, &pos2, &pos3);
    printf("\nOrtak Sayi Bilinen: %d", common);
    printf("\nOrtak Sayi Bulunan: %d\n\n", foundCommon);
    printf("1.carktaki konumu: %d\n", pos1);
    printf("2.carktaki konumu: %d\n", pos2);
    printf("3.carktaki konumu: %d\n", pos3);

    int steps2 = pos1 - pos2;
    int steps3 = pos1 - pos3;
    printf("\n2.cark %s yonunde %d adim cevrilmeli\n", steps2 > 0 ? "saat" : "saatin ters", abs(steps2));
    printf("3.cark %s yonunde %d adim cevrilmeli\n", steps3 > 0 ? "saat" : "saatin ters", abs(steps3));

    rotate(&wheels[1], steps2);
    rotate(&wheels[2], steps3);

    printf("\nCarklarin Son Hali:\n");
    for (i = 0; i < 3; i++)
    {
        printList(wheels[i]);
    }

    // Free memory
    for (i = 0; i < 3; i++)
    {
        Node *temp = wheels[i];
        while (temp != NULL)
        {
            Node *nextNode = temp->next;
            free(temp);
            temp = nextNode;
        }
    }

    return 0;
}