#pragma once

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

//CLSID of MultiplicationDivision Component {3D6BF9AC-8AB0-4E5E-96C4-D1251FCC5E17}
const CLSID CLSID_MultiplicationDivision = { 0x3d6bf9ac, 0x8ab0, 0x4e5e, 0x96, 0xc4, 0xd1, 0x25, 0x1f, 0xcc, 0x5e, 0x17 };


//IID of IMultiplication Interface  {C49C2090-CFF8-4B69-9A09-A4C77ACC8ED4}
const IID IID_IMultiplication = { 0xc49c2090, 0xcff8, 0x4b69, 0x9a, 0x9, 0xa4, 0xc7, 0x7a, 0xcc, 0x8e, 0xd4 };


//IID of IDivision Interface  {9005260C-D739-4A31-8895-042A1691611B}
const IID IID_IDivision = { 0x9005260c, 0xd739, 0x4a31, 0x88, 0x95, 0x4, 0x2a, 0x16, 0x91, 0x61, 0x1b };

