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
        if(Sen[i]==' ' || Sen[i]=='\n'){ continue; } // 공백이거나 개행이면 무시
        else if(KT[p] == '\0'){ KT[p] = KeySen[i]; } // 각 알파벳에 하나씩 들어가는지 판단
        else if(KT[p] == KeySen[i]){ continue; } //겹치면 진행
        else{ return false; } //만약 다른문자가 같은 방에 들어가면 key 문장이 아님 리턴
    }
    for(int i=0;i<26;i++){ Key[i]=KT[i]; } // 다 들어가면 전역 배열에 넣어주기
    return true;
}

int main(){
    char KeySen[80]={},Sen[100][80]={};
    printf("암호 키 문장을 입력하세요. >> "); // 키 문장 입력
    fgets(KeySen,80,stdin);
    int cnt=0,k=-1;

    while(true){
        printf("복호화할 문장을 입력하세요 >> ");
        fgets(Sen[cnt],80,stdin); //암호화 키 문장 보여주기
        if(Sen[cnt][0] == '\n'){ break; } // 공백이 들어오면 문장입력 끝
        if(strlen(KeySen) == strlen(Sen[cnt])){ //키문장이 복호화할 문자열 길이와 같을때 실행
            if(FigKey(Sen[cnt],KeySen)){ k=cnt; } //암호 키 구하기
        }cnt+=1;
    }

    if(k == -1){ printf("No Solution\n"); } //만약 암호 키가 없으면 출력
    else {
        for(int i=0;i<cnt;i++,printf("\n")){
            for(int j=0;j<strlen(Sen[i]);j++){ // 복호화 해서 출력
                if(Sen[i][j]==' ' || Sen[i][j] == '\n' ){ printf(" "); }
                else{
                    k = Sen[i][j]-'a';
                    printf("%c",Key[k]);
                }
            }
        }
    }
}
