// testapp.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "testapp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "DEBSTRING.h"


// 유일한 응용 프로그램 개체입니다.

CWinApp theApp;

using namespace std;

UINT ThreadFunc(LPVOID lpParam)
{
	return 0L;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
    setlocale ( LC_ALL, "" );   

	// MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		_tprintf(_T("심각한 오류: MFC를 초기화하지 못했습니다.\n"));
		return  1;
	}

    LOG(L"\tOutputDebugString 출력");
	LOG(L"\tdebug mode로 실행되었을 경우만 출력됨");
	LOG(L"\t의심되면 debugview로 채크해보세요.");


	for(int i = 0; i < 5; i++)
		AfxBeginThread(ThreadFunc, &i);

    Sleep(1000 * 2);
    
	return 0;
}
