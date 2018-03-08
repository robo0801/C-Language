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

void merge_sort(int L,int R);
void merge(int L,int M,int R);


int main() {
    scan();
    merge_sort(0,n-1);
    print();
}

void merge_sort(int L,int R){
    int M;

    if(L < R) {
        M = (L+R)/2;
        merge_sort(L,M);
        merge_sort(M+1,R);
        merge(L,M,R);
    }
}

void merge(int L,int M,int R){
    int i = L;
    int j = M+1;
    int k = L;

    int tempArr[Max];

    while(i<=M && j<= R) {
        if(arr[i] < arr[j]) {
            tempArr[k] = arr[i];
            i+=1;
        }
        else {
            tempArr[k] = arr[j];
            j+=1;
        }
        k+=1;
    }

    if(i>M){
        for(int m=j;m<=R;m++){
            tempArr[k] = arr[m];
            k+=1;
        }
    }
    else{
        for(int m=i;m<=M;m++){
            tempArr[k] = arr[m];
            k+=1;
        }
    }
    for(int m=L;m<=R;m++){
        arr[m] = tempArr[m];
    }
}
