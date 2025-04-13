Scriptname slsw_sk_drugged extends activemagiceffect  

slsw_mcmconfig property mcm auto
imagespacemodifier property slsw_sk_ISM auto

Event OnEffectStart(actor akTarget, actor akCaster)
slsw_sk_ISM.remove()

if mcm.visuals == true
	slsw_sk_ISM.apply(1.0)
endif

endEvent