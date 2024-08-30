#define UNICODE
#include<windows.h>
#include"QIPropDllServer.h"

// class declarations
class CSumSubtractMultiply :public ISum, ISubtract,IMultiply,IDivision
{
private:
	long m_cRef;
public:
	// constructor method declarations  
	CSumSubtractMultiply(void);
	// destructor method declarations
	~CSumSubtractMultiply(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	// ISubtract specific method declarations (inherited) 
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
	// IMultiplication specific method declarations (inherited) 
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
	// IDivision specific method declarations (inherited) 
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CSumSubtractMultiplyClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	// constructor method declarations
	CSumSubtractMultiplyClassFactory(void);
	// destructor method declarations
	~CSumSubtractMultiplyClassFactory(void);
	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**); 
	HRESULT __stdcall LockServer(BOOL);
};
// global variable declarations
long glNumberOfActiveComponents = 0; // number of active components
long glNumberOfServerLocks = 0; // number of locks on this dll
// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}
// Implementation Of CSumSubtract's Constructor Method
CSumSubtractMultiply::CSumSubtractMultiply(void)
{
	// hardcoded initialization to anticipate possible failure of QueryInterface()
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);// increment global counter
}
// Implementation Of CSumSubtract's Destructor Method
CSumSubtractMultiply::~CSumSubtractMultiply(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);// decrement global counter
}
// Implementation Of CSumSubtract's IUnknown's Methods
HRESULT CSumSubtractMultiply::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiply*>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSumSubtractMultiply::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtractMultiply::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
// Implementation Of ISum's Methods
HRESULT CSumSubtractMultiply::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	*pSum = num1 + num2;
	return(S_OK);
}
// Implementation Of ISubtract's Methods
HRESULT CSumSubtractMultiply::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	*pSubtract = num1 - num2;
	return(S_OK);
}

// Implementation Of IMultiplication's Methods
HRESULT CSumSubtractMultiply::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiply)
{
	*pMultiply = num1 * num2;
	return(S_OK);
}

// Implementation Of IDivision's Methods
HRESULT CSumSubtractMultiply::DivisionOfTwoIntegers(int num1, int num2, int* pDivision)
{
	*pDivision = num1 / num2;
	return(S_OK);
}
// Implementation Of CSumSubtractClassFactory's Constructor Method
CSumSubtractMultiplyClassFactory::CSumSubtractMultiplyClassFactory(void)
{
	m_cRef = 1;// hardcoded initialization to anticipate possible failure of QueryInterface()
}
// Implementation Of CSumSubtractClassFactory's Destructor Method
CSumSubtractMultiplyClassFactory::~CSumSubtractMultiplyClassFactory(void)
{
	// no code
}
// Implementation Of CSumSubtractClassFactory's IClassFactory's IUnknown's Methods
HRESULT CSumSubtractMultiplyClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this); 
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSumSubtractMultiplyClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtractMultiplyClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
// Implementation Of CSumSubtractClassFactory's IClassFactory's Methods
HRESULT CSumSubtractMultiplyClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// variable declarations
	CSumSubtractMultiply* pCSumSubtractMultiply =NULL; 
	HRESULT hr;
	// code
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	// create the instance of component i.e. of CSumSubtract
	pCSumSubtractMultiply = new CSumSubtractMultiply;
	if (pCSumSubtractMultiply == NULL)
		return(E_OUTOFMEMORY);
	// get the requested interface
	hr = pCSumSubtractMultiply->QueryInterface(riid, ppv);
	pCSumSubtractMultiply->Release();// anticipate possible failure of QueryInterface()
	return(hr);
}
HRESULT CSumSubtractMultiplyClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}
// Implementation Of Exported Functions From This Dll
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// variable declaraions
	CSumSubtractMultiplyClassFactory* pCSumSubtractMultiplyClassFactory = NULL;
	HRESULT hr;
	// code
	if (rclsid != CLSID_SumSubtractMultiply)
		return(CLASS_E_CLASSNOTAVAILABLE);
	// create class factory
	pCSumSubtractMultiplyClassFactory = new CSumSubtractMultiplyClassFactory;
	if
		(pCSumSubtractMultiplyClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCSumSubtractMultiplyClassFactory->QueryInterface(riid, ppv); pCSumSubtractMultiplyClassFactory->Release();
	// anticipate possible failure of QueryInterface()
	return(hr);
}
	HRESULT __stdcall DllCanUnloadNow(void)
	{
		if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
			return(S_OK);
		else
			return(S_FALSE);
	}