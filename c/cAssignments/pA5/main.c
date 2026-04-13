#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 25  // max characters allowed in a name
#define NUM_TRAITS 5 // total number of traits each cat has

typedef struct Cat
{
    char *name;             // pointer to dynamically allocated name string
    char *breed;            // pointer to dynamically allocated breed string
    int charm;              // charm score for this cat
    int traits[NUM_TRAITS]; // array of trait flags matching trait names array
} Cat;

typedef struct BST_Node
{
    Cat *cat;               // pointer to the cat stored in this node
    struct BST_Node *left;  // pointer to the left child
    struct BST_Node *right; // pointer to the right child
    int subtree_size;       // total number of nodes in this subtree including itself
} BST_Node;

// array of trait name strings indexed by trait position
const char *TRAIT_NAMES[NUM_TRAITS] = {"friendly", "grumpy", "playful", "lazy", "curious"};

// forward declarations
char **filterByTrait(BST_Node *root, int traitIndex, int traitValue, int *resultSize);
Cat *createCat(void);
BST_Node *instantiateTree(void);
int countTraits(Cat *cat);
void updateSize(BST_Node *node);
BST_Node *query1(BST_Node *root, Cat *newCat, int depth, int *replaced);
BST_Node *query2(BST_Node *root, const char *name);
void query3(BST_Node *root, int k, int treeSize);
void query4(BST_Node *root, int traitIndex, int traitValue);
BST_Node *query5(BST_Node *root, int traitIndex, int traitValue, int *removedCount);
void query6(BST_Node *root);
BST_Node *minVal(BST_Node *node);
void freeNode(BST_Node *node);
BST_Node *findNode(BST_Node *cn, const char *name);
BST_Node *parent(BST_Node *root, BST_Node *node);
void freeTree(BST_Node *root);

// returns null to start the tree empty
BST_Node *instantiateTree(void)
{
    return NULL;
}

// reads one and returns a pointer to it
Cat *createCat(void)
{
    Cat *cat = malloc(sizeof(Cat));

    // read and copy the name
    char tempName[MAX_NAME + 1];
    scanf("%s", tempName);
    int strLen = strlen(tempName) + 1;
    cat->name = malloc(strLen);
    strcpy(cat->name, tempName);

    // read and copy the breed
    char tempBreed[MAX_NAME + 1];
    scanf("%s", tempBreed);
    strLen = strlen(tempBreed) + 1;
    cat->breed = malloc(strLen);
    strcpy(cat->breed, tempBreed);

    // read the charm score
    int charm;
    scanf("%d", &charm);
    cat->charm = charm;

    // read each trait flag and store it in the traits array
    for (int i = 0; i < NUM_TRAITS; i++)
    {
        int traitValue;
        scanf("%d", &traitValue);
        cat->traits[i] = traitValue;
    }

    return cat;
}

// recalculates the subtree size for a given node
void updateSize(BST_Node *node)
{
    if (node == NULL)
        return;

    // get left child size or zero if no left child exists
    int leftS = 0;
    if (node->left != NULL)
        leftS = node->left->subtree_size;

    // get right child size or zero if no right child exists
    int rightS = 0;
    if (node->right != NULL)
        rightS = node->right->subtree_size;

    // size is this node plus both subtrees
    node->subtree_size = 1 + leftS + rightS;
}

// counts how many traits are set to 1 for a given cat
int countTraits(Cat *cat)
{
    int count = 0;
    for (int i = 0; i < NUM_TRAITS; i++)
    {
        if (cat->traits[i] == 1)
            count++;
    }
    return count;
}

// inserts a new cat into the bst keyed by name, replaces data if new cat has more traits
BST_Node *query1(BST_Node *root, Cat *newCat, int depth, int *replaced)
{
    // empty spot found so create and return a new node here
    if (root == NULL)
    {
        printf("Insert: %d\n", depth);
        BST_Node *newNode = malloc(sizeof(BST_Node));
        newNode->cat = newCat;
        newNode->left = newNode->right = NULL;
        newNode->subtree_size = 1;

        // tell the parent call that a real insertion happened
        *replaced = 0;
        return newNode;
    }

    int result = strcmp(newCat->name, root->cat->name);

    if (result == 0)
    {
        // name already exists so no structural change to the tree
        *replaced = 1;
        if (countTraits(newCat) > countTraits(root->cat))
        {
            // free old cat data and swap in the new cat
            free(root->cat->name);
            free(root->cat->breed);
            free(root->cat);
            root->cat = newCat;
            printf("Replaced\n");
        }
        else
        {
            // new cat has fewer or equal traits so discard it
            free(newCat->name);
            free(newCat->breed);
            free(newCat);
        }
    }
    else if (result < 0)
    {
        // new cat name comes before current so go left
        root->left = query1(root->left, newCat, depth + 1, replaced);
    }
    else
    {
        // new cat name comes after current so go right
        root->right = query1(root->right, newCat, depth + 1, replaced);
    }

    // gather left and right sizes to recalculate this nodes subtree size
    int leftS = 0;
    int rightS = 0;

    if (root->left != NULL)
        leftS = root->left->subtree_size;

    if (root->right != NULL)
        rightS = root->right->subtree_size;

    // update size as this node plus both subtrees
    root->subtree_size = 1 + leftS + rightS;

    return root;
}

// searches the tree for a node matching the given name and returns it
BST_Node *findNode(BST_Node *cn, const char *name)
{
    if (cn != NULL)
    {
        if (strcmp(cn->cat->name, name) == 0)
            return cn;
        else if (strcmp(name, cn->cat->name) > 0)
            return findNode(cn->right, name);
        else
            return findNode(cn->left, name);
    }
    else
        return NULL;
}

// returns the parent of the given node by searching from root
BST_Node *parent(BST_Node *root, BST_Node *node)
{
    // root has no parent
    if (root == NULL || root == node)
        return NULL;

    // check if either child is the target node
    if (root->left == node || root->right == node)
        return root;

    // search the correct subtree based on name comparison
    if (strcmp(node->cat->name, root->cat->name) < 0)
        return parent(root->left, node);
    else
        return parent(root->right, node);
}

// finds and returns the minimum node in a subtree
BST_Node *minVal(BST_Node *node)
{
    if (node->left == NULL)
        return node;
    return minVal(node->left);
}

// frees a node and its cat data completely
void freeNode(BST_Node *node)
{
    free(node->cat->name);
    free(node->cat->breed);
    free(node->cat);
    free(node);
}

// helper returns 1 if the node has no children
int isLeaf(BST_Node *node)
{
    if (node->left == NULL && node->right == NULL)
        return 1;
    return 0;
}

// helper returns 1 if the node has only a left child
int hasOnlyLeftChild(BST_Node *node)
{
    if (node->left != NULL && node->right == NULL)
        return 1;
    return 0;
}

// helper returns 1 if the node has only a right child
int hasOnlyRightChild(BST_Node *node)
{
    if (node->left == NULL && node->right != NULL)
        return 1;
    return 0;
}

// removes a cat by name using the iterative parent pointer approach from lecture
BST_Node *query2(BST_Node *root, const char *name)
{
    // tree is empty so nothing to delete
    if (root == NULL)
        return NULL;
 
    // get a pointer to the node to delete
    BST_Node *delnode = findNode(root, name);
 
    // name was not found in the tree
    if (delnode == NULL)
        return root;
 
    // get the parent of the node to delete
    BST_Node *par = parent(root, delnode);
 
    // case 1 - delnode is a leaf with no children
    if (isLeaf(delnode))
    {
        // deleting the root node of the tree
        if (par == NULL)
        {
            freeNode(root);
            return NULL;
        }
 
        // deletes the node if it is a left child
        if (strcmp(name, par->cat->name) < 0)
        {
            freeNode(par->left);
            par->left = NULL;
        }
        else
        {
            // deletes the node if it is a right child
            freeNode(par->right);
            par->right = NULL;
        }
    }
 
    // case 2.1 - delnode has only a left child
    else if (hasOnlyLeftChild(delnode))
    {
        // deleting the root node of the tree
        if (par == NULL)
        {
            BST_Node *save_node = delnode->left;
            freeNode(delnode);
            return save_node;
        }
 
        // deletes the node if it is a left child
        if (strcmp(name, par->cat->name) < 0)
        {
            BST_Node *save_node = par->left;
            par->left = par->left->left;
            freeNode(save_node);
        }
        else
        {
            // deletes the node if it is a right child
            BST_Node *save_node = par->right;
            par->right = par->right->left;
            freeNode(save_node);
        }
    }
 
    // case 2.2 - delnode has only a right child
    else if (hasOnlyRightChild(delnode))
    {
        // deleting the root node of the tree
        if (par == NULL)
        {
            BST_Node *save_node = delnode->right;
            freeNode(delnode);
            return save_node;
        }
 
        // deletes the node if it is a left child
        if (strcmp(name, par->cat->name) < 0)
        {
            BST_Node *save_node = par->left;
            par->left = par->left->right;
            freeNode(save_node);
        }
        else
        {
            // deletes the node if it is a right child
            BST_Node *save_node = par->right;
            par->right = par->right->right;
            freeNode(save_node);
        }
    }
 
    // case 3 - delnode has two children so replace with in order successor
    else
    {
        // find the minimum node in the right subtree
        BST_Node *new_del_node = minVal(delnode->right);
 
        // save all successor cat data before the recursive delete removes it
        char save_name[MAX_NAME + 1];
        char save_breed[MAX_NAME + 1];
        int save_charm = new_del_node->cat->charm;
        int save_traits[NUM_TRAITS];
 
        strcpy(save_name, new_del_node->cat->name);
        strcpy(save_breed, new_del_node->cat->breed);
        for (int i = 0; i < NUM_TRAITS; i++)
            save_traits[i] = new_del_node->cat->traits[i];
 
        // recursively delete the successor node from the tree
        root = query2(root, save_name);
 
        // replace all of delnode's cat data with the successor's saved data
        free(delnode->cat->name);
        free(delnode->cat->breed);
        delnode->cat->name = malloc(strlen(save_name) + 1);
        strcpy(delnode->cat->name, save_name);
        delnode->cat->breed = malloc(strlen(save_breed) + 1);
        strcpy(delnode->cat->breed, save_breed);
        delnode->cat->charm = save_charm;
        for (int i = 0; i < NUM_TRAITS; i++)
            delnode->cat->traits[i] = save_traits[i];
 
        // sizes are updated through the recursive query2 call
        return root;
    }
 
    // walk up from par to root updating each ancestor's subtree size
    BST_Node *ancestor = par;
    while (ancestor != NULL)
    {
        updateSize(ancestor);
        ancestor = parent(root, ancestor);
    }
 
    return root;
}
    // finds the kth smallest node using subtree sizes to navigate without full traversal
    BST_Node *kthSmallest(BST_Node * root, int k)
    {
        if (root == NULL)
            return NULL;

        // get the number of nodes in the left subtree
        int leftSize = 0;
        if (root->left != NULL)
            leftSize = root->left->subtree_size;

        if (k == leftSize + 1)
        {
            // this node is exactly the kth smallest
            return root;
        }
        else if (k <= leftSize)
        {
            // kth smallest is somewhere in the left subtree
            return kthSmallest(root->left, k);
        }
        else
        {
            // kth smallest is in the right subtree so adjust k accordingly
            return kthSmallest(root->right, k - leftSize - 1);
        }
    }

    // prints the kth smallest cat by name or a not found message if k is out of range
    void query3(BST_Node * root, int k, int treeSize)
    {
        if (k > treeSize || root == NULL)
        {
            printf("NO SMALLEST ELEMENT FOUND\n");
            return;
        }

        BST_Node *result = kthSmallest(root, k);
        if (result == NULL)
            printf("NO SMALLEST ELEMENT FOUND\n");
        else
            printf("%s %s %d\n", result->cat->name, result->cat->breed, result->cat->charm);
    }

    // traverses the tree in order and copies matching cat names into the result array
    void filterHelper(BST_Node * root, int traitIndex, int traitValue, char **arr, int *idx)
    {
        if (root == NULL)
            return;

        // visit left subtree first to maintain alphabetical order
        filterHelper(root->left, traitIndex, traitValue, arr, idx);

        // copy the name if this cat matches the trait condition
        if (root->cat->traits[traitIndex] == traitValue)
        {
            int len = strlen(root->cat->name) + 1;
            arr[*idx] = malloc(len);
            strcpy(arr[*idx], root->cat->name);
            (*idx)++;
        }
        // visits right sub tree
        filterHelper(root->right, traitIndex, traitValue, arr, idx);
    }

    // builds and returns an array of cat names matching the given trait condition
    char **filterByTrait(BST_Node * root, int traitIndex, int traitValue, int *resultSize)
    {
        // allocate worst case size based on total number of nodes
        int treeSize = 0;
        if (root != NULL)
            treeSize = root->subtree_size;

        char **arr = malloc(treeSize * sizeof(char *));

        int idx = 0;
        filterHelper(root, traitIndex, traitValue, arr, &idx);
        *resultSize = idx;

        // no matches so free the array and return null
        if (idx == 0)
        {
            free(arr);
            return NULL;
        }

        // shrink the array down to only the space actually used
        arr = realloc(arr, idx * sizeof(char *));
        return arr;
    }

    // prints all cat names matching a trait condition in alphabetical order
    void query4(BST_Node * root, int traitIndex, int traitValue)
    {
        int resultSize = 0;
        char **names = filterByTrait(root, traitIndex, traitValue, &resultSize);

        if (resultSize == 0 || names == NULL)
        {
            printf("NONE FOUND\n");
            return;
        }

        // in order traversal already produces alphabetical order so no sort needed
        printf("%s:", TRAIT_NAMES[traitIndex]);
        for (int i = 0; i < resultSize; i++)
        {
            printf(" %s", names[i]);
            free(names[i]);
        }
        printf("\n");
        free(names);
    }

    // traverses the tree in order and copies matching cat names into the array
    void collectNames(BST_Node * root, int traitIndex, int traitValue, char **arr, int *idx)
    {
        if (root == NULL)
            return;

        collectNames(root->left, traitIndex, traitValue, arr, idx);

        // save the name if this cat matches the trait condition
        if (root->cat->traits[traitIndex] == traitValue)
        {
            int len = strlen(root->cat->name) + 1;
            arr[*idx] = malloc(len);
            strcpy(arr[*idx], root->cat->name);
            (*idx)++;
        }

        collectNames(root->right, traitIndex, traitValue, arr, idx);
    }

    // removes all cats matching a trait condition and returns the number deleted
    BST_Node *query5(BST_Node * root, int traitIndex, int traitValue, int *removedCount)
    {
        if (root == NULL)
        {
            *removedCount = 0;
            return NULL;
        }

        // allocate enough space to hold every name in the tree
        int treeSize = root->subtree_size;
        char **toDelete = malloc(treeSize * sizeof(char *));
        int count = 0;

        // phase 1 - collect the names of all cats that match the condition
        collectNames(root, traitIndex, traitValue, toDelete, &count);

        // phase 2 - delete each collected name from the tree one by one
        for (int i = 0; i < count; i++)
        {
            root = query2(root, toDelete[i]);
            free(toDelete[i]);
        }
        free(toDelete);

        *removedCount = count;
        return root;
    }

    // prints each node in alphabetical order with name charm and subtree size
    void inorderPrint(BST_Node * root)
    {
        if (root == NULL)
            return;

        inorderPrint(root->left);
        printf("%s %d %d\n", root->cat->name, root->cat->charm, root->subtree_size);
        inorderPrint(root->right);
    }

    // prints the whole tree in order or empty if the tree has no nodes
    void query6(BST_Node * root)
    {
        if (root == NULL)
        {
            printf("EMPTY\n");
            return;
        }
        inorderPrint(root);
    }

    // frees all nodes and cat data in the tree using post order traversal
    void freeTree(BST_Node * root)
    {
        if (root == NULL)
            return;

        freeTree(root->left);
        freeTree(root->right);
        freeNode(root);
    }

    int main(void)
    {
        int numOfQueries;
        scanf("%d", &numOfQueries);

        // start with an empty tree
        BST_Node *root = instantiateTree();

        for (int i = 0; i < numOfQueries; i++)
        {
            int q;
            scanf("%d", &q);

            if (q == 1)
            {
                // read a new cat and insert it into the tree
                Cat *newCat = createCat();
                int replaced = 0;
                root = query1(root, newCat, 0, &replaced);
            }
            else if (q == 2)
            {
                // read a name and delete that cat from the tree
                char name[MAX_NAME + 1];
                scanf("%s", name);
                root = query2(root, name);
                printf("Deletion Complete\n");
            }
            else if (q == 3)
            {
                // read k and find the kth smallest cat in the tree
                int k;
                scanf("%d", &k);
                int treeSize = 0;
                if (root != NULL)
                    treeSize = root->subtree_size;
                query3(root, k, treeSize);
            }
            else if (q == 4)
            {
                // read a trait condition and print all matching cat names
                int traitIndex, traitValue;
                scanf("%d %d", &traitIndex, &traitValue);
                query4(root, traitIndex, traitValue);
            }
            else if (q == 5)
            {
                // read a trait condition and remove all cats that match it
                int traitIndex, traitValue;
                scanf("%d %d", &traitIndex, &traitValue);
                int removedCount = 0;
                root = query5(root, traitIndex, traitValue, &removedCount);
                if (removedCount == 0)
                    printf("NONE REMOVED\n");
                else
                    printf("%d\n", removedCount);
            }
            else if (q == 6)
            {
                // print all cats in alphabetical order with their sizes
                query6(root);
            }
        }

        freeTree(root);
        return 0;
    }