#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
PSEUDO CODE FOR THE SEARCH FUNCTION

Parameter: The tree that you want to search in, and the search value.
Returns the M-tree or NULL PTR if searchvalue not found

    IF [TREE == NULL]
        Return NULL
        [END OF IF]

    IF (VAL < TREE->VAL[0])
        TRAVERSE LEFT SUBTREE
        RETURN SEARCHELEMENT(TREE->LEFT, VAL)
        [END OF IF]

    IF (VAL > TREE->[CHILDREN])
        TRAVERSE RIGHT SUBTREE
        RETURN SEARCHELEMENT(TREE->RIGHT, VAL)
        [END OF IF]

    ELSE
        FOR KEY IN TREE->VAL[]
            IF KEY == VAL
                RETURN TREE
        [END OF IF]

    FOR (i = 0 ; (i + 1) < KEY COUNT OF TREE; i++)
        IF (VAL > TREE->KEYS[i] && VAL < TREE->KEYS[i+1]
            RETURN searchElement(TREE->CHILD[i + 1], VAL)
        [END OF IF]
    [END OF LOOP]

    RETURN NULL IF KEY NOT FOUND
*/

// B-tree order
#define MAX 4

struct node
{
    struct node* children[MAX]; // M sub-trees
    int keys[MAX - 1];          // M-1 keys
    int key_count;              // number of keys, number of children is key_count+1
};

struct node* root;

//create a node with given keys and number of them and a pointer to children
struct node* createNode(int keys[], int count, struct node* children[])
{
    int i = 0;
    struct node* newNode;
    newNode = (struct node*)malloc(sizeof(struct node));
    newNode->key_count = count;

    while (i < count)
    {
        newNode->keys[i] = keys[i];
        newNode->children[i] = children[i];
        i++;
    }

    newNode->children[count] = children[count];
    return newNode;

}

// Inorder traversal
void traverse(struct node* tree, int level)
{
    if (tree == NULL)
    {
        return;
    }
    for (int i = 0; i < tree->key_count; i++)
    {
        traverse(tree->children[i], level + 1);
        printf("\n");
        for (int i = 0; i < level; i++)
        {
            printf("  ");
        }
        printf("%d ", tree->keys[i]);
    }
    traverse(tree->children[tree->key_count], level + 1);
}

//function that search for given element
struct node* search(struct node* tree, int val)
{
    if (tree == NULL)
    {
        puts("Subtree didn't exist");
        return tree;
    }

    if (val < tree->keys[0]) //If the key is less than the smallest, Traverse right subtree
    {
        printf("%d Is less than %d traversing right subtree \n", val, tree->keys[0]);
        return search(tree->children[0], val);
    }


    if (val > tree->keys[tree->key_count - 1]) //If key is larger than the biggest element, Traverse left subtree
    {
        printf("%d Is larger than %d traversing left subtree \n", val, tree->keys[tree->key_count - 1]);
        return search(tree->children[tree->key_count], val);
    }
    else
    {
        for (int i = 0; i < tree->key_count; i++)
        {
            if (tree->keys[i] == val)
            {
                return tree;
            }
        }
    }

    for (int i = 0; (i + 1) < tree->key_count; i++) //Find subtree between
    {
        if (val > tree->keys[i] && val < tree->keys[i + 1])
        {
            printf("Key should be in a subtree between these two keys %d %d\n", tree->keys[i], tree->keys[i + 1]);
            return search(tree->children[i + 1], val);
        }

    }

    return NULL;
}

int main()
{
    // Max amount of children for all nodes is 4
    struct node* leaf_children[4] = { NULL, NULL, NULL, NULL };

    // Create the left sub-tree
    int leaf1_keys[2] = { 18, 27 };
    struct node* leaf1 = createNode(leaf1_keys, 2, leaf_children);

    int leaf2_keys[2] = { 30, 31 };
    struct node* leaf2 = createNode(leaf2_keys, 2, leaf_children);

    int leaf3_keys[2] = { 36, 39 };
    struct node* leaf3 = createNode(leaf3_keys, 2, leaf_children);

    int inter1_keys[2] = { 29, 32 };
    struct node* inter1_children[3] = { leaf1, leaf2, leaf3 };
    struct node* inter1 = createNode(inter1_keys, 2, inter1_children);

    // Create the right sub-tree
    int leaf4_keys[2] = { 46, 47 };
    struct node* leaf4 = createNode(leaf4_keys, 2, leaf_children);

    int leaf5_keys[3] = { 54, 59, 61 };
    struct node* leaf5 = createNode(leaf5_keys, 3, leaf_children);

    int leaf6_keys[2] = { 67, 72 };
    struct node* leaf6 = createNode(leaf6_keys, 2, leaf_children);

    int inter2_keys[2] = { 49, 63 };
    struct node* inter2_children[3] = { leaf4, leaf5, leaf6 };
    struct node* inter2 = createNode(inter2_keys, 2, inter2_children);

    // Create the root
    int root_keys[1] = { 45 };
    struct node* root_children[2] = { inter1, inter2 };
    root = createNode(root_keys, 1, root_children);



    puts(" ");
    puts("MENU");

    int choice;

    while (1)
    {
        puts(" ");
        puts("1. Search");
        puts("2. Display tree");
        puts("3. Quit");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter key to find: ");
            scanf("%d", &choice);
            if (search(root, choice) != NULL)
                puts("Key found!");
            else
                puts("Not found");
            break;
        case 2:
            traverse(root, 0);
            break;
        case 3:
            exit(0);
            break;
        }
    }

    printf("\n");
}