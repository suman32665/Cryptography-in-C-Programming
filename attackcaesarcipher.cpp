#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

int stringlength(char text[]);
int charactercount(char character, char text[]);
char removesameletter(char text[], char modifiedtext[]);
void sortindesc(float array[]);
void decryption(char message[50], int k, char alphabet[]);

int main()
{

	char alpha[27]= "abcdefghijklmnopqrstuvwxyz";
	float frequencies[27]={0.080, 0.015, 0.030, 0.040, 0.130, 0.020, 0.015, 0.060, 0.065, 0.005, 0.005, 0.035, 0.030, 0.070, 0.080, 0.020, 0.002, 0.065, 0.060, 0.090, 0.030, 0.010, 0.015, 0.005, 0.020, 0.002};
	int length, i, j, k;
	float frequency[27], probablekey[27], sorted[27];
	char encrypted[50], modifiedtext[50];
	
	puts("Enter the encrypted message:");
	gets(encrypted);
	length=stringlength(encrypted);
	removesameletter(encrypted, modifiedtext);
	
	for (i=0; modifiedtext[i]!=NULL; i++){
		for (j=0; alpha[j]!=NULL; j++){
			if (modifiedtext[i]==alpha[j]){
				frequency[j]=(float)charactercount(modifiedtext[i], encrypted)/length;
			}
		}
	}
	
	for (i=0; alpha[i]!=NULL; i++){
		probablekey[i]=0;
		for (j=0; modifiedtext[j]!=NULL; j++){
			for (k=0; alpha[k]!=NULL; k++){
				if (modifiedtext[j]==alpha[k]){
					probablekey[i]=probablekey[i]+(frequency[k] * frequencies[(k-i+26)%26]);
				}
			}
		}
		sorted[i]=probablekey[i];
	}
	
	sortindesc(sorted);
	
	for (i=0; i<26; i++){
		for (j=0; j<26;j++){
			if (sorted[i]==probablekey[j]){
				decryption(encrypted, j, alpha);
				fflush(stdin);
				puts("Did you get meaning decrypted message(y/n)?");
				if (getchar() == 'y'){
					exit(0);
				}else{
					continue;
				}
			}
		}
	}
	getch();
}

void decryption(char message[50], int k, char alphabet[])
{
	char decryptmessage[50];
	int  i, j;
	
	for (i=0; message[i]!=NULL; i++){
		if (message[i] != ' '){		
			for (j=0; alphabet[j]!=NULL; j++){	
				if (message[i]==alphabet[j]){
					decryptmessage[i]=alphabet[((j-k)+26)%26];	
				}		
			}
		}else{
			decryptmessage[i]=' ';
		}
	}
	decryptmessage[i]=NULL;
	printf("\n");
	printf("Decrypted message:");
	puts(decryptmessage);
	printf("\n");
}

int stringlength(char text[])
{
	int i, length=0;
	
	for (i=0; text[i]!=NULL; i++){
		if (text[i]>='A' && text[i<='z']){
			length++;
		}
	}
	return length;
}

int charactercount(char character, char text[])
{
	int i,j, count=0;
	
	for (i=0; text[i]!=NULL; i++){
		if (character==text[i]){
			count++;
		}
	}
	return count;
}

char removesameletter(char text[], char modifiedtext[])
{
	int i, j, flag=0, k=0;
	for (i=0; text[i]!=NULL; i++){
		for (j=0; modifiedtext[j]!=NULL;j++){
			if (text[i]==modifiedtext[j]){
				flag=1;
			}
		}
		if (flag==0){
			modifiedtext[k]=text[i];
			k++;
			modifiedtext[k]='\0';
		}
		flag=0;
	}	
} 

void sortindesc(float array[])
{
	int i, j;
	float temp;
	
	for (i=0;i<26;i++){
		for (j=i+1; j<26;j++){
			if (array[i]<array[j]){
				temp=array[j];
				array[j]=array[i];
				array[i]=temp;	
			} 
		}
	}
}
