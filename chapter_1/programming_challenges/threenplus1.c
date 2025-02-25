//
// Created by Akeen Lewis on 2/24/25.
// https://onlinejudge.org/external/1/100.pdf
//
#include <stdio.h>

int algo(int n) {
  int count = 1;
  while (n != 1) {
    if (n % 2 == 0) {
      n = n / 2;
    } else {
      n = 3 * n + 1;
    }
    count++;
  }
  return count;
}

int main(){
  int a,b;
  scanf("%d %d",&a,&b);
  int max = algo(a);
  int out = a;
  for (int i = a + 1;i <= b;i++) {
    if (algo(i) > max) {
      max = algo(i);
      out = i;
    }
  }
  printf("%d %d %d\n",a,b,max);
  return 0;
}