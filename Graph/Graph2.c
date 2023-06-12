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
        addEdge(graph, s, d);
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

    // printf("\nDersleri ve donemleri:\n");
    // findSemesters(graph);

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

void addEdge(Graph *graph, int s, int d)
{
    graph->indegree[d - 1]++;

    Node *newNodeDestination = createNode(d - 1);
    Node *newNodeSource = createNode(s - 1);

    if (graph->adjLists[s - 1] == NULL)
    {
        graph->adjLists[s - 1] = newNodeSource;
    }
    else
    {
        for (int i = 0; i < graph->numVertices; i++)
        {
            if (graph->adjLists[i - 1]->next == NULL)
            {
                continue;
            }
            if (graph->adjLists[i - 1]->next->vertex == s - 1)
            {
                graph->adjLists[i - 1]->next = newNodeSource;
            }
        }
    }

    if (graph->adjLists[d - 1] == NULL)
    {
        graph->adjLists[d - 1] = newNodeDestination;
    }
    else
    {
        for (int i = 0; i < graph->numVertices; i++)
        {
            if (graph->adjLists[i - 1]->next == NULL)
            {
                continue;
            }
            if (graph->adjLists[i - 1]->next->vertex == d - 1)
            {
                graph->adjLists[i - 1]->next = newNodeDestination;
            }
        }
    }
}

void printGraph(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        Node *temp = graph->adjLists[i];
        printf("%d: ", i + 1);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
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
        printf("\n");

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
    printf("\n");

    printf("ogrenci derslerini en az %d donemde bitirebilir.\n", semester);
}