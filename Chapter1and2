// Algorithmtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

unsigned int Recursive(int number, int expo)
{
	if (expo == 1)
		return number;
	if (expo == 0)
		return 1;
	if (expo % 2 == 0)
	{
		//std::cout << "Even:expo:" << expo << std::endl;
		unsigned int temp = Recursive(number, expo / 2);
		unsigned int result = temp * temp;
		//std::cout << result << std::endl;
		return result;
	}
	if (expo % 2 == 1)
	{
		//std::cout << "Odd:expo:" << expo << std::endl;
		unsigned int temp = Recursive(number, (expo-1)/2);
		unsigned int result = number*temp*temp;
		//std::cout << result << std::endl;
		return result;
	}
}


unsigned int Non_Recursive(int number, int expo)
{
	unsigned int result = 1;
	unsigned int num=number, ex=expo;
	while (ex)
	{
		if(ex%2 ==1)
			result = result*num;
		num = num* num;
		ex = ex / 2;
	}
	return result;
}

int gcd(int a, int b)
{
	while (b)
	{
		int r = a%b; 
		a = b;
		b = r;
	}
	return a;
}


void Node_insert(int v, int *H, int current)
{
	H[current] = v;
	for (int i = current; i >= 0; i = i / 2)
	{
		if (H[i] > H[i / 2])
		{
			int temp = H[i];
			H[i] = H[i / 2];
			H[i / 2] = temp;
		}
		else
			break;
	}
}

int Deleting_root(int *H, int current)
{
	if (current == 0)
		return 0;
	std::cout <<"H[0]:"<< H[0] << ", current:"<<current<<", H[current-1]="<<H[current-1]<<std::endl;
	current = current - 1;
	H[0] = H[current];
	std::cout << H[0] << std::endl;
	H[current] = 0;
	if (current >= 2)
	{
		int i;
		for (i = 0; i * 2 + 1 <= current; )
		{
			if (i * 2 + 2 > current)
			{
				if (H[i * 2 + 1] > H[i])
				{
					int temp = H[i];
					H[i] = H[i * 2 + 1];
					H[i * 2 + 1] = temp;
				}
				return current;
			}
			if (H[i * 2 + 1] <= H[i * 2 + 2])
			{
				std::cout << "i*2+1<=i*2+2, " << H[i] << "," << H[i * 2 + 2] << std::endl;
				int temp = H[i];
				H[i] = H[i * 2 + 2];
				H[i * 2 + 2] = temp;
				i = i * 2 + 2;
			}
			else if (H[i * 2 + 1] > H[i * 2 + 2])
			{
				std::cout << "i*2+1>i*2+2, " << H[i] << "," << H[i * 2 + 1] << std::endl;
				int temp = H[i];
				H[i] = H[i * 2 + 1];
				H[i * 2 + 1] = temp;
				i = i * 2 + 1;
			}
		}
	}
	return current;
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	// Math foundamental
	int number;
	int expo;
	std::cin >> number >> expo;
	printf("%ld\n", Recursive(number,expo));
	printf("%ld\n", Non_Recursive(number, expo));
	*/

	// Heap test
	int Heap[100];
	int current = 0;

	while (1)
	{
		int input;
		std::cin>>input;
		if (input == 0)
			break;
		Node_insert(input, Heap, current++);
	}

	
	for (int i = 0; i <= current-1; i++)
	{
		printf("%d,",Heap[i]);
	}
	printf("\n");
	
	Deleting_root(Heap, current);

	for (int i = 0; i <= current - 1; i++)
	{
		printf("%d,", Heap[i]);
	}

	getchar();
	getchar();
	return 0;
}
