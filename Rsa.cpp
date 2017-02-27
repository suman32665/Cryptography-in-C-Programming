#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int gcd(int n , int i);
int encryption(int m, int e, int n);
int decryption(int c, int d, int n);
int main()
{
	srand(time(NULL));
	int p, q, n, flag=1, e, m=2, d;
	int totient;
	puts("Enter the value of p(large prime number)");
	scanf("%d", &p);
	puts("Enter the value of q(large prime number)");
	scanf("%d", &q);
	
	n=p*q;
	totient=(p-1)*(q-1);
	while (flag){
		e=(rand()%totient)+1;
		if (gcd(e, totient)==1){
			flag=0;
		}
	}
//	printf("m=%d, e=%d, n=%d", m, e, n);
	
	
	for (int x=0; x<1000; x++){
		if ((e*x)%totient==1){				
			d=x;	
			break;
		}
	}
	decryption(encryption(m, e, n), d,n);
	
	
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
int decryption(int c, int d, int n)
{
	int message=pow(c, d);
	message=message%n;
	printf("\nDecryption=%d", message);
}
int encryption(int m, int e, int n)
{
	int c;
	c=pow(m, e);
	c=c%n;
	printf("Encryption=%d", c);
	return c;
}
