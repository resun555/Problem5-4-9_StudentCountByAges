// Problem5-4-9_StudentCountByAges.c : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#define LENGTH 10

#pragma warning( disable : 4996 )

struct Student
{
	char sname[20];
	size_t sage;
};

typedef struct Student Student;

struct AgeCountMap
{
	size_t age;
	size_t count;
};

typedef struct AgeCountMap AgeCountMap;

struct BinaryNode
{
	AgeCountMap countMap;
	struct BinaryNode *leftChild;
	struct BinaryNode *rightChild;
};

typedef struct BinaryNode BinaryNode;

BinaryNode * Insert(
	BinaryNode **root, 
	BinaryNode *newNode
);

void InOrder(
	BinaryNode *root, 
	void (*Process)(BinaryNode *node)
);


void AccessProcess(
	BinaryNode *node
);

void Release(
	BinaryNode *root
);


int main()
{
	Student student;
	BinaryNode *root = NULL;
	for (size_t i = 0; i < LENGTH; i++)
	{
		printf("Enter student name: ");
		gets_s(student.sname, 20);
		printf("Enter student age: ");
		scanf("%zu", &student.sage);
		getchar();
		BinaryNode *newNode = (BinaryNode *)malloc(sizeof(BinaryNode));
		newNode->countMap.age = student.sage;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		BinaryNode *node = Insert(&root, newNode);
		if (node != newNode)
		{
			free(newNode);
		}
		if (node == newNode)
		{
			node->countMap.count = 0;
		}
		node->countMap.count++;
	}
	InOrder(root, AccessProcess);
	Release(root);
    return 0;
}


BinaryNode * Insert(BinaryNode **root, BinaryNode *newNode)
{
	if (*root == NULL)
	{
		*root = newNode;
		return *root;
	}
	else
	{
		if (newNode->countMap.age < (*root)->countMap.age)
		{
			return Insert(&(*root)->leftChild, newNode);
		}
		else if (newNode->countMap.age > (*root)->countMap.age)
		{
			return Insert(&(*root)->rightChild, newNode);
		}
		else
		{
			return *root;
		}
	}
}


void InOrder(BinaryNode *root, void (*Process)(BinaryNode *node))
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		InOrder(root->leftChild, Process);
		Process(root);
		InOrder(root->rightChild, Process);
		return;
	}
}


void AccessProcess(BinaryNode *node)
{
	printf("Student age: %zu\n", node->countMap.age);
	printf("Student count: %zu\n", node->countMap.count);
	return;
}


void Release(BinaryNode *root)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		Release(root->leftChild);
		Release(root->rightChild);
		free(root);
		return;
	}
}

