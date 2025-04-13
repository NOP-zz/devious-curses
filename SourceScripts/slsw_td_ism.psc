Scriptname slsw_td_ISM extends activemagiceffect  

imageSpaceModifier property slsw_td_ISMD auto
slsw_mcmconfig property mcm auto

event onEffectStart(actor akTarget, actor akCaster)
slsw_td_ISMD.remove()
if mcm.visuals == true
		slsw_td_ISMD.apply(1.0)
endif
EndEvent
