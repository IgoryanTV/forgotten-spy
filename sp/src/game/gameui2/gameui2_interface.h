#pragma once

#include "igameui2.h"

#include "cdll_int.h"
#include "engine/ienginesound.h"
#include "ienginevgui.h"
#include "SoundEmitterSystem/isoundemittersystembase.h"

class IVEngineClient;
class IEngineSound;
class IEngineVGui;
class ISoundEmitterSystemBase;

class CGameUI2 : public IGameUI2
{
public:
	virtual void		Initialize(CreateInterfaceFn appFactory);
	virtual void		Shutdown();

	virtual bool		IsInLevel();
	virtual bool		IsInBackgroundLevel();
	virtual bool		IsInMultiplayer();
	virtual bool		IsInLoading();

	virtual Vector2D	GetViewport();
	virtual float		GetTime();
	virtual vgui::VPANEL GetRootPanel();
};

extern CGameUI2& GameUI2();
extern IVEngineClient* engine;
extern IEngineSound* enginesound;
extern IEngineVGui* enginevgui;
extern ISoundEmitterSystemBase* soundemitterbase;