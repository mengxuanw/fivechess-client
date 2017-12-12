#pragma once


#include "IP.h"
#include "Board.h"
#define NETWORK_EVENT     WM_USER+166 
#define MAX_PLAYERS 8



//Õ¯¬Á–≠“È
#define MSG_ASSIGN_PLAYERID 1
#define MSG_CHOICE_CHESS 2
#define MSG_LBUTTON_DOWN 3
#define MSG_WIN 4
#define MSG_LOSE 5

typedef struct sPlayer
{
	bool Connected;
	int PlayerID;
	int black;
	sPlayer(){Connected = false; }
}sPlayer;

typedef struct sMessageHeader 
{
	int Type;
	long Size;
	int PlayerID;
}sMessageHeader;

typedef struct sMessage
{
	sMessageHeader Header;
	int x;
	int y;
	int black;
}sMessage;

class CNetwork
{
private:
	CNetwork(void);
	~CNetwork(void);
public:
	static CNetwork* GetInstance(){return &s_Network;}
	BOOL InitNetwork(HWND m_hWnd);
	int OnReceive(SOCKET CurSock);
	BOOL OnClose(SOCKET CurSock);
	BOOL OnSend(sMessage *Msg);
	int GetMgID(sMessage *Msg);
	int ServerLBDown(sMessage *Msg);
private:
	static CNetwork s_Network;
	SOCKET LocalSock;
	bool link;
	int clientID;
};

