Scriptname SLSW_SkoomaMonitor extends activemagiceffect  

GlobalVariable Property DrugPool_pd  Auto
GlobalVariable Property DrugPool_md  Auto
GlobalVariable Property DrugPool_mkd  Auto
GlobalVariable Property SLSW_AddictionIndicator  Auto
GlobalVariable Property SLSW_DoseCounter  Auto
SLSW_mcmConfig Property MCM  Auto  
SLSW_upkeep Property upkeep Auto
SLSW_BlackoutUpkeep Property Blackout Auto
Race Property KhajiitRace Auto
SPELL Property sk1  Auto
SPELL Property sk2  Auto
SPELL Property sk3  Auto
SPELL Property sk4  Auto
SPELL Property skkj1  Auto
SPELL Property skkj2  Auto
SPELL Property skkj3  Auto
SPELL Property skkj4  Auto
SPELL Property sp1  Auto

Event OnEffectStart(Actor akTarget, Actor akCaster)

float CurrentValue_pd = DrugPool_pd.getValue()

if Game.getPlayer().getActorBase().getRace() == KhajiitRace
	CurrentValue_pd += (12 + (Utility.RandomFloat(1,5)))
else
	CurrentValue_pd += (7 + (Utility.RandomFloat(1,5)))
endif

	If MCM.HighRisk == true && Utility.RandomInt(1, 100) <= MCM.HRchance && SLSW_AddictionIndicator.getValue() <= 1
		CurrentValue_pd += 100
	endif

DrugPool_pd.setValue(CurrentValue_pd)

if MCM.blackout == true
	Float dose = SLSW_DoseCounter.getValue()
	dose += 1
	SLSW_DoseCounter.setValue(dose)
	
	Blackout.Overdose(Utility.getCurrentGameTime())
endif

if Game.getPlayer().getActorBase().getRace() == KhajiitRace
	upkeep.drugged(CurrentValue_pd, skkj1, skkj2, skkj3, skkj4)
else
	upkeep.drugged(CurrentValue_pd, sk1, sk2, sk3, sk4)
endif

Game.getPlayer().RemoveSpell(sp1)

upkeep.suppression_pd(DrugPool_pd.getValue())
upkeep.suppression_md(DrugPool_md.getValue())
upkeep.suppression_mkd(DrugPool_mkd.getValue())

Game.GetPlayer().AddSpell(sp1, false)

upkeep.UpdateIndicator()

EndEvent