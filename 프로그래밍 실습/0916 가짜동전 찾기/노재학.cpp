/*
�Է� ����
13
1 1 1 1 1 1 1 1 0 1 1 1 1
9

15
1 1 1 0 1 1 1 1 1 1 1 1 1 1 1
4

14
1 1 1 1 0 1 1 1 1 1 1 1 1 1 1
5
*/


//3�� Ž��
#include<stdio.h>
#define MAX 100
//��� �� ���� ���� ������� ���� ����
int arr[MAX]={0};

void fi(int s,int f){
    int m1,m2;
    printf("%d %d\n",s,f);
    if((f-s)<=2){ //���� ���� 2���ϸ� return
        printf("%d",((arr[s]>arr[s-1]) > (arr[f]>arr[f-1]) )? f : s );
        return;
    }

    //m1 �� ���� m2 �� ���� �迭���� 3���� 1���� 3���� 2����
    if( (f-s)%3==0 ){ m1=s-1+(f-s)/3; m2=s-1+2*(f-s)/3; }
    else if( (f-s)%3==1 ){ m1=s-1+(f-s)/3+1; m2=s-1+2*(f-s)/3+2; }
    else if( (f-s)%3==2 ){ m1=s-1+(f-s+1)/3; m2=s-1+2*(f-s+1)/3; }
    printf(":%d %d\n",m1,m2);
    // �� �� �ϱ� ������ �Լ� ȣ�� ������ �� ���ߴ� �� �Լ� ȣ��
    if((arr[m1]-arr[s-1]) > (arr[m2]-arr[m1]) ) {printf(">"); fi(m1+1,m2); }
    else if( (arr[m1]-arr[s-1]) < (arr[m2]-arr[m1]) ) {printf("<"); fi(s,m1); }
    else if( (arr[m1]-arr[s-1]) == (arr[m2]-arr[m1]) ) {printf("="); fi(m2+1,f); }
}

int main(){
    int n,sum=0;

    scanf("%d",&n);
    for(int i=1;i<=n;i++){ //���� ���� ����
        scanf("%d",&sum);
        arr[i]=arr[i-1]+sum;
    }
    fi(1,n); //��� �Լ� ȣ�� ù��° �� ������ ��
}
