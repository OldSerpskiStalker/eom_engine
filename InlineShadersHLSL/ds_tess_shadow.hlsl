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
#include "Headers\tess.hlsl"

//if you use ccw then corresponding coefs are w, v, u
//if you use cw then corresponding coefs are u, v, w
[domain("tri")]
v2p_shadow_direct main( HS_CONSTANT_DATA_OUTPUT input, 
						float3 uvw : SV_DomainLocation,
						const OutputPatch<p_bumped, 3> bp )
{
    v2p_shadow_direct output;
	float u = uvw.x;
	float v = uvw.y;
	float w = uvw.z;
	
	float3 Pos 	= bp[0].position.xyz*w + bp[1].position.xyz*v + bp[2].position.xyz*u;
	float3 M1	= bp[0].M1*w + bp[1].M1*v + bp[2].M1*u;
	float3 M2	= bp[0].M2*w + bp[1].M2*v + bp[2].M2*u;
	float3 M3	= bp[0].M3*w + bp[1].M3*v + bp[2].M3*u;
	float3 Norm	= normalize(float3(M1.z, M2.z, M3.z));
	float2 tc   = bp[0].tcdh*w + bp[1].tcdh*v + bp[2].tcdh*u;
#	ifdef USE_TDETAIL
	float2 tcd	= bp[0].tcdbump*w + bp[1].tcdbump*v + bp[2].tcdbump*u;
#	else
	float2 tcd	= 0;
#	endif
	

#if TESS_PN
	float3 N[3] =
	{
		float3(bp[0].M1.z, bp[0].M2.z, bp[0].M3.z),
		float3(bp[1].M1.z, bp[1].M2.z, bp[1].M3.z),
		float3(bp[2].M1.z, bp[2].M2.z, bp[2].M3.z)
	};
	
	float3 P[3] = 
	{
		bp[0].position.xyz,
		bp[1].position.xyz,
		bp[2].position.xyz
	};

	ComputePatchVertex(P, N, uvw, input.patch, Pos, Norm);
#endif

#if TESS_HM
	ComputeDisplacedVertex(Pos, Norm, tc, tcd);
#endif
	
	output.hpos	= mul(m_P, float4(Pos,1.f));

    return output;
}

