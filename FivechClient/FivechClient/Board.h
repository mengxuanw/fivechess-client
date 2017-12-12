#pragma once
#include "FivechClientDlg.h"
#include "Network.h"
#include "resource.h"

#include <vector>
using namespace std;
typedef struct chess
{
	int x;
	int y;
	int black;
}chess;
// CBoard 对话框

class CBoard : public CDialog
{
	DECLARE_DYNAMIC(CBoard)

// 对话框数据
	enum { IDD = IDD_BOARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	vector<chess> Chess;
	int turn;
	int color;
	bool over;
	static CBoard s_Board;
private:
	CBoard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBoard();
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void setTurn(int t);
	void setColor(int c);
	int getTurn();
	void addChess(chess c);
	void setOver(bool o);
	static CBoard* GetInstance(){return &s_Board;};
};
