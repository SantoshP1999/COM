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

class IMultiply :public IUnknown
{
public:
	// IMult specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;// pure virtual
};

class IDivision :public IUnknown
{
public:
	// IMult specific method declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;// pure virtual
};




// CLSID of SumSubtract Component // {85C61A82-46DE-442C-B877-353BA161C3BD}
const CLSID CLSID_SumSubtractMultiply ={ 0x85c61a82, 0x46de, 0x442c, 0xb8, 0x77, 0x35, 0x3b, 0xa1, 0x61, 0xc3, 0xbd };

// IID of ISum Interface  // {9E9FDC0B-63D9-4018-B28B-4D1F826E674A}
const IID IID_ISum = { 0x9e9fdc0b, 0x63d9, 0x4018, 0xb2, 0x8b, 0x4d, 0x1f, 0x82, 0x6e, 0x67, 0x4a };

// IID of ISubtract Interface   // {FF8BBE65-A5E2-4AE5-857D-95A2CAB45779}
const IID IID_ISubtract = { 0xff8bbe65, 0xa5e2, 0x4ae5, 0x85, 0x7d, 0x95, 0xa2, 0xca, 0xb4, 0x57, 0x79 };

// IID of IMultiplication Interface   // {394BE5C3-CB08-4B63-90D6-4AE7C52FB3A8}
const IID IID_IMultiplication = { 0x394be5c3, 0xcb08, 0x4b63, 0x90, 0xd6, 0x4a, 0xe7, 0xc5, 0x2f, 0xb3, 0xa8 };

// IID of IDivision Interface  // {01076C62-F5D3-4BB7-AD5C-B86528B9CE29}
const IID IID_IDivision = { 0x1076c62, 0xf5d3, 0x4bb7, 0xad, 0x5c, 0xb8, 0x65, 0x28, 0xb9, 0xce, 0x29 };


