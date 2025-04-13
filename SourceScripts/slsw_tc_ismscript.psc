Scriptname slsw_TC_ISMscript extends activemagiceffect  

imageSpaceModifier property slsw_tc_ISM auto
slsw_mcmconfig property mcm auto

event onEffectStart(actor akTarget, actor akCaster)
slsw_tc_ISM.remove()
if mcm.visuals == true
	slsw_tc_ISM.apply(1.0)
endif
EndEvent