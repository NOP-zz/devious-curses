Scriptname slsw_roa_drugged extends activemagiceffect  

imagespacemodifier property slsw_roa_ISM auto
slsw_mcmconfig property mcm auto

Event OnEffectStart(actor akTarget, actor akCaster)
slsw_roa_ISM.remove()
if mcm.visuals == true
	slsw_roa_ISM.apply(1.0)
endif

endEvent