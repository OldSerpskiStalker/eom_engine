#include "stdafx.h"
#pragma hdrstop

#pragma warning(push)
#pragma warning(disable : 4995)
#include <d3dx9.h>
#pragma warning(pop)

#include "ResourceManager.h"
#include "blenders\Blender_Recorder.h"
#include "blenders\Blender.h"

#include "../../xrEngine/igame_persistent.h"
#include "../../xrEngine/environment.h"
#include "../../xrEngine/Rain.h"

#include "dxRenderDeviceRender.h"

// matrices
#define BIND_DECLARE(xf)                                                                                               \
    class cl_xform_##xf : public R_constant_setup                                                                      \
    {                                                                                                                  \
        virtual void setup(R_constant* C)                                                                              \
        {                                                                                                              \
            RCache.xforms.set_c_##xf(C);                                                                               \
        }                                                                                                              \
    };                                                                                                                 \
    static cl_xform_##xf binder_##xf
BIND_DECLARE(w);
BIND_DECLARE(invw);
BIND_DECLARE(v);
BIND_DECLARE(p);
BIND_DECLARE(wv);
BIND_DECLARE(vp);
BIND_DECLARE(wvp);

#define DECLARE_TREE_BIND(c)                                                                                           \
    class cl_tree_##c : public R_constant_setup                                                                        \
    {                                                                                                                  \
        virtual void setup(R_constant* C)                                                                              \
        {                                                                                                              \
            RCache.tree.set_c_##c(C);                                                                                  \
        }                                                                                                              \
    };                                                                                                                 \
    static cl_tree_##c tree_binder_##c

DECLARE_TREE_BIND(m_xform_v);
DECLARE_TREE_BIND(m_xform);
DECLARE_TREE_BIND(consts);
DECLARE_TREE_BIND(wave);
DECLARE_TREE_BIND(wind);
DECLARE_TREE_BIND(c_scale);
DECLARE_TREE_BIND(c_bias);
DECLARE_TREE_BIND(c_sun);

class cl_hemi_cube_pos_faces : public R_constant_setup
{
    virtual void setup(R_constant* C) { RCache.hemi.set_c_pos_faces(C); }
};

static cl_hemi_cube_pos_faces binder_hemi_cube_pos_faces;

class cl_hemi_cube_neg_faces : public R_constant_setup
{
    virtual void setup(R_constant* C) { RCache.hemi.set_c_neg_faces(C); }
};

static cl_hemi_cube_neg_faces binder_hemi_cube_neg_faces;

class cl_material : public R_constant_setup
{
    virtual void setup(R_constant* C) { RCache.hemi.set_c_material(C); }
};

static cl_material binder_material;

class cl_texgen : public R_constant_setup
{
    virtual void setup(R_constant* C)
    {
        Fmatrix mTexgen;

#if defined(USE_DX10) || defined(USE_DX11)
        Fmatrix mTexelAdjust = {
            0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f};
#else //	USE_DX10
        float _w = float(RDEVICE.dwWidth);
        float _h = float(RDEVICE.dwHeight);
        float o_w = (.5f / _w);
        float o_h = (.5f / _h);
        Fmatrix mTexelAdjust = {0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f + o_w,
            0.5f + o_h, 0.0f, 1.0f};
#endif //	USE_DX10

        mTexgen.mul(mTexelAdjust, RCache.xforms.m_wvp);

        RCache.set_c(C, mTexgen);
    }
};
static cl_texgen binder_texgen;

class cl_VPtexgen : public R_constant_setup
{
    virtual void setup(R_constant* C)
    {
        Fmatrix mTexgen;

#if defined(USE_DX10) || defined(USE_DX11)
        Fmatrix mTexelAdjust = {
            0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f};
#else //	USE_DX10
        float _w = float(RDEVICE.dwWidth);
        float _h = float(RDEVICE.dwHeight);
        float o_w = (.5f / _w);
        float o_h = (.5f / _h);
        Fmatrix mTexelAdjust = {0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f + o_w,
            0.5f + o_h, 0.0f, 1.0f};
#endif //	USE_DX10

        mTexgen.mul(mTexelAdjust, RCache.xforms.m_vp);

        RCache.set_c(C, mTexgen);
    }
};
static cl_VPtexgen binder_VPtexgen;

// fog
#ifndef _EDITOR
class cl_fog_plane : public R_constant_setup
{
    u32 marker;
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        if (marker != Device.dwFrame)
        {
            // Plane
            Fvector4 plane;
            Fmatrix& M = Device.mFullTransform;
            plane.x = -(M._14 + M._13);
            plane.y = -(M._24 + M._23);
            plane.z = -(M._34 + M._33);
            plane.w = -(M._44 + M._43);
            float denom = -1.0f / _sqrt(_sqr(plane.x) + _sqr(plane.y) + _sqr(plane.z));
            plane.mul(denom);

            // Near/Far
            float A = g_pGamePersistent->Environment().CurrentEnv->fog_near;
            float B = 1 / (g_pGamePersistent->Environment().CurrentEnv->fog_far - A);
            result.set(-plane.x * B, -plane.y * B, -plane.z * B, 1 - (plane.w - A) * B); // view-plane
        }
        RCache.set_c(C, result);
    }
};
static cl_fog_plane binder_fog_plane;

// fog-params
class cl_fog_params : public R_constant_setup
{
    u32 marker;
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        if (marker != Device.dwFrame)
        {
            // Near/Far
            float n = g_pGamePersistent->Environment().CurrentEnv->fog_near;
            float f = g_pGamePersistent->Environment().CurrentEnv->fog_far;
            float r = 1 / (f - n);
            result.set(-n * r, r, r, r);
        }
        RCache.set_c(C, result);
    }
};
static cl_fog_params binder_fog_params;

// fog-color
class cl_fog_color : public R_constant_setup
{
    u32 marker;
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        if (marker != Device.dwFrame)
        {
            CEnvDescriptor& desc = *g_pGamePersistent->Environment().CurrentEnv;
            result.set(desc.fog_color.x, desc.fog_color.y, desc.fog_color.z, 0);
        }
        RCache.set_c(C, result);
    }
};
static cl_fog_color binder_fog_color;
#endif

// times
class cl_times : public R_constant_setup
{
    virtual void setup(R_constant* C)
    {
        float t = RDEVICE.fTimeGlobal;
        RCache.set_c(C, t, t * 10, t / 10, _sin(t));
    }
};
static cl_times binder_times;

// eye-params
class cl_eye_P : public R_constant_setup
{
    virtual void setup(R_constant* C)
    {
        Fvector& V = RDEVICE.vCameraPosition;
        RCache.set_c(C, V.x, V.y, V.z, 1);
    }
};
static cl_eye_P binder_eye_P;

// eye-params
class cl_eye_D : public R_constant_setup
{
    virtual void setup(R_constant* C)
    {
        Fvector& V = RDEVICE.vCameraDirection;
        RCache.set_c(C, V.x, V.y, V.z, 0);
    }
};
static cl_eye_D binder_eye_D;

// eye-params
class cl_eye_N : public R_constant_setup
{
    virtual void setup(R_constant* C)
    {
        Fvector& V = RDEVICE.vCameraTop;
        RCache.set_c(C, V.x, V.y, V.z, 0);
    }
};
static cl_eye_N binder_eye_N;

#ifndef _EDITOR
// D-Light0
class cl_sun0_color : public R_constant_setup
{
    u32 marker;
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        if (marker != Device.dwFrame)
        {
            CEnvDescriptor& desc = *g_pGamePersistent->Environment().CurrentEnv;
            result.set(desc.sun_color.x, desc.sun_color.y, desc.sun_color.z, 0);
        }
        RCache.set_c(C, result);
    }
};
static cl_sun0_color binder_sun0_color;

class cl_sky_color : public R_constant_setup
{
    u32 marker;
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        if (marker != Device.dwFrame)
        {
            CEnvDescriptor& desc = *g_pGamePersistent->Environment().CurrentEnv;
            result.set(desc.sky_color.x, desc.sky_color.y, desc.sky_color.z, 0);
        }
        RCache.set_c(C, result);
    }
};
static cl_sky_color binder_sky_color;

class cl_sun0_dir_w : public R_constant_setup
{
    u32 marker;
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        if (marker != Device.dwFrame)
        {
            CEnvDescriptor& desc = *g_pGamePersistent->Environment().CurrentEnv;
            result.set(desc.sun_dir.x, desc.sun_dir.y, desc.sun_dir.z, 0);
        }
        RCache.set_c(C, result);
    }
};
static cl_sun0_dir_w binder_sun0_dir_w;
class cl_sun0_dir_e : public R_constant_setup
{
    u32 marker;
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        if (marker != Device.dwFrame)
        {
            Fvector D;
            CEnvDescriptor& desc = *g_pGamePersistent->Environment().CurrentEnv;
            Device.mView.transform_dir(D, desc.sun_dir);
            D.normalize();
            result.set(D.x, D.y, D.z, 0);
        }
        RCache.set_c(C, result);
    }
};
static cl_sun0_dir_e binder_sun0_dir_e;

//
class cl_amb_color : public R_constant_setup
{
    u32 marker;
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        if (marker != Device.dwFrame)
        {
            CEnvDescriptorMixer& desc = *g_pGamePersistent->Environment().CurrentEnv;
            result.set(desc.ambient.x, desc.ambient.y, desc.ambient.z, desc.weight);
        }
        RCache.set_c(C, result);
    }
};
static cl_amb_color binder_amb_color;
class cl_hemi_color : public R_constant_setup
{
    u32 marker;
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        if (marker != Device.dwFrame)
        {
            CEnvDescriptor& desc = *g_pGamePersistent->Environment().CurrentEnv;
            result.set(desc.hemi_color.x, desc.hemi_color.y, desc.hemi_color.z, desc.hemi_color.w);
        }
        RCache.set_c(C, result);
    }
};
static cl_hemi_color binder_hemi_color;
#endif

static class cl_screen_res : public R_constant_setup
{
    virtual void setup(R_constant* C)
    {
        RCache.set_c(C, (float)RDEVICE.dwWidth, (float)RDEVICE.dwHeight, 1.0f / (float)RDEVICE.dwWidth,
            1.0f / (float)RDEVICE.dwHeight);
    }
} binder_screen_res;

static class cl_screen_params : public R_constant_setup
{
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        float fov = float(Device.fFOV);
        float aspect = float(Device.fASPECT);
        result.set(fov, aspect, tan(deg2rad(fov) / 2), g_pGamePersistent->Environment().CurrentEnv->far_plane * 0.75f);
        RCache.set_c(C, result);
    }
};
static cl_screen_params binder_screen_params;

class cl_rain_params : public R_constant_setup
{
    u32 marker;
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        if (marker != Device.dwFrame)
        {
            CEnvDescriptor& desc = *g_pGamePersistent->Environment().CurrentEnv;
            result.set(desc.rain_density, 0.f, 0.f, 0.f);
        }
        RCache.set_c(C, result);
    }
};
static cl_rain_params binder_rain_params;

class cl_inv_v : public R_constant_setup
{
    u32 marker;
    Fmatrix result;
    virtual void setup(R_constant* C)
    {
        //		if (marker!=Device.dwFrame)	{
        result.invert(Device.mView);
        //		}
        RCache.set_c(C, result);
    }
};
static cl_inv_v binder_inv_v;

// wind for clouds
class cl_clouds_velocity : public R_constant_setup
{
    u32 marker;
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        if (marker != Device.dwFrame)
        {
            float a = g_pGamePersistent->Environment().CurrentEnv->clouds_velocity_0;
            float b = g_pGamePersistent->Environment().CurrentEnv->clouds_velocity_1;
            result.set(a, b, 0, 0);
        }
        RCache.set_c(C, result);
    }
};
static cl_clouds_velocity binder_clouds_velocity;

// wind for clouds
class cl_weather_test : public R_constant_setup
{
    u32 marker;
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        if (marker != Device.dwFrame)
        {
            int test_bool_to_int;
            BOOL indoor_weather = RImplementation.indoor_weather();
            if (indoor_weather == true)
                test_bool_to_int = 1;
            else
                test_bool_to_int = 0;

            // Msg("test_ws = %i", test_bool_to_int);
            result.set(test_bool_to_int, 0, 0, 0);
        }
        RCache.set_c(C, result);
    }
};
static cl_weather_test binder_weather_test;

class cl_lut_palette : public R_constant_setup
{
    u32 marker;
    Fvector4 result;
    virtual void setup(R_constant* C)
    {
        if (marker != Device.dwFrame)
        {
            result.set(ps_r4_lut_palette, 0, 0, 0);
        }
        RCache.set_c(C, result);
    }
};
static cl_lut_palette binder_lut_palette;

class cl_pos_decompress_params_xray : public R_constant_setup
{
    virtual void setup(R_constant* C)
    {
        float VertTan = -1.0f * tanf(deg2rad(Device.fFOV / 2.0f));
        float HorzTan = -VertTan / Device.fASPECT;

        RCache.set_c(
            C, HorzTan, VertTan, (2.0f * HorzTan) / (float)Device.dwWidth, (2.0f * VertTan) / (float)Device.dwHeight);
    }
};
static cl_pos_decompress_params_xray binder_pos_decompress_params_xray;

class cl_hud_params : public R_constant_setup //--#SM+#--
{
    virtual void setup(R_constant* C) { RCache.set_c(C, g_pGamePersistent->m_pGShaderConstants->hud_params); }
};
static cl_hud_params binder_hud_params;

class cl_actor_params : public R_constant_setup
{
    u32 marker;
    Fvector4 result;

    virtual void setup(R_constant* C)
    {
        float actorHealth = g_pGamePersistent->actor_data.health;
        float actorStamina = g_pGamePersistent->actor_data.stamina;
        float actorBleeding = g_pGamePersistent->actor_data.bleeding;
        float actorRadiation = g_pGamePersistent->actor_data.radiation;

        // Msg("health = %f, stamina = %f, bleeding = %f, radiation = %f", actorHealth, actorStamina, actorBleeding,
        // actorRadiation);

        RCache.set_c(C, actorHealth, actorStamina, actorBleeding, actorRadiation);
    }
};
static cl_actor_params binder_actor_data;

// Standart constant-binding
void CBlender_Compile::SetMapping()
{
    r_Constant("ogse_c_screen", &binder_screen_params);
    r_Constant("ogse_c_rain", &binder_rain_params);
    r_Constant("m_v2w", &binder_inv_v);
    r_Constant("clouds_velocity", &binder_clouds_velocity);
    r_Constant("weather_section_indoor", &binder_weather_test);

    r_Constant("lut_palette", &binder_lut_palette);

    r_Constant("dx_Pos_Decompression_Params", &binder_pos_decompress_params_xray);

    r_Constant("m_hud_params", &binder_hud_params); //--#SM+#--

    r_Constant("actor_data", &binder_actor_data);

    // matrices
    r_Constant("m_W", &binder_w);
    r_Constant("m_invW", &binder_invw);
    r_Constant("m_V", &binder_v);
    r_Constant("m_P", &binder_p);
    r_Constant("m_WV", &binder_wv);
    r_Constant("m_VP", &binder_vp);
    r_Constant("m_WVP", &binder_wvp);
    r_Constant("m_inv_V", &binder_inv_v);

    r_Constant("m_xform_v", &tree_binder_m_xform_v);
    r_Constant("m_xform", &tree_binder_m_xform);
    r_Constant("consts", &tree_binder_consts);
    r_Constant("wave", &tree_binder_wave);
    r_Constant("wind", &tree_binder_wind);
    r_Constant("c_scale", &tree_binder_c_scale);
    r_Constant("c_bias", &tree_binder_c_bias);
    r_Constant("c_sun", &tree_binder_c_sun);

    // hemi cube
    r_Constant("L_material", &binder_material);
    r_Constant("hemi_cube_pos_faces", &binder_hemi_cube_pos_faces);
    r_Constant("hemi_cube_neg_faces", &binder_hemi_cube_neg_faces);

    //	Igor	temp solution for the texgen functionality in the shader
    r_Constant("m_texgen", &binder_texgen);
    r_Constant("mVPTexgen", &binder_VPtexgen);

#ifndef _EDITOR
    // fog-params
    r_Constant("fog_plane", &binder_fog_plane);
    r_Constant("fog_params", &binder_fog_params);
    r_Constant("fog_color", &binder_fog_color);
#endif
    // time
    r_Constant("timers", &binder_times);

    // eye-params
    r_Constant("eye_position", &binder_eye_P);
    r_Constant("eye_direction", &binder_eye_D);
    r_Constant("eye_normal", &binder_eye_N);

#ifndef _EDITOR
    // global-lighting (env params)
    r_Constant("L_sun_color", &binder_sun0_color);
    r_Constant("L_sky_color", &binder_sky_color);
    r_Constant("L_sun_dir_w", &binder_sun0_dir_w);
    r_Constant("L_sun_dir_e", &binder_sun0_dir_e);
    //	r_Constant				("L_lmap_color",	&binder_lm_color);
    r_Constant("L_hemi_color", &binder_hemi_color);
    r_Constant("L_ambient", &binder_amb_color);
#endif
    r_Constant("screen_res", &binder_screen_res);

    // detail
    // if (bDetail	&& detail_scaler)
    //	Igor: bDetail can be overridden by no_detail_texture option.
    //	But shader can be deatiled implicitly, so try to set this parameter
    //	anyway.
    if (detail_scaler)
        r_Constant("dt_params", detail_scaler);

    // other common
    for (u32 it = 0; it < DEV->v_constant_setup.size(); it++)
    {
        std::pair<shared_str, R_constant_setup*> cs = DEV->v_constant_setup[it];
        r_Constant(*cs.first, cs.second);
    }
}
