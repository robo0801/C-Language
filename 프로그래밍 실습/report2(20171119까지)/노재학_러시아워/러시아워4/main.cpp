#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int x, y, res, n;
int cx[26], cy[26], g[26], s[26], st[30], dx[2]= {1,0}, dy[2]= {0,1};
/*
    res -> 최소 실행 횟수     x -> 세로 길이  y -> 가로 길이
    cx[26], -> x 좌표    cy[26], -> y 좌표
    g[26],  -> 길이      s[26],  -> 수직 0 수평 1 판단
    dx[2]= {1,0}, dy[2]= {0,1}
*/
char mp[22][22];
char Map[22][22],RMapGet[20][6];
// 경로 출력 변수
char ans[100][2],temp[100][2];
int anscnt=0,cnt=0;

bool success = false;

int W(int q, int go[])
{
    /*
        q 자동차 넘버
    */

    int i, j, k, nx, ny, o=0;
    for(k=1;; k++)
    {
        /*
            nx /자돛아 이동한 x 좌표
            ny /자동차 이동한 y 좌표
            //앞으로 이동
        */
        nx=cx[q]-dx[s[q]]*k;
        ny=cy[q]-dy[s[q]]*k;

        /*
            자동차 이동한 좌표가 판이 넘어가면 끝내기
            자동차 이동한 좌표가 자동차 이면 끝내기
            만약 이동 가능하면 이동한 거리 넣기
        */
        if(nx<0||ny<0) {
            break;
        }
        if(mp[nx][ny]!='.'){
            break;
        }
        go[o++]=-k;
    }
    ///몇개 넣었는지 o 에 들어 있음
    //printf("2-W----\n");
    ///뒤로 이동
    for(k=1;; k++)
    {
        ///dx 앞의 부호를 보면 알 수 있음
        nx=cx[q]+dx[s[q]]*(g[q]+k-1);
        ny=cy[q]+dy[s[q]]*(g[q]+k-1);
        if(nx>=x||ny>=y) break;
        if(mp[nx][ny]!='.') break;
        go[o++]=k;
    }
    ///몇개 넣었는지 o 에 들어 있음
    return o;
}

void V(int sx, int sy, int g, int s, char c) // 그냥 맵 다시 만드는 함수
{
    /*
        sx -> 차 위치 x 좌표
        sy -> 차 위치 y 좌표
        g -> 길이
        s -> 수평 수직
        c -> 차 문자
    */

    for(int i=0;i<g;i++){
        mp[sx+dx[s]*i][sy+dy[s]*i]=c;
    }
}

// 0 , -1
void losen(int arg1, int arg2)
{
    int i, j, k, o, a, b, p1, p2;
    int go[30];
    //최소 경우인지 판단하는 if 문
    if(cy[0]+g[0]==y)   //답이 더 크면 갱신
    {
        if(res>arg1) {
            res=arg1;
            for(i=0;i<arg1;i++){
                ans[i][0]=temp[i][0];
                ans[i][1]=temp[i][1];
            }
        }
        return;
    }
    for(i=cx[p1=p2=0],j=cy[0]+g[0]; j<y; j++)
    {
        if('a'<=mp[i][j]&&mp[i][j]<='z')
        {
            p1++;
            if(!p2&&!W(mp[i][j]-'a',go)) p2=1;  //하나라도 못 움직이면 p2는 1
        }
    }
    p1+=p2; //못움직이는게 있으면 p1=1로 갱신
    if(arg1+p1+1>=res) { return; } // 움직인 횟수가 현재 저장된 답보다 많으면 리턴
    for(k=0; k<n;k++)
    {
        if(arg2!=k)
        {
            o=W(k,go); // 갈 수 있는 경로 찾는 함수 자동차 종류를 넣어준다.
            V(cx[k],cy[k],g[k],s[k],'.');
            for(i=0; i<o;i++) {
                /*
                    w 함수에서 이동한 좌표들을 받아서 go 배열에 이동거리  o 변수에 개수 를 넣었다.
                    그 다음 v 함수에 그렸다가 다시 뺀다.
                    그 중간에 losen함수 재귀로 돌려서 다음 노드로 넘어간다.
                */
                cx[k]+=go[i]*dx[s[k]];
                cy[k]+=go[i]*dy[s[k]];
                V(cx[k],cy[k],g[k],s[k],'a'+k);
                temp[cnt][0]='a'+k;
                temp[cnt++][1]=go[i];
                losen(arg1+1,k);
                V(cx[k],cy[k],g[k],s[k],'.');
                temp[--cnt][0]='\0';
                temp[cnt][1]=0;
                cx[k]-=go[i]*dx[s[k]];
                cy[k]-=go[i]*dy[s[k]];
            }
            V(cx[k],cy[k],g[k],s[k],'a'+k);
        }
    }
}

void solve()
{
    int fall, i, j, k, l, m, dum;
    /*
    fall -> 게임 판 개수
    i,j,k
    dum -> 자동차 개수
    l
    m
    */

    x=6;y=6;
    for(i=-1; ++i<26; g[i]=0);          /// 자동차 길이 초기화
    res=40;                 /// 최종 횟수 40으로 초기화

    for(i=0; i<x; i++){
        for(j=0; j<y;j++){
            /*
                i,j 가 판의 가로 세로로 이동
                맵 스캔
            */
            if('a'<=mp[i][j]&&mp[i][j]<='z')
            {
                /*
                    자동차 일때 들어가기
                    k 자동차 번호 -> a 자동차가 0번
                    cx -> 자동차 x 좌표
                    cy -> 자동차 y 좌표
                */
                k=mp[i][j]-'a';
                cx[k]=i;
                cy[k]=j;
                /*
                    mp -> 자동차 있던 자리 . 으로 초기화
                    s[] -> 수직 0 수평 1
                    g[] -> 자동차 길이 2 or 3
                */
                if(i+2<x&&mp[i+2][j]==mp[i][j]) // 길이 3인 수직 차
                {
                    mp[i][j]=mp[i+1][j]=mp[i+2][j]='.';
                    s[k]=0;
                    g[k]=3;
                    continue;
                }
                if(i+1<x&&mp[i+1][j]==mp[i][j]) // 길이 2인 수직 차
                {
                    mp[i][j]=mp[i+1][j]='.';
                    s[k]=0;
                    g[k]=2;
                    continue;
                }
                if(j+2<y&&mp[i][j+2]==mp[i][j]) // 길이 3인 수평 차
                {
                    mp[i][j]=mp[i][j+1]=mp[i][j+2]='.';
                    s[k]=1;
                    g[k]=3;
                    continue;
                }
                if(j+1<y&&mp[i][j+1]==mp[i][j]) // 길이 2인 수평 차
                {
                    mp[i][j]=mp[i][j+1]='.';
                    s[k]=1;
                    g[k]=2;
                    continue;
                }
            }
        }
    }
    // 문자를 꺼내서 순서대로 만들기 즉 n으로 배열 0부터 넣어준다.
    for(n=!(i=-1); ++i<26;){
        //printf("n=!(i=-1):%d , \n",n);
        if(g[i])
        {
            V(cx[i],cy[i],g[i],s[i],'a'+n);
            cx[n]=cx[i];
            cy[n]=cy[i];
            g[n]=g[i];
            s[n]=s[i];
            n++;
        }
    }

    losen(0,-1);
    printf("%d\n",res);

    for(i=0;i<res;i++){
        printf("%c%d -> ",ans[i][0],ans[i][1]);
    }printf("end\n");
    //실제 실행 함수는 losen() 함수
}

int ScanMap()
{
    //txt 파일에 맵을 받아오기 RMapGet에 들어감
    char ExNum[10]= {};
    int line=0;
    printf("문제를 골라 주세요(1~10) (현재는 문제 1 선택 가능) >> ");
    scanf("%s",ExNum);
    sprintf(ExNum,"%s%s",ExNum,".txt"); //파일 이름 합치기
    FILE* f= fopen(ExNum,"rt"); // 맵 파일 열기

    if(f == NULL)
    {
        printf("실패\n");
        return 0;
    }
    while(true)
    {
        fgets(RMapGet[line],255,f);
        if(feof(f) != 0)
        {
            break;    // 파일을 끝까지 읽었는지 체크합니다.
        }
        line++;
    }
    fclose(f);
    return line;
}

void initMap()  //맵 초기화
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<6; j++)
        {
            Map[i][j] = NULL;
        }
    }
}

void MakeMap(int line)  // 받아온 배열을 맵에 표시하기 RMapGet --> Map
{
    char CAR_IDS[100] = "XABCDEFGHIJK";
    char TRUCK_IDS[50] = "OPQR";
    char ch_IDS[50] = "xbcdefghijklmnopqrstuvwayz";
    int flag = 0;
    initMap();
    for(int i=0; i<line; i++)
    {
        for(int j=0; j<strlen(CAR_IDS); j++)
        {
            if(RMapGet[i][0] == CAR_IDS[j])
            {
                if(RMapGet[i][3] == 'V')
                {
                    for(int j=0; j<2; j++)
                    {
                        Map[RMapGet[i][2]-'0'+j][RMapGet[i][1]-'0'] = ch_IDS[(int)(RMapGet[i][0]-'A')];
                    }
                }
                else if(RMapGet[i][3] == 'H')
                {
                    for(int j=0; j<2; j++)
                    {
                        Map[RMapGet[i][2]-'0'][RMapGet[i][1]-'0'+j] = ch_IDS[(int)(RMapGet[i][0]-'A')];
                    }
                }
            }
        }
        for(int j=0; j<strlen(TRUCK_IDS); j++)
        {
            if( RMapGet[i][0] ==  TRUCK_IDS[j] )
            {
                if(RMapGet[i][3] == 'V')
                {
                    for(int j=0; j<3; j++)
                    {
                        Map[RMapGet[i][2]-'0'+j][RMapGet[i][1]-'0'] = ch_IDS[RMapGet[i][0]-'A'];
                    }
                }
                else if(RMapGet[i][3] == 'H')
                {
                    for(int j=0; j<3; j++)
                    {
                        Map[RMapGet[i][2]-'0' ][RMapGet[i][1]-'0'+j] = ch_IDS[RMapGet[i][0]-'A'];
                    }
                }
            }
        }
    }

}

void ShowMap()  //맵 출력
{
    for(int i=0; i<6; i++,printf("\n"))
    {
        for(int j=0; j<6; j++,printf(" "))
        {
            if(Map[i][j] == NULL)
            {
                printf(".");
            }
            else
            {
                printf("%c",Map[i][j]);
            }
        }
    }
}
void Showmp()  //맵 출력
{
    for(int i=0; i<6; i++,printf("\n"))
    {
        for(int j=0; j<6; j++,printf(" "))
        {
            if(mp[i][j] == NULL)
            {
                printf(".");
            }
            else
            {
                printf("%c",mp[i][j]);
            }
        }
    }
}

void mvMap()
{
    x=6;
    y=6;
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(Map[i][j] == NULL){
                mp[i][j] = '.';
            }
            else{
                mp[i][j] = (char)Map[i][j];
            }
        }
    }
}


void mvCar(char id, char di,int can)
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(Map[i][j] == id)
            {
                if(di == 'd')
                {
                    if(Map[i+2][j] == Map[i][j])
                    {
                        for(int k=2; k>=0; k--)
                        {
                            Map[i+k+can][j] = Map[i+k][j];
                            Map[i+k][j] = '.';
                        }
                    }
                    else if(Map[i+1][j] == Map[i][j])
                    {
                        for(int k=1; k>=0; k--)
                        {
                            Map[i+k+can][j] = Map[i+k][j];
                            Map[i+k][j] = '.';
                        }
                    }
                    return;
                }
                if(di == 'u')
                {
                    if(Map[i+2][j] == Map[i][j])
                    {
                        for(int k=0; k<3; k++)
                        {
                            Map[i+k-can][j] = Map[i+k][j];
                            Map[i+k][j] = '.';
                        }
                    }
                    else if(Map[i+1][j] == Map[i][j])
                    {
                        for(int k=0; k<2; k++)
                        {
                            Map[i+k-can][j] = Map[i+k][j];
                            Map[i+k][j] = '.';
                        }
                    }
                    return;
                }
                if(di == 'r')
                {
                    if(Map[i][j+2] == Map[i][j])
                    {
                        for(int k=2; k>=0; k--)
                        {
                            Map[i][j+k+can] = Map[i][j+k];
                            Map[i][j+k] = '.';
                        }
                    }
                    else if(Map[i][j+1] == Map[i][j])
                    {
                        for(int k=1; k>=0; k--)
                        {
                            Map[i][j+k+can] = Map[i][j+k];
                            Map[i][j+k] = '.';
                        }
                    }
                    return;
                }
                if(di == 'l')
                {
                    if(Map[i][j+2] == Map[i][j])
                    {
                        for(int k=0; k<3; k++)
                        {
                            Map[i][j+k-can] = Map[i][j+k];
                            Map[i][j+k] = '.';
                        }
                    }
                    else if(Map[i][j+1] == Map[i][j])
                    {
                        for(int k=0; k<2; k++)
                        {
                            Map[i][j+k-can] = Map[i][j+k];
                            Map[i][j+k] = '.';
                        }
                    }
                    return;
                }
            }
        }
    }

}


void gameStart()
{
    printf("게임을 나가려면 (exit) 풀이를 보려면 (help)\n");
    printf("이동 명령어 예시 (a 자동차를 오른쪽으로 2칸 : ar2 , b 자동차를 위로 1칸 : bu1)\n");
    printf("이동 명령어 예시 (a 자동차를 왼쪽으로 3칸 : al3 , b 자동차를 아래로 3칸 : bd3)\n");
    char cmd[6];
    while(true)
    {
        printf("> ");
        scanf("%s",cmd);
        if(!strcmp(cmd,"exit"))
        {
            printf("게임을 나갑니다.\n");
            break;
        }
        else if(!strcmp(cmd,"help"))
        {
            mvMap();
            Showmp();
            solve();
            break;
        }
        else
        {
            mvCar(cmd[0],cmd[1],cmd[2]-'0');
            ShowMap();
            for(int i=0; i<6; i++)
            {
                for(int j=0; j<6; j++)
                {
                    if(Map[i][j] == 'a' && j == 5){
                        success=true;
                    }
                }
            }
            if(success){
                printf("자동차를 빼내었습니다!");
                break;
            }
        }
    }
}

int main()
{
    char ch;
    int line=0;
    printf("***러시아워를 시작합니다.***\n");
    printf("게임을 시작할까요? (y/n) : ");
    while(true)
    {
        scanf("%c",&ch);
        if(ch == 'n')
        {
            printf("종료합니다.\n");
            break;
        }
        else if (ch == 'y')
        {
            success=false;
            line = ScanMap();
            MakeMap(line);
            ShowMap();
            printf("\n");
            gameStart();
            printf("한번 더 하시겠습니까?\n");
        }
        initMap();
    }
}
