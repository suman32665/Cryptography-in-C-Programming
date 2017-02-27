#include<stdio.h>
#include<string.h>
int substitutebytes_transformation(char state_array[5][5][3], char substitute_array[5][5][3]);
int shiftrows_transformation(char substitute_array[5][5][3], char shifted_array[5][5][3]);
int number_return(char letter);
char hex_return(int number);
int XOR_key(char plaintext[5][5][3], char array_afterroundkey[5][5][3]);

int main()
{
	char input_bytes[17][3]={"54", "77", "6F", "20", "4F", "6E", "65", "20", "4E", "69", "6E", "65", "20", "54", "77", "6F"};
	char state_array[5][5][3], shifted_array[5][5][3], substitute_array[5][5][3];
	char array_afterroundkey[5][5][3];
	int i, j, k;
	puts("INPUT BYTES");
	for (i=0; i<16; i++){
		printf("%s\t", input_bytes[i]);
		if ((i+1)%4==0){
			printf("\n");
		}
	}
	puts("State Array:");
	for (i=0; i<4; i++){
		for (j=0; j<4; j++){
			for (k=0; k<2; k++){
				state_array[i][j][k]= input_bytes[i + 4*j][k];
			}
			state_array[i][j][k] = NULL;	
			printf("%s\t", state_array[i][j]);
		}
		printf("\n");
	}
	
	XOR_key(state_array,array_afterroundkey);
	substitutebytes_transformation(array_afterroundkey, substitute_array);
	shiftrows_transformation(substitute_array, shifted_array);
}
int XOR_key(char plaintext[5][5][3],char array_afterroundkey[5][5][3])
{
//	char plaintext[5][5][3]={"54", "4F","4E", "20", "77", "6E", "69", "54", "6F","65","6E", "77", "20", "20", "65", "6F"};
	char key[4][4][3]={"54", "73", "20", "67", "68", "20", "4B", "20", "61", "6D", "75", "46", "74", "79", "6E", "75"};
	puts("KEY MATRIX");
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			printf("%s\t", key[i][j]);
		}
		printf("\n");
	}
	puts("AFTER ADD ROUND KEY");
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			array_afterroundkey[i][j][0]=hex_return(number_return(plaintext[i][j][0])^number_return(key[i][j][0]));
			array_afterroundkey[i][j][1]=hex_return(number_return(plaintext[i][j][1])^number_return(key[i][j][1]));
			array_afterroundkey[i][j][2]=NULL;
			printf("%s\t", array_afterroundkey[i][j]);
		}
		printf("\n");
	}
}

int shiftrows_transformation(char substitute_array[5][5][3], char shifted_array[5][5][3])
{
	int i, j;
	printf("\nSHIFTED ARRAY\n");
	for (i=0; i<4; i++){
		for (j=0; j<4; j++){
			shifted_array[i][j][0]=substitute_array[i][(j+i)%4][0];
			shifted_array[i][j][1]=substitute_array[i][(j+i)%4][1];
			shifted_array[i][j][2]=NULL;
			printf("%s\t", shifted_array[i][j]);
		}
		printf("\n");
	}	
}

int substitutebytes_transformation(char state_array[5][5][3], char substitute_array[5][5][3])
{
	int i, j;
	char s_box[16][16][3]={"63", "7C", "77", "7B", "F2","6B", "6F", "C5", "30", "01", "67", "2B", "FE", "D7", "AB", "76",
						 "CA", "82", "C9", "7D", "FA", "59", "47", "F0", "AD", "D4", "A2", "AF", "9C","A4", "72", "C0", 
						 "B7", "FD", "93", "26", "36", "3F", "F7", "CC", "34", "A5", "E5", "F1", "71", "D8", "31", "15",
						 "04", "C7", "23", "C3", "18", "96", "05", "9A", "07", "12", "80", "E2", "EB", "27", "B2", "75",
						 "09", "83", "2C", "1A", "1B", "6E", "5A", "A0", "52", "3B", "D6", "B3", "29", "E3", "2F", "84",
						 "53", "D1", "00", "ED", "20", "FC", "B1", "5B", "6A", "CB", "BE", "39", "4A", "4C", "58", "CF",
						  "D0", "EF", "AA", "FB", "43", "4D", "33", "85", "45", "F9", "02", "7F", "50", "3C", "9F", "A8", 
						  "51", "A3", "40", "8F", "92", "9D", "38", "F5", "BC", "B6", "DA", "21", "10", "FF", "F3", "D2", 
						  "CD", "0C", "13", "EC", "5F", "97", "44", "17", "C4", "A7", "7E", "3D", "64", "5D", "19", "73", 
						  "60", "81", "4F", "DC", "22", "2A", "90", "88", "46", "EE", "B8", "14", "DE", "5E", "0B", "DB", 
						  "E0", "32", "3A", "0A", "49", "06", "24", "5C", "C2", "D3", "AC", "62", "91", "95", "E4", "79", 
						  "E7", "C8", "37", "6D", "8D", "D5", "4E", "A9", "6C", "56", "F4", "EA", "65", "7A", "AE", "08", 
						  "BA", "78", "25", "2E", "1C", "A6", "B4", "C6", "E8", "DD", "74", "1F", "4B", "BD", "8B", "8A", 
						  "70", "3E", "B5", "66", "48", "03", "F6", "0E", "61", "35", "57", "B9", "86", "C1", "1D", "9E", 
						  "E1", "F8", "98", "11", "69", "D9", "8E", "94", "9B", "1E", "87", "E9", "CE", "55", "28", "DF",
						  "8C", "A1", "89", "0D", "BF", "E6", "42", "68", "41", "99", "2D", "0F", "B0", "54", "BB", "16"};
		printf("Substituted Array\n");
		for (i=0; i<4; i++){
			for (j=0; j<4; j++){
				substitute_array[i][j][0]=s_box[number_return(state_array[i][j][0])][number_return(state_array[i][j][1])][0];
				substitute_array[i][j][1]=s_box[number_return(state_array[i][j][0])][number_return(state_array[i][j][1])][1];
				substitute_array[i][j][2]=NULL;
				printf("%s\t", substitute_array[i][j]);
			}
			printf("\n");
		}
	
}
int number_return(char letter)
{
	char hex[17]={"0123456789ABCDEF"};
	
	int i;
	for (i=0; i<16;i++){
		if (letter==hex[i]){
			return i;
		}
	}                    
}
char hex_return(int number)
{
	char hex[17]={"0123456789ABCDEF"};
	return hex[number];
}
