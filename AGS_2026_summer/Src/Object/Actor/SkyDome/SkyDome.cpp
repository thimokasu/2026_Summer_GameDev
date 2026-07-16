#include "SkyDome.h"
#include "../../../Manager/Resource/ResourceManager.h"
#include "../../../Utility/AsoUtility.h"

SkyDome::SkyDome()
{
}

void SkyDome::SubLoad(void)
{
	trans_.SetModel(ResourceManager::GetInstance().LoadModelDuplicate(SRC::SKY_DOME));
}

void SkyDome::SubInit(void)
{
	entityKind_ = EntityKind::SKY_DOME;
	const float scale = 3.0f;
	trans_.scl = VGet(scale, scale, scale);
	rot_ = 90.0f;
	trans_.quaRot = Quaternion::Euler(VGet(0.0f, AsoUtility::Deg2RadF(rot_), 0.0f));
	trans_.pos = POS;
	trans_.Update();
}

void SkyDome::SubUpdate(void)
{
	

}

void SkyDome::SubDraw(void)
{
}

void SkyDome::SubRelease(void)
{
}
