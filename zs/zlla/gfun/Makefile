include ../../conf.mk
RD = ../../
DIR_LIB = ../../lib/
export RD
LIB_DIR = libgfun.a
OBJ_DIR = gfun.o
OBJECTS=main.o #$(OBJ_DIR) 
include ./lib.mk
main.exe:$(OBJECTS)
	$(CC) $(DEBUG) -o $@ $(OBJECTS) $(LINKLIB) $(LIBS)
libgfun.a:$(OBJ_DIR)
	ar r $@ $^
main.o:main.cpp
	$(CC) $(DEBUG) -o $@ -c $<
install:lib
	mv $(LIB_DIR) $(LINKLIB)
lib:$(OBJ_DIR)
	ar r $(LIB_DIR) $(OBJ_DIR)	
	$(MAKE) cleano
cleano:
	rm -f $(OBJ_DIR)
clean:
	$(MAKE) cleano
	rm -f *.exe *.o *.txt

