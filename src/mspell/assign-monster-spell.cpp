﻿/*!
 * @brief モンスターのスペル振り分け処理 / Spell launch by a monster
 * @date 2014/07/14
 * @author Habu
 */

#include "mspell/assign-monster-spell.h"
#include "blue-magic/blue-magic-checker.h"
#include "monster-race/race-ability-flags.h"
#include "mspell/mspell-ball.h"
#include "mspell/mspell-bolt.h"
#include "mspell/mspell-breath.h"
#include "mspell/mspell-curse.h"
#include "mspell/mspell-dispel.h"
#include "mspell/mspell-floor.h"
#include "mspell/mspell-learn-checker.h"
#include "mspell/mspell-particularity.h"
#include "mspell/mspell-result.h"
#include "mspell/mspell-special.h"
#include "mspell/mspell-status.h"
#include "mspell/mspell-summon.h"
#include "mspell/mspell-util.h"
#include "mspell/mspell-result.h"
#include "system/player-type-definition.h"
#include "util/enum-converter.h"

static MonsterSpellResult monspell_to_player_impl(PlayerType *player_ptr, MonsterAbilityType ms_type, POSITION y, POSITION x, MONSTER_IDX m_idx)
{
    // clang-format off
    switch (ms_type) {
    case MonsterAbilityType::SHRIEK: return spell_RF4_SHRIEK(m_idx, player_ptr, 0, MONSTER_TO_PLAYER); /* RF4_SHRIEK */
    case MonsterAbilityType::XXX1: break;   /* RF4_XXX1 */
    case MonsterAbilityType::DISPEL: return spell_RF4_DISPEL(m_idx, player_ptr, 0, MONSTER_TO_PLAYER); /* RF4_DISPEL */
    case MonsterAbilityType::ROCKET: return spell_RF4_ROCKET(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER);  /* RF4_ROCKET */
    case MonsterAbilityType::SHOOT: return spell_RF4_SHOOT(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER);   /* RF4_SHOOT */
    case MonsterAbilityType::XXX2: break;   /* RF4_XXX2 */
    case MonsterAbilityType::XXX3: break;   /* RF4_XXX3 */
    case MonsterAbilityType::XXX4: break;   /* RF4_XXX4 */
    case MonsterAbilityType::BR_ACID: return spell_RF4_BREATH(player_ptr, AttributeType::ACID, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_ACID */
    case MonsterAbilityType::BR_ELEC: return spell_RF4_BREATH(player_ptr, AttributeType::ELEC, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_ELEC */
    case MonsterAbilityType::BR_FIRE: return spell_RF4_BREATH(player_ptr, AttributeType::FIRE, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_FIRE */
    case MonsterAbilityType::BR_COLD: return spell_RF4_BREATH(player_ptr, AttributeType::COLD, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_COLD */
    case MonsterAbilityType::BR_POIS: return spell_RF4_BREATH(player_ptr, AttributeType::POIS, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_POIS */
    case MonsterAbilityType::BR_NETH: return spell_RF4_BREATH(player_ptr, AttributeType::NETHER, y, x, m_idx, 0, MONSTER_TO_PLAYER);   /* RF4_BR_NETH */
    case MonsterAbilityType::BR_LITE: return spell_RF4_BREATH(player_ptr, AttributeType::LITE, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_LITE */
    case MonsterAbilityType::BR_DARK: return spell_RF4_BREATH(player_ptr, AttributeType::DARK, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_DARK */
    case MonsterAbilityType::BR_CONF: return spell_RF4_BREATH(player_ptr, AttributeType::CONFUSION, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_CONF */
    case MonsterAbilityType::BR_SOUN: return spell_RF4_BREATH(player_ptr, AttributeType::SOUND, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_SOUN */
    case MonsterAbilityType::BR_CHAO: return spell_RF4_BREATH(player_ptr, AttributeType::CHAOS, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_CHAO */
    case MonsterAbilityType::BR_DISE: return spell_RF4_BREATH(player_ptr, AttributeType::DISENCHANT, y, x, m_idx, 0, MONSTER_TO_PLAYER);   /* RF4_BR_DISE */
    case MonsterAbilityType::BR_NEXU: return spell_RF4_BREATH(player_ptr, AttributeType::NEXUS, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_NEXU */
    case MonsterAbilityType::BR_TIME: return spell_RF4_BREATH(player_ptr, AttributeType::TIME, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_TIME */
    case MonsterAbilityType::BR_INER: return spell_RF4_BREATH(player_ptr, AttributeType::INERTIAL, y, x, m_idx, 0, MONSTER_TO_PLAYER);  /* RF4_BR_INER */
    case MonsterAbilityType::BR_GRAV: return spell_RF4_BREATH(player_ptr, AttributeType::GRAVITY, y, x, m_idx, 0, MONSTER_TO_PLAYER);  /* RF4_BR_GRAV */
    case MonsterAbilityType::BR_SHAR: return spell_RF4_BREATH(player_ptr, AttributeType::SHARDS, y, x, m_idx, 0, MONSTER_TO_PLAYER);   /* RF4_BR_SHAR */
    case MonsterAbilityType::BR_PLAS: return spell_RF4_BREATH(player_ptr, AttributeType::PLASMA, y, x, m_idx, 0, MONSTER_TO_PLAYER);   /* RF4_BR_PLAS */
    case MonsterAbilityType::BR_FORC: return spell_RF4_BREATH(player_ptr, AttributeType::FORCE, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_WALL */
    case MonsterAbilityType::BR_MANA: return spell_RF4_BREATH(player_ptr, AttributeType::MANA, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_MANA */
    case MonsterAbilityType::BA_NUKE: return spell_RF4_BA_NUKE(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BA_NUKE */
    case MonsterAbilityType::BR_NUKE: return spell_RF4_BREATH(player_ptr, AttributeType::NUKE, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_NUKE */
    case MonsterAbilityType::BA_CHAO: return spell_RF4_BA_CHAO(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BA_CHAO */
    case MonsterAbilityType::BR_DISI: return spell_RF4_BREATH(player_ptr, AttributeType::DISINTEGRATE, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF4_BR_DISI */
    case MonsterAbilityType::BA_ACID: return spell_RF5_BA_ACID(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BA_ACID */
    case MonsterAbilityType::BA_ELEC: return spell_RF5_BA_ELEC(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BA_ELEC */
    case MonsterAbilityType::BA_FIRE: return spell_RF5_BA_FIRE(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BA_FIRE */
    case MonsterAbilityType::BA_COLD: return spell_RF5_BA_COLD(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BA_COLD */
    case MonsterAbilityType::BA_POIS: return spell_RF5_BA_POIS(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BA_POIS */
    case MonsterAbilityType::BA_NETH: return spell_RF5_BA_NETH(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BA_NETH */
    case MonsterAbilityType::BA_WATE: return spell_RF5_BA_WATE(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BA_WATE */
    case MonsterAbilityType::BA_MANA: return spell_RF5_BA_MANA(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BA_MANA */
    case MonsterAbilityType::BA_DARK: return spell_RF5_BA_DARK(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BA_DARK */
    case MonsterAbilityType::DRAIN_MANA: return spell_RF5_DRAIN_MANA(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER);  /* RF5_DRAIN_MANA */
    case MonsterAbilityType::MIND_BLAST: return spell_RF5_MIND_BLAST(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER);  /* RF5_MIND_BLAST */
    case MonsterAbilityType::BRAIN_SMASH: return spell_RF5_BRAIN_SMASH(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_MIND_BLAST */
    case MonsterAbilityType::CAUSE_1: return spell_RF5_CAUSE_1(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_CAUSE_1 */
    case MonsterAbilityType::CAUSE_2: return spell_RF5_CAUSE_2(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_CAUSE_2 */
    case MonsterAbilityType::CAUSE_3: return spell_RF5_CAUSE_3(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_CAUSE_3 */
    case MonsterAbilityType::CAUSE_4: return spell_RF5_CAUSE_4(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_CAUSE_4 */
    case MonsterAbilityType::BO_ACID: return spell_RF5_BO_ACID(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BO_ACID */
    case MonsterAbilityType::BO_ELEC: return spell_RF5_BO_ELEC(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BO_ELEC */
    case MonsterAbilityType::BO_FIRE: return spell_RF5_BO_FIRE(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BO_FIRE */
    case MonsterAbilityType::BO_COLD: return spell_RF5_BO_COLD(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BO_COLD */
    case MonsterAbilityType::BA_LITE: return spell_RF5_BA_LITE(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BA_LITE */
    case MonsterAbilityType::BO_NETH: return spell_RF5_BO_NETH(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BO_NETH */
    case MonsterAbilityType::BO_WATE: return spell_RF5_BO_WATE(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BO_WATE */
    case MonsterAbilityType::BO_MANA: return spell_RF5_BO_MANA(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BO_MANA */
    case MonsterAbilityType::BO_PLAS: return spell_RF5_BO_PLAS(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BO_PLAS */
    case MonsterAbilityType::BO_ICEE: return spell_RF5_BO_ICEE(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_BO_ICEE */
    case MonsterAbilityType::MISSILE: return spell_RF5_MISSILE(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF5_MISSILE */
    case MonsterAbilityType::SCARE: return spell_RF5_SCARE(m_idx, player_ptr, 0, MONSTER_TO_PLAYER); /* RF5_SCARE */
    case MonsterAbilityType::BLIND: return spell_RF5_BLIND(m_idx, player_ptr, 0, MONSTER_TO_PLAYER); /* RF5_BLIND */
    case MonsterAbilityType::CONF: return spell_RF5_CONF(m_idx, player_ptr, 0, MONSTER_TO_PLAYER); /* RF5_CONF */
    case MonsterAbilityType::SLOW: return spell_RF5_SLOW(m_idx, player_ptr, 0, MONSTER_TO_PLAYER); /* RF5_SLOW */
    case MonsterAbilityType::HOLD: return spell_RF5_HOLD(m_idx, player_ptr, 0, MONSTER_TO_PLAYER); /* RF5_HOLD */
    case MonsterAbilityType::HASTE: return spell_RF6_HASTE(player_ptr, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_HASTE */
    case MonsterAbilityType::HAND_DOOM: return spell_RF6_HAND_DOOM(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_HAND_DOOM */
    case MonsterAbilityType::HEAL: return spell_RF6_HEAL(player_ptr, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_HEAL */
    case MonsterAbilityType::INVULNER: return spell_RF6_INVULNER(player_ptr, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_INVULNER */
    case MonsterAbilityType::BLINK: return spell_RF6_BLINK(player_ptr, m_idx, MONSTER_TO_PLAYER, false); /* RF6_BLINK */
    case MonsterAbilityType::TPORT: return spell_RF6_TPORT(player_ptr, m_idx, MONSTER_TO_PLAYER); /* RF6_TPORT */
    case MonsterAbilityType::WORLD: return spell_RF6_WORLD(player_ptr, m_idx); /* RF6_WORLD */
    case MonsterAbilityType::SPECIAL: return spell_RF6_SPECIAL(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER);   /* RF6_SPECIAL */
    case MonsterAbilityType::TELE_TO: return spell_RF6_TELE_TO(player_ptr, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_TELE_TO */
    case MonsterAbilityType::TELE_AWAY: return spell_RF6_TELE_AWAY(player_ptr, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_TELE_AWAY */
    case MonsterAbilityType::TELE_LEVEL: return spell_RF6_TELE_LEVEL(player_ptr, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_TELE_LEVEL */
    case MonsterAbilityType::PSY_SPEAR: return spell_RF6_PSY_SPEAR(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_PSY_SPEAR */
    case MonsterAbilityType::DARKNESS: return spell_RF6_DARKNESS(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_DARKNESS */
    case MonsterAbilityType::TRAPS: return spell_RF6_TRAPS(player_ptr, y, x, m_idx); /* RF6_TRAPS */
    case MonsterAbilityType::FORGET: return spell_RF6_FORGET(player_ptr, m_idx); /* RF6_FORGET */
    case MonsterAbilityType::RAISE_DEAD: return spell_RF6_RAISE_DEAD(player_ptr, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_RAISE_DEAD */
    case MonsterAbilityType::S_KIN: return spell_RF6_S_KIN(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_KIN */
    case MonsterAbilityType::S_CYBER: return spell_RF6_S_CYBER(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_CYBER */
    case MonsterAbilityType::S_MONSTER: return spell_RF6_S_MONSTER(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_MONSTER */
    case MonsterAbilityType::S_MONSTERS: return spell_RF6_S_MONSTERS(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_MONSTER */
    case MonsterAbilityType::S_ANT: return spell_RF6_S_ANT(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_ANT */
    case MonsterAbilityType::S_SPIDER: return spell_RF6_S_SPIDER(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_SPIDER */
    case MonsterAbilityType::S_HOUND: return spell_RF6_S_HOUND(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_HOUND */
    case MonsterAbilityType::S_HYDRA: return spell_RF6_S_HYDRA(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_HYDRA */
    case MonsterAbilityType::S_ANGEL: return spell_RF6_S_ANGEL(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_ANGEL */
    case MonsterAbilityType::S_DEMON: return spell_RF6_S_DEMON(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_DEMON */
    case MonsterAbilityType::S_UNDEAD: return spell_RF6_S_UNDEAD(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_UNDEAD */
    case MonsterAbilityType::S_DRAGON: return spell_RF6_S_DRAGON(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_DRAGON */
    case MonsterAbilityType::S_HI_UNDEAD: return spell_RF6_S_HI_UNDEAD(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_HI_UNDEAD */
    case MonsterAbilityType::S_HI_DRAGON: return spell_RF6_S_HI_DRAGON(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_HI_DRAGON */
    case MonsterAbilityType::S_AMBERITES: return spell_RF6_S_AMBERITES(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_AMBERITES */
    case MonsterAbilityType::S_UNIQUE: return spell_RF6_S_UNIQUE(player_ptr, y, x, m_idx, 0, MONSTER_TO_PLAYER); /* RF6_S_UNIQUE */
    default: break;
    }
    // clang-format on

    return MonsterSpellResult::make_invalid();
}

static MonsterSpellResult monspell_to_monster_impl(
    PlayerType *player_ptr, MonsterAbilityType ms_type, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, bool is_special_spell)
{
    // clang-format off
    switch (ms_type) {
    case MonsterAbilityType::SHRIEK: return spell_RF4_SHRIEK(m_idx, player_ptr, t_idx, MONSTER_TO_MONSTER); /* RF4_SHRIEK */
    case MonsterAbilityType::XXX1: break;   /* RF4_XXX1 */
    case MonsterAbilityType::DISPEL: return spell_RF4_DISPEL(m_idx, player_ptr, t_idx, MONSTER_TO_MONSTER); /* RF4_DISPEL */
    case MonsterAbilityType::ROCKET: return spell_RF4_ROCKET(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_ROCKET */
    case MonsterAbilityType::SHOOT: return spell_RF4_SHOOT(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER);  /* RF4_SHOOT */
    case MonsterAbilityType::XXX2: break;   /* RF4_XXX2 */
    case MonsterAbilityType::XXX3: break;   /* RF4_XXX3 */
    case MonsterAbilityType::XXX4: break;   /* RF4_XXX4 */
    case MonsterAbilityType::BR_ACID: return spell_RF4_BREATH(player_ptr, AttributeType::ACID, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BR_ACID */
    case MonsterAbilityType::BR_ELEC: return spell_RF4_BREATH(player_ptr, AttributeType::ELEC, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BR_ELEC */
    case MonsterAbilityType::BR_FIRE: return spell_RF4_BREATH(player_ptr, AttributeType::FIRE, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BR_FIRE */
    case MonsterAbilityType::BR_COLD: return spell_RF4_BREATH(player_ptr, AttributeType::COLD, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BR_COLD */
    case MonsterAbilityType::BR_POIS: return spell_RF4_BREATH(player_ptr, AttributeType::POIS, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BR_POIS */
    case MonsterAbilityType::BR_NETH: return spell_RF4_BREATH(player_ptr, AttributeType::NETHER, y, x, m_idx, t_idx, MONSTER_TO_MONSTER);  /* RF4_BR_NETH */
    case MonsterAbilityType::BR_LITE: return spell_RF4_BREATH(player_ptr, AttributeType::LITE, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BR_LITE */
    case MonsterAbilityType::BR_DARK: return spell_RF4_BREATH(player_ptr, AttributeType::DARK, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BR_DARK */
    case MonsterAbilityType::BR_CONF: return spell_RF4_BREATH(player_ptr, AttributeType::CONFUSION, y, x, m_idx, t_idx, MONSTER_TO_MONSTER);   /* RF4_BR_CONF */
    case MonsterAbilityType::BR_SOUN: return spell_RF4_BREATH(player_ptr, AttributeType::SOUND, y, x, m_idx, t_idx, MONSTER_TO_MONSTER);   /* RF4_BR_SOUN */
    case MonsterAbilityType::BR_CHAO: return spell_RF4_BREATH(player_ptr, AttributeType::CHAOS, y, x, m_idx, t_idx, MONSTER_TO_MONSTER);   /* RF4_BR_CHAO */
    case MonsterAbilityType::BR_DISE: return spell_RF4_BREATH(player_ptr, AttributeType::DISENCHANT, y, x, m_idx, t_idx, MONSTER_TO_MONSTER);  /* RF4_BR_DISE */
    case MonsterAbilityType::BR_NEXU: return spell_RF4_BREATH(player_ptr, AttributeType::NEXUS, y, x, m_idx, t_idx, MONSTER_TO_MONSTER);   /* RF4_BR_NEXU */
    case MonsterAbilityType::BR_TIME: return spell_RF4_BREATH(player_ptr, AttributeType::TIME, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BR_TIME */
    case MonsterAbilityType::BR_INER: return spell_RF4_BREATH(player_ptr, AttributeType::INERTIAL, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BR_INER */
    case MonsterAbilityType::BR_GRAV: return spell_RF4_BREATH(player_ptr, AttributeType::GRAVITY, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BR_GRAV */
    case MonsterAbilityType::BR_SHAR: return spell_RF4_BREATH(player_ptr, AttributeType::SHARDS, y, x, m_idx, t_idx, MONSTER_TO_MONSTER);  /* RF4_BR_SHAR */
    case MonsterAbilityType::BR_PLAS: return spell_RF4_BREATH(player_ptr, AttributeType::PLASMA, y, x, m_idx, t_idx, MONSTER_TO_MONSTER);  /* RF4_BR_PLAS */
    case MonsterAbilityType::BR_FORC: return spell_RF4_BREATH(player_ptr, AttributeType::FORCE, y, x, m_idx, t_idx, MONSTER_TO_MONSTER);   /* RF4_BR_WALL */
    case MonsterAbilityType::BR_MANA: return spell_RF4_BREATH(player_ptr, AttributeType::MANA, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BR_MANA */
    case MonsterAbilityType::BA_NUKE: return spell_RF4_BA_NUKE(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BA_NUKE */
    case MonsterAbilityType::BR_NUKE: return spell_RF4_BREATH(player_ptr, AttributeType::NUKE, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BR_NUKE */
    case MonsterAbilityType::BA_CHAO: return spell_RF4_BA_CHAO(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BA_CHAO */
    case MonsterAbilityType::BR_DISI: return spell_RF4_BREATH(player_ptr, AttributeType::DISINTEGRATE, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF4_BR_DISI */
    case MonsterAbilityType::BA_ACID: return spell_RF5_BA_ACID(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BA_ACID */
    case MonsterAbilityType::BA_ELEC: return spell_RF5_BA_ELEC(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BA_ELEC */
    case MonsterAbilityType::BA_FIRE: return spell_RF5_BA_FIRE(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BA_FIRE */
    case MonsterAbilityType::BA_COLD: return spell_RF5_BA_COLD(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BA_COLD */
    case MonsterAbilityType::BA_POIS: return spell_RF5_BA_POIS(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BA_POIS */
    case MonsterAbilityType::BA_NETH: return spell_RF5_BA_NETH(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BA_NETH */
    case MonsterAbilityType::BA_WATE: return spell_RF5_BA_WATE(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BA_WATE */
    case MonsterAbilityType::BA_MANA: return spell_RF5_BA_MANA(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BA_MANA */
    case MonsterAbilityType::BA_DARK: return spell_RF5_BA_DARK(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BA_DARK */
    case MonsterAbilityType::DRAIN_MANA: return spell_RF5_DRAIN_MANA(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_DRAIN_MANA */
    case MonsterAbilityType::MIND_BLAST: return spell_RF5_MIND_BLAST(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_MIND_BLAST */
    case MonsterAbilityType::BRAIN_SMASH: return spell_RF5_BRAIN_SMASH(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BRAIN_SMASH */
    case MonsterAbilityType::CAUSE_1: return spell_RF5_CAUSE_1(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_CAUSE_1 */
    case MonsterAbilityType::CAUSE_2: return spell_RF5_CAUSE_2(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_CAUSE_2 */
    case MonsterAbilityType::CAUSE_3: return spell_RF5_CAUSE_3(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_CAUSE_3 */
    case MonsterAbilityType::CAUSE_4: return spell_RF5_CAUSE_4(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_CAUSE_4 */
    case MonsterAbilityType::BO_ACID: return spell_RF5_BO_ACID(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BO_ACID */
    case MonsterAbilityType::BO_ELEC: return spell_RF5_BO_ELEC(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BO_ELEC */
    case MonsterAbilityType::BO_FIRE: return spell_RF5_BO_FIRE(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BO_FIRE */
    case MonsterAbilityType::BO_COLD: return spell_RF5_BO_COLD(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BO_COLD */
    case MonsterAbilityType::BA_LITE: return spell_RF5_BA_LITE(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BA_LITE */
    case MonsterAbilityType::BO_NETH: return spell_RF5_BO_NETH(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BO_NETH */
    case MonsterAbilityType::BO_WATE: return spell_RF5_BO_WATE(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BO_WATE */
    case MonsterAbilityType::BO_MANA: return spell_RF5_BO_MANA(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BO_MANA */
    case MonsterAbilityType::BO_PLAS: return spell_RF5_BO_PLAS(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BO_PLAS */
    case MonsterAbilityType::BO_ICEE: return spell_RF5_BO_ICEE(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_BO_ICEE */
    case MonsterAbilityType::MISSILE: return spell_RF5_MISSILE(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF5_MISSILE */
    case MonsterAbilityType::SCARE: return spell_RF5_SCARE(m_idx, player_ptr, t_idx, MONSTER_TO_MONSTER); /* RF5_SCARE */
    case MonsterAbilityType::BLIND: return spell_RF5_BLIND(m_idx, player_ptr, t_idx, MONSTER_TO_MONSTER); /* RF5_BLIND */
    case MonsterAbilityType::CONF: return spell_RF5_CONF(m_idx, player_ptr, t_idx, MONSTER_TO_MONSTER); /* RF5_CONF */
    case MonsterAbilityType::SLOW: return spell_RF5_SLOW(m_idx, player_ptr, t_idx, MONSTER_TO_MONSTER); /* RF5_SLOW */
    case MonsterAbilityType::HOLD: return spell_RF5_HOLD(m_idx, player_ptr, t_idx, MONSTER_TO_MONSTER); /* RF5_HOLD */
    case MonsterAbilityType::HASTE: return spell_RF6_HASTE(player_ptr, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_HASTE */
    case MonsterAbilityType::HAND_DOOM: return spell_RF6_HAND_DOOM(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_HAND_DOOM */
    case MonsterAbilityType::HEAL: return spell_RF6_HEAL(player_ptr, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_HEAL */
    case MonsterAbilityType::INVULNER: return spell_RF6_INVULNER(player_ptr, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_INVULNER */
    case MonsterAbilityType::BLINK: return spell_RF6_BLINK(player_ptr, m_idx, MONSTER_TO_MONSTER, is_special_spell); /* RF6_BLINK */
    case MonsterAbilityType::TPORT: return spell_RF6_TPORT(player_ptr, m_idx, MONSTER_TO_MONSTER); /* RF6_TPORT */
    case MonsterAbilityType::WORLD: break; /* RF6_WORLD */
    case MonsterAbilityType::SPECIAL: return spell_RF6_SPECIAL(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER);   /* RF6_SPECIAL */
    case MonsterAbilityType::TELE_TO: return spell_RF6_TELE_TO(player_ptr, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_TELE_TO */
    case MonsterAbilityType::TELE_AWAY: return spell_RF6_TELE_AWAY(player_ptr, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_TELE_AWAY */
    case MonsterAbilityType::TELE_LEVEL: return spell_RF6_TELE_LEVEL(player_ptr, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_TELE_LEVEL */
    case MonsterAbilityType::PSY_SPEAR: return spell_RF6_PSY_SPEAR(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_PSY_SPEAR */
    case MonsterAbilityType::DARKNESS: return spell_RF6_DARKNESS(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_DARKNESS */
    case MonsterAbilityType::TRAPS: break; /* RF6_TRAPS */
    case MonsterAbilityType::FORGET: break; /* RF6_FORGET */
    case MonsterAbilityType::RAISE_DEAD: return spell_RF6_RAISE_DEAD(player_ptr, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_RAISE_DEAD */
    case MonsterAbilityType::S_KIN: return spell_RF6_S_KIN(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_KIN */
    case MonsterAbilityType::S_CYBER: return spell_RF6_S_CYBER(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_CYBER */
    case MonsterAbilityType::S_MONSTER: return spell_RF6_S_MONSTER(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_MONSTER */
    case MonsterAbilityType::S_MONSTERS: return spell_RF6_S_MONSTERS(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_MONSTER */
    case MonsterAbilityType::S_ANT: return spell_RF6_S_ANT(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_ANT */
    case MonsterAbilityType::S_SPIDER: return spell_RF6_S_SPIDER(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_SPIDER */
    case MonsterAbilityType::S_HOUND: return spell_RF6_S_HOUND(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_HOUND */
    case MonsterAbilityType::S_HYDRA: return spell_RF6_S_HYDRA(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_HYDRA */
    case MonsterAbilityType::S_ANGEL: return spell_RF6_S_ANGEL(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_ANGEL */
    case MonsterAbilityType::S_DEMON: return spell_RF6_S_DEMON(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_DEMON */
    case MonsterAbilityType::S_UNDEAD: return spell_RF6_S_UNDEAD(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_UNDEAD */
    case MonsterAbilityType::S_DRAGON: return spell_RF6_S_DRAGON(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_DRAGON */
    case MonsterAbilityType::S_HI_UNDEAD: return spell_RF6_S_HI_UNDEAD(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_HI_UNDEAD */
    case MonsterAbilityType::S_HI_DRAGON: return spell_RF6_S_HI_DRAGON(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_HI_DRAGON */
    case MonsterAbilityType::S_AMBERITES: return spell_RF6_S_AMBERITES(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_AMBERITES */
    case MonsterAbilityType::S_UNIQUE: return spell_RF6_S_UNIQUE(player_ptr, y, x, m_idx, t_idx, MONSTER_TO_MONSTER); /* RF6_S_UNIQUE */
    default: break;
    }
    // clang-format on

    return MonsterSpellResult::make_invalid();
}

/*!
 * @brief モンスターからプレイヤーへの魔法使用。ラーニング処理も行う。
 * @param ms_type モンスター魔法ID (monster_spell_typeのenum値とは異なる)
 * @param y 対象の地点のy座標
 * @param x 対象の地点のx座標
 * @param m_idx 呪文を唱えるモンスターID
 */
MonsterSpellResult monspell_to_player(PlayerType *player_ptr, MonsterAbilityType ms_type, POSITION y, POSITION x, MONSTER_IDX m_idx)
{
    // 特技使用前の時点でプレイヤーがモンスターを視認できているかチェック(ラーニングの必要条件)。
    const bool player_could_see_monster = spell_learnable(player_ptr, m_idx);

    auto res = monspell_to_player_impl(player_ptr, ms_type, y, x, m_idx);
    if (!player_could_see_monster)
        res.learnable = false;

    // 条件を満たしていればラーニングを試みる。
    if (res.valid && res.learnable) {
        learn_spell(player_ptr, ms_type);
    }

    return res;
}

/*!
 * @brief モンスターからモンスターへの魔法使用。ラーニング処理も行う。
 * @param player_ptr プレイヤーへの参照ポインタ (monster_spell_typeのenum値とは異なる)
 * @param ms_type モンスター魔法ID
 * @param y 対象の地点のy座標
 * @param x 対象の地点のx座標
 * @param m_idx 呪文を唱えるモンスターID
 * @param t_idx 呪文を受けるモンスターID。プレイヤーの場合はdummyで0とする。
 * @param is_special_spell 特殊な行動である時TRUE
 * @todo モンスターからモンスターへの呪文なのにPlayerTypeが引数になり得るのは間違っている……
 */
MonsterSpellResult monspell_to_monster(
    PlayerType *player_ptr, MonsterAbilityType ms_type, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, bool is_special_spell)
{
    // 特技使用前の時点でプレイヤーがモンスターを視認できているかチェック(ラーニングの必要条件)。
    const bool player_could_see_monster = spell_learnable(player_ptr, m_idx);

    auto res = monspell_to_monster_impl(player_ptr, ms_type, y, x, m_idx, t_idx, is_special_spell);
    if (!player_could_see_monster)
        res.learnable = false;

    // 条件を満たしていればラーニングを試みる。
    if (res.valid && res.learnable) {
        learn_spell(player_ptr, ms_type);
    }

    return res;
}
