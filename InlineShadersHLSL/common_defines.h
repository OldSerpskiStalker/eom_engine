#ifndef	common_defines_h_included
#define	common_defines_h_included

//////////////////////////////////////////////////////////////////////////////////////////
// Defines                                		//
#define def_gloss       float(2.f /255.f)
#define def_aref        float(200.f/255.f)
#define def_dbumph      float(0.333f)
#define def_virtualh    float(0.05f)              // 5cm
#define def_distort     float(0.05f)             // we get -0.5 .. 0.5 range, this is -512 .. 512 for 1024, so scale it
#define def_hdr         float(9.h)         		// hight luminance range float(3.h)
#define def_hdr_clip	float(0.75h)        		//

#define	LUMINANCE_VECTOR	float3(0.3f, 0.38f, 0.22f)

#define USE_GRASS_WAVE              // вкл/выкл волны по траве
#define GRASS_WAVE_FREQ float(0.9)  // частота появления волн
#define GRASS_WAVE_POWER float(2.0) // яркость волн

//#define USE_SUNMASK // вкл/выкл тени от облаков

//////////////////////////////////////////////////////////////////////////////////////////
#ifndef SMAP_size
#define SMAP_size        1024
#endif
//////////////////////////////////////////////////////////////////////////////////////////

#endif	//	common_defines_h_included