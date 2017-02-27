#include<stdio.h>
#include<conio.h>
#include<math.h>
void encryption(char message[50]);
void decryption(char message[50]);

char alphabet[100]="abcdefghijklmnopqrstuvwxyz";
int main()
{
	
	char message[50];
	
	printf("Enter message:");
	gets(message);
	encryption(message);
}

void encryption(char message[])
{
	char encryptmessage[50];
	int k=3, i, j;
	
	for (i=0; message[i]!=NULL; i++){
		if (message[i] != ' '){		
			for (j=0; alphabet[j]!=NULL; j++){	
				if (message[i]==alphabet[j]){
					
					encryptmessage[i]=alphabet[(j+k)%26];	
				}		
			}
		}else{
			encryptmessage[i]=' ';
		}
	}
	encryptmessage[i]=NULL;
	printf("\n");
	printf("Encrypted message:");
	puts(encryptmessage);
	
	decryption(encryptmessage);
	getch();
}

void decryption(char message[50])
{
	char decryptmessage[50];
	int k=3, i, j;
	
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
	
	
}
