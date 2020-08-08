﻿#include "effect/effect-monster-lite-dark.h"
#include "monster-race/monster-race.h"
#include "monster-race/race-flags-resistance.h"
#include "monster-race/race-flags3.h"
#include "monster/monster-info.h"

switch_result effect_monster_lite_weak(player_type *caster_ptr, effect_monster_type *em_ptr)
{
	if (!em_ptr->dam)
	{
		em_ptr->skipped = TRUE;
		return SWITCH_CONTINUE;
	}

	if ((em_ptr->r_ptr->flags3 & RF3_HURT_LITE) == 0)
	{
		em_ptr->dam = 0;
		return SWITCH_CONTINUE;
	}

	if (em_ptr->seen) em_ptr->obvious = TRUE;

	if (is_original_ap_and_seen(caster_ptr, em_ptr->m_ptr))
		em_ptr->r_ptr->r_flags3 |= (RF3_HURT_LITE);

	em_ptr->note = _("は光に身をすくめた！", " cringes from the light!");
	em_ptr->note_dies = _("は光を受けてしぼんでしまった！", " shrivels away in the light!");
	return SWITCH_CONTINUE;
}


switch_result effect_monster_lite(player_type *caster_ptr, effect_monster_type *em_ptr)
{
	if (em_ptr->seen) em_ptr->obvious = TRUE;

	if (em_ptr->r_ptr->flagsr & RFR_RES_LITE)
	{
		em_ptr->note = _("には耐性がある！", " resists!");
		em_ptr->dam *= 2; em_ptr->dam /= (randint1(6) + 6);
		if (is_original_ap_and_seen(caster_ptr, em_ptr->m_ptr))
			em_ptr->r_ptr->r_flagsr |= (RFR_RES_LITE);
	}
	else if (em_ptr->r_ptr->flags3 & (RF3_HURT_LITE))
	{
		if (is_original_ap_and_seen(caster_ptr, em_ptr->m_ptr))
			em_ptr->r_ptr->r_flags3 |= (RF3_HURT_LITE);

		em_ptr->note = _("は光に身をすくめた！", " cringes from the light!");
		em_ptr->note_dies = _("は光を受けてしぼんでしまった！", " shrivels away in the light!");
		em_ptr->dam *= 2;
	}

	return SWITCH_CONTINUE;
}


switch_result effect_monster_dark(player_type *caster_ptr, effect_monster_type *em_ptr)
{
	if (em_ptr->seen) em_ptr->obvious = TRUE;

	if ((em_ptr->r_ptr->flagsr & RFR_RES_DARK) == 0)
		return SWITCH_CONTINUE;

	em_ptr->note = _("には耐性がある！", " resists!");
	em_ptr->dam *= 2; em_ptr->dam /= (randint1(6) + 6);
	if (is_original_ap_and_seen(caster_ptr, em_ptr->m_ptr))
		em_ptr->r_ptr->r_flagsr |= (RFR_RES_DARK);

	return SWITCH_CONTINUE;
}
