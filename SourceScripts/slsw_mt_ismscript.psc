Scriptname slsw_mt_ismscript extends activemagiceffect  

imageSpaceModifier property slsw_mt_ISM auto
slsw_mcmconfig property mcm auto

event onEffectStart(actor akTarget, actor akCaster)
slsw_mt_ISM.remove()
	if mcm.visuals == true
		slsw_mt_ISM.apply(1.0)
	endif
EndEvent
