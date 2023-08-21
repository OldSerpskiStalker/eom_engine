#include "stdafx.h"
#pragma hdrstop

#include "Blender_zoom.h"

CBlender_zoom::CBlender_zoom() { description.CLS = 0; }
CBlender_zoom::~CBlender_zoom() {}

void CBlender_zoom::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);
    switch (C.iElement)
    {
    case 0: // no dis
        C.r_Pass("stub_notransform_aa_AA", "zoom", FALSE, FALSE, FALSE);
        C.r_dx10Texture("s_position", r2_RT_P);
        C.r_dx10Texture("s_normal", r2_RT_N);
        C.r_dx10Texture("s_image", r2_RT_generic0);
        C.r_dx10Texture("s_bloom", r2_RT_bloom1);
        C.r_dx10Texture("s_distort", r2_RT_generic1);
        C.r_dx10Texture("s_lut", "shaders\\lut_palettes");

        C.r_dx10Sampler("smp_nofilter");
        C.r_dx10Sampler("smp_rtlinear");
        C.r_End();
        break;
    case 1: // dis
        C.r_Pass("stub_notransform_aa_AA", "zoom_dis", FALSE, FALSE, FALSE);
        C.r_dx10Texture("s_position", r2_RT_P);
        C.r_dx10Texture("s_normal", r2_RT_N);
        C.r_dx10Texture("s_image", r2_RT_generic0);
        C.r_dx10Texture("s_bloom", r2_RT_bloom1);
        C.r_dx10Texture("s_distort", r2_RT_generic1);
        C.r_dx10Texture("s_lut", "shaders\\lut_palettes");

        C.r_dx10Sampler("smp_nofilter");
        C.r_dx10Sampler("smp_rtlinear");
        C.r_End();
        break;
    }
}

CBlender_zoom_MSAA::CBlender_zoom_MSAA() { description.CLS = 0; }
CBlender_zoom_MSAA::~CBlender_zoom_MSAA() {}

void CBlender_zoom_MSAA::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);

    if (Name)
        ::Render->m_MSAASample = atoi(Definition);
    else
        ::Render->m_MSAASample = -1;

    switch (C.iElement)
    {
    case 0: // no dis
        C.r_Pass("stub_notransform_aa_AA", "zoom", FALSE, FALSE, FALSE);
        C.r_dx10Texture("s_position", r2_RT_P);
        C.r_dx10Texture("s_normal", r2_RT_N);
        C.r_dx10Texture("s_image", r2_RT_generic0);
        C.r_dx10Texture("s_bloom", r2_RT_bloom1);
        C.r_dx10Texture("s_distort", r2_RT_generic1_r);
        C.r_dx10Texture("s_lut", "shaders\\lut_palettes");

        C.r_dx10Sampler("smp_nofilter");
        C.r_dx10Sampler("smp_rtlinear");
        C.r_End();
        break;
    case 1: // dis
        C.r_Pass("stub_notransform_aa_AA", "zoom_dis", FALSE, FALSE, TRUE);
        C.r_dx10Texture("s_position", r2_RT_P);
        C.r_dx10Texture("s_normal", r2_RT_N);
        C.r_dx10Texture("s_image", r2_RT_generic0);
        C.r_dx10Texture("s_bloom", r2_RT_bloom1);
        C.r_dx10Texture("s_distort", r2_RT_generic1_r);
        C.r_dx10Texture("s_lut", "shaders\\lut_palettes");

        C.r_dx10Sampler("smp_nofilter");
        C.r_dx10Sampler("smp_rtlinear");
        C.r_End();
        break;
    }

    ::Render->m_MSAASample = -1;
}
