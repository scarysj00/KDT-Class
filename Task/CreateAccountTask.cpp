#include "CreateAccountTask.h"
#include "MISC/Utils.h"
#include "Classes/DataBase.h"

FCreateAccountTask::FCreateAccountTask()
{
	cout << "[------ Create Account -----]" << endl;
	FAccount Account = FUtils::MakeAccountFromUserInput();
	FAccount* Result = GDataBase.CreateAccount(Account);
	FUtils::PrintSystemSuccessOrFailed(Result, __func__);
}
