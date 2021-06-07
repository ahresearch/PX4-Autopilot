# Buffer Overflow Attack

This is a set of attack experiments to figure out how to test the Yolo protection mechanisms.

## Compilation

To compile the programs you need to use the Makefile.   
Otherwise, Linux may prevent the attack.

## Before Running

Also you need to disable the memory randomization from Linux, which disables the stack protection.   
This is done by issuing the command:  

#### echo 0 | sudo tee /proc/sys/kernel/randomize_va_space  

Each program has either one or two run shell program to run a successful/unsuccessful attack.

This code is in setup.sh, which is only applicable for Linux.  

## Testing
An example of buffer overflow through socket communication can be tested with stack4 and clientsock programs.  
./serversocket  
./attacksocket  
Run serversocket in a terminal and connect with attacksocket from another terminal window.  
At the attacksocket side enter the address of the function you want to overwrite as printed by serversocket server program.  



