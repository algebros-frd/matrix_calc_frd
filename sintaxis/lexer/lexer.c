#include "all.h"

int main(void){
	Afd* afd_exit = init_afd(transition_exit, "TOKEN_EXIT");
	Afd* afd_igual = init_afd(transition_igual, "TOKEN_IGUAL");


	Node *n_exit = malloc(sizeof(Node));
	Node *n_igual = malloc(sizeof(Node));

	n_exit->data = afd_exit;
	n_exit->next = n_igual;

	n_igual->data = afd_igual;
	n_igual->next = NULL;

	print_afd(n_exit->data);
	print_afd((n_exit->next)->data);

	return 0;
}


int reader(int max_len, char *source){
	char c;

	for(int i = 0; i < max_len; i++){
		c = getchar();
		source[i] = c;
		if (c == ';')return 0;
	}
	printf("ERROR CADENA MUY LARGA\n");
	return 1;
}

Node* tokenizer(char *fuente, Afd* afds[]){//devuelve un linked list de tokens
	int c_afds = sizeof(afds) / sizeof(Afd*);
}

