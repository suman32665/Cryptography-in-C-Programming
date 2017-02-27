#include<stdio.h>
#include<conio.h>
#include<string.h>

void vigenerecipher(char message[], char key[]);
void vigeneredecipher(char encrypted[], char key[]);
void convertkeyandtext(char text[], char key[], char converted[]);

int main()
{
	char key[20], message[100];
	puts("Enter Message:");
	gets(message);
	puts("Enter key:");
	gets(key);
	
	vigenerecipher(message, key);
	
}

void convertkeyandtext(char text[], char key[], char converted[])
{
	int i, k=0, index=0;
	for (i=0; text[i]!=NULL; i++){
		if (text[i]!=' '){
			converted[index]=key[(k+strlen(key))%strlen(key)];
			index++;
			converted[index]=text[i];
			index++;
			k++;	
		}else{
			converted[index]=' ';
			index++;
		}	
	}
	converted[index]==NULL;
}
void vigenerecipher(char message[], char key[])
{
	char alphabet[27]="abcdefghijklmnopqrstuvwxyz";
	char beforencrypted[100], encrypted[100];
	int i, j, k=0, keyindex, messageindex;

	convertkeyandtext(message, key, beforencrypted);
	for (i=0; beforencrypted[i]!=NULL; i++){
		if (beforencrypted[i] != ' '){
			for (j=0; alphabet[j]!=NULL;j++){
				if (beforencrypted[i]==alphabet[j]){
					keyindex=j;
				}
				if (beforencrypted[i+1]==alphabet[j]){
					messageindex=j;
				}
			}
			encrypted[k]=alphabet[(keyindex+messageindex)%26];
			k++;
			i++;
		}else{
			encrypted[k]=' ';
			k++;
		}
	}
	encrypted[strlen(message)]=NULL;
	puts("Encrypted Message:");
	puts(strupr(encrypted));
	vigeneredecipher(strlwr(encrypted), key);	
}

void vigeneredecipher(char encrypted[], char key[])
{
	char alphabet[27]="abcdefghijklmnopqrstuvwxyz";
	char beforedecrypted[100], decrypted[100];
	int i, j, k=0, messageindex, keyindex;
	
	convertkeyandtext(encrypted, key, beforedecrypted);
	
	for (i=0; beforedecrypted[i]!=NULL; i++){
		if (beforedecrypted[i] != ' '){
			for (j=0; alphabet[j]!=NULL;j++){
				if (beforedecrypted[i]==alphabet[j]){
					keyindex=j;
				}
				if (beforedecrypted[i+1]==alphabet[j]){
					messageindex=j;
				}
			}
			decrypted[k]=alphabet[(messageindex-keyindex+26)%26];
			k++;
			i++;
		}else{
			decrypted[k]=' ';
			k++;
		}
	}
	decrypted[strlen(encrypted)]=NULL;
	puts("\nDecrypted Message:");
	puts(decrypted);
	
}
