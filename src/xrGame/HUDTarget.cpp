#include "stdafx.h"
#include "hudtarget.h"
#include "../xrEngine/gamemtllib.h"

#include "../xrEngine/Environment.h"
#include "../xrEngine/CustomHUD.h"
#include "Entity.h"
#include "level.h"
#include "game_cl_base.h"
#include "../xrEngine/igame_persistent.h"

#include "ui_base.h"
#include "InventoryOwner.h"
#include "relation_registry.h"
#include "character_info.h"

#include "string_table.h"
#include "entity_alive.h"

#include "inventory_item.h"
#include "inventory.h"

#include <ai/monsters/poltergeist/poltergeist.h>

u32 C_ON_ENEMY D3DCOLOR_RGBA(0xff, 0, 0, 0x80);
u32 C_ON_NEUTRAL D3DCOLOR_RGBA(0xff, 0xff, 0x80, 0x80);
u32 C_ON_FRIEND D3DCOLOR_RGBA(0, 0xff, 0, 0x80);

#define C_DEFAULT D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0x80)
#define C_SIZE 0.025f
#define NEAR_LIM 0.5f

#define SHOW_INFO_SPEED 0.5f
#define HIDE_INFO_SPEED 10.f

IC float recon_mindist() { return 2.f; }
IC float recon_maxdist() { return 50.f; }
IC float recon_minspeed() { return 0.5f; }
IC float recon_maxspeed() { return 10.f; }

CHUDTarget::CHUDTarget()
{
    fuzzyShowInfo = 0.f;
    PP.RQ.range = 0.f;
    hShader->create("hud\\cursor", "ui\\cursor");

    PP.RQ.set(NULL, 0.f, -1);

    Load();
    m_bShowCrosshair = false;
}

CHUDTarget::~CHUDTarget() {}

void CHUDTarget::Load() { HUDCrosshair.Load(); }

void CHUDTarget::ShowCrosshair(bool b) { m_bShowCrosshair = b; }
//. fVisTransparencyFactor
float fCurrentPickPower;
ICF static BOOL pick_trace_callback(collide::rq_result& result, LPVOID params)
{
    SPickParam* pp = (SPickParam*)params;
    //	collide::rq_result* RQ	= pp->RQ;
    ++pp->pass;

    if (result.O)
    {
        pp->RQ = result;
        return FALSE;
    }
    else
    {
        // �������� ����������� � ������ ��� ��������
        CDB::TRI* T = Level().ObjectSpace.GetStaticTris() + result.element;

        SGameMtl* mtl = GMLib.GetMaterialByIdx(T->material);
        pp->power *= mtl->fVisTransparencyFactor;
        if (pp->power > 0.34f)
        {
            return TRUE;
        }
        //.		if (mtl->Flags.is(SGameMtl::flPassable))
        //.			return TRUE;
    }
    pp->RQ = result;
    return FALSE;
}

void CHUDTarget::CursorOnFrame()
{
    Fvector p1, dir;

    p1 = Device.vCameraPosition;
    dir = Device.vCameraDirection;

    // Render cursor
    if (Level().CurrentEntity())
    {
        PP.RQ.O = 0;
        PP.RQ.range = g_pGamePersistent->Environment().CurrentEnv->far_plane * 0.99f;
        PP.RQ.element = -1;

        collide::ray_defs RD(p1, dir, PP.RQ.range, CDB::OPT_CULL, collide::rqtBoth);
        RQR.r_clear();
        VERIFY(!fis_zero(RD.dir.square_magnitude()));

        PP.power = 1.0f;
        PP.pass = 0;

        if (Level().ObjectSpace.RayQuery(RQR, RD, pick_trace_callback, &PP, NULL, Level().CurrentEntity()))
            clamp(PP.RQ.range, NEAR_LIM, PP.RQ.range);
    }
}

extern ENGINE_API BOOL g_bRendering;
void CHUDTarget::Render()
{
    BOOL b_do_rendering = (psHUD_Flags.is(HUD_CROSSHAIR | HUD_CROSSHAIR_RT | HUD_CROSSHAIR_RT2));

    if (!b_do_rendering)
        return;

    VERIFY(g_bRendering);

    CObject* O = Level().CurrentEntity();
    if (0 == O)
        return;
    CEntity* E = smart_cast<CEntity*>(O);
    if (0 == E)
        return;

    Fvector p1 = Device.vCameraPosition;
    Fvector dir = Device.vCameraDirection;

    // Render cursor
    u32 C = C_DEFAULT;

    Fvector p2;
    p2.mad(p1, dir, PP.RQ.range);
    Fvector4 pt;
    Device.mFullTransform.transform(pt, p2);
    pt.y = -pt.y;
    float di_size = C_SIZE / powf(pt.w, .2f);

    CGameFont* F = UI().Font().pFontGraffiti19Russian;
    F->SetAligment(CGameFont::alCenter);
    F->OutSetI(0.f, 0.05f);
}

void CHUDTarget::net_Relcase(CObject* O)
{
    if (PP.RQ.O == O)
        PP.RQ.O = NULL;

    RQR.r_clear();
}
