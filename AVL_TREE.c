#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



struct node* rightRotate(struct node* root);
struct node* leftRotate(struct node* root);
int height(struct node* root);
struct node* findMax(struct node* root);
struct node* findMin(struct node* root);

typedef enum { FALSE, TRUE } bool;

struct node
{
    int data;
    int balance;
    struct node* left;
    struct node* right;
};

struct node* search(struct node* ptr, int data)
{
    if (ptr != NULL)
        if (data < ptr->data)
            ptr = search(ptr->left, data);
        else if (data > ptr->data)
            ptr = search(ptr->right, data);
    return (ptr);
}

struct node* insert(int data, struct node* tree, bool* ht_inc)
{
    // ht_inc is a tricky variable. It is set to TRUE after a new node is inserted
    // as a leaf, which means that a re-balancing might be needed at a hihger
    // level of a tree, where the critical node resides. When re-balancing is  
    // done or will not be needed at a hihger level, ht_inc is set to FALSE.
    struct node* aptr, * bptr;
    if (tree == NULL)
    {
        tree = (struct node*)malloc(sizeof(struct node));
        tree->data = data;
        tree->left = NULL;
        tree->right = NULL;
        tree->balance = 0;
        *ht_inc = TRUE; // a new node is a added
        return (tree);
    }
    // A new node is inserted as a leaf.
    // First find where to add it by following the BST order
    // Then check the balance factor
    // Finally perform a rebalancing rotation
    if (data < tree->data)
    {
        // Insert in the left sub-tree
        tree->left = insert(data, tree->left, ht_inc);
        if (*ht_inc == TRUE) // a re-balancing might be needed
        {
            // Check the balance factor after the insertion
            switch (tree->balance)
            {
            case -1: /* Right heavy */
                // the node was right heavy and after insertion has become balanced.
                tree->balance = 0;
                *ht_inc = FALSE; // re-balancing will not be needed at a hihger level
                break;
            case 0: /* Balanced */
                // the node was balanced and after insertion has become left heavy.
                tree->balance = 1;
                break;
            case 1: /* Left heavy */
                // the node was left heavy and after insertion has become an unbalanced sub-tree.
                // Rebalancing rotation is needed - determine the type of rotation
                // Check the left sub-tree
                aptr = tree->left; // "tree" is A and "aptr" is B (see slides 46 and 48)
                if (aptr->balance == 1)
                {
                    // LL rotation: the new node is inserted in the left sub-tree of
                    // the left sub-tree of the critical node
                    printf("Left to Left Rotation\n");
                    tree->left = aptr->right; // T2 is made left sub-tree of A (see slide 46)
                    aptr->right = tree;             // A is made right sub-tree of B (see slide 46)
                    tree->balance = 0;
                    aptr->balance = 0;
                    tree = aptr; // B is moved up to the A-place (see slide 46)
                }
                else
                {
                    // LR rotation: the new node is inserted in the right sub-tree of
                    // the left sub-tree of the critical node
                    printf("Left to Right rotation\n");
                    bptr = aptr->right;             // "bptr" is C (see slide 48)
                    aptr->right = bptr->left; // T2 is made right sub-tree of B (see slide 48)
                    bptr->left = aptr;              // B is made left sub-tree of C (see slide 48)
                    tree->left = bptr->right;  // T3 is made left sub-tree of A (see slide 48)
                    bptr->right = tree;              // A is made right sub-tree of C (see slide 48)
                    if (bptr->balance == 1)
                        tree->balance = -1;
                    else
                        tree->balance = 0;
                    if (bptr->balance == -1)
                        aptr->balance = 1;
                    else
                        aptr->balance = 0;
                    bptr->balance = 0;
                    tree = bptr; // C moved up to the A-place (see slide 48)
                }
                *ht_inc = FALSE; //re-balancing is done
            }
        }
    }
    else if (data > tree->data)
    {
        // Insert in the right sub-tree
        tree->right = insert(data, tree->right, ht_inc);
        if (*ht_inc == TRUE) // a re-balancing might be needed
        {
            // Check the balance factor after the insertion
            switch (tree->balance)
            {
            case 1: /* Left heavy */
                // the node was left heavy and after insertion has become balanced.
                tree->balance = 0;
                *ht_inc = FALSE; // re-balancing will not be needed at a hihger level
                break;
            case 0: /* Balanced */
                // the node was balanced and after insertion has become right heavy.
                tree->balance = -1;
                break;
            case -1: /* Right heavy */
                // the node was right heavy and after insertion has become an unbalanced sub-tree.
                // Rebalancing rotation is needed - determine the type of rotation
                aptr = tree->right; // "tree" is A and "aptr" is B (see slides 47 and 49)
                if (aptr->balance == -1)
                {
                    printf("Right to Right Rotation\n");
                    tree->right = aptr->left; // T2 is made right sub-tree of A (see slide 47)
                    aptr->left = tree;              // A is made left sub-tree of B (see slide 47)
                    tree->balance = 0;
                    aptr->balance = 0;
                    tree = aptr; // B is moved up to A-palce (see slide 47)
                }
                else
                {
                    printf("Right to Left Rotation\n");
                    bptr = aptr->left;              //  "bptr" is C (see slide 49)
                    aptr->left = bptr->right; // T3 is made left sub-tree of B (see slide 49)
                    bptr->right = aptr;             // B is made right sub-tree of C (see slide 49)
                    tree->right = bptr->left;  // T2 is made right sub-tree of A (see slide 49)
                    bptr->left = tree;
                    if (bptr->balance == -1)
                        tree->balance = 1;
                    else
                        tree->balance = 0;
                    if (bptr->balance == 1)
                        aptr->balance = -1;
                    else
                        aptr->balance = 0;
                    bptr->balance = 0;
                    tree = bptr; // C is moved up to A-palce (see slide 49)
                }               /*End of else*/
                *ht_inc = FALSE; // re-balancing is done
            }
        }
    }
    return (tree);
}

void display(struct node* ptr, int level)
{
    int i;
    if (ptr != NULL)
    {
        display(ptr->right, level + 1);
        printf("\n");
        for (i = 0; i < level; i++)
            printf(" ");
        printf("%d", ptr->data);
        display(ptr->left, level + 1);
    }
}


void inorder(struct node* tree)
{
    if (tree != NULL)
    {
        inorder(tree->left);
        printf("%d(%d)  ", tree->data, tree->balance);
        inorder(tree->right);
    }
}

//Make a function to find the height of a tree, Code below!
int findHeight(struct node* tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    else
    {
        int leftHeight = findHeight(tree->left);
        int rightHeight = findHeight(tree->right);

        if (leftHeight > rightHeight)
        {
            return leftHeight + 1;
        }
        else
        {
            return rightHeight + 1;
        }
    }
}


//Make a deletion function for a AVL Tree, Code below!
struct node* deleteNode(struct node* root, int data)
{
    if (root == NULL)
    {
        return root;
    }
    else if (data < root->data)
    {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = deleteNode(root->right, data);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        else if (root->left == NULL)
        {
            struct node* temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL)
        {
            struct node* temp = root;
            root = root->left;
            free(temp);
        }
        else
        {
            struct node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    if (root == NULL)
    {
        return root;
    }
    root->balance = height(root->left) - height(root->right);
    if (root->balance > 1 && root->left->balance >= 0)
    {
        return rightRotate(root);
    }
    if (root->balance > 1 && root->left->balance < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (root->balance < -1 && root->right->balance <= 0)
    {
        return leftRotate(root);
    }
    if (root->balance < -1 && root->right->balance > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
//Make a function to find the minimum value in a AVL Tree, Code below!
struct node* findMin(struct node* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->left == NULL)
    {
        return root;
    }
    else
    {
        return findMin(root->left);
    }
}
//Make a function to find the maximum value in a AVL Tree, Code below!
struct node* findMax(struct node* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->right == NULL)
    {
        return root;
    }
    else
    {
        return findMax(root->right);
    }
}
//Make a function to find the height of a AVL Tree, Code below!
int height(struct node* root)
{
    if (root == NULL)
    {
        return -1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if (leftHeight > rightHeight)
    {
        return leftHeight + 1;
    }
    else
    {
        return rightHeight + 1;
    }
}
//Make a function to find the balance of a AVL Tree, Code below!
int balance(struct node* root)
{
    if (root == NULL)
    {
        return 0;
    }
    return height(root->left) - height(root->right);
}
//Make a function to rotate the AVL Tree to the left, Code below!
struct node* leftRotate(struct node* root)
{
    struct node* temp = root->right;
    struct node* temp2 = temp->left;
    temp->left = root;
    root->right = temp2;
    root->balance = height(root->left) - height(root->right);
    temp->balance = height(temp->left) - height(temp->right);
    return temp;
}
//Make a function to rotate the AVL Tree to the right, Code below!
struct node* rightRotate(struct node* root)
{
    struct node* temp = root->left;
    struct node* temp2 = temp->right;
    temp->right = root;
    root->left = temp2;
    root->balance = height(root->left) - height(root->right);
    temp->balance = height(temp->left) - height(temp->right);
    return temp;
}

int main()
{
    struct node* root = NULL;
    struct node* root2 = NULL;
    bool ht_inc = FALSE;
    bool ht_dec = FALSE;

    puts("first test");
    root = insert(45, root, &ht_inc);
    root = insert(63, root, &ht_inc);
    root = insert(36, root, &ht_inc);
    root = insert(72, root, &ht_inc);
    root = insert(39, root, &ht_inc);
    root = insert(27, root, &ht_inc);
    root = insert(37, root, &ht_inc);
    root = insert(41, root, &ht_inc);
    display(root, 1);
    root = deleteNode(root, 72);
    puts("\nDeleted node 72");
    display(root, 1);
    printf("\n");


    puts("second test");
    root2 = insert(54, root2, &ht_inc);
    root2 = insert(63, root2, &ht_inc);
    root2 = insert(45, root2, &ht_inc);
    root2 = insert(65, root2, &ht_inc);
    root2 = insert(51, root2, &ht_inc);
    root2 = insert(39, root2, &ht_inc);
    root2 = insert(47, root2, &ht_inc);
    root2 = insert(18, root2, &ht_inc);

    printf("\n");
    display(root2, 1);
    root2 = deleteNode(root2, 65);
    puts("\nDeleted node 65");
    display(root2, 1);
    printf("\n");
    return 0;
}
