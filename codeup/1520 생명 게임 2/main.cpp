#include <stdio.h>

int a[172][172], b[172][172], i, j;
int m,n,x,y,z,k,r;

int main()
{
    scanf("%d %d",&m,&n);
    scanf("%d %d %d",&x,&y,&z);
    for(i = 1; i <= m; i++)
        for(j = 1 ;j <= n; j++)
        {
            scanf("%d", &a[i][j]);

        }
    scanf("%d",&k);
    for(r=0;r<k;r++){
        for(i = 1; i <= m; i++){
            for(j = 1; j <= n; j++)
            {
                b[i][j] = 0;
                b[i][j] = a[i-1][j-1] + a[i-1][j] + a[i-1][j+1] + a[i][j-1] + a[i][j+1] + a[i+1][j-1] + a[i+1][j] + a[i+1][j+1];
                if(a[i][j] == 0)
                    b[i][j] = b[i][j] == x ? 1 : 0;
                else
                    b[i][j] = (b[i][j] >= z || b[i][j] < y) ? 0 : 1;
            }
        }
        for(i = 1; i <= m; i++){
            for(j = 1 ;j <= n; j++)
            {
                a[i][j]=b[i][j];
            }
        }
    }



    for(i = 1; i <= m; i++, puts(""))
        for(j = 1; j <= n; j++)
        {
            printf("%d ", b[i][j]);
        }
    return 0;
}
