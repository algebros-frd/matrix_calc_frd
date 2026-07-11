typedef struct Node{
	void* data;
	struct Node* next;
}Node;

typedef struct Token{
	char* nombre;
	char* lexema;
}

int reader(int max_len, char *prueba);


