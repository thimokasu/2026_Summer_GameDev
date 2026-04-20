#pragma once
#include<array>
#include<DxLib.h>

enum class StageLayout
{
	None=0,
	Block,
	ReactionBlock,
};

constexpr StageLayout b = StageLayout::Block;
constexpr StageLayout n = StageLayout::None;
constexpr StageLayout r = StageLayout::ReactionBlock;

constexpr int TileSize = 20;
constexpr int W = 20;
constexpr int D = 10;
constexpr int H = 2;

namespace Stage1
{
    // 各高さごとにD行W列の2次元配列をH個用意
    constexpr std::array<std::array<std::array<StageLayout, W>, D>, H> stage = { {
        { // ===== 高さ 0 =====
            {
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b}, // 1行目
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},// 2行目
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b}
            }
        },
        { // ===== 高さ 1 =====
            {
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b},
                {b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b}
            }
        }
    } };
}