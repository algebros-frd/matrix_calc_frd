#include <stdio.h>

#define LEN_FUENTE 128
//char **(int fuente_len, char **

int reader(int max_len, char *prueba);

	
int main(int argc, char **argv){
	char prueba[LEN_FUENTE];
	int i = 0;
	int error;
	error = reader(LEN_FUENTE, prueba);

}

int reader(int max_len, char *prueba){
	char c;

	for(int i = 0; i < max_len; i++){
		c = getchar();
		prueba[i] = c;
		if (c == ';')return 0;
	}
	printf("ERROR CADENA MUY LARGA\n");
	return 1;
}
