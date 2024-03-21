#include "Account.h"

void FAccountSaveLoader::Save(rapidjson::Document::AllocatorType& InAllocator)
{
	AccountValue.AddMember("ID", rapidjson::StringRef(Account.ID.data()), InAllocator);
	AccountValue.AddMember("Password", rapidjson::StringRef(Account.Password.data()), InAllocator);
}

void FAccountSaveLoader::Load()
{
	const bool bID = AccountValue.HasMember("ID");
	const bool bPassword = AccountValue.HasMember("Password");
	// 둘중에 하나라도 없으면 실패
	if (!(bID && bPassword))
	{
		return;
	}

	Account.ID = AccountValue["ID"].GetString();
	Account.Password = AccountValue["Password"].GetString();
}
