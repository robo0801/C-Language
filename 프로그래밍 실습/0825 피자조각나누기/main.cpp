#include<stdio.h>

int N;

int f(int n){
    if(n==1) return 2;
    return f(n-1)+n;
}

int main(){
    scanf("%d",&N);
    printf("%d",f(N));
}
