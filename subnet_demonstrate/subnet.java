import java.util.*;
class subnet
{
	public static void main(String args[])
	{
	String ip;
	System.out.print("Enter the ip address : ");
	Scanner scan = new Scanner(System.in);
	ip = scan.nextLine();
	System.out.println();
	System.out.print("enter no of address required : ");
	int n = scan.nextInt();
	System.out.println();
	String ip_split []= ip.split("\\.");
	String bip_split[] = new String[4];
	String bip="";
	for(int i=0;i<4;i++)
	{
		bip_split[i] =appendzeroes(Integer.toBinaryString(Integer.parseInt(ip_split[i])));
		bip+=bip_split[i];
	}
	System.out.print("ip in binary form : "+bip);
	System.out.println();

	int bits = (int)Math.ceil(Math.log(n)/Math.log(2));
	int mask = 32-bits;

	System.out.print("subnet mask : "+mask);
	System.out.println();

	int fbip[]=new int[32];
	for(int i=0;i<32;i++)
	{
		fbip[i]=(int)bip.charAt(i)-48;
	}

		for(int i=31;i>31-bits;i--)
		{
			fbip[i]&=0;
		}
		String fip[]={"","","",""};
		for(int i=0;i<32;i++)
			fip[i/8]=new String(fip[i/8]+fbip[i]);

		System.out.print("First Address : ");
		for(int i=0;i<4;i++)
		{
			System.out.print(Integer.parseInt(fip[i],2));
			if(i!=3)
			{
				System.out.print(".");
			}
		}
		System.out.println();

	 int lbip[]=new int[32];
	 for(int i=0;i<32;i++)
	 {
	 	lbip[i] = (int)bip.charAt(i)-48;
	 }
	 for(int i=31;i>31-bits;i--)
	 {
	 	lbip[i]|=1;
	 }
	 String lip[]={"","","",""};
	 for(int i=0;i<32;i++)
	 {
	 	lip[i/8]=new String(lip[i/8]+lbip[i]);
	 }
	 System.out.print("last address : ");
	 for(int i=0;i<4;i++)
	 {
	 	System.out.print(Integer.parseInt(lip[i],2));
	 	if(i!=3)
	 		System.out.print(".");
	 }

    }

  static String appendzeroes(String s)
   {
   	 String temp ="00000000";
   	 return temp.substring(s.length())+s;
   }
}