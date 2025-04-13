Scriptname slsw_VerminasPriceDrugges extends activemagiceffect  

imageSpaceModifier property slsw_vp_ISM auto
imageSpaceModifier property slsw_vplight_ISM auto
slsw_mcmconfig property MCM auto

event onEffectStart(actor akTarget, actor akCaster)
slsw_vp_ISM.remove()
slsw_vplight_ISM.remove()
if mcm.visuals == true
if MCM.vp_light == "Normal"
	slsw_vp_ISM.apply(1.0)
elseif MCM.vp_light == "Light"
	slsw_vplight_ISM.apply(1.0)
endif
endif

EndEvent