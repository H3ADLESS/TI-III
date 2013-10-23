#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	char *eingabe = argv[1];
	float input = 0.0;
	input = atof(eingabe);

	float ergebnis;
	float teiler;
	teiler = (float)9/5;

	ergebnis = (teiler * input + 32.00000 );

	printf("Das Ergebnis ist %f. \n", ergebnis);

	printf("\n");
	printf("Umrechnungstabelle: \n");
	float i = -30.0;
	for (i= -30; i<=100; i=i+10){
		ergebnis = (teiler * (float)i + 32.00000 );	
		printf(" %f°C sind %f°F. \n", (float)i, ergebnis);
	}

	return 0;
}
