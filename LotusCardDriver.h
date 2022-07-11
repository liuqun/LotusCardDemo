#ifndef __LOTUS_CARD_DRIVER_H__
#define __LOTUS_CARD_DRIVER_H__

#if 1 //作为VC demo调用头文件 把0改为1
		typedef int		 						BOOL;
		typedef unsigned char		 					byte;
		//#undef FALSE
		//#undef TRUE
		//#undef NULL

		#define FALSE   0
		#define TRUE    1
		#define NULL    0
		#ifndef WINAPI
			#define WINAPI
		#endif //WINAPI

	#define		RT_NOT_HALT				0x26
	#define		RT_ALL					0x52

	#define		AM_A					0x60
	#define		AM_B					0x61
#define		COS_RESULT_BUFFER_LENGTH		256
#define		COS_SEND_BUFFER_LENGTH			256

//#define		FOR_WINDOWS10					//WINDOWS 10 用long long
#ifdef FOR_WINDOWS10
	typedef long long LotusHandle;				//针对句柄单独搞个类型 便于改动
#else
	typedef long LotusHandle;				//针对句柄单独搞个类型 便于改动
#endif

	//错误代码
	typedef enum _LotusCardErrorCode
	{
		LCEC_OK = 0,				//正常执行
		LCEC_UNKNOWN,				//未知的 
		LCEC_SEND_FALSE,			//发送失败
		LCEC_RECV_TIME_OUT,			//接收超时
		LCEC_RECV_ZERO_LEN,			//接收长度为0
		LCEC_RECV_CRC_FALSE,		//接收校验失败
		LCEC_REQUEST,				//寻卡
		LCEC_ANTICOLL,				//防冲突
		LCEC_SELECT,				//选卡
		LCEC_AUTHENTICATION,		//三次验证
		LCEC_HALT,					//中止
		LCEC_READ,					//读
		LCEC_WRITE,					//写
		LCEC_INCREMENT,				//加值
		LCEC_DECREMENT,				//减值
		LCEC_LOADKEY,				//装载密码
		LCEC_BEEP,					//蜂鸣
		LCEC_RESTORE,				//卡数据块传入卡的内部寄存器
		LCEC_TRANSFER,				//内部寄存器传入卡的卡数据块
		LCEC_SEND_COMMAND,			//发送14443指令
		LCEC_WIFI_SCANAP_BEGIN,		//发送扫描动作开始信号
		LCEC_WIFI_SCANAP_COUNT,		//获取扫描AP计数
		LCEC_WIFI_SCANAP_RESULT,	//获取扫描结果
		LCEC_WIFI_GET_STAINFO,	//获取STA信息
		LCEC_WIFI_SET_STAINFO,	//设置STA信息
		LCEC_WIFI_GET_MODE,		//获取模式
		LCEC_WIFI_SET_MODE,		//设置模式
		LCEC_WIFI_RESET,			//复位WIFI模块
		LCEC_FELICA_POLLING,		//FELICA寻卡动作
		LCEC_REQUESTB,				//typeb寻卡错误
		LCEC_SELECTB,				//typeb选卡
		LCEC_HALTB,					//typeb中止
		LCEC_M100_INVENTORY_FAIL,	//轮询操作失败。没有标签返回或者返回数据CRC 校验错误。
	}LotusCardErrorCode;


	//二代证错误编码
	typedef enum _TwoIdErrorCode
	{
		TIEC_NO_ERROR = 0,					//正常执行 没有错误
		TIEC_IPADDRESS,						//错误IP地址 格式错误
		TIEC_REQUESTB,						//寻卡错误
		TIEC_SELECTB,						//选卡错误
		TIEC_GET_NO,						//获取卡号错误 执行卡ID COS指令失败
		TIEC_GET_NO_RESULT,					//获取卡号错误结果 没有返回9000
		TIEC_GET_NO_OTHER,					//获取卡号其他错误
		TIEC_GET_RANDOM,					//取随机数错误
		TIEC_GET_RANDOM_RESULT,				//取随机数错误结果 没有返回9000
		TIEC_SELECT_FIRST_FILE,				//选第一个文件错误
		TIEC_SELECT_FIRST_FILE_RESULT,		//选第一个文件错误结果 没有返回9000
		TIEC_READ_FIRST_FILE,				//读第一个文件错误
		TIEC_READ_FIRST_FILE_RESULT,		//选第一个文件错误结果 没有返回9000
		TIEC_RECEIVE_INTERNAL_AUTHENTICATE,	//接收内部认证 TCP 动作
		TIEC_EXEC_INTERNAL_AUTHENTICATE,	//执行内部认证
		TIEC_SEND_INTERNAL_AUTHENTICATE,	//发送内部认证结果 TCP
		TIEC_EXEC_GET_RANDOM,				//获取随机数
		TIEC_SEND_RANDOM,					//发送随机数 TCP
		TIEC_RECEIVE_EXTERNAL_AUTHENTICATE,	//接收外部认证 TCP 动作
		TIEC_EXEC_EXTERNAL_AUTHENTICATE,	//执行外部认证
		TIEC_READ_SEND_SECOND_FILE,			//读取并发送第二个文件
		TIEC_READ_SEND_THIRD_FILE,			//读取并发送第三个文件
		TIEC_READ_SEND_FOURTH_FILE,			//读取并发送第四个文件
		TIEC_RECEIVE_LAST_DATA,				//接收最后的数据
		TIEC_CONNECT_SERVER,				//连接服务器失败
		TIEC_SAMV_BUSY,						//服务器端SAMV 繁忙
		TIEC_READ_SEND_FIFTH_FILE,			//读取并发送第五个文件
		TIEC_DATA_EMPTY,					//数据为空
		TIEC_MCU_RESET_ERROR,				//MCU复位错误
		TIEC_SAMV_RESET_ERROR,				//SAMV复位错误
		TIEC_SAMV_MANAGER_MESSAGE,			//SAMV管理信息
		TIEC_GET_SAMV_IP_PORT,				//获取SAMV地址端口错误
		TIEC_GET_SAMV_LAST_ERROR,			//获取SAMV最后错误
		TIEC_CONNECT_WL_DECODER_SERVER,		//连接wl解码服务器失败
		TIEC_CONNECT_DISPATCH_SERVER,		//连接调度服务器失败
		TIEC_SEND_COS_FALSE,				//发送COS指令失败
		TIEC_ZERO_DATA,						//数据全部为0
		TIEC_COS_RESULT_ERROR,				//COS结果错误
		TIEC_SEND_NETWORK_ERROR,			//网络发送错误
		TIEC_RESET_PSAM,					//复位PSAM
		TIEC_QUERY_PSAM_STATUS,				//查询PSAM状态失败
		TIEC_GET_PSAM_MFKEY,				//获取MFKEY失败
		TIEC_PROCESS_PSAM_VERIFY_LOCK_DATA,	//处理校验加密数据失败
		TIEC_SEND_SAMV_DECODE_INFO,			//发送安全模块解码信息失败
		TIEC_SET_APP_CONFIG,				//设置APP配置
		TIEC_GET_APP_CONFIG,				//获取APP配置
		TIEC_CLEAR_APP_CONFIG,				//清除配置 恢复默认值
		TIEC_CHANGE_APP_CONFIG_PASSWORD,	//修改配置密码
		TIEC_POWER_ON_OFF,					//打开关闭电源
		TIEC_GET_ANDROID_PHONE_STATE,		//获取android手机状态信息出错
		TIEC_GET_ANDROID_PHONE_IMEI,		//获取android手机状态IMEI信息为空
		TIEC_GET_ANDROID_CONTEXT_NULL,		//获取android手机状态信息上下文对象为空
		TIEC_LED_ON_OFF,					//LED 开关错误
		TIEC_DOMAIN_NAME_ERROR,				//域名错误
		TIEC_SELECT_AID,						//二代证DN码
		TIEC_SELECT_AID_RESULT,				//二代证DN码结果错误
		TIEC_READ_BINARY,						//二代证DN码
		TIEC_READ_BINARY_RESULT,				//二代证DN码结果错误

		TIEC_UNKNOWN_ERROR = 1000,			//未知错误

	}TwoIdErrorCode;


	typedef BOOL (*LotusCardExtendReadWriteCallBack)(BOOL bRead, unsigned char * pReadWriteBuffer, int nBufferLength);
	typedef BOOL (*LotusCardExtendIdDeviceCallBack)(unsigned char * pReadWriteBuffer, int nBufferLength); //二代证外部设备用回调
	typedef void (*LotusCardWrite2FlashCallBack)(unsigned int unCurrentPos, unsigned int unFileLength);
	typedef BOOL (*LotusCardIdCallBack)(unsigned char * pCommandBuffer, int nCommandLength, unsigned char * pResultBuffer, int nResultLength);
	typedef struct _LotusCardParamStruct
	{
		/**
		* 卡片类型
		*/
		int nCardType;
		/**
		* 8字节卡号
		*/
		byte arrCardNo[8];
		
		/**
		* 卡片容量大小
		*/
		int nCardSize;
		
		/**
		* 读写缓冲
		*/
		byte arrBuffer[64];

		int nBufferSize;
		
		/**
		* 密钥
		*/
		byte arrKeys[64];
		int nKeysSize;
		/**
		* pCosResultBuffer COS执行结果缓冲
		*/
		byte arrCosResultBuffer[COS_RESULT_BUFFER_LENGTH];
		/**
		* unCosReultBufferLength COS执行结果缓冲长度 
		*/
		unsigned int unCosReultBufferLength;
	/**
	 * pCosSendBuffer COS指令发送缓冲
	 */
	byte arrCosSendBuffer[COS_SEND_BUFFER_LENGTH];
	/**
	 * unCosSendBufferLength COS指令发送缓冲长度 
	 */
	unsigned int unCosSendBufferLength;		
	}LotusCardParamStruct;


typedef struct _BssInfoStruct {
    unsigned char arrBssid[8];	//BSSID
    unsigned char arrSsid[32];	//SSID
    unsigned char ucChannel;	//通道
    signed char	scRssi;			//信号强度
    unsigned char ucAuthMode;	//认证模式
}BssInfoStruct;

typedef struct _StaInfoStruct {
    unsigned char arrSsid[16];				//SSID
	unsigned char arrPassword[16];			//Password 密码
	unsigned char arrStaIp[4];				//Sta IP 地址
	//unsigned char arrStaNetMaskIp[4];		//Sta 掩码 地址
	//unsigned char arrStaDnsIp[4];			//Sta DNS 地址

	//unsigned char arrApIp[4];				//Ap IP 地址
	//unsigned char arrApNetMaksIp[4];		//Ap 掩码 地址

	//unsigned char ucStaUseDhcp;			//Sta 使用DHCP获取 1=使用DHCP 0=不使用DHCP
}StaInfoStruct;

//二代证信息结构
typedef struct _TwoIdInfoStruct {
    char arrTwoIdName[30];					//姓名 UNICODE
	char arrTwoIdSex[2];					//性别 UNICODE
	char arrTwoIdNation[4];					//民族 UNICODE
	char arrTwoIdBirthday[16];				//出生日期 UNICODE YYYYMMDD
	char arrTwoIdAddress[70];				//住址 UNICODE
	char arrTwoIdNo[36];					//身份证号码 UNICODE
	char arrTwoIdSignedDepartment[30];		//签发机关 UNICODE
	char arrTwoIdValidityPeriodBegin[16];	//有效期起始日期 UNICODE YYYYMMDD
	char arrTwoIdValidityPeriodEnd[16];		//有效期截止日期 UNICODE YYYYMMDD 有效期为长期时存储“长期”

	char arrTwoIdNewAddress[70];			//最新住址 UNICODE
	char arrReserve[2];						//保留字节 字节对齐用
	unsigned char arrTwoIdPhoto[1024];		//照片信息
	unsigned char arrTwoIdFingerprint[1024];//指纹信息
	unsigned char arrTwoIdPhotoJpeg[4096];	//照片信息 JPEG 格式
	unsigned int  unTwoIdPhotoJpegLength;	//照片信息长度 JPEG格式


}TwoIdInfoStruct;
//错误信息
typedef struct _SamvErrorInfoStruct
{
	unsigned int sdtLastOperate;		//最后一次操作数据类型
	unsigned char arrCommandBuffer[16];		//最后一次执行指令缓冲
	unsigned char arrSamvUartResult[16];		//存放SAMV模块串口返回的数据 取前32字节
	unsigned char arrCardResultBuffer[96];	//卡片执行结果
	BOOL 	bExecCommandResult;			//指令执行结果
	unsigned int unLastTcpDataIndex;		//最后一次接收到的数据索引
	unsigned char u64PreSendTime[8];			//记录前一次向SAMV发送指令的时间 此处不使用__int64 主要是会导致按照8字节对齐 156 变成160
	unsigned char u64CurrentSendTime[8];		//记录当前向SAMV发送指令的时间
}SamvErrorInfoStruct;

//发送或接收时间来记录
typedef struct _SamvSendReceiveTimeStruct
{
	BOOL bIsSend;							//TRUE 表示MCU发送到SAMV 否则 表示MCU从SAMV接收
	unsigned int unTimeSpaceFromBegin;		//从指令开始的时间间隔
}SamvSendReceiveTimeStruct;



//中石化记录结构
typedef struct _SinopecRecordStruct
{
	unsigned char arrEtNo[2];//ET联机或脱机交易序号
	unsigned char arrOverdraftAmount[3];//透支限额
	unsigned char arrTradeAmount[4];//交易金额
	unsigned char ucTradeType;//交易类型
	unsigned char arrTradeTerminalNo[6];//终端机编号
	unsigned char arrTradeDate[4];//记录日期 带时分秒 20181026172639
	unsigned char arrTradeTime[3];//记录时间
	unsigned char ucReserve;//为了对其保留
}
SinopecRecordStruct;

//中石化卡片数据结构
typedef struct _SinopecCardStruct
{
	unsigned char arrCardNo[16];//16字节
	unsigned char arrSignedDate[4];//签发日期
	unsigned char arrValidityEndDate[4];//到期日期
	int nCardBalance;		//卡片余额
	int nPinFalseCount;//Pin失败统计数
	SinopecRecordStruct arrSinopecRecord[16];//16个记录
}
SinopecCardStruct;

typedef struct _SocialSecurityCardStruct//社保卡结构 里面存放公开信息
{
	char szCardNo[16];//实际只有9个字符
	char szName[32];//一般是4-8个字符 考虑到特殊人名 搞多点
	char szSSCNo[32];//一般是身份证号18个字符
	char szSex[8];//性别
	char szNation[32];//民族 有的民族名称有点长
	char szBankNo[32];//对应的银行卡号
	char szSignedDate[32];//签发日期
	char szValidityEndDate[32];//到期日期
}SocialSecurityCardStruct;

typedef struct _SocialSecurityCardStructV3//社保卡结构 里面存放公开信息
{
	//以下为发卡机构数据文件EF05 根据V2.0 构造 后续有了V3.0的东东再处理 这个应该是一致的
	char szIdentificationCode[64];//卡的识别码 实际只有16个字节 转成hex字串 便于显示 长度就搞长点
	char szType[4];//卡类型 实际只有1个字节 
	char szVersion[4];//卡版本 实际4个字节 
	char szInstitutionalNumber[32];//发卡机构 实际只有12个字节 
	char szSignedDate[32];//签发日期 实际只有4个字节 
	char szValidityEndDate[32];//到期日期 实际只有4个字节 
	char szCardNo[32];//卡号 实际只有9个字节 
}SocialSecurityCardStructV3;


#pragma pack(push) //保存对齐状态
#pragma pack(1)//设定为1字节对齐
typedef struct _UhfCmdFrameHeadStruct
{
	unsigned char ucFrameBegin;			//数据帧头 == BB
	unsigned char ucFrameType;			//数据帧类型
										//0x00 命令帧: 由上位机发送给 M100/QM100 芯片
										//0x01 响应帧: 由 M100/QM100 芯片发回给上位机
										//0x02 通知帧: 由 M100/QM100 芯片发回给上位机
	unsigned char ucCommand;			//指令
	//unsigned short usParameterLength;	//后续参数长度
	unsigned char ucParameterLengthMSB;	//后续参数长度高字节
	unsigned char ucParameterLengthLSB;	//后续参数长度低字节
	////后续不再定义
	unsigned char ucParameterData;		//参数数据

} UhfCmdFrameHeadStruct;
#pragma pack(pop)//恢复对齐状态
#define EPC_MAX_LENGTH			64		//EPC缓冲长度 一般好像是12字节 搞长点是为了以后有长的
typedef struct _UhfInventoryStruct
{
	unsigned char arrEPCBuffer[EPC_MAX_LENGTH];//EPC缓冲 
	unsigned char ucEPCRealLength;//EPC真实长度
	unsigned char  ucRssi;//型号强度
	unsigned short usPC;//协议控制码 这个信息里面也有EPC长度 考虑方便 和 字节对齐 上面多定义了一个
}UhfInventoryStruct;

//手机信息结构体
typedef struct _PhoneInfoStruct
{
	char szImei[32];				//IMEI
	char szImsi[32];				//IMSI
	char szLine1Number[32];			//手机号 貌似只能取GSM的
	char szSimSerialNumber[32];		//SIM卡序列号
	char szAndroidDeviceID[32];		//ANDROID设备ID
}PhoneInfoStruct;
//ST32 同一个结构体 应用配置数据 可以多次改写写入地址CONFIG1_FLASH_FIRST_PAGE_ADDRESS  CONFIG1BAK_FLASH_FIRST_PAGE_ADDRESS
typedef struct _AppConfigStruct//考虑到4字节对齐 以下所有定义都是4字节的倍数 所有一次性的配置数据都放到这里
{
#define uint8_t unsigned char
	uint8_t arrIapSwitch[4];				//Iap开关参数 FFFFFFFF 有效 00000000 无效
	uint8_t arrLocalIpAddress[4];		//本地IP地址
	uint8_t arrLocalNetMaskAddress[4];	//本地子网掩码
	uint8_t arrLocalGatewayAddress[4];	//本地网关
	uint8_t arrPassWord[16];			//密码 只有密码核对通过才能执行改写 清除动作 清楚后密码为32个F或0
//	uint8_t arrUhfConfig[256];			//超高频配置信息
//	uint8_t arrWifiConfig[256];			//Wifi配置信息

}AppConfigStruct;

//这个配置用于串口服务器 存放地址和_AppConfigStruct 
typedef struct _AppConfigE2sStruct//考虑到4字节对齐 以下所有定义都是4字节的倍数 所有一次性的配置数据都放到这里
{
	unsigned char arrIapSwitch[4];				//Iap开关参数 FFFFFFFF 有效 00000000 无效
	unsigned char arrLocalIpAddress[4];		//本地IP地址
	unsigned char arrLocalNetMaskAddress[4];	//本地子网掩码
	unsigned char arrLocalGatewayAddress[4];	//本地网关
	unsigned char arrPassWord[16];			//密码 只有密码核对通过才能执行改写 清除动作 清除后密码为32个F或0
											// 	union
											// 	{
											// 		struct //这个定义是给串口服务器用的
											// 		{
	int				nRs232BaudRate;//串口通信用波特率
	unsigned char	ucRs232DataBits;// 数据位5 6 7 8
	unsigned char	ucRs232StopBits;//停止位 0:ONESTOPBIT; 1:ONE5STOPBITS; 2:TWOSTOPBITS;
	unsigned char	ucRs232Parity;//奇偶校验 0 NONE 1 ODD 2 EVEN 3 MARK 4 SPACE
	unsigned char	ucRs232FlowControl;// 流控

	int				nRs485BaudRate;//串口通信用波特率
	unsigned char	ucRs485DataBits;// 数据位5 6 7 8
	unsigned char	ucRs485StopBits;//停止位 0:ONESTOPBIT; 1:ONE5STOPBITS; 2:TWOSTOPBITS;
	unsigned char	ucRs485Parity;//奇偶校验 0 NONE 1 ODD 2 EVEN 3 MARK 4 SPACE
	unsigned char	ucRs485FlowControl;// 流控

}AppConfigE2sStruct;

#endif

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * 打开设备
	 * 
	 * @param strDeviceName
	 *            串口设备名称
	 * @param nVID
	 *            USB设备VID
	 * @param nPID
	 *            USB设备PID
	 * @param nUsbDeviceIndex
	 *            USB设备索引
	 * @param unRecvTimeOut
	 *            接收超时
	 * @param pLotusCardExtendReadWriteCallBack 外部读写通道回调函数 只要针对ANDROID 
	 * 			如果没有设备写权限时，可以使用外部USB或串口进行通讯，
	 * 			需要改造callBackProcess中相关代码完成读写工作 目前范例提供USB操作
	 * @return true=成功
	 */
	LotusHandle WINAPI LotusCardOpenDevice(char * pszDeviceName, int nVID, int nPID, int nUsbDeviceIndex, unsigned int unRecvTimeOut, LotusCardExtendReadWriteCallBack  pLotusCardExtendReadWriteCallBack);

	/**
	 * 关闭设备
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 */
	void WINAPI LotusCardCloseDevice(LotusHandle nDeviceHandle);

	/**
	 * 寻卡
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nRequestType
	 *            请求类型
	 * @param tLotusCardParam
	 *            结果值 用里面的卡片类型
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardRequest(LotusHandle nDeviceHandle, int nRequestType,
			LotusCardParamStruct* pLotusCardParam);

	/**
	 * 防冲突
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param tLotusCardParam
	 *            结果值 用里面的卡号
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardAnticoll(LotusHandle nDeviceHandle,
			LotusCardParamStruct* pLotusCardParam);

	/**
	 * 选卡
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param tLotusCardParam
	 *            参数(使用里面的卡号)与结果值(使用里面的卡容量大小)
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardSelect(LotusHandle nDeviceHandle,
			LotusCardParamStruct* pLotusCardParam);

	/**
	 * 密钥验证
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nAuthMode
	 *            验证模式
	 * @param nSectionIndex
	 *            扇区索引
	 * @param tLotusCardParam
	 *            参数(使用里面的卡号)
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardAuthentication(LotusHandle  nDeviceHandle, int nAuthMode,
			int nSectionIndex, LotusCardParamStruct* pLotusCardParam);

	/**
	 * 密钥验证使用参数里面的密钥
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nAuthMode
	 *            验证模式
	 * @param nSectionIndex
	 *            扇区索引
	 * @param tLotusCardParam
	 *            参数(使用里面的卡号)
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardAuthenticationWithPassword(LotusHandle  nDeviceHandle, int nAuthMode,
			int nSectionIndex, LotusCardParamStruct* pLotusCardParam);

	/**
	 * 卡片中止响应
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardHalt(LotusHandle nDeviceHandle);

	/**
	 * 读指定地址数据
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nAddress 块地址
	 * @param tLotusCardParam 结果值（读写缓冲）
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardRead(LotusHandle nDeviceHandle, int nAddress, LotusCardParamStruct* pLotusCardParam);
	
	/**
	 * 写指定地址数据
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nAddress 块地址
	 * @param tLotusCardParam 参数（读写缓冲）
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardWrite(LotusHandle nDeviceHandle, int nAddress, LotusCardParamStruct* pLotusCardParam);
	
	/**
	 * 加值
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nAddress 块地址
	 * @param nValue 值
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardIncrement(LotusHandle nDeviceHandle, int nAddress, int nValue);
	
	/**
	 * 减值
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nAddress 块地址
	 * @param nValue 值
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardDecrement(LotusHandle nDeviceHandle, int nAddress,int nValue);
	
	/**
	 * 卡数据块传入卡的内部寄存器
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nAddress 块地址
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardRestore(LotusHandle nDeviceHandle, int nAddress);
	/**
	 * 内部寄存器传入卡的卡数据块
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nAddress 块地址
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardTransfer(LotusHandle nDeviceHandle, int nAddress);

	/**
	 * 装载密钥
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nAuthMode 验证模式
	 * @param nSectionIndex 扇区索引
	 * @param tLotusCardParam 参数（密钥）
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardLoadKey(LotusHandle nDeviceHandle,int nAuthMode, int nSectionIndex, LotusCardParamStruct* pLotusCardParam);
	
	/**
	 * 蜂鸣
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nDeviceHandle 设备句柄
	 * @param nBeepLen 蜂鸣长度 毫秒为单位
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardBeep(LotusHandle nDeviceHandle, int nBeepLen);

	/**
	 * 清空缓冲
	 * @param nDeviceHandle 设备句柄
	 * @param tLotusCardParam 结果值（读写缓冲）
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardEmptyBuffer(LotusHandle  nDeviceHandle, LotusCardParamStruct* pLotusCardParam);

	/**
	 * 发送指令 用于CPU卡
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nTimeOut 超时参数
	 * @param tLotusCardParam 参数（指令缓冲,返回结果）
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardSendCpuCommand(LotusHandle nDeviceHandle, int nTimeOut, LotusCardParamStruct* pLotusCardParam);

	/********************************以下函数调用上述函数，为了简化第三方调用操作***************************/
	/**
	* 读指定地址文本
	* @param nSectionIndex 扇区索引
	* @param pTextInfo 结果值（读写缓冲）
	* @param unTextInfoLength 文本缓冲长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardReadText(LotusHandle nDeviceHandle, int nSectionIndex, char * pTextInfo, unsigned int unTextInfoLength);
	/**
	* 写指定地址文本
	* @param nSectionIndex 扇区索引
	* @param pTextInfo 结果值（读写缓冲）
	* @param unTextInfoLength 文本缓冲长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardWriteText(LotusHandle nDeviceHandle, int nSectionIndex, char * pTextInfo, unsigned int unTextInfoLength);

	/**
	 * 获取卡号 上位机简化
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nRequestType
	 *            请求类型
	 * @param tLotusCardParam
	 *            结果值 
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetCardNo(LotusHandle nDeviceHandle, int nRequestType,
			LotusCardParamStruct* pLotusCardParam);
	/**
	 * 获取卡号 MCU简化
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nRequestType
	 *            请求类型
	* @param ucBeepLen 蜂鸣长度 最长255毫秒
	* @param ucUseHalt 使用中止 1=调用中止操作 0=不动作
	* @param ucUseLoop 使用循环 
	*        1=读卡器内部循环获取卡号 获取到数据再返回 上位机接收超时后 应立即再次读取
	*        0=读卡器内部只动作一次
	 * @param tLotusCardParam
	 *            结果值 
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetCardNoEx(LotusHandle nDeviceHandle, int nRequestType, unsigned char ucBeepLen, unsigned char ucUseHalt, 
		unsigned char ucUseLoop, LotusCardParamStruct* pLotusCardParam);
	/**
	 * 初始值
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nAddress 块地址
	 * @param nValue 值
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardInitValue(LotusHandle nDeviceHandle,  int nAddress, int nValue);

	/**
	 * 修改密码AB
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pPasswordA 密码A
	 * @param pPasswordB 密码B
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardChangePassword(LotusHandle nDeviceHandle, int nSectionIndex, const char * pPasswordA, const  char * pPasswordB);

	/**
	 * 设置外部读写函数
	* @param nDeviceHandle
	*            设备句柄
	 * @param pLotusCardExtendReadWriteCallBack 外部读写操作函数
	 * @return 
	 */
	void WINAPI LotusCardSetExtendReadWrite(LotusHandle nDeviceHandle, LotusCardExtendReadWriteCallBack  pLotusCardExtendReadWriteCallBack);

	/**
	* 设置身份证设备外部读写函数
	* @param nDeviceHandle
	*            设备句柄
	* @param pLotusCardExtendIdDeviceCallBack 外部读写操作函数
	* @return 
	*/
	void WINAPI LotusCardSetIdDeviceExtendReadWrite(LotusHandle  nDeviceHandle, LotusCardExtendIdDeviceCallBack  pLotusCardExtendIdDeviceCallBack);


	/**
	 * 复位CPU卡
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param tLotusCardParam
	 *            结果值 
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardResetCpuCard(LotusHandle  nDeviceHandle, LotusCardParamStruct* pLotusCardParam);

	/**
	* 复位CPU卡 此方法里面没有调用GetCardNo
	* @param nDeviceHandle
	*            设备句柄
	* @param tLotusCardParam
	*            结果值 
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardResetCpuCardNoGetCardNo(LotusHandle  nDeviceHandle, LotusCardParamStruct* pLotusCardParam);

	/**
	* 取消激活CPU卡 后续可以发送WUPA
	* @param nDeviceHandle
	*            设备句柄
	* @param tLotusCardParam
	*            结果值 
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardDeselectCpuCard(LotusHandle  nDeviceHandle, LotusCardParamStruct* pLotusCardParam);

	/**
	 * 发送指令 用于CPU卡 封装LotusCardSendCpuCommand
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param tLotusCardParam 参数（指令缓冲,返回结果）
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardSendCOSCommand(LotusHandle nDeviceHandle, LotusCardParamStruct* pLotusCardParam);
	/**
	* 获取银行卡卡号
	* @param nDeviceHandle
	* @param pBankCardNo 银行卡号 同印刷号码
	* @param unBankCardNoLength 银行卡号长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetBankCardNo(LotusHandle nDeviceHandle, char * pBankCardNo, unsigned int unBankCardNoLength);
	/**
	 * 7816通道获取银行卡
	 * @param nDeviceHandle
	 * @param pBankCardNo 银行卡号 同印刷号码
	 * @param unBankCardNoLength 银行卡号长度
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetBankCardNoBy7816(LotusHandle  nDeviceHandle, char * pBankCardNo, unsigned int unBankCardNoLength);
	/**
	 * 7816通道获取社保卡号
	 * @param nDeviceHandle
	 * @param psttSocialSecurityCard 社保卡信息结构体指针
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetSocialSecurityInfoBy7816(LotusHandle  nDeviceHandle, SocialSecurityCardStruct * psttSocialSecurityCard);
	/**
	* 获取社保卡信息V3.0
	* @param nDeviceHandle
	* @param bIs7816 是否7816 默认为否 使用非接触式通道
	* @param psttSocialSecurityCard 社保卡信息结构体指针
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetSocialSecurityInfo(LotusHandle  nDeviceHandle, BOOL bIs7816, SocialSecurityCardStructV3 * psttSocialSecurityCardV3);
	/**
	 * 进入Esp isp模式
	 * @param nDeviceHandle
	 *            设备句柄
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardSendEspEnterIspCommand(LotusHandle nDeviceHandle);
	/**
	 * 发送Esp isp开始动作
	 * @param nDeviceHandle
	 *            设备句柄
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardSendEspIspBeginCommand(LotusHandle nDeviceHandle);

	/**
	 * 写文件到ESP FLASH
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pszFilePath
	 *            文件路径
	 * @param unOffset
	 *            FLASH 偏移量
	 * @param pOnLotusCardWrite2FlashCallBack
	 *            回调函数 用于处理进度显示
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardWriteEspFile2Flash(LotusHandle nDeviceHandle, char * pszFilePath, unsigned int unOffset, LotusCardWrite2FlashCallBack  pOnLotusCardWrite2FlashCallBack);
	/**
	 * 发送Esp isp结束动作
	 * @param nDeviceHandle
	 *            设备句柄
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardSendEspIspEndCommand(LotusHandle nDeviceHandle);

	/**
	* 读指定地址数据 一个指令就完成所有动作
	* @param nDeviceHandle
	*            设备句柄
	* @param nRequestType
	*            请求类型
	* @param nAddress 块地址
	* @param ucUsePassWord 使用密码 1=使用参数密码 0 =使用设备内部密码
	* @param ucBeepLen 蜂鸣长度 最长255毫秒
	* @param ucUseHalt 使用中止
	* @param tLotusCardParam 结果值（读写缓冲）
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardReadData(LotusHandle nDeviceHandle, int nRequestType, int nAddress, unsigned char ucUseParameterPassWord, 
		unsigned char ucBeepLen, unsigned char ucUseHalt, LotusCardParamStruct* pLotusCardParam);

	/**
	 * 写指定地址数据
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nAddress 块地址
	 * @param ucBeepLen 蜂鸣长度 最长255毫秒
	 * @param ucUseHalt 使用中止
	 * @param tLotusCardParam 参数（读写缓冲）
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardWriteData(LotusHandle nDeviceHandle,  int nAddress, unsigned char ucBeepLen, unsigned char ucUseHalt, LotusCardParamStruct* pLotusCardParam);
	/******************************** 以下函数为WIFI操作函数 ***************************/
	/**
	 * 扫描AP
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pBssInfoArray 装载返回AP信息数组
	 * @param unBssInfoArraySize 装载返回AP数组大小
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardScanAp(LotusHandle nDeviceHandle, BssInfoStruct * pBssInfoArray, unsigned int unBssInfoArraySize);

	/**
	* 获取WIFI 工作模式
	 * @param nDeviceHandle
	 *            设备句柄
	* @param pucWifiMode
	*            模式返回值
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetWifiMode(LotusHandle nDeviceHandle, unsigned char * pucWifiMode);

	/**
	* 设置WIFI 工作模式
	 * @param nDeviceHandle
	 *            设备句柄
	* @param ucWifiMode
	*            模式值
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardSetWifiMode(LotusHandle nDeviceHandle, unsigned char ucWifiMode);

	/**
	* 禁用WIFI
	 * @param nDeviceHandle
	 *            设备句柄
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardWifiDisable(LotusHandle  nDeviceHandle);

	/**
	* 启用WIFI
	 * @param nDeviceHandle
	 *            设备句柄
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardWifiEnable(LotusHandle  nDeviceHandle);

	/**
	* 获取TA信息
	 * @param nDeviceHandle
	 *            设备句柄
	* @param pStaInfoStruct
	*            STA相关参数
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetStaInfo(LotusHandle nDeviceHandle,StaInfoStruct * pStaInfoStruct);
	/**
	* 设置STA信息
	 * @param nDeviceHandle
	 *            设备句柄
	* @param pStaInfoStruct
	*            STA相关参数
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardSetStaInfo(LotusHandle nDeviceHandle, StaInfoStruct * pStaInfoStruct);


	/**
	* 连接测试
	 * @param pServerIp
	 *            服务器IP地址
	* @param nConnectTimeOut
	*            超时us为单位
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardConnectTest(char * pServerIp, int nConnectTimeOut);

	/**
	* 获取错误编码 
	 * @param nDeviceHandle
	 *            设备句柄
	* @return 错误编码 详见枚举值定义
	*/
	unsigned int WINAPI LotusCardGetErrorCode(LotusHandle nDeviceHandle);

	/**
	* 获取二代证操作错误编码 
	 * @param nDeviceHandle
	 *            设备句柄
	* @return 错误编码 详见枚举值定义
	*/
	unsigned int WINAPI LotusCardGetTwoIdErrorCode(LotusHandle  nDeviceHandle);

	/**
	* 设置二代证操作错误编码 
	* @param nDeviceHandle
	*            设备句柄
	* @param nErrorCode 错误编码 详见枚举值定义
	*/
	void WINAPI LotusCardSetTwoIdErrorCode(LotusHandle  nDeviceHandle, int nErrorCode);

	/**
	* 获取错误信息
	 * @param nDeviceHandle
	 *            设备句柄
	* @param errCode 错误编码
	* @param pszErrorInfo 错误信息地址
	* @param unErrorInfoLength 错误信息长度
	*/
	void  WINAPI LotusCardGetErrorInfo(LotusHandle  nDeviceHandle, LotusCardErrorCode errCode, char * pszErrorInfo, unsigned int unErrorInfoLength);


	/**
	* 获取二代证错误信息
	 * @param nDeviceHandle
	 *            设备句柄
	* @param errCode 错误编码
	* @param pszErrorInfo 错误信息地址
	* @param unErrorInfoLength 错误信息长度
	*/
	void  WINAPI LotusCardGetTwoIdErrorInfo(LotusHandle  nDeviceHandle, TwoIdErrorCode errCode, char * pszErrorInfo, unsigned int unErrorInfoLength);

	/**
	* 获取二代证调度服务器错误信息
	 * @param nDeviceHandle
	 *            设备句柄
	* @param pszErrorInfo 错误信息地址
	* @param unErrorInfoLength 错误信息长度
	*/
	void  WINAPI LotusCardGetTwoIdDispatchServerErrorInfo(LotusHandle  nDeviceHandle, char * pszErrorInfo, unsigned int unErrorInfoLength);

	/**
	 * 设置卡片类型
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param cCardType 卡片类型 A='A'/'a' B='B'/'b' F='F'/'f' C='C'/'c'
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardSetCardType( LotusHandle nDeviceHandle, char cCardType);

	/**
	 * Felica寻卡 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param unTimerSlot timer slot
	 * @param tLotusCardParam 参数（读写缓冲）
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardFelicaPolling(LotusHandle nDeviceHandle, unsigned char unTimerSlot, LotusCardParamStruct* pLotusCardParam);


	/**
	 * 发送SAMV命令
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param tLotusCardParam 参数（读写缓冲）
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardSendSamvCommand(LotusHandle nDeviceHandle, LotusCardParamStruct* pLotusCardParam);

	/**
	 * 发送COS指令结果给SAMV
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param tLotusCardParam 参数（读写缓冲）
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardSendCosResult2Samv(LotusHandle  nDeviceHandle, LotusCardParamStruct* pLotusCardParam);
	
	/**
	 * 获取安全模块串口数据
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param tLotusCardParam 参数（读写缓冲）
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetSamvUartData(LotusHandle  nDeviceHandle, LotusCardParamStruct* pLotusCardParam);

	/**
	 * 获取二代证信息
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pTwoIdInfo 参数 二代证信息结构体地址
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetTwoIdInfo(LotusHandle  nDeviceHandle, TwoIdInfoStruct * pTwoIdInfo);

	/**
	 * 通过网络获取二代证照片信息 WL格式输入
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pszServerIp 参数 安全模块所在服务器IP
	 * @param pTwoIdInfo 参数 二代证信息结构体地址
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardWlDecodeByServer(LotusHandle  nDeviceHandle, const  char * pszDecodeServerIp, TwoIdInfoStruct * pTwoIdInfo);

	/**
	 * 通过网络获取二代证信息 这个API用于网络环境比较糟糕的地方 内部有重试动作
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pszServerIp 参数 安全模块所在服务器IP
	 * @param unServerPort 参数 服务器端口
	 * @param pTwoIdInfo 参数 二代证信息结构体地址
	 * @param unRecvTimeOut 参数 接收超时 默认10秒
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetTwoIdInfoByWireless(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort, TwoIdInfoStruct * pTwoIdInfo, unsigned int unRecvTimeOut);

	/**
	 * 通过网络获取二代证信息 这个API用于网络环境比较糟糕的地方 内部有重试动作 扩展函数 有指纹返回
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pszServerIp 参数 安全模块所在服务器IP
	 * @param unServerPort 参数 服务器端口
	 * @param pTwoIdInfo 参数 二代证信息结构体地址
	 * @param unRecvTimeOut 参数 接收超时 默认10秒
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetTwoIdInfoByWirelessEx(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort, TwoIdInfoStruct * pTwoIdInfo, unsigned int unRecvTimeOut);
	/**
	 * 通过网络获取二代证信息
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pszServerIp 参数 安全模块所在服务器IP
	 * @param pTwoIdInfo 参数 二代证信息结构体地址
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetTwoIdInfoByServer(LotusHandle  nDeviceHandle, const  char * pszServerIp, TwoIdInfoStruct * pTwoIdInfo);

	/**
	 * 通过网络获取二代证信息
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pszServerIp 参数 安全模块所在服务器IP
	 * @param unServerPort 参数 服务器端口
	 * @param pTwoIdInfo 参数 二代证信息结构体地址
	 * @param unRecvTimeOut 参数 接收超时 默认10秒
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetTwoIdInfoByServerEx(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort, TwoIdInfoStruct * pTwoIdInfo, unsigned int unRecvTimeOut);

	/**
	 * 通过单片机服务器网络获取二代证信息
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pszServerIp 参数 调度服务器IP
	 * @param nUserAccount 参数 用户账号 整形 便于服务器检索
	 * @param pszPassWord 参数 密码
	 * @param pTwoIdInfo 参数 二代证信息结构体地址
	 * @param nPostcode 参数 邮政编码
	 * @param nLineType 参数 线路类型 0=未知 1=电信 2=联通 3=移动 4=其他
	 * @param unRecvTimeOut 参数 接收超时 默认10秒
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetTwoIdInfoByMcuServer(LotusHandle  nDeviceHandle, const  char * pszDispatchServerIp, int nUserAccount, const char * pszPassWord, TwoIdInfoStruct * pTwoIdInfo, int nPostcode, int nLineType, unsigned int unRecvTimeOut);

	/**
	 * 设置二代证照片地址
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pBmpBuffer 参数 BMP缓冲地址
	 * @param unBmpBufferLength 参数 bmp缓冲长度
	 * @param bCompressJpeg 参数 是否处理JPEG压缩 默认压缩
	 * @return BMP实际数据大小
	 */
	BOOL WINAPI LotusCardSetIdPhotoAddress(LotusHandle  nDeviceHandle, unsigned char * pBmpBuffer, int unBmpBufferLength, BOOL bCompressJpeg);
	/**
	 * 通过单片机服务器网络获取二代证信息 带指纹
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pszServerIp 参数 调度服务器IP
	 * @param nUserAccount 参数 用户账号 整形 便于服务器检索
	 * @param pszPassWord 参数 密码
	 * @param pTwoIdInfo 参数 二代证信息结构体地址
	 * @param nPostcode 参数 邮政编码
	 * @param nLineType 参数 线路类型 0=未知 1=电信 2=联通 3=移动 4=其他
	 * @param unRecvTimeOut 参数 接收超时 默认10秒
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetTwoIdInfoByMcuServerEx(LotusHandle  nDeviceHandle, const  char * pszDispatchServerIp, int nUserAccount, const char * pszPassWord, TwoIdInfoStruct * pTwoIdInfo, int nPostcode, int nLineType, unsigned int unRecvTimeOut);
	/**
	 * 通过单片机服务器网络获取二代证信息 ANDROID专用 此函数不做到处处理 仅提供给JAVA环境调用使用
	 * @param psttPhoneInfo android手机信息
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pszServerIp 参数 调度服务器IP
	 * @param nUserAccount 参数 用户账号 整形 便于服务器检索
	 * @param pszPassWord 参数 密码
	 * @param pTwoIdInfo 参数 二代证信息结构体地址
	 * @param nPostcode 参数 邮政编码
	 * @param nLineType 参数 线路类型 0=未知 1=电信 2=联通 3=移动 4=其他
	 * @param bIsLotusDevice  LOTUS 设备 默认问false
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetTwoIdInfoByMcuServerForAndroid(PhoneInfoStruct * psttPhoneInfo, LotusHandle  nDeviceHandle, const  char * pszDispatchServerIp, int nUserAccount, const char * pszPassWord, TwoIdInfoStruct * pTwoIdInfo, int nPostcode, int nLineType, unsigned int unRecvTimeOut, BOOL bIsLotusDevice = FALSE);

	/**
	 * 通过带PSAM单片机服务器网络获取二代证信息
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pszServerIp 参数 安全模块所在服务器IP
	 * @param unServerPort 参数 服务器端口
	 * @param pTwoIdInfo 参数 二代证信息结构体地址
	 * @param unRecvTimeOut 参数 接收超时 默认10秒
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetTwoIdInfoByPsamServer(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort, TwoIdInfoStruct * pTwoIdInfo, unsigned int unRecvTimeOut);

	/**
	 * 通过带PSAM单片机服务器网络获取二代证信息 带指纹
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pszServerIp 参数 安全模块所在服务器IP
	 * @param unServerPort 参数 服务器端口
	 * @param pTwoIdInfo 参数 二代证信息结构体地址
	 * @param unRecvTimeOut 参数 接收超时 默认10秒
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetTwoIdInfoByPsamServerEx(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort, TwoIdInfoStruct * pTwoIdInfo, unsigned int unRecvTimeOut);
	/**
	* 复位mcu 第二代产品用API
	* @param nDeviceHandle
	*            设备句柄
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardResetMcuByServer(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort);

	/**
	* 复位SAMV模块 第二代产品用API
	* @param nDeviceHandle
	*            设备句柄
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardResetSamvByServer(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort);

	/**
	* 检查SAMV状态 第二代产品用API
	* @param nDeviceHandle
	*            设备句柄	
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetSamvCheckStatusByServer(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort);

	/**
	* 获取SAMV管理信息 第二代产品用API
	* @param nDeviceHandle
	*            设备句柄	
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param pszManagerMessage 参数 管理信息缓冲地址
	* @param unManagerMessageLength 参数 管理信息缓冲长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetSamvManagerMessageByServer(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort, 
		char * pszManagerMessage, unsigned int unManagerMessageLength);

	/**
	* 获取SAMV指令执行重复间隔等待时间 第二代产品用API
	* @param nDeviceHandle
	*            设备句柄	
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param pszTimeBuffer 参数 时间缓冲 里面有3个64位计数
	* @param unTimeBufferLength 参数 缓冲长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetSamvWaitTimeByInterval(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort, 
		char * pszTimeBuffer, unsigned int unTimeBufferLength);

	/**
	* 获取SAMV最后错误信息
	* @param nDeviceHandle
	*            设备句柄	
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param pSamvErrorInfoS 参数 错误信息结构体
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetSamvLastErrorInfo(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort, 
		SamvErrorInfoStruct * pSamvErrorInfo);

	/**
	* 获取SAMV收发时间记录
	* @param nDeviceHandle
	*            设备句柄	
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param pSamvSendReceiveTimeInfo 收发结构体数组指针
	* @param unArrayLength 收发结构体数组长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetSamvSendReceivTimeInfo(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort, 
		  SamvSendReceiveTimeStruct * pSamvSendReceiveTimeInfo, unsigned int unArrayLength);

	/**
	* 复位服务器端PSAM卡片
	* @param nDeviceHandle
	*            设备句柄
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param pPsamResetMessageBuffer PSAM复位信息缓冲地址
	* @param unBufferLength PSAM复位信息缓冲长度
	* @return true = 成功
	*/
	int WINAPI LotusCardResetPsamByServer(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort,
		unsigned char * pPsamResetMessageBuffer, unsigned int unBufferLength);

	/**
	* 执行PSAM指令
	* @param nDeviceHandle
	*            设备句柄
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param pPsamCommandBuffer 指令缓冲地址
	* @param unCommandLength 指令长度
	* @param unBufferLength 缓冲长度
	* @return >0 成功 <=0 失败
	*/
	int WINAPI LotusCardPsamCommandByServer(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort,
		unsigned char * pPsamCommandBuffer, unsigned int unCommandLength, unsigned int unBufferLength);
	/**
	* 获取二代证服务器MAC地址
	* @param nDeviceHandle
	*            设备句柄
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param pMacAddressBuffer MAC地址缓冲地址
	* @param unBufferLength MAC地址缓冲长度
	* @return >0 MAC地址长度 <=0 失败
	*/
	int WINAPI LotusCardGetTwoIdServerMacAddress(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort,
		unsigned char * pMacAddressBuffer, unsigned int unBufferLength);

	/**
	* 获取二代证服务器MCU序列号
	* @param nDeviceHandle
	*            设备句柄
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param pMcuSerialNoBuffer MCU序列号缓冲地址
	* @param unBufferLength MAC地址缓冲长度
	* @return >0 MCU序列号长度 <=0 失败
	*/
	int WINAPI LotusCardGetTwoIdServerMcuSerialNo(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort,
		unsigned char * pMcuSerialNoBuffer, unsigned int unBufferLength);

	/**
	* 获取二代证服务器应用配置信息 里面有IP配置
	* @param nDeviceHandle
	*            设备句柄
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param psttAppConfig 二代证服务器模块配置信息
	* @return >0 配置信息长度 <=0 失败
	*/
	int WINAPI LotusCardGetTwoIdServerAppConfig(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort,
		AppConfigStruct * psttAppConfig);

	/**
	* 设置二代证服务器应用配置信息 里面有IP配置
	* @param nDeviceHandle
	*            设备句柄
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param psttAppConfig 二代证服务器模块配置信息
	* @return >0 配置信息长度 <=0 失败
	*/
	int WINAPI LotusCardSetTwoIdServerAppConfig(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort,
		AppConfigStruct * psttAppConfig);

	/**
	* 清除二代证服务器应用配置信息 里面有IP配置
	* @param nDeviceHandle
	*            设备句柄
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param psttAppConfig 二代证服务器模块配置信息
	* @return >0 配置信息长度 <=0 失败
	*/
	int WINAPI LotusCardClearTwoIdServerAppConfig(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort,
		AppConfigStruct * psttAppConfig);

	/**
	* 修改二代证服务器应用配置密码
	* @param nDeviceHandle
	*            设备句柄
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param pOldPassword 旧密码 
	* @param pNewPassword 新密码
	* @return >0 配置信息长度 <=0 失败
	*/
	int WINAPI LotusCardChangeTwoIdServerAppConfigPassword(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort,
		char * pOldPassword, char * pNewPassword);

	/**
	* 通过小模块 控制其他小模块电源
	* @param nDeviceHandle
	*            设备句柄
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param nPowerOnOff 1 = 打开电源 0 = 关闭电源
	* @param pConfigPassword 密码  只有密码核对通过才允许动作 避免被攻击
	* @return >0 成功 <=0 失败
	*/
	int WINAPI LotusCardPowerOnOffOtherDevice(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort,
		int nPowerOnOff, char * pConfigPassword);
	/**
	* 控制小模块LED
	* @param nDeviceHandle
	*            设备句柄
	* @param pszServerIp 参数 安全模块IP
	* @param unServerPort 参数 安全模块端口 由于通过路由器中转 实际指向路由IP 和PORT
	* @param nLedOnOff 1 = 打开电源 0 = 关闭电源
	* @return >0 成功 <=0 失败
	*/
	int WINAPI LotusCardSamvLedOnOff(LotusHandle  nDeviceHandle, const  char * pszServerIp, unsigned int unServerPort, int nLedOnOff);
	/**
	* 读取NFC缓冲
	 * @param nDeviceHandle
	 *            设备句柄
	* @param pszNfcBuffer
	*            缓冲地址
	* @param unNfcBufferLength
	*            缓冲长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardReadNfcBuffer(LotusHandle nDeviceHandle, char * pszNfcBuffer, unsigned int unNfcBufferLength);

	/**
	* 写入NFC缓冲
	 * @param nDeviceHandle
	 *            设备句柄
	* @param pszNfcBuffer
	*            缓冲地址
	* @param unNfcBufferLength
	*            缓冲长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardWriteNfcBuffer(LotusHandle nDeviceHandle, char * pszNfcBuffer, unsigned int unNfcBufferLength);

	/******************************** 以下函数为type b操作函数 ***************************/
	/**
	 * 寻卡
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nRequestType
	 *            请求类型
	 * @param tLotusCardParam
	 *            结果值 用里面的卡片类型
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardRequestB(LotusHandle nDeviceHandle, int nRequestType,
			LotusCardParamStruct* pLotusCardParam);



	/**
	 * 选卡
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param tLotusCardParam
	 *            参数(使用里面的卡号)与结果值(使用里面的卡容量大小)
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardSelectB(LotusHandle nDeviceHandle,
			LotusCardParamStruct* pLotusCardParam);


	/**
	 * 卡片中止响应
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardHaltB(LotusHandle nDeviceHandle);

	/**
	 * 获取超高频固件信息
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucVersionType 
	 *			  参数 版本类型 硬件版本  0x00 软件版本 0x01  制造商信息  0x02
	 * @param pUhfFwVersionInfo 
	 *			  参数 超高频固件版本信息字串地址
	 * @param unVersionInfoLength 
	 *			  参数 字串分配内存长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardGetUhfFwVersion(LotusHandle nDeviceHandle, unsigned char ucVersionType, char * pUhfFwVersionInfo,  unsigned int unVersionInfoLength);


	/**
	* 发送M100系列UHF 单次轮询指令
	* 
	* @param nDeviceHandle
	*            设备句柄
	* @param unInventoryCount 
	*			  参数 盘存返回的标签总数
	* @return true = 成功
	*/
	BOOL  WINAPI LotusCardM100UhfInventory(LotusHandle  nDeviceHandle, unsigned int * punInventoryCount);

	/**
	 * 发送M100系列UHF 获取盘存返回信息 在单次轮询/多次轮询后调用 以后如果需要也可以搞成回调的方式 搞个线程处理 不过有点麻烦 暂时就这样 wdy 2015-05-04
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucInventoryIndex 
	 *			  参数 盘存返回信息的索引
	 * @param pUhfInventory 
	 *			  参数 盘存返回信息结构体指针
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfGetInventoryStruct(LotusHandle nDeviceHandle, unsigned char ucInventoryIndex, UhfInventoryStruct * pUhfInventory);

	/**
	 * 发送M100系列UHF 多次轮询指令
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucRssi 
	 *			  参数 获取RSSI
	 * @param ucPC 
	 *			  参数 获取PC
	 * @param pEPCBuffer 
	 *			  参数 获取EPC 存放地址
	 * @param unEPCBufferLength 
	 *			  参数 EPC存放缓冲长度
	 * @param unEPCLength 
	 *			  参数 获取EPC实际长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfReadMulti(LotusHandle  nDeviceHandle,unsigned char * pucRssi, unsigned short * pusPC, unsigned char * pEPCBuffer, 
		unsigned int unEPCBufferLength, unsigned int * punEPCLength);

	/**
	 * 发送M100系列UHF 停止多次轮询指令
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfStopMulti(LotusHandle nDeviceHandle);

	/**
	 * 发送M100系列UHF 获取发射功率
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param usPower 
	 *			  参数 0x07D0(当前功率为十进制2000，即20dBm)
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfGetPower(LotusHandle  nDeviceHandle, unsigned short * pusPower);


	/**
	 * 发送M100系列UHF 设置发射功率
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param usPower 
	 *			  参数 0x07D0(当前功率为十进制2000，即20dBm)
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfSetPower(LotusHandle nDeviceHandle, unsigned short usPower);

	/**
	 * 发送M100系列UHF 设置工作地区
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucRegion 
	 *			  参数 中国900MHz 01 中国800MHz 04 美国02 欧洲03 韩国06 
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfSetRegion(LotusHandle nDeviceHandle, unsigned char ucRegion);

	/**
	 * 发送M100系列UHF 获取工作信道
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucRfChannel 
	 *			  参数 0x00(Channel_Index 为0x00)
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfGetRfChannel(LotusHandle  nDeviceHandle, unsigned char * pucRfChannel);

	/**
	 * 发送M100系列UHF 设置工作信道
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucRfChannel 
	 *			  参数 0x00(Channel_Index 为0x00)
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfSetRfChannel(LotusHandle  nDeviceHandle, unsigned char ucRfChannel);

	/**
	 * 发送M100系列UHF 设置自动跳频
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucFHSS 
	 *			  参数 0xFF(0xFF 为设置自动跳频，0x00 为取消自动跳频)
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfSetFHSS(LotusHandle  nDeviceHandle, unsigned char ucFHSS);

	/**
	 * 发送M100系列UHF 获取Query 参数
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param usQueryParameter 
	 *			  参数 设置Query 命令中的相关参数。参数为2 字节，有下面的具体参数按位拼接而成：
	 *DR(1 bit): DR=8(1’b0), DR=64/3(1’b1). 只支持DR=8 的模式
	 *M(2 bit): M=1(2’b00), M=2(2’b01), M=4(2’b10), M=8(2’b11). 只支持M=1 的模式
	 *TRext(1 bit): No pilot tone(1’b0), Use pilot tone(1’b1). 只支持Use pilot tone(1’b1)模式
	 *Sel(2 bit): ALL(2’b00/2’b01), ~SL(2’b10), SL(2’b11)
	 *Session(2 bit): S0(2’b00), S1(2’b01), S2(2’b10), S3(2’b11)
	 *Target(1 bit): A(1’b0), B(1’b1)
	 *Q(4 bit): 4’b0000-4’b1111
	 *如果DR=8, M=1, TRext=Use pilot tone, Sel=00, Session=00, Target=A, Q=4，则指令如下：
	 *BB 00 0E 00 02 10 20 40 7E
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfGetQueryParamter(LotusHandle  nDeviceHandle, unsigned short * pusQueryParameter);

	/**
	 * 发送M100系列UHF 设置Query 参数
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param usQueryParameter 
	 *			  参数 设置Query 命令中的相关参数。参数为2 字节，有下面的具体参数按位拼接而成：
	 *DR(1 bit): DR=8(1’b0), DR=64/3(1’b1). 只支持DR=8 的模式
	 *M(2 bit): M=1(2’b00), M=2(2’b01), M=4(2’b10), M=8(2’b11). 只支持M=1 的模式
	 *TRext(1 bit): No pilot tone(1’b0), Use pilot tone(1’b1). 只支持Use pilot tone(1’b1)模式
	 *Sel(2 bit): ALL(2’b00/2’b01), ~SL(2’b10), SL(2’b11)
	 *Session(2 bit): S0(2’b00), S1(2’b01), S2(2’b10), S3(2’b11)
	 *Target(1 bit): A(1’b0), B(1’b1)
	 *Q(4 bit): 4’b0000-4’b1111
	 *如果DR=8, M=1, TRext=Use pilot tone, Sel=00, Session=00, Target=A, Q=4，则指令如下：
	 *BB 00 0E 00 02 10 20 40 7E
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfSetQueryParamter(LotusHandle  nDeviceHandle,  unsigned short usQueryParameter);

	/**
	 * 发送M100系列UHF 设置发射连续载波
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucCW 
	 *			  参数 0xFF 为打开连续波，0x00 为关闭连续波
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfSetCW(LotusHandle  nDeviceHandle, unsigned char ucCW);

	/**
	 * 发送M100系列UHF 测试射频输入端阻塞信号
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucChannelLow 
	 *			  参数 信道最低数值
	 * @param ucChannelHigh 
	 *			  参数 信道最高数值
	 * @param parrJammerBuffer 
	 *			  参数 Jammer数组缓冲地址
	 * @param unJammerBufferLength 
	 *			  参数 Jammer数组缓冲长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfScanJammer(LotusHandle  nDeviceHandle, unsigned char * pucChannelLow,  unsigned char * pucChannelHigh, unsigned char * parrJammerBuffer, unsigned int * punJammerBufferLength );

	/**
	 * 发送M100系列UHF 测试信道RSSI
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucChannelLow 
	 *			  参数 信道最低数值
	 * @param ucChannelHigh 
	 *			  参数 信道最高数值
	 * @param parrRssiBuffer 
	 *			  参数 RSSI数组缓冲地址
	 * @param unRssiBufferLength 
	 *			  参数 RSSI数组缓冲长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfScanRssi(LotusHandle  nDeviceHandle, unsigned char * pucChannelLow,  unsigned char * pucChannelHigh, unsigned char * parrRssiBuffer, unsigned int * punRssiBufferLength );

	/**
	 * 发送M100系列UHF 获取接收解调器参数
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucMixerGain 
	 *			  参数 混频器增益
	 * @param ucIFGain 
	 *			  参数 中频放大器增益
	 * @param usThrd 
	 *			  参数 信号解调阈值
	 * @param unJammerBufferLength 
	 *			  参数 Jammer数组缓冲长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfReadModemParameter(LotusHandle  nDeviceHandle, unsigned char * pucMixerGain,  unsigned char * pucIFGain, unsigned short * pusThrd);

	/**
	 * 发送M100系列UHF 设置接收解调器参数
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucMixerGain 
	 *			  参数 混频器增益
	 * @param ucIFGain 
	 *			  参数 中频放大器增益
	 * @param usThrd 
	 *			  参数 信号解调阈值
	 * @param unJammerBufferLength 
	 *			  参数 Jammer数组缓冲长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfSetModemParameter(LotusHandle  nDeviceHandle, unsigned char ucMixerGain,  unsigned char ucIFGain, unsigned short usThrd);

	/**
	 * 发送M100系列UHF 设置Inventory模式
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucInventoryMode 
	 *			  参数 Inventory模式
	 *			  Select 模式Mode 含义：
	 *			  0x00: 在对标签的所有操作之前都预先发送Select 指令选取特定的标签。
	 *			  0x01: 在对标签操作之前不发送Select 指令。
	 *			  0x02: 仅对除轮询Inventory 之外的标签操作之前发送Select 指令，如在
	 *			  Read，Write，Lock，Kill 之前先通过Select 选取特定的标签。
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfSetInventoryMode(LotusHandle  nDeviceHandle, unsigned char ucInventoryMode);

	/**
	 * 发送M100系列UHF 设置选择参数
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucSelParam 
	 *			  参数 0x01 (Target: 3’b000, Action: 3’b000, MemBank: 2’b01)
	 * @param unPtr 
	 *			  参数 0x00000020(以bit 为单位，非word) 从EPC 存储位开始
	 * @param ucMaskLen 
	 *			  参数 0x60(6 个word，96bits)
	 * @param ucTruncate 
	 *			  参数 0x00(0x00 是Disable truncation，0x80 是Enable truncation)
	 * @param parrMask 
	 *			  参数 Mask缓冲地址
	 * @param unMaskLength 
	 *			  参数 Mask缓冲长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfSetSelectParameter(LotusHandle  nDeviceHandle, unsigned char ucSelParam, unsigned int unPtr, unsigned char ucMaskLen, unsigned char ucTruncate,
		unsigned char * parrMask, unsigned int unMaskLength);


	/**
	 * 发送M100系列UHF 读取数据
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param unAccessPassword 
	 *			  参数 访问密码
	 * @param ucMemBank 
	 *			  参数 标签数据存储区
	 * @param usSAdreess 
	 *			  参数 读标签数据区地址偏移
	 * @param usDataLength 
	 *			  参数 读标签数据区地址长度 WORD为单位
	 * @param parrDataBuffer 
	 *			  参数 数据缓冲地址
	 * @param unDataBufferLength 
	 *			  参数 数据缓冲长度 送入buffer长度 返回实际长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfReadData(LotusHandle  nDeviceHandle, unsigned int unAccessPassword, unsigned char ucMemBank, unsigned short usSAdreess,  unsigned short usDataLength,
		unsigned char * parrDataBuffer, unsigned int * punDataBufferLength);

	/**
	 * 发送M100系列UHF 写标签数据存储区
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param unAccessPassword 
	 *			  参数 访问密码
	 * @param ucMemBank 
	 *			  参数 标签数据存储区
	 * @param usSAdreess 
	 *			  参数 读标签数据区地址偏移
	 * @param usDataLength 
	 *			  参数 读标签数据区地址长度 WORD为单位
	 * @param parrDataBuffer 
	 *			  参数 数据缓冲地址
	 * @param unDataBufferLength 
	 *			  参数 数据缓冲长度 送入buffer长度 返回实际长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfWriteData(LotusHandle  nDeviceHandle, unsigned int unAccessPassword, unsigned char ucMemBank, unsigned short usSAdreess,  unsigned short usDataLength,
		unsigned char * parrDataBuffer, unsigned int * punDataBufferLength);

	/**
	 * 发送M100系列UHF 锁定Lock 标签数据存储区
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param unAccessPassword 
	 *			  参数 访问密码
	 * @param parrLockLd 
	 *			  参数 LockLd数组缓冲地址
	 * @param unLockLdLength 
	 *			  参数 LockLd数组缓冲长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfLockUnLock(LotusHandle  nDeviceHandle, unsigned int unAccessPassword, unsigned char * parrLockLd, unsigned int unLockLdLength);

	/**
	 * 发送M100系列UHF 灭活Kill 标签
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param unKillPassword 
	 *			  参数 KILL密码
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardM100UhfKill(LotusHandle  nDeviceHandle, unsigned int unKillPassword);
	/**
	 * 获取设备号
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param parrDeviceNo 
	 *			  参数 设备号缓冲地址
	 * @param unDeviceNoLength 
	 *			  参数 设备号缓冲长度 目前不小于8字节 以后可能有调整
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardGetDeviceNo(LotusHandle  nDeviceHandle, char * pstrDeviceNo,  unsigned int unDeviceNoLength);

	/**
	 * 获取设备MAC地址
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param parrMacAddress
	 *			  参数 设备MAC地址缓冲地址
	 * @param unMacAddressLength 
	 *			  参数 设备MAC地址缓冲长度 目前不小于8字节 以后可能有调整
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardGetDeviceMacAddress(LotusHandle  nDeviceHandle, unsigned char * parrMacAddress,  unsigned int unMacAddressLength);
	/**
	 * 获取芯片序列号
	 * 
	 * @param parrMcuSerialNo 
	 *			  参数 序列号缓冲地址
	 * @param unMcuSerialNoLength 
	 *			  参数 序列号缓冲长度 目前不小于12字节 以后可能有调整
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardGetMcuSerailNo(LotusHandle  nDeviceHandle, char * parrMcuSerialNo,  unsigned int unMcuSerialNoLength);

	/**
	 * 获取二代身份证卡片ID
	 * 
 	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pstrTwoGenerationID 
	 *			  参数 二代身份证ID缓冲地址
	 * @param unTwoGenerationIDLength 
	 *			  参数 二代身份证ID缓冲长度 
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardGetTwoGenerationIDCardNo(LotusHandle  nDeviceHandle, char * pstrTwoGenerationID,  unsigned int unTwoGenerationIDLength);

	/**
	* 获取二代身份证卡片DN码
	*
	* @param nDeviceHandle
	*            设备句柄
	* @param pstrDnNo
	*			  参数 DN码缓冲地址
	* @param unDnNoLength
	*			  参数 DN码缓冲长度
	* @return true = 成功
	*/
	BOOL  WINAPI LotusCardGetTwoGenerationIDDnNo(LotusHandle  nDeviceHandle, char * pstrDnNo, unsigned int  unDnNoLength);
	/**
	* 设置射频开关
 	* @param nDeviceHandle
	*            设备句柄
	* @param ucRfOnOff
	*            1=打开射频信号 0= 关闭射频信号
	* @return true = 成功
	*/
	BOOL  WINAPI LotusCardSetRfOnOff(LotusHandle  nDeviceHandle, unsigned char ucRfOnOff);

	/**
	 * 设置LED状态
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucLedStatus 
	 *			  参数 0=关闭 1=绿灯亮 2=红灯亮 3=两个灯都亮
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardSetLedStatus(LotusHandle  nDeviceHandle, unsigned char ucLedStatus);

	/**
	 * 复位射频IC
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardResetRfIc(LotusHandle  nDeviceHandle);

	/**
	 * 设置服务器IP PORT
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param unIpAddress 
	 *			  参数 IP地址
	 * @param usPort 
	 *			  参数 端口
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardSetServerIpPort(LotusHandle  nDeviceHandle, unsigned int unIpAddress, unsigned short usPort);

	/**
	 * 获取服务器IP PORT
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param punIpAddress 
	 *			  参数 IP地址
	 * @param pusPort 
	 *			  参数 端口
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardGetServerIpPort(LotusHandle  nDeviceHandle, unsigned int * punIpAddress, unsigned short * pusPort);

	/**
	 * 根据编码获取性别字符串
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pszSexCode 
	 *			  参数 性别编码 0 未知 2 女 1 男 9 未说明
	 * @param pszSexBuffer 
	 *			  结果 存放返回字符串
	 * @param nSexBufferLength 
	 *			  参数 buffer长度
	 * @return true = 成功
	 */
	void  WINAPI LotusCardGetTwoIdSexByCode(LotusHandle  nDeviceHandle, char * pszSexCode, char * pszSexBuffer, int nSexBufferLength);
	/**
	 * 根据编码获取民族字符串
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pszNationCode 
	 *			  参数 民族编码
	 * @param pszNationBuffer 
	 *			  结果 存放返回字符串
	 * @param nNationBufferLength 
	 *			  参数 buffer长度
	 * @return true = 成功
	 */
	void  WINAPI LotusCardGetTwoIdNationByCode(LotusHandle  nDeviceHandle, char * pszNationCode, char * pszNationBuffer, int nNationBufferLength);

	/**
	 * b64编码
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pSrcDataBuffer 
	 *			  参数 源数据缓冲
	 * @param nSrcDataLen 
	 *			  参数 源数据缓冲长度
	 * @param pDestDataBuffer 
	 *			  参数 目标Buffer
	 * @param nDestDataLen 
	 *			  参数 目标Buffer长度
	 * @return true = 成功
	 */
	void  WINAPI LotusCardBase64Encode(LotusHandle  nDeviceHandle, unsigned char* pSrcDataBuffer, int nSrcDataLen, unsigned char* pDestDataBuffer, int nDestDataLen);

	/**
	 * 获取b64编码后长度
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pSrcDataBuffer 
	 *			  参数 源数据缓冲
	 * @param nSrcDataLen 
	 *			  参数 源数据缓冲长度
	 */
	int WINAPI LotusCardGetEncodeNewLen(LotusHandle  nDeviceHandle, const char * pSrcDataBuffer, int nSrcDataLen);

	/**
	 * b64解码
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pSrcDataBuffer 
	 *			  参数 源数据缓冲
	 * @param nSrcDataLen 
	 *			  参数 源数据缓冲长度
	 * @param pDestDataBuffer 
	 *			  参数 目标Buffer
	 * @param nDestDataLen 
	 *			  参数 目标Buffer长度
	 * @return true = 成功
	 */
	void  WINAPI LotusCardBase64Decode(LotusHandle  nDeviceHandle, unsigned char* pSrcDataBuffer, int nSrcDataLen, unsigned char* pDestDataBuffer, int nDestDataLen);

	/**
	 * 获取b64解码后长度
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pSrcDataBuffer 
	 *			  参数 源数据缓冲
	 * @param nSrcDataLen 
	 *			  参数 源数据缓冲长度
	 */
	int WINAPI LotusCardGetDecodeNewLen(LotusHandle  nDeviceHandle, const char* pSrcDataBuffer, int nSrcDataLen);

	/**
	 * 获取二代证用随机数
	 * 
	 * @param pszRandom 
	 *			  参数 随机数缓冲
	 * @param unRandomLength 
	 *			  参数 随机数缓冲长度
	 */
	void WINAPI LotusCardGetIdRandom(unsigned char * pszRandom, unsigned int unRandomLength);

	/**
	 * 保存日志
	 * 
	 * @param pszLogFile 
	 *			  参数 日志文件
	 * @param pszLog 
	 *			  参数 日志内容
	 */
	void WINAPI LotusCardSaveLog(char * pszLogFile, char * pszLog);

	/**
	 * 获取USB设备数量
	 * 
	 * @param nVID 
	 *			  参数 设备VID
	 * @param nPID 
	 *			  参数 设备PID
	 */
	int  WINAPI LotusCardGetUsbDeviceCount(int nVID, int nPID);


	/**
	 * 获取MCU配置
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pMcuConfig 
	 *			  参数 MCU配置数据地址  0=禁止 非0=允许
	 * @param unMcuConfigLegnth 
	 *			  参数 MCU配置数据长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardGetMcuConfig(LotusHandle  nDeviceHandle, unsigned char * pMcuConfig, unsigned int unMcuConfigLegnth);

	/**
	 * 获取ISP选项
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pIspOption 
	 *			  参数 选项数据地址  0=禁止 非0=允许
	 * @param unIspOptionLegnth 
	 *			  参数 选型数据长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardGetIspOption(LotusHandle  nDeviceHandle, unsigned char * pIspOption, unsigned int unIspOptionLegnth);

	/**
	 * 设置ISP选项
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pIspOption 
	 *			  参数 选项数据地址 0=禁止 非0=允许
	 * @param unIspOptionLegnth 
	 *			  参数 选型数据长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardSetIspOption(LotusHandle  nDeviceHandle, unsigned char * pIspOption, unsigned int unIspOptionLegnth);

	/**
	 * 获取ntag版本 21x支持
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pNtagVersionBuffer 
	 *			  参数 版本信息缓冲地址
	 * @param unNtagVersionBuffeLegnth 
	 *			  参数 版本信息缓冲长度
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardNtagGetVersion(LotusHandle  nDeviceHandle, unsigned char * pNtagVersionBuffer, unsigned int unNtagVersionBuffeLegnth);

	/**
	 * ntag密码验证 21x支持
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pNtagPasswordBuffer 
	 *			  参数 密码缓冲地址
	 * @param unNtagPasswordBuffeLegnth 
	 *			  参数 密码缓冲长度 默认4字节
	 * @return true = 成功
	 */
	BOOL  WINAPI LotusCardNtagPwdAuth(LotusHandle  nDeviceHandle, unsigned char * pNtagPasswordBuffer, unsigned int unNtagPasswordBuffeLegnth);

	/**
	 * 设置7816插槽索引
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucIndex 
	 *			  参数 插槽索引0=大卡 1,2,3=小卡
	 */
	BOOL  WINAPI LotusCardSetSamSlotIndex(LotusHandle  nDeviceHandle, unsigned char ucIndex);
	/**
	 * 设置7816上下电 仅对大卡座有效
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucPowerOnOff 
	 *			  参数 0=下电操作 1=上电操作
	 */
	BOOL  WINAPI LotusCardSetSamPowerOnOff(LotusHandle  nDeviceHandle, unsigned char ucPowerOnOff);

	/**
	* 设置7816 电压选择VSEL0
	*
	* @param nDeviceHandle
	*            设备句柄
	* @param ucIndex
	*			  参数 插槽索引0=大卡 1,2,3=小卡
	* @param ucSetLevel
	*			  参数 设置电平  1=高 0=低
	*/
	BOOL  WINAPI LotusCardSetSamVSel0(LotusHandle  nDeviceHandle, unsigned char ucIndex, unsigned char ucSetLevel);
	/**
	* 设置7816 电压选择VSEL0
	*
	* @param nDeviceHandle
	*            设备句柄
	* @param ucIndex
	*			  参数 插槽索引0=大卡 1,2,3=小卡
	* @param ucSetLevel
	*			  参数 设置电平  1=高 0=低
	*/
	BOOL  WINAPI LotusCardSetSamVSel1(LotusHandle  nDeviceHandle, unsigned char ucIndex, unsigned char ucSetLevel);

	/**
	 * 复位7816
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param tLotusCardParam
	 *            结果值 返回复位ATR信息
	 */
	BOOL  WINAPI LotusCardResetSam(LotusHandle  nDeviceHandle, LotusCardParamStruct* pLotusCardParam);

	/**
	 * 发送SAM APDU
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param tLotusCardParam
	 *            结果值 返回APDU执行结果
	 */
	BOOL  WINAPI LotusCardSendSamAPDU(LotusHandle  nDeviceHandle, LotusCardParamStruct* pLotusCardParam);

	/**
	* CPU卡根据名称选择文件或目录
	* @param nDeviceHandle
	*            设备句柄
	* @param pszDirOrFileName
	*           文件或目录名
	* @param pszResultBuffer
	*			返回结果BUFFER指针
	* @param unResultBufferLength
	*			返回结果BUFFER长度 256字节长
	* @return true = 成功
	*/
	BOOL  WINAPI LotusCardCpuCardSelectByName(LotusHandle  nDeviceHandle, char * pszDirOrFileName, char * pszResultBuffer, unsigned int * punResultBufferLength);


	/**
	* CPU卡读取二进制文件
	* @param nSfi
	*           文件标识
	* @param pszResultBuffer
	*			返回结果BUFFER指针
	* @param unResultBufferLength
	*			返回结果BUFFER长度 256字节长
	* @return true = 成功
	*/
	BOOL  WINAPI LotusCardCpuCardReadBinary(LotusHandle  nDeviceHandle, int nSfi, char * pszResultBuffer, unsigned int * punResultBufferLength);

	/**
	* 单DES
	* @param pszInData
	*           输入字符串
	* @param pszKey
	*			密钥
	* @param pszOutData
	*			输出字符串
	* @param unOutDataLength
	*			输出字符串长度
	* @param bDecrypt
	*			TRUE = 解密 FALSE =加密
	* @return true = 成功
	*/
	BOOL  WINAPI LotusCardDes(char * pszInData, char * pszKey, char * pszOutData, unsigned int unOutDataLength, BOOL bDecrypt);

	/**
	* 3DES
	* @param pszInData
	*           输入字符串
	* @param pszKey
	*			密钥
	* @param pszOutData
	*			输出字符串
	* @param unOutDataLength
	*			输出字符串长度
	* @param bDecrypt
	*			TRUE = 解密 FALSE =加密
	* @return true = 成功
	*/
	BOOL  WINAPI LotusCard3Des(char * pszInData, char * pszKey, char * pszOutData, unsigned int unOutDataLength, BOOL bDecrypt);

	/**
	* MAC计算
	* @param pszInitString
	*			初始字符串 PBOC是随机数 普通MAC是8个0字符串
	* @param pszInData
	*           输入字符串
	* @param pszKey
	*			密钥
	* @param pszOutData
	*			输出字符串
	* @param unOutDataLength
	*			输出字符串长度
	* @return true = 成功
	*/
	BOOL  WINAPI LotusCardMac(char * pszInitString, char * pszInData, char * pszKey, char * pszOutData, unsigned int unOutDataLength);

	/**
	 * 读写RF寄存器
	 * 
	 * @param nDeviceHandle
	 *            设备句柄	 
	 * @param 读写动作 
	 *			  参数 0=读 1=写
	 * @param ucRegister 
	 *			  参数 寄存器
	 * @param ucValue 
	 *			  参数 写的值 读没有意义
	 * @return 返回寄存器值
	 */
	unsigned char  WINAPI LotusCardReadWriteRfRegister(LotusHandle  nDeviceHandle, unsigned char ucReadWrite, unsigned char ucRegister, unsigned char ucValue);
	
	/**
	 * 执行字符串指令 指令由函数名+参数构成 结果根据不同函数进行相应解析
	 * 
	 * @param nDeviceHandle
	 *            设备句柄	 
	 * @param pStringCommand
	 *			  参数 指令字符串地址
	 * @param unCommandLength 
	 *			  参数 指令字符串长度
	 * @param pStringResult
	 *			  参数 结果字符串地址 
	 * @param unResultLength 
	 *			  参数 结果字符串长度
	 * @return 指令执行是否成功
	 */
	BOOL  WINAPI LotusCardExecStringCommand(LotusHandle  nDeviceHandle,  char * pStringCommand, unsigned int unCommandLength, char * pStringResult, unsigned int unResultLength);

	/**
	 * 设置MCU UART0 波特率 用于蓝牙设置操作
	 * 
	 * @param nDeviceHandle
	 *            设备句柄	 
	 * @param nBauldeRate
	 *			  参数 串口通信用波特率
	 * @return 指令执行是否成功
	 */
	BOOL  WINAPI LotusCardSetMcuUart0BaudeRate(LotusHandle  nDeviceHandle,  int nBauldeRate);
	/**
	 * 发送Mcu Uart0指令 通过USB 通道进行
	 * 
	 * @param nDeviceHandle
	 *            设备句柄	 
	 * @param pSendDataBuffer
	 *			  参数 发送数据缓冲
	 * @param nSendDataLength
	 *			  参数  发送数据长度
	 * @return 指令执行是否成功
	 */
	BOOL  WINAPI LotusCardSendCommand2McuUart0(LotusHandle  nDeviceHandle,  unsigned char * pSendDataBuffer, int nSendDataLength);
	/**
	 * 接收 Uart0返回值 通过USB 通道进行
	 * 
	 * @param nDeviceHandle
	 *            设备句柄	 
	 * @param pReceiveDataBuffer
	 *			  参数 接收数据缓冲
	 * @param pnReceiveDataBufferLength
	 *			  参数 接收数据缓冲长度 返回真实数据长度 
	 * @return 指令执行是否成功
	 */
	BOOL  WINAPI LotusCardReceiveResultOfMcuUart0(LotusHandle  nDeviceHandle, unsigned char * pReceiveDataBuffer, int * pnReceiveDataBufferLength);
	/**
	 * 设置二代证回调动作 用于处理指令与结果 提供给调用者 目前暂时都送NULL
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pLotusCardIdCallBack
	 *            回调函数地址
	 */
	void WINAPI LotusCardSetIdCallBack(LotusHandle  nDeviceHandle, LotusCardIdCallBack pLotusCardIdCallBack);

	/**
	 * 设置应用配置 包括IP 密码等一堆东西
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param psttAppConfig
	 *			  参数 应用配置结构体指针
	 * @return 指令执行是否成功
	 */
	BOOL WINAPI LotusCardSetAppConfig(LotusHandle  nDeviceHandle, AppConfigStruct * psttAppConfig);
	/**
	 * 获取应用配置 包括IP 密码等一堆东西
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param psttAppConfig
	 *			  参数 应用配置结构体指针
	 * @return 指令执行是否成功
	 */
	BOOL WINAPI LotusCardGetAppConfig(LotusHandle  nDeviceHandle, AppConfigStruct * psttAppConfig);
	/**
	* 设置串口服务器配置 包括IP 密码等一堆东西
	*
	* @param nDeviceHandle
	*            设备句柄
	* @param psttAppConfigE2s
	*			  参数 应用配置结构体指针
	* @return 指令执行是否成功
	*/
	BOOL WINAPI LotusCardSetAppConfigE2s(LotusHandle  nDeviceHandle, AppConfigE2sStruct * psttAppConfigE2s);
	/**
	* 获取串口服务器配置 包括IP 密码等一堆东西
	*
	* @param nDeviceHandle
	*            设备句柄
	* @param nDeviceHandle
	*            设备句柄
	* @param psttAppConfigE2s
	*			  参数 应用配置结构体指针
	* @return 指令执行是否成功
	*/
	BOOL WINAPI LotusCardGetAppConfigE2s(LotusHandle  nDeviceHandle, AppConfigE2sStruct * psttAppConfigE2s);
	/**
	 * 发送PS2键 模拟键盘输入动作 只处理发送 键盘与主机直接握手动作 MCU内部完成
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pKeyBuffer
	 *			  参数 按键缓冲 外部只送入通码 这个函数里面增加断码
	 * @param unKeyBufferLength
	 *			  参数 应用配置结构体指针
	 * @param punSendStatus
	 *			  参数 发送状态 0 表示成功 其他的以后定义
	 * @return 指令执行是否成功
	 */
	BOOL WINAPI LotusCardSendPs2Key(LotusHandle  nDeviceHandle, unsigned char * pKeyBuffer, unsigned int unKeyBufferLength, unsigned int * punSendStatus);
	/**
	 * 发送体彩按键
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param nKeyCode
	 *			  参数 体彩按键枚举值
	 * @param punSendStatus
	 *			  参数 发送状态 0 表示成功 其他的以后定义
	 * @return 指令执行是否成功
	 */
	BOOL WINAPI LotusCardSendTiCaiKey(LotusHandle  nDeviceHandle, int nKeyCode, unsigned int * punSendStatus);
	/**
	 * 获取打印机信息大小 
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param punMessageSize
	 *			  参数 里面填入信息大小 以便后续获取的时候使用
	 * @return 指令执行是否成功
	 */
	BOOL WINAPI LotusCardGetPrinterMessageSize(LotusHandle  nDeviceHandle, unsigned int * punMessageSize);
	/**
	 * 获取打印机信息
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pPrinterMessageBuffer
	 *			  参数 打印信息缓冲 实际里面放的是一堆ESC指令
	 * @param unBufferPos
	 *			  参数 偏移量  用于USB 等有包大小限制的场合
	 * @param punBufferLength
	 *			  参数 缓冲长度 实际的数据也在里面返回  不能大于255 主要考虑兼容早期代码
	 * @return 指令执行是否成功
	 */
	BOOL WINAPI LotusCardGetPrinterMessage(LotusHandle  nDeviceHandle, unsigned char * pPrinterMessageBuffer, unsigned int unBufferPos, unsigned int * punBufferLength);
	/**
	 * 获取所有打印机信息
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pPrinterMessageBuffer
	 *			  参数 打印信息缓冲 实际里面放的是一堆ESC指令
	 * @param punBufferLength
	 *			  参数 缓冲长度 实际的数据也在里面返回 
	 * @return 指令执行是否成功
	 */
	BOOL WINAPI LotusCardGetPrinterAllMessage(LotusHandle  nDeviceHandle, unsigned char * pPrinterMessageBuffer, unsigned int * punBufferLength);
	/**
	 * 清空打印机缓冲
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @return 指令执行是否成功
	 */
	BOOL WINAPI LotusCardClearPrinterBuffer(LotusHandle  nDeviceHandle);
	/**
	 * 发送数据到二维码阅读器上位机 这里模拟二维码阅读器动作
	 * 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param pPrinterMessageBuffer
	 *			  参数 打印信息缓冲 实际里面放的是一堆ESC指令
	 * @param unDataLength
	 *			  参数 数据长度 
	 * @return 指令执行是否成功
	 */
	BOOL WINAPI LotusCardSendData2QrReaderHost(LotusHandle  nDeviceHandle, unsigned char * pPrinterMessageBuffer, unsigned int unDataLength);
	/**
	 * 获取打印消息里面的文本 静态函数 无需送句柄
	 * 
	 * @param pPrinterMessageBuffer
	 *			  参数 打印信息缓冲 实际里面放的是一堆ESC指令
	 * @param unMessageBufferLength
	 *			  参数 缓冲长度 
	 * @param pTextBuffer
	 *			  参数 文本信息缓冲 
	 * @param punTextBufferLength
	 *			  参数 文本缓冲长度 实际的数据也在里面返回 
	 * @return 指令执行是否成功
	 */
	BOOL WINAPI LotusCardGetTextFromPrinterMessage(unsigned char * pPrinterMessageBuffer, unsigned int unMessageBufferLength,
		unsigned char * pTextBuffer, unsigned int * punTextBufferLength);
	/**
	 * 发送消息到打印机
	 * 
	 * @param pszDeviceName
	 *			  参数 设备名称
	 * @param pPrinterMessageBuffer
	 *			  参数 打印信息缓冲 实际里面放的是一堆ESC指令
	 * @param unMessageBufferLength
	 *			  参数 缓冲长度 
	 * @param pResultBuffer
	 *			  参数 结果缓冲
	 * @param punResultBufferLength
	 *			  参数 结果缓冲长度 
	 * @return 指令执行是否成功
	 */
	BOOL WINAPI LotusCardSendMessage2Printer(char * pszDeviceName, unsigned char * pPrinterMessageBuffer, unsigned int unMessageBufferLength, 
		unsigned char * pResultBuffer, unsigned int * punResultBufferLength);
	/**
	 * 设置继电器状态 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucRelayIndex 继电器索引 从0开始
	 * @param ucHighOrLow 1 = 拉高 0 = 拉低
	 * @param pszOperatePassword 操作密码 控制的时候 需要密码验证 暂时只用一个密码 以后再考虑是否一路一个密码
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardSetRelayStatus(LotusHandle  nDeviceHandle, unsigned char ucRelayIndex, unsigned char ucHighOrLow, char * pszOperatePassword);
	/**
	 * 获取继电器状态 
	 * @param nDeviceHandle
	 *            设备句柄
	 * @param ucRelayIndex 继电器索引 从0开始
	 * @param pucHighOrLow 1 = 拉高 0 = 拉低
	 * @return true = 成功
	 */
	BOOL WINAPI LotusCardGetRelayStatus(LotusHandle  nDeviceHandle, unsigned char ucRelayIndex, unsigned char  * pucHighOrLow);
	/**
	* 设置继电器初始状态
	* @param nDeviceHandle
	*            设备句柄
	* @param pRelayInitStatus 继电器初始状态 16字节
	* @param pszOperatePassword 操作密码 控制的时候 需要密码验证 暂时只用一个密码 以后再考虑是否一路一个密码 以太网通道不能设置
	* @param nResetInitStatusTimeLength 恢复初始状态时间长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardSetRelayInitStatus(LotusHandle  nDeviceHandle, unsigned char * pRelayInitStatus, char * pszOperatePassword, int nResetInitStatusTimeLength);
	/**
	* 获取继电器初始状态
	* @param nDeviceHandle
	*            设备句柄
	* @param pRelayInitStatus 继电器初始状态 16字节
	* @param pszOperatePassword 操作密码 控制的时候 需要密码验证 暂时只用一个密码 以后再考虑是否一路一个密码 以太网通道不能读取
	* @param pnResetInitStatusTimeLength 恢复初始状态时间长度地址
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetRelayInitStatus(LotusHandle  nDeviceHandle, unsigned char * pRelayInitStatus, char * pszOperatePassword, int * pnResetInitStatusTimeLength);
	/**
	* 获取中石化卡片信息
	* @param nDeviceHandle
	*            设备句柄
	* @param pSinopecCard 结构信息
	* @param pCardPassword 卡片密码
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetSinopecCardInfo(LotusHandle  nDeviceHandle, SinopecCardStruct * pSinopecCard, char * pCardPassword);
	/**
	* 获取中石油卡片信息
	* @param nDeviceHandle
	*            设备句柄
	* @param pSinopecCard 结构信息 使用和中石化同样的结构
	* @param pCardPassword 卡片密码
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetPetroChinaCardInfo(LotusHandle  nDeviceHandle, SinopecCardStruct * pSinopecCard, char * pCardPassword); 
	/**
	* 获取充电电压
	* @param nDeviceHandle
	*            设备句柄
	* @param pVoltage 充电电压
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetChargeVoltage(LotusHandle  nDeviceHandle, float * pVoltage);
	/**
	* 获取充电状态 返回一个枚举值 这样方便和具体的充电IC 隔离
	* @param nDeviceHandle
	*            设备句柄
	* @param pChargeStatus 返回一个枚举值
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetChargeStatus(LotusHandle  nDeviceHandle, unsigned char * pChargeStatus);
	/**
	* 设置充电电流 80ma 450 ma IO口拉高拉低
	* @param nDeviceHandle
	*            设备句柄
	* @param unChargeCurrent 充电电流 80ma 450 ma IO口拉高拉低
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardSetChargeCurrent(LotusHandle  nDeviceHandle, unsigned int unChargeCurrent);
	/**
	* 获取充电电流 80ma 450 ma IO口拉高拉低
	* @param nDeviceHandle
	*            设备句柄
	* @param punChargeCurrent 充电电流 80ma 450 ma IO口拉高拉低
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetChargeCurrent(LotusHandle  nDeviceHandle, unsigned int * punChargeCurrent);
	/**
	* 获取USB 是否供电
	* @param nDeviceHandle
	*            设备句柄
	* @param punUsbCharge 0=电池供电 1=USB 供电
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetUsbCharge(LotusHandle  nDeviceHandle, unsigned int * punUsbCharge);
	/**
	* 复位单片机 仅处理 非以太网通道
	* @param nDeviceHandle
	*            设备句柄
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardResetMcu(LotusHandle  nDeviceHandle);
	/**
	* 用于设置BKP值 便于复位后进入ISP IAP 状态
	* @param nDeviceHandle
	*            设备句柄
	* @param punUsbCharge 0=电池供电 1=USB 供电
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardSetMcuBkp(LotusHandle  nDeviceHandle, unsigned char ucBkpValue);
	/**
	* 用于获取调试BKP值 
	* @param nDeviceHandle
	*            设备句柄
	* @param punBkpValue 返回BKP 值
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetMcuDebugBkp(LotusHandle  nDeviceHandle, unsigned int * punBkpValue);
	/**
	* 获取固件编译时间
	* @param nDeviceHandle
	*            设备句柄
	* @param pszBuildTime 固件编译时间
	* @param unBuildTimeLength 固件编译时间缓冲长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetFirewareBuildTime(LotusHandle  nDeviceHandle, char * pszBuildTime, unsigned int unBuildTimeLength);
	/**
	* 获取库编译时间
	* @param nDeviceHandle
	*            设备句柄
	* @param pszBuildTime 库编译时间
	* @param unBuildTimeLength 库编译时间缓冲长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetLibBuildTime(LotusHandle  nDeviceHandle, char * pszBuildTime, unsigned int unBuildTimeLength);
	/**
	* 读取USB数据，用于获取USB主动发过来的数据
	* @param nDeviceHandle
	*            设备句柄
	* @param pszData 数据地址
	* @param unDataLength 数据长度
	* @param unTimeOut 超时
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardReadUsbData(LotusHandle  nDeviceHandle, unsigned char * pszData, unsigned int unDataLength, unsigned int unTimeOut);
	/**
	* 写USB数据
	* @param nDeviceHandle
	*            设备句柄
	* @param pszData 数据地址
	* @param unDataLength 数据长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardWriteUsbData(LotusHandle  nDeviceHandle, unsigned char * pszData, unsigned int unDataLength);
	/**
	* 获取SDT 指令
	* @param nDeviceHandle
	*            设备句柄
	* @param pszCmdData 指令数据地址
	* @param punCmdDataLength 指令数据长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetSdtCmd(LotusHandle  nDeviceHandle, unsigned char * pszCmdData, unsigned int * punCmdDataLength);
	/**
	* 清除SDT 指令 避免多次动作
	* @param nDeviceHandle
	*            设备句柄
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardClearSdtCmd(LotusHandle  nDeviceHandle);
	/**
	* 保存安全模块结果到JPEG 缓冲
	* @param nDeviceHandle
	*            设备句柄
	* @param ucValue 0=不保存 1=保存 不处理解码
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardSaveSamvResult2JpegBuffer(LotusHandle  nDeviceHandle, unsigned char ucValue);
	/**
	* 设置安全模块结果标志 用于后续透传数据
	* @param nDeviceHandle
	*            设备句柄
	* @param unSamvResultLength 安全模块结果长度
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardSetSamvResultTag(LotusHandle  nDeviceHandle, unsigned int unSamvResultLength);
	/**
	* 获取安全模块电源状态
	* @param nDeviceHandle
	*            设备句柄
	* @param ucValue 1 = 上电 0= 下电 实际动作在MCU内部是反的
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetSamvPowerStatus(LotusHandle  nDeviceHandle, unsigned int * punValue);
	/**
	* 设置安全模块电源状态
	* @param nDeviceHandle
	*            设备句柄
	* @param ucValue 1 = 上电 0= 下电 实际动作在MCU内部是反的
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardSetSamvPowerStatus(LotusHandle  nDeviceHandle, unsigned int unValue);
	/**
	* 获取安全模块最后apdu I2C数据
	* @param nDeviceHandle
	*            设备句柄
	* @param tLotusCardParam 参数（读写缓冲）
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetSamvLastApdu(LotusHandle  nDeviceHandle, LotusCardParamStruct* pLotusCardParam);
	/**
	* 获取安全模块最后apdu结果 I2C数据
	* @param nDeviceHandle
	*            设备句柄
	* @param tLotusCardParam 参数（读写缓冲）
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetSamvLastApduResult(LotusHandle  nDeviceHandle, LotusCardParamStruct* pLotusCardParam);
	/**
	* 获取SDT数据达到的状态
	* @param nDeviceHandle
	*            设备句柄
	* @param punValue 参数 0=没有请求 1请求不带指纹数据 2=请求带指纹数据
	* @return true = 成功
	*/
	BOOL WINAPI LotusCardGetSdtMessageArrivedStatus(LotusHandle  nDeviceHandle, unsigned int * punValue);

#ifdef __cplusplus
}
#endif

#endif//__LOTUS_CARD_DRIVER_H__
