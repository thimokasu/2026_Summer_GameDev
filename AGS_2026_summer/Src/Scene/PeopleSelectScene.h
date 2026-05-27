#pragma once
#include "SceneBase.h"
class PeopleSelectScene :
    public SceneBase
{
	public:
	PeopleSelectScene();
	~PeopleSelectScene();
    void Load(void)override;
    void Init(void)override;
    void Update(void)override;
    void Draw(void)override;
    void Release(void)override;
private:
};

