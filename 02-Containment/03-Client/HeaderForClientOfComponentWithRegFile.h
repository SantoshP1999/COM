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
class IMultiplication : public IUnknown
{
public:
	//IMultiplication specific method declarations pure virtual
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;		//pure Virtual function

};

class IDivision :public IUnknown
{
public:
	//IDivision specific method Declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;	//pure Virtual function

};
//CLSID of SumSubtract Component {F27A01E8-0558-41F7-9745-8B9998E417A1}
const CLSID CLSID_SumSubtract = { 0xf27a01e8, 0x558, 0x41f7, 0x97, 0x45, 0x8b, 0x99, 0x98, 0xe4, 0x17, 0xa1 };


//IID of ISum Interface {319952CC-3B65-49D5-A2A7-C9E81C30CA5F}
const IID IID_ISum = { 0x319952cc, 0x3b65, 0x49d5, 0xa2, 0xa7, 0xc9, 0xe8, 0x1c, 0x30, 0xca, 0x5f };



//IID of ISubtract Interface  {184F51A6-B34F-413F-B3B6-B1AFC89C32F3}
const IID IID_ISubtract = { 0x184f51a6, 0xb34f, 0x413f, 0xb3, 0xb6, 0xb1, 0xaf, 0xc8, 0x9c, 0x32, 0xf3 };


//CLSID of MultiplicationDivision Component {3D6BF9AC-8AB0-4E5E-96C4-D1251FCC5E17}
const CLSID CLSID_MultiplicationDivision = { 0x3d6bf9ac, 0x8ab0, 0x4e5e, 0x96, 0xc4, 0xd1, 0x25, 0x1f, 0xcc, 0x5e, 0x17 };


//IID of IMultiplication Interface  {C49C2090-CFF8-4B69-9A09-A4C77ACC8ED4}
const IID IID_IMultiplication = { 0xc49c2090, 0xcff8, 0x4b69, 0x9a, 0x9, 0xa4, 0xc7, 0x7a, 0xcc, 0x8e, 0xd4 };


//IID of IDivision Interface  {9005260C-D739-4A31-8895-042A1691611B}
const IID IID_IDivision = { 0x9005260c, 0xd739, 0x4a31, 0x88, 0x95, 0x4, 0x2a, 0x16, 0x91, 0x61, 0x1b };

