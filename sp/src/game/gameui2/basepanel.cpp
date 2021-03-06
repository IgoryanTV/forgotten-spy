#include "gameui2_interface.h"
#include "basepanel.h"

#include "mainmenu.h"

#include "vgui/IVGui.h"
#include "vgui/ISurface.h"
#include "vgui/ILocalize.h"

#include "tier0/icommandline.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static CDllDemandLoader g_GameUI("GameUI");
static BasePanel* g_pBasePanel;
BasePanel* GetBasePanel()
{
	return g_pBasePanel;
}

BasePanel::BasePanel(vgui::VPANEL parent) : BaseClass(NULL)
{
	SetParent(parent);
	SetPaintBorderEnabled(false);
	SetPaintBackgroundEnabled(false);
	SetKeyBoardInputEnabled(true);
	SetMouseInputEnabled(true);
	SetProportional(false);
	SetVisible(false);

	m_backgroundMusic = "Interface.Music";
	m_nBackgroundMusicGUID = 0;

	CreateInterfaceFn gameUIFactory = g_GameUI.GetFactory();
	if (gameUIFactory)
	{
		m_pGameUI = (IGameUI*)gameUIFactory(GAMEUI_INTERFACE_VERSION, NULL);
		if (m_pGameUI)
			m_pGameUI->SetMainMenuOverride(GetVPanel());
	}

	g_pVGuiLocalize->AddFile("resource2/gameui2_%language%.txt");

	MainMenuHelper* pMMHelper = new MainMenuHelper(new MainMenu(NULL), NULL);
	if (pMMHelper)
		pMMHelper->SetParent((vgui::VPANEL)parent);
}

void BasePanel::Create()
{
	ConColorMsg(Color(0, 148, 255, 255), "Trying to create BasePanel...\n");

	if (g_pBasePanel == nullptr)
	{
		g_pBasePanel = new BasePanel(GameUI2().GetRootPanel());
		ConColorMsg(Color(0, 148, 255, 255), "BasePanel created.\n");
	}
	else
	{
		ConColorMsg(Color(0, 148, 255, 255), "BasePanel already exists.\n");
	}
}

void BasePanel::OnThink()
{
	BaseClass::OnThink();

	SetBounds(0, 0, GameUI2().GetViewport().x, GameUI2().GetViewport().y);

	if (!CommandLine()->FindParm("-nostartupsound"))
	{
		if (!IsBackgroundMusicPlaying())
		{
			if (GameUI2().IsInBackgroundLevel() || !GameUI2().IsInLevel())
				StartBackgroundMusic(1.0f);
		}
		else if (IsBackgroundMusicPlaying())
		{
			if (!GameUI2().IsInBackgroundLevel() || GameUI2().IsInLevel())
				ReleaseBackgroundMusic();
		}
	}
}

bool BasePanel::IsBackgroundMusicPlaying()
{
	if (m_backgroundMusic.IsEmpty())
		return false;

	if (m_nBackgroundMusicGUID == 0)
		return false;

	return enginesound->IsSoundStillPlaying(m_nBackgroundMusicGUID);
}

#define BACKGROUND_MUSIC_DUCK 0.15f

bool BasePanel::StartBackgroundMusic(float fVol)
{
	if (IsBackgroundMusicPlaying())
		return true;

	if (m_backgroundMusic.IsEmpty())
		return false;

	CSoundParameters params;
	if (!soundemitterbase->GetParametersForSound(m_backgroundMusic.Get(), params, GENDER_NONE))
		return false;

	enginesound->EmitAmbientSound(params.soundname, params.volume * fVol, params.pitch);
	m_nBackgroundMusicGUID = enginesound->GetGuidForLastSoundEmitted();

	return (m_nBackgroundMusicGUID != 0);
}

void BasePanel::UpdateBackgroundMusicVolume(float fVol)
{
	if (!IsBackgroundMusicPlaying())
		return;

	enginesound->SetVolumeByGuid(m_nBackgroundMusicGUID, BACKGROUND_MUSIC_DUCK * fVol);
}

void BasePanel::ReleaseBackgroundMusic()
{
	if (m_backgroundMusic.IsEmpty())
		return;

	if (m_nBackgroundMusicGUID == 0)
		return;

	enginesound->StopSoundByGuid(m_nBackgroundMusicGUID);

	m_nBackgroundMusicGUID = 0;
}