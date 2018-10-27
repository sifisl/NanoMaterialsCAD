#pragma once

#include <Windows.h>


bool extractResource(const HINSTANCE hInstance, WORD resourceID, LPCTSTR szFilename)
{
	bool bSuccess = false;
	try
	{
		// Find and load the resource
		HRSRC hResource = FindResource(hInstance, MAKEINTRESOURCE(resourceID), L"DLL");
		HGLOBAL hFileResource = LoadResource(hInstance, hResource);

		// Open and map this to a disk file
		LPVOID lpFile = LockResource(hFileResource);
		DWORD dwSize = SizeofResource(hInstance, hResource);

		// Open the file and filemap
		HANDLE hFile = CreateFile(szFilename, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, dwSize, NULL);
		LPVOID lpAddress = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);

		// Write the file
		CopyMemory(lpAddress, lpFile, dwSize);

		// Un-map the file and close the handles
		UnmapViewOfFile(lpAddress);
		CloseHandle(hFileMap);
		CloseHandle(hFile);
		bSuccess = true;
	}
	catch (...)
	{
		// Whatever
	}
	return bSuccess;
}