/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

// proxydll.cpp
#include "stdafx.h"
#include "proxydll.h"
#include "myIDirect3D9.h"
#include "myIDirect3DDevice9.h"

HINSTANCE           gl_hOriginalDll;
HINSTANCE           gl_hThisInstance;

void WINAPI D3DPERF_SetOptions( DWORD dwOptions )
{
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right d3d9.dll"

	// Hooking IDirect3D Object from Original Library
	typedef void (WINAPI* D3D9_Type)(DWORD dwOptions);
	D3D9_Type D3DPERF_SetOptions_fn = (D3D9_Type) GetProcAddress(
		gl_hOriginalDll, "D3DPERF_SetOptions");

	// Debug
	if (!D3DPERF_SetOptions_fn)
	{
		MessageBoxA(0,"not found :(","0",0);
	}
	return (D3DPERF_SetOptions_fn (dwOptions));
}

// Exported function (faking d3d9.dll's one-and-only export)
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right d3d9.dll"

	// Hooking IDirect3D Object from Original Library
	typedef IDirect3D9 *(WINAPI* D3D9_Type)(UINT SDKVersion);
	D3D9_Type D3DCreate9_fn = (D3D9_Type) GetProcAddress( gl_hOriginalDll, "Direct3DCreate9");

    // Debug
	if (!D3DCreate9_fn)
    {
        OutputDebugString("PROXYDLL: Pointer to original D3DCreate9 function not received ERROR ****\r\n");
        ::ExitProcess(0); // exit the hard way
    }

	// Request pointer from Original Dll.
	IDirect3D9 *pIDirect3D9_orig = D3DCreate9_fn(SDKVersion);

	// Create my IDirect3D8 object and store pointer to original object there.
	// note: the object will delete itself once Ref count is zero (similar to COM objects)
	myIDirect3D9::instance = new myIDirect3D9(pIDirect3D9_orig);

	// Return pointer to hooking Object instead of "real one"
	return (myIDirect3D9::instance );
}

void InitInstance(HANDLE hModule)
{
	OutputDebugString("PROXYDLL: InitInstance called.\r\n");

	// Initialisation
	gl_hOriginalDll        = NULL;
	gl_hThisInstance       = NULL;

	// Storing Instance handle into global var
	gl_hThisInstance = (HINSTANCE)  hModule;
}

void LoadOriginalDll(void)
{
    char buffer[MAX_PATH];

    // Getting path to system dir and to d3d8.dll
	::GetSystemDirectory(buffer,MAX_PATH);

	// Append dll name
	strcat(buffer,"\\d3d9.dll");

	// try to load the system's d3d9.dll, if pointer empty
	if (!gl_hOriginalDll) gl_hOriginalDll = ::LoadLibrary(buffer);

	// Debug
	if (!gl_hOriginalDll)
	{
		OutputDebugString("PROXYDLL: Original d3d9.dll not loaded ERROR ****\r\n");
		::ExitProcess(0); // exit the hard way
	}
}

void ExitInstance()
{
    OutputDebugString("PROXYDLL: ExitInstance called.\r\n");

	// Release the system's d3d9.dll
	if (gl_hOriginalDll)
	{
		::FreeLibrary(gl_hOriginalDll);
	    gl_hOriginalDll = NULL;
	}
}