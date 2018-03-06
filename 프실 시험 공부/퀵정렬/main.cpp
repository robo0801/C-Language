#include<stdio.h>
#define Max 100

#define swap(x,y) {int temp;temp=x;x=y;y=temp;}

/*
5
5 2 39 23 44


5
5 23 39 2 44

*/

int arr[Max] ={};
int n=0;

void scan(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){ scanf("%d",&arr[i]); }
}

void print(){
    for(int k=0;k<n;k++){ printf("%d ",arr[k]); }
    printf("\n");
}

void quick(int L,int R){
    int pivot = L;
    int j = pivot;
    int i = L+1;

    if(L < R) {
        for(; i<=R;i++){
            if(arr[i]<arr[pivot]){
                j++;
                swap(arr[j],arr[i]);
                print();
            }
        }
        swap(arr[L],arr[j]);
        print();
        pivot = j;
        quick(L,pivot-1);
        quick(pivot+1,R);
    }
}

int main(){
    scan();
    quick(0,n-1);
    print();
}

//http://thrillfighter.tistory.com/212?category=399367
