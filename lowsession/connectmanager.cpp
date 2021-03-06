﻿#include "connectmanager.h"
#include "Client.h"
#include "Log.h"
void CConnectManager::OnTimer(int event)
{
	switch (event)
	{
	case EVENT_CONNECT_TIMER:
		TryConnect();
		break;
	default:
		break;
	}
}

CConnectManager::CConnectManager(CSelectReactor *outReactor, string connectLocation) : CHandler(this)
{
	AddHandler(this);
	m_outReactor = outReactor;
	m_ConnectLocation = connectLocation;
	SetTimer(EVENT_CONNECT_TIMER, 100);
}

int CConnectManager::HandleEvent(int event, DWORD dwParam, void *pParam)
{
	switch (event)
	{
	case EVENT_CONNECT_FAILED:
		SetTimer(EVENT_CONNECT_TIMER, 100);
		break;
	default:
		break;
	}
	return CHandler::HandleEvent(event, dwParam, pParam);
}

int CConnectManager::TryConnect()
{
	if (m_ConnectLocation.empty())
		return 0;

	CClient *client = new CClient();
	client->CreateClient("127.0.0.1:1234");
	CChannel *channel = client->ConnectServer(m_ConnectLocation.c_str());
	if (channel != NULL)
	{
		SendConnected(channel);
		KillTimer(EVENT_CONNECT_TIMER);
	}
	CLog::GetInstance()->PrintLog("%s_%s_%d_%p\n", __FILE__, __FUNCTION__, __LINE__, (void *)channel);
	return 0;
}

void CConnectManager::SendConnected(CChannel *channel)
{
	if (m_outReactor != NULL)
	{
		m_outReactor->PostEvent(NULL, EVENT_CONNECT_SUCCESS, 0, (void *)channel);
	}
}

void CConnectManager::SetConnectLocation(string connectLocation)
{
	m_ConnectLocation = connectLocation;
}

void CConnectManager::PostEvent(int event, DWORD dwParam, void *pParam)
{
	CHandler::PostEvent(event, dwParam, pParam);
}
