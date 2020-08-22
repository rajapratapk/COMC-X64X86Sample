// MySampleCOMObject.h : Declaration of the CMySampleCOMObject

#pragma once
#include "resource.h"       // main symbols



#include "MyX64COMComponent_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CMySampleCOMObject

class ATL_NO_VTABLE CMySampleCOMObject :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMySampleCOMObject, &CLSID_MySampleCOMObject>,
	public IDispatchImpl<IMySampleCOMObject, &IID_IMySampleCOMObject, &LIBID_MyX64COMComponentLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMySampleCOMObject()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CMySampleCOMObject)
	COM_INTERFACE_ENTRY(IMySampleCOMObject)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(GetProcessDetails)(BSTR* details);
};

OBJECT_ENTRY_AUTO(__uuidof(MySampleCOMObject), CMySampleCOMObject)
