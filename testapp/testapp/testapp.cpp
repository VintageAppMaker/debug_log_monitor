// testapp.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "testapp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "DEBSTRING.h"


// ������ ���� ���α׷� ��ü�Դϴ�.

CWinApp theApp;

using namespace std;

UINT ThreadFunc(LPVOID lpParam)
{
	return 0L;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
    setlocale ( LC_ALL, "" );   

	// MFC�� �ʱ�ȭ�մϴ�. �ʱ�ȭ���� ���� ��� ������ �μ��մϴ�.
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		_tprintf(_T("�ɰ��� ����: MFC�� �ʱ�ȭ���� ���߽��ϴ�.\n"));
		return  1;
	}

    LOG(L"\tOutputDebugString ���");
	LOG(L"\tdebug mode�� ����Ǿ��� ��츸 ��µ�");
	LOG(L"\t�ǽɵǸ� debugview�� äũ�غ�����.");


	for(int i = 0; i < 5; i++)
		AfxBeginThread(ThreadFunc, &i);

    Sleep(1000 * 2);
    
	return 0;
}
