#pragma once

#include "telekinetic_object.h"
#include "../../../xrphysics/PHUpdateObject.h"

class CTelekinesis : public CPHUpdateObject
{
protected:
    DEFINE_VECTOR(CTelekineticObject*, TELE_OBJECTS, TELE_OBJECTS_IT);
    TELE_OBJECTS objects;
    xr_vector<CObject*> m_nearest;
    bool active;

public:
    CTelekinesis();
    virtual ~CTelekinesis();

    // allocates relevant TelekineticObject

    // àêòèâèðîâàòü îáúåêò
    virtual CTelekineticObject* activate(
        CPhysicsShellHolder* obj, float strength, float height, u32 max_time_keep, bool rot = true);

    // äåàêòèâèðîâàòü âñå îáúåêòû
    void deactivate();

    // clear objects (does not call release, but call switch to TS_None)
    void clear_deactivate();
    // clear
    virtual void clear();
    virtual void clear_notrelevant();
    // äåàêòèâèðîâàòü îáúåêò
    void deactivate(CPhysicsShellHolder* obj);
    void remove_object(TELE_OBJECTS_IT it);
    void remove_object(CPhysicsShellHolder* obj);
    // áðîñèòü âñå îáúåêòû â ïîçèöèþ 'target'
    void fire_all(const Fvector& target);

    // áðîñèòü îáúåêò 'obj' â ïîçèöèþ 'target' ñ ó÷åòîì êîýô ñèëû
    void fire(CPhysicsShellHolder* obj, const Fvector& target, float power);

    // áðîñèòü îáúåêò 'obj' â ïîçèöèþ 'target' ñ ó÷åòîì êîýô ñèëû
    void fire_t(CPhysicsShellHolder* obj, const Fvector& target, float time);

    // âåðíóòü àêòèâíîñòü òåëåêèíåçà
    bool is_active() { return active; }

    // âåðíóòü àêòèâíîñòü îáúåêòà
    bool is_active_object(CPhysicsShellHolder* obj);

    // âåðíóòü êîëè÷åñòâî êîíòðîëèðóåìûõ îáúåêòîâ (â ñîñòîÿíèè TS_Raise & TS_Keep)
    u32 get_objects_count();

    // âåðíóòü êîëè÷åñòâî êîíòðîëèðóåìûõ îáúåêòîâ (âñåõ)
    u32 get_objects_total_count() { return objects.size(); }

    // âåðíóòü îáúåêò ïî èíäåêñó â ìàññèâå
    // a	copy of the object!
    CTelekineticObject get_object_by_index(u32 index)
    {
        VERIFY(objects.size() > index);
        return *objects[index];
    }

    // îáíîâèòü ñîñòîíÿèå íà shedule_Update
    void schedule_update();

    // îáúåêò áûë óäàëåí - óäàëèòü âñå ñâÿçè íà îáúåêò
    void remove_links(CObject* O);

protected:
    virtual CTelekineticObject* alloc_tele_object() { return xr_new<CTelekineticObject>(); }

private:
    // îáíîâëåíèå íà øàãàõ ôèçèêè
    virtual void PhDataUpdate(float step);
    virtual void PhTune(float step);
};
