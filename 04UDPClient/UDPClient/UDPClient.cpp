#include<iostream>
#include<WinSock2.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

int main()
{
	//1.加载库
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

	//2.创建套接字
	SOCKET sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (INVALID_SOCKET == sock)
	{
		WSACleanup();
		return -1;
	}
	//广播权限
	BOOL bval = TRUE;
	setsockopt(sock,SOL_SOCKET,SO_BROADCAST,(const char*)&bval,sizeof(BOOL));
	char szbuf[1024] = {0};
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");
	addrServer.sin_port = htons(1234);
	while (1)
	{
		cin>>szbuf;
		sendto(sock,szbuf,sizeof(szbuf),0,(const sockaddr*)&addrServer,sizeof(addrServer));

		int nRel = recvfrom(sock,szbuf,sizeof(szbuf),0,0,0);
		if (nRel>0)
		{
			cout<<szbuf<<endl;
		}
	}
	
	closesocket(sock);
	system("pause");
	return 0;
}