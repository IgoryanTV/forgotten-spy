#pragma once

#ifdef GAMEUI2_DLL
#include "tier1/interface.h"
#else
#include "interface.h"
#endif
#include "vgui/VGUI.h"
#include "mathlib/vector.h"

abstract_class IGameUI2 : public IBaseInterface
{
public:
	virtual void		Initialize(CreateInterfaceFn appFactory) = 0;
	virtual void		Shutdown() = 0;

	virtual bool		IsInLevel() = 0;
	virtual bool		IsInBackgroundLevel() = 0;
	virtual bool		IsInMultiplayer() = 0;
	virtual bool		IsInLoading() = 0;

	virtual Vector2D	GetViewport() = 0;
	virtual float		GetTime() = 0;
	virtual vgui::VPANEL GetRootPanel() = 0;
};

#define GAMEUI2_DLL_INTERFACE_VERSION "GAMEUI2_V001"