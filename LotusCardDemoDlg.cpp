// LotusCardDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LotusCardDemo.h"
#include "LotusCardDemoDlg.h"
#include ".\lotuscarddemodlg.h"
//#include "atlimage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CLotusCardDemoDlg * m_pLotusCardDemoDlg = NULL;
 BOOL __stdcall OnLotusCardIdCallBack(unsigned char * pCommandBuffer, int nCommandLength, unsigned char * pResultBuffer, int nResultLength)
{
	if(NULL != m_pLotusCardDemoDlg)
	{
		m_pLotusCardDemoDlg->SetIdCommandIndex();
	}
	return TRUE;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CLotusCardDemoDlg 对话框



CLotusCardDemoDlg::CLotusCardDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLotusCardDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pLotusCardDemoDlg = this;
}

void CLotusCardDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstLog);
	DDX_Control(pDX, IDC_WifiIpAdrress, m_edtWifiIpAdrress);
	DDX_Control(pDX, IDC_Image, m_Image);
	DDX_Control(pDX, IDC_IdCommandIndex, m_IdCommandIndex);
}

BEGIN_MESSAGE_MAP(CLotusCardDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_ClearLog, OnBnClickedClearlog)
	ON_BN_CLICKED(IDC_TestEasyApi, OnBnClickedTesteasyapi)
	ON_BN_CLICKED(IDC_GetCardNoEx, OnBnClickedGetcardnoex)
	ON_BN_CLICKED(IDC_TestConnect, OnBnClickedTestconnect)
	ON_BN_CLICKED(IDC_GetBankCardNo, OnBnClickedGetbankcardno)
	ON_BN_CLICKED(IDC_GetTwoGenerationIDCardNo, OnBnClickedGettwogenerationidcardno)
	ON_BN_CLICKED(IDC_GetTwoGenerationIDInfo, OnBnClickedGettwogenerationidinfo)
	ON_BN_CLICKED(IDC_GetTwoGenerationIDInfoByServer, OnBnClickedGettwogenerationidinfobyserver)
	ON_BN_CLICKED(IDC_NtagGetVersion, OnBnClickedNtaggetversion)
	ON_BN_CLICKED(IDC_LockNtag21x, OnBnClickedLockntag21x)
	ON_BN_CLICKED(IDC_UnlockNtag21x, OnBnClickedUnlockntag21x)
	ON_BN_CLICKED(IDC_7816Test, OnBnClicked7816test)
END_MESSAGE_MAP()


// CLotusCardDemoDlg 消息处理程序

BOOL CLotusCardDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_edtWifiIpAdrress.SetWindowText(_T("192.168.6.6"));
	m_ucWriteIndex = 0;
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CLotusCardDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLotusCardDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CLotusCardDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLotusCardDemoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
	int  hLotusCard = LotusCardOpenDevice("",0,0,0,0,NULL);

	if(-1 != hLotusCard)
	{
		TestIcCard(hLotusCard);
		
		LotusCardCloseDevice(hLotusCard);
	}
}
void CLotusCardDemoDlg::TestIcCard(int hLotusCard)
{
	CString strLog = _T("");
	LotusCardParamStruct sttLotusCardParam;
	BOOL bResult = FALSE;
	bResult = LotusCardBeep(hLotusCard, 10);
	unsigned int nCardNo = 0;
	CString strData = _T("");
	CString strTmp = _T("");
	unsigned int unCyc = 0;
	if(FALSE == bResult) return;
	int nRequestType = RT_NOT_HALT;

      //获取卡号 同执行LotusCardRequest/LotusCardAnticoll/LotusCardSelect三个函数
      memset(&sttLotusCardParam, 0x00, sizeof(sttLotusCardParam));
      bResult = LotusCardGetCardNo(hLotusCard,nRequestType, &sttLotusCardParam);
      if(FALSE == bResult) 
	  {
          strLog.Format(_T("LotusCardGetCardNo Exec Failure"));
          AddLog(strLog);
		  return;
	  }
	  memcpy(&nCardNo, sttLotusCardParam.arrCardNo, 4);
	  strLog.Format(_T("CardNo 0x%.8x"), nCardNo);
	  AddLog(strLog);
      //装载密码A
      memset(&sttLotusCardParam.arrKeys, 0x00, sizeof(sttLotusCardParam.arrKeys));
      sttLotusCardParam.arrKeys[0]=0xff;
      sttLotusCardParam.arrKeys[1]=0xff;
      sttLotusCardParam.arrKeys[2]=0xff;
      sttLotusCardParam.arrKeys[3]=0xff;
      sttLotusCardParam.arrKeys[4]=0xff;
      sttLotusCardParam.arrKeys[5]=0xff;
	  sttLotusCardParam.nKeysSize = 6;
      bResult =LotusCardLoadKey(hLotusCard, AM_A, 0, &sttLotusCardParam); 
      if(FALSE == bResult) 
	  {
          strLog.Format(_T("LotusCardLoadKey  Exec Failure"));
          AddLog(strLog);
		  return;
	  }
      strLog.Format(_T("LotusCardLoadKey  Exec Success"));
      AddLog(strLog);

      //验证密码
      bResult =LotusCardAuthentication(hLotusCard, AM_A, 0, &sttLotusCardParam);
      if(FALSE == bResult) 
	  {
          strLog.Format(_T("LotusCardAuthentication Exec Failure"));
          AddLog(strLog);
		  return;
	  }
      strLog.Format(_T("LotusCardAuthentication Exec Success"));
      AddLog(strLog);

      
      //读
      bResult=LotusCardRead(hLotusCard, 2, &sttLotusCardParam);
      if(FALSE == bResult) 
	  {
          strLog.Format(_T("LotusCardRead Exec Failure"));
          AddLog(strLog);
		  return;
	  }
	  strData = _T("");
	  for(unCyc = 0; unCyc < 16; unCyc++)
	  {
		  strTmp.Format(_T("%.2x "), sttLotusCardParam.arrBuffer[unCyc]);
		  strData += strTmp;
	  }
      strLog.Format(_T("LotusCardRead Exec Success"));
	  strLog.Format(strData);
      AddLog(strLog);


      //写
      memset(&sttLotusCardParam.arrBuffer, 0x00, sizeof(sttLotusCardParam.arrBuffer));
      sttLotusCardParam.arrBuffer[0] = 0x00;
      sttLotusCardParam.arrBuffer[1] = 0x01;
      sttLotusCardParam.arrBuffer[2] = 0x02;
      sttLotusCardParam.arrBuffer[3] = 0x03;
      sttLotusCardParam.arrBuffer[4] = 0x04;
      sttLotusCardParam.arrBuffer[5] = 0x05;
      sttLotusCardParam.arrBuffer[6] = 0x06;
      sttLotusCardParam.arrBuffer[7] = 0x07;
      sttLotusCardParam.arrBuffer[8] = 0x08;
      sttLotusCardParam.arrBuffer[9] = 0x09;
      sttLotusCardParam.arrBuffer[10] = 0x0a;
      sttLotusCardParam.arrBuffer[11] = 0x0b;
      sttLotusCardParam.arrBuffer[12] = 0x0c;
      sttLotusCardParam.arrBuffer[13] = 0x0d;
      sttLotusCardParam.arrBuffer[14] = 0x0e;
      sttLotusCardParam.arrBuffer[15] = 0x0f;
      sttLotusCardParam.nBufferSize=16;
      bResult=LotusCardWrite(hLotusCard, 2, &sttLotusCardParam);
      if(FALSE == bResult) 
	  {
          strLog.Format(_T("LotusCardWrite  Exec Failure"));
          AddLog(strLog);
		  return;
	  }
      strLog.Format(_T("LotusCardWrite Exec Success"));
      AddLog(strLog);

      bResult = LotusCardInitValue(hLotusCard, 1, 10);
	  if(FALSE == bResult) return;
      strLog.Format(_T("LotusCardInitValue Exec Success！"));      
	  AddLog(strLog);

      //减值
      bResult=LotusCardDecrement(hLotusCard, 1, 1);
      if(FALSE == bResult) return;
      strLog.Format(_T("LotusCardDecrement Exec Success ！"));
	  AddLog(strLog);
      //中止
      bResult=LotusCardHalt(hLotusCard);
	  if(FALSE == bResult) return;
	  strLog.Format(_T("LotusCardHalt Exec Success！"));
	  AddLog(strLog);
}
void CLotusCardDemoDlg::AddLog(CString strLog)
{
	CString strTmp = _T("");
	CTime time = CTime::GetCurrentTime();
	SYSTEMTIME st;
	GetLocalTime(&st);
	//strTmp.Format(_T("%s:%s"), time.Format("%m-%d %H:%M:%S") ,strLog);
	strTmp.Format(_T("%s:%s"), time.Format("%m-%d %H:%M:%S") ,strLog);
	strTmp.Format("%2d:%2d:%2d:%3d%s",st.wHour,st.wMinute,st.wSecond,st.wMilliseconds ,strLog) ;
	m_lstLog.InsertString(m_lstLog.GetCount(), strTmp);
}
void CLotusCardDemoDlg::OnBnClickedClearlog()
{
	// TODO: 在此添加控件通知处理程序代码
	m_lstLog.ResetContent();
#if 0
	int  hLotusCard = LotusCardOpenDevice("",0,0,0,0,NULL);


	char szBuffer[2048] = "V0xmAH4AMgAA/4UeUVFRPnEN1WTwrlEGHDgYtYnzydX63kPUv6WvkPsDqBhAKRFAIuoflSJM6oO0vYNtulgJeQx3gKKLsqgR2iXnAtAPhiZxY21wP3e3LZOY+d5RrtVSUVFaPoTg8zNDc71lEMLkxj43rRdDLVVI5yLknXN58qt7Ky6soALwnju7FUKqAVob4upr69PV9AIoyp45bB6ZoBsruqRMbFguuBSXJdPTgCsj/nQ4RBZ2NJz1qX//NYj0ZIuphdDfUsGNlQDNFNc5/ui/g8aV8c48frQ04NJbmPv879vy6bfcfPRzAr66uSfK6MvLe+jbtf9er0GX95RW3yF57aIqXRNi0F16fxbMqeuTcFgk8oJXibsVZGTh1CrHebQ0UN83oBUYYp04snqrjze3F8alVffY+/OHo1KdBL1RufsFQetxzIIEE/r/YsjY3KHeMzFAdQD3bGQikABCcYnFcbJ61hwbWa/fPT2rJ7uFHAA4lGsuuNAFdf5ar+01bvNyzAlBjbhUtpr0IoWlmoyXZQrslQjVdX9HfR+TiqXvVIJh0yiFoR/4vdxuQzsvEhnQtJ+3tMUKE1KAvOZlPPJNA+PUMeTuizqgisyuUSrE3CMvtj91/9YboNCWdzLcJaLHYuehCR1Kn38m/25YHNhBe0GOX65RrlG+0mEoK0yofTNhMBDeIkKiPOTD8Nwbg4ZN8QFRQMkWMCZJxJ8/JxN6wcAYmXG7Q+0xSGQQnj7FK0xKZhmfZTJZvAItvcauUQjve+yKFmlbZDD3Gr78FAWEv/Nr7HDagJZtMDDyTs/H4W6Wc1HmR+N1+ghSw5Jaxz+FsNcCbz/Zy0M2Lp80RZ34jWpxOMsDl1ZNTWgBB4fDQSwkIt1y35V+Q/8IIidSkoSSYKfeYbr9OndOKobha6lKbBXXq4MYCvBD6HEHSbWoFa2RdJcbJSdbqUw6KS494LzgyZS3iB8zgtJ6im6/AxMpV8GKAupzqUcjMEl5rKazjSdxDtqTElcWuZo0McdC/RF3L9xI8YuK4qHOtwedR6v6T5c5C7Q3kDPIUKEdXHKT8jVjjcTD98pWzT76SMbldykwu7JsMPEa5QZhEDxEcXGBFktIYKxFts4HTEJkml5L/AIbNqRKEdWMHRJJoOTAOmdx4xJaPgskymYqDwuLrlHqb5P8B2L5SXB8QDIUzaHanX44IcV/RnLXfoKz3ybSq03PK0kcPSDapKceKE/PDV4Y59wElDfZktw1TcW3Uih1Xr/AAaFaPoS/F16kynNU/z61NvqDnbz4PEWh5mDntpA3DMqLkDi70Cer6cr3iqWK5EIfiZtvpun0mD/TD8+m39836dvwJrxt4+Hal5j+EQ==";
	char szTmp[2048] = {0};
	int nResult = 0;
	//
	if(-1 != hLotusCard)
	{
		LotusCardBase64Decode( hLotusCard, (unsigned char *)szBuffer, strlen(szBuffer), (unsigned char *)szTmp, sizeof(szTmp));
		nResult = LotusCardGetDecodeNewLen( hLotusCard, (const char *)szBuffer, strlen(szBuffer));
		CFile fJpeg;
		fJpeg.Open("C:\\1.jpg",CFile::modeCreate | CFile::modeWrite);
		fJpeg.Write(szTmp,nResult);
		fJpeg.Close();
		LotusCardCloseDevice(hLotusCard);
	}
#endif //0
}

void CLotusCardDemoDlg::OnBnClickedTesteasyapi()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strWifiIpAddress;
	CString strTmp;
	int  hLotusCard = -1;
	CString strLog;
	m_edtWifiIpAdrress.GetWindowText(strWifiIpAddress);

	hLotusCard = LotusCardOpenDevice(strWifiIpAddress.GetBuffer(),0,0,0,0,NULL);

	if(-1 != hLotusCard)
	{
		TestEasyApi(hLotusCard);
		
		LotusCardCloseDevice(hLotusCard);
	}
}
void CLotusCardDemoDlg::TestEasyApi(int hLotusCard)
{
	LotusCardParamStruct sttLotusCardParam;
	int nRequestType;
	BOOL bResult = FALSE;
	DWORD nCardNo;
	CString strLog;
	int nCyc;
	int nErrorCode;
	CString strErrorInfo;
	CString strTmp;

	if(-1 == hLotusCard) return;
    nRequestType = RT_NOT_HALT;
	memset(&sttLotusCardParam, 0x00, sizeof(sttLotusCardParam));
	sttLotusCardParam.arrKeys[0] = 0xff;
	sttLotusCardParam.arrKeys[1] = 0xff;
	sttLotusCardParam.arrKeys[2] = 0xff;
	sttLotusCardParam.arrKeys[3] = 0xff;
	sttLotusCardParam.arrKeys[4] = 0xff;
	sttLotusCardParam.arrKeys[5] = 0xff;
	//bResult:= LotusCardReadData(hLotusCard, nRequestType, 5, 1,10,1, &sttLotusCardParam);
    //bResult = LotusCardReadData(hLotusCard, nRequestType, 5, 1,10,0, &sttLotusCardParam);
	bResult = LotusCardReadData(hLotusCard, nRequestType, 5, 1,0,0, &sttLotusCardParam);
	if(FALSE == bResult)
	{
		AddLog(_T("调用 LotusCardReadData 失败!"));
		return;
	}
	AddLog(_T("调用 LotusCardReadData 成功!"));
	memcpy(&nCardNo, sttLotusCardParam.arrCardNo, 4);
	strTmp.Format(_T("卡号：%8X"), nCardNo);
	AddLog(strTmp);
	strTmp.Format(_T("卡号：%u"), nCardNo);
	AddLog(strTmp);
	strLog = _T("读取块5数据：");

	for (nCyc = 0;  nCyc < 15; nCyc++)
	{
		strTmp.Format(_T("%.2X "), sttLotusCardParam.arrBuffer[nCyc]);
		strLog += strTmp;
	}
	AddLog(strLog);
	Sleep(200);
	m_ucWriteIndex++;
    sttLotusCardParam.arrBuffer[0] = m_ucWriteIndex;
    sttLotusCardParam.arrBuffer[1] = 0x01;
    sttLotusCardParam.arrBuffer[2] = 0x02;
    sttLotusCardParam.arrBuffer[3] = 0x03;
    sttLotusCardParam.arrBuffer[4] = 0x04;
    sttLotusCardParam.arrBuffer[5] = 0x05;
    sttLotusCardParam.arrBuffer[6] = 0x06;
    sttLotusCardParam.arrBuffer[7] = 0x07;
    sttLotusCardParam.arrBuffer[8] = 0x08;
    sttLotusCardParam.arrBuffer[9] = 0x09;
    sttLotusCardParam.arrBuffer[10] = 0x0a;
    sttLotusCardParam.arrBuffer[11] = 0x0b;
    sttLotusCardParam.arrBuffer[12] = 0x0c;
    sttLotusCardParam.arrBuffer[13] = 0x0d;
    sttLotusCardParam.arrBuffer[14] = 0x0e;
    sttLotusCardParam.arrBuffer[15] = 0x0f;
    sttLotusCardParam.nBufferSize=16;     
////     bResult = LotusCardWriteData(hLotusCard, 5,10,0,&sttLotusCardParam);
	bResult = LotusCardWriteData(hLotusCard, 5,10,0, &sttLotusCardParam);
	if(FALSE == bResult)
	{
		AddLog(_T("调用LotusCardWriteData失败!"));
		return;
	}
	else
	{
		AddLog(_T("调用LotusCardWriteData成功!"));
	}
        


}

void CLotusCardDemoDlg::OnBnClickedGetcardnoex()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strWifiIpAddress;
	CString strTmp;
	int  hLotusCard = -1;
	CString strLog;
	m_edtWifiIpAdrress.GetWindowText(strWifiIpAddress);

	hLotusCard = LotusCardOpenDevice(strWifiIpAddress.GetBuffer(),0,0,0,0,NULL);

	if(-1 != hLotusCard)
	{
		TestGetCardNoEx(hLotusCard);
		
		LotusCardCloseDevice(hLotusCard);
	}
}

void CLotusCardDemoDlg::OnBnClickedTestconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strWifiIpAddress;
	CString strTmp;
	int  hLotusCard = -1;
	CString strLog;
	m_edtWifiIpAdrress.GetWindowText(strWifiIpAddress);
	if(LotusCardConnectTest(strWifiIpAddress.GetBuffer(),200000))
	{
		strLog.Format(_T("连接IP %s 成功"),strWifiIpAddress);
		AddLog(strLog);
	}
	else
	{
		strLog.Format(_T("连接IP %s 失败"),strWifiIpAddress);
		AddLog(strLog);
		return;
	}
}
void CLotusCardDemoDlg::TestGetCardNoEx(int hLotusCard)
{

	LotusCardParamStruct sttLotusCardParam;
	int nRequestType;
	BOOL bResult = FALSE;
	DWORD nCardNo;
	CString strLog;
	int nCyc;
	int nErrorCode;
	CString strErrorInfo;
	CString strTmp;

	if(-1 == hLotusCard) return;
    nRequestType = RT_NOT_HALT;
	memset(&sttLotusCardParam, 0x00, sizeof(sttLotusCardParam));
	sttLotusCardParam.arrKeys[0] = 0xff;
	sttLotusCardParam.arrKeys[1] = 0xff;
	sttLotusCardParam.arrKeys[2] = 0xff;
	sttLotusCardParam.arrKeys[3] = 0xff;
	sttLotusCardParam.arrKeys[4] = 0xff;
	sttLotusCardParam.arrKeys[5] = 0xff;
	bResult = LotusCardGetCardNoEx(hLotusCard, nRequestType,10,0,0, &sttLotusCardParam);
	if(FALSE == bResult)
	{
		AddLog(_T("调用 LotusCardGetCardNoEx 失败!"));
		return;
	}
	AddLog(_T("调用 LotusCardGetCardNoEx 成功!"));
	memcpy(&nCardNo, sttLotusCardParam.arrCardNo, 4);
	strTmp.Format(_T("卡号：%8X"), nCardNo);
	AddLog(strTmp);
	strTmp.Format(_T("卡号：%u"), nCardNo);
	AddLog(strTmp);

}
void CLotusCardDemoDlg::OnBnClickedGetbankcardno()
{
	// TODO: 在此添加控件通知处理程序代码
	int  hLotusCard = LotusCardOpenDevice("",0,0,0,0,NULL);

	if(-1 != hLotusCard)
	{
		TestGetBankCardNo(hLotusCard);
		
		LotusCardCloseDevice(hLotusCard);
	}
}

void CLotusCardDemoDlg::TestGetBankCardNo(int hLotusCard)
{
	CString strLog = _T("");
	LotusCardParamStruct sttLotusCardParam;
	BOOL bResult = FALSE;
	bResult = LotusCardBeep(hLotusCard, 10);
	unsigned int nCardNo = 0;
	CString strData = _T("");
	CString strTmp = _T("");
	unsigned int unCyc = 0;
	char szATS[256] = {0};
	char szBankCardNo[32] = {0};
	if(FALSE == bResult) return;
	bResult = LotusCardBeep(hLotusCard,10);
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardBeep 执行失败"));
		AddLog(strLog);
		return;
	}

	//获取卡号 同执行LotusCardRequest/LotusCardAnticoll/LotusCardSelect三个函数
	memset(&sttLotusCardParam, 0x00, sizeof(sttLotusCardParam));
	bResult = LotusCardResetCpuCard(hLotusCard,&sttLotusCardParam);
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardResetCpuCard 执行失败"));
		AddLog(strLog);
		return;
	}

	for(int i = 0; i < sttLotusCardParam.nBufferSize; i++)
	{
		sprintf(szATS + (i*2), "%02x", sttLotusCardParam.arrBuffer[(i)]);
	}
	strLog.Format(_T("ATS:%s"), szATS);
	AddLog(strLog);
	bResult = LotusCardGetBankCardNo(hLotusCard,szBankCardNo, sizeof(szBankCardNo));
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardGetBankCardNo 执行失败"));
		AddLog(strLog);
		return;
	}

	strLog.Format(_T("CARDNO:%s"), szBankCardNo);
	AddLog(strLog);

}
void CLotusCardDemoDlg::OnBnClickedGettwogenerationidcardno()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strWifiIpAddress;
	m_edtWifiIpAdrress.GetWindowText(strWifiIpAddress);
	int  hLotusCard = LotusCardOpenDevice(strWifiIpAddress.GetBuffer(),0,0,0,0,NULL);

	if(-1 != hLotusCard)
	{
		TestGetTwoGenerationIdCardNo(hLotusCard);
		
		LotusCardCloseDevice(hLotusCard);
	}
}
void CLotusCardDemoDlg::TestGetTwoGenerationIdCardNo(int hLotusCard)
{
	CString strLog = _T("");
	LotusCardParamStruct sttLotusCardParam;
	BOOL bResult = FALSE;
	bResult = LotusCardBeep(hLotusCard, 10);
	unsigned int nCardNo = 0;
	CString strData = _T("");
	CString strTmp = _T("");
	unsigned int unCyc = 0;
	char szTwoGenerationIdCardNo[64] = {0};
	if(FALSE == bResult) return;
	bResult = LotusCardBeep(hLotusCard,10);
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardBeep 执行失败"));
		AddLog(strLog);
		return;
	}

	bResult = LotusCardSetCardType(hLotusCard, 'B');
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardSetCardType 执行失败"));
		AddLog(strLog);
		return;
	}
	bResult = LotusCardGetTwoGenerationIDCardNo(hLotusCard,szTwoGenerationIdCardNo,sizeof(szTwoGenerationIdCardNo));
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardGetTwoGenerationIDCardNo 执行失败"));
		AddLog(strLog);
		return;
	}
	strLog.Format(_T("CARDNO:%s"), szTwoGenerationIdCardNo);
	AddLog(strLog);
}

void CLotusCardDemoDlg::TestGetTwoGenerationIdInfo(int hLotusCard)
{
	CString strLog = _T("");
	LotusCardParamStruct sttLotusCardParam;
	BOOL bResult = FALSE;
	bResult = LotusCardBeep(hLotusCard, 10);
	unsigned int nCardNo = 0;
	CString strData = _T("");
	CString strTmp = _T("");
	unsigned int unCyc = 0;
	char szTwoGenerationIdCardNo[64] = {0};
	WCHAR wstrTmp[35] = {0};
	TwoIdInfoStruct sttTwoIdInfo;
	memset(&sttTwoIdInfo, 0x00, sizeof(TwoIdInfoStruct));
	if(FALSE == bResult) return;
	bResult = LotusCardBeep(hLotusCard,10);
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardBeep 执行失败"));
		AddLog(strLog);
		return;
	}

	bResult = LotusCardSetCardType(hLotusCard, 'B');
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardSetCardType 执行失败"));
		AddLog(strLog);
		return;
	}
	bResult = LotusCardGetTwoGenerationIDCardNo(hLotusCard,szTwoGenerationIdCardNo,sizeof(szTwoGenerationIdCardNo));
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardGetTwoGenerationIDCardNo 执行失败"));
		AddLog(strLog);
		return;
	}
	strLog.Format(_T("CARDNO:%s"), szTwoGenerationIdCardNo);
	AddLog(strLog);
	//bResult = LotusCardGetTwoIdInfo(hLotusCard,&sttTwoIdInfo);
	bResult = LotusCardGetTwoIdInfoByServerEx(hLotusCard, "219.153.15.85", 10000, &sttTwoIdInfo, 15);
	if(FALSE == bResult) 
	{
		//strLog.Format(_T("LotusCardGetTwoIdInfo 执行失败"));
		strLog.Format(_T("　LotusCardGetTwoIdInfoByServerEx 执行失败"));
		AddLog(strLog);
		strLog.Format(_T("　无法连接到 SAMV 安全模块服务器（IP地址:%s）"), "219.153.15.85");
		AddLog(strLog);
		return;
	}
	USES_CONVERSION;
	memset(&wstrTmp, 0x00, sizeof(wstrTmp));
	memcpy(&wstrTmp, &sttTwoIdInfo.arrTwoIdName, sizeof(sttTwoIdInfo.arrTwoIdName));
	strLog.Format(_T("　姓名: %s"),  W2A(wstrTmp));
	AddLog(strLog);

	{
		WCHAR wstrSN[sizeof(sttTwoIdInfo.arrTwoIdNo)] = { 0 };
		WCHAR wstrSex[sizeof(sttTwoIdInfo.arrTwoIdSex)] = { 0 };
		WCHAR wstrNationCode[sizeof(sttTwoIdInfo.arrTwoIdNation)] = { 0 };
		WCHAR wstrAddress[sizeof(sttTwoIdInfo.arrTwoIdAddress)] = { 0 };
		WCHAR wstrCA[sizeof(sttTwoIdInfo.arrTwoIdSignedDepartment)] = { 0 };
		WCHAR wstrValidityFromDate[sizeof(sttTwoIdInfo.arrTwoIdValidityPeriodBegin)] = { 0 };
		WCHAR wstrValidityExpiryDate[sizeof(sttTwoIdInfo.arrTwoIdValidityPeriodEnd)] = { 0 };

		memcpy(&wstrSN, &sttTwoIdInfo.arrTwoIdNo, sizeof(sttTwoIdInfo.arrTwoIdNo));
		memcpy(&wstrSex, &sttTwoIdInfo.arrTwoIdSex, sizeof(sttTwoIdInfo.arrTwoIdSex));
		memcpy(&wstrNationCode, &sttTwoIdInfo.arrTwoIdNation, sizeof(sttTwoIdInfo.arrTwoIdNation));
		memcpy(&wstrAddress, &sttTwoIdInfo.arrTwoIdAddress, sizeof(sttTwoIdInfo.arrTwoIdAddress));
		memcpy(&wstrCA, &sttTwoIdInfo.arrTwoIdSignedDepartment, sizeof(sttTwoIdInfo.arrTwoIdSignedDepartment));
		memcpy(&wstrValidityFromDate, &sttTwoIdInfo.arrTwoIdValidityPeriodBegin, sizeof(sttTwoIdInfo.arrTwoIdValidityPeriodBegin));
		memcpy(&wstrValidityExpiryDate, &sttTwoIdInfo.arrTwoIdValidityPeriodEnd, sizeof(sttTwoIdInfo.arrTwoIdValidityPeriodEnd));

		strLog.Format(_T("　身份证号：%s"), W2A(wstrSN));
		AddLog(strLog);
		strLog.Format(_T("　性别代码：%s（备注：男=1，女=2）"), W2A(wstrSex));
		AddLog(strLog);
		strLog.Format(_T("　民族代码：%s（备注：汉族=01）"), W2A(wstrNationCode));
		AddLog(strLog);
		strLog.Format(_T("　住址：%s"), W2A(wstrAddress));
		AddLog(strLog);
		strLog.Format(_T("　签发机关：%s"), W2A(wstrCA));
		AddLog(strLog);
		strLog.Format(_T("　有效期限：%s - %s"), W2A(wstrValidityFromDate), W2A(wstrValidityExpiryDate));
		AddLog(strLog);
	}

	if (sttTwoIdInfo.unTwoIdPhotoJpegLength == 0)
	{
		bResult = LotusCardWlDecodeByServer(hLotusCard, "wl1.highwillow.cn", &sttTwoIdInfo);
		if (FALSE == bResult)
		{
			strLog.Format(_T("LotusCardWlDecodeByServer 执行失败"));
			AddLog(strLog);
			return;
		}

		strLog.Format(_T("LotusCardWlDecodeByServer 执行成功"));
		AddLog(strLog);
	}
	if (sttTwoIdInfo.unTwoIdPhotoJpegLength > 0)
	{
		//fJpeg.Open("C:\\1.jpg",CFile::modeCreate | CFile::modeWrite);
		//fJpeg.Write(sttTwoIdInfo.arrTwoIdPhotoJpeg,sttTwoIdInfo.unTwoIdPhotoJpegLength);
		//fJpeg.Close();
		CoInitialize(NULL);
		HGLOBAL hImageMemory = GlobalAlloc(GMEM_MOVEABLE, sttTwoIdInfo.unTwoIdPhotoJpegLength);
		IStream* pIStream;//创建一个IStream接口指针，用来保存图片流
		IPicture* pIPicture;//创建一个IPicture接口指针，表示图片对象
		CreateStreamOnHGlobal(hImageMemory, false, &pIStream); //用全局内存初使化IStream接口指针

		void* pImageMemory = GlobalLock(hImageMemory); //锁定内存
		memcpy(pImageMemory, sttTwoIdInfo.arrTwoIdPhotoJpeg, sttTwoIdInfo.unTwoIdPhotoJpegLength);
		GlobalUnlock(hImageMemory); //解锁内存

		OleLoadPicture(pIStream, 0, false, IID_IPicture, (LPVOID*)&(pIPicture));//用OleLoadPicture获得IPicture接口指针
		//得到IPicture COM接口对象后，你就可以进行获得图片信息、显示图片等操作
		OLE_XSIZE_HIMETRIC hmWidth;
		OLE_YSIZE_HIMETRIC hmHeight;
		pIPicture->get_Width(&hmWidth);//用接口方法获得图片的宽和高
		pIPicture->get_Height(&hmHeight);

		pIPicture->Render(m_Image.GetWindowDC()->GetSafeHdc(), 0, 0, 80, 80, 0, hmHeight, hmWidth, -hmHeight, NULL);//在指定的DC上绘出图片

		GlobalFree(hImageMemory); //释放全局内存
		pIStream->Release(); //释放pIStream
		pIPicture->Release(); //释放pIPicture
	}
}
void CLotusCardDemoDlg::OnBnClickedGettwogenerationidinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strWifiIpAddress;
	m_edtWifiIpAdrress.GetWindowText(strWifiIpAddress);
	int  hLotusCard = LotusCardOpenDevice(strWifiIpAddress.GetBuffer(), 0, 0, 0, 0, NULL);

	if(-1 != hLotusCard)
	{
		TestGetTwoGenerationIdInfo(hLotusCard);
		
		LotusCardCloseDevice(hLotusCard);
	}
}

void CLotusCardDemoDlg::OnBnClickedGettwogenerationidinfobyserver()
{
	//// TODO: 在此添加控件通知处理程序代码
	//int  hLotusCard = LotusCardOpenDevice("",0,0,0,0,NULL);

	//if(-1 != hLotusCard)
	//{
	//	m_unIdCommandIndex = 0;
	//	LotusCardSetIdCallBack(hLotusCard,&OnLotusCardIdCallBack);
	//	TestGetTwoGenerationIdInfoByServer(hLotusCard);
	//	
	//	LotusCardCloseDevice(hLotusCard);
	//}
}


void CLotusCardDemoDlg::TestGetTwoGenerationIdInfoByServer(long hLotusCard)
{
//	CImage img;
//	CFile fJpeg;
//	CString strLog = _T("");
//	LotusCardParamStruct sttLotusCardParam;
//	BOOL bResult = FALSE;
//	bResult = LotusCardBeep(hLotusCard, 10);
//	unsigned int nCardNo = 0;
//	CString strData = _T("");
//	CString strTmp = _T("");
//	unsigned int unCyc = 0;
//	char szTwoGenerationIdCardNo[64] = {0};
//	WCHAR wstrTmp[256] = {0};
//	char szErrorInfo[256] = {0};
//	TwoIdInfoStruct sttTwoIdInfo;
//	int nErrorCode = 0;
//	memset(&sttTwoIdInfo, 0x00, sizeof(TwoIdInfoStruct));
//	if(FALSE == bResult) return;
//	bResult = LotusCardBeep(hLotusCard,10);
//	if(FALSE == bResult) 
//	{
//		strLog.Format(_T("LotusCardBeep 执行失败"));
//		AddLog(strLog);
//		return;
//	}
//
//	bResult = LotusCardSetCardType(hLotusCard, 'B');
//	if(FALSE == bResult) 
//	{
//		strLog.Format(_T("LotusCardSetCardType 执行失败"));
//		AddLog(strLog);
//		return;
//	}
//	bResult = LotusCardGetTwoGenerationIDCardNo(hLotusCard,szTwoGenerationIdCardNo,sizeof(szTwoGenerationIdCardNo));
//	if(FALSE == bResult) 
//	{
//		strLog.Format(_T("LotusCardGetTwoGenerationIDCardNo 执行失败"));
//		AddLog(strLog);
//		return;
//	}
//	strLog.Format(_T("CARDNO:%s"), szTwoGenerationIdCardNo);
//	AddLog(strLog);
////	bResult = LotusCardGetTwoIdInfoByServer(hLotusCard,"218.16.96.117",&sttTwoIdInfo);
//	//bResult = LotusCardGetTwoIdInfoByMcuServer(hLotusCard,"samv.highwillow.cn",99999,"123456",&sttTwoIdInfo,400000,0,2);
//	bResult = LotusCardGetTwoIdInfoByPsamServer(hLotusCard,"219.153.15.85",10000,&sttTwoIdInfo,2);
//	if(FALSE == bResult) 
//	{
//		nErrorCode = LotusCardGetTwoIdErrorCode(hLotusCard);
//		LotusCardGetTwoIdErrorInfo(hLotusCard, (TwoIdErrorCode)nErrorCode,szErrorInfo, sizeof(szErrorInfo));
//		strLog.Format(_T("LotusCardGetTwoIdInfoByMcuServer 执行失败, 错误码 %d "), nErrorCode);
//		AddLog(strLog);
//		strLog.Format(_T("          错误描述 %s"),szErrorInfo);
//		AddLog(strLog);
//		if(TIEC_GET_SAMV_IP_PORT==nErrorCode)
//		{
//			LotusCardGetTwoIdDispatchServerErrorInfo(hLotusCard, szErrorInfo,sizeof(szErrorInfo));
//			strLog.Format(_T("          调度错误描述 %s"),szErrorInfo);
//			AddLog(strLog);
//		}
//
//		return;
//	}
//	USES_CONVERSION;
//	memset(&wstrTmp, 0x00, sizeof(wstrTmp));
//	memcpy(&wstrTmp, &sttTwoIdInfo.arrTwoIdName, sizeof(sttTwoIdInfo.arrTwoIdName));
//	strLog.Format(_T("姓名 %s"),  W2A(wstrTmp));
//	AddLog(strLog);
//	memset(&wstrTmp, 0x00, sizeof(wstrTmp));
//	memcpy(&wstrTmp, &sttTwoIdInfo.arrTwoIdAddress, sizeof(sttTwoIdInfo.arrTwoIdAddress));
//	strLog.Format(_T("地址 %s"),  W2A(wstrTmp));
//	AddLog(strLog);
//	memset(&wstrTmp, 0x00, sizeof(wstrTmp));
//	memcpy(&wstrTmp, &sttTwoIdInfo.arrTwoIdBirthday, sizeof(sttTwoIdInfo.arrTwoIdBirthday));
//	strLog.Format(_T("生日 %s"),  W2A(wstrTmp));
//	AddLog(strLog);
//	memset(&wstrTmp, 0x00, sizeof(wstrTmp));
//	memcpy(&wstrTmp, &sttTwoIdInfo.arrTwoIdNo, sizeof(sttTwoIdInfo.arrTwoIdNo));
//	strLog.Format(_T("号码 %s"),  W2A(wstrTmp));
//	AddLog(strLog);
//
//	memset(&wstrTmp, 0x00, sizeof(wstrTmp));
//	memcpy(&wstrTmp, &sttTwoIdInfo.arrTwoIdSignedDepartment, sizeof(sttTwoIdInfo.arrTwoIdSignedDepartment));
//	strLog.Format(_T("签发机关 %s"),  W2A(wstrTmp));
//	AddLog(strLog);
//
//	memset(&wstrTmp, 0x00, sizeof(wstrTmp));
//	memcpy(&wstrTmp, &sttTwoIdInfo.arrTwoIdValidityPeriodBegin, sizeof(sttTwoIdInfo.arrTwoIdValidityPeriodBegin));
//	strLog.Format(_T("有效期开始 %s"),  W2A(wstrTmp));
//	AddLog(strLog);
//
//	memset(&wstrTmp, 0x00, sizeof(wstrTmp));
//	memcpy(&wstrTmp, &sttTwoIdInfo.arrTwoIdValidityPeriodEnd, sizeof(sttTwoIdInfo.arrTwoIdValidityPeriodEnd));
//	strLog.Format(_T("有效期结束 %s"),  W2A(wstrTmp));
//	AddLog(strLog);
//
//	memset(&wstrTmp, 0x00, sizeof(wstrTmp));
//	memcpy(&wstrTmp, &sttTwoIdInfo.arrTwoIdSex, sizeof(sttTwoIdInfo.arrTwoIdSex));
//	strLog.Format(_T("%s"),  W2A(wstrTmp));
//	if(_T("1") == strLog)
//	{
//		strLog.Format(_T("性别 男"));
//	}
//	else if(_T("2") == strLog)
//	{
//		strLog.Format(_T("性别 男"));
//	}
//	else {
//		strLog.Format(_T("性别 未知"));
//	}
//	AddLog(strLog);
//
//
//	memset(&wstrTmp, 0x00, sizeof(wstrTmp));
//	memcpy(&wstrTmp, &sttTwoIdInfo.arrTwoIdNation, sizeof(sttTwoIdInfo.arrTwoIdNation));
//	strLog.Format(_T("%s"),  W2A(wstrTmp));
//	if(_T("01") == strLog)
//	{
//		strLog.Format(_T("民族 汉"));
//	}
//	else if(_T("02") == strLog)
//	{
//		strLog.Format(_T("民族 蒙古"));
//	}
//	else {
//		strLog.Format(_T("民族 未知"));
//	}
//	AddLog(strLog);
	//if( sttTwoIdInfo.unTwoIdPhotoJpegLength==0)
	//{
	//	bResult = LotusCardWlDecodeByServer(hLotusCard,"wl1.highwillow.cn",&sttTwoIdInfo);
	//	if(FALSE == bResult) 
	//	{
	//		strLog.Format(_T("LotusCardWlDecodeByServer 执行失败"));
	//		AddLog(strLog);
	//		return;
	//	}

	//	strLog.Format(_T("LotusCardWlDecodeByServer 执行成功"));
	//	AddLog(strLog);
	//}
	//if( sttTwoIdInfo.unTwoIdPhotoJpegLength>0)
	//{
	//	//fJpeg.Open("C:\\1.jpg",CFile::modeCreate | CFile::modeWrite);
	//	//fJpeg.Write(sttTwoIdInfo.arrTwoIdPhotoJpeg,sttTwoIdInfo.unTwoIdPhotoJpegLength);
	//	//fJpeg.Close();
	//	CoInitialize(NULL);
	//	HGLOBAL hImageMemory=GlobalAlloc(GMEM_MOVEABLE, sttTwoIdInfo.unTwoIdPhotoJpegLength);
	//	IStream *pIStream;//创建一个IStream接口指针，用来保存图片流
 //       IPicture *pIPicture;//创建一个IPicture接口指针，表示图片对象
 //       CreateStreamOnHGlobal(hImageMemory, false,&pIStream); //用全局内存初使化IStream接口指针

	//	void *pImageMemory=GlobalLock(hImageMemory); //锁定内存
	//	memcpy(pImageMemory, sttTwoIdInfo.arrTwoIdPhotoJpeg,sttTwoIdInfo.unTwoIdPhotoJpegLength);
 //       GlobalUnlock(hImageMemory); //解锁内存

 //       OleLoadPicture(pIStream, 0, false, IID_IPicture,(LPVOID*)&(pIPicture));//用OleLoadPicture获得IPicture接口指针
 //       //得到IPicture COM接口对象后，你就可以进行获得图片信息、显示图片等操作
 //       OLE_XSIZE_HIMETRIC hmWidth;
 //       OLE_YSIZE_HIMETRIC hmHeight;
 //       pIPicture->get_Width(&hmWidth);//用接口方法获得图片的宽和高
 //       pIPicture->get_Height(&hmHeight);
	//	
	//	pIPicture->Render(m_Image.GetWindowDC()->GetSafeHdc(),0,0,80,80,0,hmHeight,hmWidth,-hmHeight,NULL);//在指定的DC上绘出图片

	//	GlobalFree(hImageMemory); //释放全局内存
 //       pIStream->Release(); //释放pIStream
 //       pIPicture->Release(); //释放pIPicture
	//}
}
void CLotusCardDemoDlg::OnBnClickedNtaggetversion()
{
	// TODO: 在此添加控件通知处理程序代码
	int  hLotusCard = LotusCardOpenDevice("",0,0,0,0,NULL);

	if(-1 != hLotusCard)
	{
		NtagGetVersion(hLotusCard);
		
		LotusCardCloseDevice(hLotusCard);
	}
}

void CLotusCardDemoDlg::NtagGetVersion(int hLotusCard)
{
	unsigned char arrVersion[8];
	int nPwdPageIndex = 43;
	int nAuth0PageIndex = 41;

	CString strLog = _T("");
	LotusCardParamStruct sttLotusCardParam;
	BOOL bResult = FALSE;
	bResult = LotusCardBeep(hLotusCard, 10);
	unsigned int nCardNo = 0;
	CString strData = _T("");
	CString strTmp = _T("");
	unsigned int unCyc = 0;
	if(FALSE == bResult) return;
	int nRequestType = RT_NOT_HALT;
    //寻卡
    memset(&sttLotusCardParam, 0x00, sizeof(sttLotusCardParam));
    bResult = LotusCardRequest(hLotusCard,nRequestType, &sttLotusCardParam);
    if(FALSE == bResult) 
	{
        strLog.Format(_T("LotusCardRequest 执行失败"));
        AddLog(strLog);
		return;
	}
	strLog.Format(_T("卡型：nCardType 0x%.8x"), sttLotusCardParam.nCardType);
	AddLog(strLog);
	//防冲撞
	bResult = LotusCardAnticoll(hLotusCard,&sttLotusCardParam);
    if(FALSE == bResult) 
	{
        strLog.Format(_T("LotusCardAnticoll 执行失败"));
        AddLog(strLog);
		return;
	}
	strLog.Format(_T("卡号nCardNo %.2x%.2x%.2x%.2x%.2x%.2x%.2x"), 
		sttLotusCardParam.arrCardNo[0],
		sttLotusCardParam.arrCardNo[1],
		sttLotusCardParam.arrCardNo[2],
		sttLotusCardParam.arrCardNo[3],
		sttLotusCardParam.arrCardNo[4],
		sttLotusCardParam.arrCardNo[5],
		sttLotusCardParam.arrCardNo[6]);
	AddLog(strLog);

	//获取版本信息
	bResult = LotusCardNtagGetVersion(hLotusCard,arrVersion, sizeof(arrVersion));
    if(FALSE == bResult) 
	{
        strLog.Format(_T("LotusCardNtagGetVersion 执行失败"));
        AddLog(strLog);
		return;
	}
	switch( arrVersion[6])
	{
		case 0x0f:
			strLog.Format(_T("卡片型号：NTAG213"));
			nPwdPageIndex = 43;
			nAuth0PageIndex = 41;
			break;
		case 0x11:
			strLog.Format(_T("卡片型号：NTAG215"));
			nPwdPageIndex = 133;
			nAuth0PageIndex = 131;
			break;
		case 0x13:
			strLog.Format(_T("卡片型号：NTAG216"));
			nPwdPageIndex = 229;
			nAuth0PageIndex = 227;
			break;
		default:
			strLog.Format(_T("卡片型号：未知"));
			AddLog(strLog);
			return;

	}
	AddLog(strLog);
}
void CLotusCardDemoDlg::OnBnClickedLockntag21x()
{
	// TODO: 在此添加控件通知处理程序代码
	int  hLotusCard = LotusCardOpenDevice("",0,0,0,0,NULL);

	if(-1 != hLotusCard)
	{
		LockNtag21x(hLotusCard);
		
		LotusCardCloseDevice(hLotusCard);
	}
}
void CLotusCardDemoDlg::LockNtag21x(int hLotusCard)
{
	unsigned char arrVersion[8];
	int nPwdPageIndex = 43;
	int nAuth0PageIndex = 41;

	CString strLog = _T("");
	LotusCardParamStruct sttLotusCardParam;
	BOOL bResult = FALSE;
	bResult = LotusCardBeep(hLotusCard, 10);
	unsigned int nCardNo = 0;
	CString strData = _T("");
	CString strTmp = _T("");
	unsigned int unCyc = 0;
	if(FALSE == bResult) return;
	int nRequestType = RT_NOT_HALT;
    //寻卡
    memset(&sttLotusCardParam, 0x00, sizeof(sttLotusCardParam));
    bResult = LotusCardRequest(hLotusCard,nRequestType, &sttLotusCardParam);
    if(FALSE == bResult) 
	{
        strLog.Format(_T("LotusCardRequest 执行失败"));
        AddLog(strLog);
		return;
	}
	strLog.Format(_T("卡型：nCardType 0x%.8x"), sttLotusCardParam.nCardType);
	AddLog(strLog);
	//防冲撞
	bResult = LotusCardAnticoll(hLotusCard,&sttLotusCardParam);
    if(FALSE == bResult) 
	{
        strLog.Format(_T("LotusCardAnticoll 执行失败"));
        AddLog(strLog);
		return;
	}
	strLog.Format(_T("卡号nCardNo %.2x%.2x%.2x%.2x%.2x%.2x%.2x"), 
		sttLotusCardParam.arrCardNo[0],
		sttLotusCardParam.arrCardNo[1],
		sttLotusCardParam.arrCardNo[2],
		sttLotusCardParam.arrCardNo[3],
		sttLotusCardParam.arrCardNo[4],
		sttLotusCardParam.arrCardNo[5],
		sttLotusCardParam.arrCardNo[6]);
	AddLog(strLog);

	//获取版本信息
	bResult = LotusCardNtagGetVersion(hLotusCard,arrVersion, sizeof(arrVersion));
    if(FALSE == bResult) 
	{
        strLog.Format(_T("LotusCardNtagGetVersion 执行失败"));
        AddLog(strLog);
		return;
	}
	switch( arrVersion[6])
	{
		case 0x0f:
			strLog.Format(_T("卡片型号：NTAG213"));
			nPwdPageIndex = 43;
			nAuth0PageIndex = 41;
			break;
		case 0x11:
			strLog.Format(_T("卡片型号：NTAG215"));
			nPwdPageIndex = 133;
			nAuth0PageIndex = 131;
			break;
		case 0x13:
			strLog.Format(_T("卡片型号：NTAG216"));
			nPwdPageIndex = 229;
			nAuth0PageIndex = 227;
			break;
		default:
			strLog.Format(_T("卡片型号：未知"));
			AddLog(strLog);
			return;

	}
	AddLog(strLog);
	//设置密码
	sttLotusCardParam.arrBuffer[0] = 0x31;
	sttLotusCardParam.arrBuffer[1] = 0x32;
	sttLotusCardParam.arrBuffer[2] = 0x33;
	sttLotusCardParam.arrBuffer[3] = 0x34;
	sttLotusCardParam.nBufferSize=16;
    //每次写入4字节
	bResult = LotusCardWrite(hLotusCard,nPwdPageIndex, &sttLotusCardParam);
    if(FALSE == bResult) 
	{
        strLog.Format(_T("调用 LotusCardWrite 写入PAGE %d 失败!"), nPwdPageIndex);
        AddLog(strLog);
		return;
	}
    strLog.Format(_T("调用 LotusCardWrite 写入PAGE %d 成功!"), nPwdPageIndex);
    AddLog(strLog);

	//设置加密生效位
	sttLotusCardParam.arrBuffer[0] = 0x04;
	sttLotusCardParam.arrBuffer[1] = 0x00;
	sttLotusCardParam.arrBuffer[2] = 0x00;
	sttLotusCardParam.arrBuffer[3] = 0x04;
	sttLotusCardParam.nBufferSize =16;
    //每次写入4字节
	bResult = LotusCardWrite(hLotusCard,nAuth0PageIndex, &sttLotusCardParam);
    if(FALSE == bResult) 
	{
        strLog.Format(_T("调用 LotusCardWrite 写入PAGE %d 失败!"), nAuth0PageIndex);
        AddLog(strLog);
		return;
	}
    strLog.Format(_T("调用 LotusCardWrite 写入PAGE %d 成功!"), nAuth0PageIndex);
    AddLog(strLog);

}

void CLotusCardDemoDlg::OnBnClickedUnlockntag21x()
{
	// TODO: 在此添加控件通知处理程序代码
	int  hLotusCard = LotusCardOpenDevice("",0,0,0,0,NULL);

	if(-1 != hLotusCard)
	{
		UnLockNtag21x(hLotusCard);
		
		LotusCardCloseDevice(hLotusCard);
	}
}

void CLotusCardDemoDlg::UnLockNtag21x(int hLotusCard)
{
	unsigned char arrVersion[8];
	int nPwdPageIndex = 43;
	int nAuth0PageIndex = 41;

	CString strLog = _T("");
	LotusCardParamStruct sttLotusCardParam;
	BOOL bResult = FALSE;
	bResult = LotusCardBeep(hLotusCard, 10);
	unsigned int nCardNo = 0;
	CString strData = _T("");
	CString strTmp = _T("");
	unsigned int unCyc = 0;
	if(FALSE == bResult) return;
	int nRequestType = RT_NOT_HALT;
    //寻卡
    memset(&sttLotusCardParam, 0x00, sizeof(sttLotusCardParam));
    bResult = LotusCardRequest(hLotusCard,nRequestType, &sttLotusCardParam);
    if(FALSE == bResult) 
	{
        strLog.Format(_T("LotusCardRequest 执行失败"));
        AddLog(strLog);
		return;
	}
	strLog.Format(_T("卡型：nCardType 0x%.8x"), sttLotusCardParam.nCardType);
	AddLog(strLog);
	//防冲撞
	bResult = LotusCardAnticoll(hLotusCard,&sttLotusCardParam);
    if(FALSE == bResult) 
	{
        strLog.Format(_T("LotusCardAnticoll 执行失败"));
        AddLog(strLog);
		return;
	}
	strLog.Format(_T("卡号nCardNo %.2x%.2x%.2x%.2x%.2x%.2x%.2x"), 
		sttLotusCardParam.arrCardNo[0],
		sttLotusCardParam.arrCardNo[1],
		sttLotusCardParam.arrCardNo[2],
		sttLotusCardParam.arrCardNo[3],
		sttLotusCardParam.arrCardNo[4],
		sttLotusCardParam.arrCardNo[5],
		sttLotusCardParam.arrCardNo[6]);
	AddLog(strLog);

	//获取版本信息
	bResult = LotusCardNtagGetVersion(hLotusCard,arrVersion, sizeof(arrVersion));
    if(FALSE == bResult) 
	{
        strLog.Format(_T("LotusCardNtagGetVersion 执行失败"));
        AddLog(strLog);
		return;
	}
	switch( arrVersion[6])
	{
		case 0x0f:
			strLog.Format(_T("卡片型号：NTAG213"));
			nPwdPageIndex = 43;
			nAuth0PageIndex = 41;
			break;
		case 0x11:
			strLog.Format(_T("卡片型号：NTAG215"));
			nPwdPageIndex = 133;
			nAuth0PageIndex = 131;
			break;
		case 0x13:
			strLog.Format(_T("卡片型号：NTAG216"));
			nPwdPageIndex = 229;
			nAuth0PageIndex = 227;
			break;
		default:
			strLog.Format(_T("卡片型号：未知"));
			AddLog(strLog);
			return;

	}
	AddLog(strLog);
	//设置密码
	sttLotusCardParam.arrBuffer[0] = 0x31;
	sttLotusCardParam.arrBuffer[1] = 0x32;
	sttLotusCardParam.arrBuffer[2] = 0x33;
	sttLotusCardParam.arrBuffer[3] = 0x34;
	sttLotusCardParam.nBufferSize=16;
    //验证密码
	bResult = LotusCardNtagPwdAuth(hLotusCard,sttLotusCardParam.arrBuffer, 4);
    if(FALSE == bResult) 
	{
        strLog.Format(_T("调用 LotusCardNtagPwdAuth PAGE %d 失败!"), nPwdPageIndex);
        AddLog(strLog);
		return;
	}
    strLog.Format(_T("调用 LotusCardNtagPwdAuth PAGE %d 成功!"), nPwdPageIndex);
    AddLog(strLog);

	//设置加密生效位失效
	sttLotusCardParam.arrBuffer[0] = 0x04;
	sttLotusCardParam.arrBuffer[1] = 0x00;
	sttLotusCardParam.arrBuffer[2] = 0x00;
	sttLotusCardParam.arrBuffer[3] = 0xff;
	sttLotusCardParam.nBufferSize =16;
    //每次写入4字节
	bResult = LotusCardWrite(hLotusCard,nAuth0PageIndex, &sttLotusCardParam);
    if(FALSE == bResult) 
	{
        strLog.Format(_T("调用 LotusCardWrite 写入PAGE %d 失败!"), nAuth0PageIndex);
        AddLog(strLog);
		return;
	}
    strLog.Format(_T("调用 LotusCardWrite 写入PAGE %d 成功!"), nAuth0PageIndex);
    AddLog(strLog);

}
void CLotusCardDemoDlg::SetIdCommandIndex()
{
	CString strTmp = _T("");
	m_unIdCommandIndex++;
	strTmp.Format(_T("指令索引：%d"), m_unIdCommandIndex);
	m_IdCommandIndex.SetWindowText(strTmp);

}

void CLotusCardDemoDlg::SetButton2English(void)
{

}

void CLotusCardDemoDlg::OnBnClicked7816test()
{
	// TODO: 在此添加控件通知处理程序代码
	int  hLotusCard = LotusCardOpenDevice("",0,0,0,0,NULL);

	if(-1 != hLotusCard)
	{
		Test7816(hLotusCard);
		
		LotusCardCloseDevice(hLotusCard);
	}
}


void CLotusCardDemoDlg::Test7816(int hLotusCard)
{
	CString strLog = _T("");
	LotusCardParamStruct sttLotusCardParam;
	BOOL bResult = FALSE;
	unsigned int nCardNo = 0;
	CString strData = _T("");
	CString strTmp = _T("");
	unsigned int unCyc = 0;
	char szATS[256] = {0};
	char szBankCardNo[32] = {0};

	bResult = LotusCardBeep(hLotusCard,10);
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardBeep 执行失败"));
		AddLog(strLog);
		return;
	}
	
	//选择卡座
    bResult = LotusCardSetSamSlotIndex(hLotusCard, 0);//0是外置卡座 1 2是内置卡座 3是扩展外置卡座
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardSetSamSlotIndex 执行失败"));
		AddLog(strLog);
		return;
	}
	strLog.Format(_T("LotusCardSetSamSlotIndex 执行成功"));
	AddLog(strLog);

	//设置电压
	// 3.3V Sel0 = 1 Sel1 = 0，
	// 1.8V Sel0 = 1 Sel1 = 1，
	//   5V Sel0 = 0 Sel1 = 1，
    bResult = LotusCardSetSamVSel0(hLotusCard, 0, 1);
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardSetSamVSel0 执行失败"));
		AddLog(strLog);
		return;
	}
	strLog.Format(_T("LotusCardSetSamVSel0 执行成功"));
	AddLog(strLog);

    bResult = LotusCardSetSamVSel1(hLotusCard, 0, 0);
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardSetSamVSel1 执行失败"));
		AddLog(strLog);
		return;
	}
	strLog.Format(_T("LotusCardSetSamVSel1 执行成功"));
	AddLog(strLog);
    AddLog(_T("调用电压设置成功!"));

    bResult = LotusCardSetSamPowerOnOff(hLotusCard, 0);
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardSetSamPowerOnOff 下电 执行失败"));
		AddLog(strLog);
		return;
	}
	strLog.Format(_T("LotusCardSetSamPowerOnOff 下电 执行成功"));
	AddLog(strLog);
	Sleep(20);      
	bResult = LotusCardSetSamPowerOnOff(hLotusCard, 1);
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardSetSamPowerOnOff 上电 执行失败"));
		AddLog(strLog);
		return;
	}
	strLog.Format(_T("LotusCardSetSamPowerOnOff 上电 执行成功"));
	AddLog(strLog);

    bResult = LotusCardResetSam(hLotusCard, &sttLotusCardParam);
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardResetSam 执行失败"));
		AddLog(strLog);
		return;
	}
	strLog.Format(_T("LotusCardResetSam 执行成功"));
	AddLog(strLog);


	for(int i = 0; i < sttLotusCardParam.nBufferSize; i++)
	{
		sprintf(szATS + (i*2), "%02x", sttLotusCardParam.arrBuffer[(i)]);
	}
	strLog.Format(_T("ATS:%s"), szATS);
	AddLog(strLog);

	//执行取随机数动作 0084000004
    sttLotusCardParam.arrCosSendBuffer[0] = 0x00;
	sttLotusCardParam.arrCosSendBuffer[1] = 0x84;
	sttLotusCardParam.arrCosSendBuffer[2] = 0x00;
	sttLotusCardParam.arrCosSendBuffer[3] = 0x00;
	sttLotusCardParam.arrCosSendBuffer[4] = 0x04;
    sttLotusCardParam.unCosSendBufferLength = 5;
    sttLotusCardParam.nBufferSize = 0;

    bResult = LotusCardSendSamAPDU(hLotusCard, &sttLotusCardParam);
	if(FALSE == bResult) 
	{
		strLog.Format(_T("LotusCardSendSamAPDU 执行失败"));
		AddLog(strLog);
		return;
	}
	strLog.Format(_T("LotusCardSendSamAPDU 执行成功"));
	AddLog(strLog);

	for(int i = 0; i < sttLotusCardParam.unCosReultBufferLength; i++)
	{
		sprintf(szATS + (i*2), "%02x", sttLotusCardParam.arrCosResultBuffer[(i)]);
	}
	strLog.Format(_T("随机数:%s"), szATS);
	AddLog(strLog);

}
