Scriptname slsw_badpotionstamina_monitor extends activemagiceffect  

GlobalVariable Property SLSW_DrugPool_pd  Auto
GlobalVariable Property SLSW_DrugPool_md  Auto
GlobalVariable Property SLSW_DrugPool_mkd  Auto
GlobalVariable Property SLSW_AddictionIndicator  Auto
float property DrugStrenght auto
float property DrugStrenght2 auto
SLSW_mcmConfig Property MCM  Auto  
SLSW_upkeep Property upkeep Auto

Event OnEffectStart(Actor akTarget, Actor akCaster)

float CurrentValue_pd = SLSW_DrugPool_pd.getValue()

CurrentValue_pd += DrugStrenght + Utility.RandomFloat(1,3)

SLSW_DrugPool_pd.setValue(CurrentValue_pd)

float CurrentValue_md = SLSW_DrugPool_md.getValue()

CurrentValue_md += DrugStrenght2 + Utility.RandomFloat(1,3)

SLSW_DrugPool_md.setValue(CurrentValue_md)

upkeep.UpdateIndicator()

EndEvent
