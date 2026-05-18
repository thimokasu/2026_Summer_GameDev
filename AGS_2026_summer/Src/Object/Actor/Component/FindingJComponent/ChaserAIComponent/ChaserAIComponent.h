#pragma once
#include "../../ComponentBase.h"
#include<memory>

class ChaserAIComponent :
    public ComponentBase
{
public:
    void SetTarget(std::shared_ptr<ActorBase> target) { target_ = target; }

private:
    std::shared_ptr<ActorBase> target_; // “¦‚°‚é‘¤‚ÌŽÀ‘Ì‚Ö‚Ìƒ|ƒCƒ“ƒ^
};

