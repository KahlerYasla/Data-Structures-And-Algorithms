#include <stdio.h>
#include <stdlib.h>

void addEdge(int v, int w, int **adjList, int *indegs)
{
    adjList[v][indegs[v]] = w;
    indegs[v]++;
}

int main()
{
    int N, E;
    printf("Ders sayisini giriniz: ");
    scanf("%d", &N);
    printf("On sart sayisini giriniz: ");
    scanf("%d", &E);

    int **adjMatrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        adjMatrix[i] = (int *)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }

    printf("On sartlari giriniz:\n");
    for (int i = 0; i < E; i++)
    {
        int v, w;
        scanf("%d %d", &v, &w);
        adjMatrix[v][w] = 1;
    }

    int **adjList = (int **)malloc(N * sizeof(int *));
    int *indegs = (int *)calloc(N, sizeof(int));
    for (int i = 0; i < N; i++)
    {
        int cnt = 0;
        for (int j = 0; j < N; j++)
        {
            if (adjMatrix[i][j] == 1)
            {
                cnt++;
            }
        }
        adjList[i] = (int *)malloc(cnt * sizeof(int));
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (adjMatrix[i][j] == 1)
            {
                addEdge(i, j, adjList, indegs);
            }
        }
    }

    int cnt = 0;
    int semester = 1;
    while (cnt < N)
    {
        int *queue = (int *)malloc(N * sizeof(int));
        int qcnt = 0;
        for (int i = 0; i < N; i++)
        {
            if (indegs[i] == 0)
            {
                queue[qcnt++] = i;
                indegs[i] = -1;
            }
        }

        printf("Donem-%d: ", semester);
        for (int i = 0; i < qcnt; i++)
        {
            int v = queue[i];
            printf("Course-%d ", v);
            cnt++;

            for (int j = 0; j < indegs[v]; j++)
            {
                int w = adjList[v][j];
                indegs[w]--;
            }
        }
        printf("\n");
        semester++;
        free(queue);
    }

    for (int i = 0; i < N; i++)
    {
        free(adjMatrix[i]);
        free(adjList[i]);
    }
    free(adjMatrix);
    free(adjList);
    free(indegs);

    return 0;
}