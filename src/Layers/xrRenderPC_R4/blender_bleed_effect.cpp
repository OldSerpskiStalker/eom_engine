#include "stdafx.h"
#pragma hdrstop

#include "Blender_bleed_effect.h"

CBlender_bleed_effect::CBlender_bleed_effect() { description.CLS = 0; }
CBlender_bleed_effect::~CBlender_bleed_effect() {}

void CBlender_bleed_effect::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);

    C.r_Pass("stub_screen_space", "actor_bleed_effect", FALSE, FALSE, FALSE);
    C.r_dx10Texture("s_image", r2_RT_generic0);
    C.r_dx10Texture("s_bleed_nrm_sample", "shaders\\bleed_nrm");
    C.r_dx10Sampler("smp_rtlinear");
    C.r_dx10Sampler("smp_linear");
    C.r_End();
}
