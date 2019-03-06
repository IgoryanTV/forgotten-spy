#pragma once

#include "vgui_controls/Panel.h"
#include "GameUI/IGameUI.h"

class BasePanel : public vgui::Panel
{
	DECLARE_CLASS_SIMPLE(BasePanel, vgui::Panel);

public:
	BasePanel(vgui::VPANEL parent);

	static void			Create();
	virtual void 		OnThink();
	
	virtual bool		IsBackgroundMusicPlaying();
	virtual bool		StartBackgroundMusic(float fVol);
	virtual void		UpdateBackgroundMusicVolume(float fVol);
	virtual void		ReleaseBackgroundMusic();

private:
	IGameUI*			m_pGameUI;
	CUtlString			m_backgroundMusic;
	int32				m_nBackgroundMusicGUID;
};

extern BasePanel* GetBasePanel();