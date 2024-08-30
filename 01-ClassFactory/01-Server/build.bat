del *.dll

del *.exp

del *.lib

del *.obj

cl.exe /c /EHsc ClassFactoryDllServerWithRegFile.cpp

link.exe ClassFactoryDllServerWithRegFile.obj /DLL /DEF:ClassFactoryDllServerWithRegFile.def User32.lib /SUBSYSTEM:WINDOWS