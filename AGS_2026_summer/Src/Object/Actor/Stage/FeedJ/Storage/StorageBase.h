#pragma once
#include "../StationBase.h"
#include<memory>
#include"../../../Item/FeedJ/Food/FoodBase.h"
#include"../../../Item/FeedJ/FeedJItemHeaders.h"
#include"../../../Item/FeedJ/Food/FoodKind.h"

class StorageBase :
    public StationBase
{
public:
    void SubLoad(void)override;
    void SubInit(void)override;

    std::unique_ptr<FoodBase> CreateFood(void);
protected:
    FOOD_KIND fKind_ = FOOD_KIND::NONE;

};

