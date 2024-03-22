#pragma once
#include "MISC/Headers.h"
#include "Account.h"

// 전방 선언 : 이런 class가 있다.
// Pointer나 Reference
// class FPlayer;

// FAccount의 컨테이너
class FDataBase final
{
	friend struct FLoginTask;
	friend class FLoginSession;

public:
	// 회원 가입
	FAccount* CreateAccount(const FAccount& InAccount);

	// 회원 검색(ID만 넣어서 찾아옴)
	// ID로 계정 정보를 찾아온다
	// 찾지 못한경우 nullptr을 반환한다
	FAccount* FindAccount(const FAccountName& InID);

	// 회원 가입 여부 검사(ID, Password가 일치해야함)
	FAccount* CheckAccount(const FAccount& InAccount);

	// 회원 탈퇴
	bool DeleteAccount(const FAccount& InAccount);

	const unordered_map<FAccountName, FAccount>& GetAccountMap() const { return AccountMap; }

public:
	// 정말로 DB에 값을 써야하는 상황이라면
	// 중요한 요청(회원가입과 같은 상황에는 즉시 DB에 값을 써야 하지만
	// 저희는 시뮬레이터기 때문에 프로그램이 켜질때 디스크에서 불러오고
	// 꺼질때 디스크에 저장 하도록 하겠습니다)
	FDataBase();
	~FDataBase();

private:
	void SaveAccount();
	void LoadAccount();

	bool SavePlayer(class FPlayer& InPlayer);
	bool LoadPlayer(const FAccountName& InAccountName, class FPlayer& OutPlayer);

private:
	unordered_map<FAccountName, FAccount> AccountMap;
};

// extern: 어딘가에 있어
extern FDataBase GDataBase;
// inline FDataBase GDataBase2; // dll에서 문제 가능성이 있음