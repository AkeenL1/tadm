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

struct point {
  int x;
  int y;
  int visited;
};

struct graph {
  struct point *points;
  int n;
};

struct graph init_graph(int n) {
  struct graph g = {malloc(n * sizeof(struct point)), n};
  for (int i = 0; i < n; i++) {
    struct point p = {rand() % 100, rand() % 100, 0};
    g.points[i] = p;

  }
  return g;
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
        int dx = p_j->x - p->x;
        int dy = p_j->y - p->y;
        int distance = sqrt(dx * dx + dy * dy);
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

int main(void){
  srand(time(NULL));
  // random number between 5 and 10
  int random_number = rand() % (10000 - 5000 + 1000) + 5000;
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
  long milliseconds = seconds * 1000 + microseocnds / 1000;
  printf("Time: %ld ms\n", milliseconds);
  // reset time
  // start time
  // run closest pair on points
  // end time
  // print time two
  // compare
  // is there a better option
  // print the random number
  printf("%d\n", random_number);
  return 0;
}
