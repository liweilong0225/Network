#include<iostream>
#include <winsock2.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
	//1.���ؿ�
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
	}
/* Confirm that the WinSock DLL supports 2.2.*/
/* Note that if the DLL supports versions greater    */
/* than 2.2 in addition to 2.2, it will still return */
/* 2.2 in wVersion since that is the version we      */
/* requested.                                        */

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        printf("Could not find a usable version of Winsock.dll\n");
        WSACleanup();
        return 1;
    }
    else
        printf("The Winsock 2.2 dll was found okay\n");


	//2.�����׽���
	SOCKET sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (INVALID_SOCKET == sock)
	{
		WSACleanup();
		return -1;
	}

	//��ȡsocket�ں˻�������С(�ֽ�)
	int nRecvBufferSize,nSendBufferSize;
	int NSize = sizeof(int);
	getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(char*)&nRecvBufferSize,&NSize);
	getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(char*)&nSendBufferSize,&NSize);
	cout<<"send size:"<<nSendBufferSize<<endl<<"recv size:"<<nRecvBufferSize<<endl;

	//3.��
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;//������������
	addrServer.sin_port = htons(1234);
	if (SOCKET_ERROR == bind(sock,(const sockaddr*)&addrServer,sizeof(sockaddr_in)))
	{
		closesocket(sock);
		WSACleanup();
		return 1;
	}

	//socket�����ͷ�����
	//u_long val = 1;
	//ioctlsocket(sock,FIONBIO,&val);//�����������

	//4.��������
	char szbuf[1024] = {0};
	sockaddr_in addrClient;
	int nSize = sizeof(sockaddr_in);
	int nRel;
	while (1)
	{
		nRel = recvfrom(sock,szbuf,sizeof(szbuf),0,(sockaddr*)&addrClient,&nSize);
		if (nRel > 0)
		{
			//5.��������sendto()
			cout<<szbuf<<endl;
			cin>>szbuf;
			sendto(sock,szbuf,sizeof(szbuf),0,(const sockaddr*)&addrClient,sizeof(addrClient));
		}
	}

	//6.�ر��׽���
	closesocket(sock);

	//7.ж�ؿ�
	WSACleanup();

	system("pause");
	return 0;
}