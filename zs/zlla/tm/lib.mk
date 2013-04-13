#zll,2006-5-31
#----------说明------------
#根据不同平台设置相应的头文件和库文件
#包含本文件之前必须定义DIR_LIB这个变量
#DIR_LIB = ../lib/
#---------end 说明---------
#winxp
ifeq ($(SYS),winxp)
LIBS = -L"D:/tools/Dev-Cpp/pthread/Pre-built.2/lib" -lpthreadGC2 -L"D:/tools/Dev-Cpp/lib" -lws2_32
LINKLIB = $(DIR_LIB)libtm.xp.a
LINKS = $(DIR_LIB)libsmpth.xp.a
endif
#FreeBSD7.0
ifeq ($(SYS),bsd70)
INCS = -I"/usr/local/include/mysql"
LIBS = -lpthread
LINKLIB = $(DIR_LIB)libtm.bsd70.a
LINKS = $(DIR_LIB)libsmpth.bsd70.a
MAKE = gmake
endif
#mac
ifeq ($(SYS),mac)
INCS = -I"/usr/local/mysql/include"
LIBS = -lpthread
LINKLIB = $(DIR_LIB)libtm.mac.a
LINKS = $(DIR_LIB)libsmpth.mac.a
endif

