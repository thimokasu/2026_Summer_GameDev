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

constexpr int TileSize = 10;
constexpr int W = 5;
constexpr int D = 205; 

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
        {n, n, n, b, n},
        {n, n, n, b, n}, 
        {n, n, n, b, n}, 
        {n, n, b, b, n}, 
        {n, b, b, b, n},
        {b, b, b, b, b},
        // Åy100 - 109çsñ⁄Åz
        { n, b, b, b, n },
        { n, b, b, b, n },
        { n, b, b, b, n },
        { n, b, b, b, n },
        { n, b, b, b, n },
        { n, n, b, b, n },
        { n, n, n, b, n },
        { n, n, n, b, b },
        { n, n, n, b, b },
        { n, n, n, b, b },

        // Åy110 - 119çsñ⁄Åz
        { n, n, n, b, b },
        { n, n, b, b, n },
        { n, n, b, b, n },
        { n, n, b, b, n },
        { n, b, b, n, n },
        { n, b, b, n, n },
        { n, b, n, n, n },
        { b, b, n, n, n },
        { b, b, n, n, n },
        { b, b, n, n, n },

        // Åy120 - 129çsñ⁄Åz
        { b, b, n, n, n },
        { n, b, n, n, n },
        { n, b, b, n, n },
        { n, b, b, n, n },
        { n, n, b, n, n },
        { n, b, b, b, n },
        { n, b, b, b, n },
        { n, b, b, b, n },
        { n, b, b, b, n },
        { n, b, b, b, n },

        // Åy130 - 139çsñ⁄Åz
        { n, n, b, n, n },
        { n, n, b, n, n },
        { n, n, b, n, n },
        { n, n, b, n, n },
        { n, n, b, n, n },
        { n, n, b, n, n },
        { n, n, b, n, n },
        { n, n, b, n, n },
        { n, n, b, n, n },
        { n, n, b, n, n },

        // Åy140 - 149çsñ⁄Åz
        { n, n, b, b, n },
        { n, n, n, b, b },
        { n, n, n, n, b },
        { n, n, n, n, b },
        { n, n, n, b, b },
        { n, n, b, b, n },
        { n, n, b, n, n },
        { n, b, b, n, n },
        { n, b, n, n, n },
        { b, b, n, n, n },

        // Åy150 - 159çsñ⁄Åz
        { b, n, n, n, n },
        { b, n, n, n, n },
        { b, b, n, n, n },
        { n, b, b, n, n },
        { n, n, b, n, n },
        { n, n, b, b, n },
        { n, n, b, b, n },
        { n, n, b, b, n },
        { n, n, b, b, n },
        { n, n, b, b, n },

        // Åy160 - 169çsñ⁄Åz
        { n, n, b, b, n },
        { n, n, b, b, n },
        { n, n, b, b, n },
        { n, n, b, b, n },
        { n, b, b, b, n },
        { n, b, b, n, n },
        { n, b, b, n, n },
        { n, b, b, n, n },
        { n, b, b, n, n },
        { n, b, b, n, n },

        // Åy170 - 179çsñ⁄Åz
        { n, n, b, b, n },
        { n, n, b, b, n },
        { n, n, b, b, n },
        { n, n, b, b, n },
        { n, b, b, n, n },
        { n, b, b, n, n },
        { n, b, b, n, n },
        { n, b, b, n, n },
        { n, b, b, n, n },
        { n, n, b, b, n },

        // Åy180 - 189çsñ⁄Åz
        { n, n, b, b, b },
        { n, n, n, b, b },
        { n, n, n, n, b },
        { n, n, n, n, b },
        { n, n, n, n, b },
        { n, n, n, n, b },
        { n, n, n, b, b },
        { n, n, b, b, n },
        { n, b, b, n, n },
        { b, b, n, n, n },

        // Åy190 - 199çsñ⁄Åz
        { b, n, n, n, n },
        { b, b, n, n, n },
        { n, b, b, n, n },
        { n, n, b, b, n },
        { n, n, n, b, n },
        { n, n, n, b, n },
        { n, n, n, b, n },
        { n, n, b, b, n },
        { n, b, b, b, n },
        { b, b, b, b, b },
        //Åy200 - 205çsñ⁄Åz
        { b, b, b, b, b },
        { b, b, b, b, b },
        { b, b, b, b, b },
        { b, b, b, b, b },
        { b, b, b, b, b },
     
   } };
}
