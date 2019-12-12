// SettingDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg 대화 상자

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_DIALOG, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AUTO_START, m_AutoStart);
	DDX_Control(pDX, IDC_AUTO_UPDATE, m_AutoUpdate);
	DDX_Control(pDX, IDC_HOME_URL_PROTECT, m_HomeUrlProtect);
	DDX_Control(pDX, IDC_HOME_URL_EDT, m_HomeUrl);
	DDX_Control(pDX, IDC_HOME_URL_CHANGE_NOTICE, m_HomeUrlChangeNotice);
	DDX_Control(pDX, IDC_HARMFUL_WEBSITE_PROTECT, m_HarmfulWebsiteProtect);
	DDX_Control(pDX, IDC_NO_SIGNED_PROCESS_NOTICE, m_NoSignedProcessNotice);
	DDX_Control(pDX, IDC_HARMFUL_SCRIPT_BLOCKING, m_HarmfulScriptBlocking);
	DDX_Control(pDX, IDC_HARMFUL_SCRIPT_BLOCKING_NOTICE, m_HarmfulScriptBlockingNotice);

	DDX_Control(pDX, IDC_LOG_SAVE_PERIOD, m_Logsave);
	DDX_Control(pDX, IDC_UNCHECK_NOTICE_PERIOD, m_Uncheck);
	DDX_Control(pDX, IDC_SETTING_SAVE_BTN, m_SettingSave);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_SETTING_SAVE_BTN, &CSettingDlg::OnBnClickedSettingSaveBtn)

	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSettingDlg 메시지 처리기


BOOL CSettingDlg::OnInitDialog()
{	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CDialogEx::OnInitDialog();

	CPngImage m_BGImage;
	m_BGImage.Load(IDB_SETTING_BG, AfxGetInstanceHandle());
	m_BGBitmap.Attach(m_BGImage.Detach());


	TCHAR StartPage[255] = L"";
	m_Home.GetRegdata(HKEY_CURRENT_USER,L"Software\\Microsoft\\Internet Explorer\\Main", L"Start Page", StartPage);
	SetDlgItemTextW(IDC_HOME_URL_EDT, StartPage);
	m_Logsave.InsertString(-1, _T("1개월"));
	m_Logsave.InsertString(-1, _T("3개월"));
	m_Logsave.InsertString(-1, _T("5개월"));
	m_Logsave.InsertString(-1, _T("1년"));
	m_Uncheck.InsertString(-1, _T("1일"));
	m_Uncheck.InsertString(-1, _T("2일"));
	m_Uncheck.InsertString(-1, _T("3일"));
	m_Uncheck.InsertString(-1, _T("1주"));
	m_Uncheck.InsertString(-1, _T("2주"));

	m_AutoStart.MoveWindow(209, 35, 60, 18);
	m_AutoUpdate.MoveWindow(209, 80, 60, 18);
	m_Logsave.MoveWindow(208.5, 122, 40, 40);
	m_Uncheck.MoveWindow(208.5, 170, 40, 40);
	m_HomeUrl.MoveWindow(242, 215, 185, 20);
	m_HomeUrlProtect.MoveWindow(272, 240, 60, 18);
	m_HomeUrlChangeNotice.MoveWindow(272, 264, 60, 18);
	m_HarmfulWebsiteProtect.MoveWindow(509, 34, 60, 18);
	m_NoSignedProcessNotice.MoveWindow(509, 80, 60, 18);
	m_HarmfulScriptBlocking.MoveWindow(509, 125, 60, 18);
	m_SettingSave.MoveWindow(494, 305, 66, 30);
	
	m_SettingSave.LoadStdImage(IDB_SETTINGSAVE_BTN, _T("PNG"));
	m_AutoStart.LoadStdImage(IDB_TOOGLE_UNCHECK, _T("PNG"));
	m_AutoStart.LoadAltImage(IDB_TOOGLE_CHECK, _T("PNG"));
	m_AutoStart.EnableToggle(TRUE);

	m_AutoUpdate.LoadStdImage(IDB_TOOGLE_UNCHECK, _T("PNG"));
	m_AutoUpdate.LoadAltImage(IDB_TOOGLE_CHECK, _T("PNG"));
	m_AutoUpdate.EnableToggle(TRUE);

	m_HomeUrlProtect.LoadStdImage(IDB_TOOGLE_UNCHECK, _T("PNG"));
	m_HomeUrlProtect.LoadAltImage(IDB_TOOGLE_CHECK, _T("PNG"));
	m_HomeUrlProtect.EnableToggle(TRUE);

	m_HomeUrlChangeNotice.LoadStdImage(IDB_TOOGLE_UNCHECK, _T("PNG"));
	m_HomeUrlChangeNotice.LoadAltImage(IDB_TOOGLE_CHECK, _T("PNG"));
	m_HomeUrlChangeNotice.EnableToggle(TRUE);

	m_HarmfulWebsiteProtect.LoadStdImage(IDB_TOOGLE_UNCHECK, _T("PNG"));
	m_HarmfulWebsiteProtect.LoadAltImage(IDB_TOOGLE_CHECK, _T("PNG"));
	m_HarmfulWebsiteProtect.EnableToggle(TRUE);

	m_NoSignedProcessNotice.LoadStdImage(IDB_TOOGLE_UNCHECK, _T("PNG"));
	m_NoSignedProcessNotice.LoadAltImage(IDB_TOOGLE_CHECK, _T("PNG"));
	m_NoSignedProcessNotice.EnableToggle(TRUE);

	m_HarmfulScriptBlocking.LoadStdImage(IDB_TOOGLE_UNCHECK, _T("PNG"));
	m_HarmfulScriptBlocking.LoadAltImage(IDB_TOOGLE_CHECK, _T("PNG"));
	m_HarmfulScriptBlocking.EnableToggle(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CSettingDlg::OnEraseBkgnd(CDC* pDC)
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


	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
	
}


void CSettingDlg::OnBnClickedSettingSaveBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_AutoStart.GetCheck() == 1)
	{
		m_Home.Registry_add(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"LossBlock", L"C:\\YClean\\YClean.exe");
	}
	else
	{
		m_Home.DelRegdata(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"LossBlock");
	}

	CString str;
	m_HomeUrl.GetWindowTextW(str);
	TCHAR Page[1024] = L"";
	memset(Page, '\0', sizeof(Page));
	wcscpy_s(Page, (LPCTSTR)str);
	m_Home.Registry_add(HKEY_CURRENT_USER,L"SOFTWARE\\Microsoft\\Internet Explorer\\Main", L"Start Page", Page);
}



HBRUSH CSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
