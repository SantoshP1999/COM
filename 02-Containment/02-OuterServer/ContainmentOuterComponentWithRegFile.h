#pragma once

class ISum : public IUnknown
{
public:
	//IMultiplication specific method declarations pure virtual
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;		//pure Virtual function

};

class ISubtract :public IUnknown
{
public:
	//IDivision specific method Declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;	//pure Virtual function

};

//CLSID of SumSubtract Component {F27A01E8-0558-41F7-9745-8B9998E417A1}
const CLSID CLSID_SumSubtract = { 0xf27a01e8, 0x558, 0x41f7, 0x97, 0x45, 0x8b, 0x99, 0x98, 0xe4, 0x17, 0xa1 };


//IID of ISum Interface {319952CC-3B65-49D5-A2A7-C9E81C30CA5F}
const IID IID_ISum = { 0x319952cc, 0x3b65, 0x49d5, 0xa2, 0xa7, 0xc9, 0xe8, 0x1c, 0x30, 0xca, 0x5f };



//IID of ISubtract Interface  {184F51A6-B34F-413F-B3B6-B1AFC89C32F3}
const IID IID_ISubtract = { 0x184f51a6, 0xb34f, 0x413f, 0xb3, 0xb6, 0xb1, 0xaf, 0xc8, 0x9c, 0x32, 0xf3 };


