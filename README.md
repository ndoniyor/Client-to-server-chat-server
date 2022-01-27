# Client-to-server-chat-server
Chat server between a client and server on the same port using linux sockets.

Compile `server.c` first and enter the port number you want to open (should be >2000), this will open the server to incoming connections. Then compile the `client.c` file and enter the port number from before and connection should be established. Use "/exit" on either side to end the connection.

In its current state the messaging is synchronous being done one at a time between the host and client. Working on implementing a more functional version with asynchronous messaging.
