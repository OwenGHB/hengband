/* File: wizard1.c */

/* Purpose: Spoiler generation -BEN- */

#include "angband.h"


#ifdef ALLOW_SPOILERS


/*
 * The spoiler file being created
 */
static FILE *fff = NULL;



/*
 * Extract a textual representation of an attribute
 */
static cptr attr_to_text(byte a)
{
	switch (a)
	{
#ifdef JP000
case TERM_DARK:    return ("XXXい");
case TERM_WHITE:   return ("白い");
case TERM_SLATE:   return ("青灰色の");
case TERM_ORANGE:  return ("オレンジの");
case TERM_RED:     return ("赤い");
case TERM_GREEN:   return ("緑の");
case TERM_BLUE:    return ("青い");
case TERM_UMBER:   return ("琥珀色の");
case TERM_L_DARK:  return ("灰色の");
case TERM_L_WHITE: return ("明青灰色の");
case TERM_VIOLET:  return ("紫の");
case TERM_YELLOW:  return ("黄色い");
case TERM_L_RED:   return ("明い赤の");
case TERM_L_GREEN: return ("明い緑の");
case TERM_L_BLUE:  return ("明い青の");
case TERM_L_UMBER: return ("明い琥珀色の");
#else
		case TERM_DARK:    return ("xxx");
		case TERM_WHITE:   return ("White");
		case TERM_SLATE:   return ("Slate");
		case TERM_ORANGE:  return ("Orange");
		case TERM_RED:     return ("Red");
		case TERM_GREEN:   return ("Green");
		case TERM_BLUE:    return ("Blue");
		case TERM_UMBER:   return ("Umber");
		case TERM_L_DARK:  return ("L.Dark");
		case TERM_L_WHITE: return ("L.Slate");
		case TERM_VIOLET:  return ("Violet");
		case TERM_YELLOW:  return ("Yellow");
		case TERM_L_RED:   return ("L.Red");
		case TERM_L_GREEN: return ("L.Green");
		case TERM_L_BLUE:  return ("L.Blue");
		case TERM_L_UMBER: return ("L.Umber");
#endif

	}

	/* Oops */
#ifdef JP000
return ("変な");
#else
	return ("Icky");
#endif

}



/*
 * A tval grouper
 */
typedef struct
{
	byte tval;
	cptr name;
} grouper;



/*
 * Item Spoilers by: benh@phial.com (Ben Harrison)
 */


/*
 * The basic items categorized by type
 */
static grouper group_item[] =
{
#ifdef JP
{ TV_SHOT,          "射撃物" },
#else
	{ TV_SHOT,          "Ammo" },
#endif

	{ TV_ARROW,         NULL },
	{ TV_BOLT,          NULL },

#ifdef JP
{ TV_BOW,           "弓" },
#else
	{ TV_BOW,           "Bows" },
#endif


#ifdef JP
{ TV_SWORD,         "武器" },
#else
	{ TV_SWORD,         "Weapons" },
#endif

	{ TV_POLEARM,       NULL },
	{ TV_HAFTED,        NULL },
	{ TV_DIGGING,       NULL },

#ifdef JP
{ TV_SOFT_ARMOR,    "防具（体）" },
#else
	{ TV_SOFT_ARMOR,    "Armour (Body)" },
#endif

	{ TV_HARD_ARMOR,    NULL },
	{ TV_DRAG_ARMOR,    NULL },

#ifdef JP
{ TV_CLOAK,         "防具（その他）" },
#else
	{ TV_CLOAK,         "Armour (Misc)" },
#endif

	{ TV_SHIELD,        NULL },
	{ TV_HELM,          NULL },
	{ TV_CROWN,         NULL },
	{ TV_GLOVES,        NULL },
	{ TV_BOOTS,         NULL },

#ifdef JP
{ TV_AMULET,        "アミュレット" },
{ TV_RING,          "指輪" },
#else
	{ TV_AMULET,        "Amulets" },
	{ TV_RING,          "Rings" },
#endif


#ifdef JP
{ TV_SCROLL,        "巻物" },
{ TV_POTION,        "薬" },
{ TV_FOOD,          "食料" },
#else
	{ TV_SCROLL,        "Scrolls" },
	{ TV_POTION,        "Potions" },
	{ TV_FOOD,          "Food" },
#endif


#ifdef JP
{ TV_ROD,           "ロッド" },
{ TV_WAND,          "魔法棒" },
{ TV_STAFF,         "杖" },
#else
	{ TV_ROD,           "Rods" },
	{ TV_WAND,          "Wands" },
	{ TV_STAFF,         "Staffs" },
#endif


#ifdef JP
{ TV_LIFE_BOOK,     "魔法書（生命）" },
{ TV_SORCERY_BOOK,  "魔法書（仙術）" },
{ TV_NATURE_BOOK,   "魔法書（自然）" },
{ TV_CHAOS_BOOK,    "魔法書（カオス）" },
{ TV_DEATH_BOOK,    "魔法書（暗黒）" },
{ TV_TRUMP_BOOK,    "魔法書（トランプ）" },
{ TV_ARCANE_BOOK,   "魔法書（秘術）" },
{ TV_ENCHANT_BOOK,  "魔法書（匠）" },
{ TV_DAEMON_BOOK,   "魔法書（悪魔）" },
{ TV_MUSIC_BOOK,    "歌集" },
{ TV_HISSATSU_BOOK, "武芸の書" },
#else
	{ TV_LIFE_BOOK,     "Books (Life)" },
	{ TV_SORCERY_BOOK,  "Books (Sorcery)" },
	{ TV_NATURE_BOOK,   "Books (Nature)" },
	{ TV_CHAOS_BOOK,    "Books (Chaos)" },
	{ TV_DEATH_BOOK,    "Books (Death)" },
	{ TV_TRUMP_BOOK,    "Books (Trump)" },
	{ TV_ARCANE_BOOK,   "Books (Arcane)" },
	{ TV_ENCHANT_BOOK,  "Books (Craft)" },
	{ TV_DAEMON_BOOK,   "Books (Daemon)" },
	{ TV_MUSIC_BOOK,    "Song Books" },
	{ TV_HISSATSU_BOOK, "Books (Kendo)" },
#endif

#ifdef JP
{ TV_PARCHEMENT,    "羊皮紙" },
#else
{ TV_PARCHEMENT,    "Parchement" },
#endif

#ifdef JP
{ TV_CHEST,         "箱" },
#else
	{ TV_CHEST,         "Chests" },
#endif

#ifdef JP
{ TV_CAPTURE,         "キャプチャー・ボール" },
#else
	{ TV_CAPTURE,         "Capture Ball" },
#endif

#ifdef JP
{ TV_CARD,         "エクスプレスカード" },
#else
	{ TV_CARD,         "Express Card" },
#endif

	{ TV_FIGURINE,      "Magical Figurines" },
	{ TV_STATUE,        "Statues" },
	{ TV_CORPSE,        "Corpses" },

#ifdef JP
{ TV_WHISTLE,         "笛" },
#else
	{ TV_WHISTLE,         "Whistle" },
#endif

#ifdef JP
{ TV_SPIKE,         "くさび" },
#else
	{ TV_SPIKE,         "Spike" },
#endif

	{ TV_LITE,          NULL },
	{ TV_FLASK,         NULL },
	{ TV_JUNK,          NULL },
	{ TV_BOTTLE,        NULL },
	{ TV_SKELETON,      NULL },

	{ 0, "" }
};


/*
 * Describe the kind
 */
static void kind_info(char *buf, char *dam, char *wgt, int *lev, s32b *val, int k)
{
	object_type forge;
	object_type *q_ptr;


	/* Get local object */
	q_ptr = &forge;

	/* Prepare a fake item */
	object_prep(q_ptr, k);

	/* It is known */
	q_ptr->ident |= (IDENT_KNOWN);

	/* Cancel bonuses */
	q_ptr->pval = 0;
	q_ptr->to_a = 0;
	q_ptr->to_h = 0;
	q_ptr->to_d = 0;


	/* Level */
	(*lev) = get_object_level(q_ptr);

	/* Value */
	(*val) = object_value(q_ptr);


	/* Hack */
	if (!buf || !dam || !wgt) return;


	/* Description (too brief) */
	object_desc_store(buf, q_ptr, FALSE, 0);


	/* Misc info */
	strcpy(dam, "");

	/* Damage */
	switch (q_ptr->tval)
	{
		/* Bows */
		case TV_BOW:
		{
			break;
		}

		/* Ammo */
		case TV_SHOT:
		case TV_BOLT:
		case TV_ARROW:
		{
			sprintf(dam, "%dd%d", q_ptr->dd, q_ptr->ds);
			break;
		}

		/* Weapons */
		case TV_HAFTED:
		case TV_POLEARM:
		case TV_SWORD:
		case TV_DIGGING:
		{
			sprintf(dam, "%dd%d", q_ptr->dd, q_ptr->ds);
			break;
		}

		/* Armour */
		case TV_BOOTS:
		case TV_GLOVES:
		case TV_CLOAK:
		case TV_CROWN:
		case TV_HELM:
		case TV_SHIELD:
		case TV_SOFT_ARMOR:
		case TV_HARD_ARMOR:
		case TV_DRAG_ARMOR:
		{
			sprintf(dam, "%d", q_ptr->ac);
			break;
		}
	}


	/* Weight */
	sprintf(wgt, "%3d.%d", q_ptr->weight / 10, q_ptr->weight % 10);
}


/*
 * Create a spoiler file for items
 */
static void spoil_obj_desc(cptr fname)
{
	int i, k, s, t, n = 0;

	u16b who[200];

	char buf[1024];

	char wgt[80];
	char dam[80];


	/* Build the filename */
	path_build(buf, 1024, ANGBAND_DIR_USER, fname);

	/* File type is "TEXT" */
	FILE_TYPE(FILE_TYPE_TEXT);

	/* Open the file */
	fff = my_fopen(buf, "w");

	/* Oops */
	if (!fff)
	{
		msg_print("Cannot create spoiler file.");
		return;
	}


	/* Header */
	fprintf(fff, "Spoiler File -- Basic Items (Hengband %d.%d.%d)\n\n\n",
		FAKE_VER_MAJOR-10, FAKE_VER_MINOR, FAKE_VER_PATCH);

	/* More Header */
	fprintf(fff, "%-45s     %8s%7s%5s%9s\n",
		"Description", "Dam/AC", "Wgt", "Lev", "Cost");
	fprintf(fff, "%-45s     %8s%7s%5s%9s\n",
		"----------------------------------------",
		"------", "---", "---", "----");

	/* List the groups */
	for (i = 0; TRUE; i++)
	{
		/* Write out the group title */
		if (group_item[i].name)
		{
			/* Hack -- bubble-sort by cost and then level */
			for (s = 0; s < n - 1; s++)
			{
				for (t = 0; t < n - 1; t++)
				{
					int i1 = t;
					int i2 = t + 1;

					int e1;
					int e2;

					s32b t1;
					s32b t2;

					kind_info(NULL, NULL, NULL, &e1, &t1, who[i1]);
					kind_info(NULL, NULL, NULL, &e2, &t2, who[i2]);

					if ((t1 > t2) || ((t1 == t2) && (e1 > e2)))
					{
						int tmp = who[i1];
						who[i1] = who[i2];
						who[i2] = tmp;
					}
				}
			}

			/* Spoil each item */
			for (s = 0; s < n; s++)
			{
				int e;
				s32b v;

				/* Describe the kind */
				kind_info(buf, dam, wgt, &e, &v, who[s]);

				/* Dump it */
				fprintf(fff, "     %-45s%8s%7s%5d%9ld\n",
					buf, dam, wgt, e, (long)(v));
			}

			/* Start a new set */
			n = 0;

			/* Notice the end */
			if (!group_item[i].tval) break;

			/* Start a new set */
			fprintf(fff, "\n\n%s\n\n", group_item[i].name);
		}

		/* Acquire legal item types */
		for (k = 1; k < max_k_idx; k++)
		{
			object_kind *k_ptr = &k_info[k];

			/* Skip wrong tval's */
			if (k_ptr->tval != group_item[i].tval) continue;

			/* Hack -- Skip instant-artifacts */
			if (k_ptr->gen_flags & (TRG_INSTA_ART)) continue;

			/* Save the index */
			who[n++] = k;
		}
	}


	/* Check for errors */
	if (ferror(fff) || my_fclose(fff))
	{
		msg_print("Cannot close spoiler file.");
		return;
	}

	/* Message */
	msg_print("Successfully created a spoiler file.");
}


/*
 * Artifact Spoilers by: randy@PICARD.tamu.edu (Randy Hutson)
 */


/*
 * Returns a "+" string if a number is non-negative and an empty
 * string if negative
 */
#define POSITIZE(v) (((v) >= 0) ? "+" : "")

/*
 * These are used to format the artifact spoiler file. INDENT1 is used
 * to indent all but the first line of an artifact spoiler. INDENT2 is
 * used when a line "wraps". (Bladeturner's resistances cause this.)
 */
#define INDENT1 "    "
#define INDENT2 "      "

/*
 * MAX_LINE_LEN specifies when a line should wrap.
 */
#define MAX_LINE_LEN 75

/*
 * Given an array, determine how many elements are in the array
 */
#define N_ELEMENTS(a) (sizeof (a) / sizeof ((a)[0]))

/*
 * The artifacts categorized by type
 */
static grouper group_artifact[] =
{
#ifdef JP
	{ TV_SWORD,             "刀剣" },
	{ TV_POLEARM,           "槍/斧" },
	{ TV_HAFTED,            "鈍器" },
	{ TV_DIGGING,           "シャベル/つるはし" },
	{ TV_BOW,               "飛び道具" },
	{ TV_ARROW,             "矢" },

	{ TV_SOFT_ARMOR,        "鎧" },
	{ TV_HARD_ARMOR,        NULL },
	{ TV_DRAG_ARMOR,        NULL },

	{ TV_CLOAK,             "クローク" },
	{ TV_SHIELD,            "盾" },
	{ TV_CARD,              NULL },
	{ TV_HELM,              "兜/冠" },
	{ TV_CROWN,             NULL },
	{ TV_GLOVES,            "籠手" },
	{ TV_BOOTS,             "靴" },

	{ TV_LITE,              "光源" },
	{ TV_AMULET,            "アミュレット" },
	{ TV_RING,              "指輪" },
#else
	{ TV_SWORD,             "Edged Weapons" },
	{ TV_POLEARM,           "Polearms" },
	{ TV_HAFTED,            "Hafted Weapons" },
	{ TV_DIGGING,           "Shovels/Picks" },
	{ TV_BOW,               "Bows" },
	{ TV_ARROW,             "Ammo" },

	{ TV_SOFT_ARMOR,        "Body Armor" },
	{ TV_HARD_ARMOR,        NULL },
	{ TV_DRAG_ARMOR,        NULL },

	{ TV_CLOAK,             "Cloaks" },
	{ TV_SHIELD,            "Shields" },
	{ TV_CARD,              NULL },
	{ TV_HELM,              "Helms/Crowns" },
	{ TV_CROWN,             NULL },
	{ TV_GLOVES,            "Gloves" },
	{ TV_BOOTS,             "Boots" },

	{ TV_LITE,              "Light Sources" },
	{ TV_AMULET,            "Amulets" },
	{ TV_RING,              "Rings" },
#endif

	{ 0, NULL }
};



/*
 * Pair together a constant flag with a textual description.
 *
 * Used by both "init.c" and "wiz-spo.c".
 *
 * Note that it sometimes more efficient to actually make an array
 * of textual names, where entry 'N' is assumed to be paired with
 * the flag whose value is "1L << N", but that requires hard-coding.
 */

typedef struct flag_desc flag_desc;

struct flag_desc
{
	const u32b flag;
	const char *const desc;
};



/*
 * These are used for "+3 to STR, DEX", etc. These are separate from
 * the other pval affected traits to simplify the case where an object
 * affects all stats.  In this case, "All stats" is used instead of
 * listing each stat individually.
 */

static flag_desc stat_flags_desc[] =
{
#ifdef JP
	{ TR1_STR,        "腕力" },
	{ TR1_INT,        "知能" },
	{ TR1_WIS,        "賢さ" },
	{ TR1_DEX,        "器用さ" },
	{ TR1_CON,        "耐久力" },
	{ TR1_CHR,        "魅力" }
#else
	{ TR1_STR,        "STR" },
	{ TR1_INT,        "INT" },
	{ TR1_WIS,        "WIS" },
	{ TR1_DEX,        "DEX" },
	{ TR1_CON,        "CON" },
	{ TR1_CHR,        "CHR" }
#endif
};

/*
 * Besides stats, these are the other player traits
 * which may be affected by an object's pval
 */

static flag_desc pval_flags1_desc[] =
{
#ifdef JP
	{ TR1_MAGIC_MASTERY,    "魔法道具使用能力" },
	{ TR1_STEALTH,    "隠密" },
	{ TR1_SEARCH,     "探索" },
	{ TR1_INFRA,      "赤外線視力" },
	{ TR1_TUNNEL,     "採掘" },
	{ TR1_BLOWS,      "攻撃回数" },
	{ TR1_SPEED,      "スピード" }
#else
	{ TR1_STEALTH,    "Stealth" },
	{ TR1_SEARCH,     "Searching" },
	{ TR1_INFRA,      "Infravision" },
	{ TR1_TUNNEL,     "Tunneling" },
	{ TR1_BLOWS,      "Attacks" },
	{ TR1_SPEED,      "Speed" }
#endif
};

/*
 * Slaying preferences for weapons
 */

static flag_desc slay_flags_desc[] =
{
#ifdef JP
	{ TR1_SLAY_ANIMAL,        "動物" },
	{ TR1_SLAY_EVIL,          "邪悪" },
	{ TR3_SLAY_HUMAN,         "人間" },
	{ TR1_SLAY_UNDEAD,        "アンデッド" },
	{ TR1_SLAY_DEMON,         "悪魔" },
	{ TR1_SLAY_ORC,           "オーク" },
	{ TR1_SLAY_TROLL,         "トロル" },
	{ TR1_SLAY_GIANT,         "巨人" },
	{ TR1_SLAY_DRAGON,        "ドラゴン" },
	{ TR1_KILL_DRAGON,        "*ドラゴン*" },
#else
	{ TR1_SLAY_ANIMAL,        "Animal" },
	{ TR1_SLAY_EVIL,          "Evil" },
	{ TR3_SLAY_HUMAN,         "Human" },
	{ TR1_SLAY_UNDEAD,        "Undead" },
	{ TR1_SLAY_DEMON,         "Demon" },
	{ TR1_SLAY_ORC,           "Orc" },
	{ TR1_SLAY_TROLL,         "Troll" },
	{ TR1_SLAY_GIANT,         "Giant" },
	{ TR1_SLAY_DRAGON,        "Dragon" },
	{ TR1_KILL_DRAGON,        "Xdragon" }
#endif
};

/*
 * Elemental brands for weapons
 *
 * Clearly, TR1_IMPACT is a bit out of place here. To simplify
 * coding, it has been included here along with the elemental
 * brands. It does seem to fit in with the brands and slaying
 * more than the miscellaneous section.
 */
static flag_desc brand_flags_desc[] =
{
#ifdef JP
	{ TR1_BRAND_ACID,         "溶解" },
	{ TR1_BRAND_ELEC,         "電撃" },
	{ TR1_BRAND_FIRE,         "焼棄" },
	{ TR1_BRAND_COLD,         "凍結" },
	{ TR1_BRAND_POIS,         "毒殺" },

	{ TR1_FORCE_WEAPON,       "理力" },
	{ TR1_CHAOTIC,            "混沌" },
	{ TR1_VAMPIRIC,           "吸血" },
	{ TR1_IMPACT,             "地震" },
	{ TR1_VORPAL,             "切れ味" },
#else
	{ TR1_BRAND_ACID,         "Acid Brand" },
	{ TR1_BRAND_ELEC,         "Lightning Brand" },
	{ TR1_BRAND_FIRE,         "Flame Tongue" },
	{ TR1_BRAND_COLD,         "Frost Brand" },
	{ TR1_BRAND_POIS,         "Poisoned" },

	{ TR1_FORCE_WEAPON,       "Force" },
	{ TR1_CHAOTIC,            "Mark of Chaos" },
	{ TR1_VAMPIRIC,           "Vampiric" },
	{ TR1_IMPACT,             "Earthquake impact on hit" },
	{ TR1_VORPAL,             "Very sharp" },
#endif
};


/*
 * The 15 resistables
 */
static const flag_desc resist_flags_desc[] =
{
#ifdef JP
	{ TR2_RES_ACID,   "酸" },
	{ TR2_RES_ELEC,   "電撃" },
	{ TR2_RES_FIRE,   "火炎" },
	{ TR2_RES_COLD,   "冷気" },
	{ TR2_RES_POIS,   "毒" },
	{ TR2_RES_FEAR,   "恐怖"},
	{ TR2_RES_LITE,   "閃光" },
	{ TR2_RES_DARK,   "暗黒" },
	{ TR2_RES_BLIND,  "盲目" },
	{ TR2_RES_CONF,   "混乱" },
	{ TR2_RES_SOUND,  "轟音" },
	{ TR2_RES_SHARDS, "破片" },
	{ TR2_RES_NETHER, "地獄" },
	{ TR2_RES_NEXUS,  "因果混乱" },
	{ TR2_RES_CHAOS,  "カオス" },
	{ TR2_RES_DISEN,  "劣化" },
#else
	{ TR2_RES_ACID,   "Acid" },
	{ TR2_RES_ELEC,   "Lightning" },
	{ TR2_RES_FIRE,   "Fire" },
	{ TR2_RES_COLD,   "Cold" },
	{ TR2_RES_POIS,   "Poison" },
	{ TR2_RES_FEAR,   "Fear"},
	{ TR2_RES_LITE,   "Light" },
	{ TR2_RES_DARK,   "Dark" },
	{ TR2_RES_BLIND,  "Blindness" },
	{ TR2_RES_CONF,   "Confusion" },
	{ TR2_RES_SOUND,  "Sound" },
	{ TR2_RES_SHARDS, "Shards" },
	{ TR2_RES_NETHER, "Nether" },
	{ TR2_RES_NEXUS,  "Nexus" },
	{ TR2_RES_CHAOS,  "Chaos" },
	{ TR2_RES_DISEN,  "Disenchantment" },
#endif
};

/*
 * Elemental immunities (along with poison)
 */

static const flag_desc immune_flags_desc[] =
{
#ifdef JP
	{ TR2_IM_ACID,    "酸" },
	{ TR2_IM_ELEC,    "電撃" },
	{ TR2_IM_FIRE,    "火炎" },
	{ TR2_IM_COLD,    "冷気" },
#else
	{ TR2_IM_ACID,    "Acid" },
	{ TR2_IM_ELEC,    "Lightning" },
	{ TR2_IM_FIRE,    "Fire" },
	{ TR2_IM_COLD,    "Cold" },
#endif
};

/*
 * Sustain stats -  these are given their "own" line in the
 * spoiler file, mainly for simplicity
 */
static const flag_desc sustain_flags_desc[] =
{
#ifdef JP
	{ TR2_SUST_STR,   "腕力" },
	{ TR2_SUST_INT,   "知能" },
	{ TR2_SUST_WIS,   "賢さ" },
	{ TR2_SUST_DEX,   "器用さ" },
	{ TR2_SUST_CON,   "耐久力" },
	{ TR2_SUST_CHR,   "魅力" },
#else
	{ TR2_SUST_STR,   "STR" },
	{ TR2_SUST_INT,   "INT" },
	{ TR2_SUST_WIS,   "WIS" },
	{ TR2_SUST_DEX,   "DEX" },
	{ TR2_SUST_CON,   "CON" },
	{ TR2_SUST_CHR,   "CHR" },
#endif
};

/*
 * Miscellaneous magic given by an object's "flags2" field
 */

static const flag_desc misc_flags2_desc[] =
{
#ifdef JP
	{ TR2_THROW,      "投擲" },
	{ TR2_REFLECT,    "反射" },
	{ TR2_FREE_ACT,   "麻痺知らず" },
	{ TR2_HOLD_LIFE,  "生命力維持" },
#else
	{ TR2_THROW,      "Throwing" },
	{ TR2_REFLECT,    "Reflection" },
	{ TR2_FREE_ACT,   "Free Action" },
	{ TR2_HOLD_LIFE,  "Hold Life" },
#endif
};

/*
 * Miscellaneous magic given by an object's "flags3" field
 *
 * Note that cursed artifacts and objects with permanent light
 * are handled "directly" -- see analyze_misc_magic()
 */

static const flag_desc misc_flags3_desc[] =
{
#ifdef JP
	{ TR3_SH_FIRE,            "火炎オーラ" },
	{ TR3_SH_ELEC,            "電撃オーラ" },
	{ TR3_SH_COLD,            "冷気オーラ" },
	{ TR3_NO_TELE,            "反テレポート" },
	{ TR3_NO_MAGIC,           "反魔法" },
	{ TR3_FEATHER,            "浮遊" },
	{ TR3_SEE_INVIS,          "可視透明" },
	{ TR3_TELEPATHY,          "テレパシー" },
	{ TR3_SLOW_DIGEST,        "遅消化" },
	{ TR3_REGEN,              "急速回復" },
	{ TR3_WARNING,            "警告" },
/*	{ TR3_XTRA_MIGHT,         "強力射撃" }, */
	{ TR3_XTRA_SHOTS,         "追加射撃" },        /* always +1? */
	{ TR3_DRAIN_EXP,          "経験値吸収" },
	{ TR3_AGGRAVATE,          "反感" },
	{ TR3_BLESSED,            "祝福" },
	{ TR3_DEC_MANA,           "消費魔力減少" },
#else
	{ TR3_SH_FIRE,            "Fiery Aura" },
	{ TR3_SH_ELEC,            "Electric Aura" },
	{ TR3_SH_COLD,            "Coldly Aura" },
	{ TR3_NO_TELE,            "Prevent Teleportation" },
	{ TR3_NO_MAGIC,           "Anti-Magic" },
	{ TR3_FEATHER,            "Levitation" },
	{ TR3_SEE_INVIS,          "See Invisible" },
	{ TR3_TELEPATHY,          "ESP" },
	{ TR3_SLOW_DIGEST,        "Slow Digestion" },
	{ TR3_REGEN,              "Regeneration" },
	{ TR3_WARNING,            "Warning" },
/*	{ TR3_XTRA_MIGHT,         "Extra Might" }, */
	{ TR3_XTRA_SHOTS,         "+1 Extra Shot" },        /* always +1? */
	{ TR3_DRAIN_EXP,          "Drains Experience" },
	{ TR3_AGGRAVATE,          "Aggravates" },
	{ TR3_BLESSED,            "Blessed Blade" },
	{ TR3_DEC_MANA,           "Decrease Shouhi Mana" },
#endif
};


/*
 * A special type used just for deailing with pvals
 */
typedef struct
{
	/*
	 * This will contain a string such as "+2", "-10", etc.
	 */
	char pval_desc[12];

	/*
	 * A list of various player traits affected by an object's pval such
	 * as stats, speed, stealth, etc.  "Extra attacks" is NOT included in
	 * this list since it will probably be desirable to format its
	 * description differently.
	 *
	 * Note that room need only be reserved for the number of stats - 1
	 * since the description "All stats" is used if an object affects all
	 * all stats. Also, room must be reserved for a sentinel NULL pointer.
	 *
	 * This will be a list such as ["STR", "DEX", "Stealth", NULL] etc.
	 *
	 * This list includes extra attacks, for simplicity.
	 */
	cptr pval_affects[N_ELEMENTS(stat_flags_desc) - 1 +
			  N_ELEMENTS(pval_flags1_desc) + 1];

} pval_info_type;


/*
 * An "object analysis structure"
 *
 * It will be filled with descriptive strings detailing an object's
 * various magical powers. The "ignore X" traits are not noted since
 * all artifacts ignore "normal" destruction.
 */

typedef struct
{
	/* "The Longsword Dragonsmiter (6d4) (+20, +25)" */
	char description[MAX_NLEN];

	/* Description of what is affected by an object's pval */
	pval_info_type pval_info;

	/* A list of an object's slaying preferences */
	cptr slays[N_ELEMENTS(slay_flags_desc) + 1];

	/* A list if an object's elemental brands */
	cptr brands[N_ELEMENTS(brand_flags_desc) + 1];

	/* A list of immunities granted by an object */
	cptr immunities[N_ELEMENTS(immune_flags_desc) + 1];

	/* A list of resistances granted by an object */
	cptr resistances[N_ELEMENTS(resist_flags_desc) + 1];

	/* A list of stats sustained by an object */
	cptr sustains[N_ELEMENTS(sustain_flags_desc)  - 1 + 1];

	/* A list of various magical qualities an object may have */
	cptr misc_magic[N_ELEMENTS(misc_flags2_desc) + N_ELEMENTS(misc_flags3_desc)
			+ 1       /* Permanent Light */
			+ 1       /* TY curse */
			+ 1       /* type of curse */
			+ 1];     /* sentinel NULL */

	/* A string describing an artifact's activation */
	cptr activation;

	/* "Level 20, Rarity 30, 3.0 lbs, 20000 Gold" */
	char misc_desc[80];
} obj_desc_list;


/*
 * Write out `n' of the character `c' to the spoiler file
 */
static void spoiler_out_n_chars(int n, char c)
{
	while (--n >= 0) fputc(c, fff);
}


/*
 * Write out `n' blank lines to the spoiler file
 */
static void spoiler_blanklines(int n)
{
	spoiler_out_n_chars(n, '\n');
}


/*
 * Write a line to the spoiler file and then "underline" it with hypens
 */
static void spoiler_underline(cptr str)
{
	fprintf(fff, "%s\n", str);
	spoiler_out_n_chars(strlen(str), '-');
	fprintf(fff, "\n");
}



/*
 * This function does most of the actual "analysis". Given a set of bit flags
 * (which will be from one of the flags fields from the object in question),
 * a "flag description structure", a "description list", and the number of
 * elements in the "flag description structure", this function sets the
 * "description list" members to the appropriate descriptions contained in
 * the "flag description structure".
 *
 * The possibly updated description pointer is returned.
 */
static cptr *spoiler_flag_aux(const u32b art_flags, const flag_desc *flag_ptr,
			      cptr *desc_ptr, const int n_elmnts)
{
	int i;

	for (i = 0; i < n_elmnts; ++i)
	{
		if (art_flags & flag_ptr[i].flag)
		{
			*desc_ptr++ = flag_ptr[i].desc;
		}
	}

	return desc_ptr;
}


/*
 * Acquire a "basic" description "The Cloak of Death [1,+10]"
 */
static void analyze_general (object_type *o_ptr, char *desc_ptr)
{
	/* Get a "useful" description of the object */
	object_desc_store(desc_ptr, o_ptr, TRUE, 1);
}


/*
 * List "player traits" altered by an artifact's pval. These include stats,
 * speed, infravision, tunneling, stealth, searching, and extra attacks.
 */
static void analyze_pval (object_type *o_ptr, pval_info_type *p_ptr)
{
	const u32b all_stats = (TR1_STR | TR1_INT | TR1_WIS |
				TR1_DEX | TR1_CON | TR1_CHR);

	u32b f1, f2, f3;

	cptr *affects_list;

	/* If pval == 0, there is nothing to do. */
	if (!o_ptr->pval)
	{
		/* An "empty" pval description indicates that pval == 0 */
		p_ptr->pval_desc[0] = '\0';
		return;
	}

	/* Extract the flags */
	object_flags(o_ptr, &f1, &f2, &f3);

	affects_list = p_ptr->pval_affects;

	/* Create the "+N" string */
	sprintf(p_ptr->pval_desc, "%s%d", POSITIZE(o_ptr->pval), o_ptr->pval);

	/* First, check to see if the pval affects all stats */
	if ((f1 & all_stats) == all_stats)
	{
#ifdef JP
		*affects_list++ = "全能力";
#else
		*affects_list++ = "All stats";
#endif
	}

	/* Are any stats affected? */
	else if (f1 & all_stats)
	{
		affects_list = spoiler_flag_aux(f1, stat_flags_desc,
						affects_list,
						N_ELEMENTS(stat_flags_desc));
	}

	/* And now the "rest" */
	affects_list = spoiler_flag_aux(f1, pval_flags1_desc,
					affects_list,
					N_ELEMENTS(pval_flags1_desc));

	/* Terminate the description list */
	*affects_list = NULL;
}


/* Note the slaying specialties of a weapon */
static void analyze_slay (object_type *o_ptr, cptr *slay_list)
{
	u32b f1, f2, f3;

	object_flags(o_ptr, &f1, &f2, &f3);

	slay_list = spoiler_flag_aux(f1, slay_flags_desc, slay_list,
				     N_ELEMENTS(slay_flags_desc));

	/* Terminate the description list */
	*slay_list = NULL;
}

/* Note an object's elemental brands */
static void analyze_brand (object_type *o_ptr, cptr *brand_list)
{
	u32b f1, f2, f3;

	object_flags(o_ptr, &f1, &f2, &f3);

	brand_list = spoiler_flag_aux(f1, brand_flags_desc, brand_list,
				      N_ELEMENTS(brand_flags_desc));

	/* Terminate the description list */
	*brand_list = NULL;
}


/* Note the resistances granted by an object */
static void analyze_resist (object_type *o_ptr, cptr *resist_list)
{
	u32b f1, f2, f3;

	object_flags(o_ptr, &f1, &f2, &f3);

	resist_list = spoiler_flag_aux(f2, resist_flags_desc,
				       resist_list, N_ELEMENTS(resist_flags_desc));

	/* Terminate the description list */
	*resist_list = NULL;
}


/* Note the immunities granted by an object */
static void analyze_immune (object_type *o_ptr, cptr *immune_list)
{
	u32b f1, f2, f3;

	object_flags(o_ptr, &f1, &f2, &f3);

	immune_list = spoiler_flag_aux(f2, immune_flags_desc,
				       immune_list, N_ELEMENTS(immune_flags_desc));

	/* Terminate the description list */
	*immune_list = NULL;
}

/* Note which stats an object sustains */

static void analyze_sustains (object_type *o_ptr, cptr *sustain_list)
{
	const u32b all_sustains = (TR2_SUST_STR | TR2_SUST_INT | TR2_SUST_WIS |
				   TR2_SUST_DEX | TR2_SUST_CON | TR2_SUST_CHR);

	u32b f1, f2, f3;

	object_flags(o_ptr, &f1, &f2, &f3);

	/* Simplify things if an item sustains all stats */
	if ((f2 & all_sustains) == all_sustains)
	{
#ifdef JP
		*sustain_list++ = "全能力";
#else
		*sustain_list++ = "All stats";
#endif
	}

	/* Should we bother? */
	else if ((f2 & all_sustains))
	{
		sustain_list = spoiler_flag_aux(f2, sustain_flags_desc,
						sustain_list,
						N_ELEMENTS(sustain_flags_desc));
	}

	/* Terminate the description list */
	*sustain_list = NULL;
}


/*
 * Note miscellaneous powers bestowed by an artifact such as see invisible,
 * free action, permanent light, etc.
 */
static void analyze_misc_magic (object_type *o_ptr, cptr *misc_list)
{
	u32b f1, f2, f3;

	object_flags(o_ptr, &f1, &f2, &f3);

	misc_list = spoiler_flag_aux(f2, misc_flags2_desc, misc_list,
				     N_ELEMENTS(misc_flags2_desc));

	misc_list = spoiler_flag_aux(f3, misc_flags3_desc, misc_list,
				     N_ELEMENTS(misc_flags3_desc));

	/*
	 * Artifact lights -- large radius light.
	 */
	if ((o_ptr->tval == TV_LITE) && artifact_p(o_ptr))
	{
#ifdef JP
		*misc_list++ = "永久光源(半径3)";
#else
		*misc_list++ = "Permanent Light(3)";
#endif
	}

	/*
	 * Glowing artifacts -- small radius light.
	 */
	if (f3 & (TR3_LITE))
	{
#ifdef JP
		*misc_list++ = "永久光源(半径1)";
#else
		*misc_list++ = "Permanent Light(1)";
#endif
	}

	/*
	 * Handle cursed objects here to avoid redundancies such as noting
	 * that a permanently cursed object is heavily cursed as well as
	 * being "lightly cursed".
	 */

/*	if (cursed_p(o_ptr)) */
	if (1)
	{
		if (f3 & TR3_TY_CURSE)
		{
#ifdef JP
			*misc_list++ = "太古の怨念";
#else
			*misc_list++ = "Ancient Curse";
#endif
		}
		if (o_ptr->curse_flags & TRC_PERMA_CURSE)
		{
#ifdef JP
			*misc_list++ = "永遠の呪い";
#else
			*misc_list++ = "Permanently Cursed";
#endif
		}
		else if (o_ptr->curse_flags & TRC_HEAVY_CURSE)
		{
#ifdef JP
			*misc_list++ = "強力な呪い";
#else
			*misc_list++ = "Heavily Cursed";
#endif
		}
/*		else */
		else if (o_ptr->curse_flags & TRC_CURSED)
		{
#ifdef JP
			*misc_list++ = "呪い";
#else
			*misc_list++ = "Cursed";
#endif
		}
	}

	/* Terminate the description list */
	*misc_list = NULL;
}




/*
 * Determine the minimum depth an artifact can appear, its rarity, its weight,
 * and its value in gold pieces
 */
static void analyze_misc (object_type *o_ptr, char *misc_desc)
{
	artifact_type *a_ptr = &a_info[o_ptr->name1];

#ifdef JP
	sprintf(misc_desc, "レベル %u, 希少度 %u, %d.%d kg, ＄%ld",
		a_ptr->level, a_ptr->rarity,
		lbtokg1(a_ptr->weight), lbtokg2(a_ptr->weight), a_ptr->cost);
#else
	sprintf(misc_desc, "Level %u, Rarity %u, %d.%d lbs, %ld Gold",
		a_ptr->level, a_ptr->rarity,
		a_ptr->weight / 10, a_ptr->weight % 10, a_ptr->cost);
#endif
}


/*
 * Fill in an object description structure for a given object
 */
static void object_analyze(object_type *o_ptr, obj_desc_list *desc_ptr)
{
	analyze_general(o_ptr, desc_ptr->description);

	analyze_pval(o_ptr, &desc_ptr->pval_info);

	analyze_brand(o_ptr, desc_ptr->brands);

	analyze_slay(o_ptr, desc_ptr->slays);

	analyze_immune(o_ptr, desc_ptr->immunities);

	analyze_resist(o_ptr, desc_ptr->resistances);

	analyze_sustains(o_ptr, desc_ptr->sustains);

	analyze_misc_magic(o_ptr, desc_ptr->misc_magic);

	analyze_misc(o_ptr, desc_ptr->misc_desc);

	desc_ptr->activation = item_activation(o_ptr);
}


static void print_header(void)
{
	char buf[80];

#ifndef FAKE_VERSION
	sprintf(buf, "Artifact Spoilers for Angband Version %d.%d.%d",
		VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
	spoiler_underline(buf);
#else /* FAKE_VERSION */
	sprintf(buf, "Artifact Spoilers for Hengband Version %d.%d.%d",
	        FAKE_VER_MAJOR-10, FAKE_VER_MINOR, FAKE_VER_PATCH);
	spoiler_underline(buf);
#endif /* FAKE_VERSION */

}

/*
 * This is somewhat ugly.
 *
 * Given a header ("Resist", e.g.), a list ("Fire", "Cold", Acid", e.g.),
 * and a separator character (',', e.g.), write the list to the spoiler file
 * in a "nice" format, such as:
 *
 *      Resist Fire, Cold, Acid
 *
 * That was a simple example, but when the list is long, a line wrap
 * should occur, and this should induce a new level of indention if
 * a list is being spread across lines. So for example, Bladeturner's
 * list of resistances should look something like this
 *
 *     Resist Acid, Lightning, Fire, Cold, Poison, Light, Dark, Blindness,
 *       Confusion, Sound, Shards, Nether, Nexus, Chaos, Disenchantment
 *
 * However, the code distinguishes between a single list of many items vs.
 * many lists. (The separator is used to make this determination.) A single
 * list of many items will not cause line wrapping (since there is no
 * apparent reason to do so). So the lists of Ulmo's miscellaneous traits
 * might look like this:
 *
 *     Free Action; Hold Life; See Invisible; Slow Digestion; Regeneration
 *     Blessed Blade
 *
 * So comparing the two, "Regeneration" has no trailing separator and
 * "Blessed Blade" was not indented. (Also, Ulmo's lists have no headers,
 * but that's not relevant to line wrapping and indention.)
 */

/* ITEM_SEP separates items within a list */
#define ITEM_SEP ','


/* LIST_SEP separates lists */
#ifdef JP
#define LIST_SEP ','
#else
#define LIST_SEP ';'
#endif

static void spoiler_outlist(cptr header, cptr *list, char separator)
{
	int line_len, buf_len;
	char line[MAX_LINE_LEN+1], buf[80];

	/* Ignore an empty list */
	if (*list == NULL) return;

	/* This function always indents */
	strcpy(line, INDENT1);

	/* Create header (if one was given) */
	if (header && (header[0]))
	{
		strcat(line, header);
		strcat(line, " ");
	}

	line_len = strlen(line);

	/* Now begin the tedious task */
	while (1)
	{
		/* Copy the current item to a buffer */
		strcpy(buf, *list);

		/* Note the buffer's length */
		buf_len = strlen(buf);

		/*
		 * If there is an item following this one, pad with separator and
		 * a space and adjust the buffer length
		 */

		if (list[1])
		{
			sprintf(buf + buf_len, "%c ", separator);
			buf_len += 2;
		}

		/*
		 * If the buffer will fit on the current line, just append the
		 * buffer to the line and adjust the line length accordingly.
		 */

		if (line_len + buf_len <= MAX_LINE_LEN)
		{
			strcat(line, buf);
			line_len += buf_len;
		}

		/* Apply line wrapping and indention semantics described above */
		else
		{
			/*
			 * Don't print a trailing list separator but do print a trailing
			 * item separator.
			 */
			if (line_len > 1 && line[line_len - 1] == ' '
			    && line[line_len - 2] == LIST_SEP)
			{
				/* Ignore space and separator */
				line[line_len - 2] = '\0';

				/* Write to spoiler file */
				fprintf(fff, "%s\n", line);

				/* Begin new line at primary indention level */
				sprintf(line, "%s%s", INDENT1, buf);
			}

			else
			{
				/* Write to spoiler file */
				fprintf(fff, "%s\n", line);

				/* Begin new line at secondary indention level */
				sprintf(line, "%s%s", INDENT2, buf);
			}

			line_len = strlen(line);
		}

		/* Advance, with break */
		if (!*++list) break;
	}

	/* Write what's left to the spoiler file */
	fprintf(fff, "%s\n", line);
}


/* Create a spoiler file entry for an artifact */

static void spoiler_print_art(obj_desc_list *art_ptr)
{
	pval_info_type *pval_ptr = &art_ptr->pval_info;

	char buf[80];

	/* Don't indent the first line */
	fprintf(fff, "%s\n", art_ptr->description);

	/* An "empty" pval description indicates that the pval affects nothing */
	if (pval_ptr->pval_desc[0])
	{
		/* Mention the effects of pval */
#ifdef JP
		sprintf(buf, "%sの修正:", pval_ptr->pval_desc);
#else
		sprintf(buf, "%s to", pval_ptr->pval_desc);
#endif
		spoiler_outlist(buf, pval_ptr->pval_affects, ITEM_SEP);
	}

	/* Now deal with the description lists */

#ifdef JP
	spoiler_outlist("対:", art_ptr->slays, ITEM_SEP);

	spoiler_outlist("武器属性:", art_ptr->brands, LIST_SEP);

	spoiler_outlist("免疫:", art_ptr->immunities, ITEM_SEP);

	spoiler_outlist("耐性:", art_ptr->resistances, ITEM_SEP);

	spoiler_outlist("維持:", art_ptr->sustains, ITEM_SEP);
#else
	spoiler_outlist("Slay", art_ptr->slays, ITEM_SEP);

	spoiler_outlist("", art_ptr->brands, LIST_SEP);

	spoiler_outlist("Immunity to", art_ptr->immunities, ITEM_SEP);

	spoiler_outlist("Resist", art_ptr->resistances, ITEM_SEP);

	spoiler_outlist("Sustain", art_ptr->sustains, ITEM_SEP);
#endif
	spoiler_outlist("", art_ptr->misc_magic, LIST_SEP);


	/* Write out the possible activation at the primary indention level */
	if (art_ptr->activation)
	{
#ifdef JP
		fprintf(fff, "%s発動: %s\n", INDENT1, art_ptr->activation);
#else
		fprintf(fff, "%sActivates for %s\n", INDENT1, art_ptr->activation);
#endif
	}

	/* End with the miscellaneous facts */
	fprintf(fff, "%s%s\n\n", INDENT1, art_ptr->misc_desc);
}


/*
 * Hack -- Create a "forged" artifact
 */
static bool make_fake_artifact(object_type *o_ptr, int name1)
{
	int i;

	artifact_type *a_ptr = &a_info[name1];


	/* Ignore "empty" artifacts */
	if (!a_ptr->name) return FALSE;

	/* Acquire the "kind" index */
	i = lookup_kind(a_ptr->tval, a_ptr->sval);

	/* Oops */
	if (!i) return (FALSE);

	/* Create the artifact */
	object_prep(o_ptr, i);

	/* Save the name */
	o_ptr->name1 = name1;

	/* Extract the fields */
	o_ptr->pval = a_ptr->pval;
	o_ptr->ac = a_ptr->ac;
	o_ptr->dd = a_ptr->dd;
	o_ptr->ds = a_ptr->ds;
	o_ptr->to_a = a_ptr->to_a;
	o_ptr->to_h = a_ptr->to_h;
	o_ptr->to_d = a_ptr->to_d;
	o_ptr->weight = a_ptr->weight;

	/* Success */
	return (TRUE);
}


/*
 * Create a spoiler file for artifacts
 */
static void spoil_artifact(cptr fname)
{
	int i, j;

	object_type forge;
	object_type *q_ptr;

	obj_desc_list artifact;

	char buf[1024];


	/* Build the filename */
	path_build(buf, 1024, ANGBAND_DIR_USER, fname);

	/* File type is "TEXT" */
	FILE_TYPE(FILE_TYPE_TEXT);

	/* Open the file */
	fff = my_fopen(buf, "w");

	/* Oops */
	if (!fff)
	{
		msg_print("Cannot create spoiler file.");
		return;
	}

	/* Dump the header */
	print_header();

	/* List the artifacts by tval */
	for (i = 0; group_artifact[i].tval; i++)
	{
		/* Write out the group title */
		if (group_artifact[i].name)
		{
			spoiler_blanklines(2);
			spoiler_underline(group_artifact[i].name);
			spoiler_blanklines(1);
		}

		/* Now search through all of the artifacts */
		for (j = 1; j < max_a_idx; ++j)
		{
			artifact_type *a_ptr = &a_info[j];

			/* We only want objects in the current group */
			if (a_ptr->tval != group_artifact[i].tval) continue;

			/* Get local object */
			q_ptr = &forge;

			/* Wipe the object */
			object_wipe(q_ptr);

			/* Attempt to "forge" the artifact */
			if (!make_fake_artifact(q_ptr, j)) continue;

			/* Analyze the artifact */
			object_analyze(q_ptr, &artifact);

			/* Write out the artifact description to the spoiler file */
			spoiler_print_art(&artifact);
		}
	}

	/* Check for errors */
	if (ferror(fff) || my_fclose(fff))
	{
		msg_print("Cannot close spoiler file.");
		return;
	}

	/* Message */
	msg_print("Successfully created a spoiler file.");
}





/*
 * Create a spoiler file for monsters   -BEN-
 */
static void spoil_mon_desc(cptr fname)
{
	int i, n = 0;

	u16b why = 2;
	s16b *who;

	char buf[1024];

	char nam[80];
	char lev[80];
	char rar[80];
	char spd[80];
	char ac[80];
	char hp[80];
	char exp[80];

	/* Build the filename */
	path_build(buf, 1024, ANGBAND_DIR_USER, fname);

	/* File type is "TEXT" */
	FILE_TYPE(FILE_TYPE_TEXT);

	/* Open the file */
	fff = my_fopen(buf, "w");

	/* Oops */
	if (!fff)
	{
		msg_print("Cannot create spoiler file.");
		return;
	}

	/* Allocate the "who" array */
	C_MAKE(who, max_r_idx, s16b);

	/* Dump the header */

#ifndef FAKE_VERSION
	fprintf(fff, "Monster Spoilers for Angband Version %d.%d.%d\n",
		VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
	fprintf(fff, "------------------------------------------\n\n");
#else
	fprintf(fff, "Monster Spoilers for Hengband Version %d.%d.%d\n",
	        FAKE_VER_MAJOR-10, FAKE_VER_MINOR, FAKE_VER_PATCH);
	fprintf(fff, "------------------------------------------\n\n");
#endif

	/* Dump the header */
	fprintf(fff, "    %-38.38s%4s%4s%4s%7s%5s  %11.11s\n",
		"Name", "Lev", "Rar", "Spd", "Hp", "Ac", "Visual Info");
	fprintf(fff, "%-42.42s%4s%4s%4s%7s%5s  %11.11s\n",
		"--------", "---", "---", "---", "--", "--", "-----------");


	/* Scan the monsters */
	for (i = 1; i < max_r_idx; i++)
	{
		monster_race *r_ptr = &r_info[i];

		/* Use that monster */
		if (r_ptr->name) who[n++] = i;
	}

        /* Select the sort method */
        ang_sort_comp = ang_sort_comp_hook;
        ang_sort_swap = ang_sort_swap_hook;

        /* Sort the array by dungeon depth of monsters */
        ang_sort(who, &why, n);

	/* Scan again */
	for (i = 0; i < n; i++)
	{
		monster_race *r_ptr = &r_info[who[i]];

		cptr name = (r_name + r_ptr->name);
		if (r_ptr->flags7 & (RF7_KAGE)) continue;

		/* Get the "name" */
/*		if (r_ptr->flags1 & (RF1_QUESTOR)) */
		if (0)
		{
			sprintf(nam, "[Q] %s", name);
		}
		else if (r_ptr->flags1 & (RF1_UNIQUE))
		{
			sprintf(nam, "[U] %s", name);
		}
		else
		{
#ifdef JP
			sprintf(nam, "    %s", name);
#else
			sprintf(nam, "The %s", name);
#endif
		}


		/* Level */
		sprintf(lev, "%d", r_ptr->level);

		/* Rarity */
		sprintf(rar, "%d", r_ptr->rarity);

		/* Speed */
		if (r_ptr->speed >= 110)
		{
			sprintf(spd, "+%d", (r_ptr->speed - 110));
		}
		else
		{
			sprintf(spd, "-%d", (110 - r_ptr->speed));
		}

		/* Armor Class */
		sprintf(ac, "%d", r_ptr->ac);

		/* Hitpoints */
		if ((r_ptr->flags1 & (RF1_FORCE_MAXHP)) || (r_ptr->hside == 1))
		{
			sprintf(hp, "%d", r_ptr->hdice * r_ptr->hside);
		}
		else
		{
			sprintf(hp, "%dd%d", r_ptr->hdice, r_ptr->hside);
		}


		/* Experience */
		sprintf(exp, "%ld", (long)(r_ptr->mexp));

		/* Hack -- use visual instead */
		sprintf(exp, "%s '%c'", attr_to_text(r_ptr->d_attr), r_ptr->d_char);

		/* Dump the info */
		fprintf(fff, "%-42.42s%4s%4s%4s%7s%5s  %11.11s\n",
			nam, lev, rar, spd, hp, ac, exp);
	}

	/* End it */
	fprintf(fff, "\n");


	/* Free the "who" array */
	C_KILL(who, max_r_idx, s16b);

	/* Check for errors */
	if (ferror(fff) || my_fclose(fff))
	{
		msg_print("Cannot close spoiler file.");
		return;
	}

	/* Worked */
	msg_print("Successfully created a spoiler file.");
}




/*
 * Monster spoilers by: smchorse@ringer.cs.utsa.edu (Shawn McHorse)
 *
 * Primarily based on code already in mon-desc.c, mostly by -BEN-
 */



/*
 * Buffer text to the given file. (-SHAWN-)
 * This is basically c_roff() from mon-desc.c with a few changes.
 */
static void spoil_out(cptr str)
{
	cptr r;

	/* Line buffer */
	static char roff_buf[256];

#ifdef JP
	char iskanji2=0;
#endif
	/* Current pointer into line roff_buf */
	static char *roff_p = roff_buf;

	/* Last space saved into roff_buf */
	static char *roff_s = NULL;

	/* Special handling for "new sequence" */
	if (!str)
	{
		if (roff_p != roff_buf) roff_p--;
		while (*roff_p == ' ' && roff_p != roff_buf) roff_p--;
		if (roff_p == roff_buf) fprintf(fff, "\n");
		else
		{
			*(roff_p + 1) = '\0';
			fprintf(fff, "%s\n\n", roff_buf);
		}
		roff_p = roff_buf;
		roff_s = NULL;
		roff_buf[0] = '\0';
		return;
	}

	/* Scan the given string, character at a time */
	for (; *str; str++)
	{
#ifdef JP
	        char cbak;
                int k_flag = iskanji((unsigned char)(*str));
#endif
		char ch = *str;
		int wrap = (ch == '\n');

#ifdef JP
                if (!isprint(ch) && !k_flag && !iskanji2) ch = ' ';
		if(k_flag && !iskanji2)iskanji2=1;else iskanji2=0;
#else
		if (!isprint(ch)) ch = ' ';
#endif

#ifdef JP
                if ( roff_p >= roff_buf+( (k_flag) ? 74 : 75) ) wrap=1;
		if ((ch == ' ') && (roff_p + 2 >= roff_buf + ((k_flag) ? 74 : 75))) wrap = 1;
#else
		if (roff_p >= roff_buf + 75) wrap = 1;
		if ((ch == ' ') && (roff_p + 2 >= roff_buf + 75)) wrap = 1;
#endif


		/* Handle line-wrap */
		if (wrap)
		{
			*roff_p = '\0';
			r = roff_p;
#ifdef JP
                                cbak=' ';
#endif
			if (roff_s && (ch != ' '))
			{
#ifdef JP
			        cbak=*roff_s;
#endif
				*roff_s = '\0';
				r = roff_s + 1;
			}
			fprintf(fff, "%s\n", roff_buf);
			roff_s = NULL;
			roff_p = roff_buf;
#ifdef JP
			if(cbak != ' ') *roff_p++ = cbak; 
#endif
			while (*r) *roff_p++ = *r++;
		}

		/* Save the char */
		if ((roff_p > roff_buf) || (ch != ' '))
		{
#ifdef JP
		  if( !k_flag ){
			if (ch == ' ' || ch == '(' ) roff_s = roff_p;
		  }
		  else{
		    if( iskanji2 && 
                        strncmp(str, "。", 2) != 0 && 
			strncmp(str, "、", 2) != 0 &&
		        strncmp(str, "ィ", 2) != 0 &&
			strncmp(str, "ー", 2) != 0) roff_s = roff_p;
		  }
#else
			if (ch == ' ') roff_s = roff_p;
#endif

			*roff_p++ = ch;
		}
	}
}



/*
 *  Hook function used in spoil_mon_info()
 */
void roff_func(byte attr, cptr str)
{
	spoil_out(str);
}


/*
 * Create a spoiler file for monsters (-SHAWN-)
 */
static void spoil_mon_info(cptr fname)
{
	char buf[1024];
	int msex, i, l, n=0;
	bool breath, magic;
	u32b flags1, flags2, flags3, flags4, flags5, flags6, flags7;

	u16b why = 2;
	s16b *who;

	/* Build the filename */
	path_build(buf, 1024, ANGBAND_DIR_USER, fname);

	/* File type is "TEXT" */
	FILE_TYPE(FILE_TYPE_TEXT);

	/* Open the file */
	fff = my_fopen(buf, "w");

	/* Oops */
	if (!fff)
	{
		msg_print("Cannot create spoiler file.");
		return;
	}


	/* Dump the header */
#ifndef FAKE_VERSION
	sprintf(buf, "Monster Spoilers for Angband Version %d.%d.%d\n",
		VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
#else
	sprintf(buf, "Monster Spoilers for Hengband Version %d.%d.%d\n",
	     FAKE_VER_MAJOR-10, FAKE_VER_MINOR, FAKE_VER_PATCH);
#endif

	spoil_out(buf);
	spoil_out("------------------------------------------\n\n");

	/* Allocate the "who" array */
	C_MAKE(who, max_r_idx, s16b);

	/* Scan the monsters */
	for (i = 1; i < max_r_idx; i++)
	{
		monster_race *r_ptr = &r_info[i];

		/* Use that monster */
		if (r_ptr->name) who[n++] = i;
	}

	/* Select the sort method */
	ang_sort_comp = ang_sort_comp_hook;
	ang_sort_swap = ang_sort_swap_hook;

	/* Sort the array by dungeon depth of monsters */
	ang_sort(who, &why, n);


	/*
	 * List all monsters in order
	 */
	for (l = 0; l < n; l++)
	{
		monster_race *r_ptr = &r_info[who[l]];

		/* Extract the flags */
		flags1 = r_ptr->flags1;
		flags2 = r_ptr->flags2;
		flags3 = r_ptr->flags3;
		flags4 = r_ptr->flags4;
		flags5 = r_ptr->flags5;
		flags6 = r_ptr->flags6;
		flags7 = r_ptr->flags7;
		breath = FALSE;
		magic = FALSE;

		/* Extract a gender (if applicable) */
		if (flags1 & (RF1_FEMALE)) msex = 2;
		else if (flags1 & (RF1_MALE)) msex = 1;
		else msex = 0;


		/* Prefix */
		if (flags1 & (RF1_QUESTOR))
		{
			spoil_out("[Q] ");
		}
		else if (flags1 & (RF1_UNIQUE))
		{
			spoil_out("[U] ");
		}
		else
		{
#ifndef JP
			spoil_out("The ");
#endif
		}

		/* Name */
#ifdef JP
		sprintf(buf, "%s/%s  (", (r_name + r_ptr->name),(r_name+r_ptr->E_name));  /* ---)--- */
#else
		sprintf(buf, "%s  (", (r_name + r_ptr->name));  /* ---)--- */
#endif

		spoil_out(buf);

		/* Color */
		spoil_out(attr_to_text(r_ptr->d_attr));

		/* Symbol --(-- */
		sprintf(buf, " '%c')\n", r_ptr->d_char);
		spoil_out(buf);


		/* Indent */
		sprintf(buf, "=== ");
		spoil_out(buf);

		/* Number */
		sprintf(buf, "Num:%d  ", who[l]);
		spoil_out(buf);

		/* Level */
		sprintf(buf, "Lev:%d  ", r_ptr->level);
		spoil_out(buf);

		/* Rarity */
		sprintf(buf, "Rar:%d  ", r_ptr->rarity);
		spoil_out(buf);

		/* Speed */
		if (r_ptr->speed >= 110)
		{
			sprintf(buf, "Spd:+%d  ", (r_ptr->speed - 110));
		}
		else
		{
			sprintf(buf, "Spd:-%d  ", (110 - r_ptr->speed));
		}
		spoil_out(buf);

		/* Hitpoints */
		if ((flags1 & (RF1_FORCE_MAXHP)) || (r_ptr->hside == 1))
		{
			sprintf(buf, "Hp:%d  ", r_ptr->hdice * r_ptr->hside);
		}
		else
		{
			sprintf(buf, "Hp:%dd%d  ", r_ptr->hdice, r_ptr->hside);
		}
		spoil_out(buf);

		/* Armor Class */
		sprintf(buf, "Ac:%d  ", r_ptr->ac);
		spoil_out(buf);

		/* Experience */
		sprintf(buf, "Exp:%ld\n", (long)(r_ptr->mexp));
		spoil_out(buf);

		/* Reuse the code of monster recall. */
		output_monster_spoiler(who[l], roff_func);

		spoil_out(NULL);
	}

	/* Free the "who" array */
	C_KILL(who, max_r_idx, s16b);

	/* Check for errors */
	if (ferror(fff) || my_fclose(fff))
	{
		msg_print("Cannot close spoiler file.");
		return;
	}

	msg_print("Successfully created a spoiler file.");
}



/*
 * Forward declare
 */
extern void do_cmd_spoilers(void);

/*
 * Create Spoiler files -BEN-
 */
void do_cmd_spoilers(void)
{
	int i;


	/* Save the screen */
	screen_save();


	/* Drop priv's */
	safe_setuid_drop();


	/* Interact */
	while (1)
	{
		/* Clear screen */
		Term_clear();

		/* Info */
		prt("Create a spoiler file.", 2, 0);

		/* Prompt for a file */
		prt("(1) Brief Object Info (obj-desc.spo)", 5, 5);
		prt("(2) Brief Artifact Info (artifact.spo)", 6, 5);
		prt("(3) Brief Monster Info (mon-desc.spo)", 7, 5);
		prt("(4) Full Monster Info (mon-info.spo)", 8, 5);

		/* Prompt */
#ifdef JP
prt("コマンド:", 18, 0);
#else
		prt("Command: ", 12, 0);
#endif


		/* Get a choice */
		i = inkey();

		/* Escape */
		if (i == ESCAPE)
		{
			break;
		}

		/* Option (1) */
		else if (i == '1')
		{
			spoil_obj_desc("obj-desc.spo");
		}

		/* Option (2) */
		else if (i == '2')
		{
			spoil_artifact("artifact.spo");
		}

		/* Option (3) */
		else if (i == '3')
		{
			spoil_mon_desc("mon-desc.spo");
		}

		/* Option (4) */
		else if (i == '4')
		{
			spoil_mon_info("mon-info.spo");
		}

		/* Oops */
		else
		{
			bell();
		}

		/* Flush messages */
		msg_print(NULL);
	}


	/* Grab priv's */
	safe_setuid_grab();


	/* Restore the screen */
	screen_load();
}

/*
 * Fill in an object description structure for a given object
 */
static void random_artifact_analyze(object_type *o_ptr, obj_desc_list *desc_ptr)
{
	analyze_general(o_ptr, desc_ptr->description);
	analyze_pval(o_ptr, &desc_ptr->pval_info);
	analyze_brand(o_ptr, desc_ptr->brands);
	analyze_slay(o_ptr, desc_ptr->slays);
	analyze_immune(o_ptr, desc_ptr->immunities);
	analyze_resist(o_ptr, desc_ptr->resistances);
	analyze_sustains(o_ptr, desc_ptr->sustains);
	analyze_misc_magic(o_ptr, desc_ptr->misc_magic);
	desc_ptr->activation = item_activation(o_ptr);
#ifdef JP
	sprintf(desc_ptr->misc_desc, "重さ %d.%d kg",
		lbtokg1(o_ptr->weight), lbtokg2(o_ptr->weight));
#else
	sprintf(desc_ptr->misc_desc, "Weight %d.%d lbs",
		o_ptr->weight / 10, o_ptr->weight % 10);
#endif
}

/* Create a spoiler file entry for an artifact */

static void spoiler_print_randart(object_type *o_ptr, obj_desc_list *art_ptr)
{
	pval_info_type *pval_ptr = &art_ptr->pval_info;

	char buf[80];

	/* Don't indent the first line */
	fprintf(fff, "%s\n", art_ptr->description);
	
	/* unidentified */
	if (!(o_ptr->ident & (IDENT_MENTAL)))
	{
#ifdef JP
		fprintf(fff, "%s不明\n",INDENT1);
#else
		fprintf(fff, "%sUnknown\n",INDENT1);
#endif
	}
	else {
		/* An "empty" pval description indicates that the pval affects nothing */
		if (pval_ptr->pval_desc[0])
		{
			/* Mention the effects of pval */
#ifdef JP
			sprintf(buf, "%sの修正:", pval_ptr->pval_desc);
#else
			sprintf(buf, "%s to", pval_ptr->pval_desc);
#endif
			spoiler_outlist(buf, pval_ptr->pval_affects, ITEM_SEP);
		}
	  
		/* Now deal with the description lists */

#ifdef JP
		spoiler_outlist("対:", art_ptr->slays, ITEM_SEP);
		spoiler_outlist("武器属性:", art_ptr->brands, LIST_SEP);
		spoiler_outlist("免疫:", art_ptr->immunities, ITEM_SEP);
		spoiler_outlist("耐性:", art_ptr->resistances, ITEM_SEP);
		spoiler_outlist("維持:", art_ptr->sustains, ITEM_SEP);
#else
		spoiler_outlist("Slay", art_ptr->slays, ITEM_SEP);
		spoiler_outlist("", art_ptr->brands, LIST_SEP);
		spoiler_outlist("Immunity to", art_ptr->immunities, ITEM_SEP);
		spoiler_outlist("Resist", art_ptr->resistances, ITEM_SEP);
		spoiler_outlist("Sustain", art_ptr->sustains, ITEM_SEP);
#endif
		spoiler_outlist("", art_ptr->misc_magic, LIST_SEP);

		/* Write out the possible activation at the primary indention level */
		if (art_ptr->activation)
		{
#ifdef JP
			fprintf(fff, "%s発動: %s\n", INDENT1, art_ptr->activation);
#else
			fprintf(fff, "%sActivates for %s\n", INDENT1, art_ptr->activation);
#endif
		}
	}
	/* End with the miscellaneous facts */
	fprintf(fff, "%s%s\n\n", INDENT1, art_ptr->misc_desc);
}

/* Create a part of file for random artifacts */

static void spoil_random_artifact_aux(object_type *o_ptr, int i)
{
	obj_desc_list artifact;

	if (!object_known_p(o_ptr) || !o_ptr->art_name
		|| o_ptr->tval != group_artifact[i].tval)
		return;

	/* Analyze the artifact */
	random_artifact_analyze(o_ptr, &artifact);

	/* Write out the artifact description to the spoiler file */
	spoiler_print_randart(o_ptr, &artifact);
}

/*
 * Create a list file for random artifacts
 */
void spoil_random_artifact(cptr fname)
{
	int i,j;

	store_type  *st_ptr;
	object_type *q_ptr;

	char buf[1024];


	/* Drop priv's */
	safe_setuid_drop();

	/* Build the filename */
	path_build(buf, 1024, ANGBAND_DIR_USER, fname);

	/* File type is "TEXT" */
	FILE_TYPE(FILE_TYPE_TEXT);

	/* Open the file */
	fff = my_fopen(buf, "w");

	/* Oops */
	if (!fff)
	{
		msg_print("Cannot create list file.");
		return;
	}

	/* Dump the header */
	sprintf(buf, "Random artifacts list.\r");
	spoiler_underline(buf);

	/* List the artifacts by tval */
	for (j = 0; group_artifact[j].tval; j++)
	{
		/* random artifacts wielding */
		for (i = INVEN_RARM; i < INVEN_TOTAL; i++)
		{
			q_ptr = &inventory[i];
			spoil_random_artifact_aux(q_ptr, j);
		}

		/* random artifacts in inventory */
		for (i = 0; i < INVEN_PACK; i++)
		{
			q_ptr = &inventory[i];
			spoil_random_artifact_aux(q_ptr, j);
		}

		/* random artifacts in home */
		st_ptr = &town[1].store[STORE_HOME];
		for (i = 0; i < st_ptr->stock_num; i++)
		{
			q_ptr = &st_ptr->stock[i];
			spoil_random_artifact_aux(q_ptr, j);
		}

		/* random artifacts in museum */
		st_ptr = &town[1].store[STORE_MUSEUM];
		for (i = 0; i < st_ptr->stock_num; i++)
		{
			q_ptr = &st_ptr->stock[i];
			spoil_random_artifact_aux(q_ptr, j);
		}
	}

	/* Check for errors */
	if (ferror(fff) || my_fclose(fff))
	{
		msg_print("Cannot close list file.");
		return;
	}

	/* Grab priv's */
	safe_setuid_grab();

	/* Message */
	msg_print("Successfully created a list file.");
}

#else

#ifdef MACINTOSH
static int i = 0;
#endif /* MACINTOSH */

#endif
