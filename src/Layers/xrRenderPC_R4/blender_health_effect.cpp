#include "stdafx.h"
#pragma hdrstop

#include "blender_health_effect.h"

CBlender_health_effect::CBlender_health_effect() { description.CLS = 0; }
CBlender_health_effect::~CBlender_health_effect() {}

void CBlender_health_effect::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);

    C.r_Pass("stub_screen_space", "actor_health_effect", FALSE, FALSE, FALSE);
    C.r_dx10Texture("s_image", r2_RT_generic0);
    C.r_dx10Sampler("smp_rtlinear");
    C.r_dx10Sampler("smp_linear");
    C.r_End();
}
