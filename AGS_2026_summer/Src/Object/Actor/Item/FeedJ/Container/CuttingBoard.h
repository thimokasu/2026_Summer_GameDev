#pragma once
#include "ContainerBase.h"
class CuttingBoard :
    public ContainerBase
{
public  :
    void SubLoad(void)override;
    void SubInit(void)override;
    void InitSlot(void)override;

};

