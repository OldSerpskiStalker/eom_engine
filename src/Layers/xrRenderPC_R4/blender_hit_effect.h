#pragma once

class CBlender_hit_effect : public IBlender
{
public:
    virtual LPCSTR getComment() { return "hit_effect"; }
    virtual BOOL canBeDetailed() { return FALSE; }
    virtual BOOL canBeLMAPped() { return FALSE; }

    virtual void Compile(CBlender_Compile& C);

    CBlender_hit_effect();
    virtual ~CBlender_hit_effect();
};
