#pragma once
enum class Game {};

enum class GameMode
{
	ONEPLAYER,
	TWOPLAYER,
	THREEPLAYER,
	FOURPLAYER,

	TEST,
	MAX
};

struct GameInfo
{
	GameMode mode_;
	Game game_;
	int stageNum_;
};

namespace Test
{
	enum class Game { A };
	namespace A
	{
		enum class Stage { Stage1 };
	}
}

namespace OnePlayer
{
	enum class Game { A, B };
	namespace A
	{
		enum class Stage { Stage1, Stage2, Stage3 };
	}
	namespace B
	{
		enum class  Stage{Stage1,Stage2,Stage3};
	}
}

namespace TwoPlayer
{
	enum class Game { A, B };
	namespace A
	{
		enum class Stage { Stage1, Stage2, Stage3 };
	}
	namespace B
	{
		enum class  Stage { Stage1, Stage2, Stage3 };
	}
}

namespace ThreePlayer
{
	enum class Game { A, B };
	namespace A
	{
		enum class Stage { Stage1, Stage2, Stage3 };
	}
	namespace B
	{
		enum class  Stage { Stage1, Stage2, Stage3 };
	}
}

namespace FourPlayer
{
	enum class Game { FindingJ, B };
	namespace FindingJ
	{
		enum class Stage { Stage1, Stage2, Stage3 };
	}
	namespace B
	{
		enum class  Stage { Stage1, Stage2, Stage3 };
	}
}