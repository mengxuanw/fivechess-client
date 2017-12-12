#include "StdAfx.h"
#include "Network.h"

CNetwork CNetwork::s_Network;

CNetwork::CNetwork(void)
{
	link = false;
	clientID = -1;
}

CNetwork::~CNetwork(void)
{
}

BOOL CNetwork::InitNetwork(HWND m_hWnd)
{
	WSADATA wsaData;
	BOOL ret = WSAStartup(MAKEWORD(2,2),&wsaData);
	if (ret != 0)
	{
		MessageBox(NULL,L"初始化网络协议失败",L"",0);
		return FALSE;
	}
	LocalSock = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
	if(LocalSock == INVALID_SOCKET)
	{
		MessageBox(NULL,L"创建套接字失败",L"",0);
		WSACleanup();
		return FALSE;
	}
	sockaddr_in localaddr;
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(8888);
	localaddr.sin_addr.s_addr = inet_addr(SERVIP);
	int ErrorMsg = connect(LocalSock,(const struct sockaddr*)&localaddr,sizeof(sockaddr));
	if(WSAAsyncSelect(LocalSock,m_hWnd,NETWORK_EVENT,FD_READ | FD_CONNECT| FD_CLOSE|FD_WRITE) == SOCKET_ERROR)
	{
		MessageBox(NULL,L"WSAAsyncSelect",L"",0);
		WSACleanup();
		return FALSE;
	}
	if (ErrorMsg == SOCKET_ERROR)
	{
		MessageBox(NULL,L"Connect Server Failed",L"",0);
		return FALSE;
	}
	return TRUE;
}

BOOL CNetwork::OnSend(sMessage *Msg)
{
	sMessage msg;
	switch(Msg->Header.Type)
	{
		case MSG_CHOICE_CHESS:
		{
			msg.Header.Type = MSG_CHOICE_CHESS;
			msg.black = Msg->black;
			msg.Header.Size = sizeof(sMessage);
			msg.Header.PlayerID = clientID;
		}
		break;
		case MSG_LBUTTON_DOWN:
		{
			msg.Header.Type = MSG_LBUTTON_DOWN;
			msg.x = Msg->x;
			msg.y = Msg->y;
			msg.black = Msg->black;
			msg.Header.Size = sizeof(sMessage);
			msg.Header.PlayerID = clientID;
		}
		default:break;
	}
	if(send(LocalSock,(char *)&msg,sizeof(msg),0) == SOCKET_ERROR)
	{
		MessageBox(NULL,L"SendPlayerInfo error",L"",0);
		return FALSE;
	}
	return TRUE;
}
BOOL CNetwork::OnClose(SOCKET CurSock)
{
	closesocket(CurSock);
	WSACleanup();
	return TRUE;
}
int CNetwork::OnReceive(SOCKET CurSock)
{
	sMessage Msg;
	if(recv(CurSock,(char *)&Msg,sizeof(Msg),0) == SOCKET_ERROR)
	{
		MessageBox(NULL,L"Client:can't receive from Server",L"",0);
	}
	switch(Msg.Header.Type)
	{
	case MSG_ASSIGN_PLAYERID://获得服务器分配ID的信息
		return GetMgID(&Msg);
		break;
	case MSG_LBUTTON_DOWN:
		ServerLBDown(&Msg);
		break;
	case MSG_WIN:
		{
			MessageBox(NULL,L"You win",L"",0);
			CBoard::GetInstance()->setOver(true);
		}
		break;
	case MSG_LOSE:
		{
			MessageBox(NULL,L"You lose",L"",0);
			CBoard::GetInstance()->setOver(true);
		}
		break;
	default:
		break;
	}
	return 0;
}

int CNetwork::GetMgID(sMessage *Msg)
{
	link = true;
	clientID = Msg->Header.PlayerID;//从服务器发送过来的为客户端分配的ID
	return 1;
	//返回值是1,表示连接成功
}

int CNetwork::ServerLBDown(sMessage *Msg)
{
	chess tmp;
	tmp.x = Msg->x;
	tmp.y = Msg->y;
	tmp.black = Msg->black;
	CBoard::GetInstance()->addChess(tmp);
	CBoard::GetInstance()->setTurn(1);
	return 0;
}