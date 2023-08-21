#include "stdafx.h"
#pragma hdrstop

#include "Blender_hit_effect.h"

CBlender_hit_effect::CBlender_hit_effect() { description.CLS = 0; }
CBlender_hit_effect::~CBlender_hit_effect() {}

void CBlender_hit_effect::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);

    C.r_Pass("stub_notransform_aa_AA", "actor_hit_effect", FALSE, FALSE, FALSE);
    C.r_dx10Texture("s_image", r2_RT_generic0);
    C.r_dx10Sampler("smp_rtlinear");
    C.r_End();
}
