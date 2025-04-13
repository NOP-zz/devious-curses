Scriptname slsw_bd_ISM extends activemagiceffect

imageSpaceModifier property slsw_bd_ISMD auto
SLSW_mcmconfig property MCM auto

event onEffectStart(actor akTarget, actor akCaster)
slsw_bd_ISMD.remove()
if MCM.visuals == true
	slsw_bd_ISMD.apply(1.0)
endif
EndEvent