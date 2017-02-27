#include<stdio.h>
#include<conio.h>
#include<string.h>

int findindexofalphabet(char alphabet);
void finddecimals(char text[], int textdecimal[20]);
void vernamencryption(char plaintext[], char key[]);
void vernamdecryption(char encrypttext[], char key[]);
int main()
{
	char plaintext[20], key[10];
	
	
	puts("Enter the plaintext:");
	gets(plaintext);
	puts("Enter the key:");
	gets(key);
	vernamencryption(plaintext, key);
	
	
}
void vernamencryption(char plaintext[], char key[])
{
	int plaintextdecimal[20], keydecimal[10], i;
	char encrypttext[20], alpha[27]= "abcdefghijklmnopqrstuvwxyz";
	
	if (strlen(plaintext) < strlen(key)){
		i=strlen(plaintext);
		while (i!=strlen(key)){
			plaintext[i]='x';
			i++;
		}
		plaintext[i]='\0';
	}
	//puts(plaintext);
	
	finddecimals(plaintext, plaintextdecimal);
	finddecimals(key, keydecimal);
	
	for (i=0; plaintext[i]!='\0'; i++){			//encrypts the text
		encrypttext[i]=alpha[(plaintextdecimal[i]^keydecimal[(i%strlen(key))])%26];
	}
	encrypttext[i]='\0';
	puts("Encrypted Text:");
	puts(strupr(encrypttext));
	
	vernamdecryption(strlwr(encrypttext), key);
}

void vernamdecryption(char encrypttext[], char key[])		
{
	int encryptdecimal[20], keydecimal[10], i;
	char decrypttext[20], alpha[27]= "abcdefghijklmnopqrstuvwxyz";
	
	finddecimals(encrypttext, encryptdecimal);
	finddecimals(key, keydecimal);
	
	for (i=0; encrypttext[i]!='\0'; i++){				//decrypts the text 
		decrypttext[i]=alpha[(encryptdecimal[i]^keydecimal[(i%strlen(key))])%26];
	}
	decrypttext[i]='\0';
	
	puts("Decrypted Text:");
	puts(strupr(decrypttext));
}

void finddecimals(char text[], int textdecimal[20])		//finds decimal value of text and stores it in textdecimals
{
	int i;
	for (i=0; text[i]!='\0'; i++){
		textdecimal[i]=findindexofalphabet(text[i]);
		//printf("%d\n", textdecimal[i]);
	}
}

int findindexofalphabet(char alphabet)
{
	char alpha[27]= "abcdefghijklmnopqrstuvwxyz";
	int i;
	for (i=0; i<26;i++){
		if (alphabet==alpha[i]){
			return i;
			break;
		}
	}
}
