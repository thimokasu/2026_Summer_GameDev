#pragma once
#include "../../ActorBase.h"
class Block :
    public ActorBase
{
public:
    Block(void);
    ~Block(void);
    Block(VECTOR pos);

    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;
private:

};

