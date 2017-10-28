#include<bits/stdc++.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

using namespace std;

int main()
{
  int client_sock,serv_sock;
  struct sockaddr_in ser;

  serv_sock=socket(AF_INET,SOCK_STREAM,0);
  if(serv_sock<0)
   {
     cout<<"Failed to create socket"<<endl;
     return 0;
   }
   cout<<"\nSocket Created\n";
   ser.sin_family=AF_INET;
   ser.sin_addr.s_addr=INADDR_ANY;
   ser.sin_port=htons(8888);

   if(bind(serv_sock,(struct sockaddr *)&ser,sizeof(ser)) < 0)
   {
     cout<<"Bind Failed\n";
     return 1;
   }
   cout<<"\nBind Successful\n";

   listen(serv_sock,3);

   cout<<"\nWaiting for incomming connection\n";

   int addrlen=sizeof(ser);
   client_sock=accept(serv_sock,(struct sockaddr *)&ser,(socklen_t*)&addrlen );

   if(client_sock<0)
   {
     cout<<"\nAccept Failed\n";
     return 0;
   }
   cout<<"\nConnection Accepted\n";

   //***********
    char msg[200]={};
      while(recv(client_sock,msg,2000,0)>0)
      {
        cout<<msg;
         cout<<"\n1.with error\n2.without error\n";
        int x;
        cin>>x;
        if(x==1)
        {
          int rn=rand()%10+1;
          if(msg[rn]=='0')
            msg[rn]='1';
          else
            msg[rn]='0';
        }
        int datarecv[20],i;
        i=0;
        for(int j=11;j>0;j--,i++)
          datarecv[j]=msg[i]-48;

        int c,c1,c2,c3,c4;
        c1=datarecv[1]^datarecv[3]^datarecv[5]^datarecv[7]^datarecv[9]^datarecv[11];
        c2=datarecv[2]^datarecv[3]^datarecv[6]^datarecv[7]^datarecv[10]^datarecv[11];
        c3=datarecv[4]^datarecv[5]^datarecv[6]^datarecv[7];
        c4=datarecv[8]^datarecv[9]^datarecv[10]^datarecv[11];

        c=c4*8+c3*4+c2*2+c1;
        if(c==0)
        {
           cout<<"\ndata received : ";
           for(int i=11;i>0;i--)
            cout<<datarecv[i];
          cout<<"\nreceived character : ";
            char a[2]={};
            a[0]= (char)(datarecv[11])+(datarecv[10]*2)+(datarecv[9]*4)+(datarecv[7]*8)+(datarecv[6]*16)+(datarecv[5]*32)+(datarecv[3]*64);
            a[1]='\0';
            cout<<a;
        }
          
         else
         {
          cout<<"\ndata received : ";
           for(int i=11;i>0;i--)
            cout<<datarecv[i];
            cout<<"\nreceived character : ";
            char a[2]={};
            a[0]= (char)(datarecv[11])+(datarecv[10]*2)+(datarecv[9]*4)+(datarecv[7]*8)+(datarecv[6]*16)+(datarecv[5]*32)+(datarecv[3]*64);
            a[1]='\0';
            cout<<a;
            
          if(datarecv[c]==0)
            datarecv[c]=1;
          else
            datarecv[c]=0;
          cout<<"\ncorrect message : ";
          char b[2]={};
            b[0]= (char)(datarecv[11])+(datarecv[10]*2)+(datarecv[9]*4)+(datarecv[7]*8)+(datarecv[6]*16)+(datarecv[5]*32)+(datarecv[3]*64);
            b[1]='\0';
            cout<<b;


                int j=11;
                for(i=0;i<11;i++,j--)
                           msg[i]=datarecv[j]+48;
                           msg[i]='\0';

         }
         send(client_sock, msg, strlen(msg),0);
              fflush(stdout);

      }

   //************
   puts("Client disconnected");
   close(serv_sock);
  return 0;
}
