#include<stdio.h>
#include<string.h>
int main(){
    char key[30]={},code[3][40]={};
    int i,j,k;
    scanf("%s",key);
    scanf("%s %s %s",code[0],code[1],code[2]);

    for(i=0;i<3;i++){
        for(j=0;j<strlen(code[i]);j++){
            for(k=0;k<10;k++){
                if(key[k]==code[i][j]){
                    printf("%d",k);
                }
            }
        }
        if(i!=2){
            printf(" ");
        }
    }
}
