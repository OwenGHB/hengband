﻿#pragma once

#include "player/special-defense-types.h"
#include "system/angband.h"

#include <vector>

typedef struct blow_stance {
    concptr desc; /* A verbose stance description */
    PLAYER_LEVEL min_level; /* Minimum level to use */
    concptr info;
} blow_stance;

extern const std::vector<blow_stance> monk_stances;
extern const std::vector<blow_stance> samurai_stances;
