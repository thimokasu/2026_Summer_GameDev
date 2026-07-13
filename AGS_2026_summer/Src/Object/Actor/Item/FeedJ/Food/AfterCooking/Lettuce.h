#pragma once
#include "../FoodBase.h"
class Lettuce :
    public FoodBase
{
public:
    void SubLoad(void)override;
    void SubInit(void)override;

};

