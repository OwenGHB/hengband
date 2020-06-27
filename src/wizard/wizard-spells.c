﻿/*!
 * @brief ウィザードモード専用のスペル処理
 * @date 2020/06/27
 * @author Hourier
 */

#include "wizard/wizard-spells.h"
#include "core/asking-player.h"
#include "floor/floor.h"
#include "io/targeting.h"
#include "monster-floor/monster-generator.h"
#include "monster-floor/monster-summon.h"
#include "monster-floor/place-monster-types.h"
#include "mspell/mspells3.h"
#include "player/player-effects.h"
#include "spell-kind/spells-teleport.h"
#include "spell-realm/spells-chaos.h"
#include "spell/spells-status.h"
#include "view/display-messages.h"

debug_spell_command debug_spell_commands_list[SPELL_MAX] = {
    { 2, "vanish dungeon", { .spell2 = { vanish_dungeon } } },
    { 3, "true healing", { .spell3 = { true_healing } } },
    { 2, "drop weapons", { .spell2 = { drop_weapons } } },
};

/*!
 * @brief コマンド入力により任意にスペル効果を起こす / Wizard spells
 * @return 実際にテレポートを行ったらTRUEを返す
 */
bool do_cmd_debug_spell(player_type *creature_ptr)
{
    char tmp_val[50] = "\0";
    int tmp_int;

    if (!get_string("SPELL: ", tmp_val, 32))
        return FALSE;

    for (int i = 0; i < SPELL_MAX; i++) {
        if (strcmp(tmp_val, debug_spell_commands_list[i].command_name) != 0)
            continue;

        switch (debug_spell_commands_list[i].type) {
        case 2:
            (*(debug_spell_commands_list[i].command_function.spell2.spell_function))(creature_ptr);
            return TRUE;
            break;
        case 3:
            tmp_val[0] = '\0';
            if (!get_string("POWER:", tmp_val, 32))
                return FALSE;
            tmp_int = atoi(tmp_val);
            (*(debug_spell_commands_list[i].command_function.spell3.spell_function))(creature_ptr, tmp_int);
            return TRUE;
            break;
        default:
            break;
        }
    }

    msg_format("Command not found.");
    return FALSE;
}

/*!
 * @brief 必ず成功するウィザードモード用次元の扉処理 / Wizard Dimension Door
 * @param caster_ptr プレーヤーへの参照ポインタ
 * @return なし
 */
void wiz_dimension_door(player_type *caster_ptr)
{
    POSITION x = 0, y = 0;
    if (!tgt_pt(caster_ptr, &x, &y))
        return;

    teleport_player_to(caster_ptr, y, x, TELEPORT_NONMAGICAL);
}

/*!
 * @brief ウィザードモード用モンスターの群れ生成 / Summon a horde of monsters
 * @param caster_ptr プレーヤーへの参照ポインタ
 * @return なし
 */
void do_cmd_summon_horde(player_type *caster_ptr)
{
    POSITION wy = caster_ptr->y, wx = caster_ptr->x;
    int attempts = 1000;

    while (--attempts) {
        scatter(caster_ptr, &wy, &wx, caster_ptr->y, caster_ptr->x, 3, 0);
        if (is_cave_empty_bold(caster_ptr, wy, wx))
            break;
    }

    (void)alloc_horde(caster_ptr, wy, wx, summon_specific);
}

/*!
 * @brief ウィザードモード用処理としてターゲット中の相手をテレポートバックする / Hack -- Teleport to the target
 * @return なし
 */
void do_cmd_wiz_bamf(player_type *caster_ptr)
{
    if (!target_who)
        return;

    teleport_player_to(caster_ptr, target_row, target_col, TELEPORT_NONMAGICAL);
}

/*!
 * @brief 青魔導師の魔法を全て習得済みにする /
 * debug command for blue mage
 * @return なし
 */
void do_cmd_wiz_blue_mage(player_type *caster_ptr)
{
    BIT_FLAGS f4 = 0L, f5 = 0L, f6 = 0L;
    for (int j = 1; j < A_MAX; j++) {
        set_rf_masks(&f4, &f5, &f6, j);

        int i;
        for (i = 0; i < 32; i++) {
            if ((0x00000001 << i) & f4)
                caster_ptr->magic_num2[i] = 1;
        }

        for (; i < 64; i++) {
            if ((0x00000001 << (i - 32)) & f5)
                caster_ptr->magic_num2[i] = 1;
        }

        for (; i < 96; i++) {
            if ((0x00000001 << (i - 64)) & f6)
                caster_ptr->magic_num2[i] = 1;
        }
    }
}

/*!
 * @brief 現在のフロアに合ったモンスターをランダムに召喚する /
 * Summon some creatures
 * @param caster_ptr プレーヤーへの参照ポインタ
 * @param num 生成処理回数
 * @return なし
 */
void do_cmd_wiz_summon(player_type *caster_ptr, int num)
{
    for (int i = 0; i < num; i++) {
        (void)summon_specific(caster_ptr, 0, caster_ptr->y, caster_ptr->x, caster_ptr->current_floor_ptr->dun_level, 0, (PM_ALLOW_GROUP | PM_ALLOW_UNIQUE));
    }
}

/*!
 * @brief モンスターを種族IDを指定して敵対的に召喚する /
 * Summon a creature of the specified type
 * @param r_idx モンスター種族ID
 * @return なし
 * @details
 * This function is rather dangerous
 */
void do_cmd_wiz_named(player_type *summoner_ptr, MONRACE_IDX r_idx)
{
    (void)summon_named_creature(summoner_ptr, 0, summoner_ptr->y, summoner_ptr->x, r_idx, (PM_ALLOW_SLEEP | PM_ALLOW_GROUP));
}

/*!
 * @brief モンスターを種族IDを指定してペット召喚する /
 * Summon a creature of the specified type
 * @param r_idx モンスター種族ID
 * @return なし
 * @details
 * This function is rather dangerous
 */
void do_cmd_wiz_named_friendly(player_type *summoner_ptr, MONRACE_IDX r_idx)
{
    (void)summon_named_creature(summoner_ptr, 0, summoner_ptr->y, summoner_ptr->x, r_idx, (PM_ALLOW_SLEEP | PM_ALLOW_GROUP | PM_FORCE_PET));
}
