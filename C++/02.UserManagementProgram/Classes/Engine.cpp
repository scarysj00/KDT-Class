#include "Engine.h"
#include "Task/Task.h"
#include "MISC/Utils.h"

void FEngine::Run()
{
	Init();

	while (!bTerminated)
	{
		system("pause");
		const EMenuEvent Event = PrintMenu();
		switch (Event)
		{
		case ETerminate:
			bTerminated = true;
			break;
		case ECreateAccount:
		{
			FPrintAccountTask PrintAccountTask;
			FPrintLoginPlayerTask PrintLoginPlayerTask;
			FCreateAccountTask Task;
			break;
		}
		case EDeleteAccount:
		{
			FPrintAccountTask PrintAccountTask;
			FPrintLoginPlayerTask PrintLoginPlayerTask;
			FDeleteAccountTask Task;
			break;
		}
		case EPrintAccount:
		{
			FPrintAccountTask Task;
			break;
		}
		case ELogin:
		{
			FPrintAccountTask PrintAccountTask;
			FPrintLoginPlayerTask PrintLoginPlayerTask;
			FLoginTask Task;
			break;
		}
		case ELogout:
		{
			FPrintAccountTask PrintAccountTask;
			FPrintLoginPlayerTask PrintLoginPlayerTask;
			FLogoutTask Task;
			break;
		}
		case EPrintLoginPlayer:
		{
			FPrintLoginPlayerTask Task;
			break;
		}

		default:
			bTerminated = true;
			break;
		}
	}

	Release();
}

void FEngine::Init()
{
	cout << format("[System]Start {}\n", __FUNCTION__);
}

void FEngine::Release()
{
	cout << format("[System]Shutdown {}\n", __FUNCTION__);
}

EMenuEvent FEngine::PrintMenu()
{
	system("cls");
	cout << "[---------------------------]" << endl;
	cout << "[ Please input event number ]" << endl;
	cout << "[ 0) 프로그램 종료          ]" << endl;
	cout << "[ 1) 회원 가입              ]" << endl;
	cout << "[ 2) 회원 탈퇴              ]" << endl;
	cout << "[ 3) 회원 정보 출력         ]" << endl;
	cout << "[ 4) 로그인                ]" << endl;
	cout << "[ 5) 로그아웃               ]" << endl;
	cout << "[ 6) 로그인 유저 정보 출력   ]" << endl;
	cout << "[---------------------------]" << endl;
	cout << "--> ";

	int Event = 0;
	cin >> Event;

	return static_cast<EMenuEvent>(Event);
}
