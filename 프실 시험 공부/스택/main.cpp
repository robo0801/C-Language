#include <stdio.h>
#include <stdlib.h>

int *stack;
int size;
int p;

void InitStack(int _size) {
    size = _size;
    stack = (int *)malloc(sizeof(int));
    p=-1;
}

bool InStack(int data) {
    if(p+1>=size) {
        return false;
    }
    stack[++p] = data;
    return true;
}

int OutStack() {
    if(p<=-1) {
        return -999;
    }
    int temp = stack[p--];
    return temp;
}

int main() {
    InitStack(4);
    InStack(1);
    InStack(2);
    InStack(3);
    InStack(4);
    int temp;
    while((temp=OutStack())!=-999) {
        printf("%d\n",temp);
    }

}
