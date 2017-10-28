#include<bits/stdc++.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

using namespace std;

int main()
{
	int ser_socket;
	struct sockaddr_in ser,cli;
	int addrlen=sizeof(cli);
	if((ser_socket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
	{
		cout<<"\nsocket creation failed";
		return 0;
	}
	ser.sin_family = AF_INET;
	ser.sin_addr.s_addr=INADDR_ANY;
	ser.sin_port = htons(8888);

	if(bind(ser_socket,(struct sockaddr*)&ser,sizeof(ser))<0)
	{
		cout<<"\nbind failed";
		return 0;
	}

	char fname[20];
	int fsize;
	char data[503];
	recvfrom(ser_socket,fname,20,0,(struct sockaddr*)&cli,(socklen_t *)&addrlen);
	
	
	recvfrom(ser_socket,&fsize,sizeof(int),0,(struct sockaddr*)&cli,(socklen_t *)&addrlen);
	fflush(stdout);
	cout<<"\nFile size to be copied : "<<fsize;
	cout<<"\nFile size to be copied : "<<fsize;
    //cout<<"\noriginal file renamed to :"<<fname;
	fname[0]='s';
	ofstream fout;
	fout.open(fname,ios::out | ios::binary);
	int itr=1;
	memset(data,0,503);
	while(itr*503<fsize)
	{
		recvfrom(ser_socket,data,503,0,(struct sockaddr*)&cli,(socklen_t *)&addrlen);
		fout.write(data,503);
		memset(data,0,503);
		itr++;
	}
	recvfrom(ser_socket,data,(fsize%503),0,(struct sockaddr*)&cli,(socklen_t *)&addrlen);
		fout.write(data,(fsize%503));

		fout.close();


	return 0;
}