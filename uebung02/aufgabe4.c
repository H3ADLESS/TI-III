// -- do stuff
/*
Affe	<- buffer[100]
AFFE	<- convert()
0554	<- String to Vignere-Chiffre (- 'A')
1111	<- zb. B = 1 / <- buffer2[10] key 
1665
BGGF

./code -e key in.txt out.txt
-e -> Encode
-d -> Decode

*/
#define INPUT_SIZE 100
#define bool int
#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>

void readfile(char*);
void writefile(char*, char*);
char asciiToVignere(char);
char vignereToAscii(char);
char absq(char);

char in[INPUT_SIZE];

int main(int argc, char* *argv){
	char* leaver = argv[1]; if (leaver[0] != '-'){
		printf("nope..");
		return -1;
	}
	char* key = argv[2]; // We expect the input to be valid: means: only capital letters and numbers!
	char* inFile = argv[3];
	char* outFile = argv[4];
	readfile(inFile);	
	bool encrypt = FALSE;
	if (leaver[1]=='e')encrypt = TRUE;
	// clean input value and apply vignere
	int i; int j; int x;
    for(i = 0, j = 0, x = 0; in[i]; i++){
		if ((in[i] > 96 && in[i] < 123) || 	//'a - z'
			(in[i] > 64 && in[i] < 91) ||  	//'A - Z'
			(in[i] > 47 && in[i] < 58)){	//'0 - 9'
			if(encrypt){
				in[j] = vignereToAscii(
					( asciiToVignere(in[i]) + asciiToVignere(key[x]) ) % 36);
			}else{
				in[j] = vignereToAscii(
					( absq(asciiToVignere(in[i]) - asciiToVignere(key[x]))) % 36);
			}
			x++;
			if (!key[x] || x > 9){
				x = 0;
			}
			j++;
		}		
	}
	in[j] = '\0';	
	writefile(outFile, in);
	return 0;
}

char asciiToVignere(char c){
	if(c > 96 && c < 123) return c - 32 - 'A';
	if(c > 64 && c < 91) return c - 'A';
	return c - 22;
}

char vignereToAscii(char c){
	if(c >= 0 && c < 26) return c + 'A';
	return c + 22;
}

void readfile(char* filename){
	FILE *fr = fopen(filename, "rt");
	while(fgets(in, INPUT_SIZE, fr) != NULL);
} 

void writefile(char* filename, char* text){
	FILE *fp = fopen(filename, "w");
	if(fp){
		fprintf(fp, text);
		fclose(fp);
	}
}

char absq(char c){
	if (c > 0) return c;
	return c * (-1);
}