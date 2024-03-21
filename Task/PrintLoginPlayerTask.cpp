#include "PrintLoginPlayerTask.h"
#include "MISC/Utils.h"
#include "Classes/LoginSession.h"

FPrintLoginPlayerTask::FPrintLoginPlayerTask()
{
	const auto& PlayerMap = GLoginSession.GetPlayerMap();
	cout << "[------   Player   ------]" << endl;
	for (auto& It : PlayerMap)
	{
		cout << format("-> Name: {}\n", It.second.GetName());
	}
	cout << "[----------------------]" << endl;
}
