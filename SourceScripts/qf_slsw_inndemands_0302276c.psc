;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
;NEXT FRAGMENT INDEX 5
Scriptname QF_SLSW_InnDemands_0302276C Extends Quest Hidden

;BEGIN ALIAS PROPERTY Innkeeper
;ALIAS PROPERTY TYPE ReferenceAlias
ReferenceAlias Property Alias_Innkeeper Auto
;END ALIAS PROPERTY

;BEGIN FRAGMENT Fragment_0
Function Fragment_0()
;BEGIN CODE
Utility.Wait(1)

If (Alias_InnKeeper.getRef() as actor) != none
self.setStage(10)
else
;Debug.Notification("None!")
stop()
endif
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_3
Function Fragment_3()
;BEGIN CODE
Utility.Wait(1)
(Alias_InnKeeper.getRef() as actor).EvaluatePackage()
main.time = (Utility.GetCurrentGameTime() * 24)
main.leave()
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment

SLSW_IDScript Property Main auto
