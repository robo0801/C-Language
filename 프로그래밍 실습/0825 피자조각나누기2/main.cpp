#include<stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    int ans=2;
    while(n!=1){
        ans += n--;
    }
    printf("%d",ans);
}
