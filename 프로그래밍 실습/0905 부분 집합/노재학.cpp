#include <stdio.h>

int arr[11]={0};
int check[11]={0};

void f(int n, int dep)
{
	if(n==dep-1)
	{
		printf("{");
		for(int i=1; i<=n; i++)
			if(check[i]==1)
				printf("%d ", arr[i]);
		printf("}\n");
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
	return 0;
}

