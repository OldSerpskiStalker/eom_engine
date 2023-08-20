#pragma once
#include "../state.h"
#include "../../../grenade.h"

template <typename Object>
class CStateBurerAttackTele : public CState<Object>
{
    typedef CState<Object> inherited;

    xr_vector<CPhysicsShellHolder*> tele_objects;
    CPhysicsShellHolder* selected_object;
    xr_vector<CObject*> m_nearest;

    u32 time_started;

    enum
    {
        ACTION_TELE_STARTED,
        ACTION_TELE_CONTINUE,
        ACTION_TELE_FIRE,
        ACTION_WAIT_FIRE_END,
        ACTION_COMPLETED,
    } m_action;

public:
    CStateBurerAttackTele(Object* obj);

    virtual void initialize();
    virtual void execute();
    virtual void finalize();
    virtual void critical_finalize();
    virtual void remove_links(CObject* object) { inherited::remove_links(object); }

    virtual bool check_start_conditions();
    virtual bool check_completion();

private:
    // Ïîèñê îáúåêòîâ äëÿ òåëåêèíåçà
    void FindObjects();

    void HandleGrenades();

    // âûïîëíÿòü ñîñòîÿíèå
    void ExecuteTeleContinue();
    void ExecuteTeleFire();

    // Ïðîâåðêà, åñòü ëè õîòü îäèí îáúåêò ïîä êîíòðîëåì
    bool IsActiveObjects();

    // Ïðîâåðèòü, ìîæåò ëè ñòàðòîâàòü òåëåêèíåç
    bool CheckTeleStart();
    // Âûáîð ïîäõîäÿùèõ îáúåêòîâ äëÿ òåëåêèíåçà
    void SelectObjects();

    // internal for FindObjects
    void FindFreeObjects(xr_vector<CObject*>& tpObjects, const Fvector& pos);
    void xr_stdcall OnGrenadeDestroyed(CGrenade* const grenade);

    void FireAllToEnemy();
    void deactivate();

private:
    TTime m_last_grenade_scan;
    TTime m_anim_end_tick;
    TTime m_end_tick;
    float m_initial_health;
};

#include "burer_state_attack_tele_inline.h"
