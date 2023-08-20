#include "pch_script.h"
#include "ActorCondition.h"
#include "EntityCondition.h"
#include "Wound.h"

using namespace luabind;

void BoosterForEach(CActorCondition* conditions, const luabind::functor<bool>& funct)
{
    CEntityCondition::BOOSTER_MAP& cur_booster_influences = conditions->GetCurBoosterInfluences();
    CEntityCondition::BOOSTER_MAP::const_iterator it = cur_booster_influences.begin();
    CEntityCondition::BOOSTER_MAP::const_iterator it_e = cur_booster_influences.end();
    for (; it != it_e; ++it)
    {
        if (funct((*it).first, (*it).second.fBoostTime, (*it).second.fBoostValue) == true)
            break;
    }
}

bool ApplyBooster_script(CActorCondition* cond, const SBooster& B, LPCSTR sect) { return cond->ApplyBooster(B, sect); }

void ClearAllBoosters(CActorCondition* conditions)
{
    CEntityCondition::BOOSTER_MAP& cur_booster_influences = conditions->GetCurBoosterInfluences();
    CEntityCondition::BOOSTER_MAP::const_iterator it = cur_booster_influences.begin();
    CEntityCondition::BOOSTER_MAP::const_iterator it_e = cur_booster_influences.end();
    for (; it != it_e; ++it)
    {
        conditions->DisableBoostParameters((*it).second);
    }
    cur_booster_influences.clear();
}

#pragma optimize("s", on)
void CActorCondition::script_register(lua_State* L)
{
    module(L)[class_<SBooster>("SBooster")
                  .def(constructor<>())
                  .def_readwrite("fBoostTime", &SBooster::fBoostTime)
                  .def_readwrite("fBoostValue", &SBooster::fBoostValue)
                  .def_readwrite("m_type", &SBooster::m_type),
        class_<CEntityCondition>("CEntityCondition")
            //.def(constructor<>())
            .def("GetWhoHitLastTimeID", &CEntityCondition::GetWhoHitLastTimeID)
            .def("GetPower", &CEntityCondition::GetPower)
            .def("GetRadiation", &CEntityCondition::GetRadiation)
            .def("GetPsyHealth", &CEntityCondition::GetPsyHealth)
            .def("GetSatiety", &CEntityCondition::GetSatiety)
            .def("GetThirst", &CEntityCondition::GetThirst)
            .def("GetEntityMorale", &CEntityCondition::GetEntityMorale)
            .def("GetHealthLost", &CEntityCondition::GetHealthLost)
            .def("IsLimping", &CEntityCondition::IsLimping)
            .def("ChangeSatiety", &CEntityCondition::ChangeSatiety)
            .def("ChangeHealth", &CEntityCondition::ChangeHealth)
            .def("ChangePower", &CEntityCondition::ChangePower)
            .def("ChangeRadiation", &CEntityCondition::ChangeRadiation)
            .def("ChangePsyHealth", &CEntityCondition::ChangePsyHealth)
            .def("ChangeAlcohol", &CEntityCondition::ChangeAlcohol)
            .def("SetMaxPower", &CEntityCondition::SetMaxPower)
            .def("GetMaxPower", &CEntityCondition::GetMaxPower)
            .def("ChangeEntityMorale", &CEntityCondition::ChangeEntityMorale)
            .def("ChangeBleeding", &CEntityCondition::ChangeBleeding)
            .def("BleedingSpeed", &CEntityCondition::BleedingSpeed)
            .enum_("EBoostParams")[value("eBoostHpRestore", int(EBoostParams::eBoostHpRestore)),
                value("eBoostPowerRestore", int(EBoostParams::eBoostPowerRestore)),
                value("eBoostRadiationRestore", int(EBoostParams::eBoostRadiationRestore)),
                value("eBoostBleedingRestore", int(EBoostParams::eBoostBleedingRestore)),
                value("eBoostMaxWeight", int(EBoostParams::eBoostMaxWeight)),
                value("eBoostRadiationProtection", int(EBoostParams::eBoostRadiationProtection)),
                value("eBoostTelepaticProtection", int(EBoostParams::eBoostTelepaticProtection)),
                value("eBoostChemicalBurnProtection", int(EBoostParams::eBoostChemicalBurnProtection)),
                value("eBoostBurnImmunity", int(EBoostParams::eBoostBurnImmunity)),
                value("eBoostShockImmunity", int(EBoostParams::eBoostShockImmunity)),
                value("eBoostRadiationImmunity", int(EBoostParams::eBoostRadiationImmunity)),
                value("eBoostTelepaticImmunity", int(EBoostParams::eBoostTelepaticImmunity)),
                value("eBoostChemicalBurnImmunity", int(EBoostParams::eBoostChemicalBurnImmunity)),
                value("eBoostExplImmunity", int(EBoostParams::eBoostExplImmunity)),
                value("eBoostStrikeImmunity", int(EBoostParams::eBoostStrikeImmunity)),
                value("eBoostFireWoundImmunity", int(EBoostParams::eBoostFireWoundImmunity)),
                value("eBoostWoundImmunity", int(EBoostParams::eBoostWoundImmunity))],

        class_<CActorCondition, CEntityCondition>("CActorCondition")
            //.def(constructor<>())
            .def("ClearAllBoosters", &ClearAllBoosters)
            .def("ApplyBooster", &ApplyBooster_script)
            .def("BoosterForEach", &BoosterForEach)
            .def("V_Satiety", &CActorCondition::V_Satiety)
            .def("V_SatietyPower", &CActorCondition::V_SatietyPower)
            .def("V_SatietyHealth", &CActorCondition::V_SatietyHealth)
            .def("SatietyCritical", &CActorCondition::SatietyCritical)
            .def("GetSatiety", &CActorCondition::GetSatiety)
            .def("GetThirst", &CActorCondition::GetThirst)
            .def("IsLimping", &CActorCondition::IsLimping)
            .def("IsCantWalk", &CActorCondition::IsCantWalk)
            .def("IsCantWalkWeight", &CActorCondition::IsCantWalkWeight)
            .def("IsCantSprint", &CActorCondition::IsCantSprint)
            .def_readwrite("m_MaxWalkWeight", &CActorCondition::m_MaxWalkWeight)
            .def_readwrite("m_fJumpPower", &CActorCondition::m_fJumpPower)
            .def_readwrite("m_fStandPower", &CActorCondition::m_fStandPower)
            .def_readwrite("m_fJumpWeightPower", &CActorCondition::m_fJumpWeightPower)
            .def_readwrite("m_fWalkWeightPower", &CActorCondition::m_fWalkWeightPower)
            .def_readwrite("m_fOverweightWalkK", &CActorCondition::m_fOverweightWalkK)
            .def_readwrite("m_fOverweightJumpK", &CActorCondition::m_fOverweightJumpK)
            .def_readwrite("m_fAccelK", &CActorCondition::m_fAccelK)
            .def_readwrite("m_fSprintK", &CActorCondition::m_fSprintK)
            .def_readwrite("m_condition_flags", &CActorCondition::m_condition_flags)
            .enum_("condition_flags")[value("eCriticalPowerReached", int(CActorCondition::eCriticalPowerReached)),
                value("eCriticalBleedingSpeed", int(CActorCondition::eCriticalBleedingSpeed)),
                value("eCriticalSatietyReached", int(CActorCondition::eCriticalSatietyReached)),
                value("eCriticalRadiationReached", int(CActorCondition::eCriticalRadiationReached)),
                value("eWeaponJammedReached", int(CActorCondition::eWeaponJammedReached)),
                value("ePhyHealthMinReached", int(CActorCondition::ePhyHealthMinReached)),
                value("ePhyHealthMinReached", int(CActorCondition::ePhyHealthMinReached)),
                value("eCantWalkWeight", int(CActorCondition::eCantWalkWeight)),
                value("eCantWalkWeightReached", int(CActorCondition::eCantWalkWeightReached))]];
}
