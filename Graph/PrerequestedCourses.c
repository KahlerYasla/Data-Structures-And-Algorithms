#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph
{
    int numVertices;
    Node **adjLists;
    int *indegree;
} Graph;

Node *createNode(int v);
Graph *createGraph(int vertices);
void addEdge(Graph *graph, int s, int d);
void printGraph(Graph *graph);
void findSemesters(Graph *graph);

int main()
{
    int N, E, s, d;
    printf("Ders sayisini girin: ");
    scanf("%d", &N);
    printf("On sart sayisini girin: ");
    scanf("%d", &E);

    Graph *graph = createGraph(N);

    printf("\nOn sartlari girin (s, d): \n");
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d", &s, &d);
        addEdge(graph, s - 1, d - 1);
    }

    // print indegrees of vertices
    printf("\nIndegreeler:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", graph->indegree[i]);
    }
    printf("\n");

    printf("\nGraf:\n");
    printGraph(graph);

    printf("\nDersleri ve donemleri:\n");
    findSemesters(graph);

    return 0;
}

Node *createNode(int v)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = (Node **)malloc(vertices * sizeof(Node *));
    graph->indegree = (int *)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->indegree[i] = 0;
    }

    return graph;
}

void addEdge(Graph *graph, int source, int destination)
{
    Node *newNode = createNode(destination);
    newNode->next = graph->adjLists[source];
    graph->adjLists[source] = newNode;
    graph->indegree[destination]++;
}

void printGraph(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        Node *temp = graph->adjLists[i];
        printf("Course-%d -> ", i + 1);
        while (temp != NULL)
        {
            printf("Course-%d ", temp->vertex + 1);
            temp = temp->next;
        }
        printf("\n");
    }
}

void findSemesters(Graph *graph)
{
    int semester = 1;
    int courses[graph->numVertices];
    int courseCount = 0;
    int visited[graph->numVertices];
    for (int i = 0; i < graph->numVertices; i++)
    {
        visited[i] = 0;
    }

    for (int i = 0; i < graph->numVertices; i++)
    {
        if (graph->indegree[i] == 0)
        {
            courses[courseCount++] = i;
            visited[i] = 1;
        }
    }

    while (courseCount != graph->numVertices)
    {
        printf("Donem-%d: ", semester);
        for (int i = 0; i < courseCount; i++)
        {
            printf("Course-%d ", courses[i] + 1);
        }
        printf("dersleri bitmistir.\n");

        for (int i = 0; i < courseCount; i++)
        {
            Node *temp = graph->adjLists[courses[i]];
            while (temp != NULL)
            {
                if (visited[temp->vertex] == 0)
                {
                    graph->indegree[temp->vertex]--;
                    if (graph->indegree[temp->vertex] == 0)
                    {
                        courses[courseCount++] = temp->vertex;
                        visited[temp->vertex] = 1;
                    }
                }
                temp = temp->next;
            }
        }
        semester++;
    }
    printf("Donem-%d: ", semester);
    for (int i = 0; i < courseCount; i++)
    {
        printf("Course-%d ", courses[i] + 1);
    }
    printf("dersleri bitmistir.\n");

    printf("ogrenci derslerini en az %d donemde bitirebilir.\n", semester);
}
