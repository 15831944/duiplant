#include "StdAfx.h"
#include "UIHander.h"

#include "MainDlg.h"

CUIHander::CUIHander(CMainDlg * pMainDlg) : m_pMainDlg(pMainDlg)
{
}

CUIHander::~CUIHander(void)
{
}

LRESULT CUIHander::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	SetMsgHandled(FALSE); 
	//��ʾ�ڳ����ʼ����ʱ��ͨ�����û������ļ�����PANE�Ĵ�С.
    return 0; 
}
