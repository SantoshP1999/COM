del *.dll

del *.exp

del *.lib

del *.obj

cl.exe /c /EHsc ContainmentInnerComponentWithRegFile.cpp

link.exe ContainmentInnerComponentWithRegFile.obj /DLL /DEF:ContainmentInnerComponentWithRegFile.def User32.lib  /SUBSYSTEM:WINDOWS