//
// Created by Akeen Lewis on 3/1/25.
//

/*
Design a stack S that supports S.push(x), S.pop(), and S.findmin(), which
returns the minimum element of S. All operations should run in constant time.
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
struct node {
  int data;
  struct node *ptr;
};

struct stack{
  // just doing this supports push & pop
  struct node data[100];
  int top;
  // to support findmin
  struct node *min;
};

void init(struct stack *s){
  s->top = -1;

  struct node *temp = malloc(sizeof(struct node));
  temp->data = 9999;
  s->min = temp; // just some large value
}

void push(struct stack *s, int data){
  struct node *temp = malloc(sizeof(struct node));
  temp->data = data;
  if (s->min->data == 9999) {
    s->min = temp;
  } else if (s->min->data >= data){
    temp->ptr = s->min;
    s->min = temp;
  }
  s->top++;
  s->data[s->top] = *temp;
}

int pop(struct stack *s){
  struct node *out = &s->data[s->top];
  if (out->data == s->min->data) {
    s->min = s->min->ptr;
  }
  s->top--;
  return out->data;
}

int findMin(struct stack *s) {
  return s->min->data;
}

int main(){
  struct stack *s = malloc(sizeof(struct stack));
  srand(time(NULL));
  init(s);
  for (int i = 0;i<10;i++) {
    int r = rand() % 100;
    push(s, r);
    printf("%d ",r);
  }
  printf("\n");
  for (int i = 0;i<10;i++) {
    printf("%d - MIN:", findMin(s));
    printf("%d - Popped\n", pop(s));
  }
  return 0;
}