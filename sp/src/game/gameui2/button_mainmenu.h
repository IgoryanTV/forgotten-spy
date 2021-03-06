#pragma once

#include "vgui_controls/Button.h"
#include "vgui_controls/AnimationController.h"

enum ButtonState
{
	Out,
	Over,
	Pressed,
	Released
};

class Button_MainMenu : public vgui::Button
{
	DECLARE_CLASS_SIMPLE(Button_MainMenu, vgui::Button);

public:
	Button_MainMenu(vgui::Panel* parent, vgui::Panel* pActionSignalTarget = NULL, const char* pCmd = NULL);

	virtual void		Init();
	virtual void		ApplySchemeSettings(vgui::IScheme* pScheme);
	virtual void 		OnThink();
	virtual void 		DrawButton();
	virtual void 		DrawText();
	virtual void 		DrawDescription();
	virtual void 		Paint();
	virtual void		Animations();

	virtual void		AdditionalCursorCheck();
	virtual void		OnCursorEntered();
	virtual void		OnCursorExited();
	virtual void		OnMouseReleased(vgui::MouseCode code);
	virtual void		OnMousePressed(vgui::MouseCode code);

	virtual void		SetButtonText(const char* text);
	virtual void		SetButtonDescription(const char* description);

	int32				GetWidth(){ return m_fWidth; }
	int32				GetHeight(){ return m_fHeight; }

	virtual void		SetPriority(int32 Priority) { m_iPriority = Priority; }
	int32				GetPriority() const{ return m_iPriority; }

private:
	ButtonState			m_sButtonState;
	ButtonState			m_sButtonStateOld;
	vgui::AnimationController* m_pAnimController;
	const char* 		m_pCmd;
	wchar_t				m_ButtonText[1024];
	wchar_t				m_ButtonDescription[1024];
	int32				m_iPriority;
	int32				m_iTextPositionX;
	int32				m_iTextPositionY;
	int32				m_iTextSizeX;
	int32				m_iTextSizeY;

	CPanelAnimationVar(float, m_fWidth, "m_fWidth", "340");
	CPanelAnimationVar(float, m_fHeight, "m_fHeight", "0");
	CPanelAnimationVar(Color, m_cBackground, "m_cBackground", "0 0 0 0");
	CPanelAnimationVar(Color, m_cText, "m_cText", "0 0 0 0");
	CPanelAnimationVar(Color, m_cDescription, "m_cDescription", "0 0 0 0");

	float				m_fWidthOut;
	float				m_fWidthOver;
	float				m_fWidthPressed;
	float				m_fWidthReleased;

	float				m_fHeightOut;
	float				m_fHeightOver;
	float				m_fHeightPressed;
	float				m_fHeightReleased;

	float				m_fTextOffsetX;
	float				m_fTextOffsetY;

	float				m_fDescriptionOffsetX;
	float				m_fDescriptionOffsetY;

	bool				m_bDescriptionHideOut;
	bool				m_bDescriptionHideOver;
	bool				m_bDescriptionHidePressed;
	bool				m_bDescriptionHideReleased;

	float				m_fAnimationWidth;
	float				m_fAnimationHeight;
	float				m_fAnimationBackground;
	float				m_fAnimationText;
	float				m_fAnimationDescription;

	Color				m_cBackgroundOut;
	Color				m_cBackgroundOver;
	Color				m_cBackgroundPressed;
	Color				m_cBackgroundReleased;

	Color				m_cTextOut;
	Color				m_cTextOver;
	Color				m_cTextPressed;
	Color				m_cTextReleased;

	Color				m_cDescriptionOut;
	Color				m_cDescriptionOver;
	Color				m_cDescriptionPressed;
	Color				m_cDescriptionReleased;

	vgui::HFont			m_fTextFont;
	vgui::HFont			m_fDescriptionFont;
};