// OptimizationDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "OptimizationDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <io.h>

using namespace std;
// COptimizationDlg 대화 상자

IMPLEMENT_DYNAMIC(COptimizationDlg, CDialogEx)

#define SUBKEY_NUM 100
#define BUFSIZE 256  

COptimizationDlg::COptimizationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPTIMIZATION_DIALOG, pParent)
{

}

COptimizationDlg::~COptimizationDlg()
{
}

void COptimizationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISK_OPTIMIZATION_STATUS_STC, m_DiskOptimizationStatus);
	DDX_Control(pDX, IDC_SYSTEM_OPTIMIZATION_STATUS_STC, m_SystemOptimizationStatus);
	DDX_Control(pDX, IDC_INTERNET_OPTIMIZATION_STATUS_ST, m_InternetOptimizationStatus);
	DDX_Control(pDX, IDC_COOKIE_OPTIMIZATION_STATUS_STC, m_CookieOptimizationStatus);
	DDX_Control(pDX, IDC_DISK_OPTIMIZATION_BTN, m_DiskOptimizationBtn);
	DDX_Control(pDX, IDC_SYSTEM_OPTIMIZATION_BTN, m_SystemOptimizationBtn);
	DDX_Control(pDX, IDC_INTERNET_OPTIMIZATION_BTN, m_InternetOptimizationBtn);
	DDX_Control(pDX, IDC_COOKIE_OPTIMIZATION_BTN, m_CookieOptimizationBtn);
}


BEGIN_MESSAGE_MAP(COptimizationDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_DISK_OPTIMIZATION_BTN, &COptimizationDlg::OnBnClickedDiskOptimizationBtn)
	ON_BN_CLICKED(IDC_SYSTEM_OPTIMIZATION_BTN, &COptimizationDlg::OnBnClickedSystemOptimizationBtn)
	ON_BN_CLICKED(IDC_INTERNET_OPTIMIZATION_BTN, &COptimizationDlg::OnBnClickedInternetOptimizationBtn)
	ON_BN_CLICKED(IDC_COOKIE_OPTIMIZATION_BTN, &COptimizationDlg::OnBnClickedCookieOptimizationBtn)
//	ON_STN_CLICKED(IDC_INTERNET_OPTIMIZATION_STATUS_ST, &COptimizationDlg::OnStnClickedInternetOptimizationStatusSt)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// COptimizationDlg 메시지 처리기


BOOL COptimizationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	CPngImage m_BGImage;
	m_BGImage.Load(IDB_OPTIMIZATION_BG, AfxGetInstanceHandle());
	m_BGBitmap.Attach(m_BGImage.Detach());


	m_DiskOptimizationStatus.MoveWindow(61,39, 230, 20);
	m_SystemOptimizationStatus.MoveWindow(361, 39, 230, 20);
	m_InternetOptimizationStatus.MoveWindow(61, 207, 230, 20);
	m_CookieOptimizationStatus.MoveWindow(361, 207, 230, 20);

	m_DiskOptimizationBtn.MoveWindow(112, 115, 76, 29);
	m_SystemOptimizationBtn.MoveWindow(412, 115, 76, 29);
	m_InternetOptimizationBtn.MoveWindow(112, 287, 76, 29);
	m_CookieOptimizationBtn.MoveWindow(412, 287, 76, 29);

	m_DiskOptimizationBtn.LoadStdImage(IDB_OPTIMIZATIONRUN_BTN, _T("PNG"));
	m_SystemOptimizationBtn.LoadStdImage(IDB_OPTIMIZATIONRUN_BTN, _T("PNG"));
	m_InternetOptimizationBtn.LoadStdImage(IDB_OPTIMIZATIONRUN_BTN, _T("PNG"));
	m_CookieOptimizationBtn.LoadStdImage(IDB_OPTIMIZATIONRUN_BTN, _T("PNG"));


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL COptimizationDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL COptimizationDlg::OnEraseBkgnd(CDC* pDC)
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

///////		디스크 최적화		/////////////
void COptimizationDlg::OnBnClickedDiskOptimizationBtn()
{
	
	LPCTSTR filename[SUBKEY_NUM] = { 0 };

	DWORD DirCnt = DeletediskCache(filename);
	if (DirCnt == 0) {
		MessageBox(L"임시파일이 없습니다.");
	}
	else
	{
		CString message;
		message.Format(L"%u 개 삭제했습니다.", DirCnt);
		AfxMessageBox(message);
	}
}


void COptimizationDlg::OnBnClickedSystemOptimizationBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

///////		인터넷 최적화		//////////////
void COptimizationDlg::OnBnClickedInternetOptimizationBtn()
{
	DWORD RegKeyCnt = 0;
	DWORD RegKeyCnt1 = 0;
	DWORD RegKeyCnt2 = 0;
	DelSubKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Browser Helper Objects", &RegKeyCnt);
	DelSubKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Browser Helper Objects", &RegKeyCnt1);
	
	DelToolbar(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Internet Explorer\\Toolbar", &RegKeyCnt2);


	DWORD Cnt = RegKeyCnt + RegKeyCnt1 + RegKeyCnt2;
	
	if (Cnt == 0) {
		MessageBox(L"BHO/툴바가 없습니다.");
	}
	else
	{
		CString message;
		message.Format(L"%u 개 삭제했습니다.", Cnt);
		AfxMessageBox(message);
	}
	
	
}

////////		쿠키최적화		/////////////////
void COptimizationDlg::OnBnClickedCookieOptimizationBtn()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPCTSTR ContentMSOList[255] = { 0 };
	DWORD Cnt = GetContentMSO();
	if (Cnt == 0) {
		MessageBox(L"쿠키가 없습니다.");
	}
	else{
	CString message;
	message.Format(L"%u 개 삭제했습니다.", Cnt);
	AfxMessageBox(message);
	}
}

///////		인터넷 쿠키		///////
BOOL COptimizationDlg::GetContentMSO( /*DWORD* Cnt,LPTSTR Content_MSO_List[]*/)
{
	TCHAR szUserProfile[1024] = L"";
	ExpandEnvironmentStrings(L"%userprofile%", szUserProfile, sizeof(szUserProfile));
	wstring Content_MSO_W(szUserProfile);
	Content_MSO_W += L"\\AppData\\Local\\Microsoft\\Windows\\INetCache\\Content.MSO\\*.*";
	LPCTSTR Path = Content_MSO_W.c_str();
	HANDLE hFile;
	WIN32_FIND_DATA wfd;
	DWORD dwFileAttr;
	string strPathFile;
	wstring Content_MSO_WS(szUserProfile);
	Content_MSO_WS += L"\\AppData\\Local\\Microsoft\\Windows\\INetCache\\Content.MSO\\";
	string content_mso(Content_MSO_WS.begin(), Content_MSO_WS.end());

	int i = 0;
	hFile = FindFirstFile(Path, &wfd);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			wchar_t* test = wfd.cFileName;
			wstring ws(test);
			string strFile(ws.begin(), ws.end());
			//string Path(szPath);
			strPathFile = content_mso + strFile;

			// get the file attributes
			dwFileAttr = GetFileAttributesA(strPathFile.c_str());

			// see if file is read-only : if so unset read-only
			if (dwFileAttr & FILE_ATTRIBUTE_READONLY)
			{
				dwFileAttr &= ~FILE_ATTRIBUTE_READONLY;
				SetFileAttributesA(strPathFile.c_str(), dwFileAttr);
			}

			// see if the file is a directory
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// make sure it isn't current or parent directory
				if (strFile != "." && strFile != "..")
				{
					strPathFile += "\\";
					// recursively delete all files in this folder
					delete(strPathFile.c_str());
					// remove the directory

					if (RemoveDirectoryA(strPathFile.c_str()))
					{
						string dir = "deleted directory : " + strPathFile;
						DWORD len;
						i++;
					}
				}
			}
			else
			{
				// delete the file
				if (DeleteFileA(strPathFile.c_str()))
				{
					string file = "deleted file : " + strPathFile;
					i++;
				}
			}
		} while (FindNextFile(hFile, &wfd));
	}
	FindClose(hFile);
	return (DWORD)i;
}
//////	디스크 임시폴더		///////
DWORD COptimizationDlg::DeletediskCache(LPCTSTR filename[])
{

	//filename[BUFSIZ] = { 0 };
	char szPath[MAX_PATH];
	GetTempPathA(MAX_PATH, szPath);  //TEMP 폴더 찾아주는 함수
	int DirCnt = 0;
	WIN32_FIND_DATA wfd;
	HANDLE hFile;
	DWORD dwFileAttr;
	string strFile;

	//Temp파일 경로 형변환(char -> string)
	string strSpec = szPath;
	//파일 경로
	string Spec = strSpec + "*.*";
	//풀 경로
	string strPathFile;

	DWORD len;
	DWORD slength = (DWORD)Spec.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, Spec.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, Spec.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	LPCTSTR Path = r.c_str();


	// find the first file
	hFile = FindFirstFile(Path, &wfd);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			wchar_t* test = wfd.cFileName;
			wstring ws(test);
			string strFile(ws.begin(), ws.end());
			//string Path(szPath);
			strPathFile = strSpec + strFile;

			// get the file attributes
			dwFileAttr = GetFileAttributesA(strPathFile.c_str());

			// see if file is read-only : if so unset read-only
			if (dwFileAttr & FILE_ATTRIBUTE_READONLY)
			{
				dwFileAttr &= ~FILE_ATTRIBUTE_READONLY;
				SetFileAttributesA(strPathFile.c_str(), dwFileAttr);
			}

			// see if the file is a directory
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// make sure it isn't current or parent directory
				if (strFile != "." && strFile != "..")
				{
					strPathFile += "\\";
					// recursively delete all files in this folder
					//DeleteAllFiles(strPathFile);
					remove(strPathFile.c_str());
					// remove the directory

					if (RemoveDirectoryA(strPathFile.c_str()))
					{
						string dir = "deleted directory : " + strPathFile;
						DWORD len;
						//	DWORD slength = (DWORD)dir.length() + 1;
						//	len = MultiByteToWideChar(CP_ACP, 0, dir.c_str(), slength, 0, 0);
						//	wchar_t* buf = new wchar_t[len];
						//	MultiByteToWideChar(CP_ACP, 0, dir.c_str(), slength, buf, len);
						//	std::wstring deldir(buf);
						//	delete[] buf;
						//	filename[DirCnt] = deldir.c_str();

						DirCnt++;
					}
					else
					{
						string notdir = "could not deleted directory : " + strPathFile;
						//	DWORD len;
						//	DWORD slength = (DWORD)notdir.length() + 1;
						//	len = MultiByteToWideChar(CP_ACP, 0, notdir.c_str(), slength, 0, 0);
						//	wchar_t* buf = new wchar_t[len];
						//	MultiByteToWideChar(CP_ACP, 0, notdir.c_str(), slength, buf, len);
						//	std::wstring notdeldir(buf);
						//	delete[] buf;
						//	filename[DirCnt] = notdeldir.c_str();
						//	DirCnt++;
					}
				}
			}
			else
			{
				// delete the file
				if (DeleteFileA(strPathFile.c_str()))
				{
					string file = "deleted file : " + strPathFile;
					//DWORD len;
					//DWORD slength = (DWORD)file.length() + 1;
					//len = MultiByteToWideChar(CP_ACP, 0, file.c_str(), slength, 0, 0);
					//wchar_t* buf = new wchar_t[len];
					//MultiByteToWideChar(CP_ACP, 0, file.c_str(), slength, buf, len);
					//std::wstring delfile(buf);
					//delete[] buf;
					//filename[DirCnt] = delfile.c_str();
					DirCnt++;
				}
				else
				{
					string notfile = "could not deleted file : " + strPathFile;
					//	DWORD len;
					//	DWORD slength = (DWORD)notfile.length() + 1;
					//	len = MultiByteToWideChar(CP_ACP, 0, notfile.c_str(), slength, 0, 0);
					//	wchar_t* buf = new wchar_t[len];
					//	MultiByteToWideChar(CP_ACP, 0, notfile.c_str(), slength, buf, len);
					//	std::wstring notdelfile(buf);
					//	delete[] buf;
					//	filename[DirCnt] = notdelfile.c_str();
					//	DirCnt++;
				}
			}
		} while (FindNextFile(hFile, &wfd));

	}
	FindClose(hFile);

	return (DWORD)DirCnt;

}
////// 레지스트리 하위키 삭제	/////////
BOOL COptimizationDlg::DelSubKey(HKEY Path, LPTSTR RegKeyPath, DWORD* RegKeyCnt)
{
	CRegistry m_Reg(NULL);  // No special flags
	if (m_Reg.Open(RegKeyPath, Path, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS)) {

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
				TCHAR	aKey[255] = L"";
				//aKey = strcat(RegKeyPath, achKey);
				_tcscat(aKey, RegKeyPath);
				_tcscat(aKey, L"\\");
				_tcscat(aKey, achKey);
				

				if(RegDeleteKey(Path, aKey) != ERROR_SUCCESS);
				{
					return FALSE;
				}
	
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

BOOL COptimizationDlg::DelToolbar(HKEY Path, LPTSTR RegKeyPath, DWORD* RegKeyCnt)
{
	CRegistry m_Reg(NULL);  // No special flags
	if (m_Reg.Open(RegKeyPath, Path, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS)) {
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
				TCHAR	aKey[255] = L"";
				//aKey = strcat(RegKeyPath, achKey);
				if (RegDeleteKey(Path, RegKeyPath) != ERROR_SUCCESS);
				{
					return FALSE;
				}
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


HBRUSH COptimizationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	return hbr;
}
