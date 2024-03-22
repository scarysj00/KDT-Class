#pragma once
#include "MISC/Headers.h"

// Account로 로그인을 수행했을 때 생성됨
class FPlayer
{
	friend class FPlayerSaveLoader;
public:
	FPlayer(string_view InName)
		:Name(InName)
	{
	}

	string_view GetName() const
	{
		return Name;
	}

	void SetLevel(const int InLevel)
	{
		Level = InLevel;
	}
	int GetLevel() const
	{
		return Level;
	}

private:   
	string Name;
	int Level = 0;
};

class FPlayerSaveLoader
{
	friend class FDataBase;
protected:
	FPlayerSaveLoader(FPlayer& InPlayer)
		: Player(InPlayer) {}

protected:
	bool Save();
	bool Load(const FAccountName& InAccountName);

private:
	FPlayer& Player;
};