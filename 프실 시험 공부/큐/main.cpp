#include <stdio.h>
#include <stdlib.h>

int *queue;
int size;
int head;
int tail;

void InitQ(int _size) {
    size = _size;
    queue = (int*)malloc(sizeof(int)*size);
    head = 0;
    tail = 0;
}

bool InsertQ(int data){
    if((tail+1)%size==head) {
        return false;
    }
    queue[tail] = data;
    tail = (tail+1)%size;
    return true;
}

int DelQ() {
    if(head == tail){
        return -999;
    }
    int temp = queue[head];
    head = (head+1)%size;
    return temp;
}

int main() {
    InitQ(10);
    for(int i=1;i<=10;i++){
        InsertQ(i);
    }

    int temp;
    for(;(temp=DelQ())!=-999;) {
        printf("%d",temp);
    }
}
