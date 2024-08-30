
#include<windows.h>

#include "Window.h"
#include "ClassFactoryDllServerWithRegFile.h"

//Declaring Interface Pointers
ISum  *pISum = NULL;
ISubtract *pISubtract = NULL;

IUnknown* pIUnknownFromISum = NULL;
IUnknown* pIUnknownFromISubtract = NULL;


//Global callback function prototype
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine,
	int iCmdShow)
{
	//Variable declarations
	WNDCLASSEX wndclass;
	TCHAR szClassName[] = TEXT("MyFirstWindow");
	HWND hwnd;
	MSG msg;
	HRESULT hr = S_OK;
	//int iNum1, iNum2, sum,sum;

	//Code


	//Initialising COM
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library can not be Initialized.\nProgram Will Now Exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}


	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(SBP_ICON));
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(SBP_ICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;

	//Register Window Class
	RegisterClassEx(&wndclass);

	//Create the Window
	hwnd = CreateWindow(szClassName, TEXT("Santosh Phatangare:First Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

		//Show The Window
	ShowWindow(hwnd, iCmdShow);

	//Update the Window
	UpdateWindow(hwnd);

	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	// Uninitializing COM
	CoUninitialize();
	return((int)msg.wParam);
}

//Callback Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
//Code
	//function Prototype
	void SafeInterfaceRelease(void);

//variable declaration
	HRESULT hr = S_OK;
	int iNum1, iNum2, iSum;
	TCHAR str[255];

	switch (iMsg)
	{

	case WM_CREATE:
/*
// refer to CoCreate instance Pseudo code
		HRESULT __stdcall CoCreateInstance(REFCLSID rclsid, IUnknown * pUnkOuter, DWORD dwClsContext, REFIID riid, void** ppv)
		{
			// Variable Declarations
			HRESULT hr;
			IClassFactory* pIClassFactory = NULL;

			//code

			hr = CoGetClassObject(rclsid, dwClsContext, NULL, IID_IClasssFactory, (void**)&pIClassFactory);

			if (SUCCEEDED(hr))
			{
				pIClassFactory->CreateInstance(pUnkOuter, riid, ppv);
				pIClassFactory->Release();
			}
			return(hr);}
*/
	


		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum Interface can not be Obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		iNum1 = 55;
		iNum2 = 45;

		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Sum Of %d And %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Sum"), MB_OK);
		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract Interface Can Not Be Obtained"), TEXT("Error"),MB_OK);
			pISum->Release();
			pISum = NULL;

			
			DestroyWindow(hwnd);
		}
		
		iNum1 = 155;
		iNum2 = 145;

		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSum);

		wsprintf(str, TEXT("Subtraction Of %d And %d = %d"), iNum1, iNum2,iSum); 
		MessageBox(hwnd, str, TEXT("Subtraction"), MB_OK);


		// Checking for Identity property of query interface

		hr = pISum->QueryInterface(IID_IUnknown, (void**)&pIUnknownFromISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IUnknown Can Not Be Obtained from ISum"), TEXT("Error"), MB_OK);
			
			
			DestroyWindow(hwnd);
		}

		hr = pISubtract->QueryInterface(IID_IUnknown, (void**)&pIUnknownFromISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IUnknown Can Not Be Obtained from ISubtract"), TEXT("Error"), MB_OK);
			
			DestroyWindow(hwnd);
		}
		
		if (pIUnknownFromISum == pIUnknownFromISubtract)
		{
			MessageBox(NULL, TEXT("Identity of query iterface is true"), TEXT("Error"), MB_OK);
		}

		else 
		{
			MessageBox(NULL, TEXT("Identity of query iterface is not true"), TEXT("Error"), MB_OK);
		}


		
		

		DestroyWindow(hwnd);

		break;

	case WM_DESTROY:
		SafeInterfaceRelease();

		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}

void SafeInterfaceRelease(void)
{
	//code
	
	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}

	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}

	if (pIUnknownFromISubtract)
	
		{
		pIUnknownFromISubtract->Release();
		pIUnknownFromISubtract = NULL;
		}

	if (pIUnknownFromISum)
	{
		pIUnknownFromISum->Release();
		pIUnknownFromISum = NULL;
	}

}