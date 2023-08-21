#ifndef OGSE_CONFIG_H
#define OGSE_CONFIG_H

#include "configurator_defines.h"
// ������� �� ���������� ����� �������
// ��������								r2_sunshafts [qt_off/qt_low/qt_medium/qt_high/qt_extreme]
// �������� ��������					r2_sunshafts_mode volumetric
// ������� �������� ��� Crysis			r2_sunshafts_mode screen_space

// PARAMETERS 
// ����������� ��������� ��� ��������� ���������������� �������
/////////////////////////////////////////////////////////////
// ������� ��������
	#define SUNSHAFTS_QUALITY 4
	#define SS_DUST
	#define SS_INTENSITY float(1.0)			// ������� �����, �������� ��������� � ����������� �� �������
	#define SS_BLEND_FACTOR float(0.8)		// ������ ���������� � ���������� ������. ��� ������ ��������, ��� ������ "��������" �� �������, �� �������� "����������"
	#define SS_LENGTH float(1.0)			// ����� �����. ��� ������ �����, ��� ������ ������������������
	#define SS_DUST_SPEED float(0.4)		// �������� ������ ���� 
	#define SS_DUST_INTENSITY float(2.0)	// ������� �������
	#define SS_DUST_DENSITY float(1.0)		// ��������� ������ ���� 
	#define SS_DUST_SIZE float(0.7)			// ������ �������

// Screen space sunshafts
struct	v_ssss
{
	float4 P : POSITIONT;
	float2 tc0	: TEXCOORD0;
};

struct	v2p_ssss
{
	float2 tc0 : TEXCOORD0;
	float4 HPos : SV_Position;	// Clip-space position 	(for rasterization)
};
#endif