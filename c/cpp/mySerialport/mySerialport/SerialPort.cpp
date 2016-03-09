//////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, 华中科技大学tickTick Group  （版权声明）
/// All rights reserved.
/// 
/// @file    SerialPort.cpp  
/// @brief   串口通信类的实现文件
///
/// 本文件为串口通信类的实现代码
///
/// @version 1.0   
/// @author  卢俊  
/// @E-mail：lujun.hust@gmail.com
/// @date    2010/03/19
/// 
///
///  修订说明：
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SerialPort.h"
#include <process.h>
#include <iostream>

#include <winsock.h>
#include <iostream>
#include <string>
#include <mysql.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS 1

using namespace std;

char receivecode;
struct tm * local;
time_t tin;
time_t tout;
int flag;

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libmysql.lib")
/** 线程退出标志 */ 
bool CSerialPort::s_bExit = false;
/** 当串口无数据时,sleep至下次查询间隔的时间,单位:秒 */ 
const UINT SLEEP_TIME_INTERVAL = 5;
int i=0;
char classpn[4];
char temp[5];
char temps;
char fans;
char hots;
char DTH[3];
char lightn[4];
char lights;
char ctrl;
char cend;
unsigned char writechar[5];

CSerialPort::CSerialPort(void)
: m_hListenThread(INVALID_HANDLE_VALUE)
{
	m_hComm = INVALID_HANDLE_VALUE;
	m_hListenThread = INVALID_HANDLE_VALUE;

	InitializeCriticalSection(&m_csCommunicationSync);

}

CSerialPort::~CSerialPort(void)
{
	CloseListenTread();
	ClosePort();
	DeleteCriticalSection(&m_csCommunicationSync);
}

bool CSerialPort::InitPort( UINT portNo /*= 1*/,UINT baud /*= CBR_9600*/,char parity /*= 'N'*/,
						    UINT databits /*= 8*/, UINT stopsbits /*= 1*/,DWORD dwCommEvents /*= EV_RXCHAR*/ )
{

	/** 临时变量,将制定参数转化为字符串形式,以构造DCB结构 */ 
	char szDCBparam[50];
	sprintf_s(szDCBparam, "baud=%d parity=%c data=%d stop=%d", baud, parity, databits, stopsbits);

	/** 打开指定串口,该函数内部已经有临界区保护,上面请不要加保护 */ 
	if (!openPort(portNo))
	{
		return false;
	}

	/** 进入临界段 */ 
	EnterCriticalSection(&m_csCommunicationSync);

	/** 是否有错误发生 */ 
	BOOL bIsSuccess = TRUE;

    /** 在此可以设置输入输出的缓冲区大小,如果不设置,则系统会设置默认值.
	 *  自己设置缓冲区大小时,要注意设置稍大一些,避免缓冲区溢出
	 */
	/*
	if (bIsSuccess )
	{
		bIsSuccess = SetupComm(m_hComm,10,10);
	}
	*/

	/** 设置串口的超时时间,均设为0,表示不使用超时限制 */
	COMMTIMEOUTS  CommTimeouts;
	CommTimeouts.ReadIntervalTimeout         = 0;
	CommTimeouts.ReadTotalTimeoutMultiplier  = 0;
	CommTimeouts.ReadTotalTimeoutConstant    = 0;
	CommTimeouts.WriteTotalTimeoutMultiplier = 0;
	CommTimeouts.WriteTotalTimeoutConstant   = 0; 
	if ( bIsSuccess)
	{
		bIsSuccess = SetCommTimeouts(m_hComm, &CommTimeouts);
	}

	DCB  dcb;
	if ( bIsSuccess )
	{
		// 将ANSI字符串转换为UNICODE字符串
		DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, szDCBparam, -1, NULL, 0);
		wchar_t *pwText = new wchar_t[dwNum] ;
		if (!MultiByteToWideChar (CP_ACP, 0, szDCBparam, -1, pwText, dwNum))
		{
			bIsSuccess = TRUE;
		}

		/** 获取当前串口配置参数,并且构造串口DCB参数 */ 
		bIsSuccess = GetCommState(m_hComm, &dcb) && BuildCommDCB(pwText, &dcb) ;
		/** 开启RTS flow控制 */ 
		dcb.fRtsControl = RTS_CONTROL_ENABLE; 

		/** 释放内存空间 */ 
		delete [] pwText;
	}

	if ( bIsSuccess )
	{
		/** 使用DCB参数配置串口状态 */ 
		bIsSuccess = SetCommState(m_hComm, &dcb);
	}
		
	/**  清空串口缓冲区 */
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	/** 离开临界段 */ 
	LeaveCriticalSection(&m_csCommunicationSync);

	return bIsSuccess==TRUE;
}

bool CSerialPort::InitPort( UINT portNo ,const LPDCB& plDCB )
{
	/** 打开指定串口,该函数内部已经有临界区保护,上面请不要加保护 */ 
	if (!openPort(portNo))
	{
		return false;
	}
	
	/** 进入临界段 */ 
	EnterCriticalSection(&m_csCommunicationSync);

	/** 配置串口参数 */ 
	if (!SetCommState(m_hComm, plDCB))
	{
		return false;
	}

	/**  清空串口缓冲区 */
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	/** 离开临界段 */ 
	LeaveCriticalSection(&m_csCommunicationSync);

	return true;
}

void CSerialPort::ClosePort()
{
	/** 如果有串口被打开，关闭它 */
	if( m_hComm != INVALID_HANDLE_VALUE )
	{
		CloseHandle( m_hComm );
		m_hComm = INVALID_HANDLE_VALUE;
	}
}

bool CSerialPort::openPort( UINT portNo )
{
	/** 进入临界段 */ 
	EnterCriticalSection(&m_csCommunicationSync);

	/** 把串口的编号转换为设备名 */ 
    char szPort[50];
	sprintf_s(szPort, "COM%d", portNo);

	/** 打开指定的串口 */ 
	m_hComm = CreateFileA(szPort,		                /** 设备名,COM1,COM2等 */ 
						 GENERIC_READ | GENERIC_WRITE,  /** 访问模式,可同时读写 */   
						 0,                             /** 共享模式,0表示不共享 */ 
					     NULL,							/** 安全性设置,一般使用NULL */ 
					     OPEN_EXISTING,					/** 该参数表示设备必须存在,否则创建失败 */ 
						 0,    
						 0);    

	/** 如果打开失败，释放资源并返回 */ 
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		LeaveCriticalSection(&m_csCommunicationSync);
		return false;
	}

	/** 退出临界区 */ 
	LeaveCriticalSection(&m_csCommunicationSync);

	return true;
}

bool CSerialPort::OpenListenThread()
{
	/** 检测线程是否已经开启了 */ 
	if (m_hListenThread != INVALID_HANDLE_VALUE)
	{
		/** 线程已经开启 */ 
		return false;
	}

	s_bExit = false;
	/** 线程ID */ 
	UINT threadId;
	/** 开启串口数据监听线程 */ 
	m_hListenThread = (HANDLE)_beginthreadex(NULL, 0, ListenThread, this, 0, &threadId);
	if (!m_hListenThread)
	{
		return false;
	}
	/** 设置线程的优先级,高于普通线程 */ 
	if (!SetThreadPriority(m_hListenThread, THREAD_PRIORITY_ABOVE_NORMAL))
	{
		return false;
	}

	return true;
}

bool CSerialPort::CloseListenTread()
{	
	if (m_hListenThread != INVALID_HANDLE_VALUE)
	{
		/** 通知线程退出 */ 
		s_bExit = true;

		/** 等待线程退出 */ 
		Sleep(10);

		/** 置线程句柄无效 */ 
		CloseHandle( m_hListenThread );
		m_hListenThread = INVALID_HANDLE_VALUE;
	}
	return true;
}

UINT CSerialPort::GetBytesInCOM()
{
	DWORD dwError = 0;	/** 错误码 */ 
	COMSTAT  comstat;   /** COMSTAT结构体,记录通信设备的状态信息 */ 
	memset(&comstat, 0, sizeof(COMSTAT));

	UINT BytesInQue = 0;
	/** 在调用ReadFile和WriteFile之前,通过本函数清除以前遗留的错误标志 */ 
	if ( ClearCommError(m_hComm, &dwError, &comstat) )
	{
		BytesInQue = comstat.cbInQue; /** 获取在输入缓冲区中的字节数 */ 
	}

	return BytesInQue;
}

UINT WINAPI CSerialPort::ListenThread( void* pParam )
{
	/** 得到本类的指针 */ 
	CSerialPort *pSerialPort = reinterpret_cast<CSerialPort*>(pParam);

	// 线程循环,轮询方式读取串口数据
	while (!pSerialPort->s_bExit) 
	{
		UINT BytesInQue = pSerialPort->GetBytesInCOM();
		/** 如果串口输入缓冲区中无数据,则休息一会再查询 */ 
		if ( BytesInQue == 0 )
		{
			Sleep(SLEEP_TIME_INTERVAL);
			continue;
		}

		/** 读取输入缓冲区中的数据并输出显示 */
		char cRecved = 0x00;

		do
		{
			cRecved = 0x00;
			if(pSerialPort->ReadChar(cRecved) == true)
			{   
				receivecode = cRecved;
				std::cout << receivecode<<endl;
				while(1)
				{
					//必备的一个数据结构
					MYSQL mydata;
 
					//初始化数据库
					if(0==mysql_library_init(0,NULL,NULL))
					{
					cout<<"mysql_library_init() succeed"<<endl;
					}
					else
					{
					cout<<"mysql_library_init() failed"<<endl;
					return -1;
					}
 
					//初始化数据结构
					if(NULL!=mysql_init(&mydata))
					{
					cout<<"mysql_init() succeed"<<endl;
					}
					else
					{
					cout<<"mysql_init() failed"<<endl;
					return -1;
					}
 
 
					//在连接数据库之前，设置额外的连接选项
					//可以设置的选项很多，这里设置字符集，否则无法处理中文
					if(0==mysql_options(&mydata,MYSQL_SET_CHARSET_NAME,"gbk"))
					{
					cout<<"mysql_options() succeed"<<endl;
					}
					else
					{
					cout<<"mysql_options() failed"<<endl;
					return -1;
					}
 
 
					//连接数据库
					if(NULL!=mysql_real_connect(&mydata,"localhost","root","123456","car",3306,NULL,0))
					//这里的地址，用户名，密码，端口可以根据自己本地的情况更改
					{
					cout<<"mysql_real_connect() succeed"<<endl;
					}
					else
					{
					cout<<"mysql_real_connect() failed"<<endl;
					return -1;
					}
 
 
					//sql字符串
					string sqlstr;
					//向表中插入数据
					if(receivecode == '1' && flag)
					{
						tin = time(NULL);
						local = localtime(&tin);
						cout<<"当前时间是"<<local->tm_mon<<"月"<<local->tm_mday<<"日"<<local->tm_hour<<"时"<<local->tm_min<<"分"<<local->tm_sec<<"秒"<<endl;
						cout<<"车在车位！"<<endl;
						sqlstr ="UPDATE stop_car SET car_number='晋M30231'，start_time=";								 
						sqlstr = (char)tin;
						sqlstr =" WHERE stop_number='10001';";
						if(0==mysql_query(&mydata,sqlstr.c_str()))
						{
						cout<<"mysql_query() insert data succeed"<<endl;
						}
						else
						{
						cout<<"mysql_query() insert data failed"<<endl;
						mysql_close(&mydata);
						return -1;
						}
						flag = 0;
					}
					if(receivecode == '1')
					{
						tin = time(NULL);
						local = localtime(&tin);
						cout<<"当前时间是"<<local->tm_mon<<"月"<<local->tm_mday<<"日"<<local->tm_hour<<"时"<<local->tm_min<<"分"<<local->tm_sec<<"秒"<<endl;
						cout<<"车在车位！"<<endl;						
					}
					if(receivecode == '0' && !flag)
					{	 
						flag = 1;
						tout = time(NULL);
						local = localtime(&tout);
						cout<<"当前时间是"<<local->tm_mon<<"月"<<local->tm_mday<<"日"<<local->tm_hour<<"时"<<local->tm_min<<"分"<<local->tm_sec<<"秒"<<endl;
						cout<<"车位为空！"<<endl;
						sqlstr ="UPDATE leave_car SET car_number='晋M30231'，leave_time=";								
						sqlstr = (char)tout;
						sqlstr =" WHERE stop_number='10001';";
						if(0==mysql_query(&mydata,sqlstr.c_str()))
						{
						cout<<"mysql_query() insert data succeed"<<endl;
						}
						else
						{
						cout<<"mysql_query() insert data failed"<<endl;
						mysql_close(&mydata);
						return -1;
						}
					}
					if(receivecode == '0')
					{
						tout = time(NULL);
						local = localtime(&tout);
						cout<<"当前时间是"<<local->tm_mon<<"月"<<local->tm_mday<<"日"<<local->tm_hour<<"时"<<local->tm_min<<"分"<<local->tm_sec<<"秒"<<endl;
						cout<<"车位为空！"<<endl;
					}
					mysql_server_end();
					break;
				}
				continue;
			}
		}while(--BytesInQue);
	}

	return 0;
}

bool CSerialPort::ReadChar( char &cRecved )
{
	BOOL  bResult     = TRUE;
	DWORD BytesRead   = 0;
	if(m_hComm == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	/** 临界区保护 */ 
	EnterCriticalSection(&m_csCommunicationSync);

	

	/** 从缓冲区读取一个字节的数据 */ 
	bResult = ReadFile(m_hComm, &cRecved, 1, &BytesRead, NULL);
	if ((!bResult))
	{ 
		/** 获取错误码,可以根据该错误码查出错误原因 */ 
		DWORD dwError = GetLastError();

		/** 清空串口缓冲区 */ 
		PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_RXABORT);
		LeaveCriticalSection(&m_csCommunicationSync);

		return false;
	}
	/** 离开临界区 */ 
	LeaveCriticalSection(&m_csCommunicationSync);

	return (BytesRead == 1);

}

bool CSerialPort::WriteData( unsigned char* pData, unsigned int length )
{
	BOOL   bResult     = TRUE;
	DWORD  BytesToSend = 0;
	if(m_hComm == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	/** 临界区保护 */ 
	EnterCriticalSection(&m_csCommunicationSync);

	/** 向缓冲区写入指定量的数据 */ 
	bResult = WriteFile(m_hComm, pData, length, &BytesToSend, NULL);
	if (!bResult)  
	{
		DWORD dwError = GetLastError();
		/** 清空串口缓冲区 */ 
		PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_RXABORT);
		LeaveCriticalSection(&m_csCommunicationSync);

		return false;
	}

	/** 离开临界区 */ 
	LeaveCriticalSection(&m_csCommunicationSync);

	return true;
}


