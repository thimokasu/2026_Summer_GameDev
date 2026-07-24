#pragma once
#include "../ActorBase.h"
#include "../../../Manager/Resource/ResourceManager.h"
class SkyDome :
    public ActorBase
{
public:
    SkyDome(void);
    SkyDome(SRC src);
    ~SkyDome() = default;

    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;

private:

    static constexpr VECTOR POS = { 180.0f,30.0f,100.0f };

    //‰ñ“]
    
    float rot_;
    float scale_;

    SRC src_;
};

