Scriptname slsw_LeafSkoomaMonitor extends activemagiceffect  

GlobalVariable Property DrugPool_pd  Auto
GlobalVariable Property DrugPool_md  Auto
GlobalVariable Property DrugPool_mkd  Auto
GlobalVariable Property SLSW_AddictionIndicator  Auto
GlobalVariable Property SLSW_DoseCounter  Auto
SLSW_mcmConfig Property MCM  Auto  
SLSW_upkeep Property upkeep Auto
SLSW_BlackoutUpkeep Property Blackout Auto
Race Property KhajiitRace Auto
SPELL Property slsw_leafskooma_1  Auto
SPELL Property slsw_leafskooma_2  Auto
SPELL Property slsw_leafskooma_3  Auto
SPELL Property slsw_leafskooma_4  Auto
SPELL Property slsw_leafskooma_kj_1  Auto
SPELL Property slsw_leafskooma_kj_2  Auto
SPELL Property slsw_leafskooma_kj_3  Auto
SPELL Property slsw_leafskooma_kj_4  Auto
SPELL Property sp1  Auto

Event OnEffectStart(Actor akTarget, Actor akCaster)

float CurrentValue_pd = DrugPool_pd.getValue()

if Game.getPlayer().getActorBase().getRace() == KhajiitRace
	CurrentValue_pd += (48 + (Utility.RandomFloat(0,4)))
else
	CurrentValue_pd += (38 + (Utility.RandomFloat(0,4)))
endif

	If MCM.HighRisk == true && Utility.RandomInt(1, 100) <= MCM.HRchance && SLSW_AddictionIndicator.getValue() <= 1

		CurrentValue_pd += 120
	endif

DrugPool_pd.setValue(CurrentValue_pd)

if MCM.blackout == true
	Float dose = SLSW_DoseCounter.getValue()
	dose += 1
	SLSW_DoseCounter.setValue(dose)
	
	Blackout.Overdose(Utility.getCurrentGameTime())
endif

if Game.getPlayer().getActorBase().getRace() == KhajiitRace
	upkeep.drugged(CurrentValue_pd, slsw_leafskooma_kj_1, slsw_leafskooma_kj_2, slsw_leafskooma_kj_3, slsw_leafskooma_kj_4)
else
	upkeep.drugged(CurrentValue_pd, slsw_leafskooma_1, slsw_leafskooma_2, slsw_leafskooma_3, slsw_leafskooma_4)
endif

Game.getPlayer().RemoveSpell(sp1)

upkeep.suppression_pd(DrugPool_pd.getValue())
upkeep.suppression_md(DrugPool_md.getValue())
upkeep.suppression_mkd(DrugPool_mkd.getValue())

Game.GetPlayer().AddSpell(sp1, false)

upkeep.UpdateIndicator()

EndEvent