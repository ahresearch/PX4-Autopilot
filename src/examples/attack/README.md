# Buffer Overflow Attack

This is a set of attack experiments to figure out how to test the Yolo protection mechanisms.

## Compilation
```
To compile the programs you need to use the Makefile in this folder.   
Just type:
make
```

## Before Running

You need to disable the memory randomization from Linux, which disables the stack protection.   
Otherwise, Linux may prevent the attack, because the address is randomized.
This is done by issuing the command:  

#### echo 0 | sudo tee /proc/sys/kernel/randomize_va_space  



## Testing

### Simple Example
```
 An example of buffer overflow through socket communication can be 
tested with serversocketmain and attacksocket programs.  
./serversocketmain  
./attacksocket  
Run serversocketmain in a terminal and run attacksocket from another terminal window.  
Client Socket Created
connected to the server..
<N>ormal or <O>verflow run?, <Q> to quit:
Normal will call the regular function.
Overflow will ask for the address of the sneaky() functuon.
You need to enter the address of the function you want to overwrite as printed 
by serversocket server program.  
The server will print if the attack succeeds and will stay in the attacked state 
forever (or until we reboot the process).  
```

### PX4 Example
```
Build the attack dynamic module.

make px4_sitl

This will create build/px4_sitl_default/src/examples/attack/examples__attack.px4mod

Copy examples__attack.px4mod as attack.px4mod in folder build/px4_sitl_default/tmp/rootfs

Run px4:  
make px4_sitl jmavsim  
At the px4 promt type 'dyn attack.px4mod start' from the command prompt  
This will start the attack server module and it will be ready to accept 
client socket buffer overflow attacks.  

Run attack from another terminal:  
attackpx4  
Enter the address of the function at the attackpx4 terminal window.  
A successful attack will run and there will be a print showing that the attack succeeded. 
The length of the attack is fixed but can be changed by changing the code in the px4 module.  
```

Here is a typical run with a successful attack on the PX4 side run from one terminal window:

```

pxh> attack start

attack starting.

Attack Application Starting
Server Socket created..
Socket successfully bound..
Server listening..



The client initating the attack from a second terminal window looks like this :


$ ./attackpx4 
Client Socket Created
connected to the server..


The px4 window will display this:

server acccept the client...
sneaky function addr: 0x5565ead8f420
regular function addr: 0x5565ead8f410
calling function pointer at address : 0x5565ead8f200
function addr: 0x5565ead8f200
calling function pointer at address : 0x5565ead8f420
sneaky() function called. Code flow successfully changed.


On the client window enter the attack parameters:

$ <N>ormal or <O>verflow run?, <Q> to quit: O
Answer O
Overflow
Function address:0x5565ead8f420
0x61 0x61 0x61 0x61 0x61 0x61 0x61 0x61 0x61 0x61 0x 0 0x 0 0x55 0x65 0xFFFFFFEA 0xFFFFFFD8 0x20 0xFFFFFFF4 

After the client selects Q the socket connection closes and the PX4 app exits.
It can be restarted again when needed:
attack start
```