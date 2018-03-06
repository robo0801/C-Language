#include<stdio.h>
#define Max 100

/*
5
5 2 39 23 44
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

int main() {
    int minidx;
    scan();

    for(int i=0;i<n-1;i++){
        minidx = i;
        for(int j=i;j<n;j++){
            if(arr[minidx]>arr[j]){
                minidx=j;
            }
        }
        if(minidx!=i){
            temp = arr[minidx];
            arr[minidx] = arr[i];
            arr[i]=temp;
            print();
        }
    }
    print();
}
