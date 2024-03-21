#include "LoginTask.h"
#include "MISC/Utils.h"
#include "Classes/LoginSession.h"

FLoginTask::FLoginTask()
{
	cout << "[------     Login     -----]" << endl;
	const FAccount Account = FUtils::MakeAccountFromUserInput();
	pair Result = GLoginSession.Login(Account);
	cout << Result.second << endl;
}
