// Written by Emerithe Cantanine on September 28, 2021

#include <iostream>
#include <vector>

using namespace std;

struct treeType
{
	int id;

	treeType* left, * right;

	treeType(int i)
	{
		id = i - 1;
		if (id == 1)
		{
			left = right = NULL;
			return;
		}
		left = new(treeType)(id);
		right = new(treeType)(id);
	}

	treeType()
	{
		id = 0;
		left = right = NULL;
	}
};

treeType* DeepCopy(treeType* __original)
{
	vector<treeType*> originalStack;	// original
	vector<treeType*> copyStack;		// copy
	treeType* current = __original;
	originalStack.push_back(NULL);	// Mark an obvious stopping point.
	treeType* copy = new(treeType);
	treeType* runner = copy;
	copyStack.push_back(NULL);	// Mark an obvious stopping point.

	runner->id = current->id;	// copy the attributes from 'current' to 'runner'

	while (current != NULL)	// Look at how each stack initially has NULL pushed to them and think about the process of this function for a second.
	{
		if (current->right != NULL && runner->right == NULL)	// if the right branch has not been copied.
		{
			originalStack.push_back(current);	// save where current is.
			copyStack.push_back(runner);		// save where runner is.

			current = current->right;	// move current 1 level down
			runner->right = new(treeType);	// make new treeType
			runner = runner->right;	// move runner 1 level down.

			// copy values from the original over to the copy.
			runner->id = current->id;

			continue;	// Cycle through each one until a dead end is hit.
		}

		if (current->left != NULL && runner->left == NULL)	// if the right branch has not been copied.
		{
			originalStack.push_back(current);	// save where current is.
			copyStack.push_back(runner);		// save where runner is.

			current = current->left;	// move current 1 level down
			runner->left = new(treeType);	// make new treeType
			runner = runner->left;	// move runner 1 level down.

			// copy values from the original over to the copy.
			runner->id = current->id;

			continue;	// Cycle through each one until a dead end is hit.
		}

		// at this point a dead end has been hit and it can't go any deeper in (this part of) the tree.

		// back track up or to the left.
		current = originalStack.back();
		originalStack.pop_back();	// remove the last element because it is no longer needed.
		runner = copyStack.back();
		copyStack.pop_back();		// remove the last element because it is no longer needed.
	}

	return copy;
}

int main()
{
	cout << sizeof(treeType);	// x86: 12 bytes, x64: 24 bytes
	// I highly recommend compiling in x64 if you do trees of more than 20 levels.
	treeType thing(26);	// make a tree with roughly 1000 nodes;

	treeType* copy = DeepCopy(&thing);

	return 0;
}
