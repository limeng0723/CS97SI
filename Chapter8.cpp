// Chapter8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

#define N 6
float linkProbability = 0.7;
int adjacentMatrix[N][N];
int bandwidth[N][N];
int tempBandwidth[N][N];

int tag[N];
int markedStack[N];
int markedStack_pointer; // A pointer that point at the top of the marked stack;
// Max-Flow algorithm

void PrintBandwidth()
{
	printf("Bandwidth:\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d, ", tempBandwidth[i][j]);
		}
		printf("\n");
	}
}

void PrintStack()
{
	printf("Stack:\n");
	for (int i = markedStack_pointer-1; i >= 0; i--)
	{
		printf("%d, ", markedStack[i]);
	}
	printf("\n");
}

void InitializeTag()
{
	for (int i = 0; i < N; i++)
	{
		tag[i] = 1;
	}
}

bool CheckTag(int i)
{
	return tag[i];
}

void MarkTag(int i)
{
	tag[i] = 0;
}

void InitializeTopology()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			adjacentMatrix[i][j] = rand() % 100;
			if (adjacentMatrix[i][j] >= 100 * linkProbability)
				adjacentMatrix[i][j] = 0;
			else
				adjacentMatrix[i][j] = 1;
		}
}
void InitializeBandwidth()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			bandwidth[i][j] = rand() % 20;
		}
}
void InitializeGraph()
{
	InitializeTopology();
	InitializeBandwidth();
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			bandwidth[i][j] = bandwidth[i][j] * adjacentMatrix[i][j];
			if (i == j)
				bandwidth[i][j] = 0;
		}
	}
}

void PrintGraph()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d, ", bandwidth[i][j]);
		}
		printf("\n");
	}
}

void Push(int * stack, int value, int * top)
{
	stack[(*top)] = value;
	(*top)++;
	return;
}

int Pop(int * stack, int * stack_top)
{
	int temp;
	if ((*stack_top)-1>-1)
	{
		temp = stack[(*stack_top)-1];
		(*stack_top)--;
		return temp;
	}
	else
	{
		return -1;
	}
}

int DFS() // Non-recursive
{
	int stack[N];
	int stack_top = 0; // Pointing at the place where the new elements can be stored.
	int current = 0;	// Current node. 
	InitializeTag();	// All tags one. 
	Push(stack, current, &stack_top);
	while (1)
	{
		current = Pop(stack, &stack_top);
		MarkTag(current);
		for (int i = 0; i < N; i++)
		{
			if (tempBandwidth[current][i] > 0)
			{
				Push(stack, i, &stack_top);
			}
		}
	}
	return 0;
}

void DFS(int currentNode, int *temp) // Recursive;
{
	printf("%d, ", currentNode);
	temp[currentNode] = 0;	// Mark as visited;
	for (int i = 0; i < N; i++)
	{
		if (bandwidth[currentNode][i] != 0)
		{
			if (temp[i] != 0)
			{
				temp[i] = 0; // Mark as visited;
				DFS(i, temp);
			}
		}
	}
}

int DFS_MF(int currentNode, int *temp, int *flag) // DFS for maxflow, recursive
{
	int minimum = 65535;
	if (currentNode == (N - 1))
	{
		(*flag) = 1;
		//printf("%d, ", currentNode);
		//cout << "temp_min:" << 65535 << ", current:" << currentNode << endl;
		Push(markedStack, currentNode, &markedStack_pointer);
		return minimum;
	}
	//printf("%d, ", currentNode);
	for (int i = 1; i < N; i++)
	{
		if (tempBandwidth[currentNode][i] > 0)
		{
			if (temp[i] != 0)
			{
				temp[i] = 0; // Mark as visited;
				int temp_min = DFS_MF(i, temp, flag);
				if ((*flag) == 1)
				{
					if (temp_min>tempBandwidth[currentNode][i])
						temp_min = tempBandwidth[currentNode][i];
					//cout << "temp_min:" << temp_min << ", current:" << currentNode << endl;
					Push(markedStack, currentNode, &markedStack_pointer);
					return temp_min;
				}
				else
				{
					//cout << "current:" << currentNode << ", choose" << i << endl;
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
	}
	return minimum;
}

void Init_markedStack()
{
	for (int i = 0; i < N; i++)
	{
		markedStack[i] = -1;
	}
	markedStack_pointer = 0;
}

void ReduceBandwidth(int reducedValue)
{
	int nodeFrom, nodeTo;
	nodeFrom = Pop(markedStack, (&markedStack_pointer));
	cout << "Call reduceBandwidth" << endl;
	while ((nodeTo = Pop(markedStack, (&markedStack_pointer)))!=-1)
	{
		tempBandwidth[nodeFrom][nodeTo] -= reducedValue;
		tempBandwidth[nodeTo][nodeFrom] += reducedValue;
		cout << "from:" << nodeFrom << ", to:" << nodeTo << endl;
		nodeFrom = nodeTo;
	}
}

void Init_markedNodes(int *temp_DFS)
{
	for (int i = 1; i < N; i++)
	{
		temp_DFS[i] = 1;
	}
	return;
}


int Maxflow()
{
	Init_markedStack();
	memcpy(tempBandwidth, bandwidth, sizeof(tempBandwidth));
	int maxflow = 0;
	int flag = 0;
	int temp_Markednodes[N];
	while (true)
	{
		Init_markedStack();
		Init_markedNodes(temp_Markednodes);
		flag = 0;
		int temp = DFS_MF(0, temp_Markednodes, &flag);
		PrintStack();
		if ((temp > 0) && (flag == 1))
		{
			maxflow += temp;
			ReduceBandwidth(temp);
			cout << temp << endl;
			PrintBandwidth();
			cout << "---------------" << endl;
			PrintGraph();
		}
		else
			break;
	}
	return maxflow;
}

int _tmain(int argc, _TCHAR* argv[])
{
	InitializeGraph();
	PrintGraph();
	//int result = Maxflow();
	//cout << result << endl;

	/*int temp_DFS[N];
	for (int i = 0; i < N; i++)
	{
	temp_DFS[i] = 1;
	}
	DFS(0, temp_DFS);*/

	/*int temp_DFS[N];
	for (int i = 1; i < N; i++)
	{
		temp_DFS[i] = 1;
	}
	temp_DFS[0] = 0;
	int flag = 0;
	int result;
	result = DFS_MF(0, temp_DFS, &flag);
	cout << "result:" << result << endl;*/

	cout << "result:" << Maxflow() << endl;


	getchar();
	return 0;
}

