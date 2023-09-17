#pragma once

class CBlender_health_effect : public IBlender
{
public:
    virtual LPCSTR getComment() { return "health_effect"; }
    virtual BOOL canBeDetailed() { return FALSE; }
    virtual BOOL canBeLMAPped() { return FALSE; }

    virtual void Compile(CBlender_Compile& C);

    CBlender_health_effect();
    virtual ~CBlender_health_effect();
};
