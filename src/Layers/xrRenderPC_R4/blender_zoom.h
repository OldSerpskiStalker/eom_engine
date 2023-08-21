#pragma once

class CBlender_zoom : public IBlender
{
public:
    virtual LPCSTR getComment() { return "zoom"; }
    virtual BOOL canBeDetailed() { return FALSE; }
    virtual BOOL canBeLMAPped() { return FALSE; }

    virtual void Compile(CBlender_Compile& C);

    CBlender_zoom();
    virtual ~CBlender_zoom();
};

class CBlender_zoom_MSAA : public IBlender
{
public:
    virtual LPCSTR getComment() { return "zoom"; }
    virtual BOOL canBeDetailed() { return FALSE; }
    virtual BOOL canBeLMAPped() { return FALSE; }

    virtual void Compile(CBlender_Compile& C);

    CBlender_zoom_MSAA();
    virtual ~CBlender_zoom_MSAA();
    virtual void SetDefine(LPCSTR Name, LPCSTR Definition)
    {
        this->Name = Name;
        this->Definition = Definition;
    }
    LPCSTR Name;
    LPCSTR Definition;
};
