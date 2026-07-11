#include "all.h"
	
/*int main(int argc, char **argv){
	Afd *afd_exit;
	Afd* afd_aux;
	afd_exit = init_afd(transition_num, "TOKEN_NUM");
	char c;

	while(1){
		printf("Ingrese caracter: ");
		c = getchar();
		getchar();

		afd_aux = afd_exit->transition(afd_exit, c);
		free(afd_exit);
		afd_exit = copy_afd(afd_aux);
		free(afd_aux);

		print_afd(afd_exit);
		printf("\n\n");
	}
	return 0;
}
*/

Afd *init_afd( Afd* (*transition)(const Afd *, char), char* name){
	Afd *afd;
	afd = calloc(1, sizeof(Afd));

	afd->q = 0;
	afd->state = NO_ACEPTADO;
	afd->transition = transition;
	afd->name = name;

	return afd;
}

Afd* copy_afd(const Afd *afd){
	Afd* afd_copy = init_afd(afd->transition, afd->name);
	afd_copy->q = afd->q;
	afd_copy->state = afd->state;

	return afd_copy;
}


void print_afd(const Afd *afd){
	printf("%s\n", afd->name);
	printf("Estado ");
	switch (afd->state){
		case TRAMPA: printf("trampa\n");
			     break;
		case NO_ACEPTADO: printf("no acepado\n");
				  break;
		case ACEPTADO: printf("aceptado\n");
			       break;
	}
	printf("Estado actual %d\n", afd->q);
	
	return;
}


//Funciones de transision
Afd* transition_letter(const  Afd *afd, char c, char letter){
	int q = afd->q;
	int q_acc = 1;
	int q_err = 2;

	Afd* afd_letter = copy_afd(afd);
	
	if (c != letter || q > 0){
		afd_letter->q = q_err;
		afd_letter->state = TRAMPA;
		return afd_letter;
	}

	afd_letter->q = q_acc;
	afd_letter->state = ACEPTADO;
	return afd_letter;
}

Afd* transition_word(const Afd* afd, char c, char *word){
	int word_len = strlen(word);
	int q_acc = strlen(word);
	int q_err = strlen(word) + 1;
	int q = afd->q;

	Afd* afd_word = copy_afd(afd);
	if(q >= q_acc){ //quiero decir que ya estaba en aceptado o trampa
		afd_word->q = q_err;
		afd_word->state = TRAMPA;
		return afd_word;
	}

	if(word[q] == c){
		afd_word->q +=1;
		afd_word->state = (afd_word->q == q_acc);
		return afd_word;
	}
	else{
		afd_word->q = q_err;
		afd_word->state = TRAMPA;
		return afd_word;
	}
}


Afd* transition_punto_coma(const  Afd *afd, char c){
	return transition_letter(afd, c, ';');
}


Afd* transition_espacio(const  Afd *afd, char c){
	int q = afd->q;
	int q_acc = 1;
	int q_err = 2;
	
	Afd* afd_espacio = copy_afd(afd);

	if (q > 1){
		afd_espacio->q = q_err;
		afd_espacio->state = TRAMPA;
		return afd_espacio;
	}

	if (c == ' ' || c == '\n' || c == '\t'){
		afd_espacio->q = q_acc;
		afd_espacio->state = ACEPTADO;
		return afd_espacio;
	}

	afd_espacio->q = q_err;
	afd_espacio->state = TRAMPA;
	return afd_espacio;
}

Afd* transition_mas(const  Afd *afd, char c){
	return transition_letter(afd, c, '+');
}

Afd* transition_por(const  Afd *afd, char c){
	return transition_letter(afd, c, '*');
}

Afd* transition_par_izq(const  Afd *afd, char c){
	return transition_letter(afd, c, '(');
}

Afd* transition_par_der(const  Afd *afd, char c){
	return transition_letter(afd, c, ')');
}

Afd *transition_igual(const Afd* afd, char c){
	return transition_letter(afd, c, '=');
}

Afd* transition_exit(const Afd *afd, char c){
	return transition_word(afd, c, "exit");
}

Afd* transition_mat_id(const  Afd *afd, char c){
	int q = afd->q;
	int q_acc = 1;
	int q_err = 2;

	Afd* afd_mat_id = copy_afd(afd);
	
	if ( (c > 64 && c < 91) || q > 0){
		afd_mat_id->q = q_err;
		afd_mat_id->state = TRAMPA;
		return afd_mat_id;
	}

	afd_mat_id->q = q_acc;
	afd_mat_id->state = ACEPTADO;
	return afd_mat_id;
}

Afd* transition_num(const Afd* afd, char c){
	int q = afd->q;
	int q_err = 5;
	//tiene dos estados aceptados, el 1 y el 3, no vale la pena generar un array
	
	Afd* afd_num = copy_afd(afd);

	if(c != '-' && c != '.' && (c<48 || c > 57)){
		afd_num->q = q_err;
		afd_num->state = TRAMPA;
		return afd_num;
	}

	switch(q){
		case 0: if(c == '-'){
				afd_num->q = 4;
				afd_num->state = NO_ACEPTADO;
				return afd_num;
			}
			else if(c == '.'){
				afd_num->q = q_err;
				afd_num->state = TRAMPA;
				return afd_num;
			}else{
				afd_num->q = 1;
				afd_num->state = ACEPTADO;
				return afd_num;
			}
		case 1: if(c == '-'){
				afd_num->q = q_err;
				afd_num->state = TRAMPA;
				return afd_num;
			}
			else if(c=='.'){
				afd_num->q = 2;
				afd_num->state = NO_ACEPTADO;
				return afd_num;
			}else{
				afd_num->q = 1;
				afd_num->state = ACEPTADO;
				return afd_num;
			}
		case 2: if(c == '.' || c=='-'){
				afd_num->q = q_err;
				afd_num->state = TRAMPA;
				return afd_num;
			}
			else{
				afd_num->q = 3;
				afd_num->state = ACEPTADO;
				return afd_num;
			}
		case 3: if(c == '.' || c=='-'){
				afd_num->q = q_err;
				afd_num->state = TRAMPA;
				return afd_num;
			}
			else{
				afd_num->q = 3;
				afd_num->state = ACEPTADO;
				return afd_num;
			}
		case 4: if(c == '.' || c=='-'){
				afd_num->q = q_err;
				afd_num->state = TRAMPA;
				return afd_num;
			}
			else{
				afd_num->q = 1;
				afd_num->state = ACEPTADO;
				return afd_num;
			}
		case 5: afd_num->q = q_err;
			afd_num->state = TRAMPA;
			return afd_num;
	}
}
