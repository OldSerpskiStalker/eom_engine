#pragma once

class CBlender_radiation_effect : public IBlender
{
public:
    virtual LPCSTR getComment() { return "radiation_effect"; }
    virtual BOOL canBeDetailed() { return FALSE; }
    virtual BOOL canBeLMAPped() { return FALSE; }

    virtual void Compile(CBlender_Compile& C);

    CBlender_radiation_effect();
    virtual ~CBlender_radiation_effect();
};
