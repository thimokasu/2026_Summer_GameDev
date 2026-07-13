#pragma once
#include "StorageBase.h"
class StorageCucamber :
    public StorageBase
{
public:
    void SubLoad(void)override;
    void SubInit(void)override;
};

