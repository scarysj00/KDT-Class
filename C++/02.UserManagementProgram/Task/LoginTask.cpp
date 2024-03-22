#include "LoginTask.h"
#include "MISC/Utils.h"
#include "Classes/LoginSession.h"
#include "Classes/DataBase.h"

FLoginTask::FLoginTask()
{
	cout << "[------     Login     -----]" << endl;
	const FAccount Account = FUtils::MakeAccountFromUserInput();
	pair Result = GLoginSession.Login(Account);
	FPlayer* Player = Result.first;
	if (Player)
	{
		const bool bLoad = GDataBase.LoadPlayer(Account.ID, *Result.first);
		if (bLoad)
		{
			cout << "Player 정보를 불러 왔습니다\n";
		}

		int Level = Player->GetLevel();
		Player->SetLevel(Level + 1);
	}

	cout << Result.second << endl;
}
