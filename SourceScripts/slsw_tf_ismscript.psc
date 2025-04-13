Scriptname slsw_tf_ISMscript extends activemagiceffect  

imageSpaceModifier property slsw_tf_ISM auto
slsw_mcmconfig property mcm auto

event onEffectStart(actor akTarget, actor akCaster)
slsw_tf_ISM.remove()
if mcm.visuals == true
	slsw_tf_ISM.apply(1.0)
endif
EndEvent