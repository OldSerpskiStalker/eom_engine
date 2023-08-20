//////////////////////////////////////////////////////////////////////////
//-' CryRay Engine x64 Shaders
//-' Based on shaders from the original Anomaly 1.5.1
//-' As well as an integrated shader pack Screen Space 15.4
//-' Repository with shaders: https://github.com/cryray-team
//-' Also, if you are a shader developer
//-' You can join our server in discord: https://discord.gg/R78uVUZCTR
//-' OldSerpskiStalker7777, CryRay Team
//////////////////////////////////////////////////////////////////////////

#ifndef	P_VOLUME_H
#define	P_VOLUME_H
	struct 	v2p_volume
	{
		float4 	tc		:TEXCOORD0;
		float4 	hpos	:SV_Position;	// Clip-space position 	(for rasterization)
	};

	struct 	p_volume
	{
		float4 	tc		:TEXCOORD0;
	};
#endif