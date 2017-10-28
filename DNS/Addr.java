import java.util.*;
import java.net.*;

class Addr
{
  public static void main(String args[])
  {
    String ip;
    System.out.println("enter the address ");
    Scanner scan=new Scanner(System.in);
    ip=scan.next();
    try
    {
      InetAddress in = InetAddress.getByName(ip);
      if(ip.charAt(0)>='0' && ip.charAt(0)<='9')
        System.out.println("url of ip address : "+ in.getHostName());
      
      else
      System.out.println("ip address : "+ in.getHostAddress());
    }
    catch(Exception e)
    {
      System.out.println(e);
    }
    
  }
  
}
