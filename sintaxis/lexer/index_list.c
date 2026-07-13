#include "all.h"

int main(void){
	Node* cabeza = create_node((int[]){5});
	append_node(cabeza, (int[]){4});
	append_node(cabeza, (int[]){3});
	append_node(cabeza, (int[]){2});
	insert_node(cabeza, (int[]){10}, 2);


	Node* node = cabeza;

	while(node != NULL){
		printf("%d\n", *(int*)node->data);
		node = node->next;
	}
	printf("\n\n");
	
	node = index_node(cabeza, 1);
	printf("1: %d\n", *(int*)node->data);
	
	node = first_node(node);
	printf("Primero: %d\n", *(int*)node->data);

	node = last_node(cabeza);
	printf("Ultimo: %d\n", *(int*)node->data);

	printf("Largo: %d\n", list_len(cabeza));

	printf("\n\n");
	Node* deleted = delete_node(cabeza, 3);
	printf("Eliminado: %d\n\n", *(int*)deleted->data);

	node = first_node(node);
	while(node != NULL){
		printf("%d\n", *(int*)node->data);
		node = node->next;
	}

	return 0;
}

Node* create_node(void* data){
	Node* node = malloc(sizeof(Node*));

	node->data = data;
	node->next = NULL;
	node->prev = NULL;

	return node;
}

int error_NULL_node(const Node* node, char* name){
	if (node == NULL){
		printf("ERROR %s, NULL node\n", name);
		return 1;
	}
	else return 0;
}

Node* index_node(Node *head, int index){
	if (error_NULL_node(head, "index_node")) return NULL;

	Node* node_i = head;
	Node* node_ant = NULL;

	for (int i = 0; i < index; i++){
		node_ant = node_i;
		node_i = node_ant->next;
		if(node_i == NULL){
			printf("ERROR: Index out of range\n");
			return NULL;
		}
	} 
	return node_i;
}

Node* first_node(Node* node){
	if (error_NULL_node(node, "firsr_node")) return NULL;

	Node* node_i = node;
	Node* node_prev = node_i->prev;

	while(node_prev != NULL){
		node_i = node_prev;
		node_prev = node_i->prev;
	}
	return node_i;

}

Node* last_node(Node *head){ //no necesariamente tiene que recibir el primer elemento de la lista
	if (error_NULL_node(head, "last_node")) return NULL;

	Node* node_i = head;
	Node* node_next = node_i->next;

	while(node_next != NULL){
		node_i = node_next;
		node_next = node_i->next;
	}
	return node_i;	
} 

Node* append_node(Node* head, void* data){
	if(error_NULL_node(head, "append_node")) return NULL;

	Node* node = create_node(data);

	Node* last = last_node(head);
	
	last->next = node;
	node->prev = last;

	return node;
}

Node* insert_node(Node* head, void* data, int index){
	if(error_NULL_node(head, "insert_node")) return NULL;

	Node* node_i = index_node(head, index);
	if(error_NULL_node(node_i, "insert_node: index out of range")) return NULL;
	Node* node_ant = node_i->prev;
	
	Node* node = create_node(data);

	if(node_ant == NULL){//significa que node_i es el primero
		node->prev = NULL;
		node->next = node_i;

		node_i->prev = node;
	}
	else{
		node_ant->next = node;
		node_i->prev = node;

		node->next = node_i;
		node->prev = node_ant;
	}
	return node;
}

Node* delete_node(Node *head, int index){//Devuelve un puntero al Node eliminado
	if (error_NULL_node(head, "delete_node")) return NULL;
	
	Node* node_i = index_node(head, index);

	if(error_NULL_node(head, "delete_node: index out of range")) return NULL;

	Node* node_next = node_i->next;
	Node* node_prev = node_i->prev;

	if(node_next == NULL){
		if(node_prev != NULL)//Era el ultimo elemento
		     node_prev->next = NULL;
	}
	else{
		if(node_prev == NULL) //era el primer elemento
				      node_next->prev = NULL;
		else{
			node_prev->next = node_next;
			node_next->prev = node_prev;
		}
	}
	//No lo libero, lo libera el usuario.
	return node_i;
}

int list_len(Node *head){
	int i = 0;
	Node* node_i = head;

	while(node_i != NULL){
		i++;
		node_i = node_i->next;
	}
	return i;
}
