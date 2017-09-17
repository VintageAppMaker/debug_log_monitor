/*
    제목:   디버그 메시지 모니터링
    작성자: 박성완(adsloader@naver.com)
    작성일: 2012.05.18
    목적  : 로그필터 프로그램 예제
*/


#include "stdafx.h"
#include "debugfilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 응용 프로그램 개체입니다.

CWinApp theApp;

using namespace std;

static void Log(TCHAR* sMsg)
{
    SYSTEMTIME LocalTime;  
    GetLocalTime(&LocalTime);  
  
    TCHAR szDate[1024];
    ZeroMemory(szDate, 1024);

    _stprintf_s(szDate, 1024, L"[%04d-%02d-%02d %02d:%02d:%02d]",   
                LocalTime.wYear, LocalTime.wMonth, 
                LocalTime.wDay, LocalTime.wHour, 
                LocalTime.wMinute, LocalTime.wSecond);  

	wprintf(L"%s %s\n", szDate, sMsg);
	
}

static int DebugFilter(TCHAR* EXENAME)
{
	STARTUPINFO			sInfo;
	PROCESS_INFORMATION pInfo;
	DEBUG_EVENT			dEvent;
	
	ZeroMemory((VOID*)&sInfo, sizeof(sInfo));
	BOOL b = CreateProcess(EXENAME, 0, 0, 0, FALSE, DEBUG_ONLY_THIS_PROCESS, 0, 0, &sInfo, &pInfo);
	if(!b) return FALSE;
	
	
	while(1)
	{
		if( !(b = WaitForDebugEvent(&dEvent, INFINITE)) ){ 
			Log(L"debuging faltal error");
			return -1;
		}

		CString s;
				
		switch(dEvent.dwDebugEventCode){
			case CREATE_PROCESS_DEBUG_EVENT:
				Log(L">>>>>>>>>>>>Process 시작");
				break;

            case EXIT_PROCESS_DEBUG_EVENT:
				Log(L">>>>>>>>>>>>Process 종료");
				return 0;

			case CREATE_THREAD_DEBUG_EVENT:
				s.Format(L"___Thread 생성:%d___", dEvent.dwThreadId);
				Log(s.GetBuffer());
				s.ReleaseBuffer();

				break;

			case EXIT_THREAD_DEBUG_EVENT:
				s.Format(L"___Thread 종료:%d___", dEvent.dwThreadId);
				Log(s.GetBuffer());
				s.ReleaseBuffer();

				break;

			case OUTPUT_DEBUG_STRING_EVENT:
				CString strEventMessage;
			    OUTPUT_DEBUG_STRING_INFO & DebugString = dEvent.u.DebugString;
		
			    WCHAR *msg=new WCHAR[DebugString.nDebugStringLength];			
			    ZeroMemory(msg, DebugString.nDebugStringLength);

			    ReadProcessMemory(pInfo.hProcess, DebugString.lpDebugStringData, msg, DebugString.nDebugStringLength, NULL);

				if ( DebugString.fUnicode ){
				    strEventMessage = msg;
				}else{
				    strEventMessage = (LPSTR)msg;
				}

			    delete []msg;

				Log(strEventMessage.GetBuffer(0));
				strEventMessage.ReleaseBuffer();

				break;
		}

		ContinueDebugEvent( dEvent.dwProcessId, dEvent.dwThreadId, DBG_CONTINUE);
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	// console에서 한글 찍으려면 반드시 ..
	setlocale ( LC_ALL, "" );   

	int nRetCode = 0;
	
	// MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0)){
		return 1;
	}
	
	if( argc < 2 ){
		cout << "파일명을 입력하세요. ex) debugfilter a.exe\n";
		return 0;
	}

	DebugFilter(argv[1]);

	return nRetCode;
}
