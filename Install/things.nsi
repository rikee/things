Name "Things"

OutFile "Things_Installer.exe"

InstallDir $PROGRAMFILES\Things

Name "Things"

DirText "Choose a directory."

Page directory
Page instfiles

Section "MainSection" SEC01

	SetOutPath $INSTDIR

	WriteUninstaller "$INSTDIR\uninstall.exe"

	CreateShortCut "$DESKTOP\Things.lnk" "$INSTDIR\things.exe"

	File things.exe
	File record.tng
	File cards_sprite.png
	File cards_sprite_negative.png
	File kings_empty.png
	File icon.ico

	AccessControl::GrantOnFile "$INSTDIR\record.tng" "(BU)" "FullAccess"

SectionEnd

Section "uninstall"

	Delete "$DESKTOP\Things.lnk"

	Delete $INSTDIR\things.exe
	Delete $INSTDIR\record.tng
	Delete $INSTDIR\cards_sprite.png
	Delete $INSTDIR\cards_sprite_negative.png
	Delete $INSTDIR\kings_empty.png
	Delete $INSTDIR\icon.ico

	Delete $INSTDIR\uninstall.exe

	rmDir $INSTDIR

SectionEnd