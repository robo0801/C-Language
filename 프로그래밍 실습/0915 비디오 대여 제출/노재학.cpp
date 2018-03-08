#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 300

typedef struct nodeRecord {
    char Data[20]={};
    struct nodeRecord* Next = NULL;
}node;

typedef node* Nptr;

typedef struct{
    int Count;
    char name[20]={};
    Nptr Head;
}listType;

//내용 초기화 함수
void Init(listType *Lptr, char nameItem[]) {
    Lptr->Count = 0;
    Lptr->Head = NULL;
    strcpy(Lptr->name,nameItem);
}

//비었는지 확인하는 함수
bool IsEmpty(listType *Lptr){
    return (Lptr->Count == 0);
}

//리스트 길이 확인하는 함수
int Length(listType *Lptr) {
    return Lptr->Count;
}

//리스트에 있는 데이터 보여주는 함수
void showData(listType *Lptr){
    printf("\n%s Book Borrow\n",Lptr->name);
    Nptr p = Lptr->Head;
    //p->Next
    for(int i=0;i<Lptr->Count;i++){
        printf("%d. %s\n",i+1,p->Data);
        p = p->Next;
    }
    printf("\n");
}

void Insert(listType *Lptr, int Position, char DataItem[]){
    if( (Position > (Lptr->Count+1)) || (Position < 1) ){
        printf("Position out of Range\n");
    }
    else {
        Nptr p = (node*)malloc(sizeof(node));
        strcpy(p->Data,DataItem);
        if(Position == 1){
            p->Next = Lptr->Head;
            Lptr->Head = p;
        }
        else {
            Nptr Temp = Lptr->Head;
            for(int i=1;i<(Position-1);i++){
                Temp = Temp->Next;
            }
            p->Next = Temp->Next;
            Temp->Next = p;
        }
        Lptr->Count += 1;
    }
}

void Delete(listType *Lptr, int Position) {
    if(IsEmpty(Lptr)){
        printf("Empty List\n");
    }
    else if (Position > (Lptr->Count) || (Position < 1)) {
        printf("Position out of Range\n");
    }
    else{
        Nptr p;
        if(Position == 1){
            p = Lptr->Head;
            Lptr->Head = Lptr->Head->Next;
        }
        else {
            Nptr Temp = Lptr->Head;
            for(int i=0;i<(Position-1);i++){
                Temp = Temp->Next;
            }
            p = Temp->Next;
            Temp->Next = p->Next;
        }
        Lptr->Count -=1;
        free(p);
    }
}



int main(){
    listType* Temp[MAX];

    int peopleCount = 0;
    char name[20]={};
    int cmd = -1;

    while(cmd != 0) {
        printf("0.quit  1.Create Account  2.Borrowing  3.Returning  4.ShowData  : ");
        scanf("%d",&cmd);
        while(!(0<=cmd && cmd<=4)){
            printf("Wrong Command : ");
            scanf("%d",&cmd);
        }
        if(cmd == 0){
            break;
        }
        else if(cmd == 1){
            printf("User Name : ");
            scanf("%s",name);
            Temp[peopleCount] = (listType*)malloc(sizeof(listType));
            Init(Temp[peopleCount],name);
            showData(Temp[peopleCount]);
            peopleCount +=1;
        }
        else if(cmd == 2){
            bool check = true;int i=0;
            printf("Input User Name : ");
            scanf("%s",name);
            while(check){
                for(i=0;i<peopleCount;i++){
                    if(stricmp(name,Temp[i]->name)==0){
                        check = false;
                        break;
                    }
                }
                if(check){
                    printf("Input Again : ");
                    scanf("%s",name);
                }
            }
            printf("Borrowing Book Name : ");
            scanf("%s",name);

            Insert(Temp[i],Temp[i]->Count+1,name);
            showData(Temp[i]);
        }
        else if(cmd == 3){
            bool check = true;int i=0,bookNum=0;
            printf("Input User Name : ");
            scanf("%s",name);
            while(check){
                for(i=0;i<peopleCount;i++){
                    if(stricmp(name,(Temp[i]->name))==0){
                        check = false;
                        break;
                    }
                }
                if(check){
                    printf("Input Again : ");
                    scanf("%s",name);
                }
            }
            printf("반납하실 책을 번호를 입력하세요.\n");
            showData(Temp[i]);
            scanf("%d",&bookNum);
            Delete(Temp[i],bookNum);
            showData(Temp[i]);
        }
        else if(cmd == 4){
            bool check = true;int i=0;
            printf("Input User Name : ");
            scanf("%s",name);
            while(check){
                for(i=0;i<peopleCount;i++){
                    if(stricmp(name,(Temp[i]->name))==0){
                        check = false;
                        break;
                    }
                }
                if(check){
                    printf("Input Again : ");
                    scanf("%s",name);
                }
            }
            showData(Temp[i]);
        }
    }

}
