#pragma once

// Õðàíèëèùå âíåøíèõ øåéäåðíûõ ïàðàìåòðîâ, êîòîðûå ÷èòàþòñÿ â Blender_Recorder_StandartBinding.cpp
class ShadersExternalData //--#SM+#--
{
public:
    Fvector4 hud_params; // [zoom_rotate_factor, secondVP_zoom_factor, hud_fov, NULL] - Ïàðàìåòðû õóäà îðóæèÿ

    ShadersExternalData() { hud_params.set(0.f, 0.f, 0.f, 0.f); }
};
