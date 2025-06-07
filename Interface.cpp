#include "stdafx.h"
#include "Common.h"
#include "CustomCommandInfo.h"
#include "CustomEventTime.h"
#include "CustomRanking.h"
#include "Interface.h"
#include "Import.h"
#include "Reconnect.h"
#include "TMemory.h"
#include "Defines.h"
#include "NewsBoard.h"
#include "OffTrade.h"
#include "Protect.h"
#include "Protocol.h"
#include "PrintPlayer.h"
#include "User.h"
#include "Util.h"
#include "array.h"
#include "Offset.h"
#include "StatsAdvance.h"
#include "CustomCloak.h"
//#include "ChatExpanded.h"
#include "Camera.h"
#include "TrayModeNew.h"
#include "Controller.h"
#include "postInterface.h"
#include "post_item.h"
#include "Ruud.h"
#include "Inter3.h"
#include "InterEx.h"
#include "Central.h"
#include "NPCRuud.h"
#include "ChangeClass.h"
#include "PartySearch.h"
#include "PartySearchSettings.h"
#include "CustomRankUser.h"
#include "MultiWare.h"
#include "ChangeClass.h"
#include "LuckyWheels.h"
#include "ChangeReset.h"
#include "CSmithItem.h"
#include "SmithItem.h"
#include "CustomJewelBank.h"
#include "SkyBox.h"
#include "EmojiSystem.h"
#include "Minimap.h"
//#include "ThueFlag.h"
//#include "CustomFlag.h"
//#include "BuyVip.h"
//#if(SKIN)
////#include "RentSkin.h"
//#endif
#include "RentSkin.h"
#include "ThueFlag.h"
#include "DailyReward.h"
#include "ItemMarket.h"
Interface gInterface;
#define FPS_		(float)0x5EF5A18

Interface::Interface()
{
}

Interface::~Interface()
{
}
void NewModelRender3D(float x, float y, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse) // code hien thi item
{
	glMatrixMode(0x1701);
	glPushMatrix( );
	glLoadIdentity( );

	glViewport2( 0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y );
	float v2 = *(float*) MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;

	gluPerspective2(1.0, v2, *(float*)0xE61E38, *(float*)0xE61E3C );
	glMatrixMode(0x1700u);
	glPushMatrix( );
	glLoadIdentity( );
	GetOpenGLMatrix(0x87933A0);
	EnableDepthTest( );
	EnableDepthMask( );

	RenderItem3D(x, y, Width, Height, ItemID, Level, Excl, Anc, OnMouse);

	glMatrixMode(0x1700u);
	glPopMatrix( );
	glMatrixMode(0x1701u);
	glPopMatrix( );

	glColor4f((GLfloat) 1.0, (GLfloat) 1.0, (GLfloat) 1.0,(GLfloat) 1.0);
	pSetBlend(false);
}
void Interface::WindowDetail()  
{
    char test[500];
    sprintf_s(test, sizeof(test), "Server: %s || Player: %s || Level: %d || Reset: %d  || WC: %d || GP: %d || MuPirata 99C", gProtect.m_MainInfo.WindowName, gObjUser.lpPlayer->Name, gObjUser.lpPlayer->Level,  ViewReset, Coin1, Coin3 );
    SetWindowText(pGameWindow, test);
}

void Interface::RenderObjectSystem() 
{
	if(gProtect.m_MainInfo.MonitorMS == 1){
		gInterface.lastReport = GetTickCount();
		gInterface.frameCount = 0;
		gEmojis.AddTextures(); 

	}
	if(gProtect.m_MainInfo.MonitorFPS == 1){
		gInterface.iniciador = 1;
	}
#if FLAG
	ThueFlag.Bind();
#endif
	#if(DEV_PLAYERSHOP)
//	g_ItemMarket.Bind();
#endif
	this->BindObject(OBJECT_FLAG_SYSTEM_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(OBJECT_SKIN_SYSTEM_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(OBJECT_DAILY_SYSTEM_CLOSE, 0x7EC5, 36, 29, -1, -1);
	//Jewel Bank
	this->BindObject(eJewelBank_MAIN, 0x7A5A, 222, 240, -1, -1);
	this->BindObject(eJewelBank_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eJewelBank_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eJewelBank_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eJewelBank_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eJewelBank_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eJewelBank_NEXT, 0x7903, 25, 40, -1, -1);
	this->BindObject(eJewelBank_PREV, 0x7904, 25, 40, -1, -1);
	for (int i=0; i < 50;i++)
	{
		this->BindObject(eJewelBank_WITHDRAW+i, 31743, 16, 32, -1, -1);
	}
	//--news
		this->BindObject(eNEWS_MAIN, 0x7A5A, 222, 303, -1, -1);
	this->BindObject(eNEWS_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eNEWS_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eNEWS_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eNEWS_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eNEWS_INFOBG, 0x787D, 170, 21, -1, -1);
	this->BindObject(eNEWS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eNEWS_BACK, 0x7A5E, 128, 29, -1, -1);	
	//--

		//Menu
	this->BindObject(eMenu_MAIN, 0x7A5A, 222, 240, -1, -1);
	this->BindObject(eMenu_MAINTWO, 0x7A5A, 222, 240, -1, -1);
	this->BindObject(eMenu_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eMenu_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eMenu_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eMenu_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eMenu_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eMenu_OPT1, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eMenu_OPT2, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eMenu_OPT3, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eMenu_OPT4, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eMenu_OPT20, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eMenu_OPT21, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eMenu_VAULT, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eMenu_USERPANEL, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eMenu_RESETCHANGE, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eMenu_LUCKYWELL, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eMenu_SMITH_ITEM, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eMenu_NEXT, 0x7918, 23, 23, -1, -1);
	this->BindObject(eMenu_PREVIUS, 0x7913, 23, 23, -1, -1);


	//--
	this->BindObject(eTIME, 30847, 106, 22, -10, 359);
	this->BindObject(eFlag01, 0x7880, 78, 78, -1, -1);
	this->BindObject(eFlag02, 0x7881, 78, 78, -1, -1);
	this->BindObject(eFlag03, 0x7882, 78, 78, -1, -1);
	this->BindObject(eFlag04, 0x7883, 78, 78, -1, -1);
	this->BindObject(eFlag05, 0x7884, 78, 78, -1, -1);
	this->BindObject(eFlag06, 0x7885, 78, 78, -1, -1);
	this->BindObject(eFlag07, 0x7886, 78, 78, -1, -1);
	this->BindObject(eFlag08, 0x7887, 78, 78, -1, -1);
	this->BindObject(eFlag09, 0x7888, 78, 78, -1, -1);
	this->BindObject(eFlag10, 0x7889, 78, 78, -1, -1);
	this->BindObject(eFlag11, 0x7890, 78, 78, -1, -1);
	this->BindObject(eFlag12, 0x7891, 78, 78, -1, -1);
	this->BindObject(eFlag13, 0x7892, 78, 78, -1, -1);
	this->BindObject(eFlag14, 0x7893, 78, 78, -1, -1);
	this->BindObject(eFlag15, 0x7894, 78, 78, -1, -1);
	this->BindObject(eFlag16, 0x7895, 78, 78, -1, -1);
	this->BindObject(eFlag17, 0x7896, 78, 78, -1, -1);
	this->BindObject(eFlag18, 0x7897, 78, 78, -1, -1);
	this->BindObject(eFlag19, 0x7898, 78, 78, -1, -1);
	this->BindObject(eFlag20, 0x7899, 78, 78, -1, -1);
	this->BindObject(eFlag21, 0x7900, 78, 78, -1, -1);
	this->BindObject(eFlag22, 0x7901, 78, 78, -1, -1);

	//--
	this->BindObject(eRanking, 0x7902, 179, 27, -1, -1);
	this->BindObject(eSAMPLEBUTTON, 0x7903, 25, 40, -1, -1);
	this->BindObject(eSAMPLEBUTTON2, 0x7904, 25, 40, -1, -1);
	//--
	this->BindObject(eVip_MAIN, 0x7A5A, 222, 300, 205, -1);
	this->BindObject(eVip_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eVip_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eVip_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eVip_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eVip_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eVip_BRONZE, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eVip_SILVER, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eVip_GOLD, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eVip_PLATINUM, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eVip_STATUS, 0x7A5E, 108, 29, -1, -1);
	
	//--
	this->BindObject(eCommand_MAIN, 0x7A5A, 222, 300, 205, -1);
	this->BindObject(eCommand_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eCommand_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eCommand_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eCommand_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eCommand_CLOSE, 0x7EC5, 36, 29, -1, -1);
	//--
	this->BindObject(eRanking_MAIN, 0x7A5A, 222, 300, 205, -1);
	this->BindObject(eRanking_CLOSE, 0x7EC5, 36, 29, -1, -1);
	//--
	this->BindObject(eEventTime_MAIN, 0x7A5A, 222, 300, 205, -1);
	this->BindObject(eEventTime_CLOSE, 0x7EC5, 36, 29, -1, -1);
	//--
	this->BindObject(eCONFIRM_MAIN, 0x7A5A, 222, 120, 205, -1);
	this->BindObject(eCONFIRM_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eCONFIRM_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eCONFIRM_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eCONFIRM_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eCONFIRM_BTN_OK, 0x7A5B, 54, 30, -1, -1);
	this->BindObject(eCONFIRM_BTN_CANCEL, 0x7A5C, 54, 30, -1, -1);
	this->BindObject(eLogo, 0x7905, 150, 114, -1, -1);

	// Change Class
	this->BindObject(eCHANGINGCLASS_MAIN, 0x7A5A, 222, 303, -1, -1);
	this->BindObject(eCHANGINGCLASS_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eCHANGINGCLASS_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eCHANGINGCLASS_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eCHANGINGCLASS_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eCHANGINGCLASS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_INFOBG, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eCHANGINGCLASS_MONEYBG, 0x7A89, 170, 26, -1, -1);
	this->BindObject(eCHANGINGCLASS_DW, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_DK, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_ELF, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_MG, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_DL, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_SUM, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_RF, 0x7A5E, 106, 29, -1, -1);

	//Party Search
	this->BindObject(ePARTYSETTINGS_MAIN, 0x7A5A, 222, 345, -1, -1);
	this->BindObject(ePARTYSETTINGS_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(ePARTYSETTINGS_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(ePARTYSETTINGS_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(ePARTYSETTINGS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(ePARTYSETTINGS_SYSTEM_ACTIVE, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_ONLY_GUILD, 0x7BAE, 15, 15, -1, -1); 
	this->BindObject(ePARTYSETTINGS_ONE_CLASS, 0x7BAE, 15, 15, -1, -1); 
	this->BindObject(ePARTYSETTINGS_DARK_WIZARD, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_DARK_KNIGHT, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_ELF, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_MAGIC_GLADIATOR, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_DARK_LORD, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_SUMMONER, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_RAGE_FIGHTER, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_LEVEL_MINUS, 0x7C0D, 16, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_LEVEL_PLUS, 0x7AA4, 16, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_OK, 0x7A5B, 54, 30, -1, -1);
	this->BindObject(ePARTYSEARCH_MAIN, 0x7A5A, 222, 345, -1, -1);
	this->BindObject(ePARTYSEARCH_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(ePARTYSEARCH_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(ePARTYSEARCH_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(ePARTYSEARCH_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(ePARTYSEARCH_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(ePARTYSEARCH_LEFT, 0x7E56, 20, 23, -1, -1);
	this->BindObject(ePARTYSEARCH_RIGHT, 0x7E57, 20, 23, -1, -1);
	this->BindObject(ePARTYSETTINGS_INF, 0x7915, 54, 30, -1, -1);
	this->BindObject(ePARTYSETTINGS_INF2, 0x7916, 54, 30, -1, -1);

	//Warehouse
	this->BindObject(eVAULT_MAIN, 0x7A5A, 222, 220, -1, -1);
	this->BindObject(eVAULT_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eVAULT_FRAME, 0x7A58, 230, 12, -1, -1);
	this->BindObject(eVAULT_FOOTER, 0x7A59, 230, 0, -1, -1);
	this->BindObject(eVAULT_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eVAULT_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eVAULT_INFOBG, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eVAULT_MONEYBG, 0x7A89, 170, 26, -1, -1);
	this->BindObject(eVAULT_FINISH, 0x7A5E, 128, 29, -1, -1);
	this->BindObject(eWARE1_FINISH, 0x7A5E, 128, 29, -1, -1);
	this->BindObject(eWARE2_FINISH, 0x7A5E, 128, 29, -1, -1);
	this->BindObject(eWARE3_FINISH, 0x7A5E, 128, 29, -1, -1);
	this->BindObject(eWARE4_FINISH, 0x7A5E, 128, 29, -1, -1);
	this->BindObject(eWARE5_FINISH, 0x7A5E, 128, 29, -1, -1);
	this->BindObject(eWARE6_FINISH, 0x7A5E, 128, 29, -1, -1);
	this->BindObject(eWARE7_FINISH, 0x7A5E, 128, 29, -1, -1);
	this->BindObject(eWARE8_FINISH, 0x7A5E, 128, 29, -1, -1);
	this->BindObject(eWARE9_FINISH, 0x7A5E, 128, 29, -1, -1);

	//LuckyWheell
	this->BindObject(eLuckyWheelStart, 0x9327, 86, 33, -1, -1);
	this->BindObject(eLuckyWheelPanel, 0x9328, 312, 292, -1, -1);
	gInterface.BindObject(eCloseLuckyWheel, 0X7EC5, 36, 29, -1, -1);
	this->LuckyWheelNumber = -1;

		// ChangeCReset
	this->BindObject(eCHANGE_RESET_MAIN, 0x7A5A, 222, 303, -1, -1);
	this->BindObject(eCHANGE_RESET_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eCHANGE_RESET_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eCHANGE_RESET_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eCHANGE_RESET_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eCHANGE_RESET_LINE, 0x7B67, 154, 2, -1, -1);
	this->BindObject(eCHANGE_RESET_CLOSE, 0x7A5E, 128, 29, -1, -1);
	this->BindObject(eCHANGE_RESET_INFOBG, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eCHANGE_RESET_MONEYBG, 0x7A89, 170, 26, -1, -1);
	this->BindObject(eCHANGE_RESET_5, 0x7908, 106, 29, -1, -1); 
	this->BindObject(eCHANGE_RESET_10, 0x7908, 106, 29, -1, -1); 
	this->BindObject(eCHANGE_RESET_15, 0x7908, 106, 29, -1, -1); 
	this->BindObject(eCHANGE_RESET_20, 0x7908, 106, 29, -1, -1);
	this->BindObject(eCHANGE_RESET_25, 0x7908, 106, 29, -1, -1); 
	//clear
SetDword(0x008651AA+1,(DWORD)"Custom\\Interface\\newui_item_money_trash.tga");
	
		this->BindObject(eTrash, 0x9993, 24, 24, -1, -1); //909986
		this->BindObject(eTrash_Expanded, 0x9993, 24, 24, -1, -1);
	
		this->BindObject(eTrash_MAIN, 0x7A5A, 222, 120, -1, -1);
		this->BindObject(eTrash_TITLE, 0x7A63, 230, 67, -1, -1);
		this->BindObject(eTrash_FRAME, 0x7A58, 230, 15, -1, -1);
		this->BindObject(eTrash_FOOTER, 0x7A59, 230, 50, -1, -1);
		this->BindObject(eTrash_YES, 0x7B12, 54, 30, -1, -1);
		this->BindObject(eTrash_NO, 0x7B0C, 54, 30, -1, -1);
	//smith
	this->BindObject(eUNCHECK_2, iOptionCheck, 15, 15, 175, 60);
	this->BindObject(eUNCHECK_3, iOptionCheck, 15, 15, 175, 90);
	this->BindObject(eUNCHECK_6, iOptionCheck, 15, 15, 195, 90);
	this->BindObject(eUNCHECK_4, iOptionCheck, 15, 15, 175, 120);
	this->BindObject(eUNCHECK_5, iOptionCheck, 15, 15, 175, 150);
	this->BindObject(eCHECKED_2, iOptionCheck, 15, 15, 175, 60);
	this->BindObject(eCHECKED_3, iOptionCheck, 15, 15, 175, 90);
	this->BindObject(eCHECKED_6, iOptionCheck, 15, 15, 195, 90);
	this->BindObject(eCHECKED_4, iOptionCheck, 15, 15, 175, 120);
	this->BindObject(eCHECKED_5, iOptionCheck, 15, 15, 175, 150);
	this->BindObject(eSMITH_MAIN, 0x7A5A, 222, 383, -1, -1);
	this->BindObject(eSMITH_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eSMITH_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eSMITH_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eSMITH_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eSMITH_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eSMITH_BUY, 0x7A5E, 128, 29, -1, -1);
	this->BindObject(eSMITH_ITEMTYPE, 0x7C0D, 16, 15, 215, 70);
	this->BindObject(eSMITH_ITEMTYPE_1, 0xAA4, 16, 15, 273, 70);
	this->BindObject(eSMITH_ITEMINDEX, 0x7C0D, 17, 18, 208, 103);
	this->BindObject(eSMITH_ITEMINDEX_1, 0xAA4, 17, 18, 400, 103);
	this->BindObject(eSMITH_DAYS, 0x7C0D, 16, 15, 340, 70);
	this->BindObject(eSMITH_DAYS_1, 0xAA4, 16, 15, 393, 70);
	this->BindObject(eSMITH_LEVEL, 0x7C0D, 16, 15, 340, 153);
	this->BindObject(eSMITH_LEVEL_1, 0xAA4, 16, 15, 380, 153);
	this->BindObject(eSMITH_OPT, 0x7C0D, 16, 15, 340, 213);
	this->BindObject(eSMITH_OPT_1, 0xAA4, 16, 15, 380, 213);
	this->BindObject(eSMITH_SKILL, 0x7B69, 15, 15, 380, 175);
	this->BindObject(eSMITH_SKILL_1, 0x7B69, 15, 15, 380, 175);
	this->BindObject(eSMITH_LUCK, 0x7B69, 15, 15, 380, 195);
	this->BindObject(eSMITH_LUCK_1, 0x7B69, 15, 15, 380, 195);
	this->BindObject(eSMITH_EXC, 0x7B69, 15, 15, 380, 235);
	this->BindObject(eSMITH_EXC_1, 0x7B69, 15, 15, 380, 235);
	this->BindObject(eSMITH_EXC1, 0x7B69, 15, 15, 380, 255);
	this->BindObject(eSMITH_EXC1_1, 0x7B69, 15, 15, 380, 255);
	this->BindObject(eSMITH_EXC2, 0x7B69, 15, 15, 380, 275);
	this->BindObject(eSMITH_EXC2_1, 0x7B69, 15, 15, 380, 275);
	this->BindObject(eSMITH_EXC3, 0x7B69, 15, 15, 380, 295);
	this->BindObject(eSMITH_EXC3_1, 0x7B69, 15, 15, 380, 295);
	this->BindObject(eSMITH_EXC4, 0x7B69, 15, 15, 380, 315);
	this->BindObject(eSMITH_EXC4_1, 0x7B69, 15, 15, 380, 315);
	this->BindObject(eSMITH_EXC5, 0x7B69, 15, 15, 380, 335);
	this->BindObject(eSMITH_EXC5_1, 0x7B69, 15, 15, 380, 335);

	//Custom Store
	if( gProtect.m_MainInfo.CustomInterfaceType == 3 )
	{
		this->BindObject(eOFFTRADE_JoB, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_JoS, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_JoC, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_WCC, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_WCP, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_WCG, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_OPEN, 51522, 108, 30, -1, -1);
	}
	else
	{
		this->BindObject(eOFFTRADE_JoB, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_JoS, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_JoC, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_WCC, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_WCP, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_WCG, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_OPEN, 0x7BFD, 108, 30, -1, -1);
	}
	//-- custom
	this->BindObject(eSTORE_CLOSE, 0x7BFD, 108, 30, -1, -1);
	//Minimap
	this->BindObject(ePLAYER_POINT, 31460, 3, 3, -1, -1);
	this->BindObject(eNULL_MAP, 31461, 128, 128, -1, -1);
	this->BindObject(eLORENCIA_MAP, 31462, 128, 128, -1, -1);
	this->BindObject(eDUNGEON_MAP, 31463, 128, 128, -1, -1);
	this->BindObject(eDEVIAS_MAP, 31464, 128, 128, -1, -1);
	this->BindObject(eNORIA_MAP, 31465, 128, 128, -1, -1);
	this->BindObject(eLOSTTOWER_MAP, 31466, 128, 128, -1, -1);
	this->BindObject(eSTADIUM_MAP, 61465, 128, 128, -1, -1);
	this->BindObject(eATLANS_MAP, 31467, 128, 128, -1, -1);
	this->BindObject(eTarkan_MAP, 31468, 128, 128, -1, -1);
	this->BindObject(eElbeland_MAP, 31469, 128, 128, -1, -1);
	this->BindObject(eICARUS_MAP, 31470, 128, 128, -1, -1);
	this->BindObject(eAIDA_MAP, 31472, 128, 128, -1, -1);
	this->BindObject(eCRYWOLF_MAP, 31473, 128, 128, -1, -1);
	this->BindObject(eKANTRU_MAP, 31474, 128, 128, -1, -1);
	this->BindObject(eKANTRU3_MAP, 31475, 128, 128, -1, -1);
	this->BindObject(eBARRACKS_MAP, 31476, 128, 128, -1, -1);
	this->BindObject(eCALMNESS_MAP, 31477, 128, 128, -1, -1);
	this->BindObject(eRAKLION_MAP, 31478, 128, 128, -1, -1);
	this->BindObject(eVULCANUS_MAP, 31479, 128, 128, -1, -1);
	this->BindObject(eKALRUTAN_MAP, 31480, 128, 128, -1, -1);
	this->BindObject(eKALRUTAN2_MAP, 31481, 128, 128, -1, -1);
	this->BindObject(eNextCommand, 31659, 17, 18, -1, -1);
	this->BindObject(ePrevCommand, 31658, 17, 18, -1, -1);
	this->BindObject(eNextEvent, 31659, 17, 18, -1, -1);
	this->BindObject(ePrevEvent, 31658, 17, 18, -1, -1);
	this->BindObject(eCamera3DInit, 31659, 17, 18, -1, -1);
	this->BindObject(eCamera3DSwitch, 31659, 17, 18, -1, -1);
this->BindObject(OBJECT_NEWSYSTEM_MAIN, 40000, -1, -1, -1, 0.0f);
	this->Data[eTIME].OnShow = true;
	//


	if(gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
	{
		this->BindObject(ButtonSettings, 51522, 19, 19, -1, -1);
		this->BindObject(ButtonStart, 51522, 19, 19, -1, -1);
		this->BindObject(ButtonStop, 51522, 19, 19, -1, -1);
	}
	else
	{
		this->BindObject(ButtonSettings, 31761, 18, 13.3, -1, -1);
		this->BindObject(ButtonStart, 31762, 18, 13.3, -1, -1);
		this->BindObject(ButtonStop, 31763, 18, 13.3, -1, -1);
	}
		this->BindObject(ButtonStartAttack, 31593, 15, 15, -15, -15);
	//--
		this->BindObject(eJewelOfBank, 51522, 230.0, 270.0, -1, -1);
		this->BindObject(eJewelOfBankPush, 71521, 59, 28, -1, -1);
		this->BindObject(eJewelOfBankRemove, 71521, 59, 28, -1, -1);
		this->BindObject(eJewelOfBankClose, 71521, 59, 28, -1, -1);

	//--
	switch(gProtect.m_MainInfo.CustomInterfaceType)
	{
	case 1:
	case 2:
		//--
		if (gProtect.m_MainInfo.CustomMenuType == 1)
		{
			this->BindObject(eMenu, 0x7906, 102, 29, -1, -1);
		}
		else
		{
			this->BindObject(eMenu, 0x7906, 55, 30, -1, -1);
			this->BindObject(eMenuBG, 0x7907, 36, 18, 174, 0);
		}
		
		//--
		this->BindObject(MINIMAP_FRAME, 31608, 154, 162, -10, 359);
		this->BindObject(MINIMAP_TIME_FRAME, 31609, 134.0, 37.0, -10, 359);
		this->BindObject(MINIMAP_BUTTOM, 31617, 38.0f, 24.0f, -10, 569);
		#if WIDE_SCREEN == 0
		//---
		this->BindObject(eDragonLeft, 2337, 108.0, 45.0, 0.0, 383.5);
		this->BindObject(eParty, iNewParty, 25, 25, 348, 449);
		this->BindObject(eCharacter, iNewCharacter, 25, 25, 379, 449);
		this->BindObject(eInventory, iNewInventory, 25, 25, 409, 449);
		this->BindObject(eFriend, iNewWinpush, 52, 18, 581, 432);

		if(gProtect.m_MainInfo.CustomInterfaceType == 2)
		{
			this->BindObject(eFastMenu, iNewFastMenu, 53, 19, 5, 432);
		}
		this->BindObject(eGuild, iNewGuild, 52, 18, 581, 454);
        #endif
		break;
	case 3:
	case 4:
		this->BindObject(eButton1, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButton2, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButton3, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButton4, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButton5, 61525, 43.0f, 17.0f, -43.0f, -17.0f);

		if (gProtect.m_MainInfo.CustomMenuType == 1)
		{
			this->BindObject(eMenu, 0x7906, 102, 29, -1, -1);
		}
		else
		{
			this->BindObject(eMenu, 51522, 19, 19, -1, -1);
			this->BindObject(eMenuBG, 51522, 36, 18, 174, 0);
		}
		//Ex700
		this->BindObject(chatbackground, 51545, 300.0f, 128.0f, -10, 569);
		this->BindObject(eShop, 51522, 19.5f, 19.5f, -1, -1);
		this->BindObject(eCharacter, 51522, 19.5f, 19.5f, -1, -1);
		this->BindObject(eInventory, 51522, 19.5f, 19.5f, -1, -1);
		this->BindObject(eQuest, 51522, 19.5f, 19.5f, -1, -1);
		this->BindObject(eCommunity, 51522, 19.5f, 19.5f, -1, -1);
		this->BindObject(eSystem, 51522, 19.5f, 19.5f, -1, -1);
		break;
	default:
		if (gProtect.m_MainInfo.CustomMenuType == 1)
		{
			this->BindObject(eMenu, 0x7906, 102, 29, -1, -1);
		}
		else
		{
			this->BindObject(eMenu, 0x7906, 16, 12, -1, -1);
			this->BindObject(eMenuBG, 0x7907, 36, 18, 174, 0);
		}
		break;
	}
	if(gProtect.m_MainInfo.InventoryUPGRADE == 1)
	{
		this->BindObject(eMoney1, 0x7909, 75, 13, -1, -1);
		this->BindObject(eMoney2, 0x7910, 75, 13, -1, -1);
	}
	if(gProtect.m_MainInfo.DisableAdvance == 0)
	{
		gInterface.BindObject(eADVANCE_STAT_INFO, ex_INFO_2, 35, 30, -1, -1);
	}

	SetRange((LPVOID)0x00842086, 5, ASM::NOP);
	SetRange((LPVOID)0x0084234F, 5, ASM::NOP);
	SetRange((LPVOID)0x008423C3, 5, ASM::NOP);
	SetOp((LPVOID)oLoadSomeForm_Call, this->LoadImages, ASM::CALL);
	SetOp((LPVOID)oDrawInterface_Call, this->Work, ASM::CALL);

	if(gProtect.m_MainInfo.InventoryUPGRADE == 1)
	{
		SetRange((LPVOID)0x00835116, 5, ASM::NOP);
		SetOp((LPVOID)0x00835116, this->DrawZenAndRud, ASM::CALL);
	}



	gSkyBox.Load();
	#if (FLAG)
	ThueFlag.Bind();
#endif
		this->ClickTime = 0;
//	myheart::MUEmoji::Init(TEXTURE_EMOJI_LIST_ARROW, TEXTURE_EMOJI_LIST_ON, TEXTURE_EMOJI_LIST_BTN, 20, 14,   4, 0);
  //  myheart::MUEmoji::AddTexture(TEXTURE_EMOJI_LIST1, 361);
 //   myheart::MUEmoji::AddTexture(TEXTURE_EMOJI_LIST2, 309);
//    myheart::MUEmoji::AddTexture(TEXTURE_EMOJI_LIST3, 118);

//   InitEncDec();

}

void Interface::DrawZenAndRud(int a1, int a2, int a3, int a4)
{
	int v10;
	int v11;
	DWORD v23;
	v10 = *(DWORD*)(a1 + 40);
	v11 = *(DWORD*)(a1 + 36);
	v23 = *(DWORD*)(*(DWORD*)0x8128AC4 + 5956);
	*(float*)(0x00D24E88); //Width

	char MoneyBuff1[50], MoneyBuff2[50], MoneyBuff3[50], MoneyBuff4[50], test[50];
	ZeroMemory(MoneyBuff1, sizeof(MoneyBuff1));
	ZeroMemory(MoneyBuff2, sizeof(MoneyBuff2));
	ZeroMemory(MoneyBuff3, sizeof(MoneyBuff3));
	ZeroMemory(MoneyBuff4, sizeof(MoneyBuff4));

	pGetMoneyFormat(v23, MoneyBuff1, 0);
	pGetMoneyFormat(Coin3, MoneyBuff2, 0);
	pGetMoneyFormat(Coin1, MoneyBuff3, 0);
	pGetMoneyFormat(Coin2, MoneyBuff4, 0);

	gInterface.DrawFormat(eWhite, v11, v10 + 12, 190, 3, pGetTextLine(pTextLineThis, 223));
	//--
	gInterface.DrawGUI(eMoney1, v11 + 18, v10 + 365);
	gInterface.DrawFormat(eBlack, v11 + 18, v10 + 367, 20, 1, "Zen");
	gInterface.DrawFormat(eRed, v11 + 40, v10 + 367, 50, 3, "%s", MoneyBuff1);
	//--
	gInterface.DrawGUI(eMoney2, v11 + 102, v10 + 365);
	gInterface.DrawFormat(eBlack, v11 + 102, v10 + 367, 20, 1, "GP");
	gInterface.DrawFormat(eWhite, v11 + 128, v10 + 367, 45, 4, "%s", MoneyBuff2);
	//--
	gInterface.DrawGUI(eMoney2, v11 + 18, v10 + 378);
	gInterface.DrawFormat(eBlack, v11 + 17, v10 + 380, 20, 1, "WC");
	gInterface.DrawFormat(eGold, v11 + 38, v10 + 381, 50, 4, "%s", MoneyBuff3);
	//--
	//gInterface.DrawGUI(eMoney2, v11 + 102, v10 + 378);
	//gInterface.DrawFormat(eBlack, v11 + 98, v10 + 380, 20, 1, "WCP");
	//gInterface.DrawFormat(eBlue, v11 + 128, v10 + 381, 45, 4, "%s", MoneyBuff4);
}
void Interface::LoadModels()
{
	pLoadModel(406, "Data\\Custom\\Bmd\\VIP1\\", "musign", -1);
	pLoadTexture(406, "Custom\\Bmd\\VIP1\\", 0x2901, 0x2600, 1);
	pLoadModel(407, "Data\\Custom\\Bmd\\VIP2\\", "musign", -1);
	pLoadTexture(407, "Custom\\Bmd\\VIP2\\", 0x2901, 0x2600, 1);
	pLoadModel(408, "Data\\Custom\\Bmd\\VIP3\\", "musign", -1);
	pLoadTexture(408, "Custom\\Bmd\\VIP3\\", 0x2901, 0x2600, 1);
	
	// ----
	pInitModelData2();
}

void Interface::LoadImages()
{
	if(gProtect.m_MainInfo.InventoryUPGRADE == 1)
	{
		pLoadImage("Custom\\Interface\\Money\\item_money.tga", 0x7909, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\Money\\item_money2.tga", 0x7910, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\Null.tga", 0x9993, 0x2601, 0x2900, 1, 0);
		pLoadImage("Custom\\Interface\\NewsBoard_Title.tga", 0x787D, 0x2601, 0x2900, 1, 0);
	}
	//
	pLoadImage("Custom\\Interface\\Rank01.tga", 0x7880, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank02.tga", 0x7881, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank03.tga", 0x7882, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank04.tga", 0x7883, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank05.tga", 0x7884, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank06.tga", 0x7885, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank07.tga", 0x7886, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank08.tga", 0x7887, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank09.tga", 0x7888, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank10.tga", 0x7889, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank11.tga", 0x7890, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank12.tga", 0x7891, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank13.tga", 0x7892, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank14.tga", 0x7893, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank15.tga", 0x7894, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank16.tga", 0x7895, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank17.tga", 0x7896, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank18.tga", 0x7897, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank19.tga", 0x7898, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank20.tga", 0x7899, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank21.tga", 0x7900, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank22.tga", 0x7901, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Ranking.tga", 0x7902, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Next.tga", 0x7903, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Previous.tga", 0x7904, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\MU-logo.tga", 0x7905, 0x2601, 0x2901, 1, 0);

	if (gProtect.m_MainInfo.CustomMenuType == 2)
	{
		pLoadImage("Custom\\Interface\\Menu1.tga", 0x7906, 0x2601, 0x2901, 1, 0);
	}
	else
	{
		pLoadImage("Custom\\Interface\\Menu2.tga", 0x7906, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\Menu_BG.tga", 0x7907, 0x2601, 0x2901, 1, 0);
	}
	pLoadImage("Custom\\Interface\\Button.tga", 0x7908, 0x2601, 0x2900,1,0);

	pLoadImage("Custom\\Interface\\NextMenu.tga", 0x7918, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\PreviousMenu.tga", 0x7913, GL_LINEAR, GL_CLAMP, 1, 0);

	pLoadImage("Custom\\Interface\\LuckyWheel\\itembackpanel.tga", 0x9326, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\LuckyWheel\\topmenutabbt1.tga", 0x9327, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\LuckyWheel\\ui_dialog_e.tga", 0x9328, 0x2601, 0x2900, 1, 0);



	pLoadImage("Custom\\Interface\\Info.tga", 0x7915, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\Info2.tga", 0x7916, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\Layout.tga", 51523, 0x2601, 0x2901, 1, 0);

//MiniMap
	pLoadImage("Custom\\Maps\\PlayerPoint.jpg", 31460, 0x2600, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\none.tga", 31461, 0x2601, 0x2900, 1, 0);
	//--
	//pLoadImage("Custom\\Maps\\edBtUcx.tga", 31464, 0x2601, 0x2900, 1, 0); //-- Dungeon
	//pLoadImage("Custom\\Maps\\edBtUcx_2.tga", 31459, 0x2601, 0x2900, 1, 0); //-- Dungeon
	//pLoadImage("Custom\\Maps\\YYB6BUk.tga", 31465, 0x2601, 0x2900, 1, 0); //-- Dungeon
	//pLoadImage("Custom\\Maps\\mini_map_ui_blacksmith.tga", 31466, 0x2601, 0x2900, 1, 0); //-- Dungeon
	//pLoadImage("Custom\\Maps\\mini_map_ui_Potion.tga", 31467, 0x2601, 0x2900, 1, 0); //-- Dungeon
	//pLoadImage("Custom\\Maps\\mini_map_ui_baul.tga", 31468, 0x2601, 0x2900, 1, 0); //-- Dungeon
	//pLoadImage("Custom\\Maps\\mini_map_ui_Que.tga", 31469, 0x2601, 0x2900, 1, 0); //-- Dungeon
	//pLoadImage("Custom\\Maps\\mini_map_ui_monsterred.tga", 31471, 0x2601, 0x2900, 1, 0); //-- Dungeon Red
	//pLoadImage("Custom\\Maps\\mini_map_ui_monsterblue.tga", 31472, 0x2601, 0x2900, 1, 0); //-- Dungeon Blue
	//pLoadImage("Custom\\Maps\\mini_map_ui_party.tga", 61520, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	//pLoadImage("Custom\\Maps\\mini_map_ui_monstergold.tga", 31473, 0x2601, 0x2900, 1, 0); //-- Dungeon Gold
	  //pLoadImage("Custom\\UISystem\\panel.tga",40000,-1,-1,-1,-1);

	if(gProtect.m_MakeViewTRSData.TooltipS15 == 1)
	{
		//-- itemtooltip
		pLoadImage("Interface\\GFx\\tooltip_bg01.tga", 61511, 0x2601, 0x2901, 1, 0); //esquina arriba izquierda
		pLoadImage("Interface\\GFx\\tooltip_bg02.tga", 61512, 0x2601, 0x2901, 1, 0);
		pLoadImage("Interface\\GFx\\tooltip_bg03.tga", 61513, 0x2601, 0x2901, 1, 0); //esquina arriba derecha
		pLoadImage("Interface\\GFx\\tooltip_bg04.tga", 61514, 0x2601, 0x2901, 1, 0);
		pLoadImage("Interface\\GFx\\tooltip_bg06.tga", 61515, 0x2601, 0x2901, 1, 0);
		pLoadImage("Interface\\GFx\\tooltip_bg07.tga", 61516, 0x2601, 0x2901, 1, 0); //esquina abajo izquierda
		pLoadImage("Interface\\GFx\\tooltip_bg08.tga", 61517, 0x2601, 0x2901, 1, 0);
		pLoadImage("Interface\\GFx\\tooltip_bg09.tga", 61518, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	}
	//-- itemtooltip
	pLoadImage("Interface\\GFx\\popupbg01.tga", 71511, 0x2601, 0x2901, 1, 0); //esquina arriba izquierda
	pLoadImage("Interface\\GFx\\popupbg02.tga", 71512, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\popupbg03.tga", 71513, 0x2601, 0x2901, 1, 0); //esquina arriba derecha
	pLoadImage("Interface\\GFx\\popupbg04.tga", 71514, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\popupbg06.tga", 71515, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\popupbg07.tga", 71516, 0x2601, 0x2901, 1, 0); //esquina abajo izquierda
	pLoadImage("Interface\\GFx\\popupbg08.tga", 71517, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\popupbg09.tga", 71518, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	//--
	pLoadImage("Interface\\GFx\\popup_line_m.tga", 71519, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	pLoadImage("Interface\\GFx\\popup_line_s.tga", 71520, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	//--
	pLoadImage("Interface\\GFx\\Render_buttom_1.tga", 71521, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	pLoadImage("Interface\\GFx\\Render_buttom_2.tga", 71522, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	pLoadImage("Interface\\GFx\\Render_buttom_3.tga", 71524, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	//--
	pLoadImage("Interface\\GFx\\RenderBits_Sound.tga", 71523, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	pLoadImage("Interface\\GFx\\newui_option_volume01.tga", 31596, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	pLoadImage("Interface\\GFx\\newui_option_volume02.tga", 31597, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	//--
	pLoadImage("Custom\\Party\\newui_Party_Back.tga", 81520, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Party\\newui_Party_flag.tga", 81521, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Party\\newui_Party_HpBar.jpg", 81522, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Party\\newui_Party_ManaBar.jpg", 81523, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Party\\newui_Party_X.tga", 81524, 0x2601, 0x2901, 1, 0);
	//--
			//--
  /*  pLoadImage("Interface\\GFx\\emojis_f.tga", TEXTURE_EMOJI_LIST1, GL_LINEAR, GL_CLAMP, 1, 0);
    pLoadImage("Interface\\GFx\\emojis_f2.tga", TEXTURE_EMOJI_LIST2, GL_LINEAR, GL_CLAMP, 1, 0);
    pLoadImage("Interface\\GFx\\emojis_f3.tga", TEXTURE_EMOJI_LIST3, GL_LINEAR, GL_CLAMP, 1, 0);
    pLoadImage("Interface\\GFx\\emoji_list_btn.tga", TEXTURE_EMOJI_LIST_BTN, GL_LINEAR, GL_CLAMP, 1, 0);
    pLoadImage("Interface\\GFx\\newui_chat_emoji_on.jpg", TEXTURE_EMOJI_LIST_ON, GL_LINEAR, GL_CLAMP, 1, 0);
    pLoadImage("Interface\\GFx\\btn_arrow.tga", TEXTURE_EMOJI_LIST_ARROW, GL_LINEAR, GL_CLAMP, 1, 0);
    pLoadImage("Interface\\GFx\\newui_chat_back.jpg", 31279, GL_LINEAR, GL_CLAMP, 1, 0);
*/
	//--
	LoadBitmapA("Interface\\newui_number1.tga", 31337, 9729, 10496, 1, 0);

	LoadBitmapA("Interface\\newui_SW_Minimap_Frame.tga", 31608, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("Interface\\newui_SW_Time_Frame.tga", 31609, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("Interface\\newui_SW_MiniMap_Bt_clearness.jpg", 31617, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("Interface\\GFx\\InventoryFrame_RuudShop.tga", 61560, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("Interface\\GFx\\Menu_RuudShopFrame.tga", 61561, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("Interface\\GFx\\Menu_Button03.tga", 61562, GL_LINEAR, GL_CLAMP, 1, 0);
	//
	switch(gProtect.m_MainInfo.CustomInterfaceType) 
	{
	case 1:
	case 2:
		//--
		LoadBitmapA("Custom\\InterfaceS2\\Item_Back01.tga", 61522, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 51522, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Custom\\InterfaceS2\\DragonLeft.tga", 2337, GL_LINEAR, GL_CLAMP, 1, 0);
//		LoadBitmapA("Custom\\UISystem\\panel.tga", 40000, OBJECT_NEWSYSTEM_MAIN,GL_CLAMP,1,0);

		//--
		if(gProtect.m_MainInfo.CustomInterfaceType == 1)
		{
			LoadBitmapA("Custom\\InterfaceS2\\Menu_left97.jpg", 31292, GL_LINEAR, GL_CLAMP, 1, 0); //replace
			LoadBitmapA("Custom\\Interface\\none.tga", 31300, GL_LINEAR, GL_CLAMP, 1, 0);
			//LoadBitmapA("Custom\\Interface\\Decor.tga", 87968, 0x2601, 0x2901, 1, 0);
			//LoadBitmapA("Custom\\Interface\\InterfaceBar.tga", 87969, 0x2601, 0x2901, 1, 0);

		}else
		{
			LoadBitmapA("Custom\\InterfaceS2\\Menu_left.jpg", 31292, GL_LINEAR, GL_CLAMP, 1, 0); //replace
			LoadBitmapA("Custom\\InterfaceS2\\Menu_SD.jpg", 31300, GL_LINEAR, GL_CLAMP, 1, 0);
		}
		
		LoadBitmapA("Custom\\InterfaceS2\\Menu_right.jpg", 31294, GL_LINEAR, GL_CLAMP, 1, 0); //replace
		LoadBitmapA("Custom\\InterfaceS2\\Menu_middle.jpg", 31293, GL_LINEAR, GL_CLAMP, 1, 0); //replace
		//--
		LoadBitmapA("Custom\\InterfaceS2\\Menu_Red.jpg", 0x7A42, GL_LINEAR, GL_CLAMP, 1, 0);//replace
		LoadBitmapA("Custom\\InterfaceS2\\Menu_Green.jpg", 0x7A41, GL_LINEAR, GL_CLAMP, 1, 0);//replace
		LoadBitmapA("Custom\\InterfaceS2\\Menu_Blue.jpg", 0x7A40, GL_LINEAR, GL_CLAMP, 1, 0);//replace
		LoadBitmapA("Custom\\InterfaceS2\\Menu_AG.jpg", 31299, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Custom\\InterfaceS2\\Boton\\Menu_fastmenu.jpg", iNewFastMenu, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31295, GL_LINEAR, GL_CLAMP, 1, 0); //replace
		LoadBitmapA("Custom\\InterfaceS2\\Boton\\Menu_Inventory.jpg", iNewInventory, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Boton\\Menu_Character.jpg", iNewCharacter, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Boton\\Menu_Party.jpg", iNewParty, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Boton\\Menu_friend.jpg", iNewWinpush, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Boton\\Menu_guild.jpg", iNewGuild, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Custom\\InterfaceS2\\skillboxR.jpg", 0x700003, 0x2601, 0x2901, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_skill.jpg", 31308, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_skill2.jpg", 31309, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_skill3.jpg", 31311, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_command.jpg", 31310, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_non_skill.jpg", 31314, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_non_skill2.jpg", 31315, GL_LINEAR, GL_CLAMP, 1, 0); 
		LoadBitmapA("Custom\\InterfaceS2\\newui_non_skill3.jpg", 31317, GL_LINEAR, GL_CLAMP, 1, 0); 
		//--
		LoadBitmapA("Custom\\InterfaceS2\\newui_skillbox.jpg", 31312, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_skillbox2.jpg", 31313, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		//Interface Character
		LoadBitmapA("Custom\\InterfaceS2\\Menu\\Stats.jpg", 31352, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Menu\\StatsDL.jpg", 51291, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Menu\\Stats2.jpg", 51292, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Menu\\Level_box.jpg", 35353, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Menu\\Level_button.jpg", 51290, GL_LINEAR, GL_CLAMP, 1, 0);
		//-- chat
		LoadBitmapA("Custom\\InterfaceS2\\chat\\nis_vframe.jpg", 51551, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\chat\\nis_rsframe.tga", 51552, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\chat\\nis_rsframe_up.jpg", 51553, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\chat\\nis_rsframe_m.jpg", 51554, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\chat\\nis_rsframe_down.jpg", 51555, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\chat\\nis_hframe.jpg", 31275, 9729, 10496, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Chat\\dialogue1.tga", 51530, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Chat\\dialogue2.tga", 51531, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Chat\\dialogue2_1.jpg", 51532, GL_LINEAR, GL_CLAMP, 1, 0);
		#if WIDE_SCREEN
		LoadBitmapA("Custom\\Interface\\DragonRight.tga", 2336, GL_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("Custom\\Interface\\DragonLeft.tga", 2337, GL_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("Custom\\Interface\\Decor.tga", 87968, 0x2601, 0x2901, 1, 0);
		//-- Botones del Main
			LoadBitmapA("Custom\\Interface\\none.tga", 31303, GL_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("Custom\\Interface\\none.tga", 31304, GL_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("Custom\\Interface\\none.tga", 31305, GL_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("Custom\\Interface\\none.tga", 31306, GL_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("Custom\\Interface\\none.tga", 31307, GL_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("Custom\\Interface\\none.tga", 31295, GL_LINEAR, GL_CLAMP, 1, 0); //replace
			LoadBitmapA("Custom\\InterfaceS2\\Menu_Character.jpg", 88900, GL_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("Custom\\InterfaceS2\\Menu_friend.jpg", 88901, GL_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("Custom\\InterfaceS2\\Menu_Inventory.jpg", 88902, GL_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("Custom\\InterfaceS2\\Menu_fastmenu.jpg", 88903, GL_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("Custom\\InterfaceS2\\Menu_Party.jpg", 88904, GL_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("Custom\\InterfaceS2\\Menu_guild.jpg", 88905, GL_LINEAR, GL_CLAMP, 1, 0);
        #endif

		break;
	case 3:
		//--
		LoadBitmapA("Interface\\GFx\\ex700\\InventoryFrame_I1.tga", 61522, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\InventoryFrame_I2.tga", 61523, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\InventoryFrame_I3.tga", 61524, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Frame_I3.tga", 61526, GL_LINEAR, GL_CLAMP, 1, 0); //-- All Window
		LoadBitmapA("Interface\\GFx\\ex700\\InventoryFrame_I4.tga", 61527, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Draw_money.tga", 61528, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\button_close.tga", 61529, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Interface\\GFx\\ex700\\CharacterInfoFrame_I1.tga", 61532, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\newui_chainfo_btn_level.tga", 61533, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\ButtonCharacterInfo.tga", 61535, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Interface\\GFx\\ex700\\CharacterInfoFrame_I2.tga", 61538, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\BaulFrame_I1.tga", 61539, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\BaulFrame_I2.tga", 61540, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\ShopFrame_I1.tga", 61541, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\newSytemButton.tga", 61542, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\ShopFrame_I2.tga", 61543, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\StoreFrame_I1.tga", 61544, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Interface\\GFx\\ex700\\Main_IE.tga", 31293, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Main_IE_Exp.tga", 59000, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Main_I1.tga", 31296, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Main_I4.jpg", 31300, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Main_I5.jpg", 31299, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\newui_skillbox2.tga", 31313, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\newui_skillbox.tga", 31312, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Main_Skillbox.tga", 51500, GL_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("Interface\\GFx\\ex700\\guege_mp.tga", 31296, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\guege_mp_1.tga", 51501, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\guege_hp_green.tga", 31297, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\guege_hp.tga", 31298, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\guege_hp_1.tga", 51502, GL_LINEAR, GL_CLAMP, 1, 0);
		goto LOAD_GFX;
	case 4:
		LoadBitmapA("Interface\\GFx\\Legends\\Main_IE.tga", 31293, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\Main_I3.tga", 31298, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\guege_mp.tga", 31296, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\guege_mp_1.tga", 51501, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\guege_hp_green.tga", 31297, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\guege_hp.tga", 31298, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\guege_hp_1.tga", 51502, GL_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("Interface\\GFx\\Legends\\Main_I5.jpg", 31299, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\Main_I4.jpg", 31300, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Interface\\GFx\\Legends\\newui_skillbox2.tga", 31313, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\newui_skillbox.tga", 31312, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\Main_Skillbox.tga", 51500, GL_LINEAR, GL_CLAMP, 1, 0);
LOAD_GFX:
		LoadBitmapA("Interface\\GFx\\Buttom_empty_small.tga", 61525, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\newui_number1.tga", 6829, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\chat_bg01.tga", 61550, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\chat_bg02.tga", 61551, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\chat_bg03.tga", 61534, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Chat_I5.tga", 61548, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\newui_chat_back.tga", 61549, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Main_IE_Buttons.tga", 0x901, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\skill_render.tga", 61546, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\winPet_I1.tga", 61545, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\item_pbtnbg.tga", 61547, GL_LINEAR, GL_CLAMP, 1, 0);
		//-- Folder MacroUI
		LoadBitmapA("Interface\\GFx\\MacroUI\\MacroUI_Main.tga", 51550, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\MacroUI\\MacroUI_BSetup.tga", 51546, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\MacroUI\\MacroUI_BStart.tga", 51547, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\MacroUI\\MacroUI_Stop.tga", 51548, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\MacroUI\\MacroUI_Bar.jpg", 51549, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\MacroUI\\MacroUI_Menu.tga", 51553, GL_LINEAR, GL_CLAMP, 1, 0);
		//-- Botones del Main
		LoadBitmapA("Custom\\Interface\\none.tga", 31303, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31304, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31305, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31306, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31307, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Custom\\Interface\\none.tga", 51522, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31294, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31295, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31292, GL_LINEAR, GL_CLAMP, 1, 0);
		
		LoadBitmapA("Interface\\GFx\\ex700\\newSytemButton.tga", 61542, GL_LINEAR, GL_CLAMP, 1, 0);

		break;
	}
		LoadBitmapA("Custom\\Interface\\TimeBar.tga", 0x787F, 0x2601, 0x2901, 1, 0);

	if( gProtect.m_MainInfo.DisableEffectRemake == 0 )
	{
		pLoadImage("Effect\\flare01.jpg", 52002, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\flareRed.jpg", 52230, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\JointLaser01.jpg", 52224, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\hikorora.jpg", 52379, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\flareBlue.jpg", 52229, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\bostar3_R.jpg", 32614, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\line_of_big_R.jpg", 32772, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\flare01.jpg", 42134, GL_LINEAR, GL_REPEAT, 1, 0);      
		//--
	}
	LoadBitmapA("Custom\\Desig\\dong.tga", 531020, GL_LINEAR, GL_REPEAT, 1, 0);
	LoadBitmapA("Custom\\Desig\\mo.tga", 531021, GL_LINEAR, GL_REPEAT, 1, 0);
	LoadBitmapA("Custom\\Desig\\giftboxnotice.tga", 531026, GL_LINEAR, GL_REPEAT, 1, 0);
	//--
	pLoadImage("Custom\\Interface\\Party_info_block.tga", ex_INFO_2, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\newui_cha_textbox03.tga", ex_TEXT_BOX3, 0x2601, 0x2900, 1, 0);
//	JGetLayer.BlindTextureLayer( );
	if(gProtect.m_MainInfo.DisableCustomCloack == 0)
	{
		gCloak.LoadTexture();
	}
	//--
	pLoadSomeForm();
	gEmojis.LoadImages();
}

//void Interface::WindowsKG(){
//	if (gProtect.m_MainInfo.CustomInterfaceType >= 0){
//		char interaltas[500];
//		if (gInterface.validar == 0){
//			if (gInterface.ultimo_Ping > 0){
//				sprintf_s(interaltas, sizeof(interaltas), " %s || Player: %s || Level: %d || Reset: %d || Coins: %d", gProtect.m_MainInfo.WindowName, gObjUser.lpPlayer->Name, gObjUser.lpPlayer->Level, ViewReset, Coin1);
//			}
//			else{
//				sprintf_s(interaltas, sizeof(interaltas), " %s || Player: %s || Level: %d || Reset: %d ||Coins: %d", gProtect.m_MainInfo.WindowName, gObjUser.lpPlayer->Name, gObjUser.lpPlayer->Level, ViewReset, Coin1);
//			}
//			SetWindowText(pGameWindow, interaltas);
//
//		}
//	}
//}
void Interface::BindObject(short MonsterID, DWORD ModelID, float Width, float Height, float X, float Y)
{
	this->Data[MonsterID].EventTick	= 0;
	this->Data[MonsterID].OnClick	= false;
	this->Data[MonsterID].OnShow	= false;
	this->Data[MonsterID].ModelID	= ModelID;
	this->Data[MonsterID].Width		= Width;
	this->Data[MonsterID].Height	= Height;
	this->Data[MonsterID].X			= X;
	this->Data[MonsterID].Y			= Y;
	this->Data[MonsterID].MaxX		= X + Width;
	this->Data[MonsterID].MaxY		= Y + Height;
	this->Data[MonsterID].Attribute	= 0;

}



void Interface::DrawGUI(short ObjectID, float PosX, float PosY)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= PosX;
		this->Data[ObjectID].Y		= PosY;
		this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;
	}

	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawGUI2(short ObjectID, float PosX, float PosY)
{
	this->Data[ObjectID].X		= PosX;
	this->Data[ObjectID].Y		= PosY;
	this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;

	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawGUI3(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	this->Data[ObjectID].X		= PosX;
	this->Data[ObjectID].Y		= PosY;
	this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;

	RenderBitmap(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height,0,0,ScaleX,ScaleY,1,1,0);
}

void Interface::DrawIMG(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= PosX;
		this->Data[ObjectID].Y		= PosY;
		this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;
	}

	RenderBitmap(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height,0,0,ScaleX,ScaleY,1,1,0);
}

void Interface::ResetDrawIMG(short ObjectID)
{
	if( this->Data[ObjectID].X != -1 || this->Data[ObjectID].Y != -1 )
	{
		this->Data[ObjectID].X		= -1;
		this->Data[ObjectID].Y		= -1;
		this->Data[ObjectID].MaxX	= -1;
		this->Data[ObjectID].MaxY	= -1;
	}
}

void Interface::Work()
{
//	gInterface.DrawNewsWindow();
	gObjUser.Refresh();
	gInterface.DrawMenuTrash();
	gInterface.DrawMenuTrash_Warning();
	jCRenderRuud.CheckOpen();
	
	if(gObjUser.lpViewPlayer->WeaponFirstSlot >= ITEM2(4,0) && gObjUser.lpViewPlayer->WeaponFirstSlot <= ITEM2(4,255)
		||gObjUser.lpViewPlayer->WeaponSecondSlot >= ITEM2(4,0) && gObjUser.lpViewPlayer->WeaponSecondSlot <= ITEM2(4,255))
	{
		gInterface.PetY = 38.0f;
		
	}
	else
	{
		gInterface.PetY = 26.0f;
	}

	if(gObjUser.lpViewPlayer->PetSlot!= -1)
	{
		gInterface.PetX = 61.0f;
	}else
	{
		gInterface.PetX = 0;
	}
#if WIDE_SCREEN ==0
	if(gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{	gInterface.DrawInterfaceDragonLS3();
		gInterface.DrawInterfaceDragonRS3();
	}
#endif

	gCustomJewelBank.DrawJewelBankWindow();
	//gInterface.DrawMiniMap();
	gRenderMap.AutoSendMove();
	gInterface.DrawTimeUI();
	gInterface.DrawPartySearchWindow();
	gInterface.DrawPartySettingsWindow();
	gInterface.DrawVaultWindow();
	gInterface.DrawChangingClassWindow();
	gInterface.DrawLuckyWheel();
	gInterface.DrawChangeResetWindow();
	gInterface.DrawSmithItem();
	//gInterface.WindowsKG();
	gInterface.WindowDetail();
	//SmoothCamera.Camera();
		//gBuyVip.Draw();
//if (gProtect.m_MainInfo.SistemFlag == 1)
//	{
////ThueFlag.Draw(); //Sitema Flag
//	}
	
	gCustomRanking.DrawRankPanelWindow();

	gCustomEventTime.DrawEventTimePanelWindow();
	
	ReconnectMainProc();
	gInterface.DrawVipWindow();

	gInterface.DrawMenu();

	gInterface.DrawMenuOpen();

	gInterface.DrawMenuOpenTwo();

	gCustomCommandInfo.DrawCommandWindow();

	gInterface.DrawConfirmOpen();

	if(gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
	{
		gInterface.DrawInterfaceCustom();
	}

	pDrawInterface();
	#if WIDE_SCREEN ==0

	if(gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		
		if(gProtect.m_MainInfo.CustomInterfaceType == 1)
		{
			gInterface.DrawInterface97Menu();
		}
		if(gProtect.m_MainInfo.CustomInterfaceType == 2)
		{
			gInterface.DrawInterfaceS2Menu();
		}
	}
#endif
	if( GetForegroundWindow() == pGameWindow )
	{
		if (GetKeyState(VK_SNAPSHOT) < 0) 
		{
			gInterface.DrawLogo(1); 
		}
		if (GetKeyState(VK_END) & 0x4000) 
		{
			if((GetTickCount()-gInterface.Data[eVip_MAIN].EventTick) > 300)
			{
				if (gInterface.CheckVipWindow())
				{
					gInterface.Data[eVip_MAIN].EventTick = GetTickCount();
					gInterface.CloseVipWindow();
				}
				else
				{
					gInterface.Data[eVip_MAIN].EventTick = GetTickCount();
					gInterface.CloseCustomWindow();
					gInterface.OpenVipWindow();
				}
			}
		}
		#if(SKIN)
	if (gProtect.m_MainInfo.SistemSkin == 1)
	{
	RentSkin.Draw();
	}
#endif

#if(DAILY)
	if (gProtect.m_MainInfo.DailyReward == 1)
	{
	DailyReward.Draw();
	}
#endif
#if FLAG
	if (gProtect.m_MainInfo.SistemFlag == 1)
	{
	ThueFlag.Draw(); //Sitema Flag
	}
#endif

		if (GetKeyState('H') & 0x4000) 
		{
			gCustomEventTime.OpenWindow();
		}
		if (GetKeyState('L') & 0x4000) 
		{
			gInterface.DrawLuckyWheel();
		}

	/*	if (GetKeyState(VK_F3) & 0x4000)
		{
		if (GetForegroundWindow() == pGameWindow && !gInterface.CheckWindow(ObjWindow::ChatWindow))
		{
		gInterface.Data[eMAIN_ThueFlag].Open();
		ThueFlag.SendRequest(0x0, 0);
		gBuyVip.OpenTestDelay = GetTickCount();
		}
	}
*/
		//		if (GetKeyState(VK_F3) & 0x4000 && GetTickCount() >= gBuyVip.OpenTestDelay + 250)
		//{
		//	if (GetForegroundWindow() == pGameWindow && !gInterface.CheckWindow(ObjWindow::ChatWindow))
		//	{
		//		gInterface.Data[eMAIN_ThueFlag].Open();
		//		//ThueFlag.SendRequest(0x0, 0);

		//		gBuyVip.OpenTestDelay = GetTickCount();
		//	}
		//}
		if (GetKeyState('J') & 0x4000) 
		{
			gCustomJewelBank.OpenWindow();
		}
#if DAILY
		if (GetKeyState('Y') & 0x4000 && GetTickCount() >= gCustomRanking.OpenTestDelay + 250)
		{
			if (GetForegroundWindow() == pGameWindow && !gInterface.CheckWindow(ObjWindow::ChatWindow))
			{
				DailyReward.ToggleWindow(true);
				gCustomRanking.OpenTestDelay = GetTickCount();
			}
		}
#endif
#if FLAG
		if (gProtect.m_MainInfo.SistemFlag == 1)
	{
		if (GetKeyState(VK_F3) & 0x4000 && GetTickCount() >= gCustomBuyVip.OpenTestDelay + 250)
		{
			if (GetForegroundWindow() == pGameWindow && !gInterface.CheckWindow(ObjWindow::ChatWindow))
			{
				gInterface.Data[eMAIN_ThueFlag].Open();
				ThueFlag.SendRequest(0x0, 0);

				gCustomBuyVip.OpenTestDelay = GetTickCount();
			}
		}
		}
#endif
		if (GetKeyState('O') & 0x4000) 
		{
			gInterface.OpenConfig(0);
		}
		if (GetKeyState(VK_UP) & 0x4000) 
		{
			gInterface.OpenConfig(1);
		}
		else if (GetKeyState(VK_DOWN) & 0x4000) 
		{
			gInterface.OpenConfig(1);
		}
		//if (GetKeyState(VK_F6) & 0x4000) 
		//{
		//	gInterface.SwitchChatExpand();
		//}
		if (GetKeyState(VK_F8) & 0x4000) 
		{
			gCustomRanking.OpenWindow();
		}
		if (GetKeyState(VK_F10) & 0x4000) 
		{
			gInterface.SwitchCamera();
		}
		if (GetKeyState(VK_F11) & 0x4000) 
		{
			gInterface.CameraInit();
		}
		if (GetKeyState(VK_F12) & 0x4000) 
		{
			if( gTrayMode.TempWindowProc == NULL )
			{
				gTrayMode.TempWindowProc = SetWindowLong(pGameWindow, GWL_WNDPROC, (long)gController.Window);
			}
			// ----
			gTrayMode.SwitchState();
		}
		if (GetKeyState(VK_ESCAPE) < 0) 
		{
			if (gInterface.Data[eCommand_MAIN].OnShow == true)
			{
				gInterface.Data[eCommand_MAIN].OnShow = false;
				
				if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
				{
					pSetCursorFocus = false;
				}
			}

			if (gInterface.Data[eRankPANEL_MAIN].OnShow == true)
			{
				gInterface.Data[eRankPANEL_MAIN].OnShow = false;
				
				if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
				{
					pSetCursorFocus = false;
				}
			}

			if (gInterface.Data[eEventTimePANEL_MAIN].OnShow == true)
			{
				gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;
				
				if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
				{
					pSetCursorFocus = false;
				}
			}

			if (gInterface.CheckVipWindow())
			{
				gInterface.CloseVipWindow();
			}

			if (gInterface.CheckMenuWindow())
			{
				gInterface.CloseMenuWindow();
			}

			if (gInterface.CheckMenuWindowTwo())
			{
				gInterface.CloseMenuWindowTwo();
			}

			if (gInterface.CheckVaultWindow())
			{
				gInterface.CloseVaultWindow();
			}

			if (gInterface.Data[eSMITH_MAIN].OnShow == true)
			{
				gInterface.Data[eSMITH_MAIN].OnShow = false;
				pSetCursorFocus = false;
		    }


			gInterface.Data[ePARTYSETTINGS_MAIN].Close();
			gInterface.Data[ePARTYSEARCH_MAIN].Close();
			gInterface.Data[eCHANGINGCLASS_MAIN].Close();
			gInterface.Data[eLuckyWheelMain].Close();
			gInterface.LuckyWheelStateclose();
			gInterface.Data[eCHANGE_RESET_CLOSE].Close();
		}


	}

//	gCRuudShop.RuudShop();

	gInterface.DrawLogo(0);
	#if SKIN
	gInterface.SetCursorFocus();
#endif
	#if(DEV_PLAYERSHOP)
//	g_ItemMarket.DrawMain();
#endif
}

void Interface::SwitchMiniMap()
{
	if((GetTickCount() - gInterface.Data[eNULL_MAP].EventTick) < 1000 ||this->CheckWindow(ChatWindow))
	{
		return;
	}

	gInterface.Data[eNULL_MAP].EventTick = GetTickCount();

	if (MiniMap != 0)
	{
		gInterface.DrawMessage(1, "MiniMap Window [OFF]");
		MiniMap = 0;
		WritePrivateProfileStringA("Graphics","MiniMap","0","./Settings.ini");
	}
	else 
	{
		gInterface.DrawMessage(1, "MiniMap Window [ON]");
		MiniMap = 1;
		WritePrivateProfileStringA("Graphics","MiniMap","1","./Settings.ini");
	}
}

void Interface::DrawTimeUI()
{

	if( !this->Data[eTIME].OnShow )
	{
		return;
	}

		if(TimerBar == 0 || (this->CheckWindow(ObjWindow::CashShop)|| this->CheckWindow(ObjWindow::CommandWindow)|| this->CheckWindow(ObjWindow::GensInfo)|| this->CheckWindow(ObjWindow::FriendList)|| this->CheckWindow(ObjWindow::FastMenu)|| this->CheckWindow(ObjWindow::Character)|| this->CheckWindow(ObjWindow::Party)|| this->CheckWindow(ObjWindow::Guild)|| this->CheckWindow(ObjWindow::FullMap) || this->CheckWindow(ObjWindow::SkillTree)
		|| this->CheckWindow(ObjWindow::Inventory) 	|| this->CheckWindow(ObjWindow::Quest)|| this->CheckWindow(ObjWindow::CommandWindow)|| this->CheckWindow(ObjWindow::MoveList)|| this->CheckWindow(MuHelper) || this->CheckWindow(ExpandInventory)  || this->CheckWindow(Warehouse) || this->CheckWindow(ExpandWarehouse) ))
	{
		return;
	}
	// -----
	time_t TimeServer, TimeLocal;
	struct tm * ServerT, * LocalT;
	time(&TimeServer);
	time(&TimeLocal);
		// ----
	ServerT = gmtime(&TimeServer);
	// ----
	char ServerTimeName[25] = "ServerTime:";
	char ServerTime[30];

	sprintf(ServerTime, "%2d:%02d:%02d", (ServerT->tm_hour + GMT)%24, ServerT->tm_min, ServerT->tm_sec);
	// -----
	LocalT = localtime(&TimeLocal); 
	// -----
	char LocalTimeName[25] = "LocalTime:";
	char LocalTime[30];
	sprintf(LocalTime, "%2d:%02d:%02d", LocalT->tm_hour, LocalT->tm_min, LocalT->tm_sec);

	this->DrawGUI(eTIME, this->Data[eTIME].X, this->Data[eTIME].Y - 20);

	// ---- servertime
	//this->DrawFormat(eShinyGreen, 550, 5, 50, 1, ServerTimeName);
	//this->DrawFormat(eGold, 600, 5, 50, 1, ServerTime);

	// ----- local time
	this->DrawFormat(eShinyGreen, 550, 14, 50, 1, LocalTimeName);
	this->DrawFormat(eGold, 600, 14, 50, 1, LocalTime);
}

	
int Interface::DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	int LineCount = 0;
	
	char * Line = strtok(Buff, "\n");
	
	while( Line != NULL )
	{
		pDrawColorText(Line, PosX, PosY, Width, 0, Color, 0, Align);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
	
	return PosY;
}

bool Interface::CheckWindow(int WindowID)
{
	return pCheckWindow(pWindowThis(), WindowID);
}
int Interface::CloseWindow(int WindowID)
{
	return pCloseWindow(pWindowThis(), WindowID);
}
int Interface::OpenWindow(int WindowID)
{
	return pOpenWindow(pWindowThis(), WindowID);
}

bool Interface::IsWorkZone2(float X, float Y, float MaxX, float MaxY)
{
	if ((gObjUser.m_CursorX < X || gObjUser.m_CursorX > MaxX)
		|| (gObjUser.m_CursorY < Y || gObjUser.m_CursorY > MaxY))
	{
		return false;
	}
	// ----
	return true;
}
bool Interface::IsWorkZone2(float X, float Y, float MaxX, float MaxY, bool a5)
{
	if (a5) 
	{
		if ((pCursorX < X || pCursorX > X + MaxX) || (pCursorY < Y || pCursorY > Y + MaxY))
			return false;
		return true;
	}
	if ((pCursorX < X || pCursorX > MaxX) || (pCursorY < Y || pCursorY > MaxY))
		return false;
	return true;
}
#if(FLAG)
bool Interface::IsWorkZone4(float x, float y, float x2, float y2)
{
	bool result = GetForegroundWindow() == pGameWindow && pCursorX >= x && pCursorX <= x + x2 && pCursorY >= y && pCursorY <= y + y2;
	return result;
}
#endif

bool Interface::IsWorkZone(short ObjectID)
{
	if( (pCursorX < this->Data[ObjectID].X || pCursorX > this->Data[ObjectID].MaxX) || (pCursorY < this->Data[ObjectID].Y || pCursorY > this->Data[ObjectID].MaxY) )
		return false;

	return true;
}

float Interface::GetResizeX(short ObjectID)
{
	if( pWinWidth == 800 )
	{
		return this->Data[ObjectID].X + 16.0;
	}
	else if( pWinWidth != 1024 )
	{
		return this->Data[ObjectID].X - 16.0;
	}
	
	return this->Data[ObjectID].X;
}

int Interface::DrawToolTip(int X, int Y, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	return pDrawToolTip(X, Y, Buff);
	//Tamaño del texto 15, minúsculas, fondo negro, centrado
    HFONT TextFont = CreateFontA(15, 0, 0, 0, 400, 0, 0, 0, 0x1, 0, 0, 3, 0, "GameMaster");
    pSetTextFont(pTextThis(), TextFont); //set font
    //pUnknow00420080(pTextThis(), -1); //
    //pUnknow004200F0(pTextThis(), 0); 
    pSetTextColor(pTextThis(), 255, 0, 0, 255);
    pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 60);
    pDrawText(pTextThis(), 50, 200, "http://tuservermu.com.ve/", 150, 0, (LPINT)3, 0);


    //Tamaño del texto 15, texto en negrita, fondo blanco azul, centrado
    HFONT TextFontBold = CreateFontA(15, 0, 0, 0, 700, 0, 0, 0, 0x1, 0, 0, 3, 0, "GameMaster");
    pSetTextFont(pTextThis(), TextFontBold); //set font


    pSetTextColor(pTextThis(), 255, 255, 255, 255);
    pSetBackgroundTextColor(pTextThis(), 0, 255, 0, 80);
    pDrawText(pTextThis(), 50, 220, "http://Tuservermu.com.ve/", 150, 0, (LPINT)3, 0);


    //Tamaño del texto 15, texto en negrita, sin fondo verde, alineación izquierda
    pSetTextColor(pTextThis(), 0, 0, 255, 255);
    pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
    pDrawText(pTextThis(), 50, 240, "http://tuservermu.com.ve/", 150, 0, (LPINT)0, 0);

    //Heredar el antiguo pTextThis ha sido configurado
    pDrawText(pTextThis(), 50, 260, "http://tuservermu.com.ve/", 150, 0, (LPINT)0, 0);

    //Get và draw dòng 1B4 = 436 trong file text.bmd (text_eng.bmd dependiendo del idioma)
    pDrawText(pTextThis(), 50, 280, pGetTextLine(pTextLineThis, 0x1B4), 0, 0, (LPINT)0, 0);
    
    
    DeleteObject(TextFont);
    DeleteObject(TextFontBold);
}
//void Interface::DrawNewsWindow()
//{
//	if(gProtect.m_MainInfo.CustomInterfaceType == 3)
//	{
//		if( !this->Data[eNEWS_MAIN].OnShow )
//		{
//			return;
//		}
//		
//		float MainWidth			= 230.0;
//		float MainHeight		= 313.0;
//		float StartY			= 100.0;
//		float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
//		float MainCenter		= StartX + (MainWidth / 3);
//		float ButtonX			= MainCenter - (29.0 / 2);
//		
//		this->DrawGUI(eNEWS_TITLE, StartX, StartY);
//		this->DrawGUI(eNEWS_FOOTER, StartX, StartY);
//		gCentral.PrintDropBox(StartX, StartY, MainWidth, MainHeight, 0, 0);
//		this->DrawGUI(eNEWS_CLOSE, StartX + MainWidth - this->Data[eNEWS_CLOSE].Width, this->Data[eNEWS_TITLE].Height + this->Data[eNEWS_CLOSE].Height + 2);
//
//		if( this->IsWorkZone2(eNEWS_CLOSE) )
//		{
//			DWORD Color = eGray100;
//			
//			if( this->Data[eNEWS_CLOSE].OnClick )
//			{
//				Color = eGray150;
//			}
//			
//			this->DrawColoredGUI(eNEWS_CLOSE, this->Data[eNEWS_CLOSE].X, this->Data[eNEWS_CLOSE].Y, Color);
//			this->DrawToolTip(this->Data[eNEWS_CLOSE].X + 5, this->Data[eNEWS_CLOSE].Y + 25, "Close");
//		}
//		
//		this->DrawFormat(eGold, StartX + 10, 110, 210, 3, "News Board");
//		
//		if( this->Data[eNEWS_MAIN].Attribute == 0 )
//		{
//			for( int i = 0; i < gNewsBoard.m_LoadedCount; i++ )
//			{
//				this->DrawGUI(eNEWS_INFOBG, StartX + 30, 140 + (i * 21));
//				
//				if( IsWorkZone2(StartX + 30, 140 + (i * 21), StartX + 200, 160 + (i * 21), true) )
//				{
//					this->DrawColoredGUI(eNEWS_INFOBG, StartX + 30,  140 + (i * 21), pMakeColor(255, 204, 20, 200));
//				}
//				
//				this->DrawFormat(eGold, StartX + 18, 142 + (i * 21), 65, 3, gNewsBoard.m_Data[i].Title.Date);
//				this->DrawFormat(eOrange, StartX + 18, 148 + (i * 21), 65, 3, gNewsBoard.m_Data[i].Title.Time);
//				this->DrawFormat(eWhite, StartX + 80, 145 + (i * 21), 190, 1, gNewsBoard.m_Data[i].Title.Text);
//			}
//			
//			this->DrawFormat(eBlue, StartX + 8, 130, 210, 3, "Last refresh: %d min. ago", gNewsBoard.m_LastRefreshMin);
//		}
//		else
//		{
//			BYTE ID = this->Data[eNEWS_MAIN].Attribute - 10;
//			
//			this->DrawGUI(eNEWS_INFOBG, StartX + 30, 140);
//			this->DrawFormat(eGold, StartX + 18, 142, 65, 3, gNewsBoard.m_Data[ID].Title.Date);
//			this->DrawFormat(eOrange, StartX + 18, 148, 65, 3, gNewsBoard.m_Data[ID].Title.Time);
//			this->DrawFormat(eWhite, StartX + 80, 145, 190, 1, gNewsBoard.m_Data[ID].Title.Text);
//			this->DrawFormat(eWhite, StartX + 15, 170, 200, 1, gNewsBoard.m_Data[ID].Text);
//			
//			this->DrawGUI(eNEWS_BACK, ButtonX, 341 + 10);
//			this->DrawFormat(eWhite, StartX + 8, 341 + 20, 210, 3, "Back");
//			this->DrawGUI(eNEWS_DIV, StartX, 341 - 10);
//			
//
//			if( IsWorkZone2(eNEWS_BACK) )
//			{
//				DWORD Color = eGray100;
//				
//				if( this->Data[eNEWS_BACK].OnClick )
//				{
//					Color = eGray150;
//				}
//				
//				this->DrawColoredGUI(eNEWS_BACK, this->Data[eNEWS_BACK].X, this->Data[eNEWS_BACK].Y, Color);
//			}
//			
//			this->DrawFormat(eBlue, StartX + 8, 130, 210, 3, "Last page refresh: %d min. ago", gNewsBoard.m_Data[ID].LastRefreshMin);
//		}
//	}
//	else
//	{
//		if( !this->Data[eNEWS_MAIN].OnShow )
//		{
//			return;
//		}
//		
//		float MainWidth			= 230.0;
//		float MainHeight		= 313.0;
//		float StartY			= 100.0;
//		float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
//		float MainCenter		= StartX + (MainWidth / 3);
//		float ButtonX			= MainCenter - (29.0 / 2);
//		
//		this->DrawGUI(eNEWS_MAIN, StartX, StartY + 2);
//		this->DrawGUI(eNEWS_TITLE, StartX, StartY);
//		StartY = this->DrawRepeatGUI(eNEWS_FRAME, StartX, StartY + 67.0, 13);
//		this->DrawGUI(eNEWS_FOOTER, StartX, StartY);
//		this->DrawGUI(eNEWS_CLOSE, StartX + MainWidth - this->Data[eNEWS_CLOSE].Width, this->Data[eNEWS_TITLE].Height + this->Data[eNEWS_CLOSE].Height + 2);
//		
//		if( this->IsWorkZone2(eNEWS_CLOSE) )
//		{
//			DWORD Color = eGray100;
//			
//			if( this->Data[eNEWS_CLOSE].OnClick )
//			{
//				Color = eGray150;
//			}
//			
//			this->DrawColoredGUI(eNEWS_CLOSE, this->Data[eNEWS_CLOSE].X, this->Data[eNEWS_CLOSE].Y, Color);
//			this->DrawToolTip(this->Data[eNEWS_CLOSE].X + 5, this->Data[eNEWS_CLOSE].Y + 25, "Close");
//		}
//		
//		this->DrawFormat(eGold, StartX + 10, 110, 210, 3, "News Board");
//		
//		if( this->Data[eNEWS_MAIN].Attribute == 0 )
//		{
//			for( int i = 0; i < gNewsBoard.m_LoadedCount; i++ )
//			{
//				this->DrawGUI(eNEWS_INFOBG, StartX + 30, 140 + (i * 21));
//				
//				if( IsWorkZone(StartX + 30, 140 + (i * 21), StartX + 200, 160 + (i * 21), true) )
//				{
//					this->DrawColoredGUI(eNEWS_INFOBG, StartX + 30,  140 + (i * 21), pMakeColor(255, 204, 20, 200));
//				}
//				
//				this->DrawFormat(eGold, StartX + 18, 142 + (i * 21), 65, 3, gNewsBoard.m_Data[i].Title.Date);
//				this->DrawFormat(eOrange, StartX + 18, 148 + (i * 21), 65, 3, gNewsBoard.m_Data[i].Title.Time);
//				this->DrawFormat(eWhite, StartX + 80, 145 + (i * 21), 190, 1, gNewsBoard.m_Data[i].Title.Text);
//			}
//			
//			this->DrawFormat(eBlue, StartX + 8, 130, 210, 3, "Last refresh: %d min. ago", gNewsBoard.m_LastRefreshMin);
//		}
//		else
//		{
//			BYTE ID = this->Data[eNEWS_MAIN].Attribute - 10;
//			
//			this->DrawGUI(eNEWS_INFOBG, StartX + 30, 140);
//			this->DrawFormat(eGold, StartX + 18, 142, 65, 3, gNewsBoard.m_Data[ID].Title.Date);
//			this->DrawFormat(eOrange, StartX + 18, 148, 65, 3, gNewsBoard.m_Data[ID].Title.Time);
//			this->DrawFormat(eWhite, StartX + 80, 145, 190, 1, gNewsBoard.m_Data[ID].Title.Text);
//			this->DrawFormat(eWhite, StartX + 15, 170, 200, 1, gNewsBoard.m_Data[ID].Text);
//			
//			this->DrawGUI(eNEWS_BACK, ButtonX, this->Data[eNEWS_FOOTER].Y + 10);
//			this->DrawFormat(eWhite, StartX + 8, this->Data[eNEWS_FOOTER].Y + 20, 210, 3, "Back");
//			this->DrawGUI(eNEWS_DIV, StartX, this->Data[eNEWS_FOOTER].Y - 10);
//			
//			if( IsWorkZone(eNEWS_BACK) )
//			{
//				DWORD Color = eGray100;
//				
//				if( this->Data[eNEWS_BACK].OnClick )
//				{
//					Color = eGray150;
//				}
//				
//				this->DrawColoredGUI(eNEWS_BACK, this->Data[eNEWS_BACK].X, this->Data[eNEWS_BACK].Y, Color);
//			}
//			
//			this->DrawFormat(eBlue, StartX + 8, 130, 210, 3, "Last page refresh: %d min. ago", gNewsBoard.m_Data[ID].LastRefreshMin);
//		}
//	}
//}
//bool Interface::EventNewsWindow_Main(DWORD Event)
//{
//	float MainWidth			= 230.0;
//	float MainHeight		= 313.0;
//	float StartY			= 100.0;
//	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
//	
//	for( int i = 0; i < gNewsBoard.m_LoadedCount; i++ )
//	{
//		if( this->IsWorkZone(StartX + 30, 140 + (i * 21), StartX + 200, 161 + (i * 21), true) )
//		{
//			if( Event == WM_LBUTTONDOWN && this->Data[eNEWS_MAIN].Attribute == 0 )
//			{
//				this->Data[eNEWS_MAIN].Attribute = i + 10;
//				gNewsBoard.ReqOpenItem(i);
//			}
//		}
//	}
//	
//	this->EventNewsWindow_Close(Event);
//	this->EventNewsWindow_Back(Event);
//	return true;
//}
//bool Interface::EventNewsWindow_Close(DWORD Event)
//{
//	DWORD CurrentTick	= GetTickCount();
//	DWORD Delay			= (CurrentTick - this->Data[eNEWS_CLOSE].EventTick);
//	
//	if( !this->Data[eNEWS_MAIN].OnShow || !IsWorkZone(eNEWS_CLOSE) )
//	{
//		return false;
//	}
//	
//	if( Event == WM_LBUTTONDOWN )
//	{
//		this->Data[eNEWS_CLOSE].OnClick = true;
//		return true;
//	}
//	
//	this->Data[eNEWS_CLOSE].OnClick = false;
//	
//	if( Delay < 500 )
//	{
//		return false;
//	}
//	
//	this->Data[eNEWS_CLOSE].EventTick	= GetTickCount();
//	this->Data[eNEWS_MAIN].Attribute	= 0;
//	this->CloseNewsWindow();
//	
//	return false;
//}
//bool Interface::EventNewsWindow_Back(DWORD Event)
//{
//	DWORD CurrentTick	= GetTickCount();
//	DWORD Delay			= (CurrentTick - this->Data[eNEWS_BACK].EventTick);
//	
//	if( !this->Data[eNEWS_MAIN].OnShow || !IsWorkZone(eNEWS_BACK) )
//	{
//		return false;
//	}
//	
//	if( Event == WM_LBUTTONDOWN )
//	{
//		this->Data[eNEWS_BACK].OnClick = true;
//		return true;
//	}
//	
//	this->Data[eNEWS_BACK].OnClick = false;;
//	
//	if( Delay < 500 )
//	{
//		return false;
//	}
//	
//	this->Data[eNEWS_BACK].EventTick = GetTickCount();
//	this->Data[eNEWS_MAIN].Attribute = 0;
//	
//	return false;
//}
int Interface::DrawMessage(int Mode, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	return pDrawMessage(Buff, Mode);
}

void Interface::DrawVipWindow()
{

	if( !this->Data[eVip_MAIN].OnShow )
	{
		return;
	}

	if( gProtect.m_MainInfo.EnableVipShop != 1 )
	{
		this->CloseVipWindow();
		return;
	}

	if (this->CheckWindow(ObjWindow::MoveList) || this->CheckWindow(ObjWindow::CashShop) || this->CheckWindow(ObjWindow::SkillTree) || this->CheckWindow(ObjWindow::FullMap)
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(ExpandInventory) 
		&& this->CheckWindow(Store)) 
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(Warehouse) 
		&& this->CheckWindow(ExpandWarehouse)) )
	{
		CloseVipWindow();
		return;
	}
	int JCResto;
	#if(WIDE_SCREEN == 1)
	JCResto =  pWinWidth / pWinHeightReal/ 2 -320;
#else
	JCResto =0;
#endif
	// ----
	float MainWidth			= 230.0;
	float MainHeight		= 320.0;
	float StartBody			= ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartY			= ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartX			= JCResto+(MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (float)(29.0 / 2);
	// ----
	gCentral.PrintDropBox(StartX, StartY, MainWidth, MainHeight, 0, 0);
	// ----
	this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 10, 210, 3, gCustomMessage.GetMessage(5));
	int LineY = this->DrawFormat(eWhite, (int)StartX + 30, (int)StartBody + 35, 210, 1, gCustomMessage.GetMessage(6), gObjUser.lpPlayer->Name);
	LineY = this->DrawFormat(eGold, (int)StartX + 30, (int)LineY, 210, 1, gCustomMessage.GetMessage(14));
	LineY = this->DrawFormat(eWhite, (int)StartX + 30, (int)LineY, 210, 1, gCustomMessage.GetMessage(7));
	LineY = this->DrawFormat(eWhite, (int)StartX + 30, (int)LineY, 210, 1, gCustomMessage.GetMessage(8));
	//--
	pDrawGUI(71520, StartX + (MainWidth / 2) - (200 / 2), StartBody + 85, 200, 1); //-- Divisor
	//--
	this->DrawFormat(eGold, (int)StartX + 30, (int)StartBody + 95 - 2, 210, 1, "Plan/Type");
	this->DrawFormat(eGold, (int)StartX + 80, (int)StartBody + 95 - 2 , 210, 1, "+EXP");
	this->DrawFormat(eGold, (int)StartX + 130, (int)StartBody + 95 - 2, 210, 1, "+Drop");
	this->DrawFormat(eGold, (int)StartX + 170, (int)StartBody + 95 - 2, 210, 1, "Time");
	// ----

	if (gProtect.m_MainInfo.VipTypes < 2 || gProtect.m_MainInfo.VipTypes > 3)
	{
		gProtect.m_MainInfo.VipTypes = 3;
	}

	for( int i = 0; i < (int)gProtect.m_MainInfo.VipTypes; i++ )
	{
		this->DrawFormat(eWhite, (int)StartX + 30, (int)StartBody + 110 + (12 * i) - 5, 210, 1, gCustomBuyVip.m_CustomBuyVipInfo[i].VipName);
		// ----
		this->DrawFormat(eWhite, (int)StartX + 80, (int)StartBody + 110 + (12 * i) - 5, 210, 1, "+%d%%", gCustomBuyVip.m_CustomBuyVipInfo[i].Exp);
		// ----
		this->DrawFormat(eWhite, (int)StartX + 130, (int)StartBody + 110 + (12 * i) - 5, 210, 1, "+%d%%", gCustomBuyVip.m_CustomBuyVipInfo[i].Drop);
		// ----
		this->DrawFormat(eWhite, (int)StartX + 170, (int)StartBody + 110 + (12 * i) - 5, 210, 1, "%d day(s)", gCustomBuyVip.m_CustomBuyVipInfo[i].Days);

		pDrawGUI(0x7B5E, StartX + 30, StartY + 110 + (12 * i) + 9 - 5, 82.0, 2.0);
		pDrawGUI(0x7B5E, StartX + 30 + 82, StartY + 110 + (12 * i) + 9 - 5, 82.0, 2.0);
	}

	if (gProtect.m_MainInfo.VipTypes > 2)
	{
	// ---- gold start ------------------------------------
	if (IsWorkZone(eVip_GOLD))
	{
		if (this->Data[eVip_GOLD].OnClick)
			this->DrawButton(eVip_GOLD, StartX + 64, 220, 0, 58);
		else
			this->DrawButton(eVip_GOLD, StartX + 64, 220, 0, 29);
		// ----
		this->DrawFormat(eGold, (int)StartX + 90, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(10));
		this->DrawFormat(eGold, (int)StartX + 120, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(11), gCustomBuyVip.m_CustomBuyVipInfo[2].Coin1);
//		this->DrawFormat(eGold, (int)StartX + 120, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(12), gCustomBuyVip.m_CustomBuyVipInfo[2].Coin2);
//		this->DrawFormat(eGold, (int)StartX + 160, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(13), gCustomBuyVip.m_CustomBuyVipInfo[2].Coin3);
	}
	else
		this->DrawButton(eVip_GOLD, StartX + 64, 220, 0, 0);

	this->DrawFormat(eWhite, (int)StartX + 90, 220 + 9, 160, 1, gCustomMessage.GetMessage(9),gCustomBuyVip.m_CustomBuyVipInfo[2].VipName);

	// ---- gold end ------------------------------------
	}

	pDrawGUI(71520, StartX + (MainWidth / 2) - (200 / 2), 220 + 55, 200, 1); //-- Divisor
}


bool Interface::EventVipWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eVip_CLOSE].EventTick);
	// ----
	if (!this->Data[eVip_MAIN].OnShow || !IsWorkZone(eVip_CLOSE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eVip_CLOSE].OnClick = true;
		return true;
	}
	// ----
	this->Data[eVip_CLOSE].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eVip_CLOSE].EventTick = GetTickCount();
	this->CloseVipWindow();
	// ----
	return false;
}
void Interface::DrawMenuTrash()
{
	if (this->CheckWindow (ObjWindow::Warehouse))
	{
		return;
	}

	if (this->CheckWindow (ObjWindow::Inventory) && this->CheckWindow (ObjWindow::Character))
	{
		this->Data[eTrash_Expanded].OnShow = true;

		float MainWidth = 230.0;

		float MainHeight = 130.0;

		float PosX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);

		this->DrawGUI(eTrash_Expanded, PosX + 212, 365);
		
		if (IsWorkZone(eTrash_Expanded))
		{
			this->DrawToolTip(PosX + 164, 350, "Clear Inventory");
		}
	}
	
	if (this->CheckWindow (ObjWindow::Inventory) )
	{
		if (this->CheckWindow (ObjWindow::Character) )
		{
			return;
		}
	
		else
		{
			this->Data[eTrash].OnShow = true;
		
			float MainWidth = 230.0;

			float MainHeight = 130.0;

			float PosX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);

			this->DrawGUI(eTrash, PosX + 400, 365);
		
			if (IsWorkZone(eTrash))
			{
				this->DrawToolTip(PosX + 364, 350, "Clear Inventory");
			}
		}
	}
}

bool Interface::EventDrawMenuTrash_Open(DWORD Event)
{
	if (this->CheckWindow (ObjWindow::Warehouse))
	{
		return false;
	}

	if ( this->CheckWindow (ObjWindow::Inventory) && this->CheckWindow (ObjWindow::Character) )
	{
		DWORD CurrentTick	= GetTickCount();
		DWORD Delay			= (CurrentTick - this->Data[eTrash_Expanded].EventTick);
	
		if(!this->CheckWindow(ObjWindow::Inventory) &&  this->CheckWindow (ObjWindow::Character) || !IsWorkZone(eTrash_Expanded))
		{
			return false;
		}
	
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eTrash_Expanded].OnClick = true;
			pSetCursorFocus = true;
			return true;
		}
	
		this->Data[eTrash_Expanded].OnClick = false;
		pSetCursorFocus = false;
	
		if( Delay < 500 )
		{
			return false;
		}
	
		this->Data[eTrash_Expanded].EventTick = GetTickCount();

		gInterface.OpenTrashWindow();
	}

	if (this->CheckWindow (ObjWindow::Inventory) )
	{
		if (this->CheckWindow (ObjWindow::Character) )
		{
			return false;
		}
	
		else
		{
			DWORD CurrentTick	= GetTickCount();
			DWORD Delay			= (CurrentTick - this->Data[eTrash].EventTick);
	
			if(!this->CheckWindow(ObjWindow::Inventory) || !IsWorkZone(eTrash))
			{
				return false;
			}
	
			if( Event == WM_LBUTTONDOWN )
			{
				this->Data[eTrash].OnClick = true;
				pSetCursorFocus = true;
				return true;
			}
	
			this->Data[eTrash].OnClick = false;
			pSetCursorFocus = false;
	
			if( Delay < 500 )
			{
				return false;
			}
	
			this->Data[eTrash].EventTick = GetTickCount();

			gInterface.OpenTrashWindow();
		}
	}

	return true;
}

void Interface::DrawMenuTrash_Warning()
{
	if( this->Data[eTrash_MAIN].OnShow )
	{
		pSetCursorFocus = true;
	}

	if( !this->Data[eTrash_MAIN].OnShow )
	{
		return;
	}

	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 80.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	this->DrawGUI(eTrash_MAIN, StartX, StartY + 2);
	this->DrawGUI(eTrash_MAIN, StartX, StartY + 17);
	this->DrawGUI(eTrash_TITLE, StartX, StartY);
	this->DrawGUI(eTrash_FRAME, StartX, StartY + 67);
	this->DrawGUI(eTrash_FRAME, StartX, StartY + 80);
	this->DrawGUI(eTrash_FOOTER, StartX, StartY + 95);

	this->DrawFormat(eGold, StartX + 10, 90, 210, 3, "Clear Invetory");

	this->DrawFormat(eRed, StartX + 10, 115, 210, 3, "WARNING!!!");

	this->DrawFormat(eGold, StartX + 10, 130, 210, 3, "This command clear your inventory ");
	this->DrawFormat(eGold, StartX + 10, 141, 210, 3, "and everything items will be deleted.");

	this->DrawFormat(eWhite, StartX + 10, 156, 210, 3, "Are you sure?");

	this->DrawGUI(eTrash_YES, StartX + 30, StartY + 95);
	this->DrawGUI(eTrash_NO, StartX + 140, StartY + 95);
}

bool Interface::DrawMenuTrash_Warning_Main(DWORD Event)
{
	this->DrawMenuTrash_Warning_Yes(Event);
	this->DrawMenuTrash_Warning_No(Event);
	return true;
}

bool Interface::DrawMenuTrash_Warning_Yes(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eTrash_YES].EventTick);
	
	if( !this->Data[eTrash_MAIN].OnShow || !IsWorkZone(eTrash_YES) )
	{
		return false;
	}
	
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eTrash_YES].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	
	this->Data[eTrash_YES].OnClick = false;
	pSetCursorFocus = false;
	
	if( Delay < 500 )
	{
		return false;
	}
	
	pChatSend("/clearinv"); //Here you change command syntax

	this->CloseTrashWindow();

	return false;
}

bool Interface::DrawMenuTrash_Warning_No(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eTrash_NO].EventTick);
	
	if( !this->Data[eTrash_MAIN].OnShow || !IsWorkZone(eTrash_NO) )
	{
		return false;
	}
	
	if( Event == WM_LBUTTONDOWN )
	{
		pSetCursorFocus = true;
		this->Data[eTrash_NO].OnClick = true;
		return true;
	}
	
	this->Data[eTrash_NO].OnClick = false;
	
	pSetCursorFocus = false;
	
	if( Delay < 500 )
	{
		return false;
	}
	
	this->Data[eTrash_NO].EventTick = GetTickCount();
	
	this->CloseTrashWindow();

	return false;
}
//--
// ----------------------------------------------------------------------------------------------

//bool Interface::EventVipWindow_Bronze(DWORD Event)
//{
//	DWORD CurrentTick = GetTickCount();
//	DWORD Delay = (CurrentTick - this->Data[eVip_BRONZE].EventTick);
//	// ----
//	if (!this->Data[eVip_MAIN].OnShow || !IsWorkZone(eVip_BRONZE))
//	{
//		return false;
//	}
//	// ----
//	if (Event == WM_LBUTTONDOWN)
//	{
//		this->Data[eVip_BRONZE].OnClick = true;
//		return true;
//	}
//	// ----
//	this->Data[eVip_BRONZE].OnClick = false;;
//	// ----
//	if (Delay < 500)
//	{
//		return false;
//	}
//	// ----
//	this->Data[eVip_BRONZE].EventTick = GetTickCount();
//	gCustomBuyVip.BuyStatus(1);
//	this->CloseVipWindow();
//	// ----
//	return false;
//}
//// ----------------------------------------------------------------------------------------------
//
//bool Interface::EventVipWindow_Silver(DWORD Event)
//{
//	DWORD CurrentTick = GetTickCount();
//	DWORD Delay = (CurrentTick - this->Data[eVip_SILVER].EventTick);
//	// ----
//	if (!this->Data[eVip_MAIN].OnShow || !IsWorkZone(eVip_SILVER))
//	{
//		return false;
//	}
//	if (gProtect.m_MainInfo.VipTypes < 2)
//	{
//		return false;
//	}
//	// ----
//	if (Event == WM_LBUTTONDOWN)
//	{
//		this->Data[eVip_SILVER].OnClick = true;
//		return true;
//	}
//	// ----
//	this->Data[eVip_SILVER].OnClick = false;;
//	// ----
//	if (Delay < 500)
//	{
//		return false;
//	}
//	// ----
//	this->Data[eVip_SILVER].EventTick = GetTickCount();
//	gCustomBuyVip.BuyStatus(2);
//	this->CloseVipWindow();
//	// ----
//	return false;
//}

// ----------------------------------------------------------------------------------------------
bool Interface::EventVipWindow_Gold(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eVip_GOLD].EventTick);
	// ----
	if (!this->Data[eVip_MAIN].OnShow || !IsWorkZone(eVip_GOLD))
	{
		return false;
	}
	if (gProtect.m_MainInfo.VipTypes < 3)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eVip_GOLD].OnClick = true;
		return true;
	}
	// ----
	this->Data[eVip_GOLD].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eVip_GOLD].EventTick = GetTickCount();
	gCustomBuyVip.BuyStatus(3);
	this->CloseVipWindow();
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool Interface::EventVipWindow_Main(DWORD Event)
{
	this->EventVipWindow_Close(Event);
	//this->EventVipWindow_Bronze(Event);
	//this->EventVipWindow_Silver(Event);
	this->EventVipWindow_Gold(Event);
	// ----
	return true;
}

float Interface::DrawRepeatGUI(short MonsterID, float X, float Y, int Count)
{
	float StartY = Y;
	// ----
	for( int i = 0; i < Count; i++ )
	{
		pDrawGUI(this->Data[MonsterID].ModelID, X, StartY,
			this->Data[MonsterID].Width, this->Data[MonsterID].Height);
		// ----
		StartY += this->Data[MonsterID].Height;
	}
	// ----
	return StartY;
}

float Interface::DrawRepeatGUIScale(short MonsterID, float X, float Y,float ScaleX, float ScaleY, int Count)
{
	float StartY = Y;
	// ----
	for( int i = 0; i < Count; i++ )
	{
		this->DrawIMG(this->Data[MonsterID].ModelID, X, StartY,ScaleX,ScaleY);
		// ----
		StartY += this->Data[MonsterID].Height;
	}
	// ----
	return StartY;
}

void Interface::DrawButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}

void Interface::DrawButtonRender(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	this->Data[ObjectID].X = PosX;
	this->Data[ObjectID].Y = PosY;
	this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}

void Interface::DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= X;
		this->Data[ObjectID].Y		= Y;
		this->Data[ObjectID].MaxX	= X + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= Y + this->Data[ObjectID].Height;
	}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y, 
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}

void Interface::DrawLogo(bool active)
{
	if (gProtect.m_MainInfo.PrintLogo != 0)
	{

		if (active == 1)
		{
			this->Data[eLogo].EventTick = GetTickCount()+1500;
		}

		if (gInterface.Data[eLogo].EventTick > GetTickCount())
		{
			if (gProtect.m_MainInfo.PrintLogo == 1)
			{
				this->DrawGUI(eLogo, 10, 10);
			}

			if (gProtect.m_MainInfo.PrintLogo == 2)
			{
				this->DrawGUI(eLogo, MAX_WIN_WIDTH - 160, 10);

			}

			if (gProtect.m_MainInfo.PrintLogo == 3)
			{
				this->DrawGUI(eLogo, 10, MAX_WIN_HEIGHT - 144);
			}

			if (gProtect.m_MainInfo.PrintLogo == 4)
			{
				this->DrawGUI(eLogo, MAX_WIN_WIDTH - 160, MAX_WIN_HEIGHT - 144);
			}

			if (gProtect.m_MainInfo.PrintLogo == 5)
			{
				this->DrawGUI(eLogo, (MAX_WIN_WIDTH/2)-(150/2), (MAX_WIN_HEIGHT/2)-(114/2));
			}
		}
	}
}

void Interface::DrawMenu()
{
	if (gProtect.m_MainInfo.CustomMenuSwitch != 1)
	{
		return;
	}

	if (this->Data[eMenu].OnShow)
	{
		this->Data[eMenu].OnShow = false;
	}

	if (this->CheckWindow(ObjWindow::MoveList) || this->CheckWindow(ObjWindow::CashShop) || this->CheckWindow(ObjWindow::SkillTree) || this->CheckWindow(ObjWindow::FullMap)
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(ExpandInventory) 
		&& this->CheckWindow(Store))
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(ExpandInventory) 
		&& this->CheckWindow(Character))
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(Warehouse) 
		&& this->CheckWindow(ExpandWarehouse)) )
	{
		CloseMenuWindow();
		return;
	}
	
	this->Data[eMenu].OnShow = true;
}

bool Interface::EventDrawMenu_Open(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu].EventTick);
	// ----
	if (!this->Data[eMenu].OnShow || !IsWorkZone(eMenu))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		
	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
		this->Data[eMenu].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	
	// ----
	this->Data[eMenu].EventTick = GetTickCount();
	
	if (CheckMenuWindow() /*Nuevo max*/|| gInterface.CheckMenuWindowTwo())
	{
		CloseMenuWindow();
		CloseMenuWindowTwo();
	}
	else
	{
		//CloseCustomWindow();// desactivado de maxvoll
		//OpenMenuWindow();
		OpenWindowMenu();// nuevo de maxvoll
	}
	// ----
	return false;
}

void Interface::OpenWindowMenu()
{

	if (gInterface.Data[eMenu_MAIN].OnShow == true)
	{
		gInterface.Data[eMenu_MAIN].OnShow = false;
		pSetCursorFocus = false;
		return;
	}

	DWORD CurrentTick = GetTickCount();

	gInterface.Data[eMenu_MAIN].EventTick = GetTickCount();
	gInterface.Data[eMenu_MAIN].OnShow = true;

}

void Interface::OpenWindowMenuTwo()
{

	if (gInterface.Data[eMenu_MAINTWO].OnShow == true)
	{
		gInterface.Data[eMenu_MAINTWO].OnShow = false;
		pSetCursorFocus = false;
		return;
	}

	DWORD CurrentTick = GetTickCount();

	gInterface.Data[eMenu_MAINTWO].EventTick = GetTickCount();
	gInterface.Data[eMenu_MAINTWO].OnShow = true;
	gRenderMap.AutoSendMove();


}

void Interface::DrawMenuOpen()
{
	if (gProtect.m_MainInfo.CustomMenuSwitch != 1)
	{
		return;
	}

	if( !this->Data[eMenu_MAIN].OnShow )
	{
		return;
	}
	int JCResto;
	#if(WIDE_SCREEN == 1)
	JCResto =  pWinWidth / pWinHeightReal/ 2 -320;
#else
	JCResto =0;
#endif

	float MainWidth			= 230.0;
	float MainHeight		= 250.0;
	float StartBody			= 30;
	float StartY			= 30;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);

	this->DrawGUI(eMenu_TITLE, JCResto+StartX, StartY);
	this->DrawGUI(eMenu_FOOTER, JCResto+StartX, StartY);

	gCentral.PrintDropBox(JCResto+StartX, StartY, MainWidth, MainHeight, 0, 0);

	this->DrawGUI(eMenu_CLOSE, JCResto+StartX + MainWidth - this->Data[eVip_CLOSE].Width, StartBody);
	// ----
	if (this->IsWorkZone(eMenu_CLOSE))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eMenu_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eVip_CLOSE, this->Data[eMenu_CLOSE].X, StartBody, Color);
		this->DrawToolTip((int)this->Data[eMenu_CLOSE].X + 5, (int)StartBody + 25, "Close");
	}

	if (gInterface.IsWorkZone(eMenu_NEXT))
	{
		DWORD Color = eGray100;
		// ----
		if (gInterface.Data[eMenu_NEXT].OnClick)
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eMenu_NEXT, gInterface.Data[eMenu_NEXT].X, gInterface.Data[eMenu_NEXT].Y, Color);
		this->DrawToolTip((int)this->Data[eMenu_NEXT].X + 5, (int)StartBody + 238, "Next");
	}

	if (gInterface.IsWorkZone(eMenu_PREVIUS))
	{
		DWORD Color = eGray100;
		// ----
		if (gInterface.Data[eMenu_PREVIUS].OnClick)
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eMenu_PREVIUS, gInterface.Data[eMenu_PREVIUS].X, gInterface.Data[eMenu_PREVIUS].Y, Color);
		this->DrawToolTip((int)this->Data[eMenu_PREVIUS].X + 3, (int)StartBody + 238, "Previus");
	}

	gInterface.DrawGUI(eMenu_NEXT, JCResto+ButtonX + 90, (int)StartBody + 210);
	gInterface.DrawGUI(eMenu_PREVIUS, JCResto+ButtonX - 10, (int)StartBody + 210);

	this->DrawFormat(eGold, JCResto+(int)StartX + 10, (int)StartBody + 10, 210, 3, "Menu");

	if(gProtect.m_MainInfo.EnableCoinStatus == 1)
	{
		this->DrawFormat(eGold, JCResto+(int)StartX + 10, (int)StartBody + 35, 210, 3, gCustomMessage.GetMessage(50));

		this->DrawFormat(eWhite, JCResto+(int)StartX + 25, (int)StartBody + 50, 40, 1, gCustomMessage.GetMessage(51));
		this->DrawFormat(eGold, JCResto+(int)StartX + 50, (int)StartBody + 50, 40, 1, "%d",Coin1);

		this->DrawFormat(eWhite,JCResto+ (int)StartX + 90, (int)StartBody + 50, 40, 1, gCustomMessage.GetMessage(52));
		this->DrawFormat(eGold, JCResto+(int)StartX + 115, (int)StartBody + 50, 40, 1, "%d",Coin2);

		this->DrawFormat(eWhite,JCResto+ (int)StartX + 153, (int)StartBody + 50, 40, 1, gCustomMessage.GetMessage(53));
		this->DrawFormat(eGold, JCResto+(int)StartX + 176, (int)StartBody + 50, 40, 1, "%d",Coin3);
	}
	else
	{
		this->DrawFormat(eGold, JCResto+(int)StartX + 10, (int)StartBody + 45, 210, 3, gCustomMessage.GetMessage(54));
	}

	this->DrawGUI(eVip_DIV, JCResto+StartX, StartBody + 60);

	int BtCount		= 0;
	int BtCount2    = 0;
	int BtStart		= StartBody + 78;
	int BtStart2    = StartBody + 78;
	int BtDistance	= 33;

	if (gProtect.m_MainInfo.MenuButtons[0] == 1)//gProtect.m_MainInfo.EnableEventTimeButton
	{
		BtCount++;
	}
	else
	{	
		BtStart	-= 33;
	}
	if (gProtect.m_MainInfo.MenuButtons[1] == 1)//EnableVipShopButton
	{
		BtCount++;
	}
	if (gProtect.m_MainInfo.MenuButtons[2] == 1)//EnableRankingButton
	{
		BtCount++;
	}
	if (gProtect.m_MainInfo.MenuButtons[3] == 1)//EnableCommandButton
	{
		BtCount++;
	}
	// Melo920 Falta el ultimo 4 -> EnableOptionButton



//	if (gProtect.m_MainInfo.EnableEventTimeButton == 1 && gProtect.m_MainInfo.EnableVipShopButton == 1 && gProtect.m_MainInfo.EnableRankingButton == 1 && gProtect.m_MainInfo.EnableCommandButton == 1)
//	{
		if (BtCount2 == 3)
		{
			BtStart2 += 30;
		}
//	}
//	if (gProtect.m_MainInfo.EnableEventTimeButton == 0 && gProtect.m_MainInfo.EnableVipShopButton == 1 && gProtect.m_MainInfo.EnableRankingButton == 1 && gProtect.m_MainInfo.EnableCommandButton == 1)
//	{
		if (BtCount2 == 2)
		{
			BtStart2 += 45;
		}
//	}
//	if (gProtect.m_MainInfo.EnableEventTimeButton == 1 && gProtect.m_MainInfo.EnableVipShopButton == 0 && gProtect.m_MainInfo.EnableRankingButton == 1 && gProtect.m_MainInfo.EnableCommandButton == 1)
//	{
		if (BtCount2 == 2)
		{
			BtStart2 += 45;
		}
//	}
//	if (gProtect.m_MainInfo.EnableEventTimeButton == 1 && gProtect.m_MainInfo.EnableVipShopButton == 1 && gProtect.m_MainInfo.EnableRankingButton == 0 && gProtect.m_MainInfo.EnableCommandButton == 1)
//	{
		if (BtCount2 == 2)
		{
			BtStart2 += 45;
		}
//	}
//	if (gProtect.m_MainInfo.EnableEventTimeButton == 1 && gProtect.m_MainInfo.EnableVipShopButton == 1 && gProtect.m_MainInfo.EnableRankingButton == 1 && gProtect.m_MainInfo.EnableCommandButton == 0)
//	{
		if (BtCount2 == 2)
		{
			BtStart2 += 45;
		}
//	}
//	if (gProtect.m_MainInfo.EnableEventTimeButton == 0 && gProtect.m_MainInfo.EnableVipShopButton == 0 && gProtect.m_MainInfo.EnableRankingButton == 1 && gProtect.m_MainInfo.EnableCommandButton == 1)
//	{
		if (BtCount2 == 1)
		{
			BtStart2 += 60;
		}
//	}
//	if (gProtect.m_MainInfo.EnableEventTimeButton == 0 && gProtect.m_MainInfo.EnableVipShopButton == 1 && gProtect.m_MainInfo.EnableRankingButton == 0 && gProtect.m_MainInfo.EnableCommandButton == 1)
//	{
		if (BtCount2 == 1)
		{
			BtStart2 += 60;
		}
//	}
//	if (gProtect.m_MainInfo.EnableEventTimeButton == 0 && gProtect.m_MainInfo.EnableVipShopButton == 1 && gProtect.m_MainInfo.EnableRankingButton == 1 && gProtect.m_MainInfo.EnableCommandButton == 0)
//	{
		if (BtCount2 == 1)
		{
			BtStart2 += 60;
		}
//	}


//	//Horario eventos
	if (gProtect.m_MainInfo.MenuButtons[0] == 1)//EnableEventTimeButton
	{
	
	if (IsWorkZone(eMenu_OPT1))
	{
		if (this->Data[eMenu_OPT1].OnClick)
			this->DrawButton(eMenu_OPT1, JCResto+StartX + 4, BtStart, 0, 58);
		else
			this->DrawButton(eMenu_OPT1, JCResto+StartX + 4, BtStart, 0, 29);
		// ----
	}
	else
		this->DrawButton(eMenu_OPT1, JCResto+StartX + 4, BtStart, 0, 0);

	this->DrawFormat(eWhite, JCResto+(int)StartX + 4, BtStart + 9, 108, 3, gCustomMessage.GetMessage(25));
	}

//	//Comprar vip
	if (gProtect.m_MainInfo.MenuButtons[1] == 1)//EnableVipShopButton
	{
	
	BtStart += BtDistance;

	if (IsWorkZone(eMenu_OPT2))
	{
		if (this->Data[eMenu_OPT2].OnClick)
			this->DrawButton(eMenu_OPT2,JCResto+ StartX + 4, BtStart, 0, 58);
		else
			this->DrawButton(eMenu_OPT2,JCResto+ StartX + 4, BtStart, 0, 29);
		// ----
	}
	else
		this->DrawButton(eMenu_OPT2, JCResto+StartX + 4, BtStart, 0, 0);

	this->DrawFormat(eWhite, JCResto+(int)StartX + 4, BtStart + 9, 108, 3, gCustomMessage.GetMessage(26));
	}

	//Ranking
	if (gProtect.m_MainInfo.MenuButtons[2] == 1)//EnableRankingButton
	{
	BtStart += BtDistance;

	if (IsWorkZone(eMenu_OPT3))
	{
		if (this->Data[eMenu_OPT3].OnClick)
			this->DrawButton(eMenu_OPT3, JCResto+StartX + 4, BtStart, 0, 58);
		else
			this->DrawButton(eMenu_OPT3, JCResto+StartX + 4, BtStart, 0, 29);
		// ----
	}
	else
		this->DrawButton(eMenu_OPT3, JCResto+StartX + 4, BtStart, 0, 0);

	this->DrawFormat(eWhite, JCResto+(int)StartX + 4, BtStart + 9, 108, 3, gCustomMessage.GetMessage(27));
	}

	if (gProtect.m_MainInfo.MenuButtons[3] == 1)//EnableCommandButton
	{
	//Commandos
	BtStart += BtDistance;

	if (IsWorkZone(eMenu_OPT4))
	{
		if (this->Data[eMenu_OPT4].OnClick)
			this->DrawButton(eMenu_OPT4,JCResto+ StartX + 4, BtStart, 0, 58);
		else
			this->DrawButton(eMenu_OPT4, JCResto+StartX + 4, BtStart, 0, 29);
		// ----
	}
	else
		this->DrawButton(eMenu_OPT4,JCResto+ StartX + 4, BtStart, 0, 0);

	this->DrawFormat(eWhite, JCResto+(int)StartX + 4, BtStart + 9, 108, 3, gCustomMessage.GetMessage(28));
	}


	// melo920 recuerda falta la 4 de EnableOptionButton

// ======================================== SEGUNDA COLUMNA ==============================================

	
	if (gProtect.m_MainInfo.MenuButtons[5] == 1)//EnableMultiWareButton
	{
		BtCount2++;
	}
	else
	{
		BtStart2 -= 33;
	}
//	if (gProtect.m_MainInfo.EnableUserPanelButton == 1)
//	{
		BtCount2++;
//	}
//	if (gProtect.m_MainInfo.EnableOptionButton == 1)
//	{
		BtCount2++;
//	}
//	if (gProtect.m_MainInfo.EnableChangeClassButton == 1)
//	{
		BtCount2++;
//	}

//	if (gProtect.m_MainInfo.EnableChangeClassButton == 1 && gProtect.m_MainInfo.EnableOptionButton == 1 && gProtect.m_MainInfo.EnableUserPanelButton == 1 && gProtect.m_MainInfo.EnableMultiWareButton == 1)
//	{
		if (BtCount2 == 3)
		{
			BtStart2 += 30;
		}
//	}
//	if (gProtect.m_MainInfo.EnableChangeClassButton == 0 && gProtect.m_MainInfo.EnableOptionButton == 1 && gProtect.m_MainInfo.EnableUserPanelButton == 1 && gProtect.m_MainInfo.EnableMultiWareButton == 1)
//	{
		if (BtCount2 == 2)
		{
			BtStart2 += 45;
		}
//	}
//	if (gProtect.m_MainInfo.EnableChangeClassButton == 1 && gProtect.m_MainInfo.EnableOptionButton == 0 && gProtect.m_MainInfo.EnableUserPanelButton == 1 && gProtect.m_MainInfo.EnableMultiWareButton == 1)
//	{
		if (BtCount2 == 2)
		{
			BtStart2 += 45;
		}
//	}
//	if (gProtect.m_MainInfo.EnableChangeClassButton == 1 && gProtect.m_MainInfo.EnableOptionButton == 1 && gProtect.m_MainInfo.EnableUserPanelButton == 0 && gProtect.m_MainInfo.EnableMultiWareButton == 1)
//	{
		if (BtCount2 == 2)
		{
			BtStart2 += 45;
		}
//	}
//	if (gProtect.m_MainInfo.EnableChangeClassButton == 1 && gProtect.m_MainInfo.EnableOptionButton == 1 && gProtect.m_MainInfo.EnableUserPanelButton == 1 && gProtect.m_MainInfo.EnableMultiWareButton == 0)
//	{
		if (BtCount2 == 2)
		{
			BtStart2 += 45;
		}
//	}
//	if (gProtect.m_MainInfo.EnableChangeClassButton == 0 && gProtect.m_MainInfo.EnableOptionButton == 0 && gProtect.m_MainInfo.EnableUserPanelButton == 1 && gProtect.m_MainInfo.EnableMultiWareButton == 1)
//	{
		if (BtCount2 == 1)
		{
			BtStart2 += 60;
		}
//	}
//	if (gProtect.m_MainInfo.EnableChangeClassButton == 0 && gProtect.m_MainInfo.EnableOptionButton == 1 && gProtect.m_MainInfo.EnableUserPanelButton == 0 && gProtect.m_MainInfo.EnableMultiWareButton == 1)
//	{
		if (BtCount2 == 1)
		{
			BtStart2 += 60;
		}
//	}
//	if (gProtect.m_MainInfo.EnableChangeClassButton == 0 && gProtect.m_MainInfo.EnableOptionButton == 1 && gProtect.m_MainInfo.EnableUserPanelButton == 1 && gProtect.m_MainInfo.EnableMultiWareButton == 0)
//	{
		if (BtCount2 == 1)
		{
			BtStart2 += 60;
		}
//	}
//	if (gProtect.m_MainInfo.EnableChangeClassButton == 0 && gProtect.m_MainInfo.EnableOptionButton == 1 && gProtect.m_MainInfo.EnableUserPanelButton == 1 && gProtect.m_MainInfo.EnableMultiWareButton == 0)
//	{
		if (BtCount2 == 1)
		{
			BtStart2 += 60;
		}
//	}

	//MultiWare
	if (gProtect.m_MainInfo.MenuButtons[5] == 1)//EnableMultiWareButton
	{
		if (IsWorkZone(eMenu_VAULT))
		{
			if (this->Data[eMenu_VAULT].OnClick)
				this->DrawButton(eMenu_VAULT,JCResto+ StartX + 115, BtStart2, 0, 58);
			else
				this->DrawButton(eMenu_VAULT,JCResto+ StartX + 115, BtStart2, 0, 29);
			// ----
		}
		else
			this->DrawButton(eMenu_VAULT, JCResto+StartX + 115, BtStart2, 0, 0);

		this->DrawFormat(eWhite, JCResto+(int)StartX + 115, BtStart2 + 9, 108, 3, "MultiWare");//gCustomMessage.GetMessage(43)
	}
	//User Panel
	if (gProtect.m_MainInfo.MenuButtons[4] == 1)//EnableUserPanelButton
	{

		BtStart2 += BtDistance;

		if (IsWorkZone(eMenu_USERPANEL))
		{
			if (this->Data[eMenu_USERPANEL].OnClick)
				this->DrawButton(eMenu_USERPANEL, JCResto+StartX + 115, BtStart2, 0, 58);
			else
				this->DrawButton(eMenu_USERPANEL, JCResto+StartX + 115, BtStart2, 0, 29);
			// ----
		}
		else
			this->DrawButton(eMenu_USERPANEL, JCResto+StartX + 115, BtStart2, 0, 0);

		this->DrawFormat(eWhite, JCResto+(int)StartX + 115, BtStart2 + 9, 108, 3, "User Panel");//gCustomMessage.GetMessage(42)
	}

	//Change Class
	if (gProtect.m_MainInfo.MenuButtons[8] == 1)//EnableChangeClassButton
	{

		BtStart2 += BtDistance;

		if (IsWorkZone(eMenu_CHANGECLASS))
		{
			if (this->Data[eMenu_CHANGECLASS].OnClick)
				this->DrawButton(eMenu_CHANGECLASS, JCResto+StartX + 115, BtStart2, 0, 58);
			else
				this->DrawButton(eMenu_CHANGECLASS, JCResto+StartX + 115, BtStart2, 0, 29);
			// ----
		}
		else
			this->DrawButton(eMenu_CHANGECLASS,JCResto+ StartX + 115, BtStart2, 0, 0);

		this->DrawFormat(eWhite, JCResto+(int)StartX + 115, BtStart2 + 9, 108, 3, "Change Class");//gCustomMessage.GetMessage(41)
	}
	if (gProtect.m_MainInfo.MenuButtons[10] == 1)//EnableChangeClassButton
	{

		BtStart2 += BtDistance;

		if (IsWorkZone(eMenu_OPT21))
		{
			if (this->Data[eMenu_OPT21].OnClick)
				this->DrawButton(eMenu_OPT21, JCResto+StartX + 115, BtStart2, 0, 58);
			else
				this->DrawButton(eMenu_OPT21, JCResto+StartX + 115, BtStart2, 0, 29);
			// ----
		}
		else
			this->DrawButton(eMenu_OPT21,JCResto+ StartX + 115, BtStart2, 0, 0);

		this->DrawFormat(eWhite, JCResto+(int)StartX + 115, BtStart2 + 9, 108, 3, "Item Market");//gCustomMessage.GetMessage(41)
	}
}
void Interface::DrawMenuOpenTwo()
{
	if (gProtect.m_MainInfo.CustomMenuSwitch != 1)
	{
		return;
	}

	if (!this->Data[eMenu_MAINTWO].OnShow)
	{
		return;
	}
	// ----
	int JCResto;
	#if(WIDE_SCREEN == 1)
	JCResto =  pWinWidth / pWinHeightReal/ 2 -320;
#else
	JCResto =0;
#endif
	float MainWidth			= 230.0;
	float MainHeight		= 250.0;
	float StartBody			= 30;
	float StartY			= 30;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);

	this->DrawGUI(eMenu_TITLE, JCResto+StartX, StartY);
	this->DrawGUI(eMenu_FOOTER, JCResto+StartX, StartY);

	gCentral.PrintDropBox(JCResto+StartX, StartY, MainWidth, MainHeight, 0, 0);

	this->DrawGUI(eMenu_CLOSE, JCResto+StartX + MainWidth - this->Data[eVip_CLOSE].Width, StartBody);
	// ----
	if (this->IsWorkZone(eMenu_CLOSE))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eMenu_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eVip_CLOSE, this->Data[eMenu_CLOSE].X, StartBody, Color);
		this->DrawToolTip((int)this->Data[eMenu_CLOSE].X + 5, StartBody + 25, "Close");
	}

	if (gInterface.IsWorkZone(eMenu_NEXT))
	{
		DWORD Color = eGray100;
		// ----
		if (gInterface.Data[eMenu_NEXT].OnClick)
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eMenu_NEXT, gInterface.Data[eMenu_NEXT].X, gInterface.Data[eMenu_NEXT].Y, Color);
		this->DrawToolTip((int)this->Data[eMenu_NEXT].X + 5, (int)StartBody + 238, "Next");
	}

	if (gInterface.IsWorkZone(eMenu_PREVIUS))
	{
		DWORD Color = eGray100;
		// ----
		if (gInterface.Data[eMenu_PREVIUS].OnClick)
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eMenu_PREVIUS, gInterface.Data[eMenu_PREVIUS].X, gInterface.Data[eMenu_PREVIUS].Y, Color);
		this->DrawToolTip((int)this->Data[eMenu_PREVIUS].X + 3, (int)StartBody + 238, "Previus");
	}

	gInterface.DrawGUI(eMenu_NEXT,JCResto+ ButtonX + 90, (int)StartBody + 210);
	gInterface.DrawGUI(eMenu_PREVIUS, JCResto+ButtonX - 10, (int)StartBody + 210);

	this->DrawFormat(eGold, JCResto+(int)StartX + 10, (int)StartBody + 10, 210, 3, "Menu");

	if (gProtect.m_MainInfo.EnableCoinStatus == 1)
	{
		this->DrawFormat(eGold, JCResto+(int)StartX + 10, (int)StartBody + 35, 210, 3, gCustomMessage.GetMessage(50));

		this->DrawFormat(eWhite, JCResto+(int)StartX + 25, (int)StartBody + 50, 40, 1, gCustomMessage.GetMessage(51));
		this->DrawFormat(eGold, JCResto+(int)StartX + 50, (int)StartBody + 50, 40, 1, "%d", Coin1);

		this->DrawFormat(eWhite,JCResto+ (int)StartX + 90, (int)StartBody + 50, 40, 1, gCustomMessage.GetMessage(52));
		this->DrawFormat(eGold, JCResto+(int)StartX + 115, (int)StartBody + 50, 40, 1, "%d", Coin2);

		this->DrawFormat(eWhite, JCResto+(int)StartX + 153, (int)StartBody + 50, 40, 1, gCustomMessage.GetMessage(53));
		this->DrawFormat(eGold, JCResto+(int)StartX + 176, (int)StartBody + 50, 40, 1, "%d", Coin3);
	}
	else
	{
		this->DrawFormat(eGold, JCResto+(int)StartX + 10, (int)StartBody + 45, 210, 3, gCustomMessage.GetMessage(54));
	}

	this->DrawGUI(eVip_DIV, JCResto+StartX, StartBody + 60);

	int BtCount = 0;
	int BtCount2 = 0;
	int BtStart = StartBody + 78;
	int BtStart2 = StartBody + 78;
	int BtDistance = 33;
	
	if (gProtect.m_MainInfo.MenuButtons[9] == 1)//EnableChangeResetButton
	{
		BtCount++;
	}
	else
	{
		BtStart -= 33;
	}

	// ======================================== SEGUNDA COLUMNA ==============================================


	if (gProtect.m_MainInfo.MenuButtons[5] == 1)
	{
		BtCount2++;
	}
	else
	{
		BtStart2 -= 33;
	}


	//OffAttack Panel
{	
	if (gProtect.m_MainInfo.MenuButtons[6] == 1);
	{

		if (IsWorkZone(eMenu_LUCKYWELL))
		{
			if (this->Data[eMenu_LUCKYWELL].OnClick)
				this->DrawButton(eMenu_LUCKYWELL, JCResto+StartX + 115, BtStart2, 0, 58);
			else
				this->DrawButton(eMenu_LUCKYWELL,JCResto+ StartX + 115, BtStart2, 0, 29);
			// ----
		}
		else
			this->DrawButton(eMenu_LUCKYWELL, JCResto+StartX + 115, BtStart2, 0, 0);

		this->DrawFormat(eWhite, JCResto+(int)StartX + 115, BtStart2 + 9, 108, 3, "Whell of Fortune");
	}
}

}
void Interface::ButtonsMenu(DWORD Event)
{
	DWORD Delay = (GetTickCount() - this->ClickTime);


	if (gInterface.Data[eMenu_MAIN].OnShow)
	{
		if (gInterface.IsWorkZone(eMenu_CLOSE))
		{
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[eMenu_CLOSE].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			gInterface.Data[eMenu_CLOSE].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			gInterface.Data[eMenu_CLOSE].EventTick = GetTickCount();

			this->CloseMenuWindow();
			return;
		}

		if (gInterface.IsWorkZone(eMenu_OPT1))
			{
				if (Event == WM_LBUTTONDOWN)
				{
					gInterface.Data[eMenu_OPT1].OnClick = true;
					pSetCursorFocus = true;
					return;
				}
				// ----
				gInterface.Data[eMenu_OPT1].OnClick = false;
				pSetCursorFocus = false;
				// ----
				if (Delay < 500)
				{
					return;
				}
				// ----
				gInterface.Data[eMenu_OPT1].EventTick = GetTickCount();

				this->CloseMenuWindow();
				gCustomEventTime.OpenWindow();
				return;
			}

		
		if (gInterface.IsWorkZone(eMenu_OPT2))
			{
				if (Event == WM_LBUTTONDOWN)
				{
					gInterface.Data[eMenu_OPT2].OnClick = true;
					pSetCursorFocus = true;
					return;
				}
				// ----
				gInterface.Data[eMenu_OPT2].OnClick = false;
				pSetCursorFocus = false;
				// ----
				if (Delay < 500)
				{
					return;
				}
				// ----
				gInterface.Data[eMenu_OPT2].EventTick = GetTickCount();

				this->CloseMenuWindow();
				this->OpenVipWindow();
				return;
			}

		
		if (gInterface.IsWorkZone(eMenu_OPT3))
			{
				if (Event == WM_LBUTTONDOWN)
				{
					gInterface.Data[eMenu_OPT3].OnClick = true;
					pSetCursorFocus = true;
					return;
				}
				// ----
				gInterface.Data[eMenu_OPT3].OnClick = false;
				pSetCursorFocus = false;
				// ----
				if (Delay < 500)
				{
					return;
				}
				// ----
				gInterface.Data[eMenu_OPT3].EventTick = GetTickCount();

				this->CloseMenuWindow();
				gCustomRanking.OpenWindow();
				return;
			}

		if (gInterface.IsWorkZone(eMenu_USERPANEL))
		{
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[eMenu_USERPANEL].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			gInterface.Data[eMenu_USERPANEL].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			gInterface.Data[eMenu_USERPANEL].EventTick = GetTickCount();

			this->CloseMenuWindow();
			this->OpenWindow(ObjWindow::Options);
			return;
		}

		if (gInterface.IsWorkZone(eMenu_CHANGECLASS))
		{
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[eMenu_CHANGECLASS].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			gInterface.Data[eMenu_CHANGECLASS].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			gInterface.Data[eMenu_CHANGECLASS].EventTick = GetTickCount();

			gInterface.DrawChangingClassWindow();
			gInterface.Data[eCHANGINGCLASS_MAIN].Open();
			this->CloseMenuWindow();			
			return;
		}

		
		if (gInterface.IsWorkZone(eMenu_OPT4))
			{
				if (Event == WM_LBUTTONDOWN)
				{
					gInterface.Data[eMenu_OPT4].OnClick = true;
					pSetCursorFocus = true;
					return;
				}
				// ----
				gInterface.Data[eMenu_OPT4].OnClick = false;
				pSetCursorFocus = false;
				// ----
				if (Delay < 500)
				{
					return;
				}
				// ----
				gInterface.Data[eMenu_OPT4].EventTick = GetTickCount();

				this->CloseMenuWindow();
				gCustomCommandInfo.OpenCommandWindow();
				return;
			}

			if (gInterface.IsWorkZone(eMenu_VAULT))
			{
				if (Event == WM_LBUTTONDOWN)
				{
					gInterface.Data[eMenu_VAULT].OnClick = true;
					pSetCursorFocus = true;
					return;
				}
				// ----
				gInterface.Data[eMenu_VAULT].OnClick = false;
				pSetCursorFocus = false;
				// ----
				if (Delay < 500)
				{
					return;
				}
				// ----
				gInterface.Data[eMenu_VAULT].EventTick = GetTickCount();

				gInterface.DrawVaultWindow();
				gInterface.Data[eVAULT_MAIN].Open();
				this->CloseMenuWindow();
				return;
			}

			if (gInterface.IsWorkZone(eMenu_OPT20))
			{
				if (Event == WM_LBUTTONDOWN)
				{
					gInterface.Data[eMenu_OPT20].OnClick = true;
					pSetCursorFocus = true;
					return;
				}
				// ----
				gInterface.Data[eMenu_OPT20].OnClick = false;
				//pSetCursorFocus = false;
				// ----
				if (Delay < 500)
				{
					return;
				}
				// ----
				gInterface.Data[eMenu_OPT20].EventTick = GetTickCount();

				this->CloseMenuWindow();
				gInterface.SwitchPartySettingsWindowState();
				pSetCursorFocus = true;
				return;
			}
			if (gInterface.IsWorkZone(eMenu_OPT21))
			{
				if (Event == WM_LBUTTONDOWN)
				{
					gInterface.Data[eMenu_OPT21].OnClick = true;
					pSetCursorFocus = true;
					return;
				}
				// ----
				gInterface.Data[eMenu_OPT21].OnClick = false;
				//pSetCursorFocus = false;
				// ----
				if (Delay < 500)
				{
					return;
				}
				// ----
				gInterface.Data[eMenu_OPT21].EventTick = GetTickCount();

				this->CloseMenuWindow();
				#if(DEV_PLAYERSHOP)
	            g_ItemMarket.SwitchResetStatsWindowState();
                #endif
				pSetCursorFocus = true;
				return;
			}

			if (gInterface.IsWorkZone(eMenu_NEXT))
			{
				if (Event == WM_LBUTTONDOWN)
				{
					gInterface.Data[eMenu_NEXT].OnClick = true;
					pSetCursorFocus = true;
					return;
				}
				// ----
				gInterface.Data[eMenu_NEXT].OnClick = false;
				pSetCursorFocus = false;
				// ----
				if (Delay < 500)
				{
					return;
				}
				// ----
				gInterface.Data[eMenu_NEXT].EventTick = GetTickCount();

				this->CloseMenuWindow();
				this->OpenWindowMenuTwo();
				return;
			}

	}
// ======================PANEL TWO ===============================

	if (gInterface.Data[eMenu_MAINTWO].OnShow)
	{
		if (gInterface.IsWorkZone(eMenu_CLOSE))
		{
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[eMenu_CLOSE].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			gInterface.Data[eMenu_CLOSE].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			gInterface.Data[eMenu_CLOSE].EventTick = GetTickCount();

			this->CloseMenuWindowTwo();
			return;
		}

		if (gInterface.IsWorkZone(eMenu_PREVIUS))
		{
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[eMenu_PREVIUS].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			gInterface.Data[eMenu_PREVIUS].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			gInterface.Data[eMenu_PREVIUS].EventTick = GetTickCount();

			this->CloseMenuWindowTwo();
			this->OpenWindowMenu();
			return;
		}

		if (gInterface.IsWorkZone(eMenu_RESETCHANGE))
		{
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[eMenu_RESETCHANGE].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			gInterface.Data[eMenu_RESETCHANGE].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			gInterface.Data[eMenu_RESETCHANGE].EventTick = GetTickCount();
			this->CloseMenuWindowTwo();
			gInterface.DrawChangeResetWindow();
			gInterface.Data[eCHANGE_RESET_MAIN].Open();
			return;
		}

		if (gInterface.IsWorkZone(eMenu_LUCKYWELL))
		{
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[eMenu_LUCKYWELL].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			gInterface.Data[eMenu_LUCKYWELL].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			gInterface.Data[eMenu_LUCKYWELL].EventTick = GetTickCount();

			gInterface.LuckyWheelState();

			this->CloseMenuWindowTwo();
			return;
		}
//-----------------------------
		if (gInterface.IsWorkZone(eMenu_SMITH_ITEM))
		{
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[eMenu_SMITH_ITEM].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			gInterface.Data[eMenu_SMITH_ITEM].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			gInterface.Data[eMenu_SMITH_ITEM].EventTick = GetTickCount();
			

			gInterface.DrawSmithItem();
			//gInterface.OpenSmithItemWindow();
			gInterface.Data[eSMITH_MAIN].Open();

			this->CloseMenuWindowTwo();
			return;
		}

//----------------------------

	}

}

bool Interface::MiniMapCheck()
{
	bool visual = false;

	if ( gInterface.CheckWindow(13) && gInterface.CheckWindow(Character)
    || gInterface.CheckWindow(8)
    || gInterface.CheckWindow(12)
    || gInterface.CheckWindow(9)
    || gInterface.CheckWindow(7)
    || gInterface.CheckWindow(14)
    || gInterface.CheckWindow(15)
    || gInterface.CheckWindow(60)
    || gInterface.CheckWindow(76) )
	{
		visual = true;
	}
	else
	{
		if ( gInterface.CheckWindow(16) && (gInterface.CheckWindow(4)||gInterface.CheckWindow(69)) )
		{
			visual = true;
		}
		else
		{
			if ( gInterface.CheckWindow(16) && gInterface.CheckWindow(11) )
			{
				visual = true;
			}
			else
			{
				if ( gInterface.CheckWindow(27) )
				{
					visual = true;
				}
				else
				{
					if ( gInterface.CheckWindow(13)
					|| gInterface.CheckWindow(16)
					|| gInterface.CheckWindow(3)
					|| gInterface.CheckWindow(21)
					|| gInterface.CheckWindow(6)
					|| gInterface.CheckWindow(22)
					|| gInterface.CheckWindow(23)
					|| gInterface.CheckWindow(24)
					|| gInterface.CheckWindow(4)
					|| gInterface.CheckWindow(18)
					|| gInterface.CheckWindow(10)
					|| gInterface.CheckWindow(5)
					|| gInterface.CheckWindow(25)
					|| gInterface.CheckWindow(26)
					|| gInterface.CheckWindow(19)
					|| gInterface.CheckWindow(20)
					|| gInterface.CheckWindow(58)
					|| gInterface.CheckWindow(59)
					|| gInterface.CheckWindow(62)
					|| gInterface.CheckWindow(73)
					|| gInterface.CheckWindow(68)
					|| gInterface.CheckWindow(69)
					|| gInterface.CheckWindow(70)
					|| gInterface.CheckWindow(66)
					|| gInterface.CheckWindow(75)
					|| gInterface.CheckWindow(74) )
					{
						visual = true;
					}
					else
					{
						if ( gInterface.CheckWindow(79) )
						{
							if ( gInterface.CheckWindow(80) )
							{
								visual = true;
							}
							else
							{
								visual = true;
							}	
						}
					}
				}
			}
		}
	}
  
	if ( gInterface.CheckWindow(77) )
	{
		if ( gInterface.CheckWindow(Warehouse) ||
			gInterface.CheckWindow(ChaosBox) ||
			gInterface.CheckWindow(Store) ||
			gInterface.CheckWindow(OtherStore) ||
			gInterface.CheckWindow(Character))
		{
			visual = true;
		}
		else
		{
			visual = true;
		}
	}
	else if ( gInterface.CheckWindow(78) )
	{
			visual = true;
	}
	return visual;
}

bool Interface::CombinedChecks()
{
	if ((this->CheckWindow(Inventory)
		&& this->CheckWindow(ExpandInventory)
		&& this->CheckWindow(Store)) ||
		(this->CheckWindow(Inventory)
		&& this->CheckWindow(Warehouse)
		&& this->CheckWindow(ExpandWarehouse)) ||
		(this->CheckWindow(Inventory)
		&& this->CheckWindow(Character)
		&& this->CheckWindow(Store)))
		return true;
	return false;
}

//bool Interface::CheckMap()
//{
//	switch(gObjUser.m_MapNumber)
//	{
//		case eMapNumber::Lorencia:
//			return false;
//			break;
//		case eMapNumber::Dungeon:
//			return false;
//			break;
//		case eMapNumber::Devias:
//			return false;
//			break;
//		case eMapNumber::Noria:
//			return false;
//			break;
//		case eMapNumber::LostTower:
//			return false;
//			break;
//		case eMapNumber::Stadium:
//			return false;
//		case eMapNumber::Atlans:
//			return false;
//			break;
//		case eMapNumber::Tarkan:
//			return false;
//			break;
//		case eMapNumber::Elbeland:
//			return false;
//			break;
//		case eMapNumber::Icarus:
//			return false;
//			break;
//		case eMapNumber::Trials:
//			return false;
//			break;
//		case eMapNumber::Aida:
//			return false;
//			break;
//		case eMapNumber::Crywolf:
//			return false;
//			break;
//		case eMapNumber::Kanturu1:
//			return false;
//			break;
//		case eMapNumber::Kanturu3:
//			return false;
//			break;
//		case eMapNumber::Barracks:
//			return false;
//			break;
//		case eMapNumber::Calmness:
//			return false;
//			break;
//		case eMapNumber::Raklion:
//			return false;
//			break;
//		case eMapNumber::Vulcanus:
//			return false;
//			break;
//		case eMapNumber::Karutan1:
//			return false;
//			break;
//		case eMapNumber::Karutan2:
//			return false;
//			break;
//		default:
//			return true;
//			break;
//	}
//}

void Interface::CloseCustomWindow()
{
	this->CloseMenuWindow();
	this->CloseVipWindow();
	this->CloseVaultWindow();
	this->Data[eRankPANEL_MAIN].OnShow		= false;
	this->Data[eEventTimePANEL_MAIN].OnShow = false;
	this->Data[eCommand_MAIN].OnShow		= false;
	this->Data[ePARTYSETTINGS_MAIN].OnShow  = false;
	this->Data[eVAULT_MAIN].OnShow          = false;
	this->Data[eCHANGINGCLASS_MAIN].OnShow  = false;
	this->Data[eLuckyWheelMain].OnShow  = false;

	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
}

void Interface::DrawItem(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse)
{

	if (this->CheckWindow(ObjWindow::MoveList) || this->CheckWindow(ObjWindow::CashShop) || this->CheckWindow(ObjWindow::SkillTree) || this->CheckWindow(ObjWindow::FullMap)
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(ExpandInventory) 
		&& this->CheckWindow(Store)) 
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(Warehouse) 
		&& this->CheckWindow(ExpandWarehouse)) )
	{
		return;
	}

	pSetBlend(true);
	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();

	sub_6363D0_Addr(0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y);

	float v2 = *(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;

	if (ItemID == 406)
	{
		sub_6358A0_Addr(0.4, v2, *(float*)0xE61E38, *(float*)0xE61E3C); //tamanho do bmd
	}
	else if (ItemID == 407)
	{
		sub_6358A0_Addr(0.5, v2, *(float*)0xE61E38, *(float*)0xE61E3C); //tamanho do bmd
	}
	else
	{
		sub_6358A0_Addr(0.7, v2, *(float*)0xE61E38, *(float*)0xE61E3C); //tamanho do bmd
	}

	glMatrixMode(0x1700);
	glPushMatrix();
	glLoadIdentity();

	sub_635830_Addr((LPVOID)0x87933A0); 
	sub_635DE0_Addr();
	sub_635E40_Addr();

	glClear(0x100);

	VAngle v45;

	unsigned __int8 v44 = 1; //0 = parado / 1 = girando

	sub_6359B0_Addr(PosX, PosY, (int)&v45, 0); //posição do bmd
	sub_5CA0D0_Addr(ItemID, Level, Excl, Anc, (int)&v45, v44, 0); //funão que mostra o BMD
	
	sub_636720_Addr();

	glMatrixMode(0x1700);
	glPopMatrix();
	glMatrixMode(0x1701);
	glPopMatrix();

	sub_637770_Addr();

	glColor3f(1,1,1);
	pSetBlend(false);
}

void Interface::DrawConfirmOpen()
{
	if(!this->CheckWindow(Shop) && this->Data[eCONFIRM_MAIN].OnShow == true)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
	}

	if ((GetTickCount() - this->Data[eCONFIRM_BTN_OK].EventTick) < 100)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
	}

	if ((GetTickCount() - this->Data[eCONFIRM_BTN_CANCEL].EventTick) < 100)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
	}

	if( !this->Data[eCONFIRM_MAIN].OnShow )
	{
		return;
	}

	float StartX;
	if( gProtect.m_MainInfo.CustomInterfaceType == 3 )
	{
		StartX = 205.0f;
	}
	else
	{
		StartX = 25.0f;
	}

	float MainWidth			= 230.0;
	float MainHeight		= 130.0;
	float StartBody			= 90.0;
	float StartY			= 90.0;
	
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (float)(29.0 / 2);

	gCentral.PrintDropBox(StartX, StartY, MainWidth, MainHeight, 0, 0);

	this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 10, 210, 3, gCustomMessage.GetMessage(66));

	this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 40, 210, 3, gCustomMessage.GetMessage(67));

	this->DrawButton(eCONFIRM_BTN_OK, (int)StartX+40, (int)StartBody + 70, 0, 0);

	if( this->IsWorkZone(eCONFIRM_BTN_OK) )
	{
		int ScaleY = 30;
		// ----
		if( this->Data[eCONFIRM_BTN_OK].OnClick )
		{
			ScaleY = 60;
		}
		// ----
		this->DrawButton(eCONFIRM_BTN_OK, (int)StartX+40, (int)StartBody + 70, 0, ScaleY);
	}

	this->DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX+140, (int)StartBody + 70, 0, 0);

	if( this->IsWorkZone(eCONFIRM_BTN_CANCEL) )
	{
		int ScaleY = 30;
		// ----
		if( this->Data[eCONFIRM_BTN_CANCEL].OnClick )
		{
			ScaleY = 60;
		}
		// ----
		this->DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX+140, (int)StartBody + 70, 0, ScaleY);
	}

}

bool Interface::EventConfirm_OK(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eCONFIRM_BTN_OK].EventTick);
	// ----
	if (!this->Data[eCONFIRM_MAIN].OnShow || !IsWorkZone(eCONFIRM_BTN_OK))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eCONFIRM_BTN_OK].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCONFIRM_BTN_OK].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eCONFIRM_BTN_OK].EventTick = GetTickCount();

	PMSG_ITEM_BUY_RECV pMsg;

	pMsg.header.set(0xF3, 0xED,sizeof(pMsg));

	pMsg.slot = this->ConfirmSlot;

	DataSend((BYTE*)&pMsg,pMsg.header.size);

	this->Data[eCONFIRM_MAIN].OnShow = false;
	
	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
	// ----
	return false;
}

bool Interface::EventConfirm_CANCEL(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eCONFIRM_BTN_CANCEL].EventTick);
	// ----
	if (!this->Data[eCONFIRM_MAIN].OnShow || !IsWorkZone(eCONFIRM_BTN_CANCEL))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eCONFIRM_BTN_CANCEL].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCONFIRM_BTN_CANCEL].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eCONFIRM_BTN_CANCEL].EventTick = GetTickCount();

	this->Data[eCONFIRM_MAIN].OnShow = false;

	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
	// ----
	return false;
}

//-- advance
void Interface::DrawBarForm(float PosX, float PosY, float Width, float Height, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	pSetBlend(true);
	glColor4f((GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (float)0.8);
	pDrawBarForm(PosX, PosY, Width, Height, 0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
}
// ----------------------------------------------------------------------------------------------
bool Interface::CheckWindowEx(int WindowID)
{
	if (WindowID < 0 || WindowID > MAX_WINDOW_EX)
	{
		return 0;
	}
	return this->WindowEx[WindowID];
}
//---- cosas peladas

void Interface::UPDATE_FPS()
{
 gInterface.frameCount++;

 if (GetTickCount() - gInterface.lastReport >= 1000)
 {
  gInterface.frameRate = gInterface.frameCount / ((GetTickCount() - gInterface.lastReport) / 1000);
   //sprintf(gInterface.FPS_REAL, "FPS : %.1d", gInterface.frameRate); 
   gInterface.lastReport = GetTickCount();
   gInterface.frameCount = 0;
 }

 sprintf_s(gInterface.FPS_REAL, "FPS : %.2f", *(float *)0x5EF5A18);

	
			if(DisablePing == 0   (this->MiniMapCheck() || this->CombinedChecks()|| this->CheckWindow(FullMap) ||this-> CheckWindow(ObjWindow::MoveList) || this->CheckWindow(SkillTree) ||this->CheckWindow(FullMap)|| this->CheckWindow(CashShop)
			|| this->CheckWindow(ObjWindow::Inventory) 	|| this->CheckWindow(ObjWindow::Quest)|| this->CheckWindow(ObjWindow::CommandWindow)|| this->CheckWindow(ObjWindow::MoveList)|| this->CheckWindow(MuHelper) || this->CheckWindow(ExpandInventory)  || this->CheckWindow(Warehouse) || this->CheckWindow(ExpandWarehouse)))
 {
  return;
 }
 this->DrawFormat(eShinyGreen, 5, 45, 120, 1, gInterface.FPS_REAL);
}

void Interface::guiMonitore(){
	if (this->MiniMapCheck() || this->CombinedChecks()|| this->CheckWindow(ObjWindow::CommandWindow)|| this-> CheckWindow(ObjWindow::MoveList)|| this->CheckWindow(FullMap) || this->CheckWindow(SkillTree) || this->CheckWindow(CashShop))
	{
		return;
	}
	pSetBlend(true);
	glColor4f((GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (float)0.8);
	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
}

void Interface::DrawPing()
{
	gInterface.msPing = GetTickCount() - gInterface.lastSend;
	gInterface.iniciador = 3;
}

struct PMSG_PING
{
	PBMSG_HEAD h;
};

void Interface::SendPingRecv()
{
	if(gInterface.iniciador == 1)
	{
		PMSG_PING pMsgPing;
		pMsgPing.h.set(0xFF,sizeof(pMsgPing));
		gInterface.lastSend = GetTickCount();
		DataSend((BYTE*)&pMsgPing,sizeof(pMsgPing));
		gInterface.iniciador=2;
	}
	else if(gInterface.iniciador == 3)
	{
		if (GetTickCount() >= gInterface.lastSend + 1500){
			PMSG_PING pMsgPing;
			pMsgPing.h.set(0xFF,sizeof(pMsgPing));
			gInterface.lastSend = GetTickCount();
			DataSend((BYTE*)&pMsgPing,sizeof(pMsgPing));
			gInterface.iniciador=2;
		}
	}

			if(DisablePing == 0  (this->MiniMapCheck() || this->CombinedChecks()||this-> CheckWindow(ObjWindow::MoveList)|| this-> CheckWindow(ObjWindow::MoveList)|| this->CheckWindow(FullMap) || this->CheckWindow(SkillTree) || this->CheckWindow(CashShop)))
	{
		return;
	}
	//sprintf(gInterface.ServerPing, "PING: %.f ms", *(float *)0x5EF5A18);
	sprintf(gInterface.ServerPing, "PING: %.d ms", (gInterface.msPing/2));

	// ----
	gInterface.validar=0;

	if(gInterface.msPing > 0){
		//----
		this->DrawFormat(eShinyGreen, 5, 65, 120, 1, gInterface.ServerPing);
		//--
		sprintf(gInterface.ultimoRTT, gInterface.ServerRTT);
		sprintf(gInterface.ultimoPing, gInterface.ServerPing);
		//--
		gInterface.ultimo_RTT = gInterface.msPing;
		gInterface.validar=1;
	}

	if(gInterface.validar==0)
	{
		if(gInterface.ultimo_RTT > 0)
		{
			this->DrawFormat(eGold, 470, 5, 80, 1, gInterface.ultimoRTT);
			this->DrawFormat(eGold, 530, 5, 120, 1, gInterface.ultimoPing);
		}
		else
		{
			this->DrawFormat(eGold, 470, 5, 120, 1, gInterface.ServerRTT);
			this->DrawFormat(eGold, 530, 5, 120, 1, gInterface.ServerPing);
		}
	}
}

//void Interface::SwitchChatExpand()
//{
//
//	if((GetTickCount() - gInterface.Data[chatbackground].EventTick) < 1000 ||this->CheckWindow(ChatWindow))
//	{
//		return;
//	}
//
//	gInterface.Data[chatbackground].EventTick = GetTickCount();
//
//	if (SeparateChat != 0)
//	{
//		gInterface.DrawMessage(1, "Chat Window Separate [OFF]");
//		SeparateChat = 0;
//		WritePrivateProfileStringA("Setting","SeparateChat","0","./Settings.ini");
//	}
//	else 
//	{
//		gInterface.DrawMessage(1, "Chat Window Separate [ON]");
//		SeparateChat = 1;f
//		WritePrivateProfileStringA("Setting","SeparateChat","1","./Settings.ini");
//	}
////	gChatExpanded.Switch();
//}

void Interface::OpenConfig(int type)
{
	if(type == 0)
	{
		if( (GetTickCount() - gInterface.Data[ePLAYER_POINT].EventTick) < 400 
			|| this->CheckWindow(ChatWindow) 
			|| this->CheckWindow(MuHelper) 
			|| this->CheckWindow(Inventory) 
			|| this->CheckWindow(Store) 
			|| this->CheckWindow(Character) 
			|| this->CheckWindow(CreateGuild) )
		{
			return;
		}

		gInterface.Data[ePLAYER_POINT].EventTick = GetTickCount();

		if (pCheckWindow(pWindowThis(), 35))
		{
			pCloseWindow(pWindowThis(), 35);
		}
		else 
		{
			pOpenWindow(pWindowThis(), 35);
		}
	}
	else if(type = 1 )
	{
		if( (GetTickCount() - gInterface.Data[ePLAYER_POINT].EventTick) < 400 || OpenSwicthSkill == 0)
		{
			return;
		}

		gInterface.Data[ePLAYER_POINT].EventTick = GetTickCount();

		if (SkillPage == 1)
		{
			SkillPage = 2;
		}
		else
		{
			SkillPage = 1;
		}
	}

	PlayBuffer(25, 0, 0);
}
//-- SwitchCamera
void Interface::SwitchCamera()
{
	if( (GetTickCount() - gInterface.Data[eCamera3DSwitch].EventTick) < 1000 )
	{
		return;
	}

	if( pMapNumber == 62 )
	{
//		gInterface.DrawMessage(1, "Camera3D not available for this map");
		gCamera.Restore();
	}

	gInterface.Data[eCamera3DSwitch].EventTick = GetTickCount();

	gCamera.Toggle();

	if (gCamera.getEnabled())
	{
//		gInterface.DrawMessage(2, "Camera3D [ON]");
	//}
	//else
	//{
//		gInterface.DrawMessage(2, "Camera3D [OFF]");
	}
}
//-- CameraInit
void Interface::CameraInit(){

	if((GetTickCount() - gInterface.Data[eCamera3DInit].EventTick) < 1000 )
	{
		return;
	}

	gInterface.Data[eCamera3DInit].EventTick = GetTickCount();

	if (gCamera.getEnabled())
	{
		//gInterface.DrawMessage(2, "Camera Restore [DEFAULT]");
		gCamera.Restore();
	}
}

bool Interface::Button(DWORD Event, int WinID, int ButtonID, bool Type)
{
	if (!this->IsWorkZone(ButtonID))
	{
		return false;
	}

	if (Type == true)
	{
		if (!this->Data[ButtonID].Attribute)
		{
			return false;
		}
	}

	// ----
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[ButtonID].EventTick);
	// ----

	if (Event == WM_LBUTTONDOWN  && this->Data[ButtonID].OnClick == false)
	{
		this->Data[ButtonID].OnClick = true;
	}

	if (Event == WM_LBUTTONUP && this->Data[ButtonID].OnClick == true)
	{
		this->Data[ButtonID].OnClick = false;
		return true;
	}
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[ButtonID].OnClick = false;
	// ----
	this->Data[ButtonID].EventTick = GetTickCount();
	// ----
	return false;
}

void Interface::DrawInterfaceS2Menu()
{
	if (IsWorkZone(eParty))
	{
		this->DrawToolTip(345, 420, "Party");
	}
	if (this->CheckWindow(Party))
	{
		gInterface.DrawButton(eParty, 348, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eCharacter))
	{
		this->DrawToolTip(375, 420, "Character");
	}
	if (this->CheckWindow(Character))
	{
		gInterface.DrawButton(eCharacter, 378.5f, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eInventory))
	{
		this->DrawToolTip(405, 420, "Inventory");
	}
	if (this->CheckWindow(Inventory))
	{
		gInterface.DrawButton(eInventory, 409, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eShop))
	{
		this->DrawToolTip(430, 420, "CashShop");
	}
	if (this->CheckWindow(CashShop))
	{
		gInterface.DrawButton(eShop, 439.5f, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eFriend))
	{
		this->DrawToolTip(580, 420, "Friends");
	}
	if (this->CheckWindow(FriendList))
	{
		gInterface.DrawButton(eFriend, 581, 433, 0.0, 0.0);
	}
	if (IsWorkZone(eGuild))
	{
		this->DrawToolTip(580, 444, "Guild");
	}
	if (this->CheckWindow(Guild))
	{
		gInterface.DrawButton(eGuild, 581, 457, 0.0, 0.0);
	}
	if (IsWorkZone(eFastMenu))
	{
		this->DrawToolTip(13, 420, "System");
	}
	if (this->CheckWindow(FastMenu))
	{
		gInterface.DrawButton(eFastMenu, 6, 433, 0.0, 0.0);
	}
}
//--------------------------------------
void Interface::DrawInterface97Menu()
{
	if (IsWorkZone(eParty))
	{
		this->DrawToolTip(345, 420, "Party");
	}
	if (this->CheckWindow(Party))
	{
		gInterface.DrawButton(eParty, 348, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eCharacter))
	{
		this->DrawToolTip(375, 420, "Character");
	}
	if (this->CheckWindow(Character))
	{
		gInterface.DrawButton(eCharacter, 378.5f, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eInventory))
	{
		this->DrawToolTip(405, 420, "Inventory");
	}
	if (this->CheckWindow(Inventory))
	{
		gInterface.DrawButton(eInventory, 409, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eShop))
	{
		this->DrawToolTip(430, 420, "CashShop");
	}
	if (this->CheckWindow(CashShop))
	{
		gInterface.DrawButton(eShop, 439.5f, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eFriend))
	{
		this->DrawToolTip(580, 420, "Friends");
	}
	if (this->CheckWindow(FriendList))
	{
		gInterface.DrawButton(eFriend, 581, 433, 0.0, 0.0);
	}
	if (IsWorkZone(eGuild))
	{
		this->DrawToolTip(580, 444, "Guild");
	}
	if (this->CheckWindow(Guild))
	{
		gInterface.DrawButton(eGuild, 581, 457, 0.0, 0.0);
	}
}
//--------------------------------------
void Interface::EventNewInterface_All(DWORD Event){
	DWORD CurrentTick = GetTickCount();
	if (this->CheckWindow(ChaosBox))
	{
		return;
	}
	
	if (IsWorkZone(eFastMenu))
	{
		DWORD Delay = (CurrentTick - this->Data[eFastMenu].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eFastMenu].OnClick = true;
			return;
		}
		this->Data[eFastMenu].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eFastMenu].EventTick = GetTickCount();
		if (this->CheckWindow(FastMenu)) {
				this->CloseWindow(FastMenu);
		}
		else {
			this->OpenWindow(FastMenu);
		}
	}
	else if (IsWorkZone(eParty))
	{
		DWORD Delay = (CurrentTick - this->Data[eParty].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eParty].OnClick = true;
			return;
		}
		this->Data[eParty].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eParty].EventTick = GetTickCount();
		if (this->CheckWindow(Party)) {
			this->CloseWindow(Party);
		}
		else {
			this->OpenWindow(Party);
		}
	}
	
	else if (IsWorkZone(eCharacter))
	{
		DWORD Delay = (CurrentTick - this->Data[eCharacter].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eCharacter].OnClick = true;
			return;
		}
		this->Data[eCharacter].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eCharacter].EventTick = GetTickCount();
		if (this->CheckWindow(Character)) {
			this->CloseWindow(Character);
		}
		else {
			this->OpenWindow(Character);
		}
	}
	else if (IsWorkZone(eInventory))
	{
		DWORD Delay = (CurrentTick - this->Data[eInventory].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eInventory].OnClick = true;
			return;
		}
		this->Data[eInventory].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eInventory].EventTick = GetTickCount();
		if (this->CheckWindow(Inventory)) {
			this->CloseWindow(Inventory);
		}
		else {
			this->OpenWindow(Inventory);
		}
	}
	else if (IsWorkZone(eFriend))
	{
		DWORD Delay = (CurrentTick - this->Data[eFriend].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eFriend].OnClick = true;
			return;
		}
		this->Data[eFriend].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eFriend].EventTick = GetTickCount();
		if (this->CheckWindow(FriendList)) {
			this->CloseWindow(FriendList);
		}
		else {
			this->OpenWindow(FriendList);
		}
	}
	else if (IsWorkZone(eGuild))
	{
		DWORD Delay = (CurrentTick - this->Data[eGuild].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eGuild].OnClick = true;
			return;
		}
		this->Data[eGuild].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eGuild].EventTick = GetTickCount();
		if (this->CheckWindow(Guild)) {
			this->CloseWindow(Guild);
		}
		else {
			this->OpenWindow(Guild);
		}
	}
}
void Interface::EventNewInterface97_All(DWORD Event){
	DWORD CurrentTick = GetTickCount();
	if (this->CheckWindow(ChaosBox))
	{
		return;
	}
	
	if (IsWorkZone(eParty))
	{
		DWORD Delay = (CurrentTick - this->Data[eParty].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eParty].OnClick = true;
			return;
		}
		this->Data[eParty].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eParty].EventTick = GetTickCount();
		if (this->CheckWindow(Party)) {
			this->CloseWindow(Party);
		}
		else {
			this->OpenWindow(Party);
		}
	}
	
	else if (IsWorkZone(eCharacter))
	{
		DWORD Delay = (CurrentTick - this->Data[eCharacter].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eCharacter].OnClick = true;
			return;
		}
		this->Data[eCharacter].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eCharacter].EventTick = GetTickCount();
		if (this->CheckWindow(Character)) {
			this->CloseWindow(Character);
		}
		else {
			this->OpenWindow(Character);
		}
	}
	else if (IsWorkZone(eInventory))
	{
		DWORD Delay = (CurrentTick - this->Data[eInventory].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eInventory].OnClick = true;
			return;
		}
		this->Data[eInventory].OnClick = false;
		if (Delay < 500)
		{
			return;
		}
		this->Data[eInventory].EventTick = GetTickCount();
		if (this->CheckWindow(Inventory))
		{
			this->CloseWindow(Inventory);
		}
		else {
			this->OpenWindow(Inventory);
		}
	}
	else if (IsWorkZone(eFriend))
	{
		DWORD Delay = (CurrentTick - this->Data[eFriend].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eFriend].OnClick = true;
			return;
		}
		this->Data[eFriend].OnClick = false;
		if (Delay < 500)
		{
			return;
		}
		this->Data[eFriend].EventTick = GetTickCount();
		if (this->CheckWindow(FriendList))
		{
			this->CloseWindow(FriendList);
		}
		else {
			this->OpenWindow(FriendList);
		}
	}
	else if (IsWorkZone(eGuild))
	{
		DWORD Delay = (CurrentTick - this->Data[eGuild].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eGuild].OnClick = true;
			return;
		}
		this->Data[eGuild].OnClick = false;
		if (Delay < 500)
		{
			return;
		}
		this->Data[eGuild].EventTick = GetTickCount();
		if (this->CheckWindow(Guild))
		{
			this->CloseWindow(Guild);
		}
		else {
			this->OpenWindow(Guild);
		}
	}
}

void Interface::DrawInterfaceDragonLS3()
{
	if(this->CheckWindow(ObjWindow::CashShop)
		|| this->CheckWindow(ObjWindow::FullMap)
		|| this->CheckWindow(ObjWindow::SkillTree)
		|| this->CheckWindow(ObjWindow::MoveList)
		|| this->CheckWindow(ObjWindow::ChatWindow)
		)
	{
		return;
	}
	this->DrawGUI(eDragonLeft, this->Data[eDragonLeft].X, this->Data[eDragonLeft].Y);
}

void Interface::DrawInterfaceDragonRS3()
{	
	if (this->MiniMapCheck()||(this->CheckWindow(SkillTree)|| this->CheckWindow(CashShop) || this->CheckWindow(FullMap)
		||this->CheckWindow(FastMenu)||this->CheckWindow(FriendList))
		|| pMapNumber == 39 //Kanturu
		|| pMapNumber == 58 //Selupam
		|| pMapNumber == 64 //Duel Arena
		|| pMapNumber == 65 //Doppelganger
		|| pMapNumber == 66 //Doppelganger
		|| pMapNumber == 67 //Doppelganger
		|| pMapNumber == 68 //Doppelganger
		|| pMapNumber == 69 //Imperial Guardian
		|| pMapNumber == 70 //Imperial Guardian
		|| pMapNumber == 71 //Imperial Guardian
		|| pMapNumber == 72 //Imperial Guardian
		|| pMapNumber == 11	//Blood Castle
		|| pMapNumber == 12	//Blood Castle
		|| pMapNumber == 13	//Blood Castle
		|| pMapNumber == 14	//Blood Castle
		|| pMapNumber == 15	//Blood Castle
		|| pMapNumber == 16	//Blood Castle
		|| pMapNumber == 17	//Blood Castle
		|| pMapNumber == 52	//Blood Castle
		|| pMapNumber == 9	//Devil Square
		|| pMapNumber == 32	//Devil Square
		|| pMapNumber == 18	//Chaos Castle
		|| pMapNumber == 19	//Chaos Castle
		|| pMapNumber == 20	//Chaos Castle
		|| pMapNumber == 21	//Chaos Castle
		|| pMapNumber == 22	//Chaos Castle
		|| pMapNumber == 23	//Chaos Castle
		|| pMapNumber == 53	//Chaos Castle
		|| pMapNumber == 45	//Illusion Temple
		|| pMapNumber == 46	//Illusion Temple
		|| pMapNumber == 47	//Illusion Temple
		|| pMapNumber == 48	//Illusion Temple
		|| pMapNumber == 49	//Illusion Temple
		|| pMapNumber == 50	//Illusion Temple
		|| pMapNumber == 18	//Chaos Castle
		|| pMapNumber == 19	//Chaos Castle
		|| pMapNumber == 20	//Chaos Castle
		|| pMapNumber == 21	//Chaos Castle
		|| pMapNumber == 22	//Chaos Castle
		|| pMapNumber == 23	//Chaos Castle
		|| pMapNumber == 53	//Chaos Castle
		|| pMapNumber == 34 //Crywolf
		|| pMapNumber == 30 //Valley/CastleSiege
		|| pMapNumber == 65 /*DuelArena*/)
	{
		return;
	}
	this->DrawGUI(eDragonRight, this->Data[eDragonRight].X, this->Data[eDragonRight].Y);
}

void Interface::DrawCoord()
{
	gObjUser.Refresh();

	if (*(DWORD*)MAIN_SCREEN_STATE == 5)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		pDrawInterfaceNumBer(22, 461, gObjUser.lpViewPlayer->MapPosX, 1);
		pDrawInterfaceNumBer(46, 461, gObjUser.lpViewPlayer->MapPosY, 1);

	}
}

//============================================ PARTY SEARCH
int Interface::DrawToolTipEx(DWORD Color, int PosX, int PosY, int Width, int Height, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	char Buff2[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----

	int LineCount = 0;

	strcpy(Buff2,Buff);

	char * Line = strtok(Buff2, "\n");
	// ----
	while( Line != NULL )
	{
		LineCount++;
		Line = strtok(NULL, "\n");
	}

	pSetBlend(1);
	glColor4f(0.0, 0.0, 0.0, 1.0);
	pDrawBarForm(PosX, PosY, Width, LineCount*10, 0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();

	glColor3f(1.0, 1.0, 1.0);

	this->DrawFormat(eWhite, PosX, PosY, Width, Align, Buff);
	return 0;
}

void Interface::DrawColoredButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY, DWORD Color)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, PosX, PosY,
	this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY, Color);
}

void Interface::SwitchPartySettingsWindowState()
{
	Data[ePARTYSETTINGS_MAIN].OnShow == true? Data[ePARTYSETTINGS_MAIN].Close():Data[ePARTYSETTINGS_MAIN].Open();
}

void Interface::DrawPartySettingsWindow()
{
	if( !this->Data[ePARTYSETTINGS_MAIN].OnShow )
	{
		return;
	}
	// ----
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 50.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	this->DrawGUI(ePARTYSETTINGS_MAIN, StartX, StartY + 2);
	this->DrawGUI(ePARTYSETTINGS_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(ePARTYSETTINGS_FRAME, StartX, StartY + 67.0, 16);
	this->DrawGUI(ePARTYSETTINGS_FOOTER, StartX, StartY);
	this->DrawGUI(ePARTYSETTINGS_CLOSE, StartX + MainWidth - this->Data[ePARTYSETTINGS_CLOSE].Width + 2, 49);
	// ----
	if( this->IsWorkZone(ePARTYSETTINGS_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[ePARTYSETTINGS_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(ePARTYSETTINGS_CLOSE, this->Data[ePARTYSETTINGS_CLOSE].X, this->Data[ePARTYSETTINGS_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[ePARTYSETTINGS_CLOSE].X + 5, this->Data[ePARTYSETTINGS_CLOSE].Y + 25, "Cerrar");
	}
	// ----
	this->DrawFormat(eGold, StartX + 10, 60, 210, 3, "Party Search Settings");
///////////////////////////////////////////ACTIVE SYSTEM///////////////////////////////////////////
	this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN].Y + 33, 200, 1, "Activar Sistema");

	if (gPartySearchSettings.m_SystemActive == false)
	{
		this->DrawButton(ePARTYSETTINGS_SYSTEM_ACTIVE, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 30, 0, 0);
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_SYSTEM_ACTIVE, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 30, 0, 15);
	}
	this->DrawGUI(ePARTYSETTINGS_DIV, StartX , this->Data[ePARTYSETTINGS_MAIN].Y + 40); // Äåëèòåëü áîëüøîé
/////////////////////////////////////////ACTIVE SYSTEM END/////////////////////////////////////////

/////////////////////////////////////////////MAX LEVEL/////////////////////////////////////////////
	this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN]. Y + 60, 200, 1, "Max Level");
	this->DrawGUI(ePARTYSETTINGS_DIV, StartX , this->Data[ePARTYSETTINGS_MAIN].Y + 67); // Äåëèòåëü áîëüøîé


	this->DrawToolTip(StartX + 174, this->Data[ePARTYSETTINGS_MAIN].Y + 62, "%d", gPartySearchSettings.m_Level);

	if (gPartySearchSettings.m_SystemActive == 0)
	{
		this->DrawColoredButton(ePARTYSETTINGS_LEVEL_MINUS, StartX + 150, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0, eGray150); // 
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_LEVEL_MINUS, StartX + 150, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0); // 

		if(this->IsWorkZone(ePARTYSETTINGS_LEVEL_MINUS) )
		{
			if( this->Data[ePARTYSETTINGS_LEVEL_MINUS].OnClick )
			{
				this->DrawButton(ePARTYSETTINGS_LEVEL_MINUS, StartX + 150, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 16);
			}
		}
	}

	if (gPartySearchSettings.m_SystemActive == 0)
	{
		this->DrawColoredButton(ePARTYSETTINGS_LEVEL_PLUS, StartX + 193, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0, eGray150); //
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_LEVEL_PLUS, StartX + 193, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0); //

		if(this->IsWorkZone(ePARTYSETTINGS_LEVEL_PLUS) )
		{
			if( this->Data[ePARTYSETTINGS_LEVEL_PLUS].OnClick )
			{
				this->DrawButton(ePARTYSETTINGS_LEVEL_PLUS, StartX + 193, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 16);
			}
		}
	}

///////////////////////////////////////////MAX LEVEL END///////////////////////////////////////////

///////////////////////////////////////////////GUILD///////////////////////////////////////////////

	this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN].Y + 87, 200, 1, "Only Guild");

	if (gPartySearchSettings.m_SystemActive)
	{
		if (gPartySearchSettings.m_OnlyGuild == false)
		{
			this->DrawButton(ePARTYSETTINGS_ONLY_GUILD, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 83, 0, 0);
		}
		else
		{
			this->DrawButton(ePARTYSETTINGS_ONLY_GUILD, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 83, 0, 15);
		}
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_ONLY_GUILD, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 83, 0, 30);
	}

	pDrawGUI(0x7B5E, StartX + 30, this->Data[ePARTYSETTINGS_MAIN].Y + 100, 82.0, 2.0); // Äåëèòåëü ìåëêèé 1
	pDrawGUI(0x7B5E, StartX + 30 + 82, this->Data[ePARTYSETTINGS_MAIN].Y + 100, 82.0, 2.0); // Äåëèòåëü ìåëêèé 2

	this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN].Y + 109, 200, 1, "Only One Class");

	if (gPartySearchSettings.m_SystemActive)
	{
		if (gPartySearchSettings.m_OneClass == false)
		{
			this->DrawButton(ePARTYSETTINGS_ONE_CLASS, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 105, 0, 0);
		}
		else
		{
			this->DrawButton(ePARTYSETTINGS_ONE_CLASS, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 105, 0, 15);
		}
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_ONE_CLASS, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 105, 0, 30);
	}

	this->DrawGUI(ePARTYSETTINGS_DIV, StartX , this->Data[ePARTYSETTINGS_MAIN].Y + 115);// 94 // Äåëèòåëü áîëüøîé
/////////////////////////////////////////////GUILD END/////////////////////////////////////////////
	char szCharNames[7][32] = 
	{
		"Dark Wizard",
		"Dard Knight",
		"Elf",
		"Magic Gladiator",
		"Dark Lord",
		"Summoner",
		"Rage Fighter"
	};

	int ObjectIDs[7] = 
	{ 
		ePARTYSETTINGS_DARK_WIZARD, 
		ePARTYSETTINGS_DARK_KNIGHT, 
		ePARTYSETTINGS_ELF, 
		ePARTYSETTINGS_MAGIC_GLADIATOR, 
		ePARTYSETTINGS_DARK_LORD, 
		ePARTYSETTINGS_SUMMONER, 
		ePARTYSETTINGS_RAGE_FIGHTER
	};

	for (int i = 0; i<7; i++)
	{
		this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN].Y + 135 + (i * 22), 200, 1, szCharNames[i]);

		bool ClassValue = 0;
		switch (i)
		{
			case 0:
				ClassValue = gPartySearchSettings.m_DarkWizard;
				break;
			case 1:
				ClassValue = gPartySearchSettings.m_DarkKnight;
				break;
			case 2:
				ClassValue = gPartySearchSettings.m_Elf;
				break;
			case 3:
				ClassValue = gPartySearchSettings.m_MagicGladiator;
				break;
			case 4:
				ClassValue = gPartySearchSettings.m_DarkLord;
				break;
			case 5:
				ClassValue = gPartySearchSettings.m_Summoner;
				break;
			case 6:
				ClassValue = gPartySearchSettings.m_RageFighter;
				break;
		}

		if (gPartySearchSettings.m_SystemActive)
		{
			if (ClassValue == false)
			{
				this->DrawButton(ObjectIDs[i], ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 131 + (i * 22), 0, 0);
			}
			else
			{
				this->DrawButton(ObjectIDs[i], ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 131 + (i * 22), 0, 15);
			}
		}
		else
		{
			this->DrawButton(ObjectIDs[i], ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 131 + (i * 22), 0, 30);
		}

		pDrawGUI(0x7B5E, StartX + 30, this->Data[ePARTYSETTINGS_MAIN].Y + 148 + (i * 22), 82.0, 2.0); // Äåëèòåëü ìåëêèé 1
		pDrawGUI(0x7B5E, StartX + 30 + 82, this->Data[ePARTYSETTINGS_MAIN].Y + 148 + (i * 22), 82.0, 2.0); // Äåëèòåëü ìåëêèé 2
	}

	this->DrawGUI(ePARTYSETTINGS_DIV, StartX , this->Data[ePARTYSETTINGS_MAIN].Y + 290); // Äåëèòåëü áîëüøîé

	//if (gPartySearchSettings.m_SystemActive)
	//{
		this->DrawButton(ePARTYSETTINGS_OK, StartX + this->Data[ePARTYSETTINGS_MAIN].Width/2-this->Data[ePARTYSETTINGS_OK].Width/2, this->Data[ePARTYSETTINGS_MAIN].Y + 310, 0, 0);

		if( this->IsWorkZone(ePARTYSETTINGS_OK) )
		{
			int ScaleY = 30;
			// ----
			if( this->Data[ePARTYSETTINGS_OK].OnClick )
			{
				ScaleY = 60;
			}
			// ----
			this->DrawButton(ePARTYSETTINGS_OK, StartX + this->Data[ePARTYSETTINGS_MAIN].Width/2-this->Data[ePARTYSETTINGS_OK].Width/2, this->Data[ePARTYSETTINGS_MAIN].Y + 310, 0, ScaleY);
		}
	//}

}

bool Interface::EventPartySettingsWindow_Main(DWORD Event)
{
	this->EventPartySettingsWindow_Close(Event);
	this->EventPartySettingsWindow_All(Event);
	// ----
	// ----
	return true;
}

bool Interface::EventPartySettingsWindow_All(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	//DWORD Delay			= (CurrentTick - this->Data[eDIABLO_CLOSE].EventTick);
	if( !this->Data[ePARTYSETTINGS_MAIN].OnShow )
	{
		return false;
	}

	if (IsWorkZone(ePARTYSETTINGS_SYSTEM_ACTIVE))
	{
		DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_SYSTEM_ACTIVE].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSETTINGS_SYSTEM_ACTIVE].OnClick = true;
			return true;
		}
		// ----
		this->Data[ePARTYSETTINGS_SYSTEM_ACTIVE].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_SYSTEM_ACTIVE].EventTick = GetTickCount();
		gPartySearchSettings.m_SystemActive ^= 1;

		for (int i=0;i<7;i++)
		{
			gPartySearchSettings.m_SystemActive==true?gPartySearchSettings.SetClassValue(i,true):gPartySearchSettings.SetClassValue(i,false);
		}
	}

	if (IsWorkZone(ePARTYSETTINGS_LEVEL_MINUS))
	{
		if (gPartySearchSettings.m_SystemActive == 0)
		{
			return false;
		}

		DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_LEVEL_MINUS].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSETTINGS_LEVEL_MINUS].OnClick = true;
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_LEVEL_MINUS].OnClick = false;
		// ----
		if( Delay < 200 )
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_LEVEL_MINUS].EventTick = GetTickCount();

		gPartySearchSettings.m_Level -= 10;
		if (gPartySearchSettings.m_Level<=0)
		{
			gPartySearchSettings.m_Level = 0;
		}
	}

	if (IsWorkZone(ePARTYSETTINGS_LEVEL_PLUS))
	{
		if (gPartySearchSettings.m_SystemActive == 0)
		{
			return false;
		}

		DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_LEVEL_PLUS].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSETTINGS_LEVEL_PLUS].OnClick = true;
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_LEVEL_PLUS].OnClick = false;
		// ----
		if( Delay < 200 )
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_LEVEL_PLUS].EventTick = GetTickCount();

		gPartySearchSettings.m_Level += 10;
		if (gPartySearchSettings.m_Level>=400)
		{
			gPartySearchSettings.m_Level = 400;
		}
	}

	if (IsWorkZone(ePARTYSETTINGS_ONLY_GUILD))
	{
		DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_ONLY_GUILD].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSETTINGS_ONLY_GUILD].OnClick = true;
			return true;
		}
		// ----
		this->Data[ePARTYSETTINGS_ONLY_GUILD].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_ONLY_GUILD].EventTick = GetTickCount();
		gPartySearchSettings.m_OnlyGuild ^= 1;
	}

	if (IsWorkZone(ePARTYSETTINGS_ONE_CLASS))
	{
		DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_ONE_CLASS].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSETTINGS_ONE_CLASS].OnClick = true;
			return true;
		}
		// ----
		this->Data[ePARTYSETTINGS_ONE_CLASS].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_ONE_CLASS].EventTick = GetTickCount();
		gPartySearchSettings.m_OneClass ^= 1;

		for (int i=0;i<7;i++)
		{
			gPartySearchSettings.m_OneClass==false?gPartySearchSettings.SetClassValue(i,true):gPartySearchSettings.SetClassValue(i,false);

		}
	}

	if (IsWorkZone(ePARTYSETTINGS_OK))
	{

		DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_OK].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSETTINGS_OK].OnClick = true;
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_OK].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_OK].EventTick = GetTickCount();
		gPartySearchSettings.CGSendPartySearchAdd();
		this->SwitchPartySettingsWindowState();
	}

	int ObjectIDs[7] = 
	{ 
		ePARTYSETTINGS_DARK_WIZARD, 
		ePARTYSETTINGS_DARK_KNIGHT, 
		ePARTYSETTINGS_ELF, 
		ePARTYSETTINGS_MAGIC_GLADIATOR, 
		ePARTYSETTINGS_DARK_LORD, 
		ePARTYSETTINGS_SUMMONER, 
		ePARTYSETTINGS_RAGE_FIGHTER
	};

	for (int i = 0; i<7; i++)
	{
		if (IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay			= (CurrentTick - this->Data[ObjectIDs[i]].EventTick);

			if( Event == WM_LBUTTONDOWN )
			{
				this->Data[ObjectIDs[i]].OnClick = true;
				return true;
			}
			// ----
			this->Data[ObjectIDs[i]].OnClick = false;
			// ----
			if( Delay < 500 )
			{
				return false;
			}
			// ----
			this->Data[ObjectIDs[i]].EventTick = GetTickCount();
			gPartySearchSettings.ChangeClassValue(i);

			if (gPartySearchSettings.m_OneClass == true)
			{
				gPartySearchSettings.m_OneClass = false;
			}
		}
	}
	return false;
}

bool Interface::EventPartySettingsWindow_Close(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_CLOSE].EventTick);
	// ----
	if( !this->Data[ePARTYSETTINGS_MAIN].OnShow || !IsWorkZone(ePARTYSETTINGS_CLOSE) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[ePARTYSETTINGS_CLOSE].OnClick = true;
		return true;
	}
	// ----
	this->Data[ePARTYSETTINGS_CLOSE].OnClick = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[ePARTYSETTINGS_CLOSE].EventTick = GetTickCount();
	this->Data[ePARTYSETTINGS_MAIN].Close();
	// ----
	return false;
}

void Interface::DrawPartySearchWindow()
{
	if( !this->Data[ePARTYSEARCH_MAIN].OnShow )
	{
		return;
	}
	// ----
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 50.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	this->DrawGUI(ePARTYSEARCH_MAIN, StartX, StartY + 2);
	this->DrawGUI(ePARTYSEARCH_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(ePARTYSEARCH_FRAME, StartX, StartY + 67.0, 16);
	this->DrawGUI(ePARTYSEARCH_FOOTER, StartX, StartY);
	this->DrawGUI(ePARTYSEARCH_CLOSE, StartX + MainWidth - this->Data[ePARTYSEARCH_CLOSE].Width + 2, 49);
	// ----
	if( this->IsWorkZone(ePARTYSEARCH_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[ePARTYSEARCH_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(ePARTYSEARCH_CLOSE, this->Data[ePARTYSEARCH_CLOSE].X, this->Data[ePARTYSEARCH_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[ePARTYSEARCH_CLOSE].X + 5, this->Data[ePARTYSEARCH_CLOSE].Y + 25, "Cerrar");
	}
	// ----
	this->DrawFormat(eGold, StartX + 10, 60, 210, 3, "Party Search");
	// ----
	int x = GetPrivateProfileIntA("Graphics", "X", 0, "./Settings.ini");
	int y = GetPrivateProfileIntA("Graphics", "Y", 0, "./Settings.ini");
	// ----
	this->DrawFormat(eWhite, StartX + 20, this->Data[ePARTYSEARCH_MAIN].Y + 34, 40, 1, "Status:");

	if (gPartySearchSettings.m_SystemActive == false)
	{
		this->DrawFormat(eRed, StartX + 60, this->Data[ePARTYSEARCH_MAIN].Y + 34, 20, 1, "OFF");
	}
	else
	{
		this->DrawFormat(eShinyGreen, StartX + 60, this->Data[ePARTYSEARCH_MAIN].Y + 34, 20, 1, "ON");
	}
	
	// ----
	this->DrawGUI(ePARTYSETTINGS_DIV, StartX , this->Data[ePARTYSEARCH_MAIN].Y + 40); // Äåëèòåëü áîëüøîé
	// ----
	this->DrawFormat(eWhite, StartX + 5, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "Player");
	// ----
	this->DrawFormat(eWhite, StartX + 45, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "Map");
	// ----
	this->DrawFormat(eWhite, StartX + 95, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "X");
	// ----
	this->DrawFormat(eWhite, StartX + 115, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "Y");
	// ----
	this->DrawFormat(eWhite, StartX + 140, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "Count");
	// ----
	this->DrawFormat(eWhite, StartX + 170, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "Join");
	// ----
	this->DrawGUI(ePARTYSETTINGS_DIV, StartX , this->Data[ePARTYSEARCH_MAIN].Y + 60); // Äåëèòåëü áîëüøîé
	// ----
	if (gPartySearch.CountPages>1)
	{
		this->DrawFormat(eGold, StartX+104, 379, 20, 3, "%d/%d", gPartySearch.Page+1,gPartySearch.CountPages);
	}

	if (gPartySearch.Page+1 > 1)
	{
		this->DrawButton(ePARTYSEARCH_LEFT, StartX+73, 372, 0, 0);
	}

	if (gPartySearch.Page+1 < gPartySearch.CountPages)
	{
		this->DrawButton(ePARTYSEARCH_RIGHT, StartX+73+60, 372, 0, 0);
	}

	int DrawnItems = 0;

	for (int i=0;i<gPartySearch.ListsCount;i++)
	{
		if (DrawnItems >= 10)
		{
			break;
		}

		PARTYLIST* info = gPartySearch.GetPartyList(i+(10*gPartySearch.Page));

		if (info == 0)
		{
			continue;
		}

		pDrawGUI(0x7916/*0x7914*/, StartX + 10, this->Data[ePARTYSEARCH_MAIN].Y + 80+(20*i), 170, 21);

		this->DrawFormat(eYellow, StartX + 15, this->Data[ePARTYSEARCH_MAIN].Y + 86+(20*i), 50, 1, info->Name);

		this->DrawFormat(eWhite, StartX + 45, this->Data[ePARTYSEARCH_MAIN].Y + 86+(20*i), 50, 3, pGetMapName(info->Map));

		this->DrawFormat(eWhite, StartX + 95, this->Data[ePARTYSEARCH_MAIN].Y + 86+(20*i), 50, 3, "%d", info->X);

		this->DrawFormat(eWhite, StartX + 115, this->Data[ePARTYSEARCH_MAIN].Y + 86+(20*i), 50, 3, "%d", info->Y);

		this->DrawFormat(eWhite, StartX + 140, this->Data[ePARTYSEARCH_MAIN].Y + 86+(20*i), 50, 3, "%d / 5", info->Count);

		pDrawGUI(0x7915/*0x7913*/, StartX + 178, this->Data[ePARTYSEARCH_MAIN].Y + 80+(i*20), 22, 19);

		if (info->ButtonActive == true)
		{
			pDrawButton(0x7AA4, StartX + 203, this->Data[ePARTYSEARCH_MAIN].Y + 82+(i*20),16, 15, 0, 0);
		}

		int X = StartX + 203;
		int Y = this->Data[ePARTYSEARCH_MAIN].Y + 82+(i*20);
		int MaxX= X + 16;
		int MaxY= Y + 15;

		if (info->ButtonActive == true)
		{
			if (IsWorkZone2(X, Y,MaxX, MaxY))
			{
				pDrawColorButton(0x7AA4, X, Y,16, 15, 0, 16,eGray100);
				//pDrawButton(0x7AA4, X, Y,16, 15, 0, 16);
			}
		}

		DrawnItems++;
	}

	DrawnItems = 0;

	for (int i=0;i<gPartySearch.ListsCount;i++)
	{
		if (DrawnItems >= 10)
		{
			break;
		}

		PARTYLIST* info = gPartySearch.GetPartyList(i+(10*gPartySearch.Page));

		if (info == 0)
		{
			continue;
		}

		int X = StartX + 178;
		int Y = this->Data[ePARTYSEARCH_MAIN].Y + 80+(i*20);
		int MaxX= X + 22;
		int MaxY= Y + 19;

		if (IsWorkZone2(X, Y,MaxX, MaxY))
		{
			char szText[2048];
			sprintf(szText,"Requisitos:\n_____________________\nLevel:%d",info->Level);

			if (info->DarkWizard == true)
			{
				strcat(szText, "\nDark Wizard");
			}
			if (info->DarkKnight == true)
			{
				strcat(szText, "\nDark Knight");
			}
			if (info->Elf == true)
			{
				strcat(szText, "\nElf");
			}
			if (info->MagicGladiator == true)
			{
				strcat(szText, "\nMagic Gladiator");
			}
			if (info->DarkLord == true)
			{
				strcat(szText, "\nDark Lord");
			}
			if (info->Summoner == true)
			{
				strcat(szText, "\nSummoner");
			}
			if (info->RageFighter == true)
			{
				strcat(szText, "\nRage Fighter");
			}
			if (info->OnlyGuild == true)
			{
				strcat(szText,"\nOnly Guild");
			}

			strcat(szText, "\n_____________________");

			this->DrawToolTipEx(eWhite,StartX + 230,this->Data[ePARTYSEARCH_MAIN].Y + 62+(i*20),100,30,3,szText);
		}

		DrawnItems++;
	}

	if (gPartySearch.Page+1 > 1)
	{
		if( IsWorkZone(ePARTYSEARCH_LEFT) )
		{
			if( this->Data[ePARTYSEARCH_LEFT].OnClick )
			{
				this->DrawButton(ePARTYSEARCH_LEFT, StartX+73, 372, 0, 46);
				return;
			}
			this->DrawButton(ePARTYSEARCH_LEFT, StartX+73, 372, 0, 23);
		}
	}
	if (gPartySearch.Page+1 < gPartySearch.CountPages)
	{
		if( IsWorkZone(ePARTYSEARCH_RIGHT) )
		{
			if( this->Data[ePARTYSEARCH_RIGHT].OnClick )
			{
				this->DrawButton(ePARTYSEARCH_RIGHT, StartX+73+60, 372, 0, 46);
				return;
			}
			this->DrawButton(ePARTYSEARCH_RIGHT, StartX+73+60, 372, 0, 23);
		}
	}	

	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
}

void Interface::EventPartySearchWindow_All(DWORD Event)
{
	float StartX			= (MAX_WIN_WIDTH / 2) - (230.0 / 2);
	DWORD CurrentTick	= GetTickCount();
	if( !this->Data[ePARTYSEARCH_MAIN].OnShow )
	{
		return;
	}

	if (IsWorkZone(ePARTYSEARCH_CLOSE))
	{
		DWORD Delay			= (CurrentTick - this->Data[ePARTYSEARCH_CLOSE].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSEARCH_CLOSE].OnClick = true;
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_CLOSE].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_CLOSE].EventTick = GetTickCount();
		this->SwitchPartySearchWindowState();
	}
	if( IsWorkZone(ePARTYSEARCH_LEFT) && gPartySearch.Page+1 > 1)
	{
		DWORD Delay	= (CurrentTick - this->Data[ePARTYSEARCH_LEFT].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSEARCH_LEFT].OnClick = true;
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_LEFT].OnClick = false;
		// ----
		if( Delay < 100 )
		{
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_LEFT].EventTick = GetTickCount();
		// ----
		gPartySearch.Page--;
		//gPartySearch.DrawnItems = 0;
	}
	if( IsWorkZone(ePARTYSEARCH_RIGHT) && gPartySearch.Page+1 < gPartySearch.CountPages )
	{
		DWORD Delay	= (CurrentTick - this->Data[ePARTYSEARCH_RIGHT].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSEARCH_RIGHT].OnClick = true;
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_RIGHT].OnClick = false;
		// ----
		if( Delay < 100 )
		{
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_RIGHT].EventTick = GetTickCount();
		// ----
		gPartySearch.Page++;
		//gPartySearch.DrawnItems = 0;
	}

	int DrawnItems = 0;

	for (int i=0;i<gPartySearch.ListsCount;i++)
	{
		if (DrawnItems >= 10)
		{
			break;
		}
	
		if (IsWorkZone2(StartX + 203,this->Data[ePARTYSEARCH_MAIN].Y + 82+(i*20),StartX + 203 + 16, this->Data[ePARTYSEARCH_MAIN].Y + 82+(i*20)+15))
		{
			DWORD Delay	= (CurrentTick - this->Data[ePARTYSEARCH_RIGHT].EventTick);
			// ----
			if( Event == WM_LBUTTONDOWN )
			{
				this->Data[ePARTYSEARCH_RIGHT].OnClick = true;
				return;
			}
			// ----
			this->Data[ePARTYSEARCH_RIGHT].OnClick = false;
			// ----
			if( Delay < 100 )
			{
				return;
			}
			// ----
			if (gPartySearch.gPartyList[i+(10*gPartySearch.Page)].ButtonActive == false)
			{
				return;
			}
			// ----
			this->Data[ePARTYSEARCH_RIGHT].EventTick = GetTickCount();
			// ----
			gPartySearch.SendPartyRequest(i+(10*gPartySearch.Page));
		}
	}
}

// ========================================================== END PARTY SEARCH


//============================================ MULTIWARE
void Interface::DrawVaultWindow()
{
	if (!this->Data[eVAULT_MAIN].OnShow)
	{
		return;
	}
	// ----

	if(gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::FullMap)
		|| gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::Inventory)
		|| gInterface.CheckWindow(ObjWindow::Guild)
		|| gInterface.CheckWindow(ObjWindow::Party)
		|| gInterface.CheckWindow(ObjWindow::Character)
		|| gInterface.CheckWindow(ObjWindow::FastMenu)
		|| gInterface.CheckWindow(ObjWindow::FriendList)
		|| gInterface.CheckWindow(ObjWindow::GensInfo)
		|| gInterface.CheckWindow(ObjWindow::MuHelper)
		|| gInterface.CheckWindow(ObjWindow::Quest)
		|| gInterface.CheckWindow(ObjWindow::CommandWindow))
	{
		gInterface.CloseVaultWindow();
		gInterface.Data[eVAULT_MAIN].Close();
		return;
	}
	int JCResto;
	#if(WIDE_SCREEN == 1)
	JCResto =  pWinWidth / pWinHeightReal/ 2 -320;
#else
	JCResto =0;
#endif
	DWORD ItemNameColor = eWhite;
	float MainWidth = 230.0;
	float MainHeight = 313.0;
	float StartY = 100.0;
	float StartX = JCResto+(MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (140.0 / 2);
	// ----
	this->DrawGUI(eVAULT_MAIN, StartX, StartY + 2);
	this->DrawGUI(eVAULT_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(eVAULT_FRAME, StartX, StartY + 67.0, 13);
	this->DrawGUI(eVAULT_FOOTER, StartX, StartY);
	this->DrawGUI(eVAULT_CLOSE, StartX + MainWidth - this->Data[eVAULT_CLOSE].Width, this->Data[eVAULT_TITLE].Height + this->Data[eVAULT_CLOSE].Height + 2);
	// ----
	if (this->IsWorkZone(eVAULT_CLOSE))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eVAULT_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eVAULT_CLOSE, this->Data[eVAULT_CLOSE].X, this->Data[eVAULT_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[eVAULT_CLOSE].X + 5, this->Data[eVAULT_CLOSE].Y + 25, "Close");
	}
	// ----
	this->DrawFormat(eGold, StartX + 10, 110, 210, 3, "Multi Vault System");
	// ----
	this->DrawFormat(eRed, StartX + 10, 140, 210, 3, "Choose Ware!");
	this->DrawGUI(eVAULT_DIV, StartX, this->Data[eVAULT_FOOTER].Y - 10);
//------------------------------------------------------------------------------------------------------------
	this->DrawGUI(eVAULT_FINISH, ButtonX, this->Data[eVAULT_FOOTER].Y - 170);
	this->DrawFormat(eWhite, StartX - 40, this->Data[eVAULT_FOOTER].Y - 160, 210, 3, "Vault");
	this->Data[eVAULT_FINISH].Attribute = true;
	// ----
	if (IsWorkZone(eVAULT_FINISH))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eVAULT_FINISH].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eVAULT_FINISH, this->Data[eVAULT_FINISH].X, this->Data[eVAULT_FINISH].Y, Color);
	}
	// ----
//--------------------------------------------------------------------------------------
	this->DrawGUI(eWARE1_FINISH, ButtonX + 105, this->Data[eVAULT_FOOTER].Y - 170);
	this->DrawFormat(eWhite, StartX + 60, this->Data[eVAULT_FOOTER].Y - 160, 210, 3, "Ware 1");
	this->Data[eWARE1_FINISH].Attribute = true;
	// ----
	if (IsWorkZone(eWARE1_FINISH))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eWARE1_FINISH].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eWARE1_FINISH, this->Data[eWARE1_FINISH].X, this->Data[eWARE1_FINISH].Y, Color);
	}
//--------------------------------------------------------------------------------------
	this->DrawGUI(eWARE2_FINISH, ButtonX, this->Data[eVAULT_FOOTER].Y - 140);
	this->DrawFormat(eWhite, StartX -40, this->Data[eVAULT_FOOTER].Y - 130, 210, 3, "Ware 2");
	this->Data[eWARE2_FINISH].Attribute = true;
	// ----
	if (IsWorkZone(eWARE2_FINISH))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eWARE2_FINISH].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eWARE2_FINISH, this->Data[eWARE2_FINISH].X, this->Data[eWARE2_FINISH].Y, Color);
	}

//--------------------------------------------------------------------------------------
	this->DrawGUI(eWARE3_FINISH, ButtonX + 105, this->Data[eVAULT_FOOTER].Y - 140);
	this->DrawFormat(eWhite, StartX + 60, this->Data[eVAULT_FOOTER].Y - 130, 210, 3, "Ware 3");
	this->Data[eWARE3_FINISH].Attribute = true;
	// ----
	if (IsWorkZone(eWARE3_FINISH))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eWARE3_FINISH].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eWARE3_FINISH, this->Data[eWARE3_FINISH].X, this->Data[eWARE3_FINISH].Y, Color);
	}
//--------------------------------------------------------------------------------------
	this->DrawGUI(eWARE4_FINISH, ButtonX, this->Data[eVAULT_FOOTER].Y - 110);
	this->DrawFormat(eWhite, StartX - 40, this->Data[eVAULT_FOOTER].Y - 100, 210, 3, "Ware 4");
	this->Data[eWARE4_FINISH].Attribute = true;
	// ----
	if (IsWorkZone(eWARE4_FINISH))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eWARE4_FINISH].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eWARE4_FINISH, this->Data[eWARE4_FINISH].X, this->Data[eWARE4_FINISH].Y, Color);
	}
//--------------------------------------------------------------------------------------
	this->DrawGUI(eWARE5_FINISH, ButtonX + 105, this->Data[eVAULT_FOOTER].Y - 110);
	this->DrawFormat(eWhite, StartX + 60, this->Data[eVAULT_FOOTER].Y - 100, 210, 3, "Ware 5");
	this->Data[eWARE5_FINISH].Attribute = true;
	// ----
	if (IsWorkZone(eWARE5_FINISH))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eWARE5_FINISH].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eWARE5_FINISH, this->Data[eWARE5_FINISH].X, this->Data[eWARE5_FINISH].Y, Color);
	}
//--------------------------------------------------------------------------------------
	this->DrawGUI(eWARE6_FINISH, ButtonX, this->Data[eVAULT_FOOTER].Y - 80);
	this->DrawFormat(eWhite, StartX - 40, this->Data[eVAULT_FOOTER].Y - 70, 210, 3, "Ware 6");
	this->Data[eWARE6_FINISH].Attribute = true;
	// ----
	if (IsWorkZone(eWARE6_FINISH))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eWARE6_FINISH].OnClick)
		{
			Color = eGray150;
		}
		// ----
	this->DrawColoredGUI(eWARE6_FINISH, this->Data[eWARE6_FINISH].X, this->Data[eWARE6_FINISH].Y, Color);
	}
 //--------------------------------------------------------------------------------------
	this->DrawGUI(eWARE7_FINISH, ButtonX + 105, this->Data[eVAULT_FOOTER].Y - 80);
	this->DrawFormat(eWhite, StartX + 60, this->Data[eVAULT_FOOTER].Y - 70, 210, 3, "Ware 7");
	this->Data[eWARE7_FINISH].Attribute = true;
	// ----
	if (IsWorkZone(eWARE7_FINISH))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eWARE7_FINISH].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eWARE7_FINISH, this->Data[eWARE7_FINISH].X, this->Data[eWARE7_FINISH].Y, Color);
	}
//--------------------------------------------------------------------------------------
	this->DrawGUI(eWARE8_FINISH, ButtonX, this->Data[eVAULT_FOOTER].Y - 50);
	this->DrawFormat(eWhite, StartX - 40, this->Data[eVAULT_FOOTER].Y - 40, 210, 3, "Ware 8");
	this->Data[eWARE8_FINISH].Attribute = true;
	// ----
	if (IsWorkZone(eWARE8_FINISH))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eWARE8_FINISH].OnClick)
		{
			Color = eGray150;
		}
		// ----
	this->DrawColoredGUI(eWARE8_FINISH, this->Data[eWARE8_FINISH].X, this->Data[eWARE8_FINISH].Y, Color);
	}
//--------------------------------------------------------------------------------------
	this->DrawGUI(eWARE9_FINISH, ButtonX + 105, this->Data[eVAULT_FOOTER].Y - 50);
	this->DrawFormat(eWhite, StartX + 60, this->Data[eVAULT_FOOTER].Y - 40, 210, 3, "Ware 9");
	this->Data[eWARE9_FINISH].Attribute = true;
	// ----
	if (IsWorkZone(eWARE9_FINISH))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eWARE9_FINISH].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eWARE9_FINISH, this->Data[eWARE9_FINISH].X, this->Data[eWARE9_FINISH].Y, Color);
	}
 //-------------------------------------------------------------------------------------- }
}
bool Interface::EventVaultWindow_Main(DWORD Event)
{
	this->EventVaultWindow_Close(Event);
	this->EventVaultWindow_Finish(Event);
	this->EventWARE1Window_Finish(Event);
	this->EventWARE2Window_Finish(Event);
	this->EventWARE3Window_Finish(Event);
	this->EventWARE4Window_Finish(Event);
	this->EventWARE5Window_Finish(Event);
	this->EventWARE6Window_Finish(Event);
	this->EventWARE7Window_Finish(Event);
	this->EventWARE8Window_Finish(Event);
	this->EventWARE9Window_Finish(Event);
	return true;
}
bool Interface::EventVaultWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eVAULT_CLOSE].EventTick);
	// ----
	if (!this->Data[eVAULT_MAIN].OnShow || !IsWorkZone(eVAULT_CLOSE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eVAULT_CLOSE].OnClick = true;
		return true;
	}
	// ----
	this->Data[eVAULT_CLOSE].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eVAULT_CLOSE].EventTick = GetTickCount();
	this->CloseVaultWindow();
	// ----
	return false;
}

bool Interface::EventVaultWindow_Finish(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eVAULT_FINISH].EventTick);
	// ----
	if (!this->Data[eVAULT_MAIN].OnShow || !IsWorkZone(eVAULT_FINISH)
		|| !this->Data[eVAULT_FINISH].Attribute)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eVAULT_FINISH].OnClick = true;
		return true;
	}
	// ----
	this->Data[eVAULT_FINISH].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eVAULT_FINISH].EventTick = GetTickCount();

	gWarehousePanel.CGSendWarehouseOpen(0);

	this->CloseVaultWindow();
	// ----
	return false;
}
bool Interface::EventWARE1Window_Finish(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eWARE1_FINISH].EventTick);
	// ----
	if (!this->Data[eVAULT_MAIN].OnShow || !IsWorkZone(eWARE1_FINISH)
		|| !this->Data[eWARE1_FINISH].Attribute)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eWARE1_FINISH].OnClick = true;
		return true;
	}
	// ----
	this->Data[eWARE1_FINISH].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eWARE1_FINISH].EventTick = GetTickCount();

	gWarehousePanel.CGSendWarehouseOpen(1);

	this->CloseVaultWindow();
	// ----

	return false;
}
bool Interface::EventWARE2Window_Finish(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eWARE2_FINISH].EventTick);
	// ----
	if (!this->Data[eVAULT_MAIN].OnShow || !IsWorkZone(eWARE2_FINISH)
		|| !this->Data[eWARE2_FINISH].Attribute)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eWARE2_FINISH].OnClick = true;
		return true;
	}
	// ----
	this->Data[eWARE2_FINISH].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eWARE2_FINISH].EventTick = GetTickCount();

	gWarehousePanel.CGSendWarehouseOpen(2);

	this->CloseVaultWindow();
	// ----
	return false;
}
bool Interface::EventWARE3Window_Finish(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eWARE3_FINISH].EventTick);
	// ----
	if (!this->Data[eVAULT_MAIN].OnShow || !IsWorkZone(eWARE3_FINISH)
		|| !this->Data[eWARE3_FINISH].Attribute)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eWARE3_FINISH].OnClick = true;
		return true;
	}
	// ----
	this->Data[eWARE3_FINISH].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eWARE3_FINISH].EventTick = GetTickCount();

	gWarehousePanel.CGSendWarehouseOpen(3);

	this->CloseVaultWindow();
	// ----
	return false;
}
bool Interface::EventWARE4Window_Finish(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eWARE4_FINISH].EventTick);
	// ----
	if (!this->Data[eVAULT_MAIN].OnShow || !IsWorkZone(eWARE4_FINISH)
		|| !this->Data[eWARE4_FINISH].Attribute)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eWARE4_FINISH].OnClick = true;
		return true;
	}
	// ----
	this->Data[eWARE4_FINISH].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eWARE4_FINISH].EventTick = GetTickCount();

	gWarehousePanel.CGSendWarehouseOpen(4);

	this->CloseVaultWindow();
	// ----
	return false;
}
bool Interface::EventWARE5Window_Finish(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eWARE5_FINISH].EventTick);
	// ----
	if (!this->Data[eVAULT_MAIN].OnShow || !IsWorkZone(eWARE5_FINISH)
		|| !this->Data[eWARE5_FINISH].Attribute)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eWARE5_FINISH].OnClick = true;
		return true;
	}
	// ----
	this->Data[eWARE5_FINISH].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eWARE5_FINISH].EventTick = GetTickCount();

	gWarehousePanel.CGSendWarehouseOpen(5);

	this->CloseVaultWindow();
	// ----
	return false;
}
bool Interface::EventWARE6Window_Finish(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eWARE6_FINISH].EventTick);
	// ----
	if (!this->Data[eVAULT_MAIN].OnShow || !IsWorkZone(eWARE6_FINISH)
		|| !this->Data[eWARE6_FINISH].Attribute)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eWARE6_FINISH].OnClick = true;
		return true;
	}
	// ----
	this->Data[eWARE6_FINISH].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eWARE6_FINISH].EventTick = GetTickCount();

	gWarehousePanel.CGSendWarehouseOpen(6);

	this->CloseVaultWindow();
	// ----
	return false;
}
bool Interface::EventWARE7Window_Finish(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eWARE7_FINISH].EventTick);
	// ----
	if (!this->Data[eVAULT_MAIN].OnShow || !IsWorkZone(eWARE7_FINISH)
		|| !this->Data[eWARE7_FINISH].Attribute)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eWARE7_FINISH].OnClick = true;
		return true;
	}
	// ----
	this->Data[eWARE7_FINISH].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eWARE7_FINISH].EventTick = GetTickCount();

	gWarehousePanel.CGSendWarehouseOpen(7);

	this->CloseVaultWindow();
	// ----
	return false;
}
bool Interface::EventWARE8Window_Finish(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eWARE8_FINISH].EventTick);
	// ----
	if (!this->Data[eVAULT_MAIN].OnShow || !IsWorkZone(eWARE8_FINISH)
		|| !this->Data[eWARE8_FINISH].Attribute)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eWARE8_FINISH].OnClick = true;
		return true;
	}
	// ----
	this->Data[eWARE8_FINISH].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eWARE8_FINISH].EventTick = GetTickCount();

	gWarehousePanel.CGSendWarehouseOpen(8);

	this->CloseVaultWindow();
	// ----
	return false;
}
bool Interface::EventWARE9Window_Finish(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eWARE9_FINISH].EventTick);
	// ----
	if (!this->Data[eVAULT_MAIN].OnShow || !IsWorkZone(eWARE9_FINISH)
		|| !this->Data[eWARE9_FINISH].Attribute)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eWARE9_FINISH].OnClick = true;
		return true;
	}
	// ----
	this->Data[eWARE9_FINISH].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eWARE9_FINISH].EventTick = GetTickCount();

	gWarehousePanel.CGSendWarehouseOpen(9);

	this->CloseVaultWindow();
	// ----
	return false;
}
// ========================================================== END MULTIWARE


//============================================ MULTIWARE
void Interface::DrawChangingClassWindow()
{
	if( !this->Data[eCHANGINGCLASS_MAIN].OnShow )
	{
		return;
	}

	if(gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::FullMap)
		|| gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::Inventory)
		|| gInterface.CheckWindow(ObjWindow::Guild)
		|| gInterface.CheckWindow(ObjWindow::Party)
		|| gInterface.CheckWindow(ObjWindow::Character)
		|| gInterface.CheckWindow(ObjWindow::FastMenu)
		|| gInterface.CheckWindow(ObjWindow::FriendList)
		|| gInterface.CheckWindow(ObjWindow::GensInfo)
		|| gInterface.CheckWindow(ObjWindow::MuHelper)
		|| gInterface.CheckWindow(ObjWindow::Quest)
		|| gInterface.CheckWindow(ObjWindow::CommandWindow))
	{
		this->Data[eCHANGINGCLASS_MAIN].OnShow		= false;
		gInterface.Data[eCHANGINGCLASS_MAIN].Close();		
		return;
	}
	// ----
	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	this->DrawGUI(eCHANGINGCLASS_MAIN, StartX, StartY + 2);
	this->DrawGUI(eCHANGINGCLASS_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(eCHANGINGCLASS_FRAME, StartX, StartY + 67.0, 13);
	this->DrawGUI(eCHANGINGCLASS_FOOTER, StartX, StartY);
	this->DrawGUI(eCHANGINGCLASS_CLOSE, StartX + MainWidth - this->Data[eCHANGINGCLASS_CLOSE].Width, this->Data[eCHANGINGCLASS_TITLE].Height + this->Data[eCHANGINGCLASS_CLOSE].Height + 2);
	// ----
	if( this->IsWorkZone(eCHANGINGCLASS_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGINGCLASS_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGINGCLASS_CLOSE, this->Data[eCHANGINGCLASS_CLOSE].X, this->Data[eCHANGINGCLASS_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[eCHANGINGCLASS_CLOSE].X + 5, this->Data[eCHANGINGCLASS_CLOSE].Y + 25, "Close");
	}
	// ----
	this->DrawFormat(eGold, StartX + 10, 110, 210, 3, "Changing Class System");
	// ----
	if (gChangeClass.m_PriceType == 0)
	{
		this->DrawFormat(eGold, StartX + 30, 355, 210, 1, "Required Zen:");
	}
	else if (gChangeClass.m_PriceType == 1)
	{
		this->DrawFormat(eGold, StartX + 30, 355, 210, 1, "Required %s:",gCustomMessage.GetMessage(6));
	}
	else if (gChangeClass.m_PriceType == 2)
	{
		this->DrawFormat(eGold, StartX + 30, 355, 210, 1, "Required %s:",gCustomMessage.GetMessage(7));
	}
	else if (gChangeClass.m_PriceType == 3)
	{
		this->DrawFormat(eGold, StartX + 30, 355, 210, 1, "Required %s:",gCustomMessage.GetMessage(13));
	}
	else if (gChangeClass.m_PriceType == 4)
	{
		this->DrawFormat(eGold, StartX + 30, 355, 210, 1, "Required %s:",gCustomMessage.GetMessage(14));
	}

	this->DrawGUI(eCHANGINGCLASS_MONEYBG, StartX + 30, 365);
	// ----
	char MoneyBuff[50], MoneyBuff2[50];
	ZeroMemory(MoneyBuff, sizeof(MoneyBuff));
	ZeroMemory(MoneyBuff2, sizeof(MoneyBuff2));
	// ----
	pGetMoneyFormat((double)gChangeClass.m_Price,MoneyBuff, 0);
	this->DrawFormat(eGold, StartX + 70, 372, 70, 1, "%s", MoneyBuff);
	// ----

	// ----
	this->DrawGUI(eCHANGINGCLASS_DW, ButtonX - 57, this->Data[eCHANGINGCLASS_MAIN].Y + 30);
	this->DrawFormat(eWhite, StartX - 45, this->Data[eCHANGINGCLASS_MAIN].Y + 40, 210, 3, "%s class",pGetTextLine(pTextLineThis,20));
	// ----
	this->DrawGUI(eCHANGINGCLASS_DK, ButtonX + 52, this->Data[eCHANGINGCLASS_MAIN].Y + 30);
	this->DrawFormat(eWhite, StartX + 62, this->Data[eCHANGINGCLASS_MAIN].Y + 40, 210, 3, "%s class",pGetTextLine(pTextLineThis,21));
	// ----
	this->DrawGUI(eCHANGINGCLASS_ELF, ButtonX - 57, this->Data[eCHANGINGCLASS_MAIN].Y + 60);
	this->DrawFormat(eWhite, StartX - 45, this->Data[eCHANGINGCLASS_MAIN].Y + 70, 210, 3, "%s class",pGetTextLine(pTextLineThis,22));
	// ----
	this->DrawGUI(eCHANGINGCLASS_MG, ButtonX + 52, this->Data[eCHANGINGCLASS_MAIN].Y + 60);
	this->DrawFormat(eWhite, StartX + 62, this->Data[eCHANGINGCLASS_MAIN].Y + 70, 210, 3, "%s class",pGetTextLine(pTextLineThis,23));
	// ----
	if (gProtect.m_MainInfo.RemoveClass != 1)
	{
		this->DrawGUI(eCHANGINGCLASS_DL, ButtonX - 57, this->Data[eCHANGINGCLASS_MAIN].Y + 90);
		this->DrawFormat(eWhite, StartX - 45, this->Data[eCHANGINGCLASS_MAIN].Y + 100, 210, 3, "%s class",pGetTextLine(pTextLineThis,24));
	}
	// ----
	if (gProtect.m_MainInfo.RemoveClass != 1 && gProtect.m_MainInfo.RemoveClass != 2)
	{
		this->DrawGUI(eCHANGINGCLASS_SUM, ButtonX + 52, this->Data[eCHANGINGCLASS_MAIN].Y + 90);
		this->DrawFormat(eWhite, StartX + 62, this->Data[eCHANGINGCLASS_MAIN].Y + 100, 210, 3, "%s class",pGetTextLine(pTextLineThis,1687));
	}
	// ----
	if (gProtect.m_MainInfo.RemoveClass != 1 && gProtect.m_MainInfo.RemoveClass != 2 && gProtect.m_MainInfo.RemoveClass != 3)
	{
		this->DrawGUI(eCHANGINGCLASS_RF, ButtonX, this->Data[eCHANGINGCLASS_MAIN].Y + 120);
		this->DrawFormat(eWhite, StartX + 8, this->Data[eCHANGINGCLASS_MAIN].Y + 130, 210, 3, "%s class",pGetTextLine(pTextLineThis,3150));
	}
	// ----
	this->DrawGUI(eCHANGINGCLASS_DIV, StartX, this->Data[eCHANGINGCLASS_MAIN].Y + 212);
	// ----
	this->Data[eCHANGINGCLASS_DW].Attribute = true;
	this->Data[eCHANGINGCLASS_DK].Attribute = true;
	this->Data[eCHANGINGCLASS_ELF].Attribute = true;
	this->Data[eCHANGINGCLASS_MG].Attribute = true;
	this->Data[eCHANGINGCLASS_DL].Attribute = true;
	this->Data[eCHANGINGCLASS_SUM].Attribute = true;
	this->Data[eCHANGINGCLASS_RF].Attribute = true;
	// ----
	if( IsWorkZone(eCHANGINGCLASS_DW) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGINGCLASS_DW].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGINGCLASS_DW, this->Data[eCHANGINGCLASS_DW].X, this->Data[eCHANGINGCLASS_DW].Y, Color);
	}
	if( IsWorkZone(eCHANGINGCLASS_DK) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGINGCLASS_DK].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGINGCLASS_DK, this->Data[eCHANGINGCLASS_DK].X, this->Data[eCHANGINGCLASS_DK].Y, Color);
	}
	if( IsWorkZone(eCHANGINGCLASS_ELF) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGINGCLASS_ELF].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGINGCLASS_ELF, this->Data[eCHANGINGCLASS_ELF].X, this->Data[eCHANGINGCLASS_ELF].Y, Color);
	}
	if( IsWorkZone(eCHANGINGCLASS_MG) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGINGCLASS_MG].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGINGCLASS_MG, this->Data[eCHANGINGCLASS_MG].X, this->Data[eCHANGINGCLASS_MG].Y, Color);
	}
	if( IsWorkZone(eCHANGINGCLASS_DL) )
	{
		if (gProtect.m_MainInfo.RemoveClass != 1)
		{
			DWORD Color = eGray100;
			// ----
			if( this->Data[eCHANGINGCLASS_DL].OnClick )
			{
				Color = eGray150;
			}
			// ----
			this->DrawColoredGUI(eCHANGINGCLASS_DL, this->Data[eCHANGINGCLASS_DL].X, this->Data[eCHANGINGCLASS_DL].Y, Color);
		}
	}
	if( IsWorkZone(eCHANGINGCLASS_SUM) )
	{
		if (gProtect.m_MainInfo.RemoveClass != 1 || gProtect.m_MainInfo.RemoveClass != 2)
		{
			DWORD Color = eGray100;
			// ----
			if( this->Data[eCHANGINGCLASS_SUM].OnClick )
			{
				Color = eGray150;
			}
			// ----
			this->DrawColoredGUI(eCHANGINGCLASS_SUM, this->Data[eCHANGINGCLASS_SUM].X, this->Data[eCHANGINGCLASS_SUM].Y, Color);
		}
	}
	if( IsWorkZone(eCHANGINGCLASS_RF) )
	{
		if (gProtect.m_MainInfo.RemoveClass != 1 || gProtect.m_MainInfo.RemoveClass != 2 || gProtect.m_MainInfo.RemoveClass != 3)
		{
			DWORD Color = eGray100;
			// ----
			if( this->Data[eCHANGINGCLASS_RF].OnClick )
			{
				Color = eGray150;
			}
			// ----
			this->DrawColoredGUI(eCHANGINGCLASS_RF, this->Data[eCHANGINGCLASS_RF].X, this->Data[eCHANGINGCLASS_RF].Y, Color);
		}
	}

}
bool Interface::EventChangingClassWindow_Main(DWORD Event)
{
	this->EventChangingClassWindow_Close(Event);
	this->EventChangingClassWindow_DW(Event);
	this->EventChangingClassWindow_DK(Event);
	this->EventChangingClassWindow_ELF(Event);
	this->EventChangingClassWindow_MG(Event);
	this->EventChangingClassWindow_DL(Event);
	this->EventChangingClassWindow_SUM(Event);
	this->EventChangingClassWindow_RF(Event);
	return true;
}
bool Interface::EventChangingClassWindow_Close(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGINGCLASS_CLOSE].EventTick);
	// ----
	if( !this->Data[eCHANGINGCLASS_MAIN].OnShow || !IsWorkZone(eCHANGINGCLASS_CLOSE) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGINGCLASS_CLOSE].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGINGCLASS_CLOSE].OnClick = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGINGCLASS_CLOSE].EventTick = GetTickCount();
	this->Data[eCHANGINGCLASS_MAIN].Close();
	// ----
	return false;
}

bool Interface::EventChangingClassWindow_DW(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGINGCLASS_DW].EventTick);
	// ----
	DWORD DelayUserPanel = (GetTickCount() - this->Data[eMenu_CHANGECLASS].EventTick);
	if (DelayUserPanel < 1000)
	{
		return false;
	}
	// ----
	if( !this->Data[eCHANGINGCLASS_MAIN].OnShow || !IsWorkZone(eCHANGINGCLASS_DW) 
		|| !this->Data[eCHANGINGCLASS_DW].Attribute )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGINGCLASS_DW].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGINGCLASS_DW].OnClick = false;;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGINGCLASS_DW].EventTick = GetTickCount();

	gChangeClass.SendChangeClass(0);

	this->Data[eCHANGINGCLASS_MAIN].Close();
	this->Data[eCHANGINGCLASS_CLOSE].Close();
	// ----
	return false;
}
bool Interface::EventChangingClassWindow_DK(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGINGCLASS_DK].EventTick);
	// ----
	DWORD DelayUserPanel = (GetTickCount() - this->Data[eMenu_CHANGECLASS].EventTick);
	if (DelayUserPanel < 1000)
	{
		return false;
	}
	// ----
	if( !this->Data[eCHANGINGCLASS_MAIN].OnShow || !IsWorkZone(eCHANGINGCLASS_DK) 
		|| !this->Data[eCHANGINGCLASS_DK].Attribute )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGINGCLASS_DK].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGINGCLASS_DK].OnClick = false;;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGINGCLASS_DK].EventTick = GetTickCount();

	gChangeClass.SendChangeClass(16);

	this->Data[eCHANGINGCLASS_MAIN].Close();
	this->Data[eCHANGINGCLASS_CLOSE].Close();
	// ----
	return false;
}
bool Interface::EventChangingClassWindow_ELF(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGINGCLASS_ELF].EventTick);
	// ----
	DWORD DelayUserPanel = (GetTickCount() - this->Data[eMenu_CHANGECLASS].EventTick);
	if (DelayUserPanel < 1000)
	{
		return false;
	}
	// ----
	if( !this->Data[eCHANGINGCLASS_MAIN].OnShow || !IsWorkZone(eCHANGINGCLASS_ELF) 
		|| !this->Data[eCHANGINGCLASS_ELF].Attribute )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGINGCLASS_ELF].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGINGCLASS_ELF].OnClick = false;;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGINGCLASS_ELF].EventTick = GetTickCount();

	gChangeClass.SendChangeClass(32);

	this->Data[eCHANGE_RESET_CLOSE].Close();
	// ----
	return false;
}
bool Interface::EventChangingClassWindow_MG(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGINGCLASS_MG].EventTick);
	// ----
	DWORD DelayUserPanel = (GetTickCount() - this->Data[eMenu_CHANGECLASS].EventTick);
	if (DelayUserPanel < 1000)
	{
		return false;
	}
	// ----
	if( !this->Data[eCHANGINGCLASS_MAIN].OnShow || !IsWorkZone(eCHANGINGCLASS_MG) 
		|| !this->Data[eCHANGINGCLASS_MG].Attribute )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGINGCLASS_MG].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGINGCLASS_MG].OnClick = false;;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGINGCLASS_MG].EventTick = GetTickCount();

	gChangeClass.SendChangeClass(48);

	this->Data[eCHANGINGCLASS_MAIN].Close();
	this->Data[eCHANGINGCLASS_CLOSE].Close();
	// ----
	return false;
}
bool Interface::EventChangingClassWindow_DL(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGINGCLASS_DL].EventTick);
	// ----
	DWORD DelayUserPanel = (GetTickCount() - this->Data[eMenu_CHANGECLASS].EventTick);
	if (DelayUserPanel < 1000)
	{
		return false;
	}
	// ----
	if( !this->Data[eCHANGINGCLASS_MAIN].OnShow || !IsWorkZone(eCHANGINGCLASS_DL) 
		|| !this->Data[eCHANGINGCLASS_DL].Attribute )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGINGCLASS_DL].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGINGCLASS_DL].OnClick = false;;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGINGCLASS_DL].EventTick = GetTickCount();

	gChangeClass.SendChangeClass(64);

	this->Data[eCHANGINGCLASS_MAIN].Close();
	this->Data[eCHANGINGCLASS_CLOSE].Close();
	// ----
	return false;
}
bool Interface::EventChangingClassWindow_SUM(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGINGCLASS_SUM].EventTick);
	// ----
	DWORD DelayUserPanel = (GetTickCount() - this->Data[eMenu_CHANGECLASS].EventTick);
	if (DelayUserPanel < 1000)
	{
		return false;
	}
	// ----
	if( !this->Data[eCHANGINGCLASS_MAIN].OnShow || !IsWorkZone(eCHANGINGCLASS_SUM) 
		|| !this->Data[eCHANGINGCLASS_SUM].Attribute )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGINGCLASS_SUM].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGINGCLASS_SUM].OnClick = false;;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGINGCLASS_SUM].EventTick = GetTickCount();

	gChangeClass.SendChangeClass(80);

	this->Data[eCHANGINGCLASS_MAIN].Close();
	this->Data[eCHANGINGCLASS_CLOSE].Close();
	// ----
	return false;
}
bool Interface::EventChangingClassWindow_RF(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGINGCLASS_RF].EventTick);
	// ----
	DWORD DelayUserPanel = (GetTickCount() - this->Data[eMenu_CHANGECLASS].EventTick);
	if (DelayUserPanel < 1000)
	{
		return false;
	}
	// ----
	if( !this->Data[eCHANGINGCLASS_MAIN].OnShow || !IsWorkZone(eCHANGINGCLASS_RF) 
		|| !this->Data[eCHANGINGCLASS_RF].Attribute )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGINGCLASS_RF].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGINGCLASS_RF].OnClick = false;;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGINGCLASS_RF].EventTick = GetTickCount();

	gChangeClass.SendChangeClass(96);

	this->Data[eCHANGINGCLASS_MAIN].Close();
	this->Data[eCHANGINGCLASS_CLOSE].Close();
	// ----
	return false;
}
// ========================================================== END ChangeClass

//============================================ LUCKY WHELL
void testfunc()
{
    glMatrixMode(0x1700u);
    glPopMatrix();
    glMatrixMode(0x1701u);
    glPopMatrix();
}
void Interface::DrawItem2(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse) // code hien thi item
{
 
    glMatrixMode(0x1701);
    glPushMatrix();
    glLoadIdentity();
 
    //float X = ull_to_float2(*(QWORD*)0xE61E58);
    //float Y = ull_to_float2(*(QWORD*)0xE61E58+1);
 
    sub_6363D0_Addr(0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y);
    //float v2 = (X / (Y / 100.0f)) / 100.0f;//(*(float*)MAIN_RESOLUTION_X / (*(float*)MAIN_RESOLUTION_Y / 100.0f)) / 100.0f;
    float v2 = *(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;
    sub_6358A0_Addr(1.0, v2, *(float*)0xE61E38, *(float*)0xE61E3C);
 
    glMatrixMode(0x1700);
    glPushMatrix();
    glLoadIdentity();
 
    sub_635830_Addr((LPVOID)0x87933A0);
    sub_635DE0_Addr();
    sub_635E40_Addr();
 
    //posX
    //posY
    //Width
    //Height
    //unk
    // 1 - Excellent Effect
    // 1 - Aura +7
    // 1 - original size
    //glClear(0x100u);
    pDrawItemModel(PosX, PosY, Width, Height, ItemID, Level, Excl, Anc, OnMouse);
   
    testfunc();
    //sub_637770_Addr();
 
    glColor3f(1,1,1);
    pSetBlend(false);
}

void Interface::DrawLuckyWheel()
{
	if (!gInterface.Data[eLuckyWheelMain].OnShow)
	{
		return;
	}


	if(gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::FullMap)
		|| gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::Guild)
		|| gInterface.CheckWindow(ObjWindow::Party)
		|| gInterface.CheckWindow(ObjWindow::Character)
		|| gInterface.CheckWindow(ObjWindow::FastMenu)
		|| gInterface.CheckWindow(ObjWindow::FriendList)
		|| gInterface.CheckWindow(ObjWindow::GensInfo)
		|| gInterface.CheckWindow(ObjWindow::MuHelper)
		|| gInterface.CheckWindow(ObjWindow::Quest)
		|| gInterface.CheckWindow(ObjWindow::CommandWindow))
	{
		this->Data[eLuckyWheelMain].OnShow		= false;
		gInterface.Data[eLuckyWheelMain].Close();		
		return;
	}
	int JCResto;
	#if(WIDE_SCREEN == 1)
	JCResto =  pWinWidth / pWinHeightReal/ 2 -320;
#else
	JCResto =0;
#endif
	pDrawGUI(0x9328,JCResto+ 145, 55, 312, 292); //1
	pDrawGUI(0x9326,JCResto+ 160, 100, 70, 57); //1
	pDrawGUI(0x9326,JCResto+ 230, 100, 70, 57); //2
	pDrawGUI(0x9326,JCResto+ 300, 100, 70, 57); //3
	pDrawGUI(0x9326,JCResto+ 370, 100, 70, 57); //4
	pDrawGUI(0x9326,JCResto+ 370, 157, 70, 57); //5
	pDrawGUI(0x9326,JCResto+ 370, 214, 70, 57); //6
	pDrawGUI(0x9326,JCResto+ 370, 271, 70, 57); //7
	pDrawGUI(0x9326,JCResto+ 300, 271, 70, 57); //8
	pDrawGUI(0x9326,JCResto+ 230, 271, 70, 57); //9
	pDrawGUI(0x9326,JCResto+ 160, 271, 70, 57); //10
	pDrawGUI(0x9326,JCResto+ 160, 157, 70, 57); //11
	pDrawGUI(0x9326,JCResto+ 160, 214, 70, 57); //12
	if(this->LuckyWheelNumber >= 0)
	{
		pSetBlend(true);
		glColor4f(1.0, 1.0, 0.0, 0.3);
		switch (LuckyWheelNumber)
		{
		case 0:
			pDrawBarForm(JCResto+160, 100, 70, 57, 0, 0);
		break;
		case 1:
			pDrawBarForm(JCResto+230, 100, 70, 57, 0, 0);
		break;
		case 2:
			pDrawBarForm(JCResto+300, 100, 70, 57, 0, 0);
		break;
		case 3:
			pDrawBarForm(JCResto+370, 100, 70, 57, 0, 0);
		break;
		case 4:
			pDrawBarForm(JCResto+370, 157, 70, 57, 0, 0);
		break;
		case 5:
			pDrawBarForm(JCResto+370, 214, 70, 57, 0, 0);
		break;
		case 6:
			pDrawBarForm(JCResto+370, 271, 70, 57, 0, 0);
		break;
		case 7:
			pDrawBarForm(JCResto+300, 271, 70, 57, 0, 0);
		break;
		case 8:
			pDrawBarForm(JCResto+230, 271, 70, 57, 0, 0);
		break;
		case 9:
			pDrawBarForm(JCResto+160, 271, 70, 57, 0, 0);
		break;
		case 10:
			pDrawBarForm(JCResto+160, 157, 70, 57, 0, 0);
		break;
		case 11:
			pDrawBarForm(JCResto+160, 214, 70, 57, 0, 0);
		break;
		}
		pGLSwitchBlend();
		glColor3f(1.0, 1.0, 1.0);
	}

	if(this->StartRoll >= 1)
	{
		pSetBlend(true);
		glColor4f(1.0, 1.0, 0.0, 0.3);
		int roll = rand() % 12;
		switch (roll)
		{
		case 0:
			pDrawBarForm(JCResto+160, 100, 70, 57, 0, 0);
		break;
		case 1:
			pDrawBarForm(JCResto+230, 100, 70, 57, 0, 0);
		break;
		case 2:
			pDrawBarForm(JCResto+300, 100, 70, 57, 0, 0);
		break;
		case 3:
			pDrawBarForm(JCResto+370, 100, 70, 57, 0, 0);
		break;
		case 4:
			pDrawBarForm(JCResto+370, 157, 70, 57, 0, 0);
		break;
		case 5:
			pDrawBarForm(JCResto+370, 214, 70, 57, 0, 0);
		break;
		case 6:
			pDrawBarForm(JCResto+370, 271, 70, 57, 0, 0);
		break;
		case 7:
			pDrawBarForm(JCResto+300, 271, 70, 57, 0, 0);
		break;
		case 8:
			pDrawBarForm(JCResto+230, 271, 70, 57, 0, 0);
		break;
		case 9:
			pDrawBarForm(JCResto+160, 271, 70, 57, 0, 0);
		break;
		case 10:
			pDrawBarForm(JCResto+160, 157, 70, 57, 0, 0);
		break;
		case 11:
			pDrawBarForm(JCResto+160, 214, 70, 57, 0, 0);
		break;
		}
		pGLSwitchBlend();
		glColor3f(1.0, 1.0, 1.0);
	}
	gInterface.DrawItem2(JCResto+163,100,70,50,ITEM(gLuckyWheel.m_LuckyWheelInfo[0].ItemType,gLuckyWheel.m_LuckyWheelInfo[0].ItemIndex),SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[0].Level),gLuckyWheel.m_LuckyWheelInfo[0].Exc,0,0);
	gInterface.DrawItem2(JCResto+237,100,65,47,ITEM(gLuckyWheel.m_LuckyWheelInfo[1].ItemType,gLuckyWheel.m_LuckyWheelInfo[1].ItemIndex),SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[1].Level),gLuckyWheel.m_LuckyWheelInfo[1].Exc,0,0);
	gInterface.DrawItem2(JCResto+307,100,65,47,ITEM(gLuckyWheel.m_LuckyWheelInfo[2].ItemType,gLuckyWheel.m_LuckyWheelInfo[2].ItemIndex),SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[2].Level),gLuckyWheel.m_LuckyWheelInfo[2].Exc,0,0);
	gInterface.DrawItem2(JCResto+377,100,65,50,ITEM(gLuckyWheel.m_LuckyWheelInfo[3].ItemType,gLuckyWheel.m_LuckyWheelInfo[3].ItemIndex),SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[3].Level),gLuckyWheel.m_LuckyWheelInfo[3].Exc,0,0);
	gInterface.DrawItem2(JCResto+377,157,65,50,ITEM(gLuckyWheel.m_LuckyWheelInfo[4].ItemType,gLuckyWheel.m_LuckyWheelInfo[4].ItemIndex),SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[4].Level),gLuckyWheel.m_LuckyWheelInfo[4].Exc,0,0);
	gInterface.DrawItem2(JCResto+377,214,63,50,ITEM(gLuckyWheel.m_LuckyWheelInfo[5].ItemType,gLuckyWheel.m_LuckyWheelInfo[5].ItemIndex),SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[5].Level),gLuckyWheel.m_LuckyWheelInfo[5].Exc,0,0);
	gInterface.DrawItem2(JCResto+377,271,70,45,ITEM(gLuckyWheel.m_LuckyWheelInfo[6].ItemType,gLuckyWheel.m_LuckyWheelInfo[6].ItemIndex),SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[6].Level),gLuckyWheel.m_LuckyWheelInfo[6].Exc,0,0);
	gInterface.DrawItem2(JCResto+307,271,70,45,ITEM(gLuckyWheel.m_LuckyWheelInfo[7].ItemType,gLuckyWheel.m_LuckyWheelInfo[7].ItemIndex),SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[7].Level),gLuckyWheel.m_LuckyWheelInfo[7].Exc,0,0);
	gInterface.DrawItem2(JCResto+237,271,70,45,ITEM(gLuckyWheel.m_LuckyWheelInfo[8].ItemType,gLuckyWheel.m_LuckyWheelInfo[8].ItemIndex),SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[8].Level),gLuckyWheel.m_LuckyWheelInfo[8].Exc,0,0);
	gInterface.DrawItem2(JCResto+167,271,70,45,ITEM(gLuckyWheel.m_LuckyWheelInfo[9].ItemType,gLuckyWheel.m_LuckyWheelInfo[9].ItemIndex),SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[9].Level),gLuckyWheel.m_LuckyWheelInfo[9].Exc,0,0);
	gInterface.DrawItem2(JCResto+167,157,70,50,ITEM(gLuckyWheel.m_LuckyWheelInfo[10].ItemType,gLuckyWheel.m_LuckyWheelInfo[10].ItemIndex),SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[10].Level),gLuckyWheel.m_LuckyWheelInfo[10].Exc,0,0);
	gInterface.DrawItem2(JCResto+167,214,70,50,ITEM(gLuckyWheel.m_LuckyWheelInfo[11].ItemType,gLuckyWheel.m_LuckyWheelInfo[11].ItemIndex),SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[11].Level),gLuckyWheel.m_LuckyWheelInfo[11].Exc,0,0);
	if(this->LuckyWheelNumber >= 0){
	    gInterface.DrawItem2(JCResto+283,170,50,50,ITEM(gLuckyWheel.m_LuckyWheelInfo[this->LuckyWheelNumber].ItemType,gLuckyWheel.m_LuckyWheelInfo[this->LuckyWheelNumber].ItemIndex),gLuckyWheel.m_LuckyWheelInfo[this->LuckyWheelNumber].Level,gLuckyWheel.m_LuckyWheelInfo[this->LuckyWheelNumber].Exc,0,0);
	}
	pSetCursorFocus = true;
	gInterface.DrawGUI(eLuckyWheelStart,JCResto+260,156.5f);
	gInterface.DrawFormat(eGold, JCResto+285, 75, 25, 5, "Lucky Wheel");
	gInterface.DrawFormat(eWhite, JCResto+292, 158, 50.0f, 1.0f, "Start");
    gInterface.DrawGUI(eCloseLuckyWheel, JCResto+418, 65);
    if (gInterface.IsWorkZone(eCloseLuckyWheel))
	{
    	DWORD Color = eGray100;
    	if (gInterface.Data[eCloseLuckyWheel].OnClick)
		{
    		Color = eGray150;
    	}
    	gInterface.DrawColoredGUI(eCloseLuckyWheel, JCResto+418, 65, Color);
    	gInterface.DrawToolTip(JCResto+418, 65, "Close");
    }
    if( gInterface.IsWorkZone(eLuckyWheelStart) )
	{
    	DWORD Color = eGray100;
    	if( gInterface.Data[eLuckyWheelStart].OnClick )
		{
    		Color = eGray150;
    	}
    	gInterface.DrawColoredGUI(eLuckyWheelStart, gInterface.Data[eLuckyWheelStart].X, gInterface.Data[eLuckyWheelStart].Y, Color);
    }
}
void Interface::EventLuckyWheel_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	if( !gInterface.Data[eLuckyWheelMain].OnShow )
	{
		return;
	}
	if (gInterface.IsWorkZone(eLuckyWheelStart))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eLuckyWheelStart].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eLuckyWheelStart].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eLuckyWheelStart].OnClick = false;
		pSetCursorFocus = false;
		if (Delay < 5000)
		{
			return;
		}

		gInterface.Data[eLuckyWheelStart].EventTick = GetTickCount();
		UP_TUCHAN_REQ pMsg;
		pMsg.h.set(0xF5, 0x16, sizeof(pMsg));
		DataSend((BYTE*)&pMsg, pMsg.h.size);
		StartRoll = 1;
	}
}
bool Interface::EventDrawClose_LuckyWheel(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eCloseLuckyWheel].EventTick);
	if (!gInterface.Data[eLuckyWheelMain].OnShow || !gInterface.IsWorkZone(eCloseLuckyWheel)){
		return false;
	}
	if (Event == WM_LBUTTONDOWN){
		gInterface.Data[eCloseLuckyWheel].OnClick = true;
		return true;
	}
	gInterface.Data[eCloseLuckyWheel].OnClick = false;
	if (Delay < 500){
		return false;
	}
	gInterface.Data[eCloseLuckyWheel].EventTick = GetTickCount();
	this->LuckyWheelStateclose();
	return false;
}
// ========================================================== END LUCKYWHELL

//============================================ ChangeReset
void Interface::DrawChangeResetWindow()
{
	if( !this->Data[eCHANGE_RESET_MAIN].OnShow )
	{
		return;
	}

	if(gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::FullMap)
		|| gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::Inventory)
		|| gInterface.CheckWindow(ObjWindow::Guild)
		|| gInterface.CheckWindow(ObjWindow::Party)
		//|| gInterface.CheckWindow(ObjWindow::Character)
		|| gInterface.CheckWindow(ObjWindow::FastMenu)
		|| gInterface.CheckWindow(ObjWindow::FriendList)
		|| gInterface.CheckWindow(ObjWindow::GensInfo)
		|| gInterface.CheckWindow(ObjWindow::MuHelper)
		|| gInterface.CheckWindow(ObjWindow::Quest)
		|| gInterface.CheckWindow(ObjWindow::CommandWindow))
	{
		this->Data[eCHANGE_RESET_MAIN].OnShow		= false;
		gInterface.Data[eCHANGE_RESET_MAIN].Close();		
		return;
	}

	// ----
	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	this->DrawGUI(eCHANGE_RESET_MAIN, StartX, StartY + 2);
	this->DrawGUI(eCHANGE_RESET_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(eCHANGE_RESET_FRAME, StartX, StartY + 67.0, 13);
	this->DrawGUI(eCHANGE_RESET_FOOTER, StartX, StartY);
	// ----
	if( this->IsWorkZone(eCHANGE_RESET_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGE_RESET_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----

		this->DrawColoredGUI(eCHANGE_RESET_CLOSE, this->Data[eCHANGE_RESET_CLOSE].X, this->Data[eCHANGE_RESET_CLOSE].Y, Color);
	}
	// ----
	this->DrawGUI(eCHANGE_RESET_CLOSE, ButtonX, this->Data[eCHANGE_RESET_FOOTER].Y + 10);
	this->DrawFormat(eWhite, StartX + 8, this->Data[eCHANGE_RESET_FOOTER].Y + 20, 210, 3, "Close");
	// ----
	this->DrawFormat(eSocket, StartX + 10, 110, 210, 3, "Panel Resets Change");
	// ----
	this->DrawGUI(eCHANGE_RESET_5, ButtonX + 106, this->Data[eCHANGE_RESET_MAIN].Y + 30);
	this->DrawFormat(eYellow, StartX + 83, this->Data[eCHANGE_RESET_MAIN].Y + 35, 215, 3,"Change");
	this->DrawFormat(eWhite, StartX - 19, this->Data[eCHANGE_RESET_MAIN].Y + 35, 215, 3,"5 Resets change for 1000 WCoin");
	// ----
	this->DrawGUI(eCHANGE_RESET_10, ButtonX + 106, this->Data[eCHANGE_RESET_MAIN].Y + 60);
	this->DrawFormat(eYellow, StartX + 83, this->Data[eCHANGE_RESET_MAIN].Y + 65, 215, 3,"Change");
	this->DrawFormat(eWhite, StartX - 20, this->Data[eCHANGE_RESET_MAIN].Y + 65, 215, 3,"10 Resets change for 2000 WCoin");
	// ----
	this->DrawGUI(eCHANGE_RESET_15, ButtonX + 106, this->Data[eCHANGE_RESET_MAIN].Y + 90);
	this->DrawFormat(eYellow, StartX + 83, this->Data[eCHANGE_RESET_MAIN].Y + 95, 215, 3,"Change");
	this->DrawFormat(eWhite, StartX - 20, this->Data[eCHANGE_RESET_MAIN].Y + 95, 215, 3,"15 Resets change for 3000 WCoin");
	// ----
	this->DrawGUI(eCHANGE_RESET_20, ButtonX + 106, this->Data[eCHANGE_RESET_MAIN].Y + 120);
	this->DrawFormat(eYellow, StartX + 83, this->Data[eCHANGE_RESET_MAIN].Y + 125, 215, 3, "Change");
	this->DrawFormat(eWhite, StartX - 20, this->Data[eCHANGE_RESET_MAIN].Y + 125, 215, 3,"20 Resets change for 4000 WCoin");
	// ----
	this->DrawGUI(eCHANGE_RESET_25, ButtonX + 106, this->Data[eCHANGE_RESET_MAIN].Y + 150);
	this->DrawFormat(eYellow, StartX + 83, this->Data[eCHANGE_RESET_MAIN].Y + 155, 215, 3,"Change");
	this->DrawFormat(eWhite, StartX - 20, this->Data[eCHANGE_RESET_MAIN].Y + 155, 215, 3,"25 Resets change for 5000 WCoin");
	// ----
	this->DrawGUI(eCHANGE_RESET_LINE, StartX + 30, this->Data[eCHANGE_RESET_MAIN].Y + 48);
	this->DrawGUI(eCHANGE_RESET_LINE, StartX + 30, this->Data[eCHANGE_RESET_MAIN].Y + 78);
	this->DrawGUI(eCHANGE_RESET_LINE, StartX + 30, this->Data[eCHANGE_RESET_MAIN].Y + 108);
	this->DrawGUI(eCHANGE_RESET_LINE, StartX + 30, this->Data[eCHANGE_RESET_MAIN].Y + 138);
	this->DrawGUI(eCHANGE_RESET_LINE, StartX + 30, this->Data[eCHANGE_RESET_MAIN].Y + 168);
	// ----
	this->DrawGUI(eCHANGE_RESET_DIV, StartX, this->Data[eCHANGE_RESET_MAIN].Y + 246);
	// ----
	this->Data[eCHANGE_RESET_25].Attribute = true;
	this->Data[eCHANGE_RESET_5].Attribute = true;
	this->Data[eCHANGE_RESET_10].Attribute = true;
	this->Data[eCHANGE_RESET_15].Attribute = true;
	this->Data[eCHANGE_RESET_20].Attribute = true;
	// ----
	if( IsWorkZone(eCHANGE_RESET_5) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGE_RESET_5].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGE_RESET_5, this->Data[eCHANGE_RESET_5].X, this->Data[eCHANGE_RESET_5].Y, Color);
	}
	if( IsWorkZone(eCHANGE_RESET_10) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGE_RESET_10].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGE_RESET_10, this->Data[eCHANGE_RESET_10].X, this->Data[eCHANGE_RESET_10].Y, Color);
	}
	if( IsWorkZone(eCHANGE_RESET_15) )
	{
			DWORD Color = eGray100;
			// ----
			if( this->Data[eCHANGE_RESET_15].OnClick )
			{
				Color = eGray150;
			}
			// ----
			this->DrawColoredGUI(eCHANGE_RESET_15, this->Data[eCHANGE_RESET_15].X, this->Data[eCHANGE_RESET_15].Y, Color);
	}
	if( IsWorkZone(eCHANGE_RESET_20) )
	{
			DWORD Color = eGray100;
			// ----
			if( this->Data[eCHANGE_RESET_20].OnClick )
			{
				Color = eGray150;
			}
			// ----
			this->DrawColoredGUI(eCHANGE_RESET_20, this->Data[eCHANGE_RESET_20].X, this->Data[eCHANGE_RESET_20].Y, Color);
	}
	if( IsWorkZone(eCHANGE_RESET_25) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGE_RESET_25].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGE_RESET_25, this->Data[eCHANGE_RESET_25].X, this->Data[eCHANGE_RESET_25].Y, Color);
	}
}
bool Interface::EventChangeResetWindow_Main(DWORD Event)
{
	this->EventChangeResetWindow_Close(Event);	
	this->EventChangeResetWindow_5(Event);
	this->EventChangeResetWindow_10(Event);
	this->EventChangeResetWindow_15(Event);
	this->EventChangeResetWindow_20(Event);
	this->EventChangeResetWindow_25(Event);
	return true;
}
bool Interface::EventChangeResetWindow_Close(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGE_RESET_CLOSE].EventTick);
	// ----
	if( !this->Data[eCHANGE_RESET_MAIN].OnShow || !IsWorkZone(eCHANGE_RESET_CLOSE) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGE_RESET_CLOSE].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGE_RESET_CLOSE].OnClick = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGE_RESET_CLOSE].EventTick = GetTickCount();
	this->Data[eCHANGE_RESET_MAIN].Close();
	// ----
	return false;
}
bool Interface::EventChangeResetWindow_5(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGE_RESET_5].EventTick);

	DWORD DelayUserPanel = (GetTickCount() - this->Data[eMenu_RESETCHANGE].EventTick);
	if (DelayUserPanel < 500)
	{
		return false;
	}
	// ----
	if( !this->Data[eCHANGE_RESET_MAIN].OnShow || !IsWorkZone(eCHANGE_RESET_5) 
		|| !this->Data[eCHANGE_RESET_5].Attribute )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGE_RESET_5].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGE_RESET_5].OnClick = false;;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGE_RESET_5].EventTick = GetTickCount();

	gChangeReset.SendChangeReset(CHANGE_RESET_5);

	this->Data[eCHANGE_RESET_MAIN].Close();
	// ----
	return false;
}
bool Interface::EventChangeResetWindow_10(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGE_RESET_10].EventTick);
	// ----
	if( !this->Data[eCHANGE_RESET_MAIN].OnShow || !IsWorkZone(eCHANGE_RESET_10) 
		|| !this->Data[eCHANGE_RESET_10].Attribute )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGE_RESET_10].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGE_RESET_10].OnClick = false;;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGE_RESET_10].EventTick = GetTickCount();

	gChangeReset.SendChangeReset(CHANGE_RESET_10);

	this->Data[eCHANGE_RESET_MAIN].Close();
	// ----
	return false;
}
bool Interface::EventChangeResetWindow_15(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGE_RESET_15].EventTick);
	// ----
	if( !this->Data[eCHANGE_RESET_MAIN].OnShow || !IsWorkZone(eCHANGE_RESET_15) 
		|| !this->Data[eCHANGE_RESET_15].Attribute )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGE_RESET_15].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGE_RESET_15].OnClick = false;;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGE_RESET_15].EventTick = GetTickCount();

	gChangeReset.SendChangeReset(CHANGE_RESET_15);

	this->Data[eCHANGE_RESET_MAIN].Close();
	// ----
	return false;
}
bool Interface::EventChangeResetWindow_20(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGE_RESET_20].EventTick);
	// ----
	if( !this->Data[eCHANGE_RESET_MAIN].OnShow || !IsWorkZone(eCHANGE_RESET_20) 
		|| !this->Data[eCHANGE_RESET_20].Attribute )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGE_RESET_20].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGE_RESET_20].OnClick = false;;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGE_RESET_20].EventTick = GetTickCount();

	gChangeReset.SendChangeReset(CHANGE_RESET_20);

	this->Data[eCHANGE_RESET_MAIN].Close();
	// ----
	return false;
}
bool Interface::EventChangeResetWindow_25(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eCHANGE_RESET_25].EventTick);

	DWORD DelayUserPanel = (GetTickCount() - this->Data[eMenu_RESETCHANGE].EventTick);
	if (DelayUserPanel < 500)
	{
		return false;
	}
	// ----
	if( !this->Data[eCHANGE_RESET_MAIN].OnShow || !IsWorkZone(eCHANGE_RESET_25) 
		|| !this->Data[eCHANGE_RESET_25].Attribute )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eCHANGE_RESET_25].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCHANGE_RESET_25].OnClick = false;;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eCHANGE_RESET_25].EventTick = GetTickCount();

	gChangeReset.SendChangeReset(CHANGE_RESET_25);

	this->Data[eCHANGE_RESET_MAIN].Close();
	// ----
	return false;
}
// ========================================================== END ChangeReset


void Interface::DrawSmithItem()
{
	if (this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(SkillTree) ||
		this->CheckWindow(Warehouse) ||
		this->CheckWindow(Shop) ||
		this->CheckWindow(Trade) ||
		this->CheckWindow(ExpandInventory) ||
		this->CheckWindow(ExpandWarehouse))
		return;

	if( !this->Data[eSMITH_MAIN].OnShow )
	{
		return;
	}
	// ---
	pSetCursorFocus = true;
	// ----
	float MainWidth			= 230.0f;
	float MainHeight		= 313.0f;
	float StartY			= 100.0f;
	float StartX			= (MAX_WIN_WIDTH / 2.0f) - (MainWidth / 2.0f);
	float MainCenter		= StartX + (MainWidth / 3.0f);
	float ButtonX			= MainCenter - (29.0f / 2.0f);
	// ----
	this->DrawGUI(eSMITH_MAIN, StartX, StartY - 78);
	this->DrawGUI(eSMITH_TITLE, StartX, StartY - 80);
	StartY = this->DrawRepeatGUI(eSMITH_FRAME, StartX, StartY - 13.0, 13);
	this->DrawGUI(eSMITH_FOOTER, StartX, StartY + 80);
	pDrawGUI(0x7A7B, StartX, 275, 5, 100); //
	pDrawGUI(0x7A7B, StartX + 221, 276, 5, 100); //
	this->DrawGUI(eSMITH_CLOSE, StartX + MainWidth - this->Data[eSMITH_CLOSE].Width, this->Data[eSMITH_TITLE].Height + this->Data[eSMITH_CLOSE].Height - 78);
	this->DrawFormat(eGold, StartX + 95, 30,25, 5, "Smith Shop");
	// ----
	if( this->IsWorkZone(eSMITH_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eSMITH_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eSMITH_CLOSE, this->Data[eSMITH_CLOSE].X, this->Data[eSMITH_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[eSMITH_CLOSE].X + 5, this->Data[eSMITH_CLOSE].Y + 25, "Close");
	}
	this->DrawFormat(eGold, StartX + 30, 50, 210, 1, "Group Item");
	pDrawGUI(0x7C0D, StartX + 15, 70, 16, 15); //
	pDrawGUI(0x7AA4, StartX + 73, 70, 16, 15); //
	switch (gSmithItem.ItemType)
	{
	case 0:
		this->DrawFormat(eGold, StartX + 40, 73,25, 5, "Sword");
		break;
	case 1:
		this->DrawFormat(eGold, StartX + 40, 73,25, 5, "Axe");
		break;
	case 2:
		this->DrawFormat(eGold, StartX + 40, 73,25, 5, "Scepter");
		break;
	case 3:
		this->DrawFormat(eGold, StartX + 40, 73,25, 5, "Spear");
		break;
	case 4:
		this->DrawFormat(eGold, StartX + 40, 73,25, 5, "Bow");
		break;
	case 5:
		this->DrawFormat(eGold, StartX + 40, 73,25, 5, "Staff");
		break;
	case 6:
		this->DrawFormat(eGold, StartX + 40, 73,25, 5, "Shield");
		break;
	case 7:
		this->DrawFormat(eGold, StartX + 40, 73,25, 5, "Helm");
		break;
	case 8:
		this->DrawFormat(eGold, StartX + 40, 73,25, 5, "Armor");
		break;
	case 9:
		this->DrawFormat(eGold, StartX + 40, 73,25, 5, "Pant");
		break;
	case 10:
		this->DrawFormat(eGold, StartX + 40, 73,25, 5, "Glove");
		break;
	case 11:
		this->DrawFormat(eGold, StartX + 40, 73,25, 5, "Boot");
		break;
	}
	this->DrawFormat(eGold, StartX + 160, 50, 210, 1, "Item Time");
	pDrawGUI(0x7C0D, StartX + 140, 70, 16, 15); //
	pDrawGUI(0x7AA4, StartX + 193, 70, 16, 15); //
	switch (gSmithItem.Days)
	{
	case 0:
		this->DrawFormat(eGold, StartX + 163, 73,25, 5, "1 Days");
		break;
	case 1:
		this->DrawFormat(eGold, StartX + 163, 73,25, 5, "7 Days");
		break;
	case 2:
		this->DrawFormat(eGold, StartX + 163, 73,25, 5, "30 Days");
		break;
	}
	pDrawGUI(0x79A2, StartX + 27, 100, 171, 23);
	pDrawGUI(0x7BAA, StartX + 8, 103, 17, 18);
	pDrawGUI(0x7BAB, StartX + 200, 103, 17, 18);
	switch(gSmithItem.ItemType){
	case 0:
		DrawItem2(StartX + 40,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		this->DrawFormat(eGold, StartX + 35, 106,25, 5, "%s",gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 1:
		DrawItem2(StartX + 40,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		this->DrawFormat(eGold, StartX + 35, 106,25, 5, "%s",gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 2:
		DrawItem2(StartX + 40,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		this->DrawFormat(eGold, StartX + 35, 106,25, 5, "%s",gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 3:
		DrawItem2(StartX + 55,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		this->DrawFormat(eGold, StartX + 35, 106,25, 5, "%s",gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 4:
		DrawItem2(StartX + 65,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		this->DrawFormat(eGold, StartX + 35, 106,25, 5, "%s",gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 5:
		DrawItem2(StartX + 55,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		this->DrawFormat(eGold, StartX + 35, 106,25, 5, "%s",gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 6:
		DrawItem2(StartX + 65,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		this->DrawFormat(eGold, StartX + 35, 106,25, 5, "%s",gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 7:
		DrawItem2(StartX + 65,10,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		this->DrawFormat(eGold, StartX + 35, 106,25, 5, "%s",gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 8:
		DrawItem2(StartX + 65,15,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		this->DrawFormat(eGold, StartX + 35, 106,25, 5, "%s",gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 9:
		DrawItem2(StartX + 65,5,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		this->DrawFormat(eGold, StartX + 35, 106,25, 5, "%s",gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 10:
		DrawItem2(StartX + 65,5,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		this->DrawFormat(eGold, StartX + 35, 106,25, 5, "%s",gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 11:
		DrawItem2(StartX + 65,5,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		this->DrawFormat(eGold, StartX + 35, 106,25, 5, "%s",gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].ItemName);
		break;
	}
	this->DrawGUI(eSMITH_DIV, StartX, 130);
	for( int i = 0; i < 10; i++ )
	{
		pDrawGUI(iOptionDot,StartX + 15,147 + (20 * i) + 9,10,10);
		pDrawGUI(0x7B5E, StartX + 30, 160 + (20 * i) + 9, 82.0, 2.0);
		pDrawGUI(0x7B5E, StartX + 30 + 82, 160 + (20 * i) + 9, 82.0, 2.0);
	}
	//Level
	this->DrawFormat(eGold, StartX + 40, 155,15, 5, "Item Level");
	pDrawGUI(0x7C0D, StartX + 140, 153, 16, 15); //
	pDrawGUI(0x7AA4, StartX + 180, 153, 16, 15); //
	this->DrawFormat(eGold, StartX + 155, 155,25, 5, "     %d",gSmithItem.mLevel);
	//Skill
	this->DrawFormat(eGold, StartX + 40, 175,15, 5, "Item Skill");
	pDrawButton(iOptionCheck,StartX + 180,175,15,15,0,15);
	if(gSmithItem.mSkill == 1)
	{
		pDrawButton(iOptionCheck,StartX + 180,175,15,15,0,0);
	}
	//Luck
	this->DrawFormat(eGold, StartX + 40, 195,15, 5, "Lucky Option");
	pDrawButton(iOptionCheck,StartX + 180,195,15,15,0,15);
	if(gSmithItem.mLuck == 1)
	{
		pDrawButton(iOptionCheck,StartX + 180,195,15,15,0,0);
	}
	//Option(Life)
	this->DrawFormat(eGold, StartX + 40, 215,15, 5, "Add Option");
	pDrawGUI(0x7C0D, StartX + 140, 213, 16, 15); //
	pDrawGUI(0x7AA4, StartX + 180, 213, 16, 15); //
	this->DrawFormat(eGold, StartX +155, 215,25, 5, "     %d",gSmithItem.mOpt);
	//
	if(gSmithItem.ItemType <= 5)
	{
	this->DrawFormat(eGold, StartX +40, 235,15, 5, "Excellent Damange Rate");
	pDrawButton(iOptionCheck,StartX + 180,235,15,15,0,15);
	if(gSmithItem.ExcOption == 32)
	{
		pDrawButton(iOptionCheck,StartX + 180,235,15,15,0,0);
	}
	//
	this->DrawFormat(eGold, StartX +40, 255,15, 5, "Increase Damage Level");
	pDrawButton(iOptionCheck,StartX + 180,255,15,15,0,15);
	if(gSmithItem.ExcOption1 == 16)
	{
		pDrawButton(iOptionCheck,StartX + 180,255,15,15,0,0);
	}
	//
	this->DrawFormat(eGold, StartX +40, 275,15, 5, "Increase Damage");
	pDrawButton(iOptionCheck,StartX + 180,275,15,15,0,15);

	if(gSmithItem.ExcOption2 == 8)
	{
		pDrawButton(iOptionCheck,StartX + 180,275,15,15,0,0);
	}
	//
	this->DrawFormat(eGold, StartX +40, 295,15, 5, "Increase Attacking(Wizard)Speed");
	pDrawButton(iOptionCheck,StartX + 180,295,15,15,0,15);
	if(gSmithItem.ExcOption3 == 4)
	{
		pDrawButton(iOptionCheck,StartX + 180,295,15,15,0,0);
	}
	//
	this->DrawFormat(eGold, StartX +40, 315,15, 5, "Increase Life Hunting Monster");
	pDrawButton(iOptionCheck,StartX + 180,315,15,15,0,15);
	if(gSmithItem.ExcOption4 == 2)
	{
		pDrawButton(iOptionCheck,StartX + 180,315,15,15,0,0);
	}
	//
	this->DrawFormat(eGold, StartX +40, 335,15, 5, "Increase Mana Hunting Monster");
	pDrawButton(iOptionCheck,StartX + 180,335,15,15,0,15);
	if(gSmithItem.ExcOption5 == 1)
	{
		pDrawButton(iOptionCheck,StartX + 180,335,15,15,0,0);
	}
	}
	if(gSmithItem.ItemType >= 6)
	{
	this->DrawFormat(eGold, StartX +40, 235,15, 5, "Increase Max HP");
	pDrawButton(iOptionCheck,StartX + 180,235,15,15,0,15);
	if(gSmithItem.ExcOption == 32)
	{
		pDrawButton(iOptionCheck,StartX + 180,235,15,15,0,0);
	}
	//
	this->DrawFormat(eGold, StartX +40, 255,15, 5, "Increase Max Mana");
	pDrawButton(iOptionCheck,StartX + 180,255,15,15,0,15);
	if(gSmithItem.ExcOption1 == 16){
		pDrawButton(iOptionCheck,StartX + 180,255,15,15,0,0);
	}
	this->DrawFormat(eGold, StartX +40, 275,15, 5, "Damage Decrease");
	pDrawButton(iOptionCheck,StartX + 180,275,15,15,0,15);
	if(gSmithItem.ExcOption2 == 8){
		pDrawButton(iOptionCheck,StartX + 180,275,15,15,0,0);
	}
	this->DrawFormat(eGold, StartX +40, 295,15, 5, "Reflect Damage");
	pDrawButton(iOptionCheck,StartX + 180,295,15,15,0,15);
	if(gSmithItem.ExcOption3 == 4){
		pDrawButton(iOptionCheck,StartX + 180,295,15,15,0,0);
	}
	this->DrawFormat(eGold, StartX +40, 315,15, 5, "Defense Success Rate");
	pDrawButton(iOptionCheck,StartX + 180,315,15,15,0,15);
	if(gSmithItem.ExcOption4 == 2){
		pDrawButton(iOptionCheck,StartX + 180,315,15,15,0,0);
	}
	this->DrawFormat(eGold, StartX +40, 335,15, 5, "Zen After Hunting Monsters");
	pDrawButton(iOptionCheck,StartX + 180,335,15,15,0,15);
	if(gSmithItem.ExcOption5 == 1){
		pDrawButton(iOptionCheck,StartX + 180,335,15,15,0,0);
	    }
	}
	this->DrawGUI(eSMITH_DIV, StartX, this->Data[eSMITH_FOOTER].Y - 15);
	this->DrawGUI(eSMITH_BUY, ButtonX, this->Data[eSMITH_FOOTER].Y + 10);
	this->DrawFormat(eGold, StartX + 105, this->Data[eSMITH_FOOTER].Y + 15,15, 5, "Buy Item");
		if( IsWorkZone(eSMITH_BUY) ){
			DWORD Color = eGray100;
			if( this->Data[eSMITH_BUY].OnClick ){
				Color = eGray150;
			}
			this->DrawColoredGUI(eSMITH_BUY, this->Data[eSMITH_BUY].X, this->Data[eSMITH_BUY].Y, Color);
		}
	if( gSmithItem.ItemType == 0)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	else if( gSmithItem.ItemType == 1)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 2)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 3)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 4)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 5)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 6)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 7)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 8)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 9)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 10)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 11)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					this->DrawFormat(eRed,StartX + 150, 106,15, 5,"Price %d", gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
}
void Interface::EventSmithItem_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	if( !this->Data[eSMITH_MAIN].OnShow )
	{
		return;
	}
	if (this->IsWorkZone(eSMITH_SKILL))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_SKILL].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_SKILL].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_SKILL].OnClick = false;
		pSetCursorFocus = true;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_SKILL].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_SKILL_1].OnShow)
		{
			this->Data[eSMITH_SKILL_1].OnShow = true;
			gSmithItem.mSkill = 1;
			gSmithItem.TotalPrice += gSmithItem.pSkill;
		}
		else {
			this->Data[eSMITH_SKILL_1].OnShow = false;
			gSmithItem.mSkill = 0;
			gSmithItem.TotalPrice -= gSmithItem.pSkill;
		}
	}
	else if (this->IsWorkZone(eSMITH_LUCK))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_LUCK].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_LUCK].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_LUCK].OnClick = false;
		pSetCursorFocus = true;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_LUCK].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_LUCK_1].OnShow)
		{
			this->Data[eSMITH_LUCK_1].OnShow = true;
			gSmithItem.mLuck = 1;
			gSmithItem.TotalPrice += gSmithItem.pLuck;
		}
		else {
			this->Data[eSMITH_LUCK_1].OnShow = false;
			gSmithItem.mLuck = 0;
			gSmithItem.TotalPrice -= gSmithItem.pLuck;
		}
	}
	else if (this->IsWorkZone(eSMITH_EXC))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_EXC].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_EXC].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_EXC].OnClick = false;
		pSetCursorFocus = true;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_EXC].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_EXC_1].OnShow)
		{
			this->Data[eSMITH_EXC_1].OnShow = true;
			gSmithItem.ExcOption = 32;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc;
		}
		else {
			this->Data[eSMITH_EXC_1].OnShow = false;
			gSmithItem.ExcOption = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc;
		}
	}
	else if (this->IsWorkZone(eSMITH_EXC1))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_EXC1].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_EXC1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_EXC1].OnClick = false;
		pSetCursorFocus = true;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_EXC1].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_EXC1_1].OnShow)
		{
			this->Data[eSMITH_EXC1_1].OnShow = true;
			gSmithItem.ExcOption1 = 16;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc1;
		}
		else {
			this->Data[eSMITH_EXC1_1].OnShow = false;
			gSmithItem.ExcOption1 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc1;
		}
	}
	else if (this->IsWorkZone(eSMITH_EXC2))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_EXC2].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_EXC2].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_EXC2].OnClick = false;
		pSetCursorFocus = true;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_EXC2].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_EXC2_1].OnShow)
		{
			this->Data[eSMITH_EXC2_1].OnShow = true;
			gSmithItem.ExcOption2 = 8;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc2;
		}
		else {
			this->Data[eSMITH_EXC2_1].OnShow = false;
			gSmithItem.ExcOption2 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc2;
		}
	}
	else if (this->IsWorkZone(eSMITH_EXC3))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_EXC3].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_EXC3].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_EXC3].OnClick = false;
		pSetCursorFocus = true;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_EXC3].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_EXC3_1].OnShow)
		{
			this->Data[eSMITH_EXC3_1].OnShow = true;
			gSmithItem.ExcOption3 = 4;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc3;
		}
		else {
			this->Data[eSMITH_EXC3_1].OnShow = false;
			gSmithItem.ExcOption3 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc3;
		}
	}
	else if (this->IsWorkZone(eSMITH_EXC4))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_EXC4].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_EXC4].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_EXC4].OnClick = false;
		pSetCursorFocus = true;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_EXC4].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_EXC4_1].OnShow)
		{
			this->Data[eSMITH_EXC4_1].OnShow = true;
			gSmithItem.ExcOption4 = 2;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc4;
		}
		else {
			this->Data[eSMITH_EXC4_1].OnShow = false;
			gSmithItem.ExcOption4 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc4;
		}
	}
	else if (this->IsWorkZone(eSMITH_EXC5))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_EXC5].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_EXC5].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_EXC5].OnClick = false;
		pSetCursorFocus = true;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_EXC5].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_EXC5_1].OnShow)
		{
			this->Data[eSMITH_EXC5_1].OnShow = true;
			gSmithItem.ExcOption5 = 1;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc5;
		}
		else {
			this->Data[eSMITH_EXC5_1].OnShow = false;
			gSmithItem.ExcOption5 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc5;
		}
	}
	else if (this->IsWorkZone(eSMITH_LEVEL))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_LEVEL].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_LEVEL].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_LEVEL].OnClick = false;
	pSetCursorFocus = true;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_LEVEL].EventTick = GetTickCount();
	if(gSmithItem.mLevel <= 0)
	{return;}
	else
	{
		gSmithItem.mLevel	-=	1;
		gSmithItem.TotalPrice -= gSmithItem.pLevel;
	}
	}
	else if (this->IsWorkZone(eSMITH_LEVEL_1))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_LEVEL_1].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_LEVEL_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_LEVEL_1].OnClick = false;
	pSetCursorFocus = true;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_LEVEL_1].EventTick = GetTickCount();
	if(gSmithItem.mLevel >= gSmithItem.MaxLevel)
	{return;}
	else
	{
		gSmithItem.mLevel	+=	1;
		gSmithItem.TotalPrice += gSmithItem.pLevel;
	}
	}
	else if (this->IsWorkZone(eSMITH_OPT))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_OPT].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_OPT].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_OPT].OnClick = false;
	pSetCursorFocus = true;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_OPT].EventTick = GetTickCount();
	if(gSmithItem.mOpt <= 0)
	{return;}
	else
	{
		gSmithItem.mOpt	-=	1;
		gSmithItem.TotalPrice -= gSmithItem.pOpt;
	}
	}
	else if (this->IsWorkZone(eSMITH_OPT_1))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_OPT_1].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_OPT_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_OPT_1].OnClick = false;
	pSetCursorFocus = true;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_OPT_1].EventTick = GetTickCount();
	if(gSmithItem.mOpt >= gSmithItem.MaxOpt)
	{return;}
	else
	{
		gSmithItem.mOpt	+=	1;
		gSmithItem.TotalPrice += gSmithItem.pOpt;
	}
	}
	else if (this->IsWorkZone(eSMITH_ITEMTYPE))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_ITEMTYPE].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_ITEMTYPE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_ITEMTYPE].OnClick = false;
	pSetCursorFocus = true;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_ITEMTYPE].EventTick = GetTickCount();
	if(gSmithItem.ItemType <= 0)
	{return;}
	else
	{
		gSmithItem.ItemType	-=	1;
		gSmithItem.ItemIndex = 0;
	}
	}
	else if (this->IsWorkZone(eSMITH_ITEMTYPE_1))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_ITEMTYPE_1].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_ITEMTYPE_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_ITEMTYPE_1].OnClick = false;
	pSetCursorFocus = true;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_ITEMTYPE_1].EventTick = GetTickCount();
	if(gSmithItem.ItemType >= 11)
	{return;}
	else
	{gSmithItem.ItemType	+=	1;
	gSmithItem.ItemIndex = 0;}
	}
	else if (this->IsWorkZone(eSMITH_DAYS))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_DAYS].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_DAYS].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_DAYS].OnClick = false;
	pSetCursorFocus = true;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_DAYS].EventTick = GetTickCount();
	if(gSmithItem.Days <= 0)
	{return;}
	else
	{gSmithItem.Days	-=	1;}
	}
	else if (this->IsWorkZone(eSMITH_DAYS_1))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_DAYS_1].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_DAYS_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_DAYS_1].OnClick = false;
	pSetCursorFocus = true;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_DAYS_1].EventTick = GetTickCount();
	if(gSmithItem.Days >= 2)
	{return;}
	else
	{gSmithItem.Days	+=	1;}
	}
	else if (this->IsWorkZone(eSMITH_ITEMINDEX))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_ITEMINDEX].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_ITEMINDEX].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_ITEMINDEX].OnClick = false;
	pSetCursorFocus = true;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_ITEMINDEX].EventTick = GetTickCount();

	if(gSmithItem.ItemIndex <= 0 )
	{return;}

	if (gSmithItem.ItemType == 0)
	{
		if(gSmithItem.ItemIndex == 31)
		{
			gSmithItem.ItemIndex -=	6;
		}
		else
			gSmithItem.ItemIndex -=	1;
	}
	else if (gSmithItem.ItemType == 2)
	{
		if(gSmithItem.ItemIndex == 18)
		{
			gSmithItem.ItemIndex -=	2;
		}
		else
			gSmithItem.ItemIndex -=	1;
	}
	else if(gSmithItem.ItemType == 4)
		{
			if(gSmithItem.ItemIndex == 8 ||
				gSmithItem.ItemIndex == 16||
				gSmithItem.ItemIndex == 24)
				{
				gSmithItem.ItemIndex -=	2;
				}
			else
				gSmithItem.ItemIndex -=	1;
		}
	else if(gSmithItem.ItemType == 7)
		{
			if(gSmithItem.ItemIndex == 16 ||
				gSmithItem.ItemIndex == 11 ||
				gSmithItem.ItemIndex == 24 ||
				gSmithItem.ItemIndex == 33 ||
				gSmithItem.ItemIndex == 38)	
				{
				gSmithItem.ItemIndex -=	2;
				}
			else
				gSmithItem.ItemIndex -=	1;
		}
	else
	{
		gSmithItem.ItemIndex	-=	1;
	}
	}
	else if (this->IsWorkZone(eSMITH_ITEMINDEX_1))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_ITEMINDEX_1].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_ITEMINDEX_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_ITEMINDEX_1].OnClick = false;
	pSetCursorFocus = true;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_ITEMINDEX_1].EventTick = GetTickCount();
	if (gSmithItem.ItemType == 0)
	{
		if(gSmithItem.ItemIndex >= 35)
			return;

		if(gSmithItem.ItemIndex == 25)
		{
			gSmithItem.ItemIndex +=	6;
		}
		else
			gSmithItem.ItemIndex +=	1;
	}
	else if (gSmithItem.ItemType == 1)
	{
		if(gSmithItem.ItemIndex >= 8)
		{
			return;
		}
		else
		gSmithItem.ItemIndex +=	1;
	}
	else if (gSmithItem.ItemType == 2)
	{
		if(gSmithItem.ItemIndex >= 18)
		{
			return;
		}
		if(gSmithItem.ItemIndex == 16)
		{
			gSmithItem.ItemIndex +=	2;
		}
		else
		gSmithItem.ItemIndex +=	1;
	}
	else if (gSmithItem.ItemType == 3)
	{
		if(gSmithItem.ItemIndex >= 11)
		{
			return;
		}
		else
		gSmithItem.ItemIndex +=	1;
	}
	else if(gSmithItem.ItemType == 4)
		{
			if(gSmithItem.ItemIndex >= 24)
			{
			return;
			}
			else if(gSmithItem.ItemIndex == 6 ||
				gSmithItem.ItemIndex == 14 ||
				gSmithItem.ItemIndex == 22)
				{
				gSmithItem.ItemIndex +=	2;
				}
			else
				gSmithItem.ItemIndex +=	1;
		}
	else if (gSmithItem.ItemType == 5)
	{
		if(gSmithItem.ItemIndex >= 23)
		{
			return;
		}
		else
		gSmithItem.ItemIndex +=	1;
	}
	else if (gSmithItem.ItemType == 6)
	{
		if(gSmithItem.ItemIndex >= 16)
		{
			return;
		}
		else
		gSmithItem.ItemIndex +=	1;
	}
	else if(gSmithItem.ItemType == 7)
		{
			if(gSmithItem.ItemIndex >= 43)
			return;

			else if(gSmithItem.ItemIndex == 14 ||
				gSmithItem.ItemIndex == 19 ||
				gSmithItem.ItemIndex == 22 ||
				gSmithItem.ItemIndex == 31 ||
				gSmithItem.ItemIndex == 36)	
				{
				gSmithItem.ItemIndex +=	2;
				}
			else
				gSmithItem.ItemIndex +=	1;
		}
	else
	{
		if(gSmithItem.ItemIndex >= 43)
		return;
		gSmithItem.ItemIndex	+=	1;
	}
	}
	else if (this->IsWorkZone(eSMITH_CLOSE))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_CLOSE].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_CLOSE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_CLOSE].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
		{
			return;
		}
	// ----
	this->Data[eSMITH_CLOSE].EventTick = GetTickCount();
	this->CloseSmithItemWindow();
	}
	else if (this->IsWorkZone(eSMITH_BUY))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_BUY].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_BUY].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_BUY].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
		{
			return;
		}
	// ----
	this->Data[eSMITH_BUY].EventTick = GetTickCount();
	if(gSmithItem.ItemType >= 7)
	{
		gSmithItem.mSkill = 0;
	}
	SDHP_BUYSVSHOP pMsg;
	pMsg.h.set(0xF5, 0x08, sizeof(pMsg));//0xFB
	pMsg.ItemType = gSmithItem.ItemType;
	pMsg.ItemIndex = gSmithItem.ItemIndex;
	pMsg.Days	= gSmithItem.Days;
	pMsg.mLevel = gSmithItem.mLevel;
	pMsg.mSkill = gSmithItem.mSkill;
	pMsg.mLuck = gSmithItem.mLuck;
	pMsg.mOpt = gSmithItem.mOpt;
	pMsg.ExcOption = gSmithItem.ExcOption;
	pMsg.ExcOption1 = gSmithItem.ExcOption1;
	pMsg.ExcOption2 = gSmithItem.ExcOption2;
	pMsg.ExcOption3 = gSmithItem.ExcOption3;
	pMsg.ExcOption4 = gSmithItem.ExcOption4;
	pMsg.ExcOption5 = gSmithItem.ExcOption5;
	pMsg.mExc = gSmithItem.mExc;
	DataSend((BYTE*)&pMsg, pMsg.h.size);
	this->CloseSmithItemWindow();
	}
}

#if SKIN
void Interface::SetCursorFocus()
{
	bool focus = false;

	bool focus1 = false;
	bool focus2 = false;

	focus = RentSkin.CheckRect();

	focus1 = DailyReward.CheckRect();

	focus2 = ThueFlag.CheckRect();

	if (focus)
	{
		if (!pSetCursorFocus)
		{
			pSetCursorFocus = true;
		}
	}

	if (focus1)
	{
		if (!pSetCursorFocus)
		{
			pSetCursorFocus = true;
		}
	}

	if (focus2)
	{
		if (!pSetCursorFocus)
		{
			pSetCursorFocus = true;
		}
	}
}
#endif

#if(DAILY)
void Interface::DrawItemToolTipText ( void * item, int x, int y ) {
		static DWORD mem = 0;
		//static DWORD ItemToolTipAdress1 = 0x00861110; //1.04D-> 0x00860FC0
		//static DWORD ItemToolTipAdress2 = 0x00861AA0; //1.04D-> 0x00861950
		//static DWORD ItemToolTipAdress3 = 0x007E3E30; //1.04D-> 0x007E3CE0
		_asm {
		    PUSH 0
		    PUSH 0
		    PUSH 0
		    PUSH item
		    PUSH y
		    PUSH x
			MOV mem,0x00861110
		    CALL mem
		    MOV ECX, EAX
			MOV mem,0x00861AA0
		    CALL mem
		    MOV ECX, EAX
			MOV mem,0x007E3E30
		    CALL mem
		}

}
#endif
#if(DEV_PLAYERSHOP)

bool checkBtn(int obj)
{
	if (gObjUser.m_CursorX < gInterface.Data[obj].X || gObjUser.m_CursorX > gInterface.Data[obj].MaxX ||
		gObjUser.m_CursorY < gInterface.Data[obj].Y || gObjUser.m_CursorY > gInterface.Data[obj].MaxY)
	{
		return false;
	}
	return true;
}
void Interface::DrawColorGUI(int MainID, int X, int Y, int Width, int Height, DWORD Color)
{
	pDrawColorButton(MainID, X, Y, Width, Height, 0, 0, Color);
}

void Interface::DrawButtonBig(int ObjID, bool bActive, float fX, float fY, char* Text)
{
	gInterface.DrawGUI(ObjID, fX, fY);
	gInterface.DrawFormat(eWhite, fX + 4, fY + 10, 100, 3, Text);
	if (bActive)
	{
		gInterface.Data[ObjID].Attribute = true;
		if (gInterface.IsWorkZone(ObjID))
		{
			DWORD Color = eGray100;
			if (gInterface.Data[ObjID].OnClick)
			{
				Color = eGray150;
			}
			gInterface.DrawColoredGUI(ObjID, gInterface.Data[ObjID].X, gInterface.Data[ObjID].Y, Color);
		}
	}
	else
	{
		gInterface.Data[ObjID].Attribute = false;
		gInterface.DrawColoredGUI(ObjID, gInterface.Data[ObjID].X, gInterface.Data[ObjID].Y, eGray150);
	}
}

void Interface::DrawCheckLineEx(bool isChecked, int PointID, int CheckID, int LineID, float X, float Y, DWORD Color, char* Text)
{
	this->DrawGUI2(PointID, X + 20, Y - 4); // Point
	this->DrawFormat(eWhite, X + 50, Y + 1, 200, 1, Text);

	if (isChecked)
	{
		this->DrawButtonRender(CheckID, X + 190, Y - 6, 0, 0);
	}
	else
	{
		this->DrawButtonRender(CheckID, X + 190, Y - 6, 0, 15);
	}

	this->DrawGUI2(LineID, X + 33, Y + 10);
}

void Interface::DrawButtonMini(int id, int X, int Y, int res, char* Text)
{
	int StartX = X;
	int StartY = Y;

	gInterface.DrawGUI(id, StartX, StartY);
	gInterface.DrawFormat(eWhite, StartX + 5, StartY + 10, 50, 3, Text);

	if (!res)
	{
		gInterface.Data[id].Attribute = false;
		gInterface.DrawColoredGUI(id, gInterface.Data[id].X, gInterface.Data[id].Y, eGray150);
	}
	else
	{
		gInterface.Data[id].Attribute = true;
		if (gInterface.IsWorkZone(id))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[id].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(id, gInterface.Data[id].X, gInterface.Data[id].Y, Color);
		}
	}
}

void Interface::PartUPandDNEx(int PointID, int UpID, int DownID, int LineID, float X, float Y, DWORD Color, int Value, char* Text)
{
	this->DrawGUI2(PointID, X + 20, Y - 4); // Point

	this->DrawFormat(eWhite, X + 50, Y + 1, 200, 1, Text);

	this->DrawButtonRender(DownID, X + 150, Y - 6, 0, 0); // 

	if (checkBtn(DownID))
	{
		if (this->Data[DownID].OnClick)
		{
			this->DrawButtonRender(DownID, X + 150, Y - 6, 0, 16);
		}
	}

	pSetBlend(true);
	this->DrawBarForm(X + 168, Y - 5, 19, 13, 0.0, 0.0, 0.0, 1.0);//ReqItems
	glColor3f(1, 1, 1);
	pSetBlend(false);
	char szText[10];
	sprintf(szText, "%d", Value);
	gInterface.TextDraw(X + 128, Y - 2, 100, 1, eWhite, 0, 3, pFontNormal, "%d", Value);

	this->DrawButtonRender(UpID, X + 190, Y - 6, 0, 0); // 

	if (checkBtn(UpID))
	{
		if (this->Data[UpID].OnClick)
		{
			this->DrawButtonRender(UpID, X + 190, Y - 6, 0, 16);
		}
	}

	this->DrawGUI(LineID, X + 33, Y + 10);
}

bool Interface::ButtonExR(DWORD Event, int ButtonID, bool Type)
{
	if (!this->IsWorkZone(ButtonID))
	{
		return false;
	}

	if (Type == true)
	{
		if (!this->Data[ButtonID].Attribute)
		{
			return false;
		}
	}

	// ----
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[ButtonID].EventTick);
	// ----

	if (Event == WM_RBUTTONDOWN && this->Data[ButtonID].OnClick == false)
	{
		this->Data[ButtonID].OnClick = true;
		//return false;
	}

	if (Event == WM_RBUTTONUP && this->Data[ButtonID].OnClick == true)
	{
		this->Data[ButtonID].OnClick = false;
		return true;
	}
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[ButtonID].OnClick = false;
	// ----
	this->Data[ButtonID].EventTick = GetTickCount();
	// ----
	return false;
}

void Interface::KeyBoxEvent(DWORD Event, char* kText, int MaxText)
{
	int Len = strlen(kText);

	if (kText[0] == '0')
	{
		kText[0] = 0;
	}

	switch (Event)
	{
	case VK_0:
	case VK_NUMPAD0:
	{
		if (Len < MaxText)
		{
			strcat(kText, "0");
		}
	}
	break;
	case VK_1:
	case VK_NUMPAD1:
	{
		if (Len < MaxText)
			strcat(kText, "1");
	}
	break;
	case VK_2:
	case VK_NUMPAD2:
	{
		if (Len < MaxText)
			strcat(kText, "2");
	}
	break;
	case VK_3:
	case VK_NUMPAD3:
	{
		if (Len < MaxText)
			strcat(kText, "3");
	}
	break;
	case VK_4:
	case VK_NUMPAD4:
	{
		if (Len < MaxText)
			strcat(kText, "4");
	}
	break;
	case VK_5:
	case VK_NUMPAD5:
	{
		if (Len < MaxText)
			strcat(kText, "5");
	}
	break;
	case VK_6:
	case VK_NUMPAD6:
	{
		if (Len < MaxText)
			strcat(kText, "6");
	}
	break;
	case VK_7:
	case VK_NUMPAD7:
	{
		strcat(kText, "7");
	}
	break;
	case VK_8:
	case VK_NUMPAD8:
	{
		if (Len < MaxText)
			strcat(kText, "8");
	}
	break;
	case VK_9:
	case VK_NUMPAD9:
	{
		if (Len < MaxText)
			strcat(kText, "9");
	}
	break;
	case VK_BACK:
	{
		if (Len > 0)
			kText[Len - 1] = 0;
	}
	break;
	}

	if (kText[0] == 0)
	{
		strcpy(kText, "0");
	}

	//int GetNum = atoi(this->KeyText);
	//gConsole.Output(cGREY, "atoi: %d", GetNum);
}
void Interface::TextDraw(int PosX, int PosY, int Width, int Arg5, int Color, int Arg7, int Align, HGDIOBJ Font, LPCTSTR Format, ...)
{
	char TextBuff[1024] = { 0 };
	va_list va;
	va_start(va, Format);
	vsprintf_s(TextBuff, Format, va);
	va_end(va);

	int v13; // ST1C_4@1
	int v15; // ST20_4@1
	pSetFont(pTextThis(), (int)Font);
	v13 = sub_41FFE0_Addr(pTextThis());
	v15 = sub_420010_Addr(pTextThis());
	SetTextColorByHDC(pTextThis(), Color);
	sub_4200F0_Addr(pTextThis(), Arg7);
	pSetBkColor(pTextThis(), 255, 255, 255, 0);
	pDrawText(pTextThis(), PosX, PosY, TextBuff, Width, Arg5, (int*)Align, 0);
	SetTextColorByHDC(pTextThis(), v13);
	sub_4200F0_Addr(pTextThis(), v15);
}
bool Interface::CheckWindowEx2(int WindowID)
{
	return this->Data[WindowID].OnShow;
}
void Interface::OpenWindowEx(int WindowID)
{
	Data[WindowID].Open();
}

void Interface::CloseWindowEx(int WindowID)
{
	Data[WindowID].Close();
}
bool Interface::ButtonEx(DWORD Event, int ButtonID, bool Type)
{
	if( !this->IsWorkZone(ButtonID) )
	{
		return false;
	}

	if( Type == true )
	{
		if( !this->Data[ButtonID].Attribute )
		{
			return false;
		}
	}

	// ----
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[ButtonID].EventTick);
	// ----

	if( Event == WM_LBUTTONDOWN  && this->Data[ButtonID].OnClick == false)
	{
		this->Data[ButtonID].OnClick = true;
		//pSetCursorFocus = true;
		//return false;
	}

	if(Event == WM_LBUTTONUP && this->Data[ButtonID].OnClick == true)
	{
		this->Data[ButtonID].OnClick = false;
		//pSetCursorFocus = true;
		return true;
	}
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[ButtonID].OnClick = false;
	//pSetCursorFocus = true;
	// ----
	this->Data[ButtonID].EventTick = GetTickCount();
	// ----
	return false;
}

#endif
//-> Clear Inventory
