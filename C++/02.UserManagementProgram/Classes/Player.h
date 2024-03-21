#pragma once
#include "MISC/Headers.h"

// Account로 로그인을 수행했을 때 생성됨
class FPlayer
{
public:
	FPlayer(string_view InName)
		:Name(InName)
	{
	}

	string_view GetName() const
	{
		return Name;
	}

private:
	string Name;
};

