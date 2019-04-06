#include "gameui2_interface.h"
#include "basepanel.h"

#include "vgui/ILocalize.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IVEngineClient* engine = NULL;
IEngineSound* enginesound = NULL;
IEngineVGui* enginevgui = NULL;
ISoundEmitterSystemBase* soundemitterbase = NULL;

static CGameUI2 g_GameUI2;
CGameUI2& GameUI2()
{
	return g_GameUI2;
}

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CGameUI2, IGameUI2, GAMEUI2_DLL_INTERFACE_VERSION, g_GameUI2);

void CGameUI2::Initialize(CreateInterfaceFn appFactory)
{
	MEM_ALLOC_CREDIT();
	ConnectTier1Libraries(&appFactory, 1);
	ConnectTier2Libraries(&appFactory, 1);
	ConVar_Register(FCVAR_CLIENTDLL);
	ConnectTier3Libraries(&appFactory, 1);

	engine = (IVEngineClient*)appFactory(VENGINE_CLIENT_INTERFACE_VERSION, NULL);
	enginesound = (IEngineSound*)appFactory(IENGINESOUND_CLIENT_INTERFACE_VERSION, NULL);
	enginevgui = (IEngineVGui*)appFactory(VENGINE_VGUI_VERSION, NULL);
	soundemitterbase = (ISoundEmitterSystemBase*)appFactory(SOUNDEMITTERSYSTEM_INTERFACE_VERSION, NULL);

	if (!enginesound || !enginevgui || !engine || !soundemitterbase)
		Error("CGameUI2::Initialize() failed to get necessary interfaces.\n");

	BasePanel::Create();
}

void CGameUI2::Shutdown()
{
	ConVar_Unregister();
	DisconnectTier3Libraries();
	DisconnectTier2Libraries();
	DisconnectTier1Libraries();
}

bool CGameUI2::IsInLevel()
{
	if (engine->IsInGame() && !engine->IsLevelMainMenuBackground())
		return true;

	return false;
}

bool CGameUI2::IsInBackgroundLevel()
{
	if ((engine->IsInGame() && engine->IsLevelMainMenuBackground()) || !engine->IsInGame())
		return true;

	return false;
}

bool CGameUI2::IsInMultiplayer()
{
	return (IsInLevel() && engine->GetMaxClients() > 1);
}

bool CGameUI2::IsInLoading()
{
	return (engine->IsDrawingLoadingImage() || engine->GetLevelName() == 0) || (!IsInLevel() && !IsInBackgroundLevel());
}

Vector2D CGameUI2::GetViewport()
{
	int32 viewportX, viewportY;
	engine->GetScreenSize(viewportX, viewportY);
	return Vector2D(viewportX, viewportY);
}

float CGameUI2::GetTime()
{
	return Plat_FloatTime();
}

vgui::VPANEL CGameUI2::GetRootPanel()
{
	return enginevgui->GetPanel(PANEL_GAMEUIDLL);
}

CON_COMMAND(gameui2_version, "")
{
	ConColorMsg(Color(0, 148, 255, 255), "Label:\t");
	Msg("%s\n", GAMEUI2_DLL_INTERFACE_VERSION);
	ConColorMsg(Color(0, 148, 255, 255), "Date:\t");
	Msg("%s\n", __DATE__);
	ConColorMsg(Color(0, 148, 255, 255), "Time:\t");
	Msg("%s\n", __TIME__);
}