#include "stdafx.h"
#pragma hdrstop

#include "Blender_rain_drops.h"

CBlender_rain_drops::CBlender_rain_drops() { description.CLS = 0; }
CBlender_rain_drops::~CBlender_rain_drops() {}

void CBlender_rain_drops::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);

    C.r_Pass("stub_screen_space", "rain_drops", FALSE, FALSE, FALSE);
    C.r_dx10Texture("s_image", r2_RT_generic0);
    C.r_dx10Texture("s_rain_drops1", "shaders\\shaders_drops_glass_1");
    C.r_dx10Texture("s_rain_drops2", "shaders\\shaders_drops_glass_2");
    C.r_dx10Texture("s_rain_drops3", "shaders\\shaders_drops_glass_3");
    C.r_dx10Texture("s_rain_drops4", "shaders\\shaders_drops_glass_4");
    C.r_dx10Texture("s_rain_drops5", "shaders\\shaders_drops_glass_5");

    C.r_dx10Texture("s_rain_drops6", "shaders\\shaders_drops_glass_1_no");
    C.r_dx10Texture("s_rain_drops7", "shaders\\shaders_drops_glass_2_no");
    C.r_dx10Texture("s_rain_drops8", "shaders\\shaders_drops_glass_3_no");
    C.r_dx10Texture("s_rain_drops9", "shaders\\shaders_drops_glass_4_no");
    C.r_dx10Texture("s_rain_drops10", "shaders\\shaders_drops_glass_5_no");
    C.r_dx10Sampler("smp_rtlinear");
    C.r_End();
}
