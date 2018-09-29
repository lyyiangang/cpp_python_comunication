CXX = g++

PYTHON_LIB_DIR = -L"/usr/lib/x86_64-linux-gnu" -L"/usr/lib/python3/dist-packages/numpy/core/lib" 
PYTHON_LIBS = -lpython3.5m -lnpymath -lm
PYTHON_INC = -I"/usr/include/python3.5m"

INC_DIR = $(PYTHON_INC)  -I"/home/nvidia/.local/lib/python3.5/site-packages/numpy/core/include" -I"/usr/local/include"

CXXFLAGS = -Wall -std=c++14  $(INC_DIR) 

ifeq ($(BUILD),debug)   
# "Debug" build - no optimization, and debugging symbols
CFLAGS += -O0 -g
else
# "Release" build - optimization, and no debug symbols
CFLAGS += -O2 -s -DNDEBUG
endif



LIB_OPENCV= `pkg-config opencv --cflags --libs` -lcrypt 


LIB_DIR= -L"/usr/lib" -L"/usr/local/lib" $(PYTHON_LIB_DIR)


COMMON_LIBS = -lrt -ldl -lpthread 
LIBS  = $(COMMON_LIBS) $(LIB_OPENCV) $(PYTHON_LIBS)

TARGET = test.out

C_SRC = $(wildcard ./*.c) 
CC_SRC = $(wildcard ./*.cc)
CPP_SRC = $(wildcard ./*.cpp)
OBJ = $(C_SRC:.c=.o) $(CC_SRC:.cc=.o) $(CPP_SRC:.cpp=.o) 

$(TARGET): $(OBJ)
	$(CXX)  -o $@ $^  $(CXXFLAGS) $(LIBS) $(LIB_DIR)


.PHONY:clean

clean:
	rm -f $(OBJ) $(TARGET)    