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
char encdec(char, char, bool);
char asciiToVignere(char, bool);

char in[INPUT_SIZE];

int main(int argc, char* *argv){
	
	char* leaver = argv[1];
	char* key = argv[2]; // We expect the input to be valid: means: only capital letters and numbers!
	char* inFile = argv[3];
	char* outFile = argv[4];
	
	readfile(inFile);	
	
	bool encrypt = TRUE;
	
	// Clean input text and convert to Vignere
	int i; int j; int x;
	for(i = 0, j = 0, x = 0; in[i]; i++){
		char current = asciiToVignere(in[i], encrypt);
		if(current != NULL){
			in[j] = encdec(current, &key[x], encdec); j++;
			if(!key[x++]){
				x = 0;
			}
		}
	
	/*
		if (in[i] > 96 && in[i] < 123){
			in[j] = in[i] - 32 -'A';j++;
		}else if(in[i] > 64 && in[i] < 91){
			in[j] = in[i] - 'A';j++;
		}else if(in[i] > 47 && in[i] < 58){
			in[j] = in[i] - 22;j++;
		}
		*/
	}
	in[j] = '\0';
	
	
	
	//printf("stuff: %s | i:%d + j:%d\n", in, i, j);
	
	return 0;
};

char encdec(char c, char key,  bool encrypt){
	if (encrypt)return c + asciiToVignere(key, encrypt);
	return c - asciiToVignere(key, encrypt);
}

char asciiToVignere(char c, bool encrypt){
	int a;int b;int d;
	if(encrypt){
		a = -32 - 'A'; b = -'A'; d = -22;
	}else{
		a = +32 + 'A'; b = +'A'; d = +22;
	}
	if(c > 96 && c < 123) return c + a;
	if(c > 64 && c < 91) return c + b;
	if(c > 47 && c < 58) return c + d;
	return NULL;
}

void readfile(char* filename){
	int n;	
	FILE *fr = fopen(filename, "rt");
	while(fgets(in, INPUT_SIZE, fr) != NULL);
} 