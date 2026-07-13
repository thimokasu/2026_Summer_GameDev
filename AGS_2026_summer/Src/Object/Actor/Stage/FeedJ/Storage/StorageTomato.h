#pragma once
#include "StorageBase.h"
class StorageTomato :
    public StorageBase
{
public:
    void SubLoad(void)override;
    void SubInit(void)override;
};

