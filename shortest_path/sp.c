#include <stdio.h>
#include <limits.h>

#define V 9

int minDist(int dist[], int sptSet[]) {
    int min = INT_MAX;
    int min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index; 
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    int sptSet[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }
    dist[src] = 0;
    for (int i = 0; i < V - 1; i++) {
        int u = minDist(dist, sptSet);
        sptSet[u] = 1;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] &&  /* It is not visited */
                graph[u][v] &&  /* A path exists */
                dist[u] != INT_MAX && /* The distance is finite */
                dist[u] + graph[u][v] < dist[v]) { /* The distance is shorter */
                    dist[v] = dist[u] + graph[u][v]; /* The distance is updated */
                    printf("u-v: %d %d\n", u, v);
                }
    }
    for (int i = 0; i < V; i++)
        printf("%d: %d\n", i, dist[i]);
}

int main() {
   int graph[V][V] = {
       { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
       { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
       { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
       { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
       { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
       { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
       { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
       { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
       { 0, 0, 2, 0, 0, 0, 6, 7, 0 }
   };
   dijkstra(graph, 0);
   return 0;
}
