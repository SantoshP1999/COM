
#include<windows.h>

#include "Window.h"
#include "HeaderForClientOfComponentWithRegFile.h"

//Declaring Interface Pointers
ISum  *pISum = NULL;
ISubtract *pISubtract = NULL;
IMultiplication *pIMultiplication =NULL; 
IDivision *pIDivision = NULL;

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
	hwnd = CreateWindow(szClassName, TEXT("Client of COM Dll Server"),
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

	//function Declarations
	void SafeInterfaceRelease(void);



//variable declaration
	HRESULT hr = S_OK;
	int iNum1, iNum2, iSum,iSubtraction,iMultiplication,iDivision;
	TCHAR str[255];

	//code

	switch (iMsg)
	{

	case WM_CREATE:
	
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
			DestroyWindow(hwnd);
		}
		pISum->Release();
		pISum = NULL;

		iNum1 = 155;
		iNum2 = 145;

		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtraction);

		//pISubtract->Release();
		//pISubtract = NULL;

		wsprintf(str, TEXT("Subtraction Of %d And %d = %d"), iNum1, iNum2,iSubtraction); 
		MessageBox(hwnd, str, TEXT("Subtraction"), MB_OK);
		

		// call QueryInterface() on ISubtract,to get IMultiplication's pointer
		hr = pISubtract->QueryInterface(IID_IMultiplication, (void**)&pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication Interface Can Not Be Obtained"), TEXT("Error"),MB_OK);
			DestroyWindow(hwnd);
		}
		pISubtract->Release();
		pISubtract = NULL;

		iNum1 = 30;
		iNum2 = 25;

		// call MultiplicationOfTwoIntegers() of IMultiplication to get the Multiplication
		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMultiplication);

		wsprintf(str, TEXT("Multiplication Of %d And %d = %d"), iNum1, iNum2, iMultiplication);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// call QueryInterface() on IMultiplication's to get IDivision pointer
		hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision Interface Can Not Be Obtained"), TEXT("Error"),MB_OK);
			DestroyWindow(hwnd);
		}
		pIMultiplication->Release();
		pIMultiplication = NULL;

		iNum1 = 200;
		iNum2 = 25;

		// call DivisionOfTwoIntegers() of IDivision to get the Division
		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDivision);
		// display the result
		wsprintf(str, TEXT("Division Of %d And %d = %d"), iNum1, iNum2,iDivision); 
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		// finally release IDivision
		pIDivision->Release();
		pIDivision = NULL;

		DestroyWindow(hwnd);

		break;

	case WM_DESTROY:
		SafeInterfaceRelease();

		PostQuitMessage(0);
		break;

	//default:
		//break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}
void SafeInterfaceRelease(void)
{
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}
	if (pIMultiplication)
	{
		pIMultiplication->Release();
		pIMultiplication = NULL;
	}
	if (pIDivision)
	{
		pIDivision->Release();
		pIDivision = NULL;
	}
}
	


