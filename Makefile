CXX = g++

PYTHON_LIB_DIR = -L"/usr/lib/x86_64-linux-gnu" -L"/usr/lib/python3/dist-packages/numpy/core/lib" 
PYTHON_LIBS = -lpython3.5m -lnpymath -lm
PYTHON_INC = -I"/usr/include/python3.5m"

INC_DIR = $(PYTHON_INC)  -I"/home/nvidia/.local/lib/python3.5/site-packages/numpy/core/include" \
	-I"/usr/local/include" -I"/home/lyyiangang/lyy/zeromq-4.2.3/include" \
	-I"/usr/local/include/opencv2" -I"./"

CXXFLAGS = -Wall -std=c++14  $(INC_DIR) 

ifeq ($(BUILD),debug)   
# "Debug" build - no optimization, and debugging symbols
CFLAGS += -O0 -g
else
# "Release" build - optimization, and no debug symbols
CFLAGS += -O2 -s -DNDEBUG
endif



LIB_OPENCV= `pkg-config opencv --cflags --libs` -lcrypt 


LIB_DIR= -L"/usr/lib" -L"/usr/local/lib" $(PYTHON_LIB_DIR) -L"/home/lyyiangang/lyy/zeromq-4.2.3/src/.libs" \
	-L"/home/lyyiangang/lyy/zeromq-4.2.3/src/.libs/"


COMMON_LIBS = -lrt -ldl -lpthread -lzmq `pkg-config --cflags --libs protobuf` 
LIBS  = $(COMMON_LIBS) $(LIB_OPENCV) $(PYTHON_LIBS)

#TARGET = test.out

#C_SRC = $(wildcard ./*.c) 
#CC_SRC = $(wildcard ./*.cc)
#CPP_SRC = $(wildcard ./*.cpp)
#OBJ = $(C_SRC:.c=.o) $(CC_SRC:.cc=.o) $(CPP_SRC:.cpp=.o) 

#$(TARGET): $(OBJ)
#	$(CXX)  -o $@ $^  $(CXXFLAGS) $(LIBS) $(LIB_DIR)
all:zmq cvzmq proto_zmq_cpp

zmq:
	$(CXX) -o hwclient.out hwclient.c $(CXXFLAGS) $(LIBS) $(LIB_DIR)
	$(CXX) -o hwserver2.out hwserver2.c $(CXXFLAGS) $(LIBS) $(LIB_DIR)

cvzmq:
	$(CXX) -o cvClient.out cvClient.c $(CXXFLAGS) $(LIBS) $(LIB_DIR)

proto_zmq_cpp: proto_zmq_client.c proto_zmq_server.py cpp_py_exchange_data.proto
	protoc --cpp_out=. --python_out=. cpp_py_exchange_data.proto
	$(CXX) -o proto_zmq_client.out proto_zmq_client.c cpp_py_exchange_data.pb.cc $(CXXFLAGS) $(LIBS) $(LIB_DIR)

#.PHONY:clean

clean:
	rm -f *.out