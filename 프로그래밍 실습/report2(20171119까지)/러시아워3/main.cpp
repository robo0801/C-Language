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
    res -> �ּ� ���� Ƚ��
    x -> ���� ����
    y -> ���� ����
    n ->
*/
int cx[26], cy[26], g[26], s[26], st[30], dx[2]= {1,0}, dy[2]= {0,1};
/*
    cx[26], -> x ��ǥ
    cy[26], -> y ��ǥ
    g[26],  -> ����
    s[26],  -> ���� 0 ���� 1 �Ǵ�
    st[30], ->
    dx[2]= {1,0},
    dy[2]= {0,1}
*/
char mp[22][22];

// ��� ����� ����
char ans[100][2];
int anscnt=0;
char temp[100][2];
int cnt=0;

int W(int q, int go[])
{
    /*
        q �ڵ��� �ѹ�
    */

    int i, j, k, nx, ny, o=0;
    //printf("1-W----\n");
    for(k=1;; k++)
    {
        /*
            nx /�ڵ��� �̵��� x ��ǥ
            ny /�ڵ��� �̵��� y ��ǥ
            //������ �̵�
        */
        nx=cx[q]-dx[s[q]]*k;
        //printf("nx(%d),cx[q](%d),dx[s[q]](%d),s[q](%d),k(%d)\n",nx,cx[q],dx[s[q]],s[q],k);
        ny=cy[q]-dy[s[q]]*k;
        //printf("ny(%d),cy[q](%d),dy[s[q]](%d),s[q](%d),k(%d)\n",ny,cy[q],dy[s[q]],s[q],k);

        /*
            �ڵ��� �̵��� ��ǥ�� ���� �Ѿ�� ������
            �ڵ��� �̵��� ��ǥ�� �ڵ��� �̸� ������
            ���� �̵� �����ϸ� �̵��� �Ÿ� �ֱ�
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
    ///� �־����� o �� ��� ����
    //printf("2-W----\n");
    ///�ڷ� �̵�
    for(k=1;; k++)
    {
        ///dx ���� ��ȣ�� ���� �� �� ����
        nx=cx[q]+dx[s[q]]*(g[q]+k-1);
        ny=cy[q]+dy[s[q]]*(g[q]+k-1);
        //printf("nx=cx[q]+dx[s[q]]*(g[q]+k-1):%d  ny=cy[q]+dy[s[q]]*(g[q]+k-1):%d\n",nx,ny);
        if(nx>=x||ny>=y) break;
        if(mp[nx][ny]!='.') break;
        go[o++]=k;
    }
    ///� �־����� o �� ��� ����
    return o;
}

void V(int sx, int sy, int g, int s, char c) // �׳� �� �ٽ� ����� �Լ�
{
    /*
        sx -> �� ��ġ x ��ǥ
        sy -> �� ��ġ y ��ǥ
        g -> ����
        s -> ���� ����
        c -> �� ����
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
    //�ּ� ������� �Ǵ��ϴ� if ��
    if(cy[0]+g[0]==y)   //���� �� ũ�� ����
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
            if(!p2&&!W(mp[i][j]-'a',go)) p2=1;  //�ϳ��� �� �����̸� p2�� 1
        }
    }
    p1+=p2; //�������̴°� ������ p1=1�� ����
    if(arg1+p1+1>=res) return;
    for(k=-1; ++k<n;)
    {
        if(arg2!=k)
        {
            o=W(k,go); // �� �� �ִ� ��� ã�� �Լ� �ڵ��� ������ �־��ش�.
            V(cx[k],cy[k],g[k],s[k],'.');
            for(i=-1; ++i<o;) {
                /*
                    w �Լ����� �̵��� ��ǥ���� �޾Ƽ� go �迭�� �̵��Ÿ�  o ������ ���� �� �־���.
                    �� ���� v �Լ��� �׷ȴٰ� �ٽ� ����.
                    �� �߰��� losen�Լ� ��ͷ� ������ ���� ���� �Ѿ��.
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
        fall -> ���� �� ����
        i,j,k
        dum -> �ڵ��� ����
        l
        m
    */
    for(scanf("%d",&fall); fall--&&scanf("%d %d %d",&x,&y,&dum); )
    {
        dum=0;
        /*
            for(1.�� ���� �Է� �ޱ�;�� ���� �ϳ� ���� && �ڵ��� �� ���� ���� �޾ƿ���; ???  ,�� ��� )
        */
        for(i=-1; ++i<x; scanf("%s",mp[i])); /// �� �Է� �ޱ�
        for(i=-1; ++i<26; g[i]=0);          /// �ڵ��� ���� �ʱ�ȭ
        res=10;                 /// ���� Ƚ�� 10���� �ʱ�ȭ

        showmp();
        for(i=-1; ++i<x;){
            for(j=-1; ++j<y;){
                /*
                    i,j �� ���� ���� ���η� �̵�
                    �� ��ĵ
                */
                if('a'<=mp[i][j]&&mp[i][j]<='z')
                {
                    /*
                        �ڵ��� �϶� ����
                        k �ڵ��� ��ȣ -> a �ڵ����� 0��
                        cx -> �ڵ��� x ��ǥ
                        cy -> �ڵ��� y ��ǥ
                    */
                    k=mp[i][j]-'a';
                    cx[k]=i;
                    cy[k]=j;
                    /*
                        mp -> �ڵ��� �ִ� �ڸ� . ���� �ʱ�ȭ
                        s[] -> ���� 0 ���� 1
                        g[] -> �ڵ��� ���� 2 or 3
                    */
                    if(i+2<x&&mp[i+2][j]==mp[i][j]) // ���� 3�� ���� ��
                    {
                        mp[i][j]=mp[i+1][j]=mp[i+2][j]='.';
                        s[k]=0;
                        g[k]=3;
                        continue;
                    }
                    if(i+1<x&&mp[i+1][j]==mp[i][j]) // ���� 2�� ���� ��
                    {
                        mp[i][j]=mp[i+1][j]='.';
                        s[k]=0;
                        g[k]=2;
                        continue;
                    }
                    if(j+2<y&&mp[i][j+2]==mp[i][j]) // ���� 3�� ���� ��
                    {
                        mp[i][j]=mp[i][j+1]=mp[i][j+2]='.';
                        s[k]=1;
                        g[k]=3;
                        continue;
                    }
                    if(j+1<y&&mp[i][j+1]==mp[i][j]) // ���� 2�� ���� ��
                    {
                        mp[i][j]=mp[i][j+1]='.';
                        s[k]=1;
                        g[k]=2;
                        continue;
                    }
                }
            }
        }
        // ���ڸ� ������ ������� ����� �� n���� �迭 0���� �־��ش�.
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
        //���� ���� �Լ��� losen() �Լ�
    }
    return 0;
}
