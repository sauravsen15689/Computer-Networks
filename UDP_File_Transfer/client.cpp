#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>

using namespace std;

int sizecal(char *fname)
{
	int len;
	ifstream fin;
	fin.open(fname);
	fin.seekg(0,ios::end);
	len = fin.tellg();
	fin.close();
	return len;
}

int main()
{
	int client_socket;
	struct sockaddr_in ser;

	if((client_socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
	{
		cout<<"\nsocket creation failed";
		return 0;
	}
	cout<<"\nsocket created";

	ser.sin_family = AF_INET;
	ser.sin_addr.s_addr=INADDR_ANY;
	ser.sin_port = htons(8888);

	char fname[20];
	cout<<"\nenter the file name with extension : ";
	cin>>fname;

	sendto(client_socket,fname,20,0,(struct sockaddr*)&ser,sizeof(ser));

	int fsize = sizecal(fname);
	cout<<"file size to send (bytes) : "<<fsize;
	sendto(client_socket,&fsize,sizeof(int),0,(struct sockaddr*)&ser,sizeof(ser));
	char data[503];
	memset(data,0,503);
	ifstream fin;
	fin.open(fname,ios::binary);
	fin.read(data,503);
	int itr=1;
	while(itr*503<fsize)
	{
		sendto(client_socket,data,503,0,(struct sockaddr*)&ser,sizeof(ser));
		memset(data,0,503);
		fin.read(data,503);
		itr++;
	}
	fin.read(data,fsize%503);
	sendto(client_socket,data,fsize%503,0,(struct sockaddr*)&ser,sizeof(ser));
	fin.close();
	return 0;
}
