#include "FolderBrowserDialog.h"

FolderBrowserDialog::FolderBrowserDialog(void)
{
	this->Flags = BIF_USENEWUI;
	this->Owner = 0;
	this->Title = "";
}

int FolderBrowserDialog::ShowDialog(void)
{
	BROWSEINFOW bi;
	memset(&bi, 0, sizeof(bi));

	bi.hwndOwner = this->Owner;
	bi.lpszTitle = s2ws(this->Title).c_str();
	bi.ulFlags = this->Flags;

	OleInitialize(NULL);

	LPITEMIDLIST pIDL = SHBrowseForFolderW(&bi);

	if (pIDL == NULL)
	{
		return -1;
	}

	//TCHAR *buffer = new TCHAR[MAX_PATH];
	LPWSTR buffer = new wchar_t[MAX_PATH];
	if (!SHGetPathFromIDListW(pIDL, buffer) != 0)
	{
		CoTaskMemFree(pIDL);
		return 0;
	}
	
	this->SelectedPath = buffer;

	CoTaskMemFree(pIDL);
	OleUninitialize();
	return 1;
}

void FolderBrowserDialog::convertWStringToCharPtr(std::wstring input, char * outputString)
{
	size_t outputSize = input.length() + 1; // +1 for null terminator
	outputString = new char[outputSize];
	size_t charsConverted = 0;
	const wchar_t * inputW = input.c_str();
	wcstombs_s(&charsConverted, outputString, outputSize, inputW, input.length());
}

std::wstring FolderBrowserDialog::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}