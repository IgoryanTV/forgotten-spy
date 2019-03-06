#include "gameui2_interface.h"
#include "button_mainmenu.h"

#include "vgui/ILocalize.h"
#include "vgui/ISurface.h"
#include "vgui/IVGui.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DECLARE_BUILD_FACTORY_DEFAULT_TEXT(Button_MainMenu, Button_MainMenu);

extern CUtlSymbolTable g_ButtonSoundNames;

Button_MainMenu::Button_MainMenu(vgui::Panel* parent, vgui::Panel* pActionSignalTarget, const char* pCmd) : BaseClass(parent, "", "", pActionSignalTarget, pCmd)
{
	Init();
	m_pCmd = pCmd;
}

void Button_MainMenu::SetButtonText(const char* text)
{
	if (text[0] == '#')
	{
		wchar_t* tempString = g_pVGuiLocalize->Find(text);
		if (tempString)
		{
			wcsncpy(m_ButtonText, tempString, sizeof(m_ButtonText) / sizeof(wchar_t));
			m_ButtonText[(sizeof(m_ButtonText) / sizeof(wchar_t)) - 1] = 0;
		}
		else
		{
			const size_t cSizeText = strlen(text) + 1;
			mbstowcs(m_ButtonText, text, cSizeText);
		}
	}
	else
	{
		const size_t cSizeText = strlen(text) + 1;
		mbstowcs(m_ButtonText, text, cSizeText);
	}
}

void Button_MainMenu::SetButtonDescription(const char* description)
{
	if (description[0] == '#')
	{
		wchar_t* tempString = g_pVGuiLocalize->Find(description);
		if (tempString)
		{
			wcsncpy(m_ButtonDescription, tempString, sizeof(m_ButtonDescription) / sizeof(wchar_t));
			m_ButtonDescription[(sizeof(m_ButtonDescription) / sizeof(wchar_t)) - 1] = 0;
		}
		else
		{
			const size_t cSizeDescription = strlen(description) + 1;
			mbstowcs(m_ButtonDescription, description, cSizeDescription);
		}
	}
	else
	{
		const size_t cSizeDescription = strlen(description) + 1;
		mbstowcs(m_ButtonDescription, description, cSizeDescription);
	}
}

void Button_MainMenu::Init()
{
	vgui::HScheme Scheme = vgui::scheme()->LoadSchemeFromFile("resource2/schememainmenu.res", "SchemeMainMenu");
	SetScheme(Scheme);

	m_pAnimController = new vgui::AnimationController(this);
	m_pAnimController->SetScheme(Scheme);
	m_pAnimController->SetProportional(false);

	SetProportional(false);
	SetPaintBorderEnabled(false);
	SetPaintBackgroundEnabled(false);
	SetEnabled(true);
	SetVisible(false);
}

void Button_MainMenu::ApplySchemeSettings(vgui::IScheme* pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);

	SetDefaultColor(Color(0, 0, 0, 0), Color(0, 0, 0, 0));
	SetArmedColor(Color(0, 0, 0, 0), Color(0, 0, 0, 0));
	SetSelectedColor(Color(0, 0, 0, 0), Color(0, 0, 0, 0));
	SetDepressedColor(Color(0, 0, 0, 0), Color(0, 0, 0, 0));
	SetBlinkColor(Color(0, 0, 0, 0));
	SetArmedSound("interface/ui/button_over.wav");
	SetDepressedSound("interface/ui/button_click.wav");
	SetReleasedSound("interface/ui/button_release.wav");

	m_fWidth = m_fWidthOut = atof(pScheme->GetResourceString("MainMenu.Button.WidthOut"));
	m_fWidthOver = atof(pScheme->GetResourceString("MainMenu.Button.WidthOver"));
	m_fWidthPressed = atof(pScheme->GetResourceString("MainMenu.Button.WidthPressed"));
	m_fWidthReleased = atof(pScheme->GetResourceString("MainMenu.Button.WidthReleased"));

	m_fHeight = m_fHeightOut = atof(pScheme->GetResourceString("MainMenu.Button.HeightOut"));
	m_fHeightOver = atof(pScheme->GetResourceString("MainMenu.Button.HeightOver"));
	m_fHeightPressed = atof(pScheme->GetResourceString("MainMenu.Button.HeightPressed"));
	m_fHeightReleased = atof(pScheme->GetResourceString("MainMenu.Button.HeightReleased"));

	m_fTextOffsetX = atof(pScheme->GetResourceString("MainMenu.Button.TextOffsetX"));
	m_fTextOffsetY = atof(pScheme->GetResourceString("MainMenu.Button.TextOffsetY"));

	m_fDescriptionOffsetX = atof(pScheme->GetResourceString("MainMenu.Button.DescriptionOffsetX"));
	m_fDescriptionOffsetY = atof(pScheme->GetResourceString("MainMenu.Button.DescriptionOffsetY"));

	m_bDescriptionHideOut = atoi(pScheme->GetResourceString("MainMenu.Button.DescriptionHideOut"));
	m_bDescriptionHideOver = atoi(pScheme->GetResourceString("MainMenu.Button.DescriptionHideOver"));
	m_bDescriptionHidePressed = atoi(pScheme->GetResourceString("MainMenu.Button.DescriptionHidePressed"));
	m_bDescriptionHideReleased = atoi(pScheme->GetResourceString("MainMenu.Button.DescriptionHideReleased"));

	m_fAnimationWidth = atof(pScheme->GetResourceString("MainMenu.Button.AnimationWidth"));
	m_fAnimationHeight = atof(pScheme->GetResourceString("MainMenu.Button.AnimationHeight"));
	m_fAnimationBackground = atof(pScheme->GetResourceString("MainMenu.Button.AnimationBackground"));
	m_fAnimationText = atof(pScheme->GetResourceString("MainMenu.Button.AnimationText"));
	m_fAnimationDescription = atof(pScheme->GetResourceString("MainMenu.Button.AnimationDescription"));

	m_cBackground = m_cBackgroundOut = GetSchemeColor("MainMenu.Button.BackgroundOut", pScheme);
	m_cBackgroundOver = GetSchemeColor("MainMenu.Button.BackgroundOver", pScheme);
	m_cBackgroundPressed = GetSchemeColor("MainMenu.Button.BackgroundPressed", pScheme);
	m_cBackgroundReleased = GetSchemeColor("MainMenu.Button.BackgroundReleased", pScheme);

	m_cText = m_cTextOut = GetSchemeColor("MainMenu.Button.TextOut", pScheme);
	m_cTextOver = GetSchemeColor("MainMenu.Button.TextOver", pScheme);
	m_cTextPressed = GetSchemeColor("MainMenu.Button.TextPressed", pScheme);
	m_cTextReleased = GetSchemeColor("MainMenu.Button.TextReleased", pScheme);

	m_cDescription = m_cDescriptionOut = GetSchemeColor("MainMenu.Button.DescriptionOut", pScheme);
	m_cDescriptionOver = GetSchemeColor("MainMenu.Button.DescriptionOver", pScheme);
	m_cDescriptionPressed = GetSchemeColor("MainMenu.Button.DescriptionPressed", pScheme);
	m_cDescriptionReleased = GetSchemeColor("MainMenu.Button.DescriptionReleased", pScheme);

	m_fTextFont = pScheme->GetFont("MainMenu.Button.TextFont");
	m_fDescriptionFont = pScheme->GetFont("MainMenu.Button.DescriptionFont");

	m_sButtonState = m_sButtonStateOld = Out;
}

void Button_MainMenu::Animations()
{
	if (m_pAnimController != nullptr)
		m_pAnimController->UpdateAnimations(GameUI2().GetTime()); // (gpGlobals->realtime);

	if (m_sButtonStateOld != m_sButtonState && m_pAnimController != nullptr)
	{
		switch (m_sButtonState)
		{
			case Out:
				m_pAnimController->RunAnimationCommand(this, "m_fWidth", m_fWidthOut, 0.0f, m_fAnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_fHeight", m_fHeightOut, 0.0f, m_fAnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackground", m_cBackgroundOut, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cText", m_cTextOut, 0.0f, m_fAnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cDescription", m_cDescriptionOut, 0.0f, m_fAnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;

			case Over:
				m_pAnimController->RunAnimationCommand(this, "m_fWidth", m_fWidthOver, 0.0f, m_fAnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_fHeight", m_fHeightOver, 0.0f, m_fAnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackground", m_cBackgroundOver, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cText", m_cTextOver, 0.0f, m_fAnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cDescription", m_cDescriptionOver, 0.0f, m_fAnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;

			case Pressed:
				m_pAnimController->RunAnimationCommand(this, "m_fWidth", m_fWidthPressed, 0.0f, m_fAnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_fHeight", m_fHeightPressed, 0.0f, m_fAnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackground", m_cBackgroundPressed, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cText", m_cTextPressed, 0.0f, m_fAnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cDescription", m_cDescriptionPressed, 0.0f, m_fAnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;

			case Released:
				m_pAnimController->RunAnimationCommand(this, "m_fWidth", m_fWidthReleased, 0.0f, m_fAnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_fHeight", m_fHeightReleased, 0.0f, m_fAnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackground", m_cBackgroundReleased, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cText", m_cTextReleased, 0.0f, m_fAnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cDescription", m_cDescriptionReleased, 0.0f, m_fAnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;

			default:
				m_pAnimController->RunAnimationCommand(this, "m_fWidth", m_fWidthOut, 0.0f, m_fAnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_fHeight", m_fHeightOut, 0.0f, m_fAnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackground", m_cBackgroundOut, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cText", m_cTextOut, 0.0f, m_fAnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cDescription", m_cDescriptionOut, 0.0f, m_fAnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;
		}

		m_sButtonStateOld = m_sButtonState;
	}

	SetSize(m_fWidth, m_fHeight);
}

void Button_MainMenu::OnThink()
{
	BaseClass::OnThink();

	if (IsVisible() == false)
	{
		ConColorMsg(Color(0, 148, 255, 255), "\nMain menu is not visible, running all animations to completion...\n");

		if (m_pAnimController != nullptr)
			m_pAnimController->RunAllAnimationsToCompletion();
	}
}

void Button_MainMenu::DrawButton()
{
	vgui::surface()->DrawSetColor(m_cBackground);
	vgui::surface()->DrawFilledRect(0, 0, m_fWidth + 0, m_fHeight + 0);
}

void Button_MainMenu::DrawText()
{
	vgui::surface()->DrawSetTextColor(m_cText);
	vgui::surface()->DrawSetTextFont(m_fTextFont);

	vgui::surface()->GetTextSize(m_fTextFont, m_ButtonText, m_iTextSizeX, m_iTextSizeY);
	m_iTextPositionX = m_fTextOffsetX;
	m_iTextPositionY = m_fHeight / 2 - m_iTextSizeY / 2 + m_fTextOffsetY;

	vgui::surface()->DrawSetTextPos(m_iTextPositionX, m_iTextPositionY);
	vgui::surface()->DrawPrintText(m_ButtonText, wcslen(m_ButtonText));
}

void Button_MainMenu::DrawDescription()
{
	if (m_sButtonState == Out && m_bDescriptionHideOut == true ||
		m_sButtonState == Over && m_bDescriptionHideOver == true ||
		m_sButtonState == Pressed && m_bDescriptionHidePressed == true ||
		m_sButtonState == Released && m_bDescriptionHideReleased == true)
		return;

	vgui::surface()->DrawSetTextColor(m_cDescription);
	vgui::surface()->DrawSetTextFont(m_fDescriptionFont);
	vgui::surface()->DrawSetTextPos(m_iTextPositionX + m_fDescriptionOffsetX, m_iTextPositionY + m_iTextSizeY + m_fDescriptionOffsetY);
	vgui::surface()->DrawPrintText(m_ButtonDescription, wcslen(m_ButtonDescription));
}

void Button_MainMenu::Paint()
{
	BaseClass::Paint();

	AdditionalCursorCheck();
	Animations();
	DrawButton();
	DrawText();
	DrawDescription();
}

void Button_MainMenu::OnCursorExited()
{
	BaseClass::OnCursorExited();

	m_sButtonState = Out;
}

void Button_MainMenu::OnCursorEntered()
{
	BaseClass::OnCursorEntered();

	m_sButtonState = Over;
}

void Button_MainMenu::AdditionalCursorCheck()
{
	if (IsCursorOver() == false)
		m_sButtonState = Out;
	else if (IsCursorOver() == true && m_sButtonState == Out)
		m_sButtonState = Over;
}

void Button_MainMenu::OnMousePressed(vgui::MouseCode code)
{
	if (code == MOUSE_LEFT)
	{
		if (m_sDepressedSoundName != UTL_INVAL_SYMBOL)
			vgui::surface()->PlaySound(g_ButtonSoundNames.String(m_sDepressedSoundName));

		m_sButtonState = Pressed;
	}
}

void Button_MainMenu::OnMouseReleased(vgui::MouseCode code)
{
	if (code == MOUSE_LEFT)
	{
		if (m_sReleasedSoundName != UTL_INVAL_SYMBOL)
			vgui::surface()->PlaySound(g_ButtonSoundNames.String(m_sReleasedSoundName));

		m_sButtonState = Released;

		GetParent()->OnCommand(m_pCmd);
	}
}