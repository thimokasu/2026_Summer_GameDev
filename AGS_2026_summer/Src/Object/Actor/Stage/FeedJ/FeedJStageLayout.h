#pragma once
#include"FeedJStageHeaders.h"
#include<DxLib.h>
#include<array>
#include"StationKind.h"

constexpr STATION_KIND nn = STATION_KIND::NONE;
constexpr STATION_KIND n = STATION_KIND::NORMAL;
constexpr STATION_KIND d = STATION_KIND::DISH;
constexpr STATION_KIND c = STATION_KIND::CUTTING;
constexpr STATION_KIND s = STATION_KIND::SERVE;
constexpr STATION_KIND t = STATION_KIND::TRASH;

constexpr STATION_KIND f_c = STATION_KIND::CUCAMBER;
constexpr STATION_KIND f_l = STATION_KIND::LETTUCE;
constexpr STATION_KIND f_t = STATION_KIND::TOMATO;

constexpr int TileSize = 20;
constexpr int W = 13;
constexpr int D = 8;

namespace FeedJStage1
{
    constexpr std::array<std::array<STATION_KIND, W>, D> station_ =
    { {
        {n,n,n,c,c,n,n,n,c,c,n,n,n},
        {f_t,nn,nn,nn,nn,nn,nn,nn,nn,nn,nn,nn,s},
        {n,nn,nn,nn,nn,nn,nn,nn,nn,nn,nn,nn,n},
        {t,nn,nn,n,n,nn,nn,nn,n,n,nn,nn,f_l},
        {n,nn,nn,nn,nn,nn,nn,nn,nn,nn,nn,nn,n},
        {f_c,nn,nn,nn,nn,nn,nn,nn,nn,nn,nn,nn,d},
        {n,nn,nn,nn,nn,nn,nn,nn,nn,nn,nn,nn,n},
        {n,n,n,c,c,n,n,n,c,c,n,n,n},
    } };
}
