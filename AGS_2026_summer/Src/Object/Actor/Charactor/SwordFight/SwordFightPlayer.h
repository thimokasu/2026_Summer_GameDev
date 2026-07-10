#pragma once
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <DxLib.h>

#include "../CharactorBase.h"
class ColliderBase;
class ColliderCapsule;
class AnimationController;

class SwordFightPlayer :
	public CharactorBase
{
public:


	SwordFightPlayer(void);
	virtual ~SwordFightPlayer(void);
	void SubLoad(void) override;
	void SubInit(void) override;
	void SubUpdate(void) override;
	void SubDraw(void) override;
	void SubRelease(void) override;
	void InitCollider(void) override;

private:

	// èdóÕÇ…ÇÊÇÈà⁄ìÆó 
	virtual void MoveInput(void) override;

};

