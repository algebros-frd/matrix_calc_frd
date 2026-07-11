#include "lex.h"

#define NO_ACEPTADO 0
#define ACEPTADO 1
#define TRAMPA 2
#define LEN_FUENTE 128

	
int main(int argc, char **argv){
	int estado = afd_exit(argv[1]);

	printf("%d\n", estado);

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


int afd_exit(char lexema[]){
	int posicion;
	int largo_lex = strlen(lexema);
	int estado_aceptado = 4;
	int estado_trampa = 5;
	char car_actual;
	int estado_actual = 0;


	for (int i = 0; i < largo_lex; i ++){
		car_actual = lexema[i];
		switch (estado_actual){
			case 0: 
				if(car_actual == 'e') {
					estado_actual = 1;
					break;
				}
				else{
					estado_actual = estado_trampa;
					return TRAMPA;
				}
			case 1: 
				if(car_actual == 'x'){
					estado_actual = 2;
					break;
				}
				else{
					estado_actual = estado_trampa;
					return TRAMPA;
				}
			case 2:
				if(car_actual == 'i'){
					estado_actual = 3;
					break;
				}
				else{
					estado_actual = estado_trampa;
					return TRAMPA;
				}
			case 3:
				if(car_actual == 't'){
					estado_actual = 4;
					break;
				}
				else{
					estado_actual = estado_trampa;
					return TRAMPA;
				}
			case 4:
				estado_actual = estado_trampa;
				return TRAMPA;
		}
	}
	if(estado_actual == estado_aceptado) return ACEPTADO;
	else return NO_ACEPTADO;
}


int afd_punto_coma(char lexema[]){
	int largo_lex = strlen(lexema);

	if(largo_lex > 1)return TRAMPA;
	if (lexema[0] == ';') return ACEPTADO;
	else return TRAMPA;
}


int afd_espacio(char lexema[]){
	int largo_lex = strlen(lexema);
	char c;

	for(int i = 0; i < largo_lex; i++){
		c = lexema[i];
		if(c != ' ' || c != '\n' || c != '\t') return TRAMPA; 
	}
	return ACEPTADO;
	
}

int afd_mas(char lexema[]){
	int largo_lex = strlen(lexema);

	if(largo_lex > 1)return TRAMPA;
	if (lexema[0] == '+') return ACEPTADO;
	else return TRAMPA;
}


int afd_por(char lexema[]){
	int largo_lex = strlen(lexema);

	if(largo_lex > 1)return TRAMPA;
	if (lexema[0] == '*') return ACEPTADO;
	else return TRAMPA;
}

int afd_par_izq(char lexema[]){
	int largo_lex = strlen(lexema);

	if(largo_lex > 1)return TRAMPA;
	if (lexema[0] == '(') return ACEPTADO;
	else return TRAMPA;
}

int afd_par_der(char lexema[]){
	int largo_lex = strlen(lexema);

	if(largo_lex > 1)return TRAMPA;
	if (lexema[0] == ')') return ACEPTADO;
	else return TRAMPA;
}


int afd_mat_id(char lexema[]){
	int largo_lex = strlen(lexema);

	if(largo_lex > 1)return TRAMPA;
	if (lexema[0] >= 65 && lexema[0] <= 91) return ACEPTADO;
	else return TRAMPA;
}

int afd_igual(char lexema[]){
	int largo_lex = strlen(lexema);

	if(largo_lex > 1)return TRAMPA;
	if (lexema[0] == '=') return ACEPTADO;
	else return TRAMPA;
}



int afd_inv(char lexema[]){
	int posicion;
	int largo_lex = strlen(lexema);
	int estado_aceptado = 3;
	int estado_trampa = 4;
	char car_actual;
	int estado_actual = 0;


	for (int i = 0; i < largo_lex; i ++){
		car_actual = lexema[i];
		switch (estado_actual){
			case 0: 
				if(car_actual == 'i') {
					estado_actual = 1;
					break;
				}
				else{
					estado_actual = estado_trampa;
					return TRAMPA;
				}
			case 1: 
				if(car_actual == 'n'){
					estado_actual = 2;
					break;
				}
				else{
					estado_actual = estado_trampa;
					return TRAMPA;
				}
			case 2:
				if(car_actual == 'v'){
					estado_actual = 3;
					break;
				}
				else{
					estado_actual = estado_trampa;
					return TRAMPA;
				}
			case 3:
				estado_actual = estado_trampa;
				return TRAMPA;
		}
	}
	if(estado_actual == estado_aceptado) return ACEPTADO;
	else return NO_ACEPTADO;
}



int afd_det(char lexema[]){
	int posicion;
	int largo_lex = strlen(lexema);
	int estado_aceptado = 3;
	int estado_trampa = 4;
	char car_actual;
	int estado_actual = 0;


	for (int i = 0; i < largo_lex; i ++){
		car_actual = lexema[i];
		switch (estado_actual){
			case 0: 
				if(car_actual == 'd') {
					estado_actual = 1;
					break;
				}
				else{
					estado_actual = estado_trampa;
					return TRAMPA;
				}
			case 1: 
				if(car_actual == 'e'){
					estado_actual = 2;
					break;
				}
				else{
					estado_actual = estado_trampa;
					return TRAMPA;
				}
			case 2:
				if(car_actual == 't'){
					estado_actual = 3;
					break;
				}
				else{
					estado_actual = estado_trampa;
					return TRAMPA;
				}
			case 3:
				estado_actual = estado_trampa;
				return TRAMPA;
		}
	}
	if(estado_actual == estado_aceptado) return ACEPTADO;
	else return NO_ACEPTADO;
}


int afd_num(char lexema[]){
	int posicion;
	int largo_lex = strlen(lexema);
	int estado_aceptado[] = {1, 3};
	int estado_trampa = 5;
	char car_actual;
	int estado_actual = 0;

	for(int i = 0; i < largo_lex; i++){
		car_actual = lexema[i];
		if(car_actual < 48 && car_actual > 57 && car_actual != '-' && car_actual != '.') return TRAMPA;
		switch(estado_actual){
			case 0: if(car_actual == '-'){
					estado_actual = 4;
					break;
				}
				else if(car_actual >= 48 && car_actual <= 57){
					estado_actual = 1;
					break;
				}
				else return TRAMPA;
			case 1: if(car_actual == '.'){
					estado_actual = 2;
					break;
				}
				else if(car_actual == '='){
					return TRAMPA;
				}
				else break;
			case 2: if (car_actual == '=' || car_actual == '.') return TRAMPA;
				else {
					estado_actual = 3;
					break;
				}
			case 3: if (car_actual == '=' || car_actual == '.') return TRAMPA;
				else {
					estado_actual = 3;
					break;
				}
			case 4: if (car_actual == '=' || car_actual == '.') return TRAMPA;
				else {
					estado_actual = 1;
					break;
				}
		}
	}		
	if(estado_actual == estado_aceptado[0] || estado_actual == estado_aceptado[1]) return ACEPTADO;
	else return NO_ACEPTADO;
}

