//////////////////////////////////////////////////////////////////////////
//-' CryRay Engine x64 Shaders
//-' Based on shaders from the original Anomaly 1.5.1
//-' As well as an integrated shader pack Screen Space 15.4
//-' Repository with shaders: https://github.com/cryray-team
//-' Also, if you are a shader developer
//-' You can join our server in discord: https://discord.gg/R78uVUZCTR
//-' OldSerpskiStalker7777, CryRay Team
//////////////////////////////////////////////////////////////////////////

#ifndef COMMON_H
#define COMMON_H
#include "Headers\common_s.hlsl"
#include "ScreenSpaceAddon\settings_global.hlsl"

#include "Main\defines.hlsl"
#include "Main\import_params.hlsl"
#include "Main\sampler.hlsl"
#include "Main\uniforms_float2.hlsl"
#include "Main\uniforms_float3.hlsl"
#include "Main\uniforms_float3x4.hlsl"
#include "Main\uniforms_float4.hlsl"
#include "Main\uniforms_float4x4.hlsl"
#include "Main\Texture2D.hlsl"
#include "Main\Texture3D.hlsl"
#include "Main\TextureCube.hlsl"
#include "Main\float_func.hlsl"
#include "Main\float3_func.hlsl"

#include "Headers\common_defines.hlsl"
#include "Headers\common_policies.hlsl"
#include "Main\struct_deffer_flat.hlsl"
#include "Main\struct_v_aa.hlsl"
#include "Main\struct_shadows.hlsl"
#include "Main\struct_ssss.hlsl"
#include "Main\struct_bumped.hlsl"
#include "Main\struct_static.hlsl"
#include "Main\struct_bloom.hlsl"
#include "Main\struct_v2p_tl.hlsl"
#include "Main\struct_v_postpr.hlsl"
#include "Main\struct_v_filter.hlsl"
#include "Main\struct_v_dumb.hlsl"
#include "Main\struct_v_model.hlsl"
#include "Main\struct_v_tree.hlsl"
#include "Main\struct_v_detail.hlsl"
#include "Main\struct_p_volume.hlsl"
#include "Headers\common_samplers.hlsl"
#include "Headers\common_cbuffers.hlsl"
#include "Headers\common_functions.hlsl"
#if (defined(MSAA_ALPHATEST_HIGH) || defined(MSAA_ALPHATEST_LOW))
#include "Msaa\msaa_a_test.hlsl"
#endif
#include "Msaa\msaa_hdao_index.hlsl"
#include "Headers\gbuffer_stage.hlsl"

#define xmaterial float(L_material.w)

#define FXPS technique _render{pass _code{PixelShader=compile ps_3_0 main();}}
#define FXVS technique _render{pass _code{VertexShader=compile vs_3_0 main();}}
#endif
