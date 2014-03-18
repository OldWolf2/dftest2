// ---------------------------------------------------------------------------
// DAXFAILCLASSIMPL : Implementation of TDaxFailClassImpl (CoClass: DaxFailClass, Interface: IDaxFailClass)
// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DaxFailClassImpl.h"


// ---------------------------------------------------------------------------
// TDaxFailClassImpl
// ---------------------------------------------------------------------------
__fastcall TDaxFailClassImpl::TDaxFailClassImpl()
{
}


// ---------------------------------------------------------------------------
// TDaxFailClassImpl
// ---------------------------------------------------------------------------
__fastcall TDaxFailClassImpl::TDaxFailClassImpl(const System::_di_IInterface Controller)
                              : inherited(Controller)
{
}


// ---------------------------------------------------------------------------
// TDaxFailClassImpl
// ---------------------------------------------------------------------------
__fastcall TDaxFailClassImpl::TDaxFailClassImpl(Comobj::TComObjectFactory* Factory,
                                      const System::_di_IInterface Controller)
                              : inherited(Factory, Controller)
{
}

// ---------------------------------------------------------------------------
// TDaxFailClassImpl - Class Factory
// ---------------------------------------------------------------------------
static void createFactory()
{
  new TCppAutoObjectFactory<TDaxFailClassImpl>(Comserv::GetComServer(),
                           __classid(TDaxFailClassImpl),
                           CLSID_DaxFailClass,
                           Comobj::ciMultiInstance,
                           Comobj::tmApartment);
}
#pragma startup createFactory 32


STDMETHODIMP TDaxFailClassImpl::foo_method()
{
  try
  {
	MessageBoxA(NULL, "foo_method", "DaxFail", MB_OK);
  }
  catch(Exception &e)
  {
	return Error(e.Message.c_str(), IID_IFoo);
  }
  return S_OK;
}


STDMETHODIMP TDaxFailClassImpl::bar_method()
{
  try
  {
	MessageBoxA(NULL, "baz_method", "DaxFail", MB_OK);
  }
  catch(Exception &e)
  {
    return Error(e.Message.c_str(), IID_IBar);
  }
  return S_OK;
}



