#  ProgSysLabs
8 hours to develop a Linux Shell

During those 2 lab sessions, we had the opportunity to delve deeper into various functiuons that were initially introduced in class.
These functions such as write, read, open and creat.
While basic understanding of these functions was straightforward, the challenge layed in comprehending the arguments required for these functions.
Additionally, we were introduced to new commands like strtok, clock_gettime, and dup2.
The labs served as a practical application to not only understand these functions and commands but also to comprehend their purpose in coding.
For example, the fork function which utility was unclear became clearer as we realized it's role in crucial apllications such as creating a shell.
Those labs were not without their challenges. 
The third and fourth questions, in particular, posed a considerable difficulty. 
This was our first encounter with real challenges, primarily because we had to search for specific functions and learn their usage. 
For instance, in question 4, we had to understand the use of WIFEXITED and WIFSIGNALED, and also consider using the sprintf function.
Or even in question 3 where we had to understand how to exit with the command <ctrl> +d.
And finally also question 7, as we finally were able to create a new file or open a existing one but in the end as an instructions like ls > file.txt the terminal don't work anymore no commands works.
We think that it comes from the fact that the file doesn't close itself properly but it is there in the code so in the end no solutions were found.
In summary, these labs were instrumental in enhancing our understanding of the functions and code discussed in class. 
They also highlighted the challenges faced during the creation of a shell in C, thereby providing a comprehensive learning experience.

# TP2   
8 hours to develop a TFTP client

During the last two lab, we had the opportunity to learn and apply a lot of new things.
First we did some socket programming, creating UDP sockets to communicate between the TFTP client and server for the get and put function.
And only at one point in the lab the two function differ, we have  gettftp which is made to download a file and then puttftp for uploading a file.
In gettftp, the program enter a loop to receive data packets from the server, it prints the hexadecimal representation of the received packet and the content of the file and finally send acknoledgment packets back to the server.
Whereas in puttftp, we open a file for reading, it construct a data packet with the file content and sends it to the server. And it suceeds we receive an acknoledgment packet from the server.
To conclude, this lab gave us the foundation for understanding basic network programming and file transfer mechanisms.