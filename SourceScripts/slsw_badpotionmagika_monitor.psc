Scriptname slsw_badpotionMagika_monitor extends ActiveMagicEffect  

GlobalVariable Property SLSW_DrugPool_pd  Auto
GlobalVariable Property SLSW_DrugPool_md  Auto
GlobalVariable Property SLSW_DrugPool_mkd  Auto
GlobalVariable Property SLSW_AddictionIndicator  Auto
float property DrugStrenght auto
SLSW_mcmConfig Property MCM  Auto  
SLSW_upkeep Property upkeep Auto

Event OnEffectStart(Actor akTarget, Actor akCaster)

float CurrentValue_mkd = SLSW_DrugPool_mkd.getValue()

CurrentValue_mkd += DrugStrenght + Utility.RandomFloat(1,3)

SLSW_DrugPool_mkd.setValue(CurrentValue_mkd)

upkeep.UpdateIndicator()

EndEvent