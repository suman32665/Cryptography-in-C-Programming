#include<stdio.h>
#include<conio.h>
#include<string.h>
void getinput(char key[], char plaintext[]);
void removesameletter(char text[], char modifiedtext[]);
int findindexofalphabet(char letter);
void createkeymatrix(int keymatrix[5][5], char key[]);
int checkmatrix(int keymatrix[5][5], int index);
void encryption(char plaintext[],int keymatrix[5][5], char encrypted[]);
void decryption(char encrypted[], int keymatrix[5][5], char decrypted[]);

int main()
{
	char key[20], plaintext[100], modifiedtext[20], encrypted[100], decrypted[100];
	int keymatrix[5][5]={30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30};
	
	getinput(key, plaintext);
	removesameletter(key, modifiedtext);
	createkeymatrix(keymatrix, modifiedtext);	
	encryption(plaintext, keymatrix, encrypted);
	decryption(strlwr(encrypted), keymatrix, decrypted);
	
}

void getinput(char key[], char plaintext[])
{
	puts("Enter the Message:");
	gets(plaintext);
	strlwr(plaintext);
	puts("KEY:");
	gets(key);
	strlwr(key);
}

void removesameletter(char text[], char modifiedtext[])
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
int findindexofalphabet(char letter)
{
	char alpha[27]= "abcdefghijklmnopqrstuvwxyz";
	int i;
	for (i=0; alpha[i]!=NULL;i++){
		if (letter==alpha[i]){
			return i;
		}
	}
	
}
int checkmatrix(int keymatrix[5][5], int index)
{
	int i, j, flag=0;
	for (i=0; i<5; i++){
		for (j=0; j<5; j++){
			if (index==keymatrix[i][j]){
				flag=1;
				break;
			}
		}
	}
	if (flag==1){
		return 0;
	}else{
		return 1;
	}
}
void createkeymatrix(int keymatrix[5][5],char key[])
{
	int i, j, k, index=0;
	char alpha[27]= "abcdefghiklmnopqrstuvwxyz";
	char alphas[27]= "abcdefghijklmnopqrstuvwxyz";
	for (i=0; i<5; i++){
		for (j=0; j<5; j++){
			if (index != strlen(key)){
				keymatrix[i][j]=findindexofalphabet(key[index]);
				index++;
			}else{
				break;
			}
		}
	}
	for (i=0; i<5;i++){
		for (j=0; j<5; j++){
			for (k=0; alpha[k]!=NULL;k++){
					if (keymatrix[i][j]==30 && checkmatrix(keymatrix,findindexofalphabet(alpha[k]))){
						keymatrix[i][j]=findindexofalphabet(alpha[k]);
				}	
			}
			printf("%c\t", alphas[keymatrix[i][j]]);
		}
		printf("\n");
	}
}

void encryption(char plaintext[],int keymatrix[5][5], char encrypted[])
{
	int i, j, k, index=0, length, index1, j1, k1, j2, k2, encryptindex=0;
	char alpha[27]= "abcdefghijklmnopqrstuvwxyz";
	char modifiedtext[50];
	for (i=0;plaintext[i]!=NULL;i++){
		if (plaintext[i]==plaintext[i+1]){
			modifiedtext[index]=plaintext[i];
			index++;
			modifiedtext[index]='X';
			index++;
		}else{
			modifiedtext[index]=plaintext[i];
			index++;
			modifiedtext[index]=plaintext[i+1];
			index++;
			i++;
		}
	}
	if (index%2==0){
		modifiedtext[index]='\0';
	}
	length=strlen(modifiedtext);
	modifiedtext[length]=NULL;
	if (length%2!=0){
		modifiedtext[length]='X';
		modifiedtext[length+1]='\0';
	}
//	puts(modifiedtext);
	strlwr(modifiedtext);
	for (i=0; i<length;i++){				
		index=findindexofalphabet(modifiedtext[i]);
		index1=findindexofalphabet(modifiedtext[i+1]);
		if (index==9){
			index--;
		}
		if (index1==9){
			index1--;
		}
		for (j=0; j<5;j++){
			for (k=0; k<5; k++){
				if (keymatrix[j][k]==index){
					j1=j;
					k1=k;
				}
				if (keymatrix[j][k]==index1){
					j2=j;
					k2=k;
				}
			}
		}
		if (j1==j2){
			encrypted[encryptindex]=alpha[(keymatrix[j1][((k1+1)%5)])];
			encryptindex++;
			encrypted[encryptindex]=alpha[(keymatrix[j2][((k2+1)%5)])];
			encryptindex++;
		}else{
			if (k1==k2){
				encrypted[encryptindex]=alpha[(keymatrix[((j1+1)%5)][k1])];
				encryptindex++;
				encrypted[encryptindex]=alpha[(keymatrix[((j2+1)%5)][k2])];
				encryptindex++;
			}else{
				encrypted[encryptindex]=alpha[(keymatrix[j1][k2])];
				encryptindex++;
				encrypted[encryptindex]=alpha[(keymatrix[j2][k1])];
				encryptindex++;
			}
		}
		i++;
	}
	encrypted[encryptindex]=NULL;
	puts("ENCRYPTED Message:");
	puts(strupr(encrypted));
}
	
void decryption(char encrypted[], int keymatrix[5][5], char decrypted[])
{
	int i, j, k, length, j1, j2, k1, k2, index, index1, decryptindex=0;
	char alpha[27]= "abcdefghijklmnopqrstuvwxyz";
	length=strlen(encrypted);
	for (i=0; i<length;i++){				
		index=findindexofalphabet(encrypted[i]);
		index1=findindexofalphabet(encrypted[i+1]);
		if (index==9){
			index--;
		}
		if (index1==9){
			index1--;
		}
		for (j=0; j<5;j++){
			for (k=0; k<5; k++){
				if (keymatrix[j][k]==index){
					j1=j;
					k1=k;
				}
				if (keymatrix[j][k]==index1){
					j2=j;
					k2=k;
				}
			}
		}
		if (j1==j2){
			decrypted[decryptindex]=alpha[(keymatrix[j1][((k1-1)%5)])];
			decryptindex++;
			decrypted[decryptindex]=alpha[(keymatrix[j2][((k2-1)%5)])];
			decryptindex++;
		}else{
			if (k1==k2){
				decrypted[decryptindex]=alpha[(keymatrix[((j1-1)%5)][k1])];
				decryptindex++;
				decrypted[decryptindex]=alpha[(keymatrix[((j2-1)%5)][k2])];
				decryptindex++;
			}else{
				decrypted[decryptindex]=alpha[(keymatrix[j1][k2])];
				decryptindex++;
				decrypted[decryptindex]=alpha[(keymatrix[j2][k1])];
				decryptindex++;
			}
		}
		i++;
	}
	decrypted[decryptindex]=NULL;
	puts("\n\nDECRYPTED Message:");
	puts(strupr(decrypted));
}




