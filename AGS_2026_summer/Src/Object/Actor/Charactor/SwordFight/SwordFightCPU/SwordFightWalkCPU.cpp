#include "SwordFightWalkCPU.h"

#include "../../../../../Object/Actor/Charactor/SwordFight/SwordFightCPU/SwordFIghtCPU.h"
#include "../../../../../Object/Actor/Charactor/SwordFight/SwordFightPlayer.h"

#include "../../../Manager/ActorManager.h"

#include "SwordFIghtCPUHeaders.h"

#include "../../../../Common/AnimationController.h"

void SwordFightWalkCPU::EnterT(SwordFIghtCPU* owner)
{
    isLoop_ = true;

    owner->GetAnimController()->Play(SwordFIghtCPU::Walk_CPU);
}

void SwordFightWalkCPU::HandleInputT(SwordFIghtCPU* owner)
{
}

void SwordFightWalkCPU::UpdateT(SwordFIghtCPU* owner)
{
    auto players =
        owner->GetActorManager()->FindActorsByKind(EntityKind::PLAYER);

    if (players.empty())
        return;

    auto* player =
        dynamic_cast<SwordFightPlayer*>(players[0]);

    if (player == nullptr)
        return;

    //プレイヤー方向
    VECTOR dir =
        VSub(
            player->GetTransform().pos,
            owner->GetTransform().pos);

    dir.y = 0.0f;

    float distance = VSize(dir);

    //プレイヤーの方向を向く

    if (distance > 0.01f)
    {
        dir = VNorm(dir);

        float yaw = atan2f(dir.x, dir.z);

        owner->GetTransform().quaRot =
            Quaternion::Euler(0.0f, yaw, 0.0f);
    }

    //--------------------------------------------------
    // プレイヤーが攻撃中ならガードすることがある
    //--------------------------------------------------

    if (player->IsAttacking())
    {
        if (distance < 120.0f)
        {
            if (GetRand(100) < 20)     //20%でガード
            {
                owner->ChangeState<SwordFightBlockIdleCPU>();
                return;
            }
        }
    }

    //--------------------------------------------------
    // 近づく
    //--------------------------------------------------

    if (distance > 90.0f)
    {
        owner->GetTransform().pos =
            VAdd(
                owner->GetTransform().pos,
                VScale(
                    dir,
                    owner->GetRigidBody().GetMoveSpeed()));
    }
    //--------------------------------------------------
    // 攻撃
    //--------------------------------------------------
    else
    {
        owner->ChangeState<SwordFightAttackCPU>();
    }
}

void SwordFightWalkCPU::ExitT(SwordFIghtCPU* owner)
{
}