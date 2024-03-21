#include "PrintAccountTask.h"
#include "Classes/DataBase.h"

FPrintAccountTask::FPrintAccountTask()
{
	const auto& AccountMap = GDataBase.GetAccountMap();
	cout << "[--------Account--------]" << endl;
	for (auto& It : AccountMap)
	{
		cout << format("-> ID: {}, PW: {} \n", It.second.ID, It.second.Password);
	}
	cout << "[-----------------------]" << endl;
}
