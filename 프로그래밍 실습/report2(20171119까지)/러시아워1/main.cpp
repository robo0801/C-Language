#include<stdio.h>
#define deep 100

char ans[100][deep][3]={};
int ansCnt=0;

char RMapGet[20][6];
char Map[6][6];

int ImporCar;

int ScanMap() {
    char ExNum[10]={};
    printf("문제를 골라 주세요(1~10) >> ");scanf("%s",ExNum);
    sprintf(ExNum,"%s%s",ExNum,".txt"); //파일 이름 합치기
    //printf("%s",ExNum);

    FILE* f;                //파일 열기
    f = fopen(ExNum,"rt");

    if(f == NULL){ printf("실패\n"); return 0; }
    int line=0;
    while(true){
        fgets(RMapGet[line],255,f);
        if(feof(f) != 0){ // 파일을 끝까지 읽었는지 체크합니다.
            break;
        }
        line++;
        //printf("%d--\n",line);
    }
    fclose(f);
    return line;
}

void MakeMap(int line){
    int flag = 0;
    for(int i=0;i<line;i++){
        if(RMapGet[i][3] == 'V'){
            for(int j=0;j<2+flag;j++){
                Map[RMapGet[i][2]-'0'+j][RMapGet[i][1]-'0'] = RMapGet[i][0];
            }
        }
        else if(RMapGet[i][3] == 'H'){
            for(int j=0;j<2+flag;j++){
                Map[RMapGet[i][2]-'0' ][RMapGet[i][1]-'0'+j] = RMapGet[i][0];
            }
        }
        if(RMapGet[i][0] == 'X') {
            flag =1;
            ImporCar = i;
        }
    }
}

void ShowMap(){
    for(int i=0;i<6;i++,printf("\n")){
        for(int j=0;j<6;j++,printf(" ")){
            if(Map[i][j] == NULL){
                printf(".");
            }
            else{
                printf("%c",Map[i][j]);
            }
        }
    }
}

void ShowLoad(){

}

void solve(int cnt,int line) {
    if(cnt>=deep){
        return;
    }
    else if(RMapGet[ImporCar][1]==4){
        ShowLoad();
        ansCnt++;
        return;
    }

    int flag=0;
    for(int i=0;j<line;j++){
        for(int j=-5;j!=0 && j<=5;j++){
            if(RMapGet[i][3] == 'V'){
                if(0<=RMapGet[i][2]-'0'+j && RMapGet[i][2]-'0'+j+2+flag<6) {
                    ans[ansCnt][cnt][0]=RMapGet[i][0];
                    if(j>0){ ans[ansCnt][cnt][1]=j+'0'-1; }
                    else if(j<0){ ans[ansCnt][cnt][1]=j+10+'0'; }
                }
            }
            else if(RMapGet[i][3] == 'H'){
                if(0<=RMapGet[i][1]-'0'+j && RMapGet[i][1]-'0'+j+2+flag<6) {
                    ans[ansCnt][cnt][0]=RMapGet[i][0];
                    if(j>0){ ans[ansCnt][cnt][1]=j+'0'-1; }
                    else if(j<0){ ans[ansCnt][cnt][1]=j+10+'0'; }
                }
            }
            if(RMapGet[i][0] == 'X'){
                flag = 1;
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

}
