/*
5
1 3 5 7 9
9

5
1 3 5 7 9
10
*/

#include<stdio.h>

int arr[100] ={};
int N;


void BS(int s, int f){
    if(s>f){
        printf("number not found\n");
        return;
    }

    int nMid = (s+f)/2;
    if( arr[nMid] == N )
    {
        printf("%d ",nMid);
        return;            //타겟을 찾았다.
    }
    else if( N < arr[nMid] )
    {
        BS(s,nMid-1);
    }
    else{
        BS(nMid+1,f);
    }
}

int main(){
    int n,temp=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
    }
    scanf("%d",&N);
    BS(1,n);
}
