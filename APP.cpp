// APP.cpp : Defines the entry point for the console application.
// By:少先队员
// QQ:89387263

#include "stdafx.h"
#undef UNICODE
#include <windows.h>
#include <iostream>
#include <tlhelp32.h>
using namespace std;

BYTE COLOR_ADD [14] = { 0x06, 0x00, 0x00, 0x00, 0x44, 0x69, 0x72, 0x65, 0x63, 0x74, 0x58, 0x20, 0x39, 0x00 },
SKY_ADD [12] = { 0x63, 0x6B, 0x61, 0x67, 0x65, 0x00, 0x00, 0x00, 0x00, 0x5F, 0x5F, 0x6D },
ALL_ADD [40] = { 0xB3, 0xF5, 0xCA, 0xBC, 0xBB, 0xAF, 0xCD, 0xEA, 0xB3, 0xC9, 0x20, 0x20, 0x40, 0xC9, 0xD9, 0xCF, 0xC8, 0xB6, 0xD3, 0xD4, 0xB1, 0x20, 0x3D, 0x3E, 0X20, 0x51, 0x51, 0xA3, 0xBA, 0x38, 0x39, 0x33, 0x38, 0x37, 0x32, 0x36, 0x33 },
WALL_ADD [32] = { 0x24, 0x8B, 0x47, 0x04, 0x89, 0x44, 0x8A, 0x28, 0x8B, 0x4D, 0x28, 0x8B, 0x95, 0x34, 0xFE, 0xFF, 0xFF, 0x89, 0x55, 0x0C, 0xF3, 0x0F, 0x10, 0x41, 0x20, 0x0F, 0x2E, 0xC1, 0x9F, 0xF6, 0xC4, 0x44 },
FLY_ADD [47] = { 0xF3, 0x0F, 0x10, 0x03, 0xF3, 0x0F, 0x58, 0xCA, 0xF3, 0x0F, 0x59, 0xE0, 0xF3, 0x0F, 0x59, 0xD8, 0xF3, 0x0F, 0x59, 0xC8, 0xF3, 0x0F, 0x11, 0x18, 0xF3, 0x0F, 0x11, 0x60, 0x04, 0xF3, 0x0F, 0x11, 0x48, 0x08, 0x8B, 0x73, 0x0C, 0x8B, 0x86, 0x50, 0x01, 0x00, 0x00, 0x83, 0x78, 0x4C, 0x01 },
CHARACTER_ADD [21] = { 0x00, 0x00, 0x7A, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00, 0x1C },
OVEROLL_ADD [15] = { 0x69, 0x63, 0x73, 0x00, 0x00, 0x00, 0x00, 0x5F, 0x5F, 0x6B, 0x77, 0x64, 0x65, 0x66, 0x61 };
INT pid;
DWORD COLOR_BASE, SKY_BASE, WALL_BASE, FLY_BASE, CHARACTER_BASE, OVEROLL_BASE;
BOOL COLOR_CHANGE = FALSE, SKY_CHANGE = FALSE, WALL_CHANGE = FALSE, FLY_CHANGE = FALSE, CHARACTER_CHANGE = FALSE, OVEROLL_CHANGE = FALSE, DOG_CHANGE = FALSE;

INT GetPid(CHAR *PwName){
	HANDLE hwnd;
	PROCESSENTRY32 pro;
	pro.dwSize = sizeof (PROCESSENTRY32); 
	BOOL flag;
	hwnd = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0);
	if (hwnd == 0){
		return 0;
	}
	flag = Process32First (hwnd, &pro);
	while (flag){
		if (strcmp (PwName, pro.szExeFile) == 0){
				CloseHandle (hwnd);
				return pro.th32ProcessID;
		}else{
			flag = Process32Next (hwnd, &pro);
		}
	}
	CloseHandle (hwnd);
	return 0;
}

INT GetModuleBaseAddress(DWORD dwPID,CHAR *lpModulName){
	HANDLE hModuleSnap;
	MODULEENTRY32 modul;
	hModuleSnap = CreateToolhelp32Snapshot (TH32CS_SNAPMODULE, dwPID);
	if (hModuleSnap == INVALID_HANDLE_VALUE){
		return (-1);
	}
	modul.dwSize = sizeof (MODULEENTRY32);
	if (!Module32First (hModuleSnap, &modul)){
		CloseHandle (hModuleSnap);
		return (-1);
	}
	do{
		if (strcmp (lpModulName, modul.szModule) == 0){
			CloseHandle (hModuleSnap);
			return ((DWORD) modul.modBaseAddr);
		}
	}while (Module32Next (hModuleSnap, &modul));
	CloseHandle (hModuleSnap);
	return(-1);
}

BOOL WriteNumProcessMemory(int npid,int lpBaseAddress,float lpBuffer){
	HANDLE hWnd = NULL;
	hWnd = OpenProcess (2035711, 0, npid);
	BOOL a = WriteProcessMemory (hWnd, (PVOID)lpBaseAddress, &lpBuffer, 4, 0);
	CloseHandle (hWnd);
	return a;
}

BOOL WriteIntProcessMemory(int npid,int lpBaseAddress,int lpBuffer){
	HANDLE hWnd = NULL;
	hWnd = OpenProcess (2035711, 0, npid);
	BOOL a = WriteProcessMemory (hWnd, (PVOID)lpBaseAddress, &lpBuffer, 4, 0);
	CloseHandle (hWnd);
	return a;
}

BOOL WriteDoubleProcessMemory(int npid,int lpBaseAddress,double lpBuffer){
	HANDLE hWnd = NULL;
	hWnd = OpenProcess (2035711, 0, npid);
	BOOL a = WriteProcessMemory (hWnd, (PVOID)lpBaseAddress, &lpBuffer, sizeof(lpBuffer), 0);
	CloseHandle (hWnd);
	return a;
}

VOID Ini(){
	BYTE TMP1 [35] = { 0x4D, 0x69, 0x63, 0x72, 0x6F, 0x73, 0x6F, 0x66, 0x74, 0x20, 0x57, 0x69, 0x6E, 0x64, 0x6F, 0x77, 0x73, 0x20, 0x5B, 0xB0, 0xE6, 0xB1, 0xBE, 0x20, 0x36, 0x2E, 0x31, 0x2E, 0x37, 0x36, 0x30, 0x31, 0x5D },
		TMP2 [57] = { 0xB0, 0xE6, 0xC8, 0xA8, 0xCB, 0xF9, 0xD3, 0xD0, 0x20, 0x28, 0x63, 0x29, 0x20, 0x32, 0x30, 0x30, 0x39, 0x20, 0x4D, 0x69, 0x63, 0x72, 0x6F, 0x73, 0x6F, 0x66, 0x74, 0x20, 0x43, 0x6F, 0x72, 0x70, 0x6F, 0x72, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0xA1, 0xA3, 0xB1, 0xA3, 0xC1, 0xF4, 0xCB, 0xF9, 0xD3, 0xD0, 0xC8, 0xA8, 0xC0, 0xFB, 0xA1, 0xA3 },
		TMP3 [24] = { 0x43, 0x3A, 0x5C, 0x55, 0x73, 0x65, 0x72, 0x5C, 0x41, 0x64, 0x6D, 0x69, 0x6E, 0x69, 0x73, 0x74, 0x72, 0x61, 0x74, 0x6F, 0x72, 0x3E };
	printf("%s\n%s\n\n%s", TMP1, TMP2, TMP3);
}

VOID Ver(){
	cout << "\n\n  ALT+Q  =========> 穿墙\n  ALT+W  =========> 低倍加速\n  ALT+E  =========> 狗皮加速（趴地使用）\n  ALT+R  =========> 飞天踏空\n    V    =========> 极速下机\n    +    =========> 开启部分常用功能（穿墙、人物变红、全图调暗）\n    -    =========> 关闭所有功能\n" << endl;
}

BOOL WriteByteProcessMemory(int npid,int lpBaseAddress,byte *lpBuffer){
	HANDLE hWnd = NULL;
	hWnd = OpenProcess (2035711, 0, npid);
	BOOL a = WriteProcessMemory (hWnd, (PVOID)lpBaseAddress, lpBuffer, 8, 0);
	CloseHandle (hWnd);
	return a;
}

CHAR *to16(DWORD poi,int addr,char addre[]){
	unsigned int ui = addr;
	ui = (ui>>24)|((ui&0xff0000)>>8)|((ui&0xff00)<<8)|(ui<<24);
	sprintf_s (addre, 32 , "%08X%08X%s", poi, ui, "");
	//VC6编译失败替换这条即可
	//sprintf (addre, "%08X%08X%s", poi, ui, "");
	return addre;
}

DWORD ReadProcess(int npid,int lpBaseAddress){
	DWORD lpBuffer;
	HANDLE hWnd = NULL;
	DWORD bools;
	hWnd = OpenProcess (2035711, 0, npid);
	bools = ReadProcessMemory (hWnd, (LPCVOID)lpBaseAddress, &lpBuffer, 4, 0);
	CloseHandle (hWnd);
	return lpBuffer;
}

BYTE *tobyte(char s[],char bits[]){
	int i,n=0;
	for(i =0;s[i];i += 2){
		if(s[i] >= 'A' && s[i] <= 'F')
			bits[n] = s[i] - 'A' + 10;
		else bits[n] = s[i] - '0';
		if(s[i + 1] >= 'A' && s[i + 1] <= 'F')
			bits[n] = (bits[n] << 4) | (s[i + 1] - 'A' + 10);
		else bits[n] = (bits[n] << 4) | (s[i + 1] - '0');
		++n;
	}
	return (byte *)bits;
}

INT AddressDy(int npid,BYTE *code, int codelen, int upcode, int startadd ) {
	int stopadd = startadd + 0x1F87FFE;
	HANDLE hWnd = NULL;
	hWnd = OpenProcess (2035711, 0, npid);
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	int currentBaseAddress = startadd;
	int stopaddress = stopadd;
	int j;
	MEMORY_BASIC_INFORMATION mbInfo = { 0 };
	ZeroMemory(&mbInfo, sizeof(mbInfo));
	SIZE_T BaseInfoLen = sizeof(mbInfo);
	BYTE *lpBuf = new BYTE[1];
	DWORD dwBufSize = 1;
	int ret_p = 0;
	while (VirtualQueryEx(hWnd, (LPVOID)currentBaseAddress, &mbInfo, BaseInfoLen) && (currentBaseAddress<stopaddress) && ((int)(currentBaseAddress + mbInfo.RegionSize)>currentBaseAddress)) {
		if (mbInfo.Type != MEM_MAPPED && mbInfo.Type != MEM_PRIVATE  && mbInfo.Protect != PAGE_NOACCESS && mbInfo.Protect != PAGE_GUARD) {
			delete[] lpBuf;
			if ((int)mbInfo.BaseAddress < startadd) {
				mbInfo.RegionSize = mbInfo.RegionSize - (startadd - (int)mbInfo.BaseAddress);
			}
			if (((int)mbInfo.BaseAddress + (int)mbInfo.RegionSize) > stopadd) {
				mbInfo.RegionSize = stopadd - (int)mbInfo.BaseAddress;
			}
			dwBufSize = mbInfo.RegionSize;
			lpBuf = new BYTE[dwBufSize];
			if (ReadProcessMemory(hWnd, (LPCVOID)currentBaseAddress, lpBuf, dwBufSize, 0)) {
				for (j = 0; j <= ((int)mbInfo.RegionSize - codelen); j++) {
					for (int k = 0; k < codelen; k++) {
						if (lpBuf[j + k] != code[k]) {
							goto s;
						}
					}
					ret_p = (currentBaseAddress + j);
					goto retn;
				s:;
				}
			}
		}
		currentBaseAddress = (int)mbInfo.BaseAddress + mbInfo.RegionSize;
	}
retn:;
	delete[] lpBuf;
	CloseHandle (hWnd);
	return ret_p + upcode;
}

INT AddressStatic(int dycode, int maincode){
	return dycode-maincode;
}

CHAR* choi(DWORD six){
	if(six){
		return "开启";
	}
	return "关闭";
}

BOOL CHRACTERtoRED(){
	DWORD a1 = ReadProcess (pid, COLOR_BASE) + 172;
	DWORD a2 = ReadProcess (pid, a1) + 224;
	DWORD a3 = ReadProcess (pid, a2) + 12;
	DWORD a4 = ReadProcess (pid, a3) + 4;
	DWORD a5 = ReadProcess (pid, a4) + 224;
	DWORD map = a5 -0x8;
	if(COLOR_CHANGE == false){
		WriteIntProcessMemory (pid, map , 1056964608);
		WriteIntProcessMemory (pid, a5 , 1134985216);
		COLOR_CHANGE = true;
	}else{
		WriteIntProcessMemory (pid, map , 1067030938);
		WriteIntProcessMemory (pid, a5 , 1065353216);
		COLOR_CHANGE = false;
	}
	return COLOR_CHANGE;
}

BOOL SKYtoBLACK(){
	if(SKY_CHANGE == false){
		WriteNumProcessMemory (pid, SKY_BASE , 0);
		SKY_CHANGE = true;
	}else{
		WriteNumProcessMemory (pid, SKY_BASE , 24);
		SKY_CHANGE = false;
	}
	return SKY_CHANGE;
}

BOOL CHARACTERtoWALL(){
	if(WALL_CHANGE == false){
		WriteIntProcessMemory (pid, WALL_BASE , 1289097062);
		WALL_CHANGE = true;
	}else{
		WriteIntProcessMemory (pid, WALL_BASE , 1154879334);
		WALL_CHANGE = false;
	}
	return WALL_CHANGE;
}

BOOL CHARACTERtoFLY(){
	if(FLY_CHANGE == false){
		WriteIntProcessMemory (pid, FLY_BASE, 5011587);
		FLY_CHANGE = true;
	}else{
		WriteIntProcessMemory (pid, FLY_BASE, 21788803);
		FLY_CHANGE = false;
	}
	return FLY_CHANGE;
}

BOOL SPEEDto2(){
	if(CHARACTER_CHANGE == false){
		if(OVEROLL_CHANGE){
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 12);
			WriteDoubleProcessMemory (pid, OVEROLL_BASE, 1000);
			OVEROLL_CHANGE = false;
			cout << "系统输出 =========> （冲突）极速下机自动关闭" << endl;
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 7);
		}
		if(DOG_CHANGE){
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 12);
			DOG_CHANGE = false;
			cout << "系统输出 =========> （冲突）狗皮加速自动关闭" << endl;
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 7);
		}
		WriteNumProcessMemory (pid, CHARACTER_BASE, 2000);
		CHARACTER_CHANGE = true;
	}else{
		WriteNumProcessMemory (pid, CHARACTER_BASE, 1000);
		CHARACTER_CHANGE = false;
	}
	return CHARACTER_CHANGE;
}

BOOL ALLto7(){
	if(OVEROLL_CHANGE == false){
		if(DOG_CHANGE || CHARACTER_CHANGE){
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 12);
			WriteNumProcessMemory (pid, CHARACTER_BASE, 1000);
			if(DOG_CHANGE){
				cout << "系统输出 =========> （冲突）狗皮加速自动关闭" << endl;
			}
			if(CHARACTER_CHANGE){
				cout << "系统输出 =========> （冲突）低倍加速自动关闭" << endl;
			}
			DOG_CHANGE = CHARACTER_CHANGE = false;
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 7);
		}
		WriteDoubleProcessMemory (pid, OVEROLL_BASE, 300);
		OVEROLL_CHANGE = true;
	}else{
		WriteDoubleProcessMemory (pid, OVEROLL_BASE, 1000);
		OVEROLL_CHANGE = false;
	}
	return OVEROLL_CHANGE;
}

BOOL SPEEDto7(){
	if(DOG_CHANGE == false){
		if(OVEROLL_CHANGE){
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 12);
			WriteDoubleProcessMemory (pid, OVEROLL_BASE, 1000);
			OVEROLL_CHANGE = false;
			cout << "系统输出 =========> （冲突）极速下机自动关闭" << endl;
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 7);
		}
		if(CHARACTER_CHANGE){
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 12);
			CHARACTER_CHANGE = false;
			cout << "系统输出 =========> （冲突）低倍加速自动关闭" << endl;
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 7);
		}
		WriteNumProcessMemory (pid, CHARACTER_BASE, 7500);
		DOG_CHANGE = true;
	}else{
		WriteNumProcessMemory (pid, CHARACTER_BASE, 1000);
		DOG_CHANGE = false;
	}
	return DOG_CHANGE;
}

VOID MoudleIni(){
	char bits[32];
	char addre[64];
	DWORD maincode = GetModuleBaseAddress (pid, "hyxd.exe");
	//天空变黑防封;
	DWORD FLY_BAN = maincode + 0x64F573;
	DWORD FLY_BAN_TMP = maincode + 0x64F2F9;
	WriteNumProcessMemory (pid, FLY_BAN_TMP, 24);
	WriteByteProcessMemory (pid, FLY_BAN, tobyte (to16 (0xF30F590D, FLY_BAN_TMP, addre), bits));
	//人物加速防封;
	DWORD SPEED_BAN_TMP = maincode + 0xB8A8C4;
	DWORD SPEED_BAN_1 = maincode + 0xB8A8A0;
	DWORD SPEED_BAN_2 = maincode + 0x64F63F;
	DWORD SPEED_BAN_3 = maincode + 0x71C3EF;
	DWORD SPEED_BAN_4 = maincode + 0x3D2A5D;
	WriteNumProcessMemory (pid, SPEED_BAN_TMP, 1000);
	WriteByteProcessMemory (pid, SPEED_BAN_1, tobyte (to16 (0xF30F5905, SPEED_BAN_TMP, addre), bits));
	WriteByteProcessMemory (pid, SPEED_BAN_2, tobyte (to16 (0xF30F5905, SPEED_BAN_TMP, addre), bits));
	WriteByteProcessMemory (pid, SPEED_BAN_3, tobyte (to16 (0xF30F1005, SPEED_BAN_TMP, addre), bits));
	WriteByteProcessMemory (pid, SPEED_BAN_4, tobyte (to16 (0xF30F1005, SPEED_BAN_TMP, addre), bits));
	//全局加速防封;
	DWORD ALL_BAN_TMP = maincode + 0x4532A3;
	DWORD ALL_BAN = maincode + 0x45325B;
	WriteDoubleProcessMemory (pid, ALL_BAN_TMP, 1000);
	WriteByteProcessMemory (pid, ALL_BAN, tobyte (to16 (0xF20F5905, ALL_BAN_TMP, addre), bits));

	cout <<endl <<endl << "内存读取中..." <<endl <<endl;
	DWORD COLOR_BASE_ADD = AddressStatic (AddressDy (pid, (BYTE *)COLOR_ADD, sizeof(COLOR_ADD), -0x198, maincode), maincode);
	printf("系统输出 =========> color：    %08X\n",COLOR_BASE_ADD);
	DWORD SKY_BASE_ADD = AddressStatic (AddressDy (pid, (BYTE *)SKY_ADD, sizeof(SKY_ADD), 0x2CD, maincode), maincode);
	printf("系统输出 =========> sky：      %08X\n",SKY_BASE_ADD);
	DWORD WALL_BASE_ADD = AddressStatic (AddressDy (pid, (BYTE *)WALL_ADD, sizeof(WALL_ADD), -0x9, maincode), maincode);
	printf("系统输出 =========> wall：     %08X\n",WALL_BASE_ADD);
	DWORD FLY_BASE_ADD = AddressStatic (AddressDy (pid, (BYTE *)FLY_ADD, sizeof(FLY_ADD), 0x2B, maincode), maincode);
	printf("系统输出 =========> fly：      %08X\n",FLY_BASE_ADD);
	DWORD CHARACTER_BASE_ADD = AddressStatic (AddressDy (pid, (BYTE *)CHARACTER_ADD, sizeof(CHARACTER_ADD), 0x0, maincode), maincode);
	printf("系统输出 =========> character：%08X\n",CHARACTER_BASE_ADD);
	DWORD OVEROLL_BASE_ADD = AddressStatic (AddressDy (pid, (BYTE *)OVEROLL_ADD, sizeof(OVEROLL_ADD), -0x4D9, maincode), maincode);
	printf("系统输出 =========> overall：  %08X\n",OVEROLL_BASE_ADD);
	if(COLOR_BASE_ADD <=0 || SKY_BASE_ADD <=0 || WALL_BASE_ADD <=0 || FLY_BASE_ADD <=0 || CHARACTER_BASE_ADD <=0 || OVEROLL_BASE_ADD <=0){
		cout<< endl << "内存读取失败" <<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
		cout<< endl << "初始化失败" <<endl <<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		system ("pause");
		return;
	}
	COLOR_BASE = COLOR_BASE_ADD + maincode;
	SKY_BASE = SKY_BASE_ADD + maincode;
	WALL_BASE = WALL_BASE_ADD + maincode;
	FLY_BASE = FLY_BASE_ADD + maincode;
	CHARACTER_BASE = CHARACTER_BASE_ADD + maincode;
	OVEROLL_BASE = OVEROLL_BASE_ADD + maincode;
}

VOID KeyIni(){
	RegisterHotKey (NULL, 0x1,  0x0001|0x4000, 0x57);
	cout << endl << "\n内存读取成功" << endl;
	system ("cls");
	Ini ();
	cout << ALL_ADD;
	Ver();
	RegisterHotKey (NULL, 0x2,  0x0001|0x4000, 0x51);
	RegisterHotKey (NULL, 0x3,  0x0001|0x4000, 0x52);
	RegisterHotKey (NULL, 0x4, 0x4000, 0x56);
	RegisterHotKey (NULL, 0x5, 0x4000, 0x6B);
	RegisterHotKey (NULL, 0x6, 0x4000, 0xBB);
	RegisterHotKey (NULL, 0x7, 0x4000, 0x6D);
	RegisterHotKey (NULL, 0x8, 0x4000, 0xBD);
	RegisterHotKey (NULL, 0x9, 0x4000, 0x2E);
	RegisterHotKey (NULL, 0xA,  0x0001|0x4000, 0x45);
	MSG msg;
	while (GetMessage (&msg, NULL, 0, 0)){
		if (msg.message == WM_HOTKEY){
			if (msg.wParam == 0x1){//ALT+W
				cout << "用户日志 =========> 低倍加速已" << choi (SPEEDto2 ()) << endl;
			}else if (msg.wParam == 0x2){//ALT+Q
				cout << "用户日志 =========> 穿墙已" << choi (CHARACTERtoWALL ()) << endl;
			}else if (msg.wParam == 0xA){//ALT+E
				cout << "用户日志 =========> 狗皮加速已" << choi (SPEEDto7 ()) << endl;
			}else if (msg.wParam == 0x3){//ALT+R
				cout << "用户日志 =========> 飞天踏空已" << choi (CHARACTERtoFLY ()) << endl;
			}else if (msg.wParam == 0x4){//V
				cout << "用户日志 =========> 极速下机已" << choi (ALLto7 ()) << endl;
			}else if (msg.wParam == 0x5 || msg.wParam == 0x6){//+
				COLOR_CHANGE = SKY_CHANGE = WALL_CHANGE = FALSE;
				CHRACTERtoRED();
				SKYtoBLACK();
				CHARACTERtoWALL();
				cout << "用户日志 =========> 部分常用功能开启成功" << endl;
			}else if (msg.wParam == 0x7 || msg.wParam == 0x8){//-
				COLOR_CHANGE = SKY_CHANGE = WALL_CHANGE = FLY_CHANGE = CHARACTER_CHANGE = OVEROLL_CHANGE = TRUE;
				DOG_CHANGE = FALSE;
				CHRACTERtoRED();
				SKYtoBLACK();
				CHARACTERtoWALL();
				CHARACTERtoFLY();
				SPEEDto2();
				ALLto7();
				cout << "用户日志 =========> 所有功能关闭成功" << endl;
			}else if (msg.wParam == 0x9){//DEL
				system("cls");
				Ini();
				Ver();
			}
		}
	}
}

int main(int argc, char* argv[]){
	Ini();
	pid = GetPid ("hyxd.exe");
	if (pid <= 0){
		SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 12);
		printf("初始化失败\n\n");
		SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 7);
		system ("pause");
		return 0;
	}
	MoudleIni ();
	KeyIni();
	return 0;
}