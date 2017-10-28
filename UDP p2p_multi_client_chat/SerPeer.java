import java.util.*;
import java.net.*;
import java.io.*;

class SerPeer
{
	BufferedReader stdIn;
	DatagramSocket socket;
	DatagramPacket packet;
	private static int port;
	InetAddress address;
	byte buf[];

	SerPeer()
	{

	}

	void connect()
	{
		try
		{
		socket = new DatagramSocket(3000);
		stdIn = new BufferedReader(new InputStreamReader(System.in));
		buf = new byte[256];
		packet = new DatagramPacket(buf,buf.length);
		socket.receive(packet);
		address = packet.getAddress();
		port = packet.getPort();
	    }
	    catch(Exception e)
	    {
	    	System.out.println(e);
	    }
	}

	void writeThread()
	{
		Thread write = new Thread()
		{
			public void run()
			{
				String data;
				try
				{
					while((data = stdIn.readLine())!=null)
					{
						buf = new byte[256];
						buf = data.getBytes();
						packet = new DatagramPacket(buf,buf.length,address,port);
						socket.send(packet);
					}
				}
				catch(Exception e)
				{
					System.out.println(e);
				}
			}
		};
		write.start();
	}

	void readThread()
	{
		Thread read = new Thread()
		{
			public void run()
			{
				String data;
				try{
				while(true)
				{
					buf = new byte[256];
					packet = new DatagramPacket(buf,buf.length);
					socket.receive(packet);
					data = new String(packet.getData(),0,packet.getLength());
					System.out.println("Client : "+data);
				}
			   }
			   catch(Exception e)
			   {
			   	System.out.println(e);
			   }
			}
		};
		read.start();
	}

	public static void main(String args[])
	{
		port = 3000;
		SerPeer chat = new SerPeer();
		chat.connect();
		chat.readThread();
		chat.writeThread();
	}
}