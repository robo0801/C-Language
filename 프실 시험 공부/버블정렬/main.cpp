#include <stdio.h>
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

void Bubble1() {

    scan();


    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                temp=arr[j];arr[j]=arr[j+1];arr[j+1]=temp;

                printf("%d\n",j);

                print();
            }
        }
    }

    print();
}

void Bubble2() {
    bool flag;

    scan();

    for(int i=0;i<n-1;i++){
        flag = false;
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                flag = true;

                temp=arr[j];arr[j]=arr[j+1];arr[j+1]=temp;

                printf("%d\n",j);
                print();
            }
            if(flag==false){ break; }
        }
    }
    print();
}

int main(){
    Bubble1();
    Bubble2();
}
