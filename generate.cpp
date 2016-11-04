#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argn, char* argv[]){ //first arg - name file, second arg - len, third - min, fourth - max
if (argn < 4){
    fprintf(stderr, "please add len\n");
    return 0;
}

int len = atoi(argv[2]);
int min = atoi(argv[3]);
int max = atoi(argv[4]);

FILE* file;
file = fopen(argv[1],"w");
fprintf(file, "%d\n",len);

srand(time(NULL));
int chislo;

for(int i = 0; i < len+1; i++){
    for(int j = 0; j < len; j++) {
	fprintf(file, "%d\t",min + rand()%(max-min));
    }
    fprintf(file, "\n");
}

fclose(file);
return 0;

}   


