#include<stdio.h>
#include<math.h>
void lucas_function(int p);
int main()
{
	int p;
	puts("Enter a number");
	scanf("%d", &p);
	lucas_function(p);
}

void lucas_function(int p)
{
	int s=4;
	int m=pow(2, p) -1;
//	printf("%d", m);
	for (int i=0; i<(p-2);i++){
		s=((s*s)-2)%m;
	}
	if (s==0){
		puts("PRIME.");
	}else{
		puts("COMPOSITE");
	}
}
