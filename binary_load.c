/**
 * @author: Andrei Stefanescu
 * @date: 28.01.2015
 *
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define USAGE "Default usage: %s [-f file] [-s separator] modif1 modi2\n"

#define ERROR_PARAM -1
#define ERROR_IO -2
#define DEFAULT_SIZE 24
#define ERROR_MEM -3

char append(char **str, int *current, int *max, FILE *fp) {
	if(*current == *max) {
		(*max) *= 2;
		char *temp = (char*)realloc(*str, (*max) * sizeof(char));

		if(!temp) {
			fprintf(stderr, "Out of mmory...\n");
			if(fp != stdin) {
				fclose(fp);
			}

			exit(ERROR_MEM);
		}
		*str = temp;
	}
	
	char c;
	fread(&c, sizeof(char), 1, fp);	
	*(*str + *current) = c;
	++ (*current);

	return c;
}

int main(int argc, char *argv[]) {

	if(argc < 2) {
		fprintf(
			stderr, 
			USAGE,
			argv[0]
		);

		return ERROR_PARAM;
	}


	FILE *fp = NULL;
	int i;
	char flag = 0;
	char separator[DEFAULT_SIZE];
	strcpy(separator, " ");

	for(i = 1; i < argc; ++ i) {

		if(strcmp(argv[i], "-f") == 0) {
			if(i == argc - 1) {
				fprintf(
					stderr, 
					USAGE,
					argv[0]
				);
				return ERROR_PARAM;

			} 
			
			if(!(fp = fopen(argv[i + 1], "rb"))) {
				fprintf(stderr, "Unable to open file: %s", argv[i + 1]);
				return ERROR_IO;
			}
			flag = 1;
		} else if(strcmp(argv[i], "-s") == 0) {
			if(i == argc - 1) {
				fprintf(
					stderr, 
					USAGE,
					argv[0]	
				);
				return ERROR_PARAM;
			}
			++ i;
			strcpy(separator, argv[i]);
		}
	}

	if(!flag) {
		fp = stdin;
	}

	for(i = 1; i < argc; ++ i) {
		if(strcmp(argv[i], "-f") == 0 || 
			strcmp(argv[i], "-s") == 0) {
			++ i; /* jump 1 step here and one in the for */
			continue;
		}

		if(!strcmp(argv[i], "%d")) {
			if(i == argc - 1) {
				fprintf(
					stderr, 
					USAGE,
					argv[0]
				);
			}
			int rez;
			fread(&rez, sizeof(int), 1, fp);
			printf("%d%s", rez, separator);
		} else if(!strcmp(argv[i], "%f")) {
			float rez;
			fread(&rez, sizeof(float), 1, fp);
			printf("%f%s", rez, separator);


		} else if(!strcmp(argv[i], "%s")) {
			char *str = NULL;
			int current, max;
			str = (char*)malloc(DEFAULT_SIZE * sizeof(char));
			if(!str) {
				fprintf(stderr, "Out of mmory...\n");
				if(fp != stdin) {
					fclose(fp);
				}

				exit(ERROR_MEM);
			}

			max = DEFAULT_SIZE;
			current = 0;
			while(append(&str, &current, &max, fp) != '\0');

			printf("%s%s", str, separator);
			free(str);

		} else if(!strcmp(argv[i], "%c")) {
			char c;
			fread(&c, sizeof(char), 1, fp);
			printf("%c%s", c, separator);

		} else if(!strcmp(argv[i], "%b")) {
			char b;
			fread(&b, sizeof(char), 1, fp);

			if(b == 0) {
				printf("false%s", separator);
			} else if(b == 1) {
				printf("true%s", separator);
			}		
		}
	
	}

	if(fp != stdin) {
		fclose(fp);
	}

	printf("\n");
	return 0;
}

