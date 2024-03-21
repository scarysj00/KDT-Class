#include "LogoutTask.h"
#include "MISC/Utils.h"
#include "Classes/LoginSession.h"

FLogoutTask::FLogoutTask()
{
	cout << "[------    Logout    -----]" << endl;
	const FAccount Account = FUtils::MakeAccountFromUserInput();
	ExecuteTask(Account);
}

FLogoutTask::FLogoutTask(const FAccount& InAccount)
{
	ExecuteTask(InAccount);
}

void FLogoutTask::ExecuteTask(const FAccount& InAccount)
{
	pair Result = GLoginSession.Logout(InAccount);
	cout << Result.second << endl;
}
