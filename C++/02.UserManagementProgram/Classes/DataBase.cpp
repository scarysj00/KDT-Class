#include "DataBase.h"

FDataBase GDataBase;

FAccount* FDataBase::CreateAccount(const FAccount& InAccount)
{
	if (InAccount.IsEmpty())
	{
		_ASSERT(false && "계정 정보가 비어 있습니다.");
		return nullptr;
	}

	// 이미 있는 ID라면 요청 반려
	FAccount* Account = FindAccount(InAccount.ID);
	if (Account)
	{
		_ASSERT(false && "이미 해당 계정이 있다!");
		return nullptr;
	}

	pair Pair = AccountMap.insert(std::make_pair(InAccount.ID, InAccount));
	if (!Pair.second)
	{
		_ASSERT(false);
		return nullptr;
	}

	return &Pair.first->second;
}

FAccount* FDataBase::FindAccount(const FAccountName& InID)
{
	auto It = AccountMap.find(InID);

	// 해당 ID를 찾을 수 없습니다.
	if(It == AccountMap.end())
	{
		return nullptr;
	}

	return &It->second;
}

FAccount* FDataBase::CheckAccount(const FAccount& InAccount)
{
	if (InAccount.IsEmpty())
	{
		_ASSERT(false);
		return nullptr;
	}

	// 해당 ID로 된 Account가 있는지 확인한다
	FAccount* Account = FindAccount(InAccount.ID);
	if (!Account)
	{
		// 해당 ID로 계정 정보를 검색할 수 없다
		_ASSERT(false && "해당 ID로 계정 정보를 검색할 수 없다");
		return nullptr;
	}

	// InAccount와 찾아온 계정 정보가 동일한지 확인
	if (*Account != InAccount)
	{
		// 비밀번호가 일치하지 않습니다!
		_ASSERT(false && "비밀번호가 일치하지 않습니다!");
		return nullptr;
	}

	return Account;
}

bool FDataBase::DeleteAccount(const FAccount& InAccount)
{
	FAccount* Account = CheckAccount(InAccount);
	if (!Account)
	{
		_ASSERT(false);
		return false;
	}

	AccountMap.erase(InAccount.ID);

	return true;
}

FDataBase::FDataBase()
{
	Load();
}

FDataBase::~FDataBase()
{
	Save();
}

void FDataBase::Save()
{
	rapidjson::Document Doc(rapidjson::kObjectType);
	rapidjson::Document::AllocatorType& Allocator = Doc.GetAllocator();

	rapidjson::Value Array(rapidjson::kArrayType);
	for (auto& It : AccountMap)
	{
		rapidjson::Value Player(rapidjson::kObjectType);
		FAccountSaveEvent Save{ It.second, Player, Allocator };
		Array.PushBack(Player, Allocator);
	}

	Doc.AddMember("AccountInfo", Array, Allocator);

	rapidjson::StringBuffer Buffer;
	rapidjson::Writer<rapidjson::StringBuffer> Writer(Buffer);
	Doc.Accept(Writer);
	std::string Json(Buffer.GetString(), Buffer.GetSize());

	std::ofstream File("AccountInfo.json");
	File << Json;
}

void FDataBase::Load()
{
	std::ifstream File("AccountInfo.json");
	if (!File.is_open())
	{
		return;
	}

	std::string Json;
	std::string TempLine;
	while (std::getline(File, TempLine))
	{
		Json += TempLine;
	}

	rapidjson::Document Doc(rapidjson::kObjectType);
	Doc.Parse(Json.data());

	const bool bAccountInfo = Doc.HasMember("AccountInfo");
	_ASSERT(bAccountInfo);
	if (bAccountInfo)
	{
		rapidjson::Value& Array = Doc["AccountInfo"];
		_ASSERT(Array.IsArray());
		if (Array.IsArray())
		{
			const rapidjson::SizeType Size = Array.Size();
			for (rapidjson::SizeType i = 0; i < Size; ++i)
			{
				FAccount NewAccount;
				rapidjson::Value& AccountValue = Array[i];
				FAccountLoadEvent Load(NewAccount, AccountValue);
				FAccount* Account = CreateAccount(NewAccount);
				if (!Account)
				{
					// Log
					_ASSERT(false);
				}
			}
		}
	}
}
