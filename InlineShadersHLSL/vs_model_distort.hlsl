//////////////////////////////////////////////////////////////////////////
//-' CryRay Engine x64 Shaders
//-' Based on shaders from the original Anomaly 1.5.1
//-' As well as an integrated shader pack Screen Space 15.4
//-' Repository with shaders: https://github.com/cryray-team
//-' Also, if you are a shader developer
//-' You can join our server in discord: https://discord.gg/R78uVUZCTR
//-' OldSerpskiStalker7777, CryRay Team
//////////////////////////////////////////////////////////////////////////

#include "Headers\common.hlsl"
#include "Headers\skin.hlsl"

struct vf
{
  float2 tc0	: TEXCOORD0;    // base
  float4 c0		: COLOR0;    // color
  float4 hpos	: SV_Position;
  float  fog	: FOG; 
};

vf _main (v_model v)
{
  vf     o;

	o.hpos     	= mul(m_WVP, v.P);    // xform, input in world coords
	o.tc0    	= v.tc.xy;          // copy tc

	// calculate fade
	float3  dir_v   = normalize    (mul(m_WV,v.P));
	float3  norm_v  = normalize    (mul((float3x3)m_WV,v.N));
	float fade   = 1.f-abs      (dot(dir_v,norm_v));
	o.c0 = fade;
	
	o.fog = saturate( calc_fogging(v.P));
	return o;
}

/////////////////////////////////////////////////////////////////////////
#ifdef   SKIN_NONE
vf  main(v_model v)     { return _main(v);     }
#endif

#ifdef   SKIN_0
vf  main(v_model_skinned_0 v)   { return _main(skinning_0(v)); }
#endif

#ifdef  SKIN_1
vf  main(v_model_skinned_1 v)   { return _main(skinning_1(v)); }
#endif

#ifdef  SKIN_2
vf  main(v_model_skinned_2 v)   { return _main(skinning_2(v)); }
#endif

#ifdef  SKIN_3
vf  main(v_model_skinned_3 v)   { return _main(skinning_3(v)); }
#endif

#ifdef  SKIN_4
vf  main(v_model_skinned_4 v)   { return _main(skinning_4(v)); }
#endif