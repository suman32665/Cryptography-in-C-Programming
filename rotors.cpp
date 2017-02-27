#include<iostream>
#include<cstdlib>
#include<time.h>
#include<string.h>

using namespace std;

class Rotors{
	int in[26], out[26];
	public: void fillArray()
	{			
		for (int i=0; i<26; i++){
			in[i]=i;
			checkandfill(i);
		}
	}
	public: void checkandfill(int i)
	{
		int randomnumber, flag=0;
		
		randomnumber=rand()%26;
		for (int j=0; j<i; j++){
			if (out[j]==randomnumber){
				flag=1;
			}
		}
		if (flag==0){
			out[i]=randomnumber;	
		}else{
			checkandfill(i);
		}
		
	}
	
	public: void printArray()
	{
		cout<<"\n\nIN\t";
		for (int i=0; i<26;i++){
			cout<<in[i]<<"   |";
		}
		cout<<"\nOUT\t";
		for (int i=0; i<26;i++){
			cout<<out[i]<<"   |";
		}
		cout<<"\n";
	}
	public: int encrypt(char letter)
	{
		char alphabet[27]="abcdefghijklmnopqrstuvwxyz";
		int i, j, first, second;
		for (i=0; i<26; i++){
			if (letter==alphabet[i]){
				for (j=0; j<26; j++){
					if (in[j]==i){
						first=in[j];
						second=j;
						break;
					}
				}
				break;
			}
		}
		cout<<"first="<<first<<"   "<<"second="<<out[second]<<" \t\t|";
		return out[second];
	}
	public: int decrypt(char letter)
	{
		char alphabet[27]="abcdefghijklmnopqrstuvwxyz";
		int i, j, first, second;
		for (i=0; i<26; i++){
			if (letter==alphabet[i]){
				for (j=0; j<26; j++){
					if (out[j]==i){
						first=out[j];
						second=j;
						break;
					}
				}
				break;
			}
		}
		cout<<"first="<<first<<"   "<<"second="<<out[second]<<" \t\t|";
		return in[second];
	}
};

int main()
{
	Rotors rotor1, rotor2, rotor3;
	srand(time(NULL));
	char alphabet[27]="abcdefghijklmnopqrstuvwxyz", plaintext[50], ciphertext[50], decrypttext[50];
	
	cout<<"Enter the plaintext:";
	cin>>plaintext;
	
	rotor1.fillArray();
	rotor1.printArray();
	
	rotor2.fillArray();
	rotor2.printArray();
		
	rotor3.fillArray();
	rotor3.printArray();
	for (int i=0; i<strlen(plaintext); i++){
		ciphertext[i]=alphabet[rotor1.encrypt(plaintext[i])];
		ciphertext[i]=alphabet[rotor2.encrypt(ciphertext[i])];
		ciphertext[i]=alphabet[rotor3.encrypt(ciphertext[i])];
		cout<<"\n\n";
	}
	cout<<"Ciphertext:"<<ciphertext<<"\n";
	
	for (int i=0; i<strlen(ciphertext); i++){
		decrypttext[i]=alphabet[rotor3.decrypt(ciphertext[i])];
		decrypttext[i]=alphabet[rotor2.decrypt(decrypttext[i])];
		decrypttext[i]=alphabet[rotor1.decrypt(decrypttext[i])];
		cout<<"\n\n";
	}
	cout<<"Decrypttext:"<<decrypttext<<"\n";
}

