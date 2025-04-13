Scriptname slsw_tam_ISMDscript extends activemagiceffect  

imageSpaceModifier property slsw_tam_ISM auto
imageSpaceModifier property slsw_tamlight_ISM auto
slsw_mcmconfig property mcm auto


event onEffectStart(actor akTarget, actor akCaster)
slsw_tam_ISM.remove()
slsw_tamlight_ISM.remove()

if mcm.visuals == true
if mcm.tam_light == "Normal"
	slsw_tam_ISM.apply(1.0)
elseif mcm.tam_light == "Light"
	slsw_tamlight_ISM.apply(1.0)
endif
endif
EndEvent
