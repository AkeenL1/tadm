//
// Created by Akeen Lewis on 3/1/25.
//
/*
A common problem for compilers and text editors is determining whether
the parentheses in a string are balanced and properly nested. For example, the
string ((())())() contains properly nested pairs of parentheses, while the strings
)()( and ()) do not.
Give an algorithm that returns true if a string contains
properly nested and balanced parentheses, and false if otherwise. For full credit,
identify the position of the first offending parenthesis if the string is not properly
nested and balanced.
 */
// I assume it will never overflow

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
# define MAX_SIZE 1000000
struct stack {
  int data[MAX_SIZE];
  int top;
};

void init(struct stack *s){
  s->top = -1;
}

void push(struct stack *s, int x){
  s->top++;
  s->data[s->top] = x;
}

int pop(struct stack *s){
  int x = s -> data[s->top];
  s->top--;
  return x;
}

bool isEmpty(struct stack *s){
  return s->top == -1;
}

int main() {
  struct stack s;
  init(&s);

  char input[50];
  scanf("%s", input);
  int len = strlen(input);

  for(int i = 0;i<len;i++){
    if(input[i] == '('){
     push(&s, i);
    }else {
      if(isEmpty(&s)){
        printf("False %d", i);
        return 0;
      }
      pop(&s);
    }
  }
  if(isEmpty(&s)){
    printf("True");
  }else{
    // if there's leftover parenthesis 0 is always the first offender
    printf("False 0");
  }
  return 0;
}