typedef struct Node{
	void* data;
	struct Node* next;
	struct Node* prev;
}Node;


int error_NULL_node(const Node* node, char* name);
Node* create_node(void* data);
Node* index_node(Node *head, int index);
Node* first_node(Node* node);
Node* last_node(Node *head); 
Node* append_node(Node* head, void* data);
Node* insert_node(Node* head, void* data, int index);
Node* delete_node(Node *head, int index);
int list_len(Node *head);
