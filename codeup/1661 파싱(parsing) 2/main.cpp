#include<stdio.h>
#include<string.h>

int main(){
    char c[103]={0};
    int i;
    scanf("%s",c);
    for(i=0;i<strlen(c);i++){
        printf("%c",c[i]);
    }

}
