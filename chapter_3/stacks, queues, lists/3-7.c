//
// Created by Akeen Lewis on 3/2/25.
//
/*
*Work out the details of supporting constant-time deletion from a singly
linked list as per the footnote from page 79, ideally to an actual implementation.
Support the other operations as efficiently as possible.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct node {
  int data;
  struct node *next;
};

void init(struct node *head){
  for(int i = 0;i<9;i++){
    struct node *temp = malloc(sizeof(struct node));
    temp->data = rand() % 100;
    temp->next = NULL;
    head->next = temp;
    head = head->next;
  }
  struct node *sentinel = malloc(sizeof(struct node));
  sentinel->data = -1;
  sentinel->next = NULL;
  head->next = sentinel;
}

void print(struct node *head){
  while(head != NULL){
    printf("%d ", head->data);
    head = head->next;
  }
  printf("\n");
}

struct node* pick(struct node *head, int num) {
  int count = 0;
  while (head != NULL) {
    if (count == num) {
      return head;
    }
    head = head->next;
    count++;
  }
}

void delete(struct node *node){
  struct node *temp = node->next;
  node -> data = temp -> data;
  if (temp->next == NULL) {
    node -> next = NULL;
  }else {
    node -> next = temp->next;
  }
  free(temp);
}

int main(){
  srand(time(NULL));

  struct node *head = malloc(sizeof(struct node));
  head->data = rand() % 100;
  head->next = NULL;
  init(head);
  print(head);
  struct node *out = pick(head, 9);
  printf("Deleting %d\n", out -> data);
  delete(out);
  print(head);
}