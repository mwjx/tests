#zll,2006-5-31
#----------说明------------
#根据不同平台设置相应的头文件和库文件
#包含本文件之前必须定义DIR_LIB这个变量
#DIR_LIB = ../lib/
#---------end 说明---------
#winxp
ifeq ($(SYS),winxp)
LIBS = #-L"D:/tools/Dev-Cpp/lib" -LD:/tools/mysql/lib/tmp -lmysqlclient2 -lws2_32 -L"D:/tools/Dev-Cpp/pthread/Pre-built.2/lib" -lpthreadGC2
INCS = -I"D:/tools/Dev-Cpp/include"
CXXINCS = -I"D:/tools/Dev-Cpp/include/c++/3.3.1"  -I"D:/tools/Dev-Cpp/include/c++/3.3.1/mingw32"  -I"D:/tools/Dev-Cpp/include/c++/3.3.1/backward"  -I"D:/tools/Dev-Cpp/lib/gcc-lib/mingw32/3.3.1/include"  -I"D:/tools/mysql/include" -I"D:/tools/Dev-Cpp/pthread/Pre-built.2/include"
LINKLIB = $(DIR_LIB)libgfun.xp.a
endif
#linux
ifeq ($(SYS),linux)
LIBS = -L"/usr/lib/mysql" -lmysqlclient -lz
INCS = -I"/usr/include/mysql" 
CXXINCS =
LINKLIB = $(DIR_LIB)libmysql_linux.a
endif
#FreeBSD4.7
ifeq ($(SYS),bsd47)
LIBS = -L"/usr/lib/mysql" -lmysqlclient -lz
INCS = -I"/usr/include/mysql" 
CXXINCS =
LINKLIB = $(DIR_LIB)libinistl_freebsd47.a $(DIR_LIB)libmysql_freebsd47.a
MAKE = gmake
endif
#FreeBSD5.4
ifeq ($(SYS),bsd54)
LIBS = -L"/usr/lib/mysql" -lmysqlclient -lz
INCS = -I"/usr/include/mysql" 
CXXINCS =
LINKLIB = $(DIR_LIB)libinistl_bsd54.a $(DIR_LIB)libmysql_freebsd54.a
MAKE = gmake
endif
#FreeBSD7.0
ifeq ($(SYS),bsd70)
LIBS = #-L"/usr/local/lib/mysql" -lmysqlclient -lz
INCS = -I"/usr/local/include/mysql"
CXXINCS =
LINKLIB = $(DIR_LIB)libgfun.bsd70.a
MAKE = gmake
endif
#mac
ifeq ($(SYS),mac)
LIBS = -L"/usr/local/mysql/lib" -lmysqlclient -lz
INCS = -I"/usr/local/mysql/include"
CXXINCS = 
LINKLIB = $(DIR_LIB)libgfun.mac.a
endif
