#include <windows.h>
#include"ContainmentInnerComponentWithRegFile.h"

//class Declarations
class CMultiplicationDivision :public IMultiplication, IDivision
{
private:
	long m_cRef;
public:
	//constructor method Declarations
	CMultiplicationDivision(void);

	//destructor method Declarations
	~CMultiplicationDivision(void);
	
	//IUnknown specific method Declarations(inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IMultiplication specific method declarations(inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	//IDivision specific method declarations(inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiplicationDivisionClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	//constructor method Declarations
	CMultiplicationDivisionClassFactory(void);

	//destructor method Declarations
	~CMultiplicationDivisionClassFactory(void);

	//IUnknown specific method Declarations(inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//global variable declarations
long glNumberOfActiveComponents = 0;	//number of active components
long glNumberOfServerLocks = 0;	//number of locks on this dll

//DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason) 
	{
	case DLL_PROCESS_ATTACH:

		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:

		break;
	}
	return(TRUE);
}

//Implementation of CMultiplicationDivision's Constructor method
CMultiplicationDivision::CMultiplicationDivision(void)
{
	m_cRef = 1;	// hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);	//Increment Global Counter
}

//Implementation of CMultiplicationDivision's Destructor method
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);	//Decrement Global Counter
}

//Implementation of CMultiplicationDivision's IUnknown methods
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CMultiplicationDivision::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CMultiplicationDivision::Release(void)
{
	InterlockedIncrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of IMultiplication's methods
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	*pMultiplication = num1 * num2;
	return(S_OK);
}

//Implementation of IDivision's methods
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
	*pDivision = num1 / num2;
	return(S_OK);
}

//Implementation of CMultiplicationDivisionClassFactory's constructor methoda
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	m_cRef = 1;	//hardcoded initialization to anticipate possible failure of QueryInterface

}

//Implementation of CMultiplicationDivisionClassFactory's Destructor methoda
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	// no code

}

// Implementation Of CMultiplicationDivisionClassFactory's IClassFactory's IUnknown's Methods
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}

	return (m_cRef);	
}

//Implementation of CMultiplicationDivisionClassFactory's IClassFactorys methods
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	//variable declarations
	CMultiplicationDivision  *pCMultiplicationDivision = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	//create the instance of component class 
	 pCMultiplicationDivision = new CMultiplicationDivision;

	if (pCMultiplicationDivision == NULL)
		return(E_OUTOFMEMORY);

	//get the requested interface
	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);

	hr=pCMultiplicationDivision->Release();	//anticipate possible failure of QueryInterface()
	return (hr);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return (S_OK);
}

//Implementation of Exported Functions From This Dll
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	//variable Declarations
	CMultiplicationDivisionClassFactory* pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MultiplicationDivision)
		return(CLASS_E_CLASSNOTAVAILABLE);

	//create class Factory
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;

	if (pCMultiplicationDivisionClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);

	//anticipate possible failures of QueryInterface()
	hr=pCMultiplicationDivisionClassFactory->Release();
	return(hr);

}

HRESULT __stdcall DllCanUnloadNow(void)
{
	if((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}

