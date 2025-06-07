#pragma once

#include "Protocol.h"
#include "Object.h"
// ---
struct CUSTOM_JEWELBANK_DATA
{
	int Bless;
	int Soul;
	int Life;
	int Creation;
	int Chaos;
};

struct PSBMSG_JEWELBANK_SEND
{
	PSBMSG_HEAD header; // C1:F3:F4
	int slot;
};

struct PSBMSG_JEWELBANKWITHDRAW_SEND
{
	PSBMSG_HEAD header; // C1:F3:F4
	int type;
	int count;
};

struct PSBMSG_JEWELBANK_UPDATE_SEND
{
	PSBMSG_HEAD header; // C1:F3:F4
};

struct PSBMSG_JEWELBANK_RECV
{
	PSBMSG_HEAD h;
	int Bless;
	int Soul;
	int Life;
	int Creation;
	int Chaos;
};
// ---
class CCustomJewelBank
{
public:
	CCustomJewelBank();
	void Load();
	// ---
	void DrawNewStatus();
	void DrawJewelBankWindow();
	void OpenWindow();
	bool CommandNext(DWORD Event);
	bool CommandPrev(DWORD Event);
	bool EventJewelBankWindow_Close(DWORD Event);
	bool EventJewelBankWithDraw(DWORD Event);
	void JewelBankWithDrawSend(int type, int count);
	// ---
	void JewelBankSend(int slot);
	void GCCustomJewelBankInfoRecv(PSBMSG_JEWELBANK_RECV* lpMsg);


private:
	// ---
	CUSTOM_JEWELBANK_DATA m_Data;
	bool IsOpen;
	short StatusLoad;
	DWORD StatusTick;
	int Loading;
	int JewelEnable;
	int Bless;
	int Soul;
	int Life;
	int Creation;
	int Chaos;
	int Page;
};
extern CCustomJewelBank gCustomJewelBank;