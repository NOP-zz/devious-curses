Scriptname slsw_mf_ISMscript extends activemagiceffect  

imageSpaceModifier property slsw_mf_ISM auto
imageSpaceModifier property slsw_mflight_ISM auto
slsw_mcmconfig property mcm auto

event onEffectStart(actor akTarget, actor akCaster)
slsw_mf_ISM.remove()
slsw_mflight_ISM.remove()

if mcm.visuals == true
	if mcm.mf_light == "Normal"
		slsw_mf_ISM.apply(1.0)
	elseif mcm.mf_light == "Light"
		slsw_mflight_ISM.apply(1.0)
	endif
endif

EndEvent