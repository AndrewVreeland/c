/* Tanvir Ahmed
CS1
This code implements doubly linked list insertions and deletion*/

#include <stdio.h>
#include <stdlib.h>

// defining the node structure
typedef struct node
{
	int data;
	struct node *prev, *next;
} node;

node *createNode(int item)
{
	node *newNode = malloc(sizeof(node));
	newNode->data = item;
	newNode->prev = NULL;
	newNode->next = NULL;
}

node *insert_end(node *head, int item)
{
	if (head == NULL)
	{
		head = createNode(item);
		return head;
	}
	else
	{
		node *current = head;
		while (current->next)
		{
			current = current->next;
		}
		node *newNode = createNode(item);
		current->next = newNode;
		newNode->prev = current;
		return head;
	}
}

node *insert_front(node *head, int item)
{
	node *newNode = createNode(item);
	newNode->next = head;
	if (head)
		head->prev = newNode;
	else
	{
		head = newNode;
		return head;
	}
}

/*takes root of a linked list and insert item to the end of the list.
Returns the root of the list after insertion
*/

/*takes root of a linked list and delete the first occurance of the item from the the list.
Returns the root of the list after deletion
*/
node *DelListDoubly(node *root, int item)
{

	if (root == NULL)
		return root;
	else if (root->data == item)
	{
		node *tempNode = root;
		root = root->next;
		free(tempNode);

		if (root)
			root->prev = NULL;

		return root;
	}
	else
	{
		node *current = root;

		while (current->next && current->next->data != item)
		{
			current = current->next;
		}

		if (!current->next)
		{
			return root;
		}
		node *tempNode = current -> next;
		current ->next = current -> next -> next;

		free(tempNode);

		current -> next ->prev = current;

		return root;
	}
}
node *insertSortedNode(node *root, int data)
{
	if (root == NULL || data < root->data)
	{
		node *newNode = createNode(data);
		newNode->next = root;
		if (root)
			root->prev = newNode;
		return newNode;
	}
	node *current = root;
	while (current->next && current->next->data < data)
	{
		current = current->next;
	}

	node *newNode = createNode(data);

	if (current->next)
	{

		newNode->next = current->next;
		newNode->prev = current;
		current->next = newNode;
	}
	else
	{
		current->next = newNode;
		newNode->prev = current;
	}

	return root;
}

void display(node *t)
{
	printf("\nPrinting your link list.......");

	while (t != NULL)
	{
		printf("%d ", t->data);
		t = t->next;
	}
}

int main()
{
	node *root = NULL;
	node *t, del;
	int ch, ele, v;
	while (1)
	{
		printf("\nMenu: 1. insert at front, 2. insert at end, 3. Delete 4. exit: ");
		scanf("%d", &ch);
		if (ch == 4)
		{
			printf("\nGOOD BYE>>>>\n");
			break;
		}
		if (ch == 1)
		{
			printf("\nEnter information(an integer): ");
			scanf("%d", &ele);
			root = insert_front(root, ele);

			display(root);
		}
		if (ch == 2)
		{
			printf("\nEnter information(an integer): ");
			scanf("%d", &ele);
			root = insert_end(root, ele);
			display(root);
		}
		if (ch == 3)
		{
			printf("\nEnter info which u want to DELETE: ");
			scanf("%d", &ele);
			root = DelListDoubly(root, ele);
			display(root);
		}
	}
	return 0;
}
