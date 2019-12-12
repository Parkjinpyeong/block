// DiagnosticDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "DiagnosticDlg.h"
#include "afxdialogex.h"


#define BUFSIZE 256  
#define SUBKEY_NUM 100
using namespace std;

// DiagnosticDlg 대화 상자

IMPLEMENT_DYNAMIC(CDiagnosticDlg, CDialogEx)

CDiagnosticDlg::CDiagnosticDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIAGNOSTIC_DIALOG, pParent)
{

}

CDiagnosticDlg::~CDiagnosticDlg()
{
}


void CDiagnosticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FORMER_LIST, m_former_list);
	DDX_Control(pDX, IDC_ACTIVEX_STC, m_ActivexStc);
	DDX_Control(pDX, IDC_AUTORUN_STC, m_AutorunStc);
	DDX_Control(pDX, IDC_COOKIE_STC, m_CookieStc);
	DDX_Control(pDX, IDC_TOOLBAR_BHO_STC, m_ToolbarStc);
	DDX_Control(pDX, IDC_DNS_STC, m_DnsStc);
	DDX_Control(pDX, IDC_DATE_COMBO, m_HistroyDate);
	DDX_Control(pDX, IDC_CURRENT_DATE, m_CurrentDate);
	DDX_Control(pDX, IDC_RECENT_LIST, m_recent_list);
}


BEGIN_MESSAGE_MAP(CDiagnosticDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	//ON_LBN_SELCHANGE(IDC_LIST1, &CDiagnosticDlg::OnLbnSelchangeList1)
//	ON_LBN_SELCHANGE(IDC_FORMER_LIST, &CDiagnosticDlg::OnLbnSelchangeFormerList)
ON_STN_CLICKED(IDC_AUTORUN_STC, &CDiagnosticDlg::OnStnClickedAutorunStc)
ON_STN_CLICKED(IDC_ACTIVEX_STC, &CDiagnosticDlg::OnStnClickedActivexStc)
ON_STN_CLICKED(IDC_TOOLBAR_BHO_STC, &CDiagnosticDlg::OnStnClickedToolbarBhoStc)
ON_STN_CLICKED(IDC_DNS_STC, &CDiagnosticDlg::OnStnClickedDnsStc)
ON_STN_CLICKED(IDC_COOKIE_STC, &CDiagnosticDlg::OnStnClickedCookieStc)
ON_WM_CTLCOLOR()
//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDiagnosticDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// DiagnosticDlg 메시지 처리기


BOOL CDiagnosticDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	CPngImage m_BGImage;
	m_BGImage.Load(IDB_TOTAL_BG, AfxGetInstanceHandle());
	m_BGBitmap.Attach(m_BGImage.Detach());


	m_AutorunStc.MoveWindow(82, 20, 72, 16);
	m_ActivexStc.MoveWindow(204, 20, 44, 15);
	m_ToolbarStc.MoveWindow(298, 20, 70, 16);
	m_DnsStc.MoveWindow(418, 20, 28, 16);
	m_CookieStc.MoveWindow(496, 20, 22, 16);
	m_HistroyDate.MoveWindow(83, 50, 134, 24);
	m_CurrentDate.MoveWindow(315, 50, 172, 24);
	m_recent_list.MoveWindow(300, 80, 280, 250);


	
	

	CTime ctime = CTime::GetCurrentTime();
	CString strDate;
	strDate.Format(_T("%04d년 %02d월 %02d일 (최종상태)"), ctime.GetYear(), ctime.GetMonth(), ctime.GetDay());
	m_CurrentDate.SetWindowTextW(strDate);
	m_former_list.ShowWindow(SW_HIDE);
	m_recent_list.ShowWindow(SW_HIDE);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CDiagnosticDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CDiagnosticDlg::OnEraseBkgnd(CDC* pDC)
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
}

////	시작프로그램		/////////////
void CDiagnosticDlg::OnStnClickedAutorunStc()
{
	CRect rt;
	while (m_recent_list.GetHeaderCtrl()->GetItemCount() > 0)
	{
		m_recent_list.DeleteColumn(0);
	}
	m_recent_list.DeleteAllItems();
	m_recent_list.GetWindowRect(&rt);
	m_recent_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_recent_list.InsertColumn(0, TEXT("시작프로그램"), LVCFMT_LEFT, rt.Width() * 0.3);
	m_recent_list.InsertColumn(1, TEXT("경로"), LVCFMT_CENTER, rt.Width() * 0.7);

	DWORD RegDataCnt = 0;
	LPTSTR SubName[SUBKEY_NUM] = { 0 };
	GetSubDataList(L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Run", &RegDataCnt, SubName);

	for (int i = 0; i < RegDataCnt; i++)
	{
		TCHAR Path[255] = L"";

		GetRegData(L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Run", SubName[i], Path);

		m_recent_list.InsertItem(i, SubName[i]);
		m_recent_list.SetItemText(i,1, Path);
		

	}
}
//////////		ActiveX		/////////////////
void CDiagnosticDlg::OnStnClickedActivexStc()
{
	m_former_list.ShowWindow(SW_SHOW);
	m_recent_list.ShowWindow(SW_SHOW);
	m_former_list.ResetContent();
	m_former_list.InsertString(-1,L"activex");

	CRect rt;
	while (m_recent_list.GetHeaderCtrl()->GetItemCount() > 0)
	{
		m_recent_list.DeleteColumn(0);
	}
	m_recent_list.DeleteAllItems();
	m_recent_list.GetWindowRect(&rt);
	m_recent_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_recent_list.InsertColumn(0, TEXT("ActiveX"), LVCFMT_LEFT, rt.Width() * 0.3);
	m_recent_list.InsertColumn(1, TEXT("경로"), LVCFMT_CENTER, rt.Width() * 0.7);

	DWORD RegKeyCnt = 0;
	LPTSTR SubName[SUBKEY_NUM] = { 0 };


	GetSubKeyList(L"SOFTWARE\\WOW6432Node\\Microsoft\\Code Store Database\\Distribution Units", &RegKeyCnt, SubName);

	for (int i = 0; i < RegKeyCnt; i++)
	{
		TCHAR CLSID[255] = L"";
		TCHAR ClsidData[255] = L"";
		TCHAR ClsidPath[255] = L"";

		GetClsidData(L"SOFTWARE\\Classes\\WOW6432Node\\CLSID", SubName[i], i, CLSID, ClsidData, ClsidPath);
		m_recent_list.InsertItem(i, ClsidData);
		m_recent_list.SetItemText(i, 1, ClsidPath);
		
	}


}

/////////		Toolbar/BHO		/////////////////
void CDiagnosticDlg::OnStnClickedToolbarBhoStc()
{
	m_former_list.ShowWindow(SW_SHOW);
	m_recent_list.ShowWindow(SW_SHOW);
	m_former_list.ResetContent();
	m_former_list.InsertString(-1,L"bho");
	CRect rt;
	DWORD RegDataCnt2 = 0;
	LPTSTR SubName2[SUBKEY_NUM] = { 0 };
	DWORD RegKeyCnt = 0;
	LPTSTR SubName[SUBKEY_NUM] = { 0 };

	while (m_recent_list.GetHeaderCtrl()->GetItemCount() > 0)
	{
		m_recent_list.DeleteColumn(0);
	}
	m_recent_list.DeleteAllItems();
	m_recent_list.GetWindowRect(&rt);
	m_recent_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_recent_list.InsertColumn(0, TEXT("Toolbar"), LVCFMT_LEFT, rt.Width() * 0.25);
	m_recent_list.InsertColumn(1, TEXT("경로"), LVCFMT_CENTER, rt.Width() * 0.25);
	m_recent_list.InsertColumn(2, TEXT("BHO"), LVCFMT_CENTER, rt.Width() * 0.25);
	m_recent_list.InsertColumn(3, TEXT("경로"), LVCFMT_CENTER, rt.Width() * 0.25);
	
	///////		TOOLBAR			/////////////
	GetSubDataList(L"SOFTWARE\\WOW6432Node\\Microsoft\\Internet Explorer\\Toolbar", &RegDataCnt2, SubName2);
	for (int i = 0; i < RegDataCnt2; i++)
	{
		TCHAR CLSID[255] = L"";
		TCHAR ClsidData[255] = L"";
		TCHAR ClsidPath[255] = L"";
		GetClsidData(L"SOFTWARE\\Classes\\WOW6432Node\\CLSID", SubName2[i], i, CLSID, ClsidData, ClsidPath);
		m_recent_list.InsertItem(i, ClsidData);
		m_recent_list.SetItemText(i, 1, ClsidPath);
	}
	//////		BHO		////////////////////
	GetSubKeyList(L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Browser Helper Objects", &RegKeyCnt, SubName);
	for (DWORD i = 0; i < RegKeyCnt; i++)
	{
		TCHAR CLSID[255] = L"";
		TCHAR ClsidData[255] = L"";
		TCHAR ClsidPath[255] = L"";
		GetClsidData(L"SOFTWARE\\Classes\\WOW6432Node\\CLSID", SubName[i], i, CLSID, ClsidData, ClsidPath);
		m_recent_list.SetItemText(i,3, ClsidData);
		m_recent_list.SetItemText(i, 4, ClsidPath);
	}
	
}
/////////		DNS			///////////////////
void CDiagnosticDlg::OnStnClickedDnsStc()
{
	m_former_list.ShowWindow(SW_SHOW);
	m_recent_list.ShowWindow(SW_SHOW);
	m_former_list.ResetContent();
	m_former_list.InsertString(-1,L"dns");
	CRect rt;
	while (m_recent_list.GetHeaderCtrl()->GetItemCount() > 0)
	{
		m_recent_list.DeleteColumn(0);
	}
	m_recent_list.DeleteAllItems();
	m_recent_list.GetWindowRect(&rt);
	m_recent_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_recent_list.InsertColumn(0, TEXT("DNS"), LVCFMT_LEFT, rt.Width() * 0.5);
	m_recent_list.InsertColumn(1, TEXT("변조 여부"), LVCFMT_CENTER, rt.Width() * 0.5);
	m_recent_list.SetItemText(4, 1, L"주요 DNS");
	TCHAR Value[255] = L"";
	TCHAR Value1[255] = L"";
	TCHAR* token;
	TCHAR* next_token;
	GetDNSdata(Value);
	token = _tcstok(Value, Value1);
	_tprintf(_T("%s\n"));
}
/////////		Cookie		////////////////
void CDiagnosticDlg::OnStnClickedCookieStc()
{
	m_former_list.ShowWindow(SW_SHOW);
	m_recent_list.ShowWindow(SW_SHOW);
	m_former_list.ResetContent();
	m_former_list.InsertString(-1,L"cookie");
	
	CRect rt;
	while (m_recent_list.GetHeaderCtrl()->GetItemCount() > 0)
	{
		m_recent_list.DeleteColumn(0);
	}
	m_recent_list.DeleteAllItems();
	m_recent_list.GetWindowRect(&rt);
	m_recent_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_recent_list.InsertColumn(0, TEXT("Cookie"), LVCFMT_LEFT, rt.Width() * 0.3);
	m_recent_list.InsertColumn(1, TEXT("경로"), LVCFMT_CENTER, rt.Width() * 0.7);

}

HBRUSH CDiagnosticDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

BOOL CDiagnosticDlg::GetRegData(LPTSTR RegKeyPath, LPTSTR RegName, LPTSTR RegData)
{

	CRegistry m_Reg(NULL);  // No special flags

	if (m_Reg.Open(RegKeyPath, HKEY_LOCAL_MACHINE)) {

		StringCchCat(RegData, BUFSIZE, m_Reg[RegName]);

		// Close the open key
		m_Reg.Close();

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDiagnosticDlg::GetSubDataList(LPTSTR RegKeyPath, DWORD* RegDataCnt, LPTSTR RegName[])
{

	CRegistry m_Reg(NULL);  // No special flags

	if (m_Reg.Open(RegKeyPath, HKEY_LOCAL_MACHINE)) {

		int Cnt = m_Reg.Count();
		*RegDataCnt = m_Reg.Count();
		for (int i = 0; i < Cnt; i++)
		{
			CRegEntry* reEntry = m_Reg.GetAt(i);

			RegName[i] = new TCHAR[BUFSIZE];

			wsprintf(RegName[i], L"%s", reEntry->lpszName);


		}
		// Close the open key
		m_Reg.Close();

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDiagnosticDlg::GetClsidData(LPTSTR RegKeyPath, LPTSTR RegName, DWORD ClsidKeyCnt, LPTSTR RegData, LPTSTR CLSID_Data, LPTSTR CLSID_PATH)
{


	CRegistry m_Reg(NULL);  // No special flags

	if (m_Reg.Open(RegKeyPath, HKEY_LOCAL_MACHINE)) {

		//StringCchCat(RegData, BUFSIZE, m_Reg[RegName]);
		//_tcsncat(RegKeyPath, RegName, BUFSIZE);
		//RegData = new TCHAR[BUFSIZE];
		StringCchCat(RegData, BUFSIZE, RegKeyPath);
		StringCchCat(RegData, BUFSIZE, L"\\");
		StringCchCat(RegData, BUFSIZE, RegName);
		if (m_Reg.Open(RegData, HKEY_LOCAL_MACHINE)) {
			StringCchCat(CLSID_Data, BUFSIZE, m_Reg[L""]);

			//레지스트리 경로에 \\InprocServer32 를 추가
			StringCchCat(RegData, BUFSIZE, L"\\InprocServer32");


			// 레지스트리 key에 InprocServer32가 있으면 실행
			if (m_Reg.Open(RegData, HKEY_LOCAL_MACHINE)) {
				StringCchCat(CLSID_PATH, BUFSIZE, m_Reg[L""]);
			}
		}
		// Close the open key

		m_Reg.Close();

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDiagnosticDlg::GetSubKeyList(LPTSTR RegKeyPath, DWORD* RegKeyCnt, LPTSTR RegKeyName[])
{

	CRegistry m_Reg(NULL);  // No special flags

	if (m_Reg.Open(RegKeyPath, HKEY_LOCAL_MACHINE, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS)) {

		DWORD KeyCnt = 0;
		m_Reg.SubKeyCount(&KeyCnt);

		DWORD    cbName;
		DWORD i, retCode;
		TCHAR    achKey[255];
		FILETIME ftLastWriteTime;      // last write time 

		*RegKeyCnt = KeyCnt;

		for (i = 0; i < KeyCnt; i++)
		{
			cbName = 255;
			retCode = RegEnumKeyEx(m_Reg.hKey, i,
				achKey,
				&cbName,
				NULL,
				NULL,
				NULL,
				&ftLastWriteTime);
			if (retCode == ERROR_SUCCESS)
			{
				_tprintf(TEXT("(%d) %s\n"), i + 1, achKey);


				RegKeyName[i] = new TCHAR[BUFSIZE];

				wsprintf(RegKeyName[i], L"%s", achKey);

			}
		}

		// Close the open key
		m_Reg.Close();

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void  CDiagnosticDlg::GetDNSdata(LPTSTR Regvalue) {
	LONG lResult;
	HKEY hKey = { 0 };
	DWORD dwType;		//데이터 타입
	DWORD dwBytes = 128;	//데이터 크기
	TCHAR buffer[128] = { 0, };
	TCHAR netcard[128] = { 0, };
	// open Regstry Key(KEY_ALL_ACCESS)
	LONG openRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\NetworkCards\\2", 0, KEY_ALL_ACCESS, &hKey);

	if (openRes == ERROR_SUCCESS) {
		printf("Success opening key.");
	}
	else {
		printf("Error opening key.");
	}
	LONG Result = RegQueryValueEx(hKey, L"ServiceName", 0, &dwType, (LPBYTE)buffer, &dwBytes);
	if (Result == ERROR_SUCCESS)
	{
		printf("Success getting to Registry.");
		StringCchCat(netcard, BUFSIZ, buffer);
	}
	else
	{
		printf("Error getting to Registry.");
	}
	LONG closeOut = RegCloseKey(hKey);
	if (closeOut == ERROR_SUCCESS) {
		printf("Success closing key.");
	}
	else {
		printf("Error closing key.");
	}


	TCHAR Path[255] = { 0, };
	_tcscat(Path, L"SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces" );
	_tcscat(Path, L"\\");
	_tcscat(Path, netcard);

	LONG openRes1 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, Path, 0, KEY_ALL_ACCESS, &hKey);

	if (openRes1 == ERROR_SUCCESS) {
		printf("Success opening key.");
	}
	else {
		printf("Error opening key.");
	}
	LONG Result1 = RegQueryValueEx(hKey, L"DhcpNameServer", 0, &dwType, (LPBYTE)buffer, &dwBytes);
	if (Result1 == ERROR_SUCCESS)
	{
		printf("Success getting to Registry.");
		StringCchCat(Regvalue, BUFSIZ, buffer);
	}
	else
	{
		printf("Error getting to Registry.");
	}
	LONG closeOut1 = RegCloseKey(hKey);
	if (closeOut1 == ERROR_SUCCESS) {
		printf("Success closing key.");
	}
	else {
		printf("Error closing key.");
	}
}
