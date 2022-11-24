/* @Author
Name: Oytun Demirbilek
Date: 24.12.2018 */
#ifndef PCH_H
#define PCH_H
#endif
#include <iostream>
#include <stdio.h>
struct leaf
{ // DEFINING NODE STRUCT
	int data;
	leaf *left;
	leaf *right;
};
struct tree
{						// DEFINING TREE STRUCT
	leaf *root;			// POINTER TO THE TREE NODES
	char endTree;		// CHECK IF ALL INPUTS OF TREE IS TAKEN
	int indicator;		// INDICATOR IN FILE
	int sum;			// SUM OF NODES
	int tempt;			// TEMPORARY VARIABLE FOR SUM
	int num;			// VARIABLE TO SCAN INPUTS FROM FILE AND CREATE THE TREE
	int i;				// ITERATOR FOR ARRAYS
	int pathleft[100];	// ARRAY TO KEEP PATH OF SUM FOR LEFT SUBTREE
	int pathright[100]; // ARRAY TO KEEP PATH OF SUM FOR RIGHT SUBTREE
	leaf *add(leaf *curr, FILE *fp)
	{
		if (curr == NULL)
		{
			fscanf(fp, "%d", &num); // SCAN
			endTree = fgetc(fp);	// PASS THE GAP
			if (endTree != '\n')
			{ // CHECK NEXT CHAR IN FILE
				endTree = fgetc(fp);
				indicator = ftell(fp);			// IDENTIFY THE PLACE OF INDICATOR
				indicator--;					// MOVE INDICATOR BACKWARDS BY ONE
				fseek(fp, indicator, SEEK_SET); // SET NEW PLACE FOR INDICATOR
			}
			curr = new leaf; // CREATE NEW NODE
			curr->left = NULL;
			curr->right = NULL;
			curr->data = num;
			return curr;
		}
		if (endTree != '\n')
			curr->left = add(curr->left, fp); // RECUR FUNC UNTIL THE LAST INPUT IS TAKEN
		if (endTree != '\n')
			curr->right = add(curr->right, fp); // AFTER LEFT NODE IS CREATED, CREATE RIGHT NODE
		return curr;
	}
	void checkPaths(leaf *curr, int *path)
	{
		if (curr == NULL || curr->data > sum)
		{
			return; // STOP UNTIL NO MORE NODES LEFT OR ALL DATA IN CHILDREN IS BIGGER THAN SUM
		}
		sum = sum - curr->data; // SUM OF NEXT GENERATION
		path[i] = curr->data;	// STORE DATA
		i++;					// NEXT ELEMENT IN ARRAY
		if (sum == 0)
			return; // IF THE SUM IS REACHED, STOP
		checkPaths(curr->left, path);
		checkPaths(curr->right, path);
		if (sum != 0)
		{
			i--; // IF ALL CHILDREN ARE CHECKED AND IT IS NOT ENOUGH TO REACH THE SUM, THEN TURN BACK TO THE PARENTS
			sum = sum + curr->data;
		}
	}
	void printpaths(int *path)
	{
		for (i = 0; i < 100; i++)
		{
			if (path[i] > 0 && path[i] < 999999)
				printf("%d ", path[i]); // INSTEAD OF WRITING THIS A COUPLE OF TIMES, USING A FUNC
		}
	}
};
int main(int argc, char **argv)
{
	leaf *root = NULL;				// DEFINE STARTING OF LEAVES
	FILE *fp = fopen(argv[1], "r"); // OPEN FILE
	tree *callTree = new tree;		// CREATE TREE STRUCT
	callTree->endTree = '0';		// INITIALIZE
	callTree->i = 1;				// INITIALIZE
	while (callTree->endTree != '\n')
	{
		root = callTree->add(root, fp); // ASSIGN ALL DATA OF ALL LEAVES
	}
	fscanf(fp, "%d", &callTree->sum);			// SCAN SUM
	callTree->sum = callTree->sum - root->data; // SUBTRACT THE VALUE OF FIRST NODE
	callTree->tempt = callTree->sum;			// TO THE TEMPORARY
	callTree->pathleft[0] = root->data;			// FIRST ELEMENT IS STABILIZED
	callTree->pathright[0] = root->data;
	callTree->checkPaths(root->left, callTree->pathleft); // CHECKPATHS IN LEFT SUBTREE IN PREORDER
	if (callTree->sum != 0)
		printf("No Path Found "); // IF THE SUM IS NOT ZERO, NO PATH IS THERE
	else
	{
		printf("Path Found: ");
		callTree->printpaths(callTree->pathleft); // PRINT STORED VALUES
	}
	printf("\n");
	callTree->sum = callTree->tempt;						// ASSIGN SUM TO GET BACK ITS VALUE IN THE BEGINNING
	callTree->i = 1;										// START OVER FOR THE OTHER ARRAY
	callTree->checkPaths(root->right, callTree->pathright); // CHECKPATHS IN RIGHT SUBTREE IN PREORDER
	if (callTree->sum != 0)
		printf("No Path Found ");
	else
	{
		printf("Path Found: ");
		callTree->printpaths(callTree->pathright); // PRINT STORED VALUES
	}
	printf("\n");
	fclose(fp); // CLOSE FILE
	return 0;
}
