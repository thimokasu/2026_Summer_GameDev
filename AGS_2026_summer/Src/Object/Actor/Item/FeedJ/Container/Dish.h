#pragma once
#include "ContainerBase.h"
class FoodBase;

class Dish :
    public ContainerBase
{
public:
    void SubLoad(void)override;
    void SubInit(void)override;
    void InitSlot(void)override;

private:

};

