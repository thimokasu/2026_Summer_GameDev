#pragma once
#include "../../../Common/IntVector3.h"
#include "../UIBase.h"
#include <functional>
using StartCallBack = std::function<void()>;


class CountTimer : public UIBase
{
public:
    // UIBaseのコンストラクタに合わせて引数を設定
    CountTimer(Vector2F pos);
    virtual ~CountTimer() = default;
    void SetUpdate(bool flag) { isUpdate_ = flag; }
    //スタート処理
    void SetStartCallBack(StartCallBack callBack) { startCallBack_ = std::move(callBack); }

   
public:

    //画像サイズ
    static constexpr int IMAGE_SIZE = 64;

	//マークの数
    static constexpr int MARK_NUM = 12;
    static constexpr float RADIUS = 100.0f;

protected:
    // UIBaseの仮想関数をオーバーライド
    void SubLoad() override;
    void SubInit() override;
    void SubUpdate() override;
    void SubDraw() override;
    void SubRelease() override;

private:
    float time_;
    bool isUpdate_;
    int fontHandle_;
    float scale_;
    int textColor_;
    int edgeColor_;
    int countHandle_;
    float angle_;
    int yellowHandle_;
    //縁取りカラー
    IntVector3 bgColor_;

	//スタートコールバック
	StartCallBack startCallBack_;


};