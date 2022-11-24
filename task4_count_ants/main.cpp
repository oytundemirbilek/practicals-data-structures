
/* @Author
Name: Oytun Demirbilek
Date: 8.12.2018 */

#ifndef PCH_H
#define PCH_H
#endif
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

struct queueNode
{
	int datainq;
	queueNode *next;
};

struct hole
{
	int antinhole;
	hole *next;
};

struct queueAnt
{
	queueNode *headq = NULL;
	queueNode *iterq = NULL;
	int n;

	void push(int antNum)
	{
		if (headq != NULL)
		{
			while (iterq->next != NULL)
				iterq = iterq->next;	   // last node
			iterq->next = new queueNode(); // add node
			iterq->next->datainq = antNum; // assign data
			iterq->next->next = NULL;	   // assign pointer
		}
		else
		{
			headq = new queueNode(); // assign head node if the input is the most first
			headq->datainq = antNum; // assign data
			headq->next = NULL;		 // assign pointer
		}
		iterq = headq; // go to the start
	}
	int pop()
	{
		int popped = headq->datainq; // keep data
		iterq = iterq->next;		 // next node
		delete headq;				 // remove and change head node
		headq = iterq;
		return popped;
	}
};

struct stackAnt
{
	hole *heads = NULL;
	hole *iters = NULL;

	void push(int anttohole)
	{
		iters = new hole();			  // create
		iters->next = heads;		  // new node to the start
		iters->antinhole = anttohole; // assign value
		heads = iters;
	}
	int pop()
	{
		int popped = heads->antinhole; // keep data
		iters = iters->next;		   // next node
		delete heads;				   // remove and change head node
		heads = iters;
		return popped;
	}
};

struct Ants
{
	queueAnt ants;
	queueAnt holeDepths;
	stackAnt hole;
	void ReadFile(char *filename)
	{
		char endf; // checks new line at the end of the file
		FILE *fp = fopen(filename, "r");
		fscanf(fp, "%d", &ants.n);
		for (int i = 0; i < ants.n; i++)
		{
			ants.push(i + 1); // All the ants
		}
		while (!feof(fp) && endf != '\n')
		{

			fscanf(fp, "%d", &holeDepths.n);
			holeDepths.push(holeDepths.n); // hole sequence
			endf = fgetc(fp);
		}
	}
	void ShowContents(bool listAnts)
	{
		if (listAnts == true)
		{
			for (int i = 0; i < ants.n; i++)
			{
				printf("%d ", ants.iterq->datainq); // list ants
				ants.iterq = ants.iterq->next;		// next node of ants
			}
			ants.iterq = ants.headq;
		}
		else
		{
			while (holeDepths.iterq != NULL)
			{
				printf("%d ", holeDepths.iterq->datainq);  // list holes
				holeDepths.iterq = holeDepths.iterq->next; // next node of holes
			}
			holeDepths.iterq = holeDepths.headq; // go to the start
		}
	}
	void CrossRoad()
	{
		int depth;
		int popped;
		while (holeDepths.iterq != NULL)
		{
			depth = holeDepths.iterq->datainq;
			for (int i = 0; i < depth; i++)
			{
				popped = ants.pop(); // ant is fell into the hole
				hole.push(popped);
			}
			for (int i = 0; i < depth; i++)
			{
				popped = hole.pop(); // ant is out of the hole
				ants.push(popped);
			}
			holeDepths.iterq = holeDepths.iterq->next; // next hole
		}
	}
};

int main(int argc, char **argv)
{
	Ants a;
	a.ReadFile(argv[1]); // store the number of ants and depths of holes
	cout << "The initial Ant sequence is: ";
	a.ShowContents(1); // list ant sequence ( initially : 1, 2, ... , N)
	cout << "\n";
	cout << "The depth of holes are: ";
	a.ShowContents(0); // list depth of holes
	cout << "\n";
	a.CrossRoad();
	cout << "The final Ant sequence is: ";
	a.ShowContents(1);
	cout << "\n";
	return 0;
}
