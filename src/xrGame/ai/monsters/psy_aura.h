#pragma once
#include "../../../xrEngine/feel_touch.h"
#include "energy_holder.h"

class CBaseMonster;

class CPsyAura : public Feel::Touch, public CEnergyHolder
{
    typedef CEnergyHolder inherited;

    // âëàäåëåö ïîëÿ
    CBaseMonster* m_object;

    // ðàäèóñ ïîëÿ
    float m_radius;

public:
    CPsyAura();
    virtual ~CPsyAura();

    void init_external(CBaseMonster* obj) { m_object = obj; }
    virtual bool feel_touch_contact(CObject* O) { return FALSE; }
    virtual void schedule_update();

    virtual void process_objects_in_aura() {}

    // ñâîéñòâà ïîëÿ
    void set_radius(float R) { m_radius = R; }
    float get_radius() { return m_radius; }

    CBaseMonster* get_object() { return m_object; }
};
