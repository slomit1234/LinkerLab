# LinkerLab
linker lab

submitters:
1. shlomit ashkenazi
2. stav avitan

# files
1.the haked binary - secret
2.the hacked lib - .so.6
3.The server - nserver.c
4.The client - vclient.c

# the lab

1. create .so.6 lib and link it with vclient.c
  $ gcc --shared -fPIC vclient.c -o .so.6 -ldl
2. create secret executable
  $ gcc secret.c -ldl -o secret
3. set path of shared library
  $ export LD_LIBRARY_PATH="."

use readelf and hexedit to change "secret" binary (like we have learned at class).

![image](https://user-images.githubusercontent.com/42152443/233864195-d7a791a1-0c5d-4193-9c5f-d492066b81fe.png)


you can check that you changed it correctly with
$ readelf -d secret
![image](https://user-images.githubusercontent.com/42152443/233864222-e8a33ef7-c0cd-4eb3-a0c0-eaf0b0edcc6d.png)


than, 
compile the server
$ gcc -Wall nserver.c -o server
![image](https://user-images.githubusercontent.com/42152443/233864293-0739b120-c68e-4d19-90fb-e714fe38fdc2.png)


finally, run secret and enter your password
$./secret
![image](https://user-images.githubusercontent.com/42152443/233864372-b144c747-fd36-4d8d-bf1b-886e424949e0.png)

you can see that the server got the password
![image](https://user-images.githubusercontent.com/42152443/233864453-73c26cf5-4108-4426-b497-562d1eb49e7e.png)


and that's the end :)


