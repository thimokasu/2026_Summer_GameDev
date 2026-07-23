#pragma once
#include "../UIBase.h"
#include "../../../Common/IntVector3.h"
#include <functional>
class Transform;
using GoalCallBack = std::function<void()>;


class Distance : public UIBase
{
public:
    // UIBaseのコンストラクタに合わせて引数を設定
    Distance(Vector2F pos);
    virtual ~Distance() = default;
    void SetUpdate(bool flag) { isUpdate_ = flag; }
    //プレイヤー位置を保持
    void SetTrans(const Transform* follow) { Transform_.push_back(follow); }
	//ゴール時のコールバック関数を設定
    void SetGoalCallBack(GoalCallBack callBack) { goalCallBack_ = std::move(callBack); }


public:

    //画像縦サイズ
    static constexpr int IMAGE_HEIGHT_HALF = 724 / 2;
    static constexpr int IMAGE_HALF = 2172 / 2 * 0.2;


protected:
    // UIBaseの仮想関数をオーバーライド
    void SubLoad() override;
    void SubInit() override;
    void SubUpdate() override;
    void SubDraw() override;
    void SubRelease() override;

private:
   std::vector< const Transform*> Transform_;
    float distance_;
    bool isUpdate_;
    int fontHandle_; 
    float scale_;
    int textColor_;
    int edgeColor_;
    int bgHandle_;
    int iconHandle_;
    int distanceHandle_;
    float StartPos_;
    //縁取りカラー
    IntVector3 bgColor_;

	//ゴール時のコールバック関数
	GoalCallBack goalCallBack_;

    
};
