Scriptname slsw_badpotion_monitor extends ActiveMagicEffect  

GlobalVariable Property SLSW_DrugPool_pd  Auto
GlobalVariable Property SLSW_DrugPool_md  Auto
GlobalVariable Property SLSW_DrugPool_mkd  Auto
GlobalVariable Property SLSW_AddictionIndicator  Auto
float property DrugStrenght auto
SLSW_mcmConfig Property MCM  Auto  
SLSW_upkeep Property upkeep Auto

Event OnEffectStart(Actor akTarget, Actor akCaster)

float CurrentValue_pd = SLSW_DrugPool_pd.getValue()

CurrentValue_pd += DrugStrenght + Utility.RandomFloat(1,3)

SLSW_DrugPool_pd.setValue(CurrentValue_pd)

upkeep.UpdateIndicator()

EndEvent