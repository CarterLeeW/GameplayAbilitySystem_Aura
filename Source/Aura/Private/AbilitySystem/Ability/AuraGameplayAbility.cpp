// Copyright Carter Wooton


#include "AbilitySystem/Ability/AuraGameplayAbility.h"
#include "AbilitySystem/AuraAttributeSet.h"

FString UAuraGameplayAbility::GetDescription(int32 Level) const
{
	return FString::Printf(TEXT("<Default>%s, </><Level>%d</>"), 
		L"Default Ability Name -  LoremIpsum LoremIpsum LoremIpsum", Level);
}

FString UAuraGameplayAbility::GetNextLevelDescription(int32 Level) const
{
	return FString::Printf(TEXT("<Default>%s, </><Level>%d</>"),
		L"NextLevel - Causes much more damage", Level+1);
}

FString UAuraGameplayAbility::GetLockedDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Spell locked until next level: %d</>"), Level);
}

float UAuraGameplayAbility::GetManaCost(float InLevel) const
{
	float ManaCost = 0.f;
	if (const UGameplayEffect* CostEffect = GetCostGameplayEffect())
	{
		for (const FGameplayModifierInfo& Mod : CostEffect->Modifiers)
		{
			if (Mod.Attribute == UAuraAttributeSet::GetManaAttribute())
			{
				Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, ManaCost);
				break;
			}
		}
	}
	return ManaCost;
}

float UAuraGameplayAbility::GetCooldown(float InLevel) const
{
	float Cooldown = 0.f;
	if (const UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect())
	{
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel, Cooldown);
	}
	return Cooldown;
}
