#ifndef __PSW_DEBUGSTRING__
#define __PSW_DEBUGSTRING__

// John Robbins
inline BOOL AntiHackIsDebuggerPresent()
{
  BOOL bRet = TRUE;
  
  __asm
  {
    MOV EAX, FS:[00000018H]
    MOV EAX, DWORD PTR [EAX+030H]
    MOVZX EAX, BYTE PTR [EAX+002H]
    MOV bRet, EAX
  }
  
  return bRet;
}

#define LOG( a ) if( AntiHackIsDebuggerPresent() ) OutputDebugString(a); 

#endif
