import java.util.*;
import java.net.*;
import java.io.*;

class SerMulti
{
	DatagramSocket socket;
	DatagramPacket packet;
	InetAddress address;
	private static int port=3001;
	byte buf[];

	SerMulti()
	{}

	void connect()
	{
		try
		{
		socket = new DatagramSocket(3000);
		address=InetAddress.getByName("224.0.0.1");
		}
		catch(Exception e)
		{
			System.out.println(e);
		}

	}
	void readThread()
	{
		Thread read = new Thread()
		{
			public void run()
			{
				String data;
				try
				{
					while(true)
					{
					buf = new byte[256];
					packet = new DatagramPacket(buf,buf.length);
					socket.receive(packet);
					data = new String(packet.getData(),0,packet.getLength());

					buf = new byte[256];
					buf=data.getBytes();
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
		read.start();
	}
		public static void main(String[] args) throws Exception {
		SerMulti chatServer = new SerMulti();
		chatServer.connect();
		chatServer.readThread();
		}
}