#-------需要根据不同平台设置的值----------
#make,gmake
#在windows平台时SYS值为win2000,winxp,bsd47,linux,bsd54,bsd70,mac
SYS = winxp
#LV是库的版本，不同版本stl的hash容器头文件可能不同,取值-D LV或空
LV = 
#DEBUG是否调试版本,-D DEBUG,-D NDEBUG, -g打印gdb信息
DEBUG = -D DEBUG $(LV) -g
#DEBUG = -D NDEBUG $(LV)
#-----------常用变量----------
CC = g++
OPTIONS = -o3
MAKE = make
DIR_INC = 
DIR_LIB = 
#--------end 需要根据不同平台设置的值-----
