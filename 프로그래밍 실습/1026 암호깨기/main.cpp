#include<stdio.h>
#include<string.h>
/*
1
the quick brown fox jumps over the lazy dog
vtz ud xnm xugm itr pyy jttk gmv xt otgm xt xnm puk ti xnm fprxq
xnm ceuob lrtzv ita hegfd tsmr xnm ypwq ktj
frtjrpgguvj otvxmdxd prm iev prmvx xnmq

2
the quick brown fox jumps over the lazy dog
vtz ud xnm xugm itr pyy jttk gmv xt otgm xt xnm puk ti xnm fprxq
xnm ceuob lrtzv ita hegfd tsmr xnm ypwq ktj
frtjrpgguvj otvxmdxd prm iev prmvx xnmq

the quick brown fox jumps over the lazy dog
vtz ud xnm xugm itr pyy jttk gmv xt otgm xt xnm puk ti xnm fprxq
xnm ceuob lrtzv ita hegfd tsmr xnm ypwq ktj
frtjrpgguvj otvxmdxd prm iev prmvx xnmq
*/

char Key[100][26]={};

bool FigKey(int k,char *Sen,char *KeySen){
    char KT[26]={};
    int p=0;
    for(int i=0;i<strlen(Sen);i++){
        p=Sen[i]-'a';
        if(Sen[i]==' ' || Sen[i]=='\n'){ continue; } // �����̰ų� �����̸� ����
        else if(KT[p] == '\0'){ KT[p] = KeySen[i]; } // �� ���ĺ��� �ϳ��� ������ �Ǵ�
        else if(KT[p] == KeySen[i]){ continue; } //��ġ�� ����
        else{ return false; } //���� �ٸ����ڰ� ���� �濡 ���� key ������ �ƴ� ����
    }
    for(int i=0;i<26;i++){ Key[k][i]=KT[i]; } // �� ���� ���� �迭�� �־��ֱ�
    return true;
}

int main(){
    char KeySen[100][80]={},Sen[100][100][80]={},trash[30]={};
    int cnt[100]={0},confi[100]={0},n;
    printf("���� ������ �Է��ϼ��� >> ");
    scanf("%d",&n);
    fgets(trash,30,stdin);
    for(int k=0;k<n;k++){
        cnt[k]=0;confi[k]=-1;
        printf("��ȣ Ű ������ �Է��ϼ���. >> "); // Ű ���� �Է�
        fgets(KeySen[k],80,stdin);
        while(true){
            printf("��ȣȭ�� ������ �Է��ϼ��� >> ");
            fgets( Sen[k][cnt[k]] , 80 ,stdin); //��ȣȭ Ű ���� �����ֱ�
            if(Sen[k][cnt[k]][0] == '\n'){ break; } // ������ ������ �����Է� ��
            if(strlen(KeySen[k]) == strlen(Sen[k][cnt[k]])){ //Ű������ ��ȣȭ�� ���ڿ� ���̿� ������ ����
                if(FigKey(k,Sen[k][cnt[k]] , KeySen[k])){ confi[k]=cnt[k]; } //��ȣ Ű ���ϱ�
            }cnt[k]+=1;
        }
        printf("\n");
    }
    for(int k=0;k<n;k++){
        if(confi[k] == -1){ printf("No Solution\n"); } //���� ��ȣ Ű�� ������ ���
        else {
            for(int i=0;i<cnt[k];i++,printf("\n")){
                for(int j=0;j<strlen(Sen[k][i]);j++){ // ��ȣȭ �ؼ� ���
                    if(Sen[k][i][j]==' ' || Sen[k][i][j] == '\n' ){ printf(" "); }
                    else{
                        confi[k] = Sen[k][i][j]-'a';
                        printf("%c",Key[k][confi[k]]);
                    }
                }
            }
        }
        printf("\n");
    }
}
