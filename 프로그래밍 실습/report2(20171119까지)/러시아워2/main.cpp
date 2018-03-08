#include <stdio.h>
#include <string.h>
#define deep 6

char CAR_IDS[] = {'X', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
char TRUCK_IDS[] = {'O', 'P', 'Q', 'R'};

//char All_IDS[20];
//int All_POS[20][2];

char temp[deep][3];
char ans[100][deep][3];
int ansCnt=0;

char RMapGet[20][6];
int MCarPos=-1;
char Map[6][6];



///Scan 성공
int ScanMap() { //txt 파일에 맵을 받아오기 RMapGet에 들어감
    char ExNum[10]={};
    printf("문제를 골라 주세요(1~10) (현재는 문제 1 선택 가능) >> ");scanf("%s",ExNum);
    sprintf(ExNum,"%s%s",ExNum,".txt"); //파일 이름 합치기
    FILE* f= fopen(ExNum,"rt"); // 맵 파일 열기

    if(f == NULL){ printf("실패\n"); return 0; }
    int line=0;
    while(true){
        fgets(RMapGet[line],255,f);
        if(feof(f) != 0){ break; }// 파일을 끝까지 읽었는지 체크합니다.
        line++;
    }
    fclose(f);
    return line;
}

/// 맵 만들기
///맵 만들기 성공

void initMap(){ //맵 초기화
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            Map[i][j] = NULL;
        }
    }
}

void MakeMap(int line){ // 받아온 배열을 맵에 표시하기 RMapGet --> Map
    int flag = 0;
    for(int i=0;i<line;i++){
        for(int j=0;j<strlen(CAR_IDS);j++){
            if(RMapGet[i][0] == CAR_IDS[j]) {
                if(RMapGet[i][3] == 'V'){
                    for(int j=0;j<2;j++){
                        Map[RMapGet[i][2]-'0'+j][RMapGet[i][1]-'0'] = RMapGet[i][0];
                    }
                }
                else if(RMapGet[i][3] == 'H'){
                    for(int j=0;j<2;j++){
                        Map[RMapGet[i][2]-'0' ][RMapGet[i][1]-'0'+j] = RMapGet[i][0];
                    }
                }
            }
            if(RMapGet[i][0] == 'X') { MCarPos=i; }
        }
        for(int j=0;j<strlen(TRUCK_IDS);j++){
            if(RMapGet[i][0] == TRUCK_IDS[j]){
                if(RMapGet[i][3] == 'V'){
                    for(int j=0;j<3;j++){
                        Map[RMapGet[i][2]-'0'+j][RMapGet[i][1]-'0'] = RMapGet[i][0];
                    }
                }
                else if(RMapGet[i][3] == 'H'){
                    for(int j=0;j<3;j++){
                        Map[RMapGet[i][2]-'0' ][RMapGet[i][1]-'0'+j] = RMapGet[i][0];
                    }
                }
            }
            if(RMapGet[i][0] == 'X') { MCarPos=i; }
        }
    }

}

void ShowMap(){ //맵 출력
    for(int i=0;i<6;i++,printf("\n")){
        for(int j=0;j<6;j++,printf(" ")){
            if(Map[i][j] == NULL){ printf("."); }
            else{ printf("%c",Map[i][j]); }
        }
    }
}

void ShowLoad(int cnt){
    for(int i=0;i<cnt;i++) {
        printf("%c(%c%c) -> ",temp[i][0],temp[i][1],temp[i][2]);
        for(int j=0;j<3;j++) {
            ans[ansCnt][i][j]=temp[i][j];
            temp[i][j]=NULL;
        }

    }
    printf("\n");
    ansCnt++;

    return;
}

//void solve(int cnt){

//}



void solve(int cnt,int line) {
    if(cnt>=deep){ return; }
    else if(RMapGet[MCarPos][1]==4){
        ShowLoad(cnt);
        return;
    }

    int flag=0;
    for(int i=0;i<line;i++){
        for(int j=-5;j<=5;j++){
            if(RMapGet[i][3] == 'V'){
                if(j!=0 && 0<=RMapGet[i][2]-'0'+j && RMapGet[i][2]-'0'+j+2+flag<6) {
                    temp[cnt][0]=RMapGet[i][0];
                    if(j>0){
                        temp[cnt][1]='+';
                        temp[cnt][2]=j+'0';
                    }
                    else if(j<0){
                        temp[cnt][1]='-';
                        temp[cnt][2]=-j+'0';
                    }
                    ///:todo:movecar
                    RMapGet[i][2]+=j;
                    solve(cnt+1,line);
                    RMapGet[i][2]-=j;
                }
            }
            else if(RMapGet[i][3] == 'H'){
                if(j!=0 && 0<=RMapGet[i][1]-'0'+j && RMapGet[i][1]-'0'+j+2+flag<6) {
                    temp[cnt][0]=RMapGet[i][0];
                    if(j>0){
                        temp[cnt][1]='+';
                        temp[cnt][2]=j+'0';
                    }
                    else if(j<0){
                        temp[cnt][1]='-';
                        temp[cnt][2]=-j+'0';
                    }
                    ///:todo:movecar
                    RMapGet[i][1]+=j;
                    solve(cnt+1,line);
                    RMapGet[i][1]-=j;

                }
            }

        }
    }
}


int main(){
    int line = ScanMap();
    if(line !=0){
        printf("%s\n",RMapGet[4]);
        MakeMap(line);
    }
    ShowMap();
    printf("\n");
    //solve(0,line);
}











