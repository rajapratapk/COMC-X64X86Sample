// dllmain.h : Declaration of module class.

class CMyX64COMComponentModule : public ATL::CAtlDllModuleT< CMyX64COMComponentModule >
{
public :
	DECLARE_LIBID(LIBID_MyX64COMComponentLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MYX64COMCOMPONENT, "{3e61ce9c-6515-4ee8-8942-c373fecafec0}")
};

extern class CMyX64COMComponentModule _AtlModule;
