CC = g++
DEBUG = -g
INCS = 
LIBS = -L"C:/msysgit/msysgit/mingw/lib" -lcrypto -lgsasl -lssl
all:main.exe
main.exe:main.o
	g++ -o $@ $^ $(LIBS) $(INCS)
%.o:%.cpp
	$(CC) $(DEBUG) -o $@ -c $^ $(INCS)
clean:
	rm -rf *.exe *.o