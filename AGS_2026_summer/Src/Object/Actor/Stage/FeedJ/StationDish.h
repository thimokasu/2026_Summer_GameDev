#pragma once
#include "StationBase.h"
class StationDish :
    public StationBase
{
public:
    void SubLoad(void)override;
    void SubInit(void)override;
};

