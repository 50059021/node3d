//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once /* ClientNetWork.h */
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "NetWork.h"
#include "TSingleton.h"
#include "../../Protocol/prodef.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define NETWORK CClientNetWork::getInstance()
#define MAX_WS_BUF_LEN	819200
#define MAX_EXSENDBUF_SIZE 7024
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef void (*WsProtocolCore)(BYTE,const unsigned char*, int);
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class CClientNetWork : public CNetWork, public TSingleton<CClientNetWork>
{
public:
	CClientNetWork();
	virtual ~CClientNetWork();
	// ----
	bool		SetProtocolCore	(WsProtocolCore pc);
	bool		send			(void* buf);
	virtual int ProtocolCore	(const unsigned char* buf, int len);
	// ----
	WsProtocolCore wsProtocolCore;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------