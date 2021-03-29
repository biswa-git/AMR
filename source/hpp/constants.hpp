#pragma once
#include"preprocessor.hpp"

constexpr int Dim = 3;
constexpr int g_MaxLevel = 5;

constexpr int g_BitsetCoordDataSize = g_MaxLevel;
constexpr int g_BitsetLevelDataSize = LOG2<g_MaxLevel> +1;
constexpr int g_BitsetHashSize = g_MaxLevel * 3 + g_BitsetLevelDataSize;