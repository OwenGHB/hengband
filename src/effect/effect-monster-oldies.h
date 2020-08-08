﻿#pragma once

#include "system/angband.h"
#include "effect/effect-monster-util.h"

switch_result effect_monster_old_poly(effect_monster_type *em_ptr);
switch_result effect_monster_old_clone(player_type *caster_ptr, effect_monster_type *em_ptr);
switch_result effect_monster_star_heal(player_type *caster_ptr, effect_monster_type *em_ptr);
switch_result effect_monster_old_heal(player_type *caster_ptr, effect_monster_type *em_ptr);
switch_result effect_monster_old_speed(player_type *caster_ptr, effect_monster_type *em_ptr);
switch_result effect_monster_old_slow(player_type *caster_ptr, effect_monster_type *em_ptr);
switch_result effect_monster_old_sleep(player_type *caster_ptr, effect_monster_type *em_ptr);
switch_result effect_monster_old_conf(player_type *caster_ptr, effect_monster_type *em_ptr);
switch_result effect_monster_stasis(effect_monster_type *em_ptr, bool to_evil);
switch_result effect_monster_stun(effect_monster_type *em_ptr);
