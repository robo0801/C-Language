#include<stdio.h>

int gcd1(int x,int y){
    while(1){
        int temp=0;
        while(x>=y){
            x-=y;
        }
        if(x==0){
            printf("%d",y);
            break;
        }
        temp = x;x=y;y=temp;
        if(y == 1){
            printf("1");
            break;
        }
    }
}

int gcd2(int x,int y){
    int temp;
    while(y != 1 && y != 0){
        temp = y;
        y = x%y;
        x = temp;
    }
    if(y==1){
        printf("1");
    }
    if(y==0){
        printf("%d",temp);
    }
}

void gcd3(int x,int y){
    if(y==1){
        printf("1");
        return;
    }
    if(x%y==0){
        printf("%d",y);
        return;
    }
    gcd3(y,x%y);
}

int main(){
    int x,y;
    scanf("%d %d",&x,&y);
    (x>=y)?gcd1(x,y):gcd1(y,x);
    printf("\n");
    (x>=y)?gcd2(x,y):gcd2(y,x);
    printf("\n");
    (x>=y)?gcd3(x,y):gcd3(y,x);
}
