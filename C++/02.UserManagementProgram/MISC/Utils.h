#pragma once
#include "Classes/Account.h"

struct FUtils
{
	static FAccount MakeAccountFromUserInput()
	{
		FAccount Account;
		cout << "Input ID: ";
		cin >> Account.ID;

		cout << "Input Password: ";
		cin >> Account.Password;

		return Account;
	}

	// InFunctionName: __func__
	static void PrintSystemSuccessOrFailed(bool bFlag, const char* InFunctionName)
	{
		if (bFlag)
		{
			cout << format("[System]{} success\n", InFunctionName);
		}
		else
		{
			cout << format("[System]{} failed\n", InFunctionName);
		}
	}
};

