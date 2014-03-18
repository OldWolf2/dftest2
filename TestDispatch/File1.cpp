#include <vcl.h>
#include <windows.h>

#pragma hdrstop
#pragma argsused

#include <tchar.h>

#include <stdio.h>

const GUID CLSID_DaxFailClass = {0x9DCD1024, 0x6E1A, 0x435E,{ 0x82, 0xF9, 0xFD,0x4F, 0xE8, 0x63,0xD7, 0x10} };
const GUID IID_IFoo = {0x2CD15FFC, 0x0C09, 0x4A29,{ 0xBD, 0x57, 0x99,0xBB, 0xC5, 0x3A,0xE0, 0x1F} };
const GUID IID_IBar = {0xAECB5DF3, 0xEDE3, 0x441A,{ 0x93, 0xE6, 0x22,0x0C, 0xB2, 0x71,0xAD, 0x43} };

//
// Call a method on `intf`.
// Error 80020006 = no such name.
// Error 80020003 = the name is a property, not a method
// Error 80020005 = wrong arguments
//
void disp_call(char const *prompt, IDispatch *&intf, char const *method_name)
{
	BSTR name = WideString(method_name).Detach();
	DISPID dispid = 0;
	DISPPARAMS params = { 0 };
	HRESULT hr;

	hr = intf->GetIDsOfNames(IID_NULL, &name, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
	if ( hr )
		printf("%s->GetIDsOfNames(%s): %lX\n", prompt, method_name, (unsigned long)hr);
	else
	{
		hr = intf->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD,
													&params, NULL, NULL, NULL);
		printf("%s->Invoke(%s): %lX\n", prompt, method_name, (unsigned long)hr);
	}
	SysFreeString(name);
}

bool obj_create(char const *prompt, const GUID &clsid, IDispatch **p_intf)
{
	HRESULT hr = CoCreateInstance(clsid, 0, CLSCTX_ALL, IID_IDispatch, (void **)p_intf);
	if ( hr )
		printf("%s: failed to create, %lX\n", prompt, hr);
	else
		printf("%s created.\n", prompt);

	return !hr;
}

bool query_interface(char const *from, char const *to, IDispatch *disp, const GUID &iid, IDispatch **p_intf)
{
	HRESULT	hr = disp->QueryInterface(iid, (void **)p_intf);
	if ( !hr )
		return true;

	printf("%s failed to support %s: %lX\n", from, to, (unsigned long)hr);
	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	IDispatch *pDispDefault;
	HRESULT hr;

	CoInitialize(NULL);

	if ( obj_create("DaxFail", CLSID_DaxFailClass, &pDispDefault) )
	{
		disp_call("(default)", pDispDefault, "foo_method");

		IDispatch *pDispBar;

		if ( query_interface("(default)", "IBar", pDispDefault, IID_IBar, &pDispBar) )
		{
			disp_call("Bar (should work)", pDispBar, "bar_method");
			disp_call("Bar (should fail)", pDispBar, "foo_method");
			pDispBar->Release();
		}

		pDispDefault->Release();
	}

	CoUninitialize();

	getchar();
	return 0;
}
