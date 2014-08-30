#pragma once
#include "SpellDefines.h"
#include "Pawn.h"
#include "AIController.h"
#include <cstdint>
#include <vector>
#include <string>

/*
class SpellEffectScript {
	public:

	    void operator() (AActor*) {

	    }

	private:
	SpellEffectCategory
};

struct SpellInfo {
	    //spell category info
	    SpellCategory m_spell_category;
		SpellEffectCategory m_spell_effect_category;

		std::tstring m_spell_name;
		uint64_t m_spell_ID;

#pragma region spell_attributes
		bool m_isPassive;                                  //whether this spell is passive
		bool m_isToggledOn;                                //if this spell is passive, is it toggled on

		float m_duration;                                  //how long will the spell effect last, in second
		bool m_isPeriodic;                                 //whether the spell effect comes periodically
		float m_secPerTick;                                //tick frequency

		float m_base_damage;                               //the type of amount change depends on the spell category
		                                                   //if this is damage spell, target's health pool will be decreased by amount_change
		                                                   //if this is slow spell, target's speed will be decreased by amount_change, etc.
		                                                   //Note: this is only a base_amount_change, SpellModifier will calculate the actual change
		                                                   //please refer to class SpellModifier
		
		float m_cast_time;
		bool m_isChanneled;                                //whether this spell need to be channeled
		float m_channelPeriod;                             //if this spell need to be channeled, how long does it take between ticks

		float m_power_required;                            //mana, rage or focus required
		int16_t m_percent_power_required;                  //percent of total mana, rage or focus required

		float m_cooldown;

		//spell distance info
		float m_max_spell_distance;                        //e.g. 45 yard for hunter
		float m_min_spell_distance;                        //e.g. 5 yard for hunter
#pragma endregion spell_attributes

		SpellTargetCategory m_spell_target_type;           //Single(e.g. frost bolt), AOE(e.g. blizzard), no_target(e.g. summon water element)

		//spell trajectory, box2d stuff
		bool m_hasTrajectory;
		//...

		bool m_isAuraTrigger;                              //does this spell trigger Aura
		Spell* m_TriggeringAura;                           //if this spell will trigger Aura, name that aura

		//launch method info
		bool m_needSelectTarget;                           //whether caster need to select target to cast spell
		LaunchMethodCategory m_launch_method;
		float m_aoe_radius;                                //if this spell is area-oriented, this is the radius
		float m_line_width;                                //if this spell is direction-oriented, this is the width of rectangle

		//cast method info
		bool m_isMoveableWhileCasting;

		//spell visual, hgeanim stuff
};

class Spell : public Pawn {
	public:
	    Spell();

		Spell(AActor* caster, SpellInfo* spell_info)
			: m_caster(caster), m_spell_info(spell_info) {}

		void calculateTargets();

		void calculateAmountChange();

		bool isLaunchable();

		bool hitTarget();

		void applySpellEffect();

		void Update(float);

		void Render(float, float);

	private:
	    AActor* m_caster;
		std::vector<AActor*> m_targets;
		SpellInfo* m_spell_info;
		//Environment variables
		std::vector<float> m_actual_amount_change;
};

class SpellController : public AIController {
	public:
	    SpellController();


	private:
	    SpellEffectCategory

};
//*/