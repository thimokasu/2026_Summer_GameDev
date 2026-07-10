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

constexpr int TileSize = 20;
constexpr int W = 19;
constexpr int D = 11;
constexpr int H = 2;
namespace Stage1
{
    constexpr std::array<std::array<std::array<StageLayout, W>, D>, H> stage = { {
       { // ===== çÇÇ≥ 0 =====
           {
              b
           }
       }  } };
}
