#pragma once
// ActorFactoryBase.h
#include <vector>
#include <memory>
#include "../../ActorBase.h"

class ActorFactoryBase {
public:
    virtual ~ActorFactoryBase() {}

    virtual std::vector<std::shared_ptr<ActorBase>> CreateActors() = 0;
};