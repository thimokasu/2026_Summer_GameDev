#include "CollisionResolve.h"
#include"../../../Object/Actor/ActorBase.h"
CollisionResolve::CollisionResolve()
{
}

CollisionResolve::~CollisionResolve()
{
}

void CollisionResolve::Resolve(const std::vector<std::shared_ptr<ActorBase>>& objects, std::vector<CollisionSystem::CollisionManifold> mainfold)
{
	for (auto& fold : mainfold)
	{
		auto& rbA= fold.actorA->GetRigidBody();
		auto& rbB = fold.actorB->GetRigidBody();

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
