#pragma once
#include "../UIBase.h"
#include "../../../Common/IntVector3.h"
class Transform;


class Distance : public UIBase
{
public:
    // UIBaseのコンストラクタに合わせて引数を設定
    Distance(Vector2F pos);
    virtual ~Distance() = default;
    void SetUpdate(bool flag) { isUpdate_ = flag; }
    //プレイヤー位置を保持
    void SetTrans(const Transform* follow) { Transform_ = follow; }

public:

    //画像縦サイズ
    static constexpr int IMAGE_HEIGHT_HALF = 724 / 2;


protected:
    // UIBaseの仮想関数をオーバーライド
    void SubLoad() override;
    void SubInit() override;
    void SubUpdate() override;
    void SubDraw() override;
    void SubRelease() override;

private:
    const Transform* Transform_;
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

    
};
