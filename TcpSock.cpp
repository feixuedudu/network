#include "./TcpSock.h"
CTcpSock::CTcpSock():CInetSock()
{
  ;
}

CTcpSock::CTcpSock(char* loc):CInetSock(loc)
{
  ;
}
CTcpSock::CTcpSock(CServiceName* service):CInetSock(service)
{
  ;
}

CTcpSock::~CTcpSock()
{
  ;
}

int CTcpSock::CreateSocket()
{
  CInetSock::CreateSocket(); 
  sockaddr_in addr;
  addr.sin_port = m_service->GetNPort();
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = m_service->GetNHost();
  socklen_t size ;
  size = sizeof(addr);
  return   bind(m_fd,(sockaddr*)&addr,size);

}

int CTcpSock::Connect(CServiceName* server)
{

  return 0;
}

int CTcpSock::Accept()
{
  return 0;
}
