// POJ1000_1001_1002.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

string MultiOne(string temp1, int n)
{
	string result;
	int length1 = temp1.length();
	int extra = 0;

	int tempResult = 0;
	string temp;

	for (int i = length1 - 1; i >= 0; i--)
	{
		tempResult = (temp1[i] - '0')*(n) + extra;
		extra = tempResult / 10;
		result.insert(0, 1, (tempResult % 10) + '0');
	}
	if (extra > 0)
		result.insert(0, 1, extra + '0');

	return result;
}

string BigPlus(string temp1, string temp2)
{
	string result;
	int length1 = temp1.length();
	int length2 = temp2.length();
	if (length2 > length1)
	{
		for (int i = 1; i <= length2 - length1; i++)
		{
			temp1.insert(0, 1, '0');
		}
	}
	else if (length2 < length1)
	{
		for (int i = 1; i <= length1 - length2; i++)
		{
			temp2.insert(0, 1, '0');
		}
	}
	//cout << temp1 << ", " << temp2 << endl;
	//cout << temp1.length() << ", " << temp2.length() << endl;
	int extra = 0;
	int digit;
	for (int i = temp1.length()-1; i >=0; i--)
	{
		digit = (temp1[i]-'0' + temp2[i]-'0' + extra) % 10;
		extra = (temp1[i]-'0' + temp2[i]-'0' + extra) / 10;
		//cout << "digit:" << digit << ", extra:" << extra << endl;
		result.insert(0, 1, digit + '0');
	}
	if (extra > 0)
		result.insert(0, 1, extra + '0');
	return result;
}

string Multiply(string temp1, string temp2)
{
	string result = "0";
	int length1 = temp1.length();
	int length2 = temp2.length();
	int extra = 0;

	int tempResult = 0;
	string result1;
	int i = length2 - 1;
	while (i >=0)
	{
		int n = temp2[i] - '0';
		result1 = MultiOne(temp1,n);
		//cout << result1 << endl;
		for (int j = 1; j <= length2 - 1 - i; j++)
		{
			result1 += '0';
		}
		result = BigPlus(result, result1);
		i--;
	}
	return result;
}

int Pre_processing(string* a)
{
	int length = (*a).length();
	int flag = 0;
	int position = -1;
	for (int i = length - 1; i >= 0; i--)
	{
		if ((*a)[i] == '0' && flag == 0)
			(*a).pop_back();
		else if (((*a)[i] - '0'>0) && ('9' - (*a)[i] >= 0) && (flag == 0))
		{
			flag = 1;
		}
		else if (flag == 0 && (*a)[i] == '.')
		{
			(*a).pop_back();
			flag = 1;
		}
		else if ((*a)[i] == '.')
		{
			position = i;
			(*a).erase((*a).begin()+i);
		}
	}
	return position;
}

string Exponent(string s, int n)
{
	if (n == 1)
	{
		return s;
	}
	else
	{
		if (n % 2 == 0)
		{
			string temp1 = Exponent(s, n / 2);
			string temp2 = Multiply(temp1, temp1);
			/*
			if (position != -1)
				temp2.insert(temp2.end()-position,'.');*/
			return temp2;
		}
		else
		{
			string temp1 = Exponent(s, (n-1)/2);
			string temp2 = Multiply(temp1, temp1);
			string temp3 = Multiply(temp2, s);
			/*
			if (position != -1)
				temp3.insert(temp3.end() - position, '.');*/
			return temp3;
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	string s;
	int n;
	int position;
	while (cin >> s >> n)
	{
		position = Pre_processing(&s);
		position = s.length() - position;
		s = Exponent(s, n);
		if (s[0] == '0')
		{
			s.erase(s.begin());
		}
		s.insert(s.end() - position * n, '.');
		cout << s << endl;
	}
}

