#pragma once
#include "../ActorFactoryBase.h"
class UnicycleFactory :
    public ActorFactoryBase
{
public:
	UnicycleFactory();
	~UnicycleFactory() = default;
	std::vector<std::unique_ptr<ActorBase>> CreateActors(void) override;

private:

	float multiOffset_;

};

