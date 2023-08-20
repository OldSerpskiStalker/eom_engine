//////////////////////////////////////////////////////////////////////////
//-' CryRay Engine x64 Shaders
//-' Based on shaders from the original Anomaly 1.5.1
//-' As well as an integrated shader pack Screen Space 15.4
//-' Repository with shaders: https://github.com/cryray-team
//-' Also, if you are a shader developer
//-' You can join our server in discord: https://discord.gg/R78uVUZCTR
//-' OldSerpskiStalker7777, CryRay Team
//////////////////////////////////////////////////////////////////////////

#include "DX10Fog\fluid_common.hlsl"

//////////////////////////////////////////////////////////////////////////////////////////
//	Pixel
float4 main( p_fluidsim input ) : SV_Target
{
    // Texture_tempvector contains the vorticity computed by PS_VORTICITY
    float4 omega = Texture_tempvector.SampleLevel( samPointClamp, input.texcoords, 0 );

    // Potential optimization: don't find length multiple times - do once for the entire texture
    float omegaL = length( Texture_tempvector.SampleLevel( samPointClamp, LEFTCELL, 0 ) );
    float omegaR = length( Texture_tempvector.SampleLevel( samPointClamp, RIGHTCELL, 0 ) );
    float omegaB = length( Texture_tempvector.SampleLevel( samPointClamp, BOTTOMCELL, 0 ) );
    float omegaT = length( Texture_tempvector.SampleLevel( samPointClamp, TOPCELL, 0 ) );
    float omegaD = length( Texture_tempvector.SampleLevel( samPointClamp, DOWNCELL, 0 ) );
    float omegaU = length( Texture_tempvector.SampleLevel( samPointClamp, UPCELL, 0 ) );

    float3 eta = 0.5f * float3( omegaR - omegaL,
                              omegaT - omegaB,
                              omegaU - omegaD );

    eta = normalize( eta + float3(0.001f,0.001f,0.001f) );

    float4 force;
    force.xyz = timestep * epsilon * float3( eta.y * omega.z - eta.z * omega.y,
                                            eta.z * omega.x - eta.x * omega.z,
                                            eta.x * omega.y - eta.y * omega.x );
    
    // Note: the result is added to the current velocity at each cell using "additive blending"
    return force;
}