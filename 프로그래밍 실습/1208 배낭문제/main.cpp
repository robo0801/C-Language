#include <stdio.h>
#define N 100
/*
4 5
1 500
2 300
3 900
4 800


*/

int main() {
    int n,MaxW=0;
    int Weight[N]={0},Price[N]={0};
    float PPW[N]={0},Temp=0,ans=0;
    int Tmp=0;
    char Name[N]={},Tp;

    scanf("%d %d",&n,&MaxW);
    for(int i=0;i<n;i++){ //�Է� �ް� ������ ���ϱ�
        Name[i] = 'a'+i;
        scanf("%d %d",&Weight[i],&Price[i]);
        PPW[i]=(float)(Price[i])/(float)(Weight[i]);
    }
    //������ ���� �����ϱ�
    for(int i=0;i<n-1;i++){
        for(int j=i;j<n;j++){
            if(PPW[i]<PPW[j]){
                Temp = PPW[i];PPW[i] = PPW[j];PPW[j] = Temp;
                Tmp = Weight[i];Weight[i] = Weight[j];Weight[j] = Tmp;
                Tmp = Price[i];Price[i] = Price[j];Price[j] = Tmp;
                Tp = Name[i];Name[i] = Name[j];Name[j] = Tp;
            }
        }
    }
    // ������ ���� �� ���� ����Ͽ� ä�� �ִ´�
    int i=0;
    while(MaxW){//�̸��� ����� ���Ը� ����Ѵ�.
        if(Weight[i]<=MaxW){
            printf("%c %d\n",Name[i],Weight[i]);
            ans+=Price[i];
            MaxW-=Weight[i];
        }
        else{
            printf("%c %d\n",Name[i],MaxW);
            ans+=PPW[i]*MaxW;
            MaxW=0;
            break;
        }
        i+=1;
    }
    printf("%.2f\n",ans);
}
