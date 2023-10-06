#pragma once

class CBlender_bleed_effect : public IBlender
{
public:
    virtual LPCSTR getComment() { return "bleed_effect"; }
    virtual BOOL canBeDetailed() { return FALSE; }
    virtual BOOL canBeLMAPped() { return FALSE; }

    virtual void Compile(CBlender_Compile& C);

    CBlender_bleed_effect();
    virtual ~CBlender_bleed_effect();
};
