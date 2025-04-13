Scriptname slsw_ef_ISMscript extends activemagiceffect

imageSpaceModifier property slsw_ef_ISM auto
SLSW_mcmconfig property MCM auto

event onEffectStart(actor akTarget, actor akCaster)
	slsw_ef_ISM.remove()
if mcm.visuals == true
	slsw_ef_ISM.apply(1.0)
endif
EndEvent
