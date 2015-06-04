; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CConFiveView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ConFive.h"
LastPage=0

ClassCount=6
Class1=CConFiveApp
Class2=CConFiveDoc
Class3=CConFiveView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CSet
Resource3=IDD_DIALOG_SET

[CLS:CConFiveApp]
Type=0
HeaderFile=ConFive.h
ImplementationFile=ConFive.cpp
Filter=N
LastObject=CConFiveApp

[CLS:CConFiveDoc]
Type=0
HeaderFile=ConFiveDoc.h
ImplementationFile=ConFiveDoc.cpp
Filter=N
LastObject=CConFiveDoc

[CLS:CConFiveView]
Type=0
HeaderFile=ConFiveView.h
ImplementationFile=ConFiveView.cpp
Filter=C
LastObject=CConFiveView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_START




[CLS:CAboutDlg]
Type=0
HeaderFile=ConFive.cpp
ImplementationFile=ConFive.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_START
Command2=ID_APP_EXIT
Command3=ID_OUTPUTALLLINEINFO
Command4=ID_SEARCHRECORD
Command5=ID_READCM
Command6=ID_SAVECM
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_DIALOG_SET]
Type=1
Class=CSet
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_BLACK,button,1342178055
Control4=IDC_STATIC_WHITE,button,1342178055
Control5=IDC_RADIO_BLC_COM,button,1342373897
Control6=IDC_RADIO_BLC_HUM,button,1342242825
Control7=IDC_RADIO_WHT_COM,button,1342373897
Control8=IDC_RADIO_WHT_HUM,button,1342242825
Control9=IDC_CHECK_FULLSCREEN,button,1342373891

[CLS:CSet]
Type=0
HeaderFile=Set.h
ImplementationFile=Set.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECK_FULLSCREEN
VirtualFilter=dWC

