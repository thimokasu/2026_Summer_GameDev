#pragma once
#include "../../ItemBase.h"
#include<memory>
#include<unordered_map>
#include<typeindex>
#include<map>
#include"../InterFace/FeedJ_ICookable.h"
#include"../InterFace/FeedJ_IThrowble.h"
#include"../InterFace/FeedJ_Drop.h"
#include"../IFoodState.h"
#include"FoodKind.h"

class FeedJPlayer;
class ContainerBase;
class StationBase;

class FoodBase :
    public ItemBase,public FeedJ_ICookable,public FeedJ_IThrowble,public FeedJ_Drop
{
public:  
	static constexpr int COOKING_TIME = 240;

    FoodBase(void);
    ~FoodBase(void);

    void SubLoad(void)override;
    void SubInit(void)override;
    void SubUpdate(void)override;
    void SubDraw(void)override;
    void SubRelease(void)override;
    void InitCollider(void)override;


	void Throw(ActorBase* target)override;
	void OnCook(void)override;

	void OnPickUp(bool isPickUp) {isPickUp_ = isPickUp; }
	void OffPickUp(void) { isPickUp_ = false; }

    void AttachToPlayer(FeedJPlayer* player);
	void AttachToContainer(ContainerBase* container,VECTOR localOffset);
	void AttachToStation(StationBase* station,VECTOR localOffset);

	void Detach(void);

	template<typename T>
	void AddState(std::unique_ptr<T>state);

	template<typename T>
	void ChangeState(void);	//遷移したいステートを<>のなかにクラス名を宣言

	template<typename T>
	T* GetState(void);

	virtual void SetState(void) {};	//ステート初期化　AddState(std::make_unique<>());

	void Drop(ActorBase* target)override;

	FOOD_KIND GetFoodKind(void) { return kind_; }

	bool GetCanCook(void) { return canCook_; }
	void SetCanCook(bool flag) { canCook_ = flag; }

	void AddCookTime(void) { cookTime_++; }

protected:
#pragma region 関数
    //調理時間の残りを描画する
	void DrawCookTime(void);

#pragma endregion
#pragma region  変数
	bool isPickUp_ = true;   //持てるかどうか、調理後かつ皿の上にある場合は持てない
	int modelIDtoCook_ = -1; //調理後のモデルID
	int cookTime_ =0;
	VECTOR localOffset_ = { 0.0f,0.0f,0.0f }; //プレイヤーやステーションにくっつけるときのオフセット

    //プレイヤーが保持している場合UI表示する画像のハンドルID
	int uiHandleID_ = -1;

	bool canCook_ = true;

	FeedJPlayer* player_ = nullptr;
	StationBase* station_ = nullptr;
	ContainerBase* container_ = nullptr;

	std::unordered_map<std::type_index, std::unique_ptr<IFoodState>>stateMap_;
	IFoodState* currentState_ = nullptr;

	FOOD_KIND kind_ = FOOD_KIND::NONE;
#pragma endregion


};


template<typename T>
inline void FoodBase::AddState(std::unique_ptr<T> state)
{
	stateMap_[typeid(T)] = std::move(state);
}

template<typename T>
inline void FoodBase::ChangeState(void)
{
	auto it = stateMap_.find(typeid(T));
	if (it != stateMap_.end())
	{
		if (currentState_)currentState_->Exit(this);
		currentState_ = it->second.get();
		currentState_->Enter(this);
	}
}

template<typename T>
inline T* FoodBase::GetState(void)
{
	auto it = stateMap_.find(typeid(T));
	if (it != stateMap_.end()) {
		return dynamic_cast<T*>(it->second.get());
	}
	return nullptr;
}

