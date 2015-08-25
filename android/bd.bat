@echo off

d:

SET DIRROOT=D:\java\zjtest
SET PATHCP=D:\tools\sdk\android.jar
SET MORECP=%DIRROOT%\libs\android-support-v4.jar;%DIRROOT%\libs\xxx.jar
SET PATHPAGE=com/example/zjtest
SET PNAME=zjtest

goto s_zjtest
:s_zjtest

cd %DIRROOT%


echo 开始资源
rm -rf bin/resources.res
rm -rf gen/com
aapt p -f -v -M AndroidManifest.xml -I %PATHCP% -S res -J gen


echo 开始编译
rm -rf bin/classes
cd bin
mkdir classes
cd ..
javac -verbose -cp %PATHCP%%MORECP% -d ./bin/classes ./src/%PATHPAGE%/*.java ./gen/R.java



echo 开始字节码
rm -rf bin/classes.dex
call dx --dex --verbose --no-strict --output=%DIRROOT%\bin\classes.dex %DIRROOT%\bin\classes



echo 开始打包
rm -rf bin/%PNAME%.apk
rm -rf bin/signed%PNAME%.apk
aapt package -u -z -f -v -M AndroidManifest.xml -I %PATHCP% -S res -A assets -F bin/%PNAME%.apk
cd bin
aapt add %PNAME%.apk classes.dex



echo 开始签名
jarsigner -verbose -digestalg SHA1 -sigalg MD5withRSA -keystore c:\android.keystore -signedjar signed%PNAME%.apk %PNAME%.apk android.keystore
rm -rf %PNAME%.apk
jarsigner -verbose -verify signed%PNAME%.apk


echo 全部完成

