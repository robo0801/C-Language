#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
2

6 6 13
b.c..e
b.cdde
fghaal
fghjjl
.giikk
mmm...

6 6 10
......
.bb.cc
aad.hi
fed.hi
feg..j
f.g..j


1
6 6 10
......
.bb.cc
aad.hi
fed.hi
feg..j
f.g..j


1
6 6 13
b.c..e
b.cdde
fghaal
fghjjl
.giikk
mmm...

*/



int x, y, res, n;
/*
    res -> 최소 실행 횟수
    x -> 세로 길이
    y -> 가로 길이
    n ->
*/
int cx[26], cy[26], g[26], s[26], st[30], dx[2]= {1,0}, dy[2]= {0,1};
/*
    cx[26], -> x 좌표
    cy[26], -> y 좌표
    g[26],  -> 길이
    s[26],  -> 수직 0 수평 1 판단
    st[30], ->
    dx[2]= {1,0},
    dy[2]= {0,1}
*/
char mp[22][22];

// 경로 출력해 보자
char ans[100][2];
int anscnt=0;
char temp[100][2];
int cnt=0;

int W(int q, int go[])
{
    /*
        q 자동차 넘버
    */

    int i, j, k, nx, ny, o=0;
    //printf("1-W----\n");
    for(k=1;; k++)
    {
        /*
            nx /자돛아 이동한 x 좌표
            ny /자동차 이동한 y 좌표
            //앞으로 이동
        */
        nx=cx[q]-dx[s[q]]*k;
        //printf("nx(%d),cx[q](%d),dx[s[q]](%d),s[q](%d),k(%d)\n",nx,cx[q],dx[s[q]],s[q],k);
        ny=cy[q]-dy[s[q]]*k;
        //printf("ny(%d),cy[q](%d),dy[s[q]](%d),s[q](%d),k(%d)\n",ny,cy[q],dy[s[q]],s[q],k);

        /*
            자동차 이동한 좌표가 판이 넘어가면 끝내기
            자동차 이동한 좌표가 자동차 이면 끝내기
            만약 이동 가능하면 이동한 거리 넣기
        */
        if(nx<0||ny<0) {
            //printf("nx(%d),ny(%d)\n",nx,ny);
            break;
        }
        if(mp[nx][ny]!='.'){
            //printf("mp[nx][ny],nx(%d),ny(%d)\n",nx,ny);
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
        //printf("nx=cx[q]+dx[s[q]]*(g[q]+k-1):%d  ny=cy[q]+dy[s[q]]*(g[q]+k-1):%d\n",nx,ny);
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
    //int i=-1;
    //for(; ++i<g; mp[sx+dx[s]*i][sy+dy[s]*i]=c);

    for(int i=0;i<g;i++){
        mp[sx+dx[s]*i][sy+dy[s]*i]=c;
    }

    /*for(int k=-1; ++k<x;printf("\n")){
        for(int j=-1; ++j<y;){
            //printf("%c",mp[k][j]);
        }
    }
    printf("\n");
    */
}

void showmp(){
    for(int i=0;i<6;i++,printf("\n")){
        for(int j=0;j<6;j++,printf(" ")){
            if(mp[i][j] == NULL){ printf("."); }
            else{ printf("%c",mp[i][j]); }
        }
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
            //printf("%d",ans[0][0]);
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
    if(arg1+p1+1>=res) return;
    for(k=-1; ++k<n;)
    {
        if(arg2!=k)
        {
            o=W(k,go); // 갈 수 있는 경로 찾는 함수 자동차 종류를 넣어준다.
            V(cx[k],cy[k],g[k],s[k],'.');
            for(i=-1; ++i<o;) {
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

int main()
{
    int fall, i, j, k, l, m, dum;
    /*
        fall -> 게임 판 개수
        i,j,k
        dum -> 자동차 개수
        l
        m
    */
    for(scanf("%d",&fall); fall--&&scanf("%d %d %d",&x,&y,&dum); )
    {
        dum=0;
        /*
            for(1.판 개수 입력 받기;판 개수 하나 빼고 && 자동차 수 가로 세로 받아오기; ???  ,답 출력 )
        */
        for(i=-1; ++i<x; scanf("%s",mp[i])); /// 맵 입력 받기
        for(i=-1; ++i<26; g[i]=0);          /// 자동차 길이 초기화
        res=10;                 /// 최종 횟수 10으로 초기화

        showmp();
        for(i=-1; ++i<x;){
            for(j=-1; ++j<y;){
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
                //printf("V(cx[i],cy[i],g[i],s[i],'a'+n) : ");
                //printf("V(%d,%d,%d,%d,%c)\n",cx[i],cy[i],g[i],s[i],'a'+n);
                V(cx[i],cy[i],g[i],s[i],'a'+n);
                cx[n]=cx[i];
                cy[n]=cy[i];
                g[n]=g[i];
                s[n]=s[i];
                //printf("V(cx[n],cy[n],g[n],s[n],'a'+n) : ");
                //printf("V(%d,%d,%d,%d,%c)\n",cx[n],cy[n],g[n],s[n],'a'+n);
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
    return 0;
}
