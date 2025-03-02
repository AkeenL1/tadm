//
// Created by Akeen Lewis on 3/1/25.
//

/*
Give an algorithm that takes a string S consisting of opening and closing
parentheses, say ) () (()) () () )) () )))(, and finds the length of the longest balanced
parentheses in S, which is 12 in the example above. (Hint: The solution is not
necessarily a contiguous run of parenthesis from S.)
*/

// ((())())() - 10
// )()( - 2
// ()) - 2
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
struct stack {
  int data[100];
  int top;
};

void init(struct stack *s) {
  s -> top = -1;
};

void push(struct stack *s, int x){
    s -> top++;
    s -> data[s -> top] = x;
}

void pop(struct stack *s) {
  s -> top--;
}

bool isEmpty(struct stack *s) {
  return s->top == -1;
}

int main() {
  struct stack s;
  init(&s);

  char in[100];
  scanf("%s", in);
  int count = 0;
  for(int i = 0;i<strlen(in);i++){
    if(in[i] == '('){
      push(&s, in[i]);
    }else {
      if (!isEmpty(&s)) {
        pop(&s);
        count += 2;
      }
    }
  }
  printf("%d", count);
  return 0;
}