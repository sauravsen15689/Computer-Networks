import java.io.*;
import java.net.*;

class SerPeer
{
	ServerSocket serversocket;
	Socket socket;
	BufferedReader in;
	BufferedReader stdIn;
	PrintWriter out;
	private static int port;

	SerPeer(){}

	void connect()
	{
		try
		{
			serversocket = new ServerSocket(port);
			System.out.println("Listening. . .");
			socket = serversocket.accept();
			System.out.println("Connected . . .");
			in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			out = new PrintWriter(socket.getOutputStream(),true);
			stdIn = new BufferedReader(new InputStreamReader(System.in));
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
				String received;
				try
				{
					while((received=in.readLine())!=null)
					{
						System.out.println("Client : "+received);
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

	void writeThread()
	{
		Thread write = new Thread()
		{
			public void run()
			{
				String sent;
				try
				{
					while((sent=stdIn.readLine())!=null)
					{
						out.println(sent);
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

	public static void main(String args[])
	{
		port = 3000;
		SerPeer chat = new SerPeer();
		chat.connect();
		chat.readThread();
		chat.writeThread();
	}
}