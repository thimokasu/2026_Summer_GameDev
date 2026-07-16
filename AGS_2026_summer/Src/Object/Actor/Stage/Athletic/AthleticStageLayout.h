#pragma once
#include"AthleticStageKind.h"
#include<DxLib.h>
#include<array>

constexpr ATHLETIC_STAGE_KIND none = ATHLETIC_STAGE_KIND::NONE;
constexpr ATHLETIC_STAGE_KIND nf = ATHLETIC_STAGE_KIND::NORMAL_FLOOR;
constexpr ATHLETIC_STAGE_KIND bf = ATHLETIC_STAGE_KIND::BROKEN_FLOOR;
constexpr ATHLETIC_STAGE_KIND mf = ATHLETIC_STAGE_KIND::MOVE_FLOOR;
constexpr ATHLETIC_STAGE_KIND cl = ATHLETIC_STAGE_KIND::CLOUD;
constexpr ATHLETIC_STAGE_KIND mcl = ATHLETIC_STAGE_KIND::MINI_CLOUD;
constexpr ATHLETIC_STAGE_KIND sbox = ATHLETIC_STAGE_KIND::SPINBOX;
constexpr ATHLETIC_STAGE_KIND msbox = ATHLETIC_STAGE_KIND::MINI_SPINBOX;
constexpr ATHLETIC_STAGE_KIND sbar = ATHLETIC_STAGE_KIND::SPININGBAR;
constexpr ATHLETIC_STAGE_KIND msbar = ATHLETIC_STAGE_KIND::MINI_SPININGBAR;
constexpr ATHLETIC_STAGE_KIND start = ATHLETIC_STAGE_KIND::START;
constexpr ATHLETIC_STAGE_KIND goal = ATHLETIC_STAGE_KIND::GOAL;

constexpr int TileSize = 80;
constexpr int W = 21;
constexpr int D = 4;

namespace Athletic
{
	constexpr std::array<std::array<ATHLETIC_STAGE_KIND, W>, D> athleticStage =
	{{
		{start,mf,bf,nf,cl,mcl,nf,sbox,msbox,nf,sbar,msbar,nf,bf,msbox,bf,mf,msbox,mcl,msbar,goal},
		{start,mf,bf,nf,none,mcl,nf,none,msbox,nf,none,msbar,nf,msbar,mcl,bf,mf,msbox,bf,msbox,goal},
		{start,mf,bf,nf,cl,mcl,nf,sbox,msbox,nf,sbar,msbar,nf,bf,msbox,bf,mf,msbox,mcl,msbar,goal},
		{start,mf,bf,nf,none,mcl,nf,none,msbox,nf,none,msbar,nf,msbar,mcl,bf,mf,msbox,bf,msbox,goal},
	}};
}

