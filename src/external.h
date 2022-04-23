#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

DWORD folyamatAzonositoSzerzes(const wchar_t* folyamatNev);

uintptr_t modulKezdoCimSzerzes(DWORD folyamatAzonosito, const wchar_t* modulNev);