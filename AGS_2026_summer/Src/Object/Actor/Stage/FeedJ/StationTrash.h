#pragma once
#include "StationBase.h"
class StationTrash :
    public StationBase
{
public:
    void SubLoad(void)override;
    void SubInit(void)override;
};

