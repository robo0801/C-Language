#include <stdio.h>

int arr[11]={0};
int check[11]={0};
int sum[100000],cnt;

//부분집합 구하기
void f(int n, int dep)
{
	if(n==dep-1)
	{
		printf("{");
		for(int i=1; i<=n; i++){
			if(check[i]==1){ //각 원소의 위치에 0과 1로 체크를 하고 1이면 출력한다.
				printf("%d ", arr[i]);
				sum[cnt]+=arr[i];
			}
		}
		printf("} ");
		printf("sum = %d\n",sum[cnt]); //바로 그 뒤에 부분집합 출력하기
		cnt++;

		return;
	}
	check[dep]=0;
	f(n, dep+1);
	check[dep]=1;
	f(n, dep+1);
}

int main()
{
	int n;

	scanf("%d", &n);

	for(int i=1; i<=n; i++)
		arr[i]=i;
	f(n,1);

	/*
	//부분 집합 그냥 출력하기
	//출력할 때 소트하기
	for(int i=0;i<cnt-1;i++){
        for(int j=i+1;j<cnt;j++){
            if(sum[i]>sum[j]){
                n = sum[i];
                sum[i] = sum[j];
                sum[j] = n;
            }
        }
	}
	//합이 같은 부분 없애기
	for(int i=0;i<cnt-1;i++){
        if(n != sum[i]){
            printf("%d ",sum[i]);
            n = sum[i];
        }
	}
	*/
	return 0;
}

