//
// Created by Akeen Lewis on 2/23/25.
//

/*
* Implement the two TSP heuristics of Section 1.1 (page 5).
* Which of them gives better solutions in practice?
* Can you devise a heuristic that works better than both of them?
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>

struct point {
  int x;
  int y;
  int visited;
  struct point *connections;
  int connections_count;
};

struct graph {
  struct point *points;
  int n;
};

struct graph init_graph(int n) {
  struct graph g = {malloc(n * sizeof(struct point)), n};
  for (int i = 0; i < n; i++) {
    struct point p = {rand() % 1000, rand() % 1000, 0, NULL, 0};
    g.points[i] = p;

  }
  return g;
}

int calculate_distance(struct point *p, struct point *p_j) {
  int dx = p_j->x - p->x;
  int dy = p_j->y - p->y;
  return sqrt(dx * dx + dy * dy);
}

void nearest_neighbor(struct graph g) {
  // pick and visit an inital point from g
  printf("Nearest Neightbor\n");
  int count = 0;
  // p = p0
  struct graph g_copy = g;
  printf("Starting at %d %d\n", g_copy.points[0].x, g_copy.points[0].y);
  struct point *p = &g_copy.points[0];
  p->visited = 1;
  int i = 0;
  // while there are still unvisited points
  while (i < g.n) {
    // iterate i
    i = i + 1;
    // select pi to be the closest unvisted point to pi-1
    int min_distance = 1000000000;
    int min_index = 0;
    for (int j = 0;j<g.n;j++) {
      if (g_copy.points[j].visited == 0) {
        struct point *p_j = &g_copy.points[j];
        int distance = calculate_distance(p, p_j);
        if (distance < min_distance) {
          min_distance = distance;
          min_index = j;
        }
      }
    }
    // visit pi
    printf("Visiting %d %d\n", g_copy.points[min_index].x, g_copy.points[min_index].y);
    count = count + 1;
    g_copy.points[min_index].visited = 1;
    p = &g_copy.points[min_index];
  }
  // return to p0 from pn-1
  p = &g_copy.points[0];
  printf("Returning to %d %d\n", p->x, p->y);
  printf("Visited %d points\n", count);
}

void closest_pair(struct graph g) {
  // let n be number of points in graph
  int n = g.n;
  // for i = 1 to n -1 do
  for (int i = 0; i < n - 1 ;i++) {
    // d = infinite
    int d = 1000000000;
    // for each pair of endpoints (s,t) from distinct vertex chain
    struct point *sm = NULL;
    struct point *tm = NULL;
    for (int j = i ; j < n - 1; j++) {
      for (int k = j + 1; k < n; k++) {
        // if distance(s,t) <= d then sm = s, tm = t and d = dist s,t
        int distinct = 1;
        if (g.points[j].connections != NULL) {
          for (int l = 0; l < g.points[j].connections_count; l++) {
            if (&g.points[k] == &g.points[j].connections[l]) {
              distinct = 0;
            }
          }
        }

        if (calculate_distance(&g.points[j], &g.points[k]) < d && distinct == 1) {
          d = calculate_distance(&g.points[j], &g.points[k]);
          sm = &g.points[j];
          tm = &g.points[k];
        }
      }
    }
    if (sm->connections == NULL) {
      sm -> connections = malloc(sizeof(struct point));
    }
    sm -> connections[0] = *tm;
    sm -> connections_count++;
    if (tm->connections == NULL) {
      tm -> connections = malloc(sizeof(struct point));
    }
    tm -> connections[0] = *sm;
    tm -> connections_count++;
    printf("Connected %d %d and %d %d\n", sm->x, sm->y, tm->x, tm->y);
  }
}

int main(void){
  srand(time(NULL));
  // random number between 500 and 1000
  int random_number = rand() % (1000 - 500 + 100) + 500;
  // init graph of points
  struct graph g;
  g = init_graph(random_number);
  //print out graph points
  printf("Graph:\n");
  for (int i = 0; i < random_number; i++) {
    printf("%d %d\n", g.points[i].x, g.points[i].y);
  }
  // start time
  struct timeval start, end;

  gettimeofday(&start, NULL);
  // run nearest neighbor on points
  nearest_neighbor(g);
  // print time one
  gettimeofday(&end, NULL);

  long seconds = end.tv_sec - start.tv_sec;
  long microseocnds = end.tv_usec - start.tv_usec;
  long nnmilliseconds = seconds * 1000 + microseocnds / 1000;
  // printf("Nearest Neighbor Time: %ld ms\n", nnmilliseconds);
  // start time
  gettimeofday(&start, NULL);
  // run closest pair on points
  closest_pair(g);
  // end time
  gettimeofday(&end, NULL);
  // print time two
  seconds = end.tv_sec - start.tv_sec;
  microseocnds = end.tv_usec - start.tv_usec;
  long cpmilliseconds = seconds * 1000 + microseocnds / 1000;
  printf("Closest Pair Time: %ld ms\n", cpmilliseconds);
  // compare
  printf("Nearest Neighbor Time: %ld ms\n", nnmilliseconds);
  // is there a better option


  // print the random number
  printf("%d\n", random_number);
  return 0;
}
