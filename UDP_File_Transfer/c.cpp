#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;

#define SER "127.0.0.1"

int filesize(char *name)
{
 int len;
 fstream fin;
 fin.open(name,ios::in);
 fin.seekg(0,ios::end);
 len = fin.tellg();
 fin.close();
 return len;
 
}
int main()
{
 int sock,client_sock,c,read_size;
 struct sockaddr_in ser;
 c = sizeof(ser);
 char buf[503],msg[503];
 
 sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
 if(sock < 0)
 {
  cout<<"socket creation failed";
  return 0;
 }
 
 memset((char*)&ser,0,sizeof(ser));
 ser.sin_family = AF_INET;
 ser.sin_port = 8888;
 
 if(inet_aton(SER , &ser.sin_addr) <0)
 {
  cout<<"failed";
  return 0;
 }
 
 char fname[20];
 memset(&fname[0],0,20);
 cout<<"enter file name with extension : ";
 cin>>fname;
 
 read_size = sendto(sock,fname,20,0,(struct sockaddr *)&ser,c);
 
 int fsize = filesize(fname);
 cout<<fsize;
 read_size = sendto(sock,&fsize,sizeof(int),0,(struct sockaddr *)&ser,c);
 
 int itr = 1;
 memset(&msg[0],0,503);
 fstream fin;
 fin.open(fname,ios::in | ios::binary);
 fin.read(msg,503);
 while(itr * 503 < fsize)
 {
  
  read_size = sendto(sock,msg,503,0,(struct sockaddr *)&ser,c);
  
  memset(&msg[0],0,503);
  fin.read(msg,503);
  itr++;
 }
 fin.read(msg,fsize%503);
  read_size = sendto(sock,msg,fsize%503,0,(struct sockaddr *)&ser,c);
  
 fin.close(); 
}
