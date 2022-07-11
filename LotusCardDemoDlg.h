// LotusCardDemoDlg.h : 头文件
//

#pragma once

#include "LotusCardDriver.h"
#include "afxwin.h"
#include "afxcmn.h"
// CLotusCardDemoDlg 对话框
class CLotusCardDemoDlg : public CDialog
{
// 构造
public:
	CLotusCardDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LOTUSCARDDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	void TestIcCard(int hLotusCard);
	void TestGetBankCardNo(int hLotusCard);
	void Test7816(int hLotusCard);
public:
	CListBox m_lstLog;
private:
	void AddLog(CString strLog);
	void TestEasyApi(int hLotusCard);
	void TestGetCardNoEx(int hLotusCard);
	void TestGetTwoGenerationIdCardNo(int hLotusCard);
	void TestGetTwoGenerationIdInfo(int hLotusCard);
	void TestGetTwoGenerationIdInfoByServer(long hLotusCard);
	void NtagGetVersion(int hLotusCard);
	void LockNtag21x(int hLotusCard);
	void UnLockNtag21x(int hLotusCard);
	void SetButton2English(void);
private:
	unsigned char m_ucWriteIndex;
	unsigned int m_unIdCommandIndex;
public:
	afx_msg void OnBnClickedClearlog();
	afx_msg void OnBnClickedTesteasyapi();
	CIPAddressCtrl m_edtWifiIpAdrress;
	afx_msg void OnBnClickedGetcardnoex();
	afx_msg void OnBnClickedTestconnect();
	afx_msg void OnBnClickedGetbankcardno();
	afx_msg void OnBnClickedGettwogenerationidcardno();
	afx_msg void OnBnClickedGettwogenerationidinfo();
	afx_msg void OnBnClickedGettwogenerationidinfobyserver();
	CStatic m_Image;
	afx_msg void OnBnClickedNtaggetversion();
	afx_msg void OnBnClickedLockntag21x();
	afx_msg void OnBnClickedUnlockntag21x();
	void SetIdCommandIndex();
	CStatic m_IdCommandIndex;
	afx_msg void OnBnClicked7816test();
};
