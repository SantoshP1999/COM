del *.dll

del *.exp

del *.lib

del *.obj

cl.exe /c /EHsc ContainmentOuterComponentWithRegFile.cpp

link.exe ContainmentOuterComponentWithRegFile.obj /DLL /DEF:ContainmentOuterComponentWithRegFile.def User32.lib ole32.lib /SUBSYSTEM:WINDOWS