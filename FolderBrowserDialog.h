#pragma once

#include <Windows.h>
#include <Shlobj.h>
#include <string>
using namespace std;


#pragma comment(lib, "Shell32.lib")

class FolderBrowserDialog
{
public:
	FolderBrowserDialog(void);

	int Flags;
	HWND Owner;
	wchar_t*SelectedPath;
	std::string Title;

	int ShowDialog();//OnCancel returns -1, OnNull returns 0, OnOK returns 1
	void convertWStringToCharPtr(_In_ std::wstring input, _Out_ char * outputString);
	static wstring s2ws(const std::string& s);
};