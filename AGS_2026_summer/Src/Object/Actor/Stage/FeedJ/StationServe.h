#pragma once
#include "StationBase.h"
class StationServe :
    public StationBase
{
public:
    void SubLoad(void)override;
    void SubInit(void)override;
};

