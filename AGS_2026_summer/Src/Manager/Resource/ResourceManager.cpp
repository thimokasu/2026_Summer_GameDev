#include <DxLib.h>
#include"../../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::DeleteInstance(void)
{
	if (instance_ != nullptr)
	{
		instance_->Destroy();
		delete instance_;
		instance_ = nullptr;
	}
}

void ResourceManager::Init(void)
{
	using RES = Resource;
	using RES_T = TYPE;

	static std::string PATH_IMG = Application::PATH_IMAGE;
	static std::string PATH_MDL = Application::PATH_MODEL;
	static std::string PATH_EFF = Application::PATH_EFFECT;

	Resource* res = nullptr;

#pragma region GameSelectScene
	res = new RES(RES_T::IMG, PATH_IMG + "GameSelectScene/PlayNum/One.png");
	resourcesMap_.emplace(SRC::ONE_PLAY, res);
	res = new RES(RES_T::IMG, PATH_IMG + "GameSelectScene/PlayNum/Two.png");
	resourcesMap_.emplace(SRC::TWO_PLAY,res);
	res = new RES(RES_T::IMG, PATH_IMG + "GameSelectScene/PlayNum/TwoVsTwo.png");
	resourcesMap_.emplace(SRC::TWO_VS_TWO, res);
	res = new RES(RES_T::IMG, PATH_IMG + "GameSelectScene/PlayNum/OneVsThree.png");
	resourcesMap_.emplace(SRC::ONE_VS_THREE, res);
	res = new RES(RES_T::IMG, PATH_IMG + "GameSelectScene/PlayNum/Four.png");
	resourcesMap_.emplace(SRC::FOUR, res);
	res = new RES(RES_T::IMG, PATH_IMG + "GameSelectScene/PlayNum/OneToFour.png");
	resourcesMap_.emplace(SRC::ONE_TO_FOUR, res);
#pragma endregion


	res = new RES(RES_T::MODEL, PATH_MDL + "FindingJ/Stage/Block.mv1");
	resourcesMap_.emplace(SRC::BLOCK, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "FindingJ/floor.mv1");
	resourcesMap_.emplace(SRC::FLOOR, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "FindingJ/ReactionBlock.mv1");
	resourcesMap_.emplace(SRC::REACTION_BLOCK, res);



}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	for (auto& res : resourcesMap_)
	{
		res.second->Release();
		delete res.second;
	}
	resourcesMap_.clear();
	delete instance_;
}

const Resource& ResourceManager::Load(SRC src)
{
	const Resource& res = _Load(src);
	if (res.type_ == TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}


int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}


ResourceManager::ResourceManager(void)
{
}

Resource& ResourceManager::_Load(SRC src)
{

	// ロード済みチェック
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return *resourcesMap_.find(src)->second;
	}

	// リソース登録チェック
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return dummy_;
	}

	// ロード処理
	rPair->second->Load();

	// 念のためコピーコンストラクタ
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;

}
