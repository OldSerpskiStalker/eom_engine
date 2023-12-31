#include "stdafx.h"
#include "r4_rendertarget.h"

void CRenderTarget::phase_fxaa()
{
    u32 Offset = 0;
    float _w = float(Device.dwWidth);
    float _h = float(Device.dwHeight);
    float du = ps_r1_pps_u, dv = ps_r1_pps_v;

    ref_rt& dest_rt = RImplementation.o.dx10_msaa ? rt_Generic : rt_Color;
    u_setrt(dest_rt, nullptr, nullptr, nullptr);

    FVF::V* pv = (FVF::V*)RCache.Vertex.Lock(4, g_fxaa->vb_stride, Offset);
    pv->set(du + 0, dv + float(_h), 0, 0, 1);
    pv++;
    pv->set(du + 0, dv + 0, 0, 0, 0);
    pv++;
    pv->set(du + float(_w), dv + float(_h), 0, 1, 1);
    pv++;
    pv->set(du + float(_w), dv + 0, 0, 1, 0);
    pv++;
    RCache.Vertex.Unlock(4, g_fxaa->vb_stride);

    RCache.set_Element(s_fxaa->E[0]);
    RCache.set_Geometry(g_fxaa);
    RCache.Render(D3DPT_TRIANGLELIST, Offset, 0, 4, 0, 2);

    HW.pContext->CopyResource(rt_Generic_0->pTexture->surface_get(), dest_rt->pTexture->surface_get());
}
