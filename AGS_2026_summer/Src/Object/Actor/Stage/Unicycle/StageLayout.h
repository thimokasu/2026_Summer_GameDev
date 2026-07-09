#pragma once
#include <array>
#include <DxLib.h>

enum class StageLayout
{
    None = 0,
    Block,
};

constexpr StageLayout b = StageLayout::Block;
constexpr StageLayout n = StageLayout::None;

constexpr int TileSize = 20;
constexpr int W = 5;
constexpr int D = 100; 

namespace Stage1
{
    // DçsWóÒÇÃ2éüå≥îzóÒ
    constexpr std::array<std::array<StageLayout, W>, D> stage = {{

        // Åy0 - 9çsñ⁄Åz
        {n, b, b, b, n},
        {n, b, b, b, n},
        {n, b, b, b, n},
        {n, b, b, b, n},
        {n, b, b, b, n},
        {n, n, b, b, n},
        {n, n, n, b, n},
        {n, n, n, b, b},
        {n, n, n, b, b},
        {n, n, n, b, b},

        // Åy10 - 19çsñ⁄Åz
        {n, n, n, b, b},
        {n, n, b, b, n},
        {n, n, b, b, n},
        {n, n, b, b, n},
        {n, b, b, n, n},
        {n, b, b, n, n},
        {n, b, n, n, n},
        {b, b, n, n, n},
        {b, b, n, n, n},
        {b, b, n, n, n},

        // Åy20 - 29çsñ⁄Åz
        {b, b, n, n, n},
        {n, b, n, n, n},
        {n, b, b, n, n},
        {n, b, b, n, n},
        {n, n, b, n, n},
        {n, b, b, b, n},
        {n, b, b, b, n},
        {n, b, b, b, n},
        {n, b, b, b, n},
        {n, b, b, b, n},

        // Åy30 - 39çsñ⁄Åz
        {n, n, b, n, n},
        {n, n, b, n, n}, 
        {n, n, b, n, n}, 
        {n, n, b, n, n}, 
        {n, n, b, n, n},
        {n, n, b, n, n}, 
        {n, n, b, n, n}, 
        {n, n, b, n, n}, 
        {n, n, b, n, n}, 
        {n, n, b, n, n},

        // Åy40 - 49çsñ⁄Åz
        {n, n, b, b, n}, 
        {n, n, n, b, b}, 
        {n, n, n, n, b}, 
        {n, n, n, n, b}, 
        {n, n, n, b, b},
        {n, n, b, b, n}, 
        {n, n, b, n, n},
        {n, b, b, n, n}, 
        {n, b, n, n, n}, 
        {b, b, n, n, n},

        // Åy50 - 59çsñ⁄Åz
        {b, n, n, n, n},
        {b, n, n, n, n},
        {b, b, n, n, n},
        {n, b, b, n, n},
        {n, n, b, n, n},
        {n, n, b, b, n},
        {n, n, b, b, n}, 
        {n, n, b, b, n}, 
        {n, n, b, b, n}, 
        {n, n, b, b, n},

        // Åy60 - 69çsñ⁄Åz
        {n, n, b, b, n}, 
        {n, n, b, b, n}, 
        {n, n, b, b, n}, 
        {n, n, b, b, n}, 
        {n, b, b, b, n},
        {n, b, b, n, n},
        {n, b, b, n, n},
        {n, b, b, n, n},
        {n, b, b, n, n}, 
        {n, b, b, n, n},

        // Åy70 - 79çsñ⁄Åz
        {n, n, b, b, n}, 
        {n, n, b, b, n}, 
        {n, n, b, b, n}, 
        {n, n, b, b, n}, 
        {n, b, b, n, n},
        {n, b, b, n, n}, 
        {n, b, b, n, n},
        {n, b, b, n, n},
        {n, b, b, n, n},
        {n, n, b, b, n},

        // Åy80 - 89çsñ⁄Åz
        {n, n, b, b, b}, 
        {n, n, n, b, b}, 
        {n, n, n, n, b}, 
        {n, n, n, n, b},
        {n, n, n, n, b},
        {n, n, n, n, b},
        {n, n, n, b, b}, 
        {n, n, b, b, n}, 
        {n, b, b, n, n},
        {b, b, n, n, n},

        // Åy90 - 99çsñ⁄Åz
        {b, n, n, n, n}, 
        {b, b, n, n, n}, 
        {n, b, b, n, n}, 
        {n, n, b, b, n}, 
        {n, n, n, b, b},
        {n, n, n, b, n}, 
        {n, n, n, b, n}, 
        {n, n, b, b, n}, 
        {n, b, b, b, n},
        {b, b, b, b, b}
   } };
}
