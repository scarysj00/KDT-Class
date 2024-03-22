#include "LogoutTask.h"
#include "MISC/Utils.h"
#include "Classes/LoginSession.h"
#include "Classes/DataBase.h"

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
	FPlayer* Player = GLoginSession.GetLoginPlayer(InAccount.ID);
	if (!Player)
	{
		cout << "[LogoutTask] Error\n";
		return;
	}
	pair Result = GLoginSession.Logout(InAccount);
	cout << Result.second << endl;
}
