#include<stdio.h>
#include<string.h>
/*
the quick brown fox jumps over the lazy dog
vtz ud xnm xugm itr pyy jttk gmv xt otgm xt xnm puk ti xnm fprxq
xnm ceuob lrtzv ita hegfd tsmr xnm ypwq ktj
frtjrpgguvj otvxmdxd prm iev prmvx xnmq
*/

char Key[26]={};

bool FigKey(char *Sen,char *KeySen){
    char KT[26]={};
    int p=0;
    for(int i=0;i<strlen(Sen);i++){
        p=Sen[i]-'a';
        if(Sen[i]==' ' || Sen[i]=='\n'){ continue; } // �����̰ų� �����̸� ����
        else if(KT[p] == '\0'){ KT[p] = KeySen[i]; } // �� ���ĺ��� �ϳ��� ������ �Ǵ�
        else if(KT[p] == KeySen[i]){ continue; } //��ġ�� ����
        else{ return false; } //���� �ٸ����ڰ� ���� �濡 ���� key ������ �ƴ� ����
    }
    for(int i=0;i<26;i++){ Key[i]=KT[i]; } // �� ���� ���� �迭�� �־��ֱ�
    return true;
}

int main(){
    char KeySen[80]={},Sen[100][80]={};
    printf("��ȣ Ű ������ �Է��ϼ���. >> "); // Ű ���� �Է�
    fgets(KeySen,80,stdin);
    int cnt=0,k=-1;

    while(true){
        printf("��ȣȭ�� ������ �Է��ϼ��� >> ");
        fgets(Sen[cnt],80,stdin); //��ȣȭ Ű ���� �����ֱ�
        if(Sen[cnt][0] == '\n'){ break; } // ������ ������ �����Է� ��
        if(strlen(KeySen) == strlen(Sen[cnt])){ //Ű������ ��ȣȭ�� ���ڿ� ���̿� ������ ����
            if(FigKey(Sen[cnt],KeySen)){ k=cnt; } //��ȣ Ű ���ϱ�
        }cnt+=1;
    }

    if(k == -1){ printf("No Solution\n"); } //���� ��ȣ Ű�� ������ ���
    else {
        for(int i=0;i<cnt;i++,printf("\n")){
            for(int j=0;j<strlen(Sen[i]);j++){ // ��ȣȭ �ؼ� ���
                if(Sen[i][j]==' ' || Sen[i][j] == '\n' ){ printf(" "); }
                else{
                    k = Sen[i][j]-'a';
                    printf("%c",Key[k]);
                }
            }
        }
    }
}
