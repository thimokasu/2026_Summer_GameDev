#pragma once
#include "../../CharactorBase.h"
#include <functional>
class AnimationController;

using FallCallBack = std::function<void()>;


class UnicyclePlayer :
    public CharactorBase
{
public:
    UnicyclePlayer(VECTOR pos,int pad);
    virtual ~UnicyclePlayer(void);
    void SubLoad(void) override;
    void SubInit(void) override;
    void SubUpdate(void) override;
    void SubDraw(void) override;
    void SubRelease(void) override;
    void InitCollider(void) override;
    void SetFallCallBack(FallCallBack callBack) { fallCallBack_ = std::move(callBack); }

    //ゲーム終了後の落下
	void FallAfterGameEnd(void) { 
        do {
			trans_.pos.y -= 0.2f;
			riderTrans_.pos.y = trans_.pos.y;
			riderTrans_.Update();
		} while (trans_.pos.y >=-1000);
    }

private:
    void MoveInput(void) override;

private:

    //搭乗者
    Transform riderTrans_;
	VECTOR riderOffset_ = VGet(0.0f, 0.0f, 0.0f);
    std::unique_ptr<AnimationController> riderAnimation_;

	//落下時のコールバック
    FallCallBack fallCallBack_;

    //コントローラーの番号
    int padNum_;

    
};