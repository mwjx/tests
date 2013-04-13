include ../Makefile.conf
export RD ../
OBJ_DIR = station.o
OBJ_LIST = main.o $(OBJ_DIR)
main.exe:$(OBJ_LIST)
	$(CC) $(DEBUG) -o $@ $(OBJ_LIST)  $(CXXINCS) $(INCS)
main.o:main.cpp
	$(CC) $(DEBUG) -o $@ -c main.cpp  $(CXXINCS) $(INCS)
include ../Makefile_o.mk
cleano:
	rm -f $(OBJ_DIR)
clean:
	rm -f *.exe *.o	$(OBJ_LIST)