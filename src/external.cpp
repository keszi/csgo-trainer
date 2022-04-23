#include "external.h"

DWORD folyamatAzonositoSzerzes(const wchar_t* folyamatNev)
{
	DWORD folyamatAzonosito = 0;
	HANDLE pillanatnyiFolyamatok = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (pillanatnyiFolyamatok != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 folyamatBelepes;
		folyamatBelepes.dwSize = sizeof(folyamatBelepes);

		if (Process32First(pillanatnyiFolyamatok, &folyamatBelepes))
		{
			do
			{
				if (!_wcsicmp(folyamatBelepes.szExeFile, folyamatNev))
				{
					folyamatAzonosito = folyamatBelepes.th32ProcessID;
					break;
				}

			} while (Process32Next(pillanatnyiFolyamatok, &folyamatBelepes));
		}
	}
	CloseHandle(pillanatnyiFolyamatok);
	return folyamatAzonosito;
}

uintptr_t modulKezdoCimSzerzes(DWORD folyamatAzonosito, const wchar_t* modulNev)
{
	uintptr_t modulKezdoCim = { 0 };
	HANDLE pillanatnyiFolyamatok = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, folyamatAzonosito);

	if (pillanatnyiFolyamatok != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modulBelepes;
		modulBelepes.dwSize = sizeof(modulBelepes);

		if (Module32First(pillanatnyiFolyamatok, &modulBelepes))
		{
			do 
			{
				if (!_wcsicmp(modulBelepes.szModule, modulNev))
				{
					modulKezdoCim = (uintptr_t)modulBelepes.modBaseAddr;
					break;
				}

			} while (Module32Next(pillanatnyiFolyamatok, &modulBelepes));
		}
	}
	CloseHandle(pillanatnyiFolyamatok);
	return modulKezdoCim;
}