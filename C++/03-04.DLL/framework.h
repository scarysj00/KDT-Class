#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

#ifdef MY_DLL
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif

void MYDLL_API fnMy0304DLL(int** InPointer);
void MYDLL_API fnMy0304DLLFree(int** InPointer);

struct /*MYDLL_API*/ FStruct
{
	FStruct();
};

class MYDLL_API FClass
{
public:
	void /*MYDLL_API*/ Test2();
	void /*MYDLL_API*/ Test3();

	int TTest = 0;

	inline /*MYDLL_API*/ static FStruct ISTest;
};