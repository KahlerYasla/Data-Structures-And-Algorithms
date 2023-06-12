#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void addEdge(Node *adjacencyList[], int u, int v)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = adjacencyList[u];
    adjacencyList[u] = newNode;
}

void printSemesterCourses(int semester, int courses[], int courseCount)
{
    printf("Donem-%d: ", semester);
    for (int i = 0; i < courseCount; i++)
    {
        printf("Course-%d ", courses[i] + 1);
    }
    printf("\n");
}

int main()
{
    int N, E;
    printf("Ders sayisini girin (N): ");
    scanf("%d", &N);
    printf("on sart sayisini girin (E): ");
    scanf("%d", &E);

    Node *adjacencyList[N];
    for (int i = 0; i < N; i++)
    {
        adjacencyList[i] = NULL;
    }

    printf("on sartlari girin (u v seklinde, her on sart icin yeni satir):\n");
    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(adjacencyList, u - 1, v - 1);
    }

    int indegree[N];
    for (int i = 0; i < N; i++)
    {
        indegree[i] = 0;
    }

    for (int i = 0; i < N; i++)
    {
        Node *temp = adjacencyList[i];
        while (temp != NULL)
        {
            indegree[temp->data]++;
            temp = temp->next;
        }
    }

    int semester = 1;
    int remainingCourses = N;

    while (remainingCourses > 0)
    {
        int currentSemesterCourses[N];
        int courseCount = 0;

        for (int i = 0; i < N; i++)
        {
            if (indegree[i] == 0)
            {
                currentSemesterCourses[courseCount++] = i;
                indegree[i] = -1;
                remainingCourses--;

                Node *temp = adjacencyList[i];
                while (temp != NULL)
                {
                    indegree[temp->data]--;
                    temp = temp->next;
                }
            }
        }

        printSemesterCourses(semester, currentSemesterCourses, courseCount);
        semester++;
    }

    printf("ogrenci bolumu %d donemde bitirir.\n", semester - 1);

    return 0;
}