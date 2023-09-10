#include "stdafx.h"
#pragma hdrstop

#include "blender_stamina_effect.h"

CBlender_stamina_effect::CBlender_stamina_effect() { description.CLS = 0; }
CBlender_stamina_effect::~CBlender_stamina_effect() {}

void CBlender_stamina_effect::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);

    C.r_Pass("stub_screen_space", "actor_stamina_effect", FALSE, FALSE, FALSE);
    C.r_dx10Texture("s_image", r2_RT_generic0);
    C.r_dx10Sampler("smp_rtlinear");
    C.r_End();
}
