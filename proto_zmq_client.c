//https://learning-0mq-with-pyzmq.readthedocs.io/en/latest/pyzmq/patterns/client_server.html
//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cv.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <cpp_py_exchange_data.pb.h>

int main (void)
{
    printf ("Connecting to hello world server...\n");
    cv::Mat img = cv::imread("./ml_guide.png");
    std::cout<<"img shape:"<<img.rows<<","<<img.cols<<".neles"<<img.cols * img.rows<< std::endl;
    std::vector<uchar> imgBuffer(img.begin<uchar>(), img.end<uchar>());
    std::cout<<"flattend img:"<<imgBuffer.size()<<std::endl;

    GOOGLE_PROTOBUF_VERIFY_VERSION;
    yy::MsgToServer msgToServer;
    msgToServer.set_msgmode(yy::MsgToServer::RUN);
    msgToServer.set_width(img.cols);
    msgToServer.set_height(img.rows);
    msgToServer.add_imgbuffer(imgBuffer.data(), imgBuffer.size());
    std::string byteStr;
    msgToServer.SerializeToString(&byteStr);
    
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    zmq_send(requester, byteStr.c_str(), byteStr.size(), 0);



    const int bufferSize = 1000000;
    char reciveBuffer[bufferSize];
    zmq_recv(requester, reciveBuffer, bufferSize, 0);
    yy::MsgToClient msgToClient;
    std::cout<<"before populate data, byte size is:"<<msgToClient.ByteSize()<<std::endl;
    msgToClient.ParseFromString(std::string(reciveBuffer, bufferSize));
    std::cout<<"after populate data, byte size is:"<<msgToClient.ByteSize()<<std::endl;
    std::cout<<"client said:recive data: width:"<<msgToClient.width()<<".height:"<<msgToClient.height()<<". action type:"<<msgToClient.actiontype()<<std::endl;
    
    // zmq_recv(requester, tmpBuffer, sizeof(tmpBuffer)/sizeof(char), 0);

    // char tmpBuffer[1];
    // zmq_recv(requester, tmpBuffer, sizeof(tmpBuffer)/sizeof(char), 0);
    // std::cout<<"get tmpBuffer:"<<tmpBuffer<<std::endl;


    // std::cout<<"send buffer"<<std::endl;
    // std::vector<uchar> debugBuffer={1,2,3,4,5};
    // zmq_send(requester, debugBuffer.data(), debugBuffer.size(), 0);

#if 0
    int responseBuffer[2];
    zmq_recv(requester, responseBuffer, 

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        printf ("Sending Hello %d...\n", request_nbr);
        char buffer [10];
        zmq_send (requester, "Hello", 5, 0);


        zmq_recv (requester, buffer, 10, 0);
        printf ("Received %s %d\n",buffer, request_nbr);


    }
#endif
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}
