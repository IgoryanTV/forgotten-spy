"MainMenu"
{	
	"ResumeGame"
	{
		"text"			"#GameUI2_ResumeGame"
		"description"	"#GameUI2_ResumeGameDescription"
		"command"		"cvar gamemenucommand resumegame"
		"priority"		"6"
		"specifics"		"ingame"
	}
	
	"SaveGame"
	{
		"text"			"#GameUI2_SaveGame"
		"description"	"#GameUI2_SaveGameDescription"
		"command"		"cvar gamemenucommand opensavegamedialog"
		"priority"		"5"
		"specifics"		"ingame"
	}
	
	"NewGame"
	{
		"text"			"#GameUI2_NewGame"
		"description"	"#GameUI2_NewGameDescription"
		"command"		"cvar gamemenucommand opennewgamedialog"
		"priority"		"45"
		"specifics"		"mainmenu"
	}
	
	"LoadGame"
	{
		"text"			"#GameUI2_LoadGame"
		"description"	"#GameUI2_LoadGameDescription"
		"command"		"cvar gamemenucommand openloadgamedialog"
		"priority"		"4"
		"specifics"		"shared"
	}
	
	"Options"
	{
		"text"			"#GameUI2_Options"
		"description"	"#GameUI2_OptionsDescription"
		"command"		"cvar gamemenucommand openoptionsdialog"
		"priority"		"3"
		"specifics"		"shared"
	}
	
	"Main"
	{
		"text"			"#GameUI2_Main"
		"description"	"#GameUI2_MainDescription"
		"command"		"cvar gamemenucommand disconnect"
		"priority"		"2"
		"specifics"		"ingame"
	}

	"Quit"
	{
		"text"			"#GameUI2_Quit"
		"description"	"#GameUI2_QuitDescription"
		"command"		"cvar gamemenucommand quit"
		"priority"		"1"
		"specifics"		"shared"
	}
}