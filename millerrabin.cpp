#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
void miller_function(int n);
int main()
{
	int n;
	srand(time(NULL));
	puts("Enter a number");
	scanf("%d", &n);
	miller_function(n);	
}
void miller_function(int n)
{
	int k, m, flag=0, a;
	int b;
	while ((pow(2,k) * m) != n-1)
	{
		m=1;
		for (k=0;k<100;k++){
			if ((pow(2,k) * m) == n-1){
				flag=1;
				break;
			}
		}
		if (flag==1){
			break;
		}	
		m=m+2;
	}
//	printf("m=%d", m);	
//	printf("k=%d", k);
	a=(rand()%(n-1))+1;
	b=pow(a,m);
	b=b%n;
	if (((b-1) % n) == 0){
		puts("PRIME");
	}  
	for (int i=0; i<k;i++){
		if (((b+1)%n)==0){
			puts("PRIME");
			break;
		}else{
			b=(b*b) % n;
		}
	}
//	puts("COMPOSITE");
	
}
