
// mfc.demoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc.demo.h"
#include "mfc.demoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmfcdemoDlg �Ի���




CmfcdemoDlg::CmfcdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmfcdemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcdemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1,OnDuiDlg)
END_MESSAGE_MAP()


// CmfcdemoDlg ��Ϣ�������

BOOL CmfcdemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmfcdemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmfcdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include <dui/DuiSystem.h> 
#include <dui/DuiDefaultLogger.h>
#include "MainDlg.h"

using namespace DuiEngine;

BOOL LoadXmlFromResource(pugi::xml_document & xmlDoc,HINSTANCE hInst,LPCTSTR pszName,LPCTSTR pszType)
{
	DuiResProviderPE res(hInst);
	DWORD dwSize=res.GetRawBufferSize(pszType,pszName);
	if(dwSize==0) return FALSE;
	CMyBuffer<char> strXml;
	strXml.Allocate(dwSize);
	res.GetRawBuffer(pszType,pszName,strXml,dwSize);
	pugi::xml_parse_result result= xmlDoc.load_buffer(strXml,strXml.size(),pugi::parse_default,pugi::encoding_utf8);
	DUIRES_ASSERTA(result,"parse xml error! xmlName=%s,desc=%s,offset=%d",pszName,result.description(),result.offset);
	return result;
}

void CmfcdemoDlg::OnDuiDlg()
{
	TCHAR szCurrentDir[MAX_PATH+1]; memset( szCurrentDir, 0, sizeof(szCurrentDir) );
	GetModuleFileName( NULL, szCurrentDir, MAX_PATH );
	LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
	*lpInsertPos = _T('\0');   

	DuiSystem duiSystem(theApp.m_hInstance);

	DefaultLogger loger;
	loger.setLogFilename(CDuiStringT(szCurrentDir)+_T("\\dui-demo.log"));
	duiSystem.SetLogger(&loger);

	duiSystem.logEvent(_T("demo started"));
	//����ID���ƶ��ձ�
	pugi::xml_document xmlNamedID;
	LoadXmlFromResource(xmlNamedID,theApp.m_hInstance,MAKEINTRESOURCE(IDR_NAME2ID),_T("XML2"));
	DuiName2ID::getSingletonPtr()->Init(xmlNamedID.first_child());
	//����Դ����Ƥ��
	duiSystem.SetResProvider(new DuiResProviderPE(theApp.m_hInstance));
	BOOL bOK=duiSystem.Init(_T("IDR_DUI_INIT")); //��ʼ��DUIϵͳ,ԭ����ϵͳ��ʼ����ʽ��Ȼ����ʹ�á�
	duiSystem.SetMsgBoxTemplate(_T("IDR_DUI_MSGBOX"));

	int nRet = 0; 
	// BLOCK: Run application
	{
		CMainDlg dlgMain;  
		nRet = dlgMain.DoModal();  
	}

	duiSystem.logEvent(_T("demo end"));

	delete duiSystem.GetResProvider();
}

