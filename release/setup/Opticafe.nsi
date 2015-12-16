; Opticafe.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install Opticafe.nsi into a directory that the user selects,

;--------------------------------

; The name of the installer
Name "OpticafeSetup"

; The file to write
OutFile "OpticafeSetup.exe"

; The default installation directory
InstallDir $PROGRAMFILES\Opticafe

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\NSIS_Example2" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "Opticafe (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "Opticafe.exe"
  File "*.dll"
  File "doc\*.pdf"
  File "style.qrc"
  File "style.qss"
  File /r "rc"
  File /r "scripts"
  File /r "platforms"
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\NSIS_Opticafe "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Opticafe" "DisplayName" "NSIS Opticafe"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Opticafe" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Opticafe" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Opticafe" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\Opticafe"
  CreateShortCut "$SMPROGRAMS\Opticafe\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\Opticafe\Opticafe (MakeNSISW).lnk" "$INSTDIR\Opticafe.nsi" "" "$INSTDIR\Opticafe.nsi" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Opticafe"
  DeleteRegKey HKLM SOFTWARE\NSIS_Example2

  ; Remove files and uninstaller
  Delete $INSTDIR\icudt53.dll
  Delete $INSTDIR\icuin53.dll
  Delete $INSTDIR\icuuc53.dll
  Delete $INSTDIR\Qt5Core.dll
  Delete $INSTDIR\Qt5Gui.dll
  Delete $INSTDIR\Qt5OpenGL.dll
  Delete $INSTDIR\Qt5Widgets.dll
  Delete $INSTDIR\uninstall.exe

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Opticafe\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\Opticafe"
  RMDir "$INSTDIR"

SectionEnd
