#pragma once

class ISum :public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;// pure virtual
};
class ISubtract :public IUnknown
{
public:
	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;// pure virtual
};

// CLSID of SumSubtract Component {799D37AF-D51D-4408-B124-292076D5F8AA}
const CLSID CLSID_SumSubtract ={0x799d37af, 0xd51d, 0x4408, 0xb1, 0x24, 0x29, 0x20, 0x76, 0xd5, 0xf8, 0xaa};


// IID of ISum Interface  {C9AFDC98-15DD-49BA-A49D-7C9D8965D310}
const IID IID_ISum = { 0xc9afdc98, 0x15dd, 0x49ba, 0xa4, 0x9d, 0x7c, 0x9d, 0x89, 0x65, 0xd3, 0x10 };

// IID of ISubtract Interface   {8EAF8E60-FE75-4F35-98AA-5E14A863B482}
const IID IID_ISubtract = { 0x8eaf8e60, 0xfe75, 0x4f35, 0x98, 0xaa, 0x5e, 0x14, 0xa8, 0x63, 0xb4, 0x82 };

