#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define USAGE "Usage: %s [-f filename] modif1 value1 modif2 value2 ...\n"
#define ERROR_PARAM -1
#define ERROR_IO -2


int main(int argc, char *argv[]) {

	if(argc < 2) {
		fprintf(
			stderr, 
			"Usage: %s [-f filename] modif1 value1 modif2 value2 ...\n",
			argv[0]
		);

		return ERROR_PARAM;
	}


	FILE *fp = NULL;
	int i;
	char flag = 0;
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
			
			if(!(fp = fopen(argv[i + 1], "wb"))) {
				fprintf(stderr, "Unable to open file: %s", argv[i + 1]);
				return ERROR_IO;
			}
			flag = 1;
		}
	}
	if(!flag) {
		fp = stdout;
	}

	for(i = 1; i < argc; ++ i) {
		if(strcmp(argv[i], "-f") == 0) {
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
			++ i;
			int rez = atoi(argv[i]);
			fwrite(&rez, sizeof(int), 1, fp);
		} else if(!strcmp(argv[i], "%f")) {
			if(i == argc - 1) {
				fprintf(
					stderr, 
					USAGE,
					argv[0]
				);
			}
			++ i;
			float rez = atof(argv[i]);
			fwrite(&rez, sizeof(float), 1, fp);


		} else if(!strcmp(argv[i], "%s")) {
			if(i == argc - 1) {
				fprintf(
					stderr, 
					USAGE,
					argv[0]
				);
			}
			++ i;
			fwrite(argv[i], sizeof(char), strlen(argv[i]) + 1, fp);

		} else if(!strcmp(argv[i], "%c")) {
			if(i == argc - 1) {
				fprintf(
					stderr, 
					USAGE,
					argv[0]
				);
			}
			++ i;
			fwrite(argv[i], sizeof(char), 1, fp);

		} else if(!strcmp(argv[i], "%b")) {
			if(i == argc - 1) {
				fprintf(
					stderr, 
					USAGE,
					argv[0]
				);
			}
			++ i;
			char b;
			if(!strcmp(argv[i], "false")) {
				b = 0;
			} else if(!strcmp(argv[i], "true")) {
				b = 1;
			} else {
				fprintf(
					stderr,
					"Boolean values are true/false."\
					" Assuming false.\n"
				);
			}
			fwrite(&b, sizeof(char), 1, fp);

		} else {
			fwrite(argv[i], sizeof(char), strlen(argv[i]) + 1, fp);
		}
		
	}

	if(fp != stdout) {
		fclose(fp);
	}

	return 0;
}

