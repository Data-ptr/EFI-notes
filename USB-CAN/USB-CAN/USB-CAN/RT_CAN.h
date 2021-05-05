#pragma once
#include "rt_com.h"

//���CAN��Ϣ�е�ch����Ϊ0xff����������������ID������Ϊ��ͨID-------------------------//
#define CAN_RESET_ID		0x01FFFEc0		//ID��ʼ��
#define CAN_ABOM_ID			0x01fffEb0		//�Զ����߹���
#define CAN_ART_ID			0x01fffEa0		//�Զ��ط�
#define CAN_FILTER_BASE_ID	0x01fffEe0		//������
#define CAN_BAUD_ID			0x01fffEd0		//CAN������
#define CAN_INIT_FLASH_ID	0x01fffEff		//�ָ���������

#define CAN_FILTER_ID(x)	(CAN_FILTER_BASE_ID + (x))	//������ID����14�������ù�����
#define CAN_FILTER_ENABLE   0x80000000		//ʹ�ܹ�����

#define MAX_CAN_BAUD		1000000			//���֧�ֵ�CAN������
#define CAN_CONFIG_CHANNEL	0xff			//CAN������ͨ��
#define FILTER_ID_MASK		0x0000000f		//������ID����
#define ENABLE_MASK			0x80000000		//ʹ������
#define DISABLE_MASK		0				//ʧ������

typedef enum {STANDARD_FORMAT = 0, EXTENDED_FORMAT} CAN_FORMAT;		//CAN���������ݸ�ʽ--��׼֡����չ֡
typedef enum {DATA_FRAME = 0, REMOTE_FRAME}         CAN_FRAME;		//CAN������֡��ʽ--����֡��Զ��֡
typedef enum
{
	CAN_ERR_TRANS = 0,		//�������
	CAN_OK,					//û�д���
	CAN_ERR_ACK,			//û�з���Ӧ��
	CAN_ERR_CHANNEL,		//CHANNEL����
	CAN_ERR_PARAM,			//��������
	CAN_ERR_TIMEOUT			//���ճ�ʱ
}CAN_ERROR;

//CAN��Ϣ�ṹ��
typedef struct  {
	DWORD id;                 // 29 λID                             
	BYTE  data[8];            // ������                                      
	BYTE  len;                // �����򳤶�
	BYTE  ch;                 // ͨ���������������������������ݰ�(0xff)����ͨ���ݰ�(����)
	BYTE  format;             // ���ݸ�ʽ����׼֡����չ֡
	BYTE  type;               // ֡��ʽ������֡��Զ��֡
}  CAN_msg;

class RT_CAN :
	public RT_COM
{
public:
	RT_CAN(void);
	~RT_CAN(void);

	CAN_ERROR SetConfigValue(DWORD dwID, void *pValueBuf, DWORD *pdwLen, DWORD dwTimeOut);
	CAN_ERROR GetConfigValue(DWORD dwID, void *pValueBuf, DWORD *pdwLen, DWORD dwTimeOut);
	CAN_ERROR SendCANMessage(CAN_msg *pMsg, DWORD dwTimeout = INFINITE);
	CAN_ERROR RecvCANMessage(CAN_msg *pMsg, DWORD dwTimeout = INFINITE);

	virtual void OnRecvPackage(const BYTE * byBuf, DWORD dwLen);
	virtual DWORD GetConfigDataLen(DWORD dwID);

protected:
	CAN_ERROR SendConfigData(DWORD dwID, void *pBufData, DWORD dwBufLen, DWORD dwTimeout);
	CAN_ERROR RequestConfigData(DWORD dwID, DWORD dwTimeout);

	HANDLE m_hConfigEvnet;
	HANDLE m_hRecvMsgEvnet;

	CAN_msg m_CANConfigMsg;
	CAN_msg m_CANRecvMsg;
};
