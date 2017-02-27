#include<stdio.h>
#include<conio.h>
#include<string.h>

void intoBinary(char hexadecimal);
void HextoBinary(char hextext[], char binarytext[]);
void createkeyplus(char key[], char keyplus[]);
void createsubkeys(char C[][28], char D[][28], char keys[][48]);
void printsubkeys(char C[][28], char D[][28], char keys[][48]);
void applyIP(char m[], char IP[]);
void createLR(char L[][32], char R[][32], char keys[][48]);
char XOR(char a, char b);
void intBinary(int hexadecimal);
void applyFP(char L[][32], char R[][32]);
void encrypt(char IPinverse[]);
int binarytohex();

char binary[4];

int main()
{
	
	char hexMessage[]="8787878787878787", hexKey[]="0E329232EA6D0D73";
	//hexMessage[]="123456ABCD132536", hexKey[]="AABB09182736CCDD";  //0123456789ABCDEF""133457799BBCDFF1";			
	char binaryMessage[64], binaryKey[64], keyplus[56], C[17][28],D[17][28], keys[16][48], IP[64],R[17][32],L[17][32];
	int i,j,k;

	printf("Hex Message:\t%s\n",hexMessage);
	printf("Hex key:\t%s\n",hexKey);	
	
	HextoBinary(hexMessage, binaryMessage);
	printf("Binary Message:\t");
	puts(binaryMessage);
	
	HextoBinary(hexKey, binaryKey);
	printf("Binary Key:\t");
	puts(binaryKey);
	
	createkeyplus(binaryKey, keyplus);
	printf("K+:\t\t");
	puts(keyplus);

	int index=0;
	for (i=0; i<56; i++){			//creates C0 and D0
		if (i<28){
			C[0][i]=keyplus[i];
		}else{
			D[0][index]=keyplus[i];
			index++;
		}
	}
	createsubkeys(C, D, keys);
	
	applyIP(binaryMessage, IP);
	index=0;
	for (i=0; i<64; i++){			//creates L0 and R0
		if (i<32){
			L[0][i]=IP[i];
		}else{
			R[0][index]=IP[i];
			index++;
		}
	}	
	
	createLR(L, R, keys);	
	applyFP(L, R);

	getch();
}
void applyFP(char L[][32], char R[][32])
{
	int FP[]={40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};
	char IPinverse[64], i;
	for (i=0; i<64; i++){
		if ((FP[i]-1)<32){
			IPinverse[i]=R[16][FP[i]-1];
		}else{
			IPinverse[i]=L[16][FP[i]-32-1];
		}
	}
	printf("\nIP':\t");
	for (i=0; i<64;i++){
		printf("%c", IPinverse[i]);
	}
	encrypt(IPinverse);
}
void encrypt(char IPinverse[])
{
	char ciphertext[16];
	int i,index=0;
	for (i=0; i<64;i=i+4){
		binary[0]=IPinverse[i];
		binary[1]=IPinverse[i+1];
		binary[2]=IPinverse[i+2];
		binary[3]=IPinverse[i+3];
		if (binarytohex()>9){
			ciphertext[index++]=binarytohex()+55;
		}else{
			ciphertext[index++]=binarytohex()+48;
		}
	}
	printf("\nCiphertext:");
	for (i=0; i<16; i++){
		printf("%c", ciphertext[i]);
	}
}
void createLR(char L[][32], char R[][32], char keys[][48])
{
	int i, j, k, l, row, column, index=0;
	int Ebit[]={32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
	char R48[48], fXOR[48], B[8][6], fXOR32[32], F[32], name[5];
	int S[8][4][16]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,13,0,11,7,4,9,1,10,14,3,5,12,2,1,8,6,1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};
	int P[]={16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
	for (i=0; i<16; i++){
		for (j=0; j<48; j++){
			R48[j]=R[i][Ebit[j]-1];
			fXOR[j]=XOR(R48[j] , keys[i+1][j]);
		}
		
		for (k=0; k<48;){
			for (j=0; j<8; j++){
				for (l=0; l<6; l++){
					B[j][l]=fXOR[k];
					k++;
				}		
			}
		}
		index=0;
		for (j=0; j<8; j++){
			if (B[j][0]=='0' && B[j][5]=='0'){
				row=0;
			}
			if (B[j][0]=='0' && B[j][5]=='1'){
				row=1;
			}
			if (B[j][0]=='1' && B[j][5]=='0'){
				row=2;
			}
			if (B[j][0]=='1' && B[j][5]=='1'){
				row=3;
			}
			binary[0]=B[j][1];
			binary[1]=B[j][2];
			binary[2]=B[j][3];
			binary[3]=B[j][4];
			column=binarytohex();
			intBinary(S[j][row][column]);
			fXOR32[index++]=binary[0];
			fXOR32[index++]=binary[1];
			fXOR32[index++]=binary[2];
			fXOR32[index++]=binary[3];
		}
		for (j=0; j<32; j++){
			F[j]=fXOR32[P[j]-1];
		}
		for (j=0; j<32; j++){
			L[i+1][j]=R[i][j];	
			R[i+1][j]=XOR(L[i][j] , F[j]);
		}		
	}
	printf("\n");
	for (i=0; i<=16; i++){
		sprintf(name,"L%d", i);
		printf("%s:\t", name);
		for (j=0; j<32; j++){
			printf("%c", L[i][j]);
		}
		sprintf(name,"R%d", i);
		printf("\t%s:\t", name);
		for (j=0; j<32; j++){
			printf("%c", R[i][j]);
		}
		printf("\n");
	}
	
		
}
char XOR(char a, char b)
{
	if (a!=b){
		return '1';
	}else{
		return '0';
	}
}

int binarytohex()
{
	int sum, hexa[4]={8,4,2,1};
	int i;
	sum=0;
	for (i=0; i<4; i++){
		if (binary[i]=='1'){
			sum=sum+hexa[i];
		}
	}
	return sum;
}
void applyIP(char m[], char IP[])
{
	int IPtable[]={58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
	int i;
	for (i=0; i<64; i++){
		IP[i]=m[IPtable[i]-1];
	}
	IP[i]='\0';
	printf("\nIP:\t%s", IP);
}
void printsubkeys(char C[][28], char D[][28], char keys[][48])
{
	int i, j;
	char name[3];
	printf("\n");
	for (i=0; i<=16; i++){
		sprintf(name, "C%d",i);
		printf("%s:\t", name);
		for (j=0; j<28; j++){	
			printf("%c", C[i][j]);
		}
		printf("\t");
		sprintf(name, "D%d",i);
		printf("%s:\t", name);
		for (j=0; j<28; j++){	
			printf("%c", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (i=0; i<16; i++){
		sprintf(name, "K%d", i+1);
		printf("%s:\t", name);
		for (j=0; j<48; j++){
			printf("%c", keys[i+1][j]);
		}
		printf("\n");
	}
}

void createsubkeys(char C[][28], char D[][28], char keys[][48])		//This functions create C1, D1, K1 to C16, D16, K16
{
	int shifts[]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	int PC_2[]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
	int i, j, k;
	for (i=0; i<16; i++){
		for (j=0; j<28; j++){
			C[i+1][j]=C[i][(j+shifts[i])%28];
			D[i+1][j]=D[i][(j+shifts[i])%28];
		}
	} 
	for (i=0; i<16; i++){
		for (j=0; j<48; j++){
			if ((PC_2[j]-1)<28){
				keys[i+1][j]=C[i+1][PC_2[j]-1];
			}else{
				keys[i+1][j]=D[i+1][PC_2[j]-28-1];
			}
			
		}
	}
	printsubkeys(C, D, keys);
}
void createkeyplus(char binaryKey[], char keyplus[])
{
	int PC_1[56]={57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
	int i;
	for (i=0; i<56; i++){
		keyplus[i]=binaryKey[(PC_1[i])-1];
	}
	keyplus[i]='\0';
}

void HextoBinary(char hextext[], char binarytext[])
{
	int i,index=0;
	for (i=0; hextext[i]!='\0';i++){
		intoBinary(hextext[i]);
		binarytext[index++]=binary[0];
		binarytext[index++]=binary[1];
		binarytext[index++]=binary[2];
		binarytext[index++]=binary[3];
	}
	binarytext[index]='\0';
}

void intoBinary(char hexadecimal)
{
	switch(hexadecimal)
	{
		case '0':
			{
				binary[0]='0';
				binary[1]='0';
				binary[2]='0';
				binary[3]='0';
				return;
			}
		case '1':
			{
				binary[0]='0';
				binary[1]='0';
				binary[2]='0';
				binary[3]='1';
				return;	
			}	
		case '2':
			{
				binary[0]='0';
				binary[1]='0';
				binary[2]='1';
				binary[3]='0';
				return;
			}
		case '3':
			{
				binary[0]='0';
				binary[1]='0';
				binary[2]='1';
				binary[3]='1';
				return;
			}
		case '4':
			{
				binary[0]='0';
				binary[1]='1';
				binary[2]='0';
				binary[3]='0';
				return;
			}
		case '5':
			{
				binary[0]='0';
				binary[1]='1';
				binary[2]='0';
				binary[3]='1';
				return;
			}
		case '6':
			{
				binary[0]='0';
				binary[1]='1';
				binary[2]='1';
				binary[3]='0';
				return;
			}
		case '7':
			{
				binary[0]='0';
				binary[1]='1';
				binary[2]='1';
				binary[3]='1';
				return;
			}
		case '8':
			{
				binary[0]='1';
				binary[1]='0';
				binary[2]='0';
				binary[3]='0';
				return;
			}
		case '9':
			{
				binary[0]='1';
				binary[1]='0';
				binary[2]='0';
				binary[3]='1';
				return;
			}
		case 'A': 
			{
				binary[0]='1';
				binary[1]='0';
				binary[2]='1';
				binary[3]='0';
				return;
			}
		case 'B' :
			{
				binary[0]='1';
				binary[1]='0';
				binary[2]='1';
				binary[3]='1';
				return;
			}
		case 'C' :
			{
				binary[0]='1';
				binary[1]='1';
				binary[2]='0';
				binary[3]='0';
				return;
			}
		case 'D' :
			{
				binary[0]='1';
				binary[1]='1';
				binary[2]='0';
				binary[3]='1';
				return;
			}
		case 'E' :
			{
				binary[0]='1';
				binary[1]='1';
				binary[2]='1';
				binary[3]='0';
				return;
			}
		case 'F' :
			{
				binary[0]='1';
				binary[1]='1';
				binary[2]='1';
				binary[3]='1';
				return;
			}
	}
}

void intBinary(int hexadecimal)
{
	switch(hexadecimal)
	{
		case 0:
			{
				binary[0]='0';
				binary[1]='0';
				binary[2]='0';
				binary[3]='0';
				return;
			}
		case 1:
			{
				binary[0]='0';
				binary[1]='0';
				binary[2]='0';
				binary[3]='1';
				return;	
			}	
		case 2:
			{
				binary[0]='0';
				binary[1]='0';
				binary[2]='1';
				binary[3]='0';
				return;
			}
		case 3:
			{
				binary[0]='0';
				binary[1]='0';
				binary[2]='1';
				binary[3]='1';
				return;
			}
		case 4:
			{
				binary[0]='0';
				binary[1]='1';
				binary[2]='0';
				binary[3]='0';
				return;
			}
		case 5:
			{
				binary[0]='0';
				binary[1]='1';
				binary[2]='0';
				binary[3]='1';
				return;
			}
		case 6:
			{
				binary[0]='0';
				binary[1]='1';
				binary[2]='1';
				binary[3]='0';
				return;
			}
		case 7:
			{
				binary[0]='0';
				binary[1]='1';
				binary[2]='1';
				binary[3]='1';
				return;
			}
		case 8:
			{
				binary[0]='1';
				binary[1]='0';
				binary[2]='0';
				binary[3]='0';
				return;
			}
		case 9:
			{
				binary[0]='1';
				binary[1]='0';
				binary[2]='0';
				binary[3]='1';
				return;
			}
		case 10: 
			{
				binary[0]='1';
				binary[1]='0';
				binary[2]='1';
				binary[3]='0';
				return;
			}
		case 11 :
			{
				binary[0]='1';
				binary[1]='0';
				binary[2]='1';
				binary[3]='1';
				return;
			}
		case 12 :
			{
				binary[0]='1';
				binary[1]='1';
				binary[2]='0';
				binary[3]='0';
				return;
			}
		case 13 :
			{
				binary[0]='1';
				binary[1]='1';
				binary[2]='0';
				binary[3]='1';
				return;
			}
		case 14 :
			{
				binary[0]='1';
				binary[1]='1';
				binary[2]='1';
				binary[3]='0';
				return;
			}
		case 15 :
			{
				binary[0]='1';
				binary[1]='1';
				binary[2]='1';
				binary[3]='1';
				return;
			}
	}
}


