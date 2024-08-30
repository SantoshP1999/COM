del *.dll

del *.exp

del *.lib

del *.obj

cl.exe /c /EHsc QIPropDllServer.cpp

link.exe QIPropDllServer.obj /DLL /DEF:QIPropDllServer.def User32.lib /SUBSYSTEM:WINDOWS