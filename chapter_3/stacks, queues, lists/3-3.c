//
// Created by Akeen Lewis on 3/1/25.
//
/*
* Give an algorithm to reverse the direction of a given singly linked list.
* In other words, after the reversal all pointers should now point backwards.
* Your algorithm should take linear time.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node{
  int data;
  struct node *next;
};

void init(struct node *head){
  srand(time(NULL));
  head -> data = rand() % 100;
  for( int i = 0; i < 9; i++){
    struct node *temp = malloc(sizeof(struct node));
    temp->data = rand() % 100;
    temp->next = NULL;
    head -> next = temp;
    head = head -> next;
  }
}

void print(struct node *head) {
  struct node *temp = head;
  while(temp != NULL){
    printf("%d -> ", temp -> data);
    temp = temp -> next;
  }
}

int main(){
  struct node *head = malloc(sizeof(struct node));
  init(head);
  print(head);
  printf("NULL \n");
  struct node *prev = NULL;
  struct node *next = head -> next;
  while (next != NULL) {
    head -> next = prev;
    prev = head;
    head = next;
    next = head -> next;
  }
  head -> next = prev;
  print(head);
  printf("NULL \n");
  return 0;
}
