
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
} node;

node *create_node(int item)
{
	node *temp = malloc(sizeof(node));
	temp->data = item;
	temp->next = NULL;
	return temp;
}

// this function takes an item and insert it in the linked list pointed by root.
node *insert_front(node *head, int item)
{
	node *temp = create_node(item);

	if (head == NULL)
	{
		head = temp;
		return head;
	}
	else
	{
		temp->next = head;
		return temp;
	}
}

node *insert_sorted(node *root, int item) {
    node *temp = create_node(item);

    // Case 1: Insert at the very front
    if (root == NULL || root->data > item) {
        temp->next = root;
        return temp; // Return the new head
    }

    // Case 2: Walk the list
    node *current = root;
    while (current->next != NULL && current->next->data < item) {
        current = current->next;
    }

    temp->next = current->next;
    current->next = temp;
    return root; // Return the head of the list
}

// this function takes an item and insert it in the end of the linked list
node *insert_end(node *root, int item)
{
	if (root == NULL)
	{
		node *newNode = create_node(item);
		return newNode;
	}
	root->next = insert_end(root->next, item);
	return root;
}

/*this function deletes the first occurrence of a given item from linked list.
it returns the updated/original root
*/
node *DelList(node *head, int item) {
    if (head == NULL) return head;

    // Handle head
    if (head->data == item) {
        node *temp = head->next;
        free(head);
        return temp;
    }

    node *current = head;
    // Look ahead at the next node's data
    while (current->next != NULL && current->next->data != item) {
        current = current->next;
    }

    if (current->next != NULL) {
        node *temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    
    return head; // Always return head
}

void display(node *t)
{
	printf("\nPrinting your linked list.......");

	while (t != NULL)
	{
		printf("%d ", t->data);
		t = t->next;
	}

	printf("\n");
}

int main()
{
    node *root = NULL; // Initialized to NULL
    int ch, ele, del;

    while (1)
    {
        printf("\nMenu: 1. Front Insert, 2. End Insert, 3. Delete, 5. Sorted Insert, 4. Exit: ");
        if (scanf("%d", &ch) != 1) break; // Safety check for non-integer input

        if (ch == 4)
        {
            printf("\nGOOD BYE>>>>\n");
            break;
        }

        if (ch == 1)
        {
            printf("\nEnter data: ");
            scanf("%d", &ele);
            // UPDATE: Capture the new head returned by the function
            root = insert_front(root, ele);
            display(root);
        }
        else if (ch == 2)
        {
            printf("\nEnter data: ");
            scanf("%d", &ele);
            // UPDATE: Capture the head (especially important if list was NULL)
            root = insert_end(root, ele);
            display(root);
        }
        else if (ch == 3)
        {
            printf("\nEnter info to DELETE: ");
            scanf("%d", &del);
            // UPDATE: Capture head in case the first node was deleted
            root = DelList(root, del);
            display(root);
        }
        else if (ch == 5)
        {
            printf("\nEnter data: ");
            scanf("%d", &ele);
            // UPDATE: Capture head
            root = insert_sorted(root, ele);
            display(root);
        }
    }
    return 0;
}
