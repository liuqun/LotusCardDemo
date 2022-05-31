# 头文件
[LotusCardDriver.h](./LotusCardDriver.h)
```
/**
 * 通过网络获取二代证信息
 * @param nDeviceHandle 设备句柄
 * @param pszServerIp 参数 安全模块所在服务器IP
 * @param unServerPort 参数 服务器端口
 * @param pTwoIdInfo 参数 二代证信息结构体地址
 * @param unRecvTimeOut 参数 接收超时 默认10秒
 * @return true = 成功
 */
BOOL WINAPI LotusCardGetTwoIdInfoByServerEx(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort, TwoIdInfoStruct * pTwoIdInfo, unsigned int unRecvTimeOut);
```

# 主程序例子
[LotusCardDemoDlg.cpp](./LotusCardDemoDlg.cpp)
```
#include <stdlib.h>
#include <string.h>

#include "LotusCardDriver.h"
#pragma comment(lib, "LotusCardDriver.lib")

// ……
WCHAR wstrTmp[35] = {0};
BOOL bResult=FALSE;
TwoIdInfoStruct sttTwoIdInfo;
memset(&sttTwoIdInfo, 0x00, sizeof(TwoIdInfoStruct));

/* @param nDeviceHandle 设备句柄
 * @param pszServerIp 安全模块所在服务器IP字符串
 * @param unServerPort 服务器端口, 无符号整数0-65535
 * @param pTwoIdInfo 二代证信息结构体地址
 * @param unRecvTimeOut 响应超时秒数
 */
bResult = LotusCardGetTwoIdInfoByServerEx(hLotusCard, "219.153.15.85", 10000, &sttTwoIdInfo, 15);
if(FALSE == bResult) 
{
		//strLog.Format(_T("　LotusCardGetTwoIdInfoByServerEx 执行失败"));
		//AddLog(strLog);
		//strLog.Format(_T("　无法连接到 SAMV 安全模块服务器（IP地址:%s）"), "219.153.15.85");
		//AddLog(strLog);
		return;
}

	USES_CONVERSION;
	memset(&wstrTmp, 0x00, sizeof(wstrTmp));
	memcpy(&wstrTmp, &sttTwoIdInfo.arrTwoIdName, sizeof(sttTwoIdInfo.arrTwoIdName));
	//strLog.Format(_T("　姓名: %s"),  W2A(wstrTmp));
	//AddLog(strLog);

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
```
