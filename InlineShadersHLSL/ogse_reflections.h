#ifndef OGSE_REFLECTIONS_H
#define OGSE_REFLECTIONS_H

#include "ogse_functions.h"

TextureCube s_env0;
TextureCube s_env1;

uniform float4 screen_res;
static const float2 resolution = screen_res.xy;
static const float2 inv_resolution = screen_res.zw;

static const float w_refl_env_power = 0.8f;
static const float w_refl_intencity = 2.5f;
static const float w_refl_range = 400.f;
static const float w_refl_obj_itter = 64.f;

float4 get_reflection (float3 screen_pixel_pos, float3 next_screen_pixel_pos, float3 reflect)
{
	float4 final_color = {1.0,1.0,1.0,1.0};
	float2 factors = {1.f,1.f};
	
	// handle case when reflect vector faces the camera
	factors.x = dot(eye_direction, reflect);

	if ((factors.x < -0.5) || (screen_pixel_pos.z > w_refl_range)) return final_color;
	else
	{
		float3 main_vec = next_screen_pixel_pos - screen_pixel_pos;
		float3 grad_vec = main_vec / (max(abs(main_vec.x), abs(main_vec.y)) * 256);
		float3 curr_pixel = screen_pixel_pos;
		curr_pixel.xy += float2(0.5,0.5)*screen_res.zw;
		bool enough = false;
		float delta = 0;
		float depth = 0;
		
		for (float i = 0; i < w_refl_obj_itter; i++)
		{
			if(!enough) // sorry, cant use 'break', since then, API can't generate instructions for this loop
			{
				curr_pixel.xyz += grad_vec.xyz;
				depth = get_depth_fast(curr_pixel.xy);
				depth = lerp(depth, 0.f, is_sky(depth));
				delta = step(depth, curr_pixel.z)*step(screen_pixel_pos.z, depth);
			
				if (delta > 0.5)
					enough = true;
			}
		}
		
		if (enough == true)
		{
			final_color.xyz = s_image.Sample( smp_rtlinear, curr_pixel.xy).xyz; // get color
			float2 tmp = curr_pixel.xy;
			tmp.y = lerp(tmp.y, 0.5, step(0.5, tmp.y));
			float screendedgefact = saturate(distance(tmp , float2(0.5, 0.5)) * 2.0);
			final_color.w = pow(screendedgefact,6);
			
			return lerp(final_color,float4(1.0,1.0,1.0,1.0),screen_pixel_pos.z / w_refl_range);
		}
	}
	
	return final_color;
}

float3 calc_envmap(float3 vreflect)
{
	float3 a = abs(vreflect);
	vreflect.xyz /= max(a.x, max(a.y, a.z));

	if (vreflect.y < 0.999)
		vreflect.y = vreflect.y * 2 - 1;

	float3 env0 = s_env0.SampleLevel(smp_base, vreflect.xyz, 0);
	float3 env1 = s_env1.SampleLevel(smp_base, vreflect.xyz, 0);

	return lerp(env0, env1, L_ambient.w);
}
float4 calc_reflections(float4 pos, float3 vreflect)
{
	float4 refl = {1.0,1.0,1.0,1.0};
	float3 v_pixel_pos = mul((float3x4)m_V, pos);
	float4 p_pixel_pos = mul(m_VP, pos);
	float4 s_pixel_pos = proj_to_screen(p_pixel_pos);
	s_pixel_pos.xy /= s_pixel_pos.w;
	s_pixel_pos.z = v_pixel_pos.z;
		
	float3 reflect_vec = normalize(vreflect);
	float3 W_m_point = pos.xyz + reflect_vec;

	float3 V_m_point = mul((float3x4)m_V, float4(W_m_point, 1.0));
	float4 P_m_point = mul(m_VP, float4(W_m_point, 1.0));
	float4 S_m_point = proj_to_screen(P_m_point);
	S_m_point.xy /= S_m_point.w;
	S_m_point.z = V_m_point.z;
		
	refl = get_reflection(s_pixel_pos.xyz, S_m_point.xyz, reflect_vec);
	
	return refl;
}

#endif