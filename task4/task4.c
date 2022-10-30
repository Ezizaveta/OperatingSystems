#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 10

typedef struct Node Node;
typedef struct List List;
struct Node {
	char* string;
	struct Node* next;
};

struct List {
	struct Node *head;
}List_;

List* create_list() {
	List* List_ = (List*)malloc(sizeof(List));
	if (!List_) 
	{
		return NULL;
	}
	List_->head = NULL;
	return List_;
}

Node* new_node() {
	Node *node = (Node*)malloc(sizeof(Node));
	if (!node) 
	{
		return NULL;
	}

	node->next = NULL;
	return node;
}

Node* insert(char* str)
{
	Node* node = new_node();
	if (!node)
	{
		return NULL;
	}	
	if (List_.head == NULL) 
	{
		List_.head = node;
	}
	Node* current = List_.head;
	while ((current->next != NULL) && (current != NULL))
	{
		current = current->next;
	}				
	current->next = node;
	node->next = NULL;
	node->string = strdup(str);
	if (!node->string)
	{
		return NULL;
	}
	return node;
	//node->string = (char*)malloc(sizeof(char)*(strlen(str) + 1));
	//strcpy(node->string, str);
}
void destroy_list(Node *head)
{
	while (head != NULL)
	{
		Node *current = head->next;
		free(head->string);
		free(head);
		head = current;
	}												
}	
void printlist(void) {						
	Node* current = List_.head;									
	int i;										
	while (current != NULL)
	{
		printf("%s", current->string);
		current = current->next;
	}
}
int main()
{
	List* List_ = create_list();
	char str[SIZE];
	char last_str[SIZE];
	int flag = 0;
	while (fgets(str, SIZE, stdin) != NULL)
	{
		if ((*str == '.') && flag)
		{
			break;
		}
		if (str[strlen(str) - 1] == '\n') flag = 1;
		else flag = 0;
		insert(str);
	}
	printlist();
	destroy_list(List_->head);
	return 0;
}
