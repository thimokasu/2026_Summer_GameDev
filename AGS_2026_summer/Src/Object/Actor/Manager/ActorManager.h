#pragma once
#include <cstdint>
#include<vector>
#include<memory>
#include<unordered_map>
#include"../ActorBase.h"
#include"../EntityKind.h"
#include"../../../Scene/GameSelect/GameInfo.h"

using EntityID = uint32_t;
class ActorFactoryBase;

class ActorManager
{
public:
	ActorManager(void);
	~ActorManager(void);

	void Load(GameInfo info);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	std::vector<std::unique_ptr<ActorBase>>& GetActors(void) { return actors_; }
	EntityKind GetEntityKind(EntityID id) const;
	//指定されたKindのActorを返す
	std::vector<ActorBase*>FindActorsByKind(EntityKind kind)const;
	//指定されたIDのActorを返す
	ActorBase* FindActorByID(EntityID id) const;
private:
#pragma region 変数
	std::vector<std::unique_ptr<ActorBase>> actors_;//アクターのリスト
	std::unordered_map<EntityID, EntityKind>id2kind_;//エンティティIDからエンティティ種別へのマップ
	std::unique_ptr<ActorFactoryBase>actorFactory_;//アクターファクトリー
	int entityID_ = 0;
#pragma endregion
#pragma region 関数
	void BindID2Kind(void);
	void SetFactory(GameInfo info);
	void OnePlayerGameFactory(GameInfo info);
	void TwoPlayerGameFactory(GameInfo info);
	void ThreePlayerGameFactory(GameInfo info);
	void FourPlayerGameFactory(GameInfo info);
#pragma endregion

};

