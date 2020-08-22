// MySampleCOMObject.cpp : Implementation of CMySampleCOMObject

#include "pch.h"
#include "MySampleCOMObject.h"
#include <sstream>
// CMySampleCOMObject

bool Is_64bit(void)
{
#if defined(_WIN64)
    return true;  // 64-bit programs run only on Win64
#elif defined(_WIN32)
    BOOL f64 = FALSE;
    return IsWow64Process(GetCurrentProcess(), &f64) && f64;
#endif
}


STDMETHODIMP CMySampleCOMObject::GetProcessDetails(BSTR* details)
{    
    if (!details)
        return E_POINTER;

    
    DWORD processId = ::GetCurrentProcessId();
    
    //retrieve the process name
    CHandle processHandle(OpenProcess(
        PROCESS_QUERY_LIMITED_INFORMATION,
        FALSE,
        processId /* This is the PID, you can find one from windows task manager */
    ));

    DWORD buffSize = 1024;
    TCHAR processName[1024] = { 0 };

    if (processHandle.m_h != NULL)
    {
        if (!QueryFullProcessImageName(processHandle.m_h, 0, processName, &buffSize))        
        {
            printf("Error GetModuleBaseNameA : %lu", GetLastError());
            return E_FAIL;
        }        
    }
    else
    {
        printf("Error OpenProcess : %lu", GetLastError());
        return E_FAIL;
    }
       

    std::wstringstream ss;
    ss << L"{\"processId\":\"" << processId << L"\", \"processName\":\"" << processName << "\", \"isX64\":\"" << Is_64bit()<<"\"}";

    *details = SysAllocString(ss.str().c_str());

    return S_OK;
}
