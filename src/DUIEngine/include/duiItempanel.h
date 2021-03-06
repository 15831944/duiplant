//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiItemPanel
// Description: A Framework wrapping frame to be used in a duiwindow.
//     Creator: Huang Jianxiong
//     Version: 2011.10.20 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma  once

#include "duiframe.h"

namespace DuiEngine
{

class CDuiItemPanel;

class DUI_EXP CDuiItemContainer
{
public:
    virtual void OnItemSetCapture(CDuiItemPanel *pItem,BOOL bCapture)=NULL;//设置or释放鼠标捕获
    virtual BOOL OnItemGetRect(CDuiItemPanel *pItem,CRect &rcItem)=NULL;	//获得表项的显示位置
	virtual BOOL IsItemRedrawDelay()=NULL;									//指示表项的更新方式
};

class DUI_EXP CDuiItemPanel : public CDuiPanel, public CDuiFrame
{
public:
    CDuiItemPanel(CDuiWindow *pFrameHost,pugi::xml_node xmlNode,CDuiItemContainer *pItemContainer=NULL);
    virtual ~CDuiItemPanel() {}

    virtual void OnFinalRelease();

	//////////////////////////////////////////////////////////////////////////
    virtual LRESULT DoFrameEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);

    virtual LRESULT CDuiItemPanel::OnDuiNotify(LPDUINMHDR pHdr);

    virtual CRect GetContainerRect();

    virtual HDC OnGetDuiDC(const CRect & rc ,DWORD gdcFlags);

    virtual void OnReleaseDuiDC(HDC hdc,const CRect &rc,DWORD gdcFlags);

    virtual void OnRedraw(const CRect &rc);

    virtual BOOL OnReleaseDuiCapture();

    virtual HDUIWND OnSetDuiCapture(HDUIWND hDuiWNd);
    virtual HWND GetHostHwnd();

    virtual BOOL IsTranslucent();

    virtual BOOL DuiCreateCaret(HBITMAP hBmp,int nWidth,int nHeight);

    virtual BOOL DuiShowCaret(BOOL bShow);

    virtual BOOL DuiSetCaretPos(int x,int y);

	virtual BOOL DuiUpdateWindow();

	virtual BOOL RegisterTimelineHandler(ITimelineHandler *pHandler);

	virtual BOOL UnregisterTimelineHandler(ITimelineHandler *pHandler);

	//////////////////////////////////////////////////////////////////////////
    virtual void ModifyItemState(DWORD dwStateAdd, DWORD dwStateRemove);

    virtual HDUIWND DuiGetHWNDFromPoint(POINT ptHitTest, BOOL bOnlyText);

    virtual void Draw(CDCHandle dc,const CRect & rc);

    virtual void SetSkin(CDuiSkinBase *pSkin);
    virtual void SetColor(COLORREF crBk,COLORREF crSelBk);

    virtual BOOL NeedRedrawWhenStateChange();

    CRect GetItemRect();
    void SetItemCapture(BOOL bCapture);
    void SetItemData(LPARAM dwData);
    LPARAM GetItemData();

    BOOL OnUpdateToolTip(HDUIWND hCurTipHost,HDUIWND &hNewTipHost,CRect &rcTip,CDuiStringT &strTip);
	
	void OnSetCaretValidateRect(LPCRECT lpRect);

	LPARAM GetItemIndex(){return m_lpItemIndex;}
	void SetItemIndex(LPARAM lp){m_lpItemIndex=lp;}

protected:
    CDuiWindow * m_pFrmHost;
    CDuiItemContainer * m_pItemContainer;
    COLORREF m_crBk, m_crSelBk;
    LPARAM		m_dwData;
	LPARAM		m_lpItemIndex;
};


}//namespace DuiEngine