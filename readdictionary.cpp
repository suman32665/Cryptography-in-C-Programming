#include<stdio.h>
#include<conio.h>
#include<string.h>
int main()
{
   	FILE *ptr_file;
   	char buf[100], text[100];
 	ptr_file =fopen("dictionary.txt","r");
 	gets(text);
   	if (!ptr_file)
	   	return 1;
      		
    while (fgets(buf,100, ptr_file)!=NULL){
		fscanf(ptr_file,"%s",buf);
		if (strcmp(buf, text) == 0){
			puts(buf);
			break;
		}
	}
	fclose(ptr_file);
	getch();
}
