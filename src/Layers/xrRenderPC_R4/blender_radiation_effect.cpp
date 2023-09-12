#include "stdafx.h"
#pragma hdrstop

#include "blender_radiation_effect.h"

CBlender_radiation_effect::CBlender_radiation_effect() { description.CLS = 0; }
CBlender_radiation_effect::~CBlender_radiation_effect() {}

void CBlender_radiation_effect::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);

    C.r_Pass("stub_screen_space", "actor_radiation_effect", FALSE, FALSE, FALSE);
    C.r_dx10Texture("s_image", r2_RT_generic0);
    C.r_dx10Texture("s_heathaze", "shaders\\heathaze");
    C.r_dx10Sampler("smp_rtlinear");
    C.r_dx10Sampler("smp_linear");
    C.r_dx10Sampler("smp_nofilter");
    C.r_End();
}
