//lyy. https://www.geeksforgeeks.org/socket-programming-cc/
// Client side C/C++ program to demonstrate Socket programming . you need start server frist.
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h> 
#include <iostream>
#include <vector>
#include <thread>
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    int sock_fd = 0; 
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    struct sockaddr_in serv_addr; 
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    struct sockaddr_in address; 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
    
    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed. Make sure you start server\n"); 
        return -1; 
    } 
    for(int ii = 0; ii< 3; ++ii)
    {
        std::cout<<"iteration:"<<ii<<std::endl;
        std::vector<int> flattenMsg( 4, 0);
        flattenMsg[0] = ii == 10 ? -1 : 1; //msg type. -1: make server exit. 
        flattenMsg[1] = 9;
        flattenMsg[2] = 8;
        flattenMsg[3] = 7;
        send(sock_fd, flattenMsg.data(), flattenMsg.size() * sizeof(int)/sizeof(char), 0);
        std::cout<<"client: msg is sent"<<std::endl;

        std::vector<float> recivedData(3, 0);
        recv(sock_fd, recivedData.data(), recivedData.size() *  sizeof(float)/sizeof(char), 0);
        std::cout<<"server:receive data:"<<recivedData[0]<<","<<recivedData[1]<<","<<recivedData[2]<<std::endl;
    }

    std::cout<<"done"<<std::endl;
    return 0; 
} 