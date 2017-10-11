/************************************************************************/
/* �������ӷ�������manager                                                */
/************************************************************************/


#ifndef CONNECTMANAGER_H
#define CONNECTMANAGER_H

#include "SelectReactor.h"
#include "Handler.h"
#include "Channel.h"
#include <string>

using namespace  std;

class CConnectManager:public CHandler,public CSelectReactor
{
public:
	CConnectManager(CSelectReactor* outReactor,string connectLocation);

	virtual int HandleEvent(int event,DWORD dwParam,void* pParam);

	virtual void OnTimer( int event );
 
	CChannel*  Connect();
	int TryConnect();
	void SendConnected(CChannel* channel);
public:
	CSelectReactor* m_outReactor;
	string m_ConnectLocation;


	
};

#endif