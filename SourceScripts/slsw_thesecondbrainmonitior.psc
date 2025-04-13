Scriptname slsw_TheSecondBrainMonitior extends activemagiceffect  

GlobalVariable Property SLSW_DrugPool_pd  Auto
GlobalVariable Property SLSW_DrugPool_md  Auto
GlobalVariable Property SLSW_DrugPool_mkd  Auto
GlobalVariable Property SLSW_DoseCounter  Auto
GlobalVariable Property SLSW_AddictionIndicator  Auto
SLSW_mcmConfig Property MCM  Auto  
SLSW_upkeep Property upkeep Auto
SLSW_BlackoutUpkeep Property Blackout Auto
SPELL Property slsw_tsb_stage1  Auto
SPELL Property slsw_tsb_stage2  Auto
SPELL Property slsw_tsb_stage3  Auto
SPELL Property slsw_tsb_stage4  Auto
SPELL Property SLSW_sp_stage1  Auto

Event OnEffectStart(Actor akTarget, Actor akCaster)

float CurrentValue_pd = SLSW_DrugPool_pd.getValue()

CurrentValue_pd += 16 + Utility.RandomFloat(1,3)

	If MCM.HighRisk == true && Utility.RandomInt(1, 100) <= MCM.HRchance && SLSW_AddictionIndicator.getValue() <= 1
		CurrentValue_pd += 150
	endif

SLSW_DrugPool_pd.setValue(CurrentValue_pd)

float CurrentValue_md = SLSW_DrugPool_md.getValue()

CurrentValue_md += 19 + Utility.RandomFloat(1,6)

	If MCM.HighRisk == true && Utility.RandomInt(1, 100) <= MCM.HRchance && SLSW_AddictionIndicator.getValue() <= 1
		CurrentValue_md += 200
	endif

SLSW_DrugPool_md.setValue(CurrentValue_md)

float CurrentValue_mkd = SLSW_DrugPool_mkd.getValue()

CurrentValue_mkd += 17 + Utility.RandomFloat(1,6)

	If MCM.HighRisk == true && Utility.RandomInt(1, 100) <= MCM.HRchance && SLSW_AddictionIndicator.getValue() <= 1
		CurrentValue_mkd += 200
	endif

SLSW_DrugPool_mkd.setValue(CurrentValue_mkd)

if MCM.blackout == true
	Float dose = SLSW_DoseCounter.getValue()
	dose += 1
	SLSW_DoseCounter.setValue(dose)
	
	Blackout.Overdose(Utility.getCurrentGameTime())
endif

upkeep.drugged(CurrentValue_pd, slsw_tsb_stage1, slsw_tsb_stage2, slsw_tsb_stage3, slsw_tsb_stage4)

Game.getPlayer().RemoveSpell(SLSW_sp_stage1)

upkeep.suppression_pd(SLSW_DrugPool_pd.getValue())
upkeep.suppression_md(SLSW_DrugPool_md.getValue())
upkeep.suppression_mkd(SLSW_DrugPool_mkd.getValue())

Game.GetPlayer().AddSpell(SLSW_sp_stage1, false)

upkeep.UpdateIndicator()

EndEvent