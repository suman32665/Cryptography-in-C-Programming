#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
int prime(int number);
int primitiveroot(int a, int p);
int main()
{
	srand(time(NULL));
	int Xa, Xb;
	long long int number;
	int KeyA,KeyB;
	int Ya, Yb, p, g;
	
	do{
		p=(rand()%100) + 3;
	}while (prime(p));
	
	printf("p=%d\n", p);
	g=1;
	while (1){
		g=(rand()%(p-1))+1;
		if (primitiveroot(g, p)){
			break;
		}	
	}
	printf("g=%d\n", g);
	
	printf("Enter the value of Xa and Xb(less than %d)\n", p);
	scanf("%d%d", &Xa, &Xb);
	
	Ya=pow(g, Xa);
	Ya=Ya% p;
	number=pow(g, Xb);
	Yb=(int)(number % p);
	printf("\nYA=%d\n", Ya);
	printf("YB=%d\n", Yb);
	
	KeyA=pow(Yb, Xa);
	KeyA=KeyA%p;
	number=pow(Ya, Xb);
	KeyB=number%p;
	
	printf("\nKEYA=%d\n", KeyA);
	printf("KEYB=%d\n", KeyB);
	if (KeyA==KeyB){
		puts("Same");
	}else{
		puts("not same");
	}
	
	getch();
}

int prime(int number)
{
	int flag=0;
	for (int i=2; i<(number/2); i++){
		if (number%i==0){
			flag=1;
			break;
		}
	}
	if (flag){
		return 1;
	}else{
		return 0;
	}
}
int primitiveroot(int a, int p)
{
	int array[30], j;
	j=0;
	for (int i=1; i<p; i++){
		array[j]=pow(a, i);
		array[j]=array[j] % p;
//		printf("array[%d]=%d\n", j, array[j]);
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
		return 0;
	}else{
		return 1;
	}
}
