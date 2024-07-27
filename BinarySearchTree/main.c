/*	Hi guys in todays video i will show u how to implement Binary search tree
 *	we will cover Insert, Find and Print functions. Erase will be in separate video.
 *	Let's begin.
 */

// Thanks guys for watching see you in next one :)

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

/* Using typedef so we dont have to repeat the struct word */
typedef struct Node{
	struct Node * left;
	struct Node * right;
	int key;
} Node;


void Insert(Node ** root, int key)
{
	Node ** current = root;


	while((*current))
	{
		/* No duplicates allowed */
		if((*current)->key == key)
			return;

		current = (*current)->key < key ? &(*current)->right : &(*current)->left;
	}

	*current = (Node *) malloc(sizeof(Node));
	(*current)->key = key;
	(*current)->left = NULL;
	(*current)->right = NULL;
}


bool Find(Node * root, int key)
{
	Node * current = root;

	while(current)
	{
		if(current->key == key)
			return true;

		current = current->key < key ? current->right : current->left;
	}
	
	return false;
}


void printRec(Node * root, const char * prefix, bool isLeft)
{
	if(root == NULL)
		return;

	printf("%s", prefix);
	printf(isLeft ? "├──" : "└──");

	printf("%d\n", root->key);

	/* Creating new prefix based on which side we came from, for large trees the prefix 
	 * array needs to be bigger 
	 */
	char newPrefix[256];
	snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLeft ? "│   " : "    ");

	printRec(root->right, newPrefix, true);
	printRec(root->left, newPrefix, false);
}


void print(Node * root)
{
	printRec(root, "", false);
}


void freeBst(Node * root)
{
	if(!root)
		return;

	freeBst(root->left);
	freeBst(root->right);
	free(root);
}


void Test()
{
	Node * root = NULL;

	Insert(&root, 20);
	Insert(&root, 10);
	Insert(&root, 31);
	Insert(&root, 110);
	Insert(&root, 5);
	Insert(&root, 12);

	/* Test finding */
	assert(Find(root, 20) == true);
	assert(Find(root, 110) == true);
	assert(Find(root, 111) == false);

	print(root);

	/* Make sure there are no memory leaks */
	freeBst(root);
}


int main ()
{
	Test();
	return 0;
}



