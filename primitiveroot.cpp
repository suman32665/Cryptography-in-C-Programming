#include<stdio.h>
#include<math.h>

int main()
{
	int a, p, array[30], j;
	puts("Enter value(a)");
	scanf("%d", &a);
	puts("Enter value(p)");
	scanf("%d", &p);
	j=0;
	for (int i=1; i<p; i++){
		array[j]=pow(a, i);
		array[j]=array[j] % p;
		printf("array[%d]=%d\n", j, array[j]);
		j++;
	}
	int flag=0;
	for (int i=0; i<(p-1); i++){
		for (int k=k+1; k<p;k++){
			if (array[i]==array[k]){
				flag=1;
				break;
			}
		}
	}
	if (flag==0){
		printf("%d is primitive root of %d", a, p);
	}else{
		printf("%d is not primitive root of %d", a, p);
	}
}
