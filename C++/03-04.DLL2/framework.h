#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <iostream>

#ifdef MY_DLLLOAD
#define MYDLLLOAD_API __declspec(dllexport)
#else
#define MYDLLLOAD_API __declspec(dllimport)
#endif

//http://en.wikipedia.org/wiki/Name_mangling
//맹글링을 하지 않겠다
extern "C"
{
	extern "C" void  MYDLLLOAD_API fnMy0305DLL(int** InPointer);
	void  MYDLLLOAD_API fnMy0305DLLFree(int** InPointer);
}

