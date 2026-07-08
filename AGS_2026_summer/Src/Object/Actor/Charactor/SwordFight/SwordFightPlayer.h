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


	// 状態
	enum class STATE
	{
		NONE,
		PLAY,
		WARP_RESERVE,
		WARP_MOVE,
		DEAD,
		VICTORY,
		END
	};

	// アニメーション種別
	enum class ANIM_TYPE
	{
		IDLE,
		WALK,
		ATTACK,
		LOSE,
		BLOCK,
		DAMAGE,
	};


    SwordFightPlayer(void);
    virtual ~SwordFightPlayer(void);
    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
    void InitCollider(void) override;

	
private:
	
	
    virtual void MoveInput(void) override;

	void InitAnimation(void);

	

	

};

