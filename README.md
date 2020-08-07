### **Old project from computer architecture class**

Lab 3: IPC Message Passing Using D-bus
By: Jared Wilson and Matthew J

Design of the program:
This new design was completely different from what we are used to considering
using dbus is new to us. We went off of the examples provided to use to give us
a good base of what code we needed to use. With dbus, it is a message bus system
that helps applications talk to one another. With the help of a configuration file,
it helps us communicate between the client and server. We designed to files with
this in mind. These two file are "server.c" and "client.c" with both build off
of each other. Both files have error handlers to catch if anything goes wrong
while running. After the connection is made, the code adds the server name to
the bus to start receiving new messages. Within a loop, it waits for an incoming
message and once it hits, there will be a reply. Once the reply comes, then that
completes the cycle. It will close the connection which ends the program. All the server does right now is reverse the order of a string you give it.

Description of Functions:
client.c -
Looking at this file, at the top it instantiates some of the variables in the file. It then
goes on to have a caller function which basically takes two arguments and checks them with
the server. It goes through and does these checks along with checking of any errors. If there
are no errors, it then appends the two arguments. It also checks for memory leakage here as well.
It then has a "request sent" if it all goes through. 

server.c -
The server is the first thing created while running this program. In the main function it basically
"listens" for any method calls from the client. It also checks for any errors here as well. It then
goes into a loop that is continuous which allows multiple calls to the server. It then calls on the reply
method function which does all the work. It takes a string and reverses it.

Pros and Cons:
Pros: Learned more about linux libraries and how dbus works. Lots of time spent working
learning new processes. Really interesting to learn and code about.
Cons: One of the harder pieces of code to learn since it was brand new to us. Had to
include outside directories such as "dbus-arch-deps.h", had to find it online.

Instructions on using our code:
1. Download the configuration file, the server file, and the client file (make sure
they are all in the same folder).
2. Open the terminal and go to the directory that those files are in.
3. Open another terminal and do the same thing.
4. Compile the server file by using "gcc server.c -ldbus-1 -I/usr/include/dbus-1.0 -o lab3Server"
on one terminal and then compile the client file by using "gcc client.c -ldbus-1 -I/usr/include/dbus-1.0
-o lab3Client" on the other.
5. After both compiled, run "sudo ./lab3Server" on your server terminal.
6. Run "sudo ./lab3Client", give it a string up to 78 characters
7. Watch as it sits and waits for a reply from the server, and it will return your string reversed
8. The server terminal will update as well.
9. Close the server by using "Control+Z" in the terminal window.



Side notes - 
At one point in this lab I did 'sudo apt-get remove dbus' which broke the virtual machine I had. That was fun. Our config file is absurdly convoluted, I couldn't get dbus to like anything I put in it.
