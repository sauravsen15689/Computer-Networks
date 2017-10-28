#include<bits/stdc++.h>
using namespace std;

int convert(char *no,int pos)
{
   int num=0;
   for(int i=pos;i<=pos+1;i++)
   {
      switch(no[i])
      {
        case 'a':num+=10;break;
        case 'b':num+=11;break;
        case 'c':num+=12;break;
        case 'd':num+=13;break;
        case 'e':num+=14;break;
        case 'f':num+=15;break;
        case ' ':break;
        default:num+=(no[i]-48);                   
      }
      if(no[i]==' '|| no[i+1]==' ')
      { 
      }
      else
      num=num*16;
   }
   return num;
}


int main()
{
  
  char data[512];
  int protocol,type,ip;
  int i=1;
  ifstream file;
  file.open("SNIFFER.LOG");
  while(!file.eof())
  {
    file.getline(data,512);
    if(strcmp(data,"")==0)
    {
      break;
    }
    cout<<"\n"<<i++<<".Packet : "<<data<<'\n';
    int i;
    int pos=0;
    for(i=0;pos<12;i++)
      if(data[i]==' ')
        pos++;
     type=convert(data,i)*100;
     
     for(;pos<13;i++)
       if(data[i]==' ')
        pos++;
     type+=convert(data,i);
     
     switch(type)
     {
       case 800:
         cout<<"\nType : IP";
         break;
       case 806:
         cout<<"\nType : ARP";
         break;
         
       default:
         cout<<"\nother packet no : "<<type;
     }
     
      for(;pos<23;i++)
       if(data[i]==' ')
         pos++;
       protocol=convert(data,i);
       
       cout<<"\nProtocol : ";
       switch(protocol)
       {
         case 0 :
           cout<<"HOPOPT";
           break;
         case 1:
           cout<<"ICMP";
           break;
         case 2:
           cout<<"TCP";
           break;
         case 3:
           cout<<"UDP";
           break;
           
         default:
           cout<<" no "<<protocol;
       }
       
       cout<<"\nsource ip address : ";
       for(;pos<26;i++)
         if(data[i]==' ')
           pos++;
       cout<<convert(data,i)<<".";
       
       for(;pos<27;i++)
         if(data[i]==' ')
           pos++;
       cout<<convert(data,i)<<".";
       
       for(;pos<28;i++)
         if(data[i]==' ')
           pos++;
       cout<<convert(data,i)<<".";
       
       for(;pos<29;i++)
         if(data[i]==' ')
           pos++;
       cout<<convert(data,i);
       
       
       cout<<"\nDestination ip : ";
       for(;pos<30;i++)
         if(data[i]==' ')
           pos++;
       cout<<convert(data,i)<<".";
       for(;pos<31;i++)
         if(data[i]==' ')
           pos++;
       cout<<convert(data,i)<<".";
       for(;pos<32;i++)
         if(data[i]==' ')
           pos++;
       cout<<convert(data,i)<<".";
       for(;pos<33;i++)
         if(data[i]==' ')
           pos++;
       cout<<convert(data,i);
  }
  file.close();
  
 return 0;
}

//**********end***********
