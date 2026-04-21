#include "PhysicsSystem.h"
#include"../../../Object/Actor/ActorBase.h"
#include"../../../Object/Actor/Component/RigidBodyComponent/RigidBody.h"


PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::Update(const std::vector<std::shared_ptr<ActorBase>>& objects)
{
    const float dt = 1.0f / 60.0f;
    const VECTOR GRAVITY = VGet(0.0f, -9.8f, 0.0f);

    for (auto obj : objects)
    {
        if (!obj->HasComponent<RigidBody>()) continue;

        auto& rb = obj->GetComponent<RigidBody>();

        // Static / Kinematic を弾くならここ
        if (rb.GetInverseMass() == 0.0f) continue;

        // ===== 重力を Force として加える =====
        if (rb.IsUseGravity())
        {
            if (!rb.IsGrounded()) {
                // F = m * g
                rb.AddForce(GRAVITY);
            }
            else rb.SetVelocity({ rb.GetVelocity().x,0,rb.GetVelocity().z });
        }

        // ===== Force → Acceleration =====
        VECTOR acceleration = rb.GetForce();

        // ===== Velocity 更新 =====
        VECTOR newVel = VAdd(rb.GetVelocity(), acceleration);
        rb.SetVelocity(newVel);

        float yKeep = rb.GetVelocity().y;

        // ===== 減速（ダンピング） =====
        newVel = VScale(newVel, 0.975);

        rb.SetVelocity(newVel);



        //意図移動考慮した位置更新
        // ===== 位置更新 =====
        obj->GetTransform().prevPos = VAdd(
            obj->GetTransform().pos,
            VScale(rb.GetVelocity(), dt)
        );

        // ===== Force クリア =====
        rb.ClearForce();
        rb.SetGrounded(false);
    }
}

void PhysicsSystem::Resolve(const std::vector<std::shared_ptr<ActorBase>>& objects, std::vector<CollisionSystem::CollisionManifold> manifolds)
{
    for (auto& fold : manifolds)
    {
        auto& rbA = fold.actorA->GetComponent<RigidBody>();
        auto& rbB = fold.actorB->GetComponent<RigidBody>();

        float invMassA = rbA.GetInverseMass();
        float invMassB = rbB.GetInverseMass();
        float totalInvMass = invMassA + invMassB;

        if (totalInvMass == 0.0f) continue;

        float ratioA = invMassA / totalInvMass;
        float ratioB = invMassB / totalInvMass;

        if (invMassA > 0.0f) {
            fold.actorA->GetTransform().prevPos = VAdd(
                fold.actorA->GetTransform().prevPos,
                VScale(fold.result.normal, fold.result.penetration * ratioA) // プラス！
            );

            // 地面判定 (法線が上向き = Aが上に押し上げられた)
            if (fold.result.normal.y > 0.5f) {
                rbA.SetVelocity(VGet(rbA.GetVelocity().x, 0, rbA.GetVelocity().z));
                rbA.ClearGravity();
				rbA.SetGrounded(true);
            }
        }

        if (invMassB > 0.0f) {
            fold.actorB->GetTransform().prevPos = VAdd(
                fold.actorB->GetTransform().prevPos,
                VScale(fold.result.normal, -fold.result.penetration * ratioB) // マイナス！
            );

            // 地面判定 (法線が上向き = Bが下に押し下げられた = Bから見て上(A側)に地面がある状態)
            if (fold.result.normal.y < -0.5f) {
                rbB.SetVelocity(VGet(rbB.GetVelocity().x, 0, rbB.GetVelocity().z));
                rbB.ClearGravity();
				rbB.SetGrounded(true);
            }
        }
    }

    for (auto obj : objects)
    {
        if (!obj->HasComponent<RigidBody>()) continue;
        obj->GetTransform().pos = obj->GetTransform().prevPos;
    }
}