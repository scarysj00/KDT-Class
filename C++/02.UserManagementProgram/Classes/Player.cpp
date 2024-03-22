#include "Player.h"

bool FPlayerSaveLoader::Save()
{
	if (Player.Name.empty()) 
	{ 
		_ASSERT(false);
		return false;
	}

	rapidjson::Document Doc(rapidjson::kObjectType);
	rapidjson::Document::AllocatorType& Allocator = Doc.GetAllocator();

	rapidjson::Value PlayerValue(rapidjson::kObjectType);
	PlayerValue.AddMember("Name", rapidjson::StringRef(Player.Name.data()), Allocator);
	PlayerValue.AddMember("Level", Player.Level,Allocator);

	Doc.AddMember("Player Info", PlayerValue, Allocator);

	rapidjson::StringBuffer Buffer;
	rapidjson::Writer<rapidjson::StringBuffer > Writer(Buffer);
	Doc.Accept(Writer);
	string Json(Buffer.GetString(), Buffer.GetSize());

	// make directory :폴더 만들어라
	system("mkdir PlayerInfo");
	string FilePath = "PlayerInfo/" + Player.Name + ".json";
	std::ofstream File(FilePath);
	File << Json;

	return true;
}

bool FPlayerSaveLoader::Load(const FAccountName& InAccountName)
{
	if (InAccountName.empty())
	{
		_ASSERT(false);
		return false;
	}

	const string FilePath = "PlayerInfo/" + InAccountName + ".json";
	ifstream File(FilePath);
	if (!File.is_open())
	{
		return false;
	}

	string Json;
	{
		string Temp;
		while (getline(File, Temp)) { Json += Temp; }
		if (Json.empty()) { return false; }
	}

	rapidjson::Document Doc(rapidjson::kObjectType);
	Doc.Parse(Json.data());

	const bool bPlayerInfo = Doc.HasMember("PlayerInfo");
	if (!bPlayerInfo)
	{
		_ASSERT(false);
		return false;
	}

	rapidjson::Value& PlayerInfo = Doc["PlayerInfo"];
	if (PlayerInfo.HasMember("Name"))
	{
		Player.Name = PlayerInfo["Name"].GetString();
	}
	if (PlayerInfo.HasMember("Level"))
	{
		Player.Level = PlayerInfo["Level"].GetInt();
	}

	return true;

}
