import java.io.*;
import java.net.*;
import java.util.*;

class SerMulti
{
	ServerSocket serversocket;
	static int port;
	HashSet<PrintWriter> writers = new HashSet<PrintWriter>();

	SerMulti()
	{
		try
		{
			serversocket = new ServerSocket(port);
			System.out.println("Listening...");
		}
		catch(Exception e)
	     	{
	     		System.out.println(e);
	     	}
		
	}

	void connect()
	{
		try
		{
			while(true)
			{
				new Handler(serversocket.accept()).start();
			}
			
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}

	public static void main(String args[])
	{
		port = 3000;
		SerMulti chat = new SerMulti();
		chat.connect();
	}

	private  class Handler extends Thread
	{
		Socket socket;
		BufferedReader in;
		PrintWriter out;

		Handler(Socket socket)
		{
			this.socket=socket;
		}
		public void run()
		{
			try
			{
			in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			out = new PrintWriter(socket.getOutputStream(),true);
			writers.add(out);
			readThread();
	     	}
	     	catch(Exception e)
	     	{
	     		System.out.println(e);
	     	}

			
		}

	 synchronized void readThread()
		{
			Thread read = new Thread()
			{
				public void run()
				{
					String data;
					try
					{
						while((data=in.readLine())!=null)
						{ 
							for(PrintWriter writer: writers)
                			{
                			  writer.println(data);
                			}
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

	}
}