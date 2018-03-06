#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    Node *next;
};

Node *head;

void InitList() {
    head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
}

Node* PutNode(Node *Target, Node *Temp) {
    Node *New;
    New = (Node*)malloc(sizeof(Node));
    *New = *Temp;

    New->next=Target->next;
    Target->next=New;
    return New;
}

bool DelNode(Node *Target) {
    Node* Del;
    Del = Target->next;
    if(Del = NULL) {
        return false;
    }
    Target->next = Del->next;
    free(Del);
    return true;
}

int main(){
    Node *Target;
    Node Temp;
    InitList();
    Target = head;
    for(int i=1;i<=10;i++){
        Temp.value=i;
        Target = PutNode(Target,&Temp);
    }
    for(Target=head->next;Target;Target=Target->next) {
        printf("%d\n",Target->value);
    }
}
