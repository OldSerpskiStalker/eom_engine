#pragma once

class CBlender_stamina_effect : public IBlender
{
public:
    virtual LPCSTR getComment() { return "stamina_effect"; }
    virtual BOOL canBeDetailed() { return FALSE; }
    virtual BOOL canBeLMAPped() { return FALSE; }

    virtual void Compile(CBlender_Compile& C);

    CBlender_stamina_effect();
    virtual ~CBlender_stamina_effect();
};
