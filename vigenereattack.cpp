#include<stdio.h>
#include<conio.h>
#include<string.h>

void stringsplitter(char ciphertext[], int start, int end, char splitted[]);
void findsimilarstring(char ciphertext[],int start, int length);

int main()
{
	char ciphertext[100];//="CSASTPKVSIQUTGQUCSASTPIUAQJB";  the boy has the ball. HUIPBCVNWHUIPNPZ
	int i, j;
	
	
	puts("Enter the cipher text:");
	gets(ciphertext);

	
	for (i=0;i<(strlen(ciphertext)-3);i++){
		for (j=3; j<((strlen(ciphertext)-i)/2);j++) {
			findsimilarstring(ciphertext, i, j);
		}
	}
}

void stringsplitter(char ciphertext[], int start, int end, char splitted[])
{
	int i, index=0;
	for (i=start; i<end; i++){
		splitted[index]=ciphertext[i];
		index++;
	}
	splitted[index]='\0';
}

void findsimilarstring(char ciphertext[],int start, int length)
{
	int i;
	char compare1[50], compare2[50];
	 
	stringsplitter(ciphertext, start, length, compare1);
	stringsplitter(ciphertext, length, length+length, compare2);
	start=length;
	for (i=0; ciphertext[i+length]!=NULL;i++){
		if (strcmp(compare1, compare2)==0){
			puts(compare1);
			printf("The possible key length is: %d\n", strlen(compare1));
		}	
		start++;
		stringsplitter(ciphertext, start, start+length, compare2);
	}
}
