// 03.LibraryUser.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "../03-01.StaticLibrary1/framework.h"
#include "../03-02.StaticLibrary/framework.h"
#include "../03-03.StaticLibrary/framework.h"
#include "../03-04.DLL/framework.h"
#include "03.LibraryUser.h"



// [Windows 기준]
// lib, dll
// - Windows에서 사용이 가능하다.
// - 리눅스(안드로이드)도 라이브러리가 있다. a(lib), so(dll)
// - 둘 다 코드 집합이다.
// - 내가 만든 코드를 다른 사람이 사용 가능하게 하고 싶다.
//      - cpp(구현) 코드는 공개하고 싶지 않은 경우 라이브러리를 만들어서 배포
//        (h는 공개; h파일들과 .lib파일 또는 .dll파일을 배포)
//      - 관리의 단위로(모듈화를 위해) 라이브러리로 구분하고, 코드를 까는 경우도 있다

// [lib, dll 차이]
// - lib는 빌드 타임에 exe에 통합된다
// - dll은 실행 시간에 exe에 로드된다

// 다른 사람이 만들어 둔 코드를 사용하는 방법
// [소스코드가 있는 경우]
// - (Ex. ini parser) 프로젝트에 code를 그대로 가져온다 (ThirdParty 폴더 등으로 분류해서 구분)
// - [StaticLibrary(.lib), DynamicLibrary(.dll)] 다른사람이 만들어 둔 프로젝트를 솔루션에 포함해서 참조
//    -> 라이브러리를 참조할 프로젝트에 우클릭 -> 추가 -> 참조 -> 원하는 라이브러리 프로젝트 선택

// [소스코드가 없는 경우]
// - [StaticLibrary] 이미 만들어 둔 lib를 빌드 시점에 링크해서 빌드 (lib파일과 Header파일만 공개된 상황, cpp(구현)는 볼 수 없다
// - 내 빌드 시스템과 호환이 안될 수 있다. (Ex. Visual studio 구버전으로 빌드 된 라이브러리의 경우 신버전에 사용할 수 없다. 아마 VS2015~ 이후로는 호환이 되도록 바뀜)
// - 런타임 라이브러리 설정이 일치해야 한다(프로젝트 속성 -> C++ -> 코드 생성 -> 런타임 라이브러리(MT, MD))
//      - 런타임 라이브러리 : 표준 함수들 (vector 등 포함)
//      - MT: 런타임 라이브러리를 lib로 취급해서 빌드 타임에 링크하겠다
//          - 단점 : exe 크기가 늘어난다
//          - 장점 : 만들 때 있던 라이브러리를 가져다 쓰기 때문에 항상 일관성 있는 동작을 보장
//      - MD: 런타임 라이브러리를 dll로 취급해서 런타임에 로드하겠다
//      - 내 프로젝트(라이브러리를 가져다 쓰는 쪽) 설정과 라이브러리 배포자가 지정해 둔 설정이 일치해야 한다

// 참조가 아닌 방식으로 정적 라이브러리 포함하는 방법 (03-02.StaticLibrary)
// 1. 프로젝트 속성에 추가                       (아래 내용은 03.LibraryUser에 포함)
//  - 프로젝트 속성 -> 링커 -> 일반 -> 추가 라이브러리 디렉토리
//      - 라이브러리 경로를 추가한다
//  - 프로젝트 속성 -> 링커 -> 입력 -> 추가 종속성
//      - 라이브러리 이름을 추가한다
// 2. 소스코드에 #pragma comment로 추가
//    - 프로젝트 속성 -> 링커 -> 일반 -> 추가 라이브러리 디렉토리
#pragma comment(lib, "03-03.StaticLibrary.lib")
// static library(A)일 경우 해당 라이브러리에서 다른 라이브러리(B)를 참조하고 있는 경우
// 해당 라이브러리를 사용하는 exe 또는 dll에서 A와 B 라이브러리 모두 포함해야 빌드가 된다.
// dll이 동일한 상황이라면, exe에서 해당 dll만 포함하면 된다. (dll이 참조하는 라이브러리를 포함할 필요가 없다)
//
// - [DynamicLibrary]
//  - lib는 우리가 만든 프로그램을 배포할 때 포함하지 않아야 하지만, dll의 경우 dll 파일도 같이 배포해야 한다
//      - dll은 dll만 수정해서 교체하면 수정된 버전으로 코드가 동작한다.
//      - lib가 수정이 발생 했을때는 exe를 교체해야 수정된 버전으로 동작한다.
//      - dll을 가져다 쓴ㄴ 구조를 잘 짜두면 exe가 실행되고 있는 시점에 dll을 교체할 수 있다. (Ex. 언리얼:라이브 코딩)
//        - exe가 켜지고, 패치서버에 접속해서 dll만 교체 가능한 경우 새로운 dll을 받아와서 패치 가능
//           - 그렇지만 보통은 별도의 런처 프로그램을 두고 패치를 하는 경우가 대부분
// - 런타임 라이브러리 설정이 불일치해도 된다.
// - DLL이 MD인 경우 내가 만든 환경에서는 문제가 없었는데, 배포를 했을 때 거기서 사용하는 프로그램이 MT여서(또는 그 반대)
//      - 메모리를 dll 함수를 통해서 할당하는 경우 할당한 dll에서 해제를 해야 문제가 없다. 그렇지않으면 crash

// - 언리얼은 에디터의 경우 
//  - 각 모듈별로 별도로 dll로 빌드가 됩니다.(우리가 언리얼에서 작성할 모듈도 에디터에서는 dll로 빌드가 되서)
//      - 에디터라는 프로그램이 우리의 dll을 로드하는 구조
//  - 패키징의 과정을 거쳐서 배포용으로 만드는 경우 (기존에 dll로 있던 녀석이)lib로 취급되어서 빌드가 되는 특징이 있다

// dll 포함하는 방법
// 0. 라이브러리를 참조할 프로젝트에 우클릭 -> 추가 -> 참조 -> 원하는 라이브러리 프로젝트 선택
// 1. 프로젝트 속성에 추가 (03-04.DLL)
//  - 프로젝트 속성 -> 링커 -> 일반 -> 추가 라이브러리 디렉토리
//      - 라이브러리 경로를 추가한다
//  - 프로젝트 속성 -> 링커 -> 입력 -> 추가 종속성
//      - 라이브러리 이름을 추가한다
// 2. 소스코드에 #pragma comment로 추가
//    - 프로젝트 속성 -> 링커 -> 일반 -> 추가 라이브러리 디렉토리


int main()
{
    std::cout << "Hello World!\n";
    fnMy0301StaticLibrary1();
    fnMy0302StaticLibrary();
    fnMy0303StaticLibrary();

    // DLL의 경우 MT, MD가 다른 경우 메모리 할당
    // 해제에서 문제가 발생할 수 있다
    int* Pointer = nullptr;
    fnMy0304DLL(&Pointer);
    // delete Pointer;
    fnMy0304DLLFree(&Pointer);

    FClass Instance;
    Instance.Test2();
    Instance.Test3();
    Instance.TTest = 100;

    // @TODO: 동적 로드
    HINSTANCE hDLLInstance = LoadLibrary(L"03-05.DLLLoad.dll");
    if (!hDLLInstance)
    {
        return 0;
    }

    using MYPROC = void(*)(int**);

    MYPROC fnMy0305DLL =  (MYPROC)GetProcAddress(hDLLInstance, "fnMy0305DLL");
    MYPROC fnMy0305DLLFree = (MYPROC)GetProcAddress(hDLLInstance, "fnMy0305DLLFree");

    int* Test = nullptr;
    fnMy0305DLL(&Test);
    fnMy0305DLLFree(&Test);

    FreeLibrary(hDLLInstance);
}

