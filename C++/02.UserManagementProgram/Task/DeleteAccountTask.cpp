#include "DeleteAccountTask.h"
#include "MISC/Utils.h"
#include "Classes/DataBase.h"
#include "LogoutTask.h"

FDeleteAccountTask::FDeleteAccountTask()
{
	cout << "[------ Delete Account -----]" << endl;
	const FAccount Account = FUtils::MakeAccountFromUserInput();

	if (GDataBase.CheckAccount(Account))
	{
		FLogoutTask LogoutTask(Account);
	}

	bool bResult = GDataBase.DeleteAccount(Account);
	FUtils::PrintSystemSuccessOrFailed(bResult, __func__);
}
