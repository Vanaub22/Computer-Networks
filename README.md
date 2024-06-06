  ## Computer Networks Laboratory (PCC - CS692)
  This repository contains all my lab assignments and practice programs written for my Computer Networks Laboratory course in B.Tech 6th Semester.
  ### Important Header files for Socket Programming
    #include<stdio.h>
    #include<stdlib.h>
    #include<unistd.h>
    #include<sys/types.h>
    #include<sys/socket.h>
    #include<arpa/inet.h>
    #include<netinet/in.h>
    #include<netinet/ip.h>
To run the client-server applications, simply open two terminal windows side-by-side and run them separately. Ensure that the server is online before running the client.


To compile:

    gcc <my_C_program_name>.c -o <executable_name>
To run:

    ./<executable_name>

### If the program uses the POSIX Thread Library:
Add the lpthread flag during compilation:

    gcc <my_C_program_name>.c -lpthread -o <executable_name>
### If the program uses Math Functions:
Add the lm flag during compilation:

    gcc <my_C_program_name>.c -lm -o <executable_name>
    

   

