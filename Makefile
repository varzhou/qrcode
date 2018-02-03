SRCS = $(wildcard *.cpp)    # wildcard把 指定目录 ./ 下的所有后缀是cpp的文件全部展开。  
OBJS = $(SRCS:.cpp = .o)    # OBJS将$(SRCS)下的.cpp文件转化为.o文件  
CXX = g++                   # 代表所使用的编译器  
INCLUDES = -I/usr/local/include/opencv2 -I/usr/local/include -I.    # 头文件查找路径   
LIBS =  -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lzxing
CXXFLAGS = -g -Wall -O0   #附加参数  
DECODE = decode      #输出程序名称
ENCODE = encode  

.PHONY : all clean

all:$(DECODE) $(ENCODE)
$(DECODE) : decode.o
	$(CXX) -g -o decode decode.o $(INCLUDES) $(LIBS)
$(ENCODE) : encode.o
	$(CXX) -g -o encode encode.o $(INCLUDES) $(LIBS) -lqr
%.o : %.cpp  
	$(CXX) -c $< $(CXXFLAGS)
clean:  
	rm -rf *.out *.o $(DECODE) $(ENCODE)    #清除中间文件及生成文件
