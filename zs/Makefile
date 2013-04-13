#-------需要根据不同平台设置的值----------
#make,gmake
#SYS值根据不同平台改动win2000,winxp,linux,bsd47,bsd54,bsd70
SYS = winxp
#LV是库的版本，不同版本stl的hash容器头文件可能不同,取值-D LV或空
LV = 
#V_DEBUG是否调试版本,-D DEBUG,-D NDEBUG
V_DEBUG = -D DEBUG
#--------end 需要根据不同平台设置的值-----
CC = g++
OPTIONS = -o3
DEBUG = $(V_DEBUG) -g
DIR_LIB = gms/lib/
EXE = zsds
#MAKE=gmake


SOU_MAIN = main.cpp
#OBJECTS = main.o backprocess.o class_webserver.o class_request.o ini/class_ini.o gms/libgms.a
OBJECTS = main.o commu/libcm.a gms/libgms.a kp/lib_kp.a
include gms/Makefile.lib
complete:$(EXE)
	@echo "make complete"
$(EXE):$(OBJECTS)
	$(CC) $(OPTIONS) $(DEBUG) -o $(EXE) $(OBJECTS) $(LINKLIB) $(LINKS) $(LIBS)
main.o:main.cpp
	$(CC) $(DEBUG) -o $@ -c main.cpp $(INCS) $(CXXINCS)
backprocess.o:backprocess.cpp
	$(CC) $(DEBUG) -o $@ -c backprocess.cpp
ini/class_ini.o:ini/class_ini.cpp
	$(CC) $(DEBUG) -o $@ -c ./ini/class_ini.cpp
class_webserver.o:class_webserver.cpp
	$(CC) $(DEBUG) -o $@ -c class_webserver.cpp
class_request.o:class_request.cpp
	$(CC) $(DEBUG) -o $@ -c class_request.cpp
kp/lib_kp.a:
	cd kp;$(MAKE) lib_kp.a;cd ..;
commu/libcm.a:
	@echo "make libcm.a"
	cd commu;$(MAKE) libcm.a;cd ..;
gms/libgms.a:
	@echo "make libgms.a"
	cd gms;$(MAKE) libgms.a;cd ..;
clean:
	rm -f $(OBJECTS) $(EXE) *.exe;cd gms;$(MAKE) clean;cd ..;cd kp;$(MAKE) clean;cd ..;
	@echo "clean is complete"
