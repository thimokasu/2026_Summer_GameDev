#include "FeedJ_Food_Cooking.h"
#include"../FoodBase.h"

void FeedJ_Food_Cooking::Enter(FoodBase* owner)
{

}
void FeedJ_Food_Cooking::Update(FoodBase* owner)
{
	owner->AddCookTime();
}
void FeedJ_Food_Cooking::Exit(FoodBase* owner)
{

}