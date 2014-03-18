// ---------------------------------------------------------------------------
// DaxFailClassImpl.h : Declaration of the TDaxFailClassImpl
// ---------------------------------------------------------------------------
#ifndef DaxFailClassImplH
#define DaxFailClassImplH

#include <ComServ.hpp>
#include <axbase.h>
#include "DaxFail_TLB.h"

// ---------------------------------------------------------------------------
// TDaxFailClassImpl     Implements IDaxFailClass, default interface of DaxFailClass
// ThreadingModel : tmApartment
// Dual Interface : TRUE
// Event Support  : FALSE
// Description    : Example of failure
// ---------------------------------------------------------------------------
class DAX_COM_CLASS TDaxFailClassImpl : public TCppAutoObject<IFoo, IBar>
{
  typedef _COM_CLASS inherited;

public:
  __fastcall TDaxFailClassImpl();
  __fastcall TDaxFailClassImpl(const System::_di_IInterface Controller);
  __fastcall TDaxFailClassImpl(Comobj::TComObjectFactory* Factory, const System::_di_IInterface Controller);
  

  // IDaxFailClass
protected:
  STDMETHOD(foo_method());
  STDMETHOD(bar_method());
};




#endif //DaxFailClassImplH
