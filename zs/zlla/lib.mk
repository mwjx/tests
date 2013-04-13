#zll,2006-5-31
#----------说明------------
#根据不同平台设置相应的头文件和库文件
#包含本文件之前必须定义DIR_LIB这个变量
#DIR_LIB = ../lib/
#---------end 说明---------
#winxp
ifeq ($(SYS),winxp)
INCS = -I"D:/tools/Dev-Cpp/include" -I"D:/tools/Dev-Cpp/lib/gcc-lib/mingw32/3.3.1/include"
CXXINCS = -I"D:/tools/mysql/include" -I"D:/tools/Dev-Cpp/pthread/Pre-built.2/include" -I"E:/code/zlla/inc"
DIR_INC = E:/code/zlla/inc/
DIR_LIB = E:/code/zlla/lib/
endif
#FreeBSD7.0
ifeq ($(SYS),bsd70)
MAKE = gmake
CXXINCS = -I"/usr/home/mwjx/src/zlla/inc"
DIR_INC = /usr/home/mwjx/src/zlla/inc/
DIR_LIB = /usr/home/mwjx/src/zlla/lib/
endif
#mac
ifeq ($(SYS),mac)
CXXINCS = -I"/Users/mahj/src/zlla/inc"
DIR_INC = /Users/mahj/src/zlla/inc/
DIR_LIB = /Users/mahj/src/zlla/lib/
endif


#win200
ifeq ($(SYS),win2000)
LIBS = -L"D:/tools/Dev-Cpp/lib" -LD:/tools/mysql/lib -lmysqlclient
INCS = -I"D:/tools/Dev-Cpp/include"
CXXINCS = -I"D:/tools/Dev-Cpp/include/c++/3.3.1"  -I"D:/tools/Dev-Cpp/include/c++/3.3.1/mingw32"  -I"D:/tools/Dev-Cpp/include/c++/3.3.1/backward"  -I"D:/tools/Dev-Cpp/lib/gcc-lib/mingw32/3.3.1/include"  -I"D:/tools/mysql/include" 
LINKLIB = $(DIR_LIB)libinistl_win2000.a $(DIR_LIB)libmysql_win2000.a
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
