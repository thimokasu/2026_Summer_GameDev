#include "SkyDome.h"
#include "../../../Utility/AsoUtility.h"

SkyDome::SkyDome(SRC src)
{
	src_=src;
}

void SkyDome::SubLoad(void)
{
	trans_.SetModel(ResourceManager::GetInstance().LoadModelDuplicate(src_));
}

void SkyDome::SubInit(void)
{
	switch (src_)
	{
	case SRC::FJ_STAGE:
		entityKind_ = EntityKind::SKY_DOME;
		scale_ = 3.0f;
		trans_.scl = VGet(scale_, scale_, scale_);
		rot_ = 90.0f;
		trans_.quaRot = Quaternion::Euler(VGet(0.0f, AsoUtility::Deg2RadF(rot_), 0.0f));
		trans_.pos = POS;
		trans_.Update();
		break;
	case SRC::SKY_DOME:
		entityKind_ = EntityKind::SKY_DOME;
		scale_ = 30.0f;
		trans_.scl = VGet(scale_, scale_, scale_);
		rot_ = 90.0f;
		trans_.quaRot = Quaternion::Euler(VGet(0.0f, AsoUtility::Deg2RadF(rot_), 0.0f));
		trans_.pos = POS;
		trans_.Update();
		break;
	default:
		break;
	}

}

void SkyDome::SubUpdate(void)
{
	switch (src_)
	{
	case SRC::FJ_STAGE:
		break;
	case SRC::SKY_DOME:
		rot_+=0.1f;
		trans_.quaRot = Quaternion::Euler(VGet(0.0f, AsoUtility::Deg2RadF(rot_), 0.0f));
		break;
	default:
		break;
	}
}

void SkyDome::SubDraw(void)
{
}

void SkyDome::SubRelease(void)
{
}
