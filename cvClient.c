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

int main (void)
{
    printf ("Connecting to hello world server...\n");
    cv::Mat img = cv::imread("./ml_guide.png");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    std::cout<<"client said: ground truth wxh is :"<<img.cols<<"x"<<img.rows<<std::endl;
    int wh[2] = {img.cols, img.rows};
    zmq_send(requester, wh, sizeof(wh)/sizeof(char), 0);
    std::cout<<"img wh is sent"<<std::endl;

    char tmpBuffer[1];
    zmq_recv(requester, tmpBuffer, sizeof(tmpBuffer)/sizeof(char), 0);
    std::cout<<"get tmpBuffer:"<<tmpBuffer<<std::endl;

    // int nEle = img.cols * img.rows * img.channels() ;
    // zmq_send(requester, img.data, nEle * sizeof(uchar)/sizeof(char), 0);
    // std::cout<<"send "<<img.data[0]<<","<<img.data[1]<<","<<img.data[2]<<std::endl;


    std::cout<<"send buffer"<<std::endl;
    std::vector<uchar> debugBuffer={1,2,3,4,5};
    zmq_send(requester, debugBuffer.data(), debugBuffer.size(), 0);

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
