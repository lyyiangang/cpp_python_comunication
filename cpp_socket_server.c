//lyy. copy from https://www.geeksforgeeks.org/socket-programming-cc/
// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>
#include <vector>
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    // Creating socket file descriptor 
    int server_fd; 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    int opt = 1; 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    struct sockaddr_in address; 
    int addrlen = sizeof(address); 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    int new_socket;
    //lyy. block here and waiting for new data.
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    int it = 0;
    while(true)
    {
        std::cout<<"iteration:"<<it++<<std::endl;
        int msgHeaderBuffer[4]={0};
        int recvSize = recv(new_socket, msgHeaderBuffer, sizeof(msgHeaderBuffer)/sizeof(char), 0);
        std::cout<<"receive header data:"<<msgHeaderBuffer[0]<<","<<msgHeaderBuffer[1]
            <<","<<msgHeaderBuffer[2]<<","<<msgHeaderBuffer[3]<<std::endl;
        if(recvSize < 1 || msgHeaderBuffer[0] < 1)
        {
            std::cout << "get exit command." << msgHeaderBuffer[0] << std::endl;
            break;
        }

        std::vector<float> msgToClient={1.1, 2.2, 3.3};
        send(new_socket, msgToClient.data(), msgToClient.size() * sizeof(float)/sizeof(char), 0);

    };
    close(server_fd);
    std::cout<<"done"<<std::endl;
    return 0; 
} 
