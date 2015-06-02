// Chapter3_DynamicProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// 1. Solving longest common subsequence (LCS), and prints its length.
// Using dynamic programming technique.

char x[] = "ABCBDAB";
char y[] = "BDCABC";
string result;
int M = 7;
int N = 6;
int D[7+1][6+1];
string str[7 + 1][6 + 1];

int Solving_LCS(char *x, char *y, string* result)
{
	// recursive
	if (x[0] == '\0' || y[0] == '\0')
		return 0;
	else if (x[0] == y[0])
	{
		(*result) += x[0];
		//cout << *result << endl;
		return 1 + Solving_LCS(x + 1, y + 1, result);
	}
	else
	{
		string temp1;
		string temp2;
		int rtemp2 = Solving_LCS(x + 1, y, &temp2);
		int rtemp1 = Solving_LCS(x, y + 1, &temp1);
		if (rtemp1 >= rtemp2)
		{
			(*result).append(temp1);
			return rtemp1;
		}
		else
		{
			(*result).append(temp2);
			return rtemp2;
		}
	}
}


int Solving_LCS_Nc(char *x, char *y, string *result)
{
	//non-recursive
	for (int i = 0; i <= M; i++)
	{
		D[i][0] = 0;
	}
	for (int i = 0; i <= N; i++)
	{
		D[0][i] = 0;
	}
	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (x[i] == y[j])
			{
				D[i][j] = D[i-1][j-1] +1;
				str[i][j] += x[i];
			}
			else
			{
				D[i][j] = D[i-1][j]>D[i][j-1]?D[i-1][j]:D[i][j-1];
				str[i][j] += D[i - 1][j]>D[i][j - 1] ? str[i-1][j]:str[i][j-1];
			}
		}
	}

	return D[M][N];
}

int _tmain(int argc, _TCHAR* argv[])
{

	//cin >> x;
	//cin >> y;

	int length = Solving_LCS(x, y, &result);
	ostringstream os;
	os << result;
	cout <<"result: "<< os.str() <<", length: "<< length << endl;

	
	length = Solving_LCS_Nc(x, y, &result);
	os << str[7][6];
	cout <<"result: "<<os.str()<< "length: " << length << endl;


	getchar();
	return 0;
}

