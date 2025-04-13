Scriptname slsw_HerbTeaMonitor extends activemagiceffect  

GlobalVariable Property SLSW_DrugPool_pd  Auto
GlobalVariable Property SLSW_DrugPool_md  Auto
GlobalVariable Property SLSW_DrugPool_mkd  Auto
SLSW_upkeep Property upkeep Auto
SPELL Property SLSW_pd_stage1 auto
SPELL Property SLSW_pd_stage2 auto
SPELL Property SLSW_pd_stage3 auto
SPELL Property SLSW_pd_stage4 auto
SPELL Property SLSW_pd_stage5 auto
SPELL Property SLSW_md_stage1 auto
SPELL Property SLSW_md_stage2 auto
SPELL Property SLSW_md_stage3 auto
SPELL Property SLSW_md_stage4 auto
SPELL Property SLSW_md_stage5 auto
SPELL Property SLSW_mkd_stage1 auto
SPELL Property SLSW_mkd_stage2 auto
SPELL Property SLSW_mkd_stage3 auto
SPELL Property SLSW_mkd_stage4 auto
SPELL Property SLSW_mkd_stage5 auto

Event OnEffectStart(Actor akTarget, Actor akCaster)

float CurrentValue_pd = SLSW_DrugPool_pd.getValue()

CurrentValue_pd -= 6 + Utility.RandomFloat(0,4)

If CurrentValue_pd <= 0
	SLSW_DrugPool_pd.setValue(0)
else
	SLSW_DrugPool_pd.setValue(CurrentValue_pd)
endif

float CurrentValue_md = SLSW_DrugPool_md.getValue()

CurrentValue_md -= 6 + Utility.RandomFloat(0,4)

If CurrentValue_md <= 0
	SLSW_DrugPool_md.setValue(0)
else
	SLSW_DrugPool_md.setValue(CurrentValue_md)
endif


float CurrentValue_mkd = SLSW_DrugPool_mkd.getValue()

CurrentValue_mkd -= 6 + Utility.RandomFloat(0,4)

If CurrentValue_mkd <= 0
	SLSW_DrugPool_mkd.setValue(0)
else
	SLSW_DrugPool_mkd.setValue(CurrentValue_mkd)
endif

upkeep.getclean(SLSW_DrugPool_pd.getValue(), slsw_pd_stage1, slsw_pd_stage2, slsw_pd_stage3, slsw_pd_stage4, slsw_pd_stage5)
upkeep.getclean(SLSW_DrugPool_md.getValue(), slsw_md_stage1, slsw_md_stage2, slsw_md_stage3, slsw_md_stage4, slsw_md_stage5)
upkeep.getclean(SLSW_DrugPool_mkd.getValue(), slsw_mkd_stage1, slsw_mkd_stage2, slsw_mkd_stage3, slsw_mkd_stage4, slsw_mkd_stage5)

upkeep.UpdateIndicator()

EndEvent
