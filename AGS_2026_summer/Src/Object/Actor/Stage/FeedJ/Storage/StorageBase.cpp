#include "StorageBase.h"

void StorageBase::SubLoad(void)
{
}

void StorageBase::SubInit(void)
{
}

std::unique_ptr<FoodBase>StorageBase::CreateFood(void)
{
	std::unique_ptr<FoodBase>f;
	switch (fKind_)
	{
	case FOOD_KIND::TOMATO:
		f= std::make_unique<Tomato>();
		break;
	case FOOD_KIND::CUCMBER:
		f= std::make_unique<Cucamber>();
		break;
	case FOOD_KIND::LETTUCE:
		f= std::make_unique<Lettuce>();
		break;
	}
	f->Load();
	f->Init();
	return f;
}
