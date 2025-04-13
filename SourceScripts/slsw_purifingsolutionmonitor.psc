Scriptname slsw_PurifingSolutionMonitor extends activemagiceffect  

GlobalVariable Property SLSW_DrugPool_pd  Auto
GlobalVariable Property SLSW_DrugPool_md  Auto
GlobalVariable Property SLSW_DrugPool_mkd  Auto
SLSW_upkeep Property upkeep Auto
SPELL Property SLSW_sp_stage1  Auto
SPELL Property SLSW_pd_stage1  Auto
SPELL Property SLSW_pd_stage2  Auto
SPELL Property SLSW_pd_stage3  Auto
SPELL Property SLSW_pd_stage4  Auto
SPELL Property SLSW_pd_stage5  Auto
SPELL Property SLSW_md_stage1  Auto
SPELL Property SLSW_md_stage2  Auto
SPELL Property SLSW_md_stage3  Auto
SPELL Property SLSW_md_stage4  Auto
SPELL Property SLSW_md_stage5  Auto
SPELL Property SLSW_mkd_stage1  Auto
SPELL Property SLSW_mkd_stage2  Auto
SPELL Property SLSW_mkd_stage3  Auto
SPELL Property SLSW_mkd_stage4  Auto
SPELL Property SLSW_mkd_stage5  Auto

Event OnEffectStart(Actor akTarget, Actor akCaster)

float CurrentValue_mkd = SLSW_DrugPool_mkd.getValue()

CurrentValue_mkd -= 150

if CurrentValue_mkd <= 0
	SLSW_DrugPool_mkd.setValue(0)
else
	SLSW_DrugPool_mkd.setValue(CurrentValue_mkd)
endif

float CurrentValue_md = SLSW_DrugPool_md.getValue()

CurrentValue_md -= 150

if CurrentValue_md <= 0
	SLSW_DrugPool_md.setValue(0)
else
	SLSW_DrugPool_md.setValue(CurrentValue_md)
endif

float CurrentValue_pd = SLSW_DrugPool_pd.getValue()

CurrentValue_pd -= 150

if CurrentValue_pd <= 0
	SLSW_DrugPool_pd.setValue(0)
else
	SLSW_DrugPool_pd.setValue(CurrentValue_pd)
endif

upkeep.getclean(SLSW_DrugPool_pd.getValue(), slsw_pd_stage1, slsw_pd_stage2, slsw_pd_stage3, slsw_pd_stage4, slsw_pd_stage5)
upkeep.getclean(SLSW_DrugPool_md.getValue(), slsw_md_stage1, slsw_md_stage2, slsw_md_stage3, slsw_md_stage4, slsw_md_stage5)
upkeep.getclean(SLSW_DrugPool_mkd.getValue(), slsw_mkd_stage1, slsw_mkd_stage2, slsw_mkd_stage3, slsw_mkd_stage4, slsw_mkd_stage5)

Game.getPlayer().RemoveSpell(SLSW_sp_stage1)

upkeep.suppression_pd(SLSW_DrugPool_pd.getValue())
upkeep.suppression_md(SLSW_DrugPool_md.getValue())
upkeep.suppression_mkd(SLSW_DrugPool_mkd.getValue())

Game.GetPlayer().AddSpell(SLSW_sp_stage1, false)

upkeep.UpdateIndicator()

EndEvent