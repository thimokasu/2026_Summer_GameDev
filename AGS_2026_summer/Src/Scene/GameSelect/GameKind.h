#pragma once


enum class Game {};

enum class GAMEKMODE
{
	OnePlayer,
	TwoPlayer,
	ThreePlayer,
	FourPlayer,
};;

struct GameInfo
{
	GAMEKMODE gameMode;
	Game gameID;
	int stageID;
};
namespace OnePlayer
{
	enum class Game { A, B, };
	namespace A {
		enum class Stage { Stage1, Stage2, Stage3, }; 
	}
	namespace B {
		enum class Stage { Stage1, Stage2, Stage3, };
	}
}

namespace TwoPlayer
{
	enum class Game { A, B, };
	namespace A {
		enum class Stage { Stage1, Stage2, Stage3, };
	}
	namespace B {
		enum class Stage { Stage1, Stage2, Stage3, };
	}
}

namespace ThreePlayer
{
	enum class Game { A, B, };
	namespace A {
		enum class Stage { Stage1, Stage2, Stage3, };
	}
	namespace B {
		enum class Stage { Stage1, Stage2, Stage3, };
	}
}

namespace FourPlayer
{
	enum class Game { FindingJ, B, };
	namespace FindingJ {
		enum class Stage { Stage1, Stage2, Stage3, };
	}
	namespace B {
		enum class Stage { Stage1, Stage2, Stage3, };
	}
}