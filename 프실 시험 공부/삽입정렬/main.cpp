#include<stdio.h>
#define Max 100

/*
5
5 2 39 23 44


5
5 23 39 2 44

*/

int arr[Max] ={};
int n=0,temp;
void scan(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){ scanf("%d",&arr[i]); }
}

void print(){
    for(int k=0;k<n;k++){ printf("%d ",arr[k]); }
    printf("\n");
}

int main(){
    scan();

    for(int i=1;i<n;i++){
        temp = arr[i];
        for(int j=i;j>0;j--){
            if(arr[j-1]>temp){
                arr[j]=arr[j-1];
                if(j==1){
                    arr[j-1]=temp;
                    break;
                }
            }
            else {
                arr[j]=temp;
                break;
            }
            print();
        }
    }
    print();
}
