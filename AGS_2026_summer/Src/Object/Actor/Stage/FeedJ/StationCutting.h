#pragma once
#include "StationBase.h"
class StationCutting :
    public StationBase
{
public:
    void SubLoad(void)override;
    void SubInit(void)override;
};

