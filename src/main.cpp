#include "external.h"

int main() 
{
	const wchar_t jatekNeve[] = { L"csgo.exe" };
	const wchar_t modulNeve[] = { L"server.dll" };
	size_t helyiJatekosOffset{ 0xA8E28C };
	size_t eletOffset{ 0x230 };

	DWORD folyamatAzonosito = folyamatAzonositoSzerzes(jatekNeve);

	uintptr_t modulCim = modulKezdoCimSzerzes(folyamatAzonosito, modulNeve);

	HANDLE folyamatCsatlakozas = OpenProcess(PROCESS_ALL_ACCESS, NULL, folyamatAzonosito);

	uintptr_t helyiJatekos{ modulCim + helyiJatekosOffset };
	BYTE* helyiJatekosCim;

	ReadProcessMemory(folyamatCsatlakozas, (BYTE*)helyiJatekos, &helyiJatekosCim, sizeof(helyiJatekos), nullptr);

	BYTE* eletCim{ helyiJatekosCim + eletOffset };
	
	short eredetiElet;
	static short modositottElet{ 500 };

	bool csalasEngedelyezve{ false };

	cout << "Program betoltve.\n"
		<< "Nyomd meg az [F1] 500 eletert!\n"
		<< "Nyomd meg az [END] a kilepeshez!\n";

	DWORD kilepesKod(0);

	while (GetExitCodeProcess(folyamatCsatlakozas, &kilepesKod) && kilepesKod == STILL_ACTIVE)
	{

		if (GetAsyncKeyState(VK_F1) & 1)
		{
			//csalasEngedelyezve = !csalasEngedelyezve;
			WriteProcessMemory(folyamatCsatlakozas, eletCim, &modositottElet, sizeof(eredetiElet), nullptr);
		}
		if(GetAsyncKeyState(VK_END))
		{
			break;
		}
	}
	cout << "kileptel a csalasbol!" << endl;
	return 0;
}
