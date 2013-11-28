/**
 * File: trashcan.c
 * TI 2 - Betriebs- und Kommunikationssysteme
 * Freie Universitaet Berlin
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE			1024
#define PATHSIZE		256
#define TRASHFOLDER	".ti3_trash"	

#ifdef __unix__
      #include <unistd.h>
#elif __MSDOS__ || __WIN32__ || _MSC_VER
      #include <io.h>
#endif


char copy_buffer[BUFSIZE];


/* 'copy' kopiert den Dateiinhalt einer Datei namens 
 * "source". Eine Kopie target wird nur erzeugt, wenn 
 * eine Datei "target" noch nicht existiert.
 * Die Zugriffsrechte werden nicht kopiert, sondern
 * auf "rwx --- ---" gesetzt.
 */
int copy(char *source, char *target)
{
	int f1;
	int f2;
	int counter_data;
	int const buffersize = 100;
	char buffer[buffersize];

	if((f1 = open(source,O_RDONLY)) == -1){
		perror("nop src load\n");
		return -1;	
	}

	if((f2 = open(target,O_WRONLY|O_EXCL|O_CREAT,S_IRWXU)) == -1){
		perror("nop targ load\n");
		return -2;	
	}

	while(counter_data = read(f1,buffer,buffersize)){
		write(f2,buffer,counter_data);
	}

	close(f1);
	close(f2);
	return 0;
}


char parse_command(char *command)
{
	return command[1];
}


/* erzeugt einen Ordner foldername */
int setup_trashcan(char *foldername)
{
	int stat;
	if((stat=mkdir(foldername,S_IRWXU)) == -1){
		return;	
	}
}

/* führt trashcan -p[ut] filename aus */
int put_file(char *foldername, char *filename)
{
	setup_trashcan(foldername);
	char *target = (char *) malloc(250);
 
	strcat(target,foldername);
	strcat(target,"/");
	strcat(target,filename);

	copy(filename,target);

	if(remove(filename) != 0)
		perror("fuck fehler.\n");
}


/* führt trashcan -g[et] filename aus */
int get_file(char *foldername, char *filename)
{
	struct stat st;
	char puffer[200];

   
	char *source = (char *) malloc(250);
	char *target = (char *) malloc(250);

	strcat(source,foldername);
	strcat(source,"/");
	strcat(source,filename);	

	if(stat(source,&st) !=0 ){
		perror("nanana.\n");
		return -1;
	}

	if(getcwd(puffer,sizeof(puffer)) == -1)
		perror("lululu\n");
	
	strcat(target,puffer);
	strcat(target,"/");
	strcat(target,filename);

	copy(source,target);		

	if(remove(source) != 0)
		perror("lalalalal\n");
}

/* führt trashcan -r[emove] filename aus */
int remove_file(char *foldername, char *filename)
{
	char *target = (char *) malloc(250);

	strcat(target, foldername);
	strcat(target,"/");
	strcat(target,filename);	

	remove(target);	
}


int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("...not enough arguments!\n");
		return EXIT_FAILURE;
	} else {
		setup_trashcan(TRASHFOLDER);
		char command = parse_command(argv[1]);
		switch (command) {
			case 'p':
				if (argc != 3) {
					printf("...not enough arguments!\n");
					return EXIT_FAILURE;
				}
				int p_error = put_file(TRASHFOLDER, argv[2]);
				switch (p_error) {
					case -1:
						printf("...source file not found!\n");
						break;
					case -2:
						printf("...trash file was not created!\n");
						break;
					case -3:
						printf("...source file could not be removed!\n");
					default:
						break;
				}
				break;
			case 'g':
				if (argc != 3) {
					printf("...not enough arguments!\n");
					return EXIT_FAILURE;
				}
				int g_error = get_file(TRASHFOLDER, argv[2]);
				switch (g_error) {
					case -1:
						printf("...trash file not found!\n");
						break;
					case -2:
						printf("...restore file was not created!\n");
						break;
					case -3:
						printf("...trash file could not be removed!\n");
					default:
						break;
				}
				break;
			case 'r':
				if (argc != 3) {
					printf("...not enough arguments!\n");
					return EXIT_FAILURE;
				}
				int r_error = remove_file(TRASHFOLDER, argv[2]);
				if (r_error)
					printf("...trash file could not be removed!\n");
				break;
			default :
				printf("...unknown command!\n");
				return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}
