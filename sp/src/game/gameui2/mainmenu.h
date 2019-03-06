#pragma once

#include "vgui_controls/Frame.h"

#include "button_mainmenu.h"

#include <string>
#include <algorithm>
#include <functional>

class MainMenu : public vgui::Frame
{
	DECLARE_CLASS_SIMPLE(MainMenu, vgui::Frame);

public:
	MainMenu(vgui::Panel* parent);

	virtual void		ApplySchemeSettings(vgui::IScheme* pScheme);
	virtual void		CreateMenu(const char* menu);
	virtual void 		OnThink();
	virtual bool		IsVisible();
	virtual void		SetLogoLeft(const char* text);
	virtual void		SetLogoRight(const char* text);
	virtual void 		DrawMainMenu();
	virtual void 		DrawLogo();
	virtual void 		Paint();
	virtual void		OnCommand(char const* cmd);
	virtual void		OnSetFocus();
	virtual void		OnKillFocus();
	virtual bool		Equals(char const* inputA, char const* inputB);

private:
	CUtlVector<Button_MainMenu*> m_pButtons;
	CUtlVector<Button_MainMenu*> m_pButtonsInGame;
	CUtlVector<Button_MainMenu*> m_pButtonsBackground;
	CUtlVector<Button_MainMenu*> m_pButtonsShared;

	bool				m_bFocused;
	wchar_t				m_logoLeft[1024];
	wchar_t				m_logoRight[1024];

	float				m_fButtonsSpace;

	float				m_fButtonsOffsetX;
	float				m_fButtonsOffsetY;

	float				m_fLogoOffsetX;
	float				m_fLogoOffsetY;

	bool				m_bLogoAttachToMenu;

	Color				m_cLogoLeft;
	Color				m_cLogoRight;

	vgui::HFont			m_fLogoFont;
};

class MainMenuHelper : public vgui::Panel
{
	DECLARE_CLASS_SIMPLE(MainMenuHelper, vgui::Panel);

public:
	MainMenuHelper(MainMenu* menu, vgui::Panel* parent);
};