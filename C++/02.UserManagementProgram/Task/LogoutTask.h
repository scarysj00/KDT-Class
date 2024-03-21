#pragma once
#include "Classes/Account.h"

struct FLogoutTask
{
	FLogoutTask();
	FLogoutTask(const FAccount& InAccount);

private:
	void ExecuteTask(const FAccount& InAccount);
};

