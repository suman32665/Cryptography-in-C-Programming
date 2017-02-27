#include<stdio.h>
#include<conio.h>

int gcd(int n , int i);
int main()
{
	int n, count=0;
	puts("ENTER a number(n)");
	scanf("%d", &n);
	
	for (int i=1; i<n; i++){
		if (gcd(n, i)==1){
			count++;
		}
	}
	printf("Euler's Totient(%d) : %d",n, count);
}

int gcd(int n , int i)
{
	for (int j=2; j<=i;j++){
		if (n%j==0 && i%j==0){
			return j;
		}
	}
	return 1;
}
