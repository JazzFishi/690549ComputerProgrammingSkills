#include <stdio.h>
int main(){
  int n;
  scanf("%d" , &n);
  int x;
  scanf("%d" ,&x);
  int min = x;
  int max = x;
  for ( int i = 1 ; i < n ; i++){
    scanf("%d" , &x);
    if ( x < min) { min = x;}
    if ( x > max) { max = x;}
  }
  printf("%d\n" , min);
  printf("%d\n" , max);
}