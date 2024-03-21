#include "LoginSession.h"
#include "DataBase.h"

pair<FPlayer*, const char*> FLoginSession::Login(const FAccount& InAccount)
{
    FAccount* Account = GDataBase.CheckAccount(InAccount);
    if (!Account)
    {
        _ASSERT(false);
        return make_pair(nullptr, "[Login] 계정 정보를 확인할 수 없습니다.");
    }

    const bool bLogin = IsLogin(InAccount.ID);
    if (bLogin)
    {
        pair LogoutPair = Logout(InAccount);
        if (!LogoutPair.first)
        {
            _ASSERT(false);
            return make_pair(nullptr, LogoutPair.second);
        }
    }

    pair Pair = PlayerMap.emplace(InAccount.ID, InAccount.ID);
    FPlayer& Player = Pair.first->second;

    return make_pair(&Player, "[Login] 성공");
}

bool FLoginSession::IsLogin(const FAccountName& InAccountName)
{
    auto It = PlayerMap.find(InAccountName);
    if (It == PlayerMap.end())
    {
        return false;
    }

    return true;
}

pair<bool, const char*> FLoginSession::Logout(const FAccount& InAccount)
{
    FAccount* Account = GDataBase.CheckAccount(InAccount);
    if (!Account)
    {
        _ASSERT(false);
        return make_pair(false, "[Logout] 계정 정보를 확인할 수 없습니다.");
    }

    const bool bLogin = IsLogin(InAccount.ID);
    if (bLogin)
    {
        return make_pair(false, "[Logout] 해당 플레이어가 로그인 하지 않았습니다.");
    }

    PlayerMap.erase(InAccount.ID);

    return make_pair(true, "[Logout] 성공");
}

