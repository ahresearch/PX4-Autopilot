# Memory Intrusion Example Using the /proc File System

## Contents and Modifications
This example was downloaded from this location:  
 https://medium.com/@holdengrissett/linux-101-how-to-hack-your-process-memory-2514a3d0778d  

The code contains host_app.c which was not modified and mem_attack.py file,  
 which had to be modified, because of a run time error with Python 3.

## Steps for running the simple test

  * Build the host application to be attacked:  
    make  
  * Run the host application:  
    ./host_app  
  * Find the PID of the host application  
    ps -aux | grep host_app  
    The PID is the first number of the line
  * Run the Python script that modifies the memory  
    Use the found PID in the following command:  
    python3 mem_attack.py 21566 0x64ed88 0 0 0 0 0  
    21566 is the PID of the process we want to attack  
    0x64ed88 is the address in the heap of the buffer we want to overwrite.  
    This information is printed from the C library called by the line_follower_clib.py script  
    0 0 0 0 0 are the values for the 5 bytes we want to overwrite  
  * Observe that the host application displays the new sensor readings and the memory is overwritten. 
    Once the attack stops the app needs to overwrite the memory. 
    
   
