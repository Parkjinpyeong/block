
// BlockDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Block.h"
#include "BlockDlg.h"
#include "afxdialogex.h"



using namespace std;
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BUFSIZE 256  

// CBlockDlg 대화 상자



CBlockDlg::CBlockDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BLOCK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBlockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HACKERSHOLDINGS_URL_STC, m_HackersHoldingsUrl);
	DDX_Control(pDX, IDC_HELPDESK_URL_STC, m_HelpDesk);	
	DDX_Control(pDX, IDC_MIN_BTN, m_MinBtn);
	DDX_Control(pDX, IDC_CLOSE_BTN, m_CloseBtn);
	DDX_Control(pDX, IDC_HOME_BTN, m_HomeBtn);
	DDX_Control(pDX, IDC_SCAN_BTN, m_ScanBtn);
	DDX_Control(pDX, IDC_OPTIMIZATION_BTN, m_OptimizationBtn);
	DDX_Control(pDX, IDC_DIAGNOSTIC_BTN, m_DiagnosticBtn);
	DDX_Control(pDX, IDC_LOG_BTN, m_LogBtn);
	DDX_Control(pDX, IDC_SETTING_BTN, m_SettingBtn);
	DDX_Control(pDX, IDC_UPDATE_BTN, m_UpdateBtn);
	DDX_Control(pDX, IDC_DBG_BTN, m_DbgBtn);
}

BEGIN_MESSAGE_MAP(CBlockDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MIN_BTN, &CBlockDlg::OnBnClickedMinBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CBlockDlg::OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_HOME_BTN, &CBlockDlg::OnBnClickedHomeBtn)
	ON_BN_CLICKED(IDC_SCAN_BTN, &CBlockDlg::OnBnClickedScanBtn)
	ON_BN_CLICKED(IDC_OPTIMIZATION_BTN, &CBlockDlg::OnBnClickedOptimizationBtn)
	ON_BN_CLICKED(IDC_DIAGNOSTIC_BTN, &CBlockDlg::OnBnClickedDiagnosticBtn)
	ON_BN_CLICKED(IDC_LOG_BTN, &CBlockDlg::OnBnClickedLogBtn)
	ON_BN_CLICKED(IDC_SETTING_BTN, &CBlockDlg::OnBnClickedSettingBtn)
	ON_BN_CLICKED(IDC_UPDATE_BTN, &CBlockDlg::OnBnClickedUpdateBtn)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_DBG_BTN, &CBlockDlg::OnBnClickedDbgBtn)
	ON_STN_CLICKED(IDC_HACKERSHOLDINGS_URL_STC, &CBlockDlg::OnClickedUrlStc)
	ON_STN_CLICKED(IDC_HELPDESK_URL_STC, &CBlockDlg::OnClickedHelpdeskUrlStc)

	ON_MESSAGE(WM_TRAYICON, OnTrayIcon)
	ON_COMMAND(WM_APP_EXIT, OnAppExit)
	ON_COMMAND(WM_DIALOG_SHOW, OnDialogShow)
	
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CBlockDlg 메시지 처리기

BOOL CBlockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//---------------------------------------------
	TCHAR szPath[512];
	memset(szPath, 0x00, sizeof(szPath));
	GetModuleFileName(NULL, szPath, _MAX_PATH);

	m_CurPath = szPath;
	int nIndex = m_CurPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		m_CurPath = m_CurPath.Left(nIndex);
	}

	else {
		m_CurPath.Empty();
	}


	_CrtDumpMemoryLeaks();

	//_CrtSetBreakAlloc(628);
	
	//SetCurrentDirectory(CurPath.GetBuffer(0));
	//---------------------------------------------
	//ini 파일 경로 설정
	m_IniPath = m_CurPath + L"\\LossBlock.ini";
	m_IniFile.SetIniFileName(m_IniPath, 255);

	//윈도우 크기 설정
	SetWindowPos(NULL, -1, -1, 600, 480, SWP_NOMOVE | SWP_NOZORDER);

	//최소화, 닫기 버튼 위치
	m_MinBtn.MoveWindow(544, 15, 18, 18);
	m_CloseBtn.MoveWindow(572, 15, 18, 18);

	m_MinBtn.LoadStdImage(IDB_MIN_BTN, _T("PNG"));
	m_CloseBtn.LoadStdImage(IDB_CLOSE_BTN, _T("PNG"));
	m_HomeBtn.LoadStdImage(IDB_HOME_BTN, _T("PNG"));
	m_ScanBtn.LoadStdImage(IDB_SCAN_BTN, _T("PNG"));
	m_OptimizationBtn.LoadStdImage(IDB_OPTIMIZATION_BTN, _T("PNG"));
	m_DiagnosticBtn.LoadStdImage(IDB_DIAGNOSTIC_BTN, _T("PNG"));
	m_LogBtn.LoadStdImage(IDB_LOG_BTN, _T("PNG"));
	m_SettingBtn.LoadStdImage(IDB_SETTING_BTN, _T("PNG"));


	//메뉴 버튼 위치
	m_HomeBtn.MoveWindow(10 , 63, 100, 35);
	m_ScanBtn.MoveWindow(105, 63, 100, 35);
	m_OptimizationBtn.MoveWindow(200.4, 63, 100, 35);
	m_DiagnosticBtn.MoveWindow(295, 63, 100, 35);
	m_LogBtn.MoveWindow(390, 63, 100, 35);
	m_SettingBtn.MoveWindow(485, 63, 96.7, 35);


	//디버그 다이알로 그 생성 - 개발시 로그를 보기 위함
	m_DbgDlg.Create(IDD_DBG_DIALOG);
	m_DbgBtn.ShowWindow(SW_HIDE);//디버그 버튼 보임
#ifdef _DEBUG

	m_DbgBtn.ShowWindow(SW_SHOW);//디버그 버튼 숨김
#endif	



	m_UpdateBtn.ShowWindow(SW_HIDE);//업데이트 버튼

	//링크 경로와 고객센터 링크 Static 위치
	m_Url.MoveWindow(458, 458, 90, 12);
	m_HelpDesk.MoveWindow(548, 458, 60, 12);

	
	SubDlgInit();

	//ini 를 읽어 들여서 가장 마지막에 저장된 화면을 보여주도록 하기 위함
	CString strView;
	m_IniFile.GetString(L"SET", L"Last View", strView, L"Home");

	if (strView.Compare(L"Home") == 0)
		SubDlgShow((CDialogEx*)& m_HomeDlg);
	else if (strView.Compare(L"Scan") == 0)
		SubDlgShow((CDialogEx *)&m_ScanDlg);
	else if (strView.Compare(L"Diagnostic") == 0)
		SubDlgShow((CDialogEx *)&m_DiagnosticDlg);
	else if (strView.Compare(L"Optimization") == 0)
		SubDlgShow((CDialogEx *)&m_OptimizationDlg);
	else if (strView.Compare(L"Log") == 0)
		SubDlgShow((CDialogEx *)&m_LogDlg);
	else if (strView.Compare(L"Setting") == 0)
		SubDlgShow((CDialogEx *)&m_SettingDlg);
	else
		SubDlgHide();


	CPngImage m_BGImage;
	m_BGImage.Load(IDB_BG, AfxGetInstanceHandle());
	m_BGBitmap.Attach(m_BGImage.Detach());


		
	m_myTray.m_bHide = m_bHide;
	m_myTray.AddTrayIcon(GetSafeHwnd());
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CBlockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CBlockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CBlockDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CBlockDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


BOOL CBlockDlg::OnEraseBkgnd(CDC* pDC)
{
	if (!m_BGBitmap.m_hObject)
		return true;

	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dc.SelectObject(&m_BGBitmap);
	int bmw, bmh;
	BITMAP bmap;
	m_BGBitmap.GetBitmap(&bmap);
	bmw = bmap.bmWidth;
	bmh = bmap.bmHeight;
	int xo = 0, yo = 0;

	pDC->StretchBlt(xo, yo, rect.Width(), rect.Height(), &dc, 0, 0, bmw, bmh, SRCCOPY);

	dc.SelectObject(pOldBitmap);

	m_MinBtn.SetBkGnd(pDC);
	m_CloseBtn.SetBkGnd(pDC);

	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


LRESULT CBlockDlg::OnNcHitTest(CPoint point)
{
	UINT nHitTest = CDialog::OnNcHitTest(point);
	// also fake windows out, but this maximizes the window when you double
	// click on it. 
	return (nHitTest == HTCLIENT) ? HTCAPTION : nHitTest;

	//return CDialog::OnNcHitTest(point);
}


void CBlockDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnLButtonDown(nFlags, point);
	// fake windows into thinking your clicking on the caption, does not
	// maximize on double click
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}




/////////////////////////////////////////////////////////
///////////			홈페이지 URL		/////////////////
/////////////////////////////////////////////////////////
void CBlockDlg::OnClickedUrlStc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShellExecuteA(NULL, "open", "iexplore", "https://hackersholdings.com/", NULL, SW_HIDE);
}

/////////////////////////////////////////////////////////
///////////			고객센터 URL		/////////////////
/////////////////////////////////////////////////////////
void CBlockDlg::OnClickedHelpdeskUrlStc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShellExecuteA(NULL, "open", "iexplore", "https://hackersholdings.com/bbs/board.php?bo_table=qa", NULL, SW_HIDE);
}



LRESULT CBlockDlg::OnTrayIcon(WPARAM wParam, LPARAM lParam)

{

	m_myTray.ProcTrayMsg(GetSafeHwnd(), wParam, lParam);

	return 0;

}

void CBlockDlg::OnAppExit(void)

{

	m_myTray.DelTrayIcon(GetSafeHwnd());

	CLossBlockDlg::OnCancel();

}

void CBlockDlg::OnDialogShow(void)

{

	if (!m_bHide) ShowWindow(false);       //보이는상태라면숨기고

	else ShowWindow(true);                //숨겨진상태라면보이게

	m_bHide = !m_bHide;

	m_myTray.m_bHide = m_bHide;

}

HBRUSH CBlockDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(192, 192, 192));
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
