#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int x, y, res, n;
int cx[26], cy[26], g[26], s[26], st[30], dx[2]= {1,0}, dy[2]= {0,1};
/*
    res -> �ּ� ���� Ƚ��     x -> ���� ����  y -> ���� ����
    cx[26], -> x ��ǥ    cy[26], -> y ��ǥ
    g[26],  -> ����      s[26],  -> ���� 0 ���� 1 �Ǵ�
    dx[2]= {1,0}, dy[2]= {0,1}
*/
char mp[22][22];
char Map[22][22],RMapGet[20][6];
// ��� ��� ����
char ans[100][2],temp[100][2];
int anscnt=0,cnt=0;

bool success = false;

int W(int q, int go[])
{
    /*
        q �ڵ��� �ѹ�
    */

    int i, j, k, nx, ny, o=0;
    for(k=1;; k++)
    {
        /*
            nx /�ڵ��� �̵��� x ��ǥ
            ny /�ڵ��� �̵��� y ��ǥ
            //������ �̵�
        */
        nx=cx[q]-dx[s[q]]*k;
        ny=cy[q]-dy[s[q]]*k;

        /*
            �ڵ��� �̵��� ��ǥ�� ���� �Ѿ�� ������
            �ڵ��� �̵��� ��ǥ�� �ڵ��� �̸� ������
            ���� �̵� �����ϸ� �̵��� �Ÿ� �ֱ�
        */
        if(nx<0||ny<0) {
            break;
        }
        if(mp[nx][ny]!='.'){
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

    for(int i=0;i<g;i++){
        mp[sx+dx[s]*i][sy+dy[s]*i]=c;
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
    if(arg1+p1+1>=res) { return; } // ������ Ƚ���� ���� ����� �亸�� ������ ����
    for(k=0; k<n;k++)
    {
        if(arg2!=k)
        {
            o=W(k,go); // �� �� �ִ� ��� ã�� �Լ� �ڵ��� ������ �־��ش�.
            V(cx[k],cy[k],g[k],s[k],'.');
            for(i=0; i<o;i++) {
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

void solve()
{
    int fall, i, j, k, l, m, dum;
    /*
    fall -> ���� �� ����
    i,j,k
    dum -> �ڵ��� ����
    l
    m
    */

    x=6;y=6;
    for(i=-1; ++i<26; g[i]=0);          /// �ڵ��� ���� �ʱ�ȭ
    res=40;                 /// ���� Ƚ�� 40���� �ʱ�ȭ

    for(i=0; i<x; i++){
        for(j=0; j<y;j++){
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
    //���� ���� �Լ��� losen() �Լ�
}

int ScanMap()
{
    //txt ���Ͽ� ���� �޾ƿ��� RMapGet�� ��
    char ExNum[10]= {};
    int line=0;
    printf("������ ��� �ּ���(1~10) (����� ���� 1 ���� ����) >> ");
    scanf("%s",ExNum);
    sprintf(ExNum,"%s%s",ExNum,".txt"); //���� �̸� ��ġ��
    FILE* f= fopen(ExNum,"rt"); // �� ���� ����

    if(f == NULL)
    {
        printf("����\n");
        return 0;
    }
    while(true)
    {
        fgets(RMapGet[line],255,f);
        if(feof(f) != 0)
        {
            break;    // ������ ������ �о����� üũ�մϴ�.
        }
        line++;
    }
    fclose(f);
    return line;
}

void initMap()  //�� �ʱ�ȭ
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<6; j++)
        {
            Map[i][j] = NULL;
        }
    }
}

void MakeMap(int line)  // �޾ƿ� �迭�� �ʿ� ǥ���ϱ� RMapGet --> Map
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

void ShowMap()  //�� ���
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
void Showmp()  //�� ���
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
    printf("������ �������� (exit) Ǯ�̸� ������ (help)\n");
    printf("�̵� ��ɾ� ���� (a �ڵ����� ���������� 2ĭ : ar2 , b �ڵ����� ���� 1ĭ : bu1)\n");
    printf("�̵� ��ɾ� ���� (a �ڵ����� �������� 3ĭ : al3 , b �ڵ����� �Ʒ��� 3ĭ : bd3)\n");
    char cmd[6];
    while(true)
    {
        printf("> ");
        scanf("%s",cmd);
        if(!strcmp(cmd,"exit"))
        {
            printf("������ �����ϴ�.\n");
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
                printf("�ڵ����� ���������ϴ�!");
                break;
            }
        }
    }
}

int main()
{
    char ch;
    int line=0;
    printf("***���þƿ��� �����մϴ�.***\n");
    printf("������ �����ұ��? (y/n) : ");
    while(true)
    {
        scanf("%c",&ch);
        if(ch == 'n')
        {
            printf("�����մϴ�.\n");
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
            printf("�ѹ� �� �Ͻðڽ��ϱ�?\n");
        }
        initMap();
    }
}
