include ../../conf.mk
BASE_OBJ = 
LOW_OBJ = 
LIB_DIR = tm.a
OBJ_DIR = tm.o
#$(BASE_OBJ) $(LOW_OBJ)
DIR_LIB = ../../lib/
OBJECTS=main.o
include ../../lib.mk
include ./lib.mk
main.exe:$(OBJECTS) 
	$(CC) $(DEBUG) -o $@ $(OBJECTS)  $(LINKLIB) $(LINKS) $(LIBS)
install:$(LIB_DIR)
	mv $(LIB_DIR) $(LINKLIB)
main.o:main.cpp
	$(CC) $(DEBUG) -o $@ -c $^ $(INCS) $(CXXINCS)
%.o:%.cpp
	$(CC) $(DEBUG) -o $@ -c $^ $(CXXINCS) $(INCS)
$(LIB_DIR):$(OBJ_DIR)
	ar r $@ $^	
	$(MAKE) cleano
lib:$(LIB_DIR)
	@echo "lib complete"
clean_o:
	rm -f $(OBJ_DIR)
cleano:
	rm -f $(OBJ_DIR)
clean:
	$(MAKE) clean_o
	rm -f *.exe *.o *.txt $(LIB_DIR)
		