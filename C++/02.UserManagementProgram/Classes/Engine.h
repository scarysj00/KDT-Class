#pragma once
#include "MISC/Headers.h"

class FEngine
{
public:
	void Run();

private:
	void Init();
	void Release();

	EMenuEvent PrintMenu();

private:
	bool bTerminated = false;
};

inline FEngine GEngine;