#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<math.h>
int findindex(char letter);
void encryption(char message[], int key[3][3]);
void matrixmultiplication(int key[3][3],int msgmatrix[5][5],char text[],int msgcolumn);
void decryption(char encrypted[], int key[3][3]);
int greatestcommondivisor(int a, int b);
int row,column;
int main()
{
	char message[50], alphabet[]="abcdefghijklmnopqrstuvwxyz";
	int key[3][3];
	int i,j;
	puts("Enter the Message:");
	gets(message);
	puts("Enter row and column size:");
	scanf("%d%d", &row, &column);
	puts("Enter the Key:");
	for (i=0; i<row;i++){						//takes input
		for (j=0; j<column;j++){
			scanf("%d", &key[i][j]);
		}
	}
	printf("\n");
	
	encryption(message, key);	
	//decryption(message, key);
}
void encryption(char message[], int key[3][3])
{
	
	int msgmatrix[5][5], i,j, messageindex=0, msgcolumn;
	char encryptedtext[50];
	
	if (row==2 && column==2){
		if (strlen(message)%2!=0){
		message[strlen(message)]='x';			//balances string if it is odd
		message[strlen(message)+1]='\0';
		}	
	}else{
		if (row==3 && column == 3){
			if (strlen(message)%3==2){
				message[strlen(message)]='x';
				message[strlen(message)+1]='\0';
			}
			if (strlen(message)%3==1){
				message[strlen(message)]='x';
				message[strlen(message)+1]='x';
				message[strlen(message)+2]='\0';
			}
		}
	}
	msgcolumn=strlen(message)/row;
	for (i=0; i<msgcolumn;i++){
		for (j=0; j<row;j++){				//converting plaintext into matrix
			msgmatrix[j][i]=findindex(message[messageindex]);
			messageindex++;
		}
	}
	
//	puts(message);
	
	matrixmultiplication(key, msgmatrix, encryptedtext, msgcolumn);
	puts("Encrypted:");
	puts(strupr(encryptedtext));		//display encryptedtext
	decryption(strlwr(encryptedtext), key);
}


void decryption(char encrypted[], int key[3][3])
{
	int i, j,x, detkey, detkeyinverse, temp, encryptindex=0, encryptedmatrix[5][5], encryptcolumn, keyinverse[3][3];
	char decryptedtext[50];
//	puts(encrypted);
	if (row==2 && column==2){			//finds determinant of 2*2 matrix
		detkey=key[0][0]*key[1][1] - key[1][0]*key[0][1];
	}else{
		if (row==3 && column==3){			//finds determinant of 3*3 matrix
			detkey = key[0][0]*((key[1][1]*key[2][2]) - (key[2][1]*key[1][2])) -key[0][1]*(key[1][0]*key[2][2] - key[2][0]*key[1][2]) + key[0][2]*(key[1][0]*key[2][1] - key[2][0]*key[1][1]);
		}			
	}
	
	if (detkey>25 || detkey < 0){
		detkey=detkey%26;
	}
	if (detkey<0){
		detkey=detkey+26;
	}
	if (greatestcommondivisor(detkey, 26)==1){
	for (x=0; x<1000; x++){
		if ((detkey*x)%26==1){				//finds determinant inverse 
			detkeyinverse=x;
			//printf("%d", detkeyinverse);
			break;
		}
	}
	if (row==2 && column==2){
		keyinverse[0][0]=((key[row-1][column-1])*detkeyinverse)%26;
		keyinverse[row-1][column-1]=(key[0][0]*detkeyinverse)%26;
	
		for (i=0;i<row;i++){
			for (j=0; j<column;j++){		//calculating inverse matrix of key of 2*2 matrix
				if (i!=j){
					keyinverse[i][j]=((-key[i][j]+26)*detkeyinverse)%26;
				}
			}
		}		
	}else{
		if (row==3 && column==3){
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					keyinverse[j][i]=((key[(i+1)%3][(j+1)%3] * key[(i+2)%3][(j+2)%3])-(key[(i+1)%3][(j+2)%3]*key[(i+2)%3][(j+1)%3]))%26;	//calculates adjoint of 3*3 matrix
					if (keyinverse[j][i]<0){
						keyinverse[j][i]=keyinverse[j][i]+26;
					}
					keyinverse[j][i]=(keyinverse[j][i]*detkeyinverse)%26;		//calculates inverse matrix of key of 3*3 matrix
					if (keyinverse[j][i]<0){
						keyinverse[j][i]=keyinverse[j][i]+26;
					}
				}
			}	
		}
	}
	
	encryptcolumn=strlen(encrypted)/row;
	for (i=0; i<encryptcolumn;i++){				//converting encrypted text into matrix
		for (j=0; j<row;j++){
			encryptedmatrix[j][i]=findindex(encrypted[encryptindex]);
			encryptindex++;
		}
	}
	matrixmultiplication(keyinverse, encryptedmatrix, decryptedtext, encryptcolumn);
	puts("Decrypted:");
	puts(strupr(decryptedtext));
	}else{
		printf("There is no multiplicative inverse of %d and 26.", detkey);
	}
}

void matrixmultiplication(int key[3][3],int msgmatrix[5][5],char text[],int msgcolumn)
{
	int multipliedmatrix[5][5];
	int i, j, k, textindex=0;
	char alphabet[]="abcdefghijklmnopqrstuvwxyz";
	for (i=0; i<row; i++){				//multiplies any order of matrix
		for (j=0; j<msgcolumn;j++){
			multipliedmatrix[i][j]=0;
			for (k=0; k<column; k++){
				multipliedmatrix[i][j]+=key[i][k]*msgmatrix[k][j];
				multipliedmatrix[i][j]=multipliedmatrix[i][j]%26;
			}
		}
	}
	for (i=0; i<msgcolumn;i++){			//convert multiplied matrix into text
		for (j=0; j<row;j++){
			text[textindex]=alphabet[multipliedmatrix[j][i]];
			textindex++;
		}
	}
	text[textindex]='\0';
}

int findindex(char letter)		//returns an index of an alphabet
{
	char alphabet[]="abcdefghijklmnopqrstuvwxyz";	
	int i, j;
	for (i=0; i<26;i++){
		if (letter==alphabet[i]){
			return i;
		}
	}
}

int greatestcommondivisor(int a, int b)		//check if gcd of two number is 1 or not
{
	int i;
	for (i=2; i<=b; i++){
		if (a%i==0 && b%i==0){
			return i;
		}else{
			return 1;
		}
	}
}
