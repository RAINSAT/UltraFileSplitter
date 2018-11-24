
// UltraFileSplitterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UltraFileSplitter.h"
#include "UltraFileSplitterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CUltraFileSplitterDlg �Ի���



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


// CUltraFileSplitterDlg ��Ϣ�������

BOOL CUltraFileSplitterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	mCombo.SetCurSel(0);
	mProgress.SetRange(0, 100);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUltraFileSplitterDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	//�ָ�ǰ�ж�����׼ȷ��
	if (pathIn.GetLength()<=0)
	{
		MessageBox(TEXT("�������ļ���"), TEXT("WARNING"));
		return;
	}
	if (pathOut.GetLength() <= 0)
	{
		MessageBox(TEXT("��������ȷ��·����"), TEXT("WARNING"));
		return;
	}
	TCHAR tc[10];
	if (GetDlgItem(IDC_EDIT_SPL)->GetWindowText(tc, 10)<=0)
	{
		MessageBox(TEXT("��ָ�����ָ���ļ���С!"), TEXT("WARNING"));
		return;
	}
	CString pathFile = this->pathIn;
	pathFile.Replace('\\', '/');
	CFile file;
	//�򿪳ɹ�
	if (file.Open(pathFile, CFile::modeRead))
	{
		//��ȡ�ļ���С
		ULONGLONG len = file.GetLength();  //�ֽ���
		//���ֽ���ת����KB
		ULONGLONG numKb = len / 1024;
		INT otherbyte = len % 1024;
		if (otherbyte >= 512)
		{
			numKb++;
		}
		//ˢ�µ�����
		CString strLength;
		strLength.Format(_T("%d%s"), numKb,TEXT("KB"));
		GetDlgItem(IDC_FILE_LENGTH)->SetWindowText(strLength);
		
		//��ȡ���ָ��С
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
			MessageBox(TEXT("�ļ����Ȳ����Էָ�"));
			return;
		}
		//����Ҫ�ָ�����ļ��� and updata to gui
		ULONGLONG numFile = len / (Length * 1024);
		++numFile;
		TCHAR statbuf[50];
		GetDlgItem(IDC_STATIC_SPLITTER)->GetWindowText(statbuf, 50);
		CString statStr;
		statStr.Format(_T("%s%d"), statbuf, numFile);
		GetDlgItem(IDC_STATIC_SPLITTER)->SetWindowText(statStr);
		//���ļ����ָ�
		int i = 0;
		ULONGLONG j = numFile; //control progressbar 
		CString outFileName = pathOut + "\\" + this->fileName;
		
		while (numFile)
		{
			//д��һ���ļ�
			CFile outFile;
			int toInsert=outFileName.Find(TEXT("."), 0);
			TCHAR *c = new TCHAR[10];
			inToChar(i, c);
			outFileName.Insert(toInsert, c);
			delete []c;
			outFile.Open(outFileName, CFile::modeCreate | CFile::modeWrite);
			//��ʼ��
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
				//д��
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



