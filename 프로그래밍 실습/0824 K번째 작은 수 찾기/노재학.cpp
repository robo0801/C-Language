#include<stdio.h>

int main(){
    int k,arr[100]={0},n;
    int i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++){ scanf("%d",&arr[i]); }
    scanf("%d",&k);

    int p=arr[n],temp=0;
    int L1=1,R1=n-1,L2=0,R2=0;
    int P=n;
    while(1){
        L2=L1;R2=R1;
        while(L2<R2){
            if(arr[R2]<=p && arr[L2]>=p){
                temp = arr[R2];
                arr[R2] = arr[L2];
                arr[L2] = temp;
            }
            if(arr[R2]>p) R2--;
            if(arr[L2]<p) L2++;
        }

        temp = arr[P];
        arr[P] = arr[L2];
        arr[L2] = temp;

        if(L2 == k) {
            printf("%d",arr[L2]);
            break;
        }
        else if(L2 < k){
            L1 = L2+1;
            R1 = R1;
            p = arr[R1+1];
            P=R1+1;
        }
        else if(L2 > k) {
            L1 = L1;
            R1 = L2-2;
            p = arr[L2-1];
            P = L2-1;
        }
    }
}
