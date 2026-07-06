#pragma once
#include "../../../StateBehavior.h"
#include "../FeedJPlayer.h"
class FeedJ_Dash :
    public StateBehavior<FeedJPlayer>
{
public  :
    void EnterT(FeedJPlayer* owner) override;
    void HandleInputT(FeedJPlayer* owner) override;
    void UpdateT(FeedJPlayer* owner) override;
    void ExitT(FeedJPlayer* owner) override;
	void SetDashVec(const VECTOR& vec) { dashVec_ = vec; }
private:
	VECTOR dashVec_ = { 0.0f,0.0f,0.0f };
};

