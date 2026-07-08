#pragma once
#include<array>
#include<DxLib.h>

enum class StageLayout
{
    None = 0,
    Block,
    ReactionBlock,
};

constexpr StageLayout b = StageLayout::Block;
constexpr StageLayout n = StageLayout::None;
constexpr StageLayout r = StageLayout::ReactionBlock;

constexpr int TileSize = 150;
constexpr int W = 150;
constexpr int D = 150;
constexpr int H = 2;

namespace Stage1
{
    // 各高さごとにD行W列の2次元配列をH個用意
    constexpr std::array<std::array<std::array<StageLayout, W>, D>, H> stage = { {
        { // ===== 高さ 0 =====
            {
                // 各高さごとにD行W列の2次元配列をH個用意
     
                 b
                 
        
            }
        }

    } };
}
