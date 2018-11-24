
// UltraFileSplitterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UltraFileSplitter.h"
#include "UltraFileSplitterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUltraFileSplitterDlg 对话框



CUltraFileSplitterDlg::CUltraFileSplitterDlg(CWnd* pParent /*=NULL*/): CDialogEx(CUltraFileSplitterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_MY);
}

void CUltraFileSplitterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FILEKM, mCombo);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, mEditOut);
	DDX_Control(pDX, IDC_EDIT_INPUT, mEditIn);
	DDX_Control(pDX, IDC_EDIT_SPL, mEditFileLen);
	DDX_Control(pDX, IDC_PROGRESS_SPL, mProgress);
}

BEGIN_MESSAGE_MAP(CUltraFileSplitterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CUltraFileSplitterDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CUltraFileSplitterDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_SPLITTER, &CUltraFileSplitterDlg::OnBnClickedButtonSplitter)
END_MESSAGE_MAP()


// CUltraFileSplitterDlg 消息处理程序

BOOL CUltraFileSplitterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	mCombo.SetCurSel(0);
	mProgress.SetRange(0, 100);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUltraFileSplitterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUltraFileSplitterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUltraFileSplitterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUltraFileSplitterDlg::OnBnClickedButton2()
{
	CFolderPickerDialog dlg;
	if (IDOK == dlg.DoModal())
	{
		pathOut=dlg.GetPathName();
		CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_OUTPUT);
		LPTSTR p = pathOut.GetBuffer();
		edit->SetWindowText(p);
	}

}


void CUltraFileSplitterDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE);
	if (IDOK == dlg.DoModal())
	{
		pathIn = dlg.GetPathName();
		LPTSTR p = pathIn.GetBuffer();
		CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_INPUT);
		edit->SetWindowText(p);
		fileName = dlg.GetFileName();
		
	}
}


void CUltraFileSplitterDlg::OnBnClickedButtonSplitter()
{
	//分割前判断输入准确性
	if (pathIn.GetLength()<=0)
	{
		MessageBox(TEXT("请输入文件！"), TEXT("WARNING"));
		return;
	}
	if (pathOut.GetLength() <= 0)
	{
		MessageBox(TEXT("请输入正确的路径！"), TEXT("WARNING"));
		return;
	}
	TCHAR tc[10];
	if (GetDlgItem(IDC_EDIT_SPL)->GetWindowText(tc, 10)<=0)
	{
		MessageBox(TEXT("请指定待分割的文件大小!"), TEXT("WARNING"));
		return;
	}
	CString pathFile = this->pathIn;
	pathFile.Replace('\\', '/');
	CFile file;
	//打开成功
	if (file.Open(pathFile, CFile::modeRead))
	{
		//获取文件大小
		ULONGLONG len = file.GetLength();  //字节数
		//将字节数转换到KB
		ULONGLONG numKb = len / 1024;
		INT otherbyte = len % 1024;
		if (otherbyte >= 512)
		{
			numKb++;
		}
		//刷新到界面
		CString strLength;
		strLength.Format(_T("%d%s"), numKb,TEXT("KB"));
		GetDlgItem(IDC_FILE_LENGTH)->SetWindowText(strLength);
		
		//获取待分割大小
		TCHAR ch[10];
		INT radNum=GetDlgItem(IDC_EDIT_SPL)->GetWindowText(ch, 10);
		int index=mCombo.GetCurSel();  
		INT Length = _tstoi(ch);  //KB
		if (index == 1)  //if danwei is MB
		{
			Length = Length * 1024;  // convert to kb
		}
		if (Length > len)
		{
			MessageBox(TEXT("文件长度不足以分割"));
			return;
		}
		//计算要分割出的文件数 and updata to gui
		ULONGLONG numFile = len / (Length * 1024);
		++numFile;
		TCHAR statbuf[50];
		GetDlgItem(IDC_STATIC_SPLITTER)->GetWindowText(statbuf, 50);
		CString statStr;
		statStr.Format(_T("%s%d"), statbuf, numFile);
		GetDlgItem(IDC_STATIC_SPLITTER)->SetWindowText(statStr);
		//读文件并分割
		int i = 0;
		ULONGLONG j = numFile; //control progressbar 
		CString outFileName = pathOut + "\\" + this->fileName;
		
		while (numFile)
		{
			//写入一个文件
			CFile outFile;
			int toInsert=outFileName.Find(TEXT("."), 0);
			TCHAR *c = new TCHAR[10];
			inToChar(i, c);
			outFileName.Insert(toInsert, c);
			delete []c;
			outFile.Open(outFileName, CFile::modeCreate | CFile::modeWrite);
			//开始读
			char buf[1024];  
			UINT hasRead = 0;
			while (hasRead != Length)
			{
				UINT hRead=file.Read(buf, 1024);
				if (hRead < 1024)
				{
					outFile.Write(buf, hRead);
					break;
				}
				//写入
				outFile.Write(buf, 1024);
				hasRead += hRead / 1024; //KB
			}
				
			outFile.Close();
			numFile--;
			i++;
			mProgress.SetPos(((float)i / j) * 100);
			outFileName = pathOut + "\\" + this->fileName;
		}
		
	}
	
	file.Close();
	MessageBox(_T("SPLITTER COMPLETY SUCCESSFULLY!"), _T("CONGRATULATION"));
}


void CUltraFileSplitterDlg::inToChar(int in,TCHAR*ch)
{
	_itow(in, ch,10);
}



