
#include <vcl.h>
#pragma hdrstop
#include <ComServ.hpp>
#include <axbase.h>

#include "DaxFailClassImpl.h"
#pragma package(smart_init)
#pragma link "System.Win.ComServ"



// -----------------------------------------------------------------------------
// Entry point of your Server invoked by Windows for processes or threads are
// initialized or terminated.
//
// -----------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
	return TRUE;
}


// -----------------------------------------------------------------------------
// Entry point of your Server invoked to inquire whether the DLL is no
// longer in use and should be unloaded.
// -----------------------------------------------------------------------------
STDAPI __export DllCanUnloadNow(void)
{
    Comserv::TComServer* comserver = Comserv::GetComServer();
    return (!comserver ||
            ((comserver->ObjectCount /* + comserver->FactoryCount */) == 0)) ?
            S_OK : S_FALSE;
}

// -----------------------------------------------------------------------------
// Entry point of your Server allowing OLE to retrieve a class object from
// your Server
// -----------------------------------------------------------------------------
STDAPI __export DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    Comobj::TComObjectFactory* Factory = Comobj::ComClassManager()->GetFactoryFromClassID(rclsid);
    if (Factory)
    {
      if (Factory->GetInterface(riid, ppv))
        return S_OK;
      else
        return E_NOINTERFACE;
    }
    else
    {
      *ppv = 0;
      return CLASS_E_CLASSNOTAVAILABLE;
    }
}

// -----------------------------------------------------------------------------
// Entry point of your Server invoked to instruct the server to create
// registry entries for all classes supported by the module
// -----------------------------------------------------------------------------
STDAPI __export DllRegisterServer(void)
{
    Comserv::TComServer* comserver = Comserv::GetComServer();
    if (comserver)
    {
        try
        {
            comserver->LoadTypeLib();
            comserver->UpdateRegistry(true);
            return S_OK;
        }
        catch(...)
        {
            return E_FAIL;
        }
    }
    else
    {
        return E_FAIL;
    }
}

// -----------------------------------------------------------------------------
// Entry point of your Server invoked to instruct the server to remove
// all registry entries created through DllRegisterServer.
// -----------------------------------------------------------------------------
STDAPI __export DllUnregisterServer(void)
{
    Comserv::TComServer* comserver = Comserv::GetComServer();
    if (comserver)
    {
        try
        {
            comserver->LoadTypeLib();
            comserver->UpdateRegistry(false);
            return S_OK;
        }
        catch(...)
        {
            return E_FAIL;
        }
    }
    else
    {
        return E_FAIL;
    }
}

// ------------------------------------------------------------------------------
// Entry point of your Server installation/setup. Used for 'PerUser' registration
// Invoked via call to "regsvr32 /n /i:user [/u] axlibrary.dll"
// ------------------------------------------------------------------------------
STDAPI __export DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
    Comserv::TComServer* comserver = Comserv::GetComServer();
    if (comserver)
    {
        bool savePerUser = comserver->PerUserRegistration;
        if (pszCmdLine && !Sysutils::StrIComp(pszCmdLine, L"user"))
            comserver->PerUserRegistration = true;
        else
            comserver->PerUserRegistration = false;
        HRESULT result = E_FAIL;
        if (bInstall)
        {
            result = DllRegisterServer();
            if (result == E_FAIL)
                DllUnregisterServer();
        }
        else
            result = DllUnregisterServer();
        comserver->PerUserRegistration = savePerUser;
        return result;
    }
    else
    {
        return E_FAIL;
    }
}



