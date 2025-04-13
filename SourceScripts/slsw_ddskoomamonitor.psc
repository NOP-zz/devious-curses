Scriptname slsw_DDSkoomaMonitor extends activemagiceffect  

GlobalVariable Property DrugPool_pd  Auto
GlobalVariable Property DrugPool_md  Auto
GlobalVariable Property DrugPool_mkd  Auto
GlobalVariable Property SLSW_AddictionIndicator  Auto
GlobalVariable Property SLSW_DoseCounter  Auto
SLSW_mcmConfig Property MCM  Auto  
SLSW_upkeep Property upkeep Auto
SLSW_BlackoutUpkeep Property Blackout Auto
Race Property KhajiitRace Auto
SPELL Property slsw_ddsk_stage1  Auto
SPELL Property slsw_ddsk_stage2  Auto
SPELL Property slsw_ddsk_stage3  Auto
SPELL Property slsw_ddsk_stage4  Auto
SPELL Property slsw_ddsk_kj_stage1  Auto
SPELL Property slsw_ddsk_kj_stage2  Auto
SPELL Property slsw_ddsk_kj_stage3  Auto
SPELL Property slsw_ddsk_kj_stage4  Auto
SPELL Property slsw_sp_stage1  Auto

Event OnEffectStart(Actor akTarget, Actor akCaster)

float CurrentValue_pd = DrugPool_pd.getValue()

if Game.getPlayer().getActorBase().getRace() == KhajiitRace
	CurrentValue_pd += (5 + (Utility.RandomFloat(1,5)))
else
	CurrentValue_pd += (2 + (Utility.RandomFloat(1,5)))
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
	upkeep.drugged(CurrentValue_pd, slsw_ddsk_kj_stage1, slsw_ddsk_kj_stage2, slsw_ddsk_kj_stage3, slsw_ddsk_kj_stage4)
else
	upkeep.drugged(CurrentValue_pd, slsw_ddsk_stage1, slsw_ddsk_stage2, slsw_ddsk_stage3, slsw_ddsk_stage4)
endif

Game.getPlayer().RemoveSpell(slsw_sp_stage1)

upkeep.suppression_pd(DrugPool_pd.getValue())
upkeep.suppression_md(DrugPool_md.getValue())
upkeep.suppression_mkd(DrugPool_mkd.getValue())

Game.GetPlayer().AddSpell(slsw_sp_stage1, false)

upkeep.UpdateIndicator()

EndEvent