// CPPCOMClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Objbase.h>

#import "../MyX64COMComponent.tlb" 

void InstantiateInProc()
{
    MyX64COMComponentLib::IMySampleCOMObjectPtr myComObj;

    HRESULT hr = CoCreateInstance(__uuidof(MyX64COMComponentLib::MySampleCOMObject), NULL, CLSCTX_ALL, __uuidof(MyX64COMComponentLib::IMySampleCOMObjectPtr), (void**)&myComObj);
    if (FAILED(hr))
    {
        std::cout << "unable to create COM object\n";
        return;
    }

    std::cout << "COM method returned:" << (char*)myComObj->GetProcessDetails() << std::endl;
}

void InstantiateOutProc()
{
    MyX64COMComponentLib::IMySampleCOMObjectPtr myComObj;
    
    WCHAR localhost[] = L"localhost";
    IID iid = __uuidof(MyX64COMComponentLib::IMySampleCOMObject);

    COSERVERINFO si = { 0 };
    si.pwszName = localhost;
    si.dwReserved1 = 0;
    si.pAuthInfo = NULL;
    si.dwReserved2 = 0;
    MULTI_QI mqi[1] = { 0 };
    mqi[0].pIID = &iid;
    mqi[0].pItf = NULL;
    mqi[0].hr = 0;
    HRESULT hr = CoCreateInstanceEx(__uuidof(MyX64COMComponentLib::MySampleCOMObject), NULL, CLSCTX_LOCAL_SERVER, &si, 1, mqi);
        
    if (FAILED(hr))
    {
        std::cout << "unable to create COM object\n";
        return;
    }

    myComObj.Attach((MyX64COMComponentLib::IMySampleCOMObject*)mqi[0].pItf);

    std::cout << "COM method returned:" << (char*)myComObj->GetProcessDetails() << std::endl;
}

int main()
{
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        std::cout << "unable to initialize COM\n";
        return 0;
    }
    
    InstantiateInProc();
    InstantiateOutProc();

    CoUninitialize();
    return 0;
}
