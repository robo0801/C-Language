#include<stdio.h>
/*

8
1 3 -1 -3 5 3 6 7
3

�ִ밪 7
*/

int main(){
    int w=0,len=0,Max = -10000;
    int a[100]={0};
    printf("â ���̸� �Է��ϼ���. :");scanf("%d",&len);
    printf("â �迭�� �Է��ϼ���: ");
    for(int i=1;i<=len;i++){ scanf("%d",&a[i]);  } //â�� �迭 �� �Է� �ޱ�
    printf("������ �Է��ϼ���. :");scanf("%d",&w);  //���� �Է�
    for(int i=1;i<=len-w+1;i++){    //���� Ƚ�� ��ŭ �ݺ��ϱ�
        Max = -10000;       // �ִ밪 ����
        for(int j=1;j<=len;j++){  //���� �迭 ���
            if(j == i){ printf("[%d ",a[j]); }
            else if (j == i+w-1){ printf("%d] ",a[j]); }
            else{ printf("%d ",a[j]); }
        }
        for(int j=i;j<i+w;j++){   // �������� �ִ밪 �� ã�� ����
            if(a[j]>=Max){ Max = a[j]; }//�ִ밪
        } printf(": %d\n",Max);
    }
}
