all: attacksocket serversocket 

attacksocket:	attacksocket.c
	gcc -fno-stack-protector -g3 -Xlinker -Map=stack3.map  -o attacksocket attacksocket.c

serversocket:	serversocket.c
	gcc -fno-stack-protector -g3 -Xlinker -Map=stack3.map  -o serversocket serversocket.c


clean:
	rm attacksocket serversocket *.map
