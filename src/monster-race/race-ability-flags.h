﻿#pragma once

enum class MonsterAbilityType {
    SHRIEK = 0, /*!< モンスター能力: 叫ぶ / Shriek for help */
    XXX1 = 1, /*!< モンスター能力: 未使用 / XXX */
    DISPEL = 2, /*!< モンスター能力: 魔力消去 / Dispel magic */
    ROCKET = 3, /*!< モンスター能力: ロケット / TY: Rocket */
    SHOOT = 4, /*!< モンスター能力: 射撃/ Fire missiles */
    XXX2 = 5, /*!< モンスター能力: 未使用 / XXX */
    XXX3 = 6, /*!< モンスター能力: 未使用 / XXX */
    XXX4 = 7, /*!< モンスター能力: 未使用 / XXX */
    BR_ACID = 8, /*!< モンスター能力: 酸のブレス / Breathe Acid */
    BR_ELEC = 9, /*!< モンスター能力: 電撃のブレス / Breathe Elec */
    BR_FIRE = 10, /*!< モンスター能力: 火炎のブレス / Breathe Fire */
    BR_COLD = 11, /*!< モンスター能力: 冷気のブレス / Breathe Cold */
    BR_POIS = 12, /*!< モンスター能力: 毒のブレス / Breathe Poison */
    BR_NETH = 13, /*!< モンスター能力: 地獄のブレス / Breathe Nether */
    BR_LITE = 14, /*!< モンスター能力: 閃光のブレス / Breathe Lite */
    BR_DARK = 15, /*!< モンスター能力: 暗黒のブレス / Breathe Dark */
    BR_CONF = 16, /*!< モンスター能力: 混乱のブレス / Breathe Confusion */
    BR_SOUN = 17, /*!< モンスター能力: 轟音のブレス / Breathe Sound */
    BR_CHAO = 18, /*!< モンスター能力: カオスのブレス / Breathe Chaos */
    BR_DISE = 19, /*!< モンスター能力: 劣化のブレス / Breathe Disenchant */
    BR_NEXU = 20, /*!< モンスター能力: 因果混乱のブレス / Breathe Nexus */
    BR_TIME = 21, /*!< モンスター能力: 時間逆転のブレス / Breathe Time */
    BR_INER = 22, /*!< モンスター能力: 遅鈍のブレス / Breathe Inertia */
    BR_GRAV = 23, /*!< モンスター能力: 重力のブレス / Breathe Gravity */
    BR_SHAR = 24, /*!< モンスター能力: 破片のブレス / Breathe Shards */
    BR_PLAS = 25, /*!< モンスター能力: プラズマのブレス / Breathe Plasma */
    BR_FORC = 26, /*!< モンスター能力: フォースのブレス / Breathe Force */
    BR_MANA = 27, /*!< モンスター能力: 魔力のブレス / Breathe Mana */
    BA_NUKE = 28, /*!< モンスター能力: 放射能球 / TY: Nuke Ball */
    BR_NUKE = 29, /*!< モンスター能力: 放射性廃棄物のブレス / TY: Toxic Breath */
    BA_CHAO = 30, /*!< モンスター能力: ログルス球 / TY: Logrus Ball */
    BR_DISI = 31, /*!< モンスター能力: 分解のブレス / Breathe Disintegration */

    BA_ACID = 32, /*!< モンスター能力: アシッド・ボール / Acid Ball */
    BA_ELEC = 33, /*!< モンスター能力: サンダー・ボール / Elec Ball */
    BA_FIRE = 34, /*!< モンスター能力: ファイア・ボール / Fire Ball */
    BA_COLD = 35, /*!< モンスター能力: アイス・ボール / Cold Ball */
    BA_POIS = 36, /*!< モンスター能力: 悪臭雲 / Poison Ball */
    BA_NETH = 37, /*!< モンスター能力: 地獄球 / Nether Ball */
    BA_WATE = 38, /*!< モンスター能力: ウォーター・ボール / Water Ball */
    BA_MANA = 39, /*!< モンスター能力: 魔力の嵐 / Mana Storm */
    BA_DARK = 40, /*!< モンスター能力: 暗黒の嵐 / Darkness Storm */
    DRAIN_MANA = 41, /*!< モンスター能力: 魔力吸収 / Drain Mana */
    MIND_BLAST = 42, /*!< モンスター能力: 精神攻撃 / Blast Mind */
    BRAIN_SMASH = 43, /*!< モンスター能力: 脳攻撃 / Smash Brain */
    CAUSE_1 = 44, /*!< モンスター能力: 軽傷の呪い / Cause Light Wound */
    CAUSE_2 = 45, /*!< モンスター能力: 重症の頃い / Cause Serious Wound */
    CAUSE_3 = 46, /*!< モンスター能力: 致命傷の呪い / Cause Critical Wound */
    CAUSE_4 = 47, /*!< モンスター能力: 秘孔を突く / Cause Mortal Wound */
    BO_ACID = 48, /*!< モンスター能力: アシッド・ボルト / Acid Bolt */
    BO_ELEC = 49, /*!< モンスター能力: サンダー・ボルト / Elec Bolt */
    BO_FIRE = 50, /*!< モンスター能力: ファイア・ボルト / Fire Bolt */
    BO_COLD = 51, /*!< モンスター能力: アイス・ボルト / Cold Bolt */
    BA_LITE = 52, /*!< モンスター能力: スター・バースト / StarBurst */
    BO_NETH = 53, /*!< モンスター能力: 地獄の矢 / Nether Bolt */
    BO_WATE = 54, /*!< モンスター能力: ウォーター・ボルト / Water Bolt */
    BO_MANA = 55, /*!< モンスター能力: 魔力の矢 / Mana Bolt */
    BO_PLAS = 56, /*!< モンスター能力: プラズマ・ボルト / Plasma Bolt */
    BO_ICEE = 57, /*!< モンスター能力: 極寒の矢 / Ice Bolt */
    MISSILE = 58, /*!< モンスター能力: マジック・ミサイルt / Magic Missile */
    SCARE = 59, /*!< モンスター能力: 恐慌 / Frighten Player */
    BLIND = 60, /*!< モンスター能力: 盲目 / Blind Player */
    CONF = 61, /*!< モンスター能力: 混乱 / Confuse Player */
    SLOW = 62, /*!< モンスター能力: 減速 / Slow Player */
    HOLD = 63, /*!< モンスター能力: 麻痺 / Paralyze Player */

    HASTE = 64, /* Speed self */
    HAND_DOOM = 65, /* Hand of Doom */
    HEAL = 66, /* Heal self */
    INVULNER = 67, /* INVULNERABILITY! */
    BLINK = 68, /* Teleport Short */
    TPORT = 69, /* Teleport Long */
    WORLD = 70, /* world */
    SPECIAL = 71, /* Special Attack */
    TELE_TO = 72, /* Move player to monster */
    TELE_AWAY = 73, /* Move player far away */
    TELE_LEVEL = 74, /* Move player vertically */
    PSY_SPEAR = 75, /* Psyco-spear */
    DARKNESS = 76, /* Create Darkness */
    TRAPS = 77, /* Create Traps */
    FORGET = 78, /* Cause amnesia */
    RAISE_DEAD = 79, /* Raise Dead */
    S_KIN = 80, /* Summon "kin" */
    S_CYBER = 81, /* Summon Cyberdemons! */
    S_MONSTER = 82, /* Summon Monster */
    S_MONSTERS = 83, /* Summon Monsters */
    S_ANT = 84, /* Summon Ants */
    S_SPIDER = 85, /* Summon Spiders */
    S_HOUND = 86, /* Summon Hounds */
    S_HYDRA = 87, /* Summon Hydras */
    S_ANGEL = 88, /* Summon Angel */
    S_DEMON = 89, /* Summon Demon */
    S_UNDEAD = 90, /* Summon Undead */
    S_DRAGON = 91, /* Summon Dragon */
    S_HI_UNDEAD = 92, /* Summon Greater Undead */
    S_HI_DRAGON = 93, /* Summon Ancient Dragon */
    S_AMBERITES = 94, /* Summon Amberites */
    S_UNIQUE = 95, /* Summon Unique Monster */
    MAX,
};
