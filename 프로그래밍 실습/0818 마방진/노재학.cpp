#include<stdio.h>
#include<stdlib.h>

int main(){
    int n=1,arr[100][100]={0};
    int i,j,k=0;
    // ������ ũ�� �Է� �ޱ�
    while(n!=0){
        printf("������ ũ�� �Է��ϼ���. Ȧ���� �Է� :");
        scanf("%d",&n);
        if(n%2==1) break;

    }
    if(n==0) return 0; // 0 �϶��� ����

    //������ �迭�� �� �ֱ�
    i=1;j=n/2+1;
    while(k!=n*n){
        k++;
        while(1){
            if(arr[i][j]==0){ // �迭�� ����� �� �� �ֱ�
                arr[i][j]=k;
                break;
            }
            else{ // ���� �迭�� ���ڰ� ���� �� �ٷ� �� �迭�� ��� �̵�
                j+=1;
                i+=2;
                if(i>n) i-=n;
                if(j>n) j-=n;
            }
        }
        // �� ���������� �̵�
        i-=1;j-=1;
        if(i==0) i+=n;
        if(j==0) j+=n;
    }

    // ���
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            printf("%2d ",arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
