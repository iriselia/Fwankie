//common defines

enum SpellCategory {
	//magical
	SPELL_CATE_Arcane       = 0x0001,
	SPELL_CATE_Holy         = 0x0002,
	SPELL_CATE_Demonic      = 0x0004,
	//elemental & natural
	SPELL_CATE_Fire         = 0x0008,
	SPELL_CATE_Frost        = 0x0010,         //Also include water
	SPELL_CATE_Natural      = 0x0020,
	SPELL_CATE_Earth        = 0x0040,
	SPELL_CATE_Celestial    = 0x0080,
	SPELL_CATE_Lightening   = 0x0100,
	SPELL_CATE_Storm        = 0x0200,
	//physical
	SPELL_CATE_Sword        = 0x0400,         //1H_sword, 2H_sword
	SPELL_CATE_Mace         = 0x0800,         //1H_mace, 2H_mace
	SPELL_CATE_AXE          = 0x1000,         //1H_axe, 2H_axe
	SPELL_CATE_Spear        = 0x2000,         //2H_spear, 2H_lance
	SPELL_CATE_Bow          = 0x4000,         //2H_bow, 2H_gun
	SPELL_CATE_Shield       = 0x8000          //1H_shield
};

enum SpellEffectCategory {
	SPELL_EFFECT_DAMAGE       = 0x01,
	SPELL_EFFECT_HEAL         = 0x02,
	SPELL_EFFECT_AURA         = 0x04,         //Include slow, accelerate and other attributes change (buff/debuff)
	SPELL_EFFECT_AURATRIGGER  = 0x08,

	//SPELL_EFFECT_CC(Crowd Control)
	SPELL_EFFECT_ROOT         = 0x10,
	SPELL_EFFECT_STUN         = 0x20,
	SPELL_EFFECT_DISORIENT    = 0x40,

	SPELL_EFFECT_SUMMON       = 0x80
};

enum SpellTargetCategory {
	SPELL_TARGET_NONE         = 0,           //No target
	SPELL_TARGET_SINGLE       = 1,
	SPELL_TARGET_AOE          = 2
};

#define SPELL_TARGET_MAX        3

enum LaunchMethodCategory {
	LAUNCH_TARGET_ORIENTED    = 0,
	LAUNCH_AREA_ORIENTED      = 1,
	LAUNCH_DIRECTION_ORIENTED = 2
};

#define LAUNCH_METHOD_MAX       3