Scriptname SLSW_double extends Quest  

SexLabFramework Property SexLab Auto
ReferenceAlias Property Dealer Auto

Event Double(string eventName, string argString, float argNum, form sender)
Utility.Wait(2)
actor[] sexActors = new actor[2]
    sexActors[0] = Game.GetPlayer()
    sexActors[1] = Dealer.getRef() as Actor

sslBaseAnimation[] anims = SexLab.GetAnimationsByTags(2, "Anal, Aggressive", TagSuppress = "", RequireAll = true)

SexLab.StartSex(sexActors, anims)

UnregisterForModEvent("Double")

EndEvent

Event Turn(string eventName, string argString, float argNum, form sender)
Utility.Wait(2)
actor[] sexActors = new actor[2]
    sexActors[0] = Game.GetPlayer()
    sexActors[1] = Dealer.getRef() as Actor

sslBaseAnimation[] anims = SexLab.GetAnimationsByTags(2, "Aggressive", TagSuppress = "", RequireAll = true)

SexLab.StartSex(sexActors, anims)

UnregisterForModEvent("Turn")

EndEvent

Function DoubleOne()

RegisterForModEvent("AnimationEnd_Double", "Double")

actor[] sexActors = new actor[2]
    sexActors[0] = Game.GetPlayer()
    sexActors[1] = Dealer.getRef() as Actor

sslBaseAnimation[] anims = SexLab.GetAnimationsByTags(2, "Anal, Aggressive", TagSuppress = "", RequireAll = true)

SexLab.StartSex(sexActors, anims, Hook="Double")

endFunction

Function TurnOne()

RegisterForModEvent("AnimationEnd_Turn", "Turn")

actor[] sexActors = new actor[2]
    sexActors[0] = Game.GetPlayer()
    sexActors[1] = Dealer.getRef() as Actor

sslBaseAnimation[] anims = SexLab.GetAnimationsByTags(2, "Aggressive", TagSuppress = "", RequireAll = true)

SexLab.StartSex(sexActors, anims, Hook="Turn")

endFunction