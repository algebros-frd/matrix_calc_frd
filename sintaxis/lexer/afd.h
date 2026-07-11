typedef struct Afd{
	struct Afd* (*transition)(const struct Afd *, char);
	int q;
	int state;
	char *name;
}Afd;


Afd *init_afd( Afd* (*transition)(const Afd *, char), char* name);
void print_afd(const Afd *afd);
Afd* copy_afd(const Afd* afd);


Afd* transition_letra(const  Afd *afd, char c, char letra);
Afd* transition_word(const  Afd* afd, char c, char *word);

Afd* transition_exit(const Afd *afd, char c);
Afd* transition_punto_coma(const Afd *afd, char c);
Afd* transition_espacio(const Afd *afd, char c);
Afd* transition_mas(const Afd *afd, char c);
Afd* transition_por(const  Afd *afd, char c);
Afd* transition_par_izq(const  Afd *afd, char c);
Afd* transition_par_der(const  Afd *afd, char c);
Afd *transition_igual(const Afd* afd, char c);
Afd* transition_mat_id(const  Afd *afd, char c);
Afd* transition_num(const Afd* afd, char c);
