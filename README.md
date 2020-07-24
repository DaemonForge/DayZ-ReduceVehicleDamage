# DayzSA-ReduceVehicleDamage
This is a simple mod that allows Dayz Standalone server owners to Reduce/Tweak  Car Damage

Link to Published Mod https://steamcommunity.com/sharedfiles/filedetails/?id=2117984167

This is a simple mod that reduces the damage taken by vehicles in Dayz when vehicles crash, this should work on most vehicles, this is my first mod so there may be bugs please report them to me I'll try my best to fix them

There is a config file that will be created on first start that allows you to modify the values
```
{
    "dmgModifier": 0.8,    //Damage Modifier for vehicles
    "mindmg": 1350,        //Minimum Damage vehicles would have to take to received damage
    "subtractmindmg": 1,       //1 Enabled/0 Disabled If enabled it will subtract the minimum damage from the total damage
    "nodmgifoff": 0   // 1 Enabled/0 Disabled If enabled the Vehicle will not take damage if the Vehicle is off
    "helidmgModifier": 0.7,   //Damage Modifier for Helis
    "helimindmg": 1300,       //Minimum Damage Helis would have to take to received damage
	"debugLogs": 0 // 1 Enabled/0 Disabled This is for debugging the mod, I'd highly recommend disabling this always
}
```

### Repacking/Building from Source Code Rules
For anyone interested in repacking please read all this
- 1st I heavily discourage Repacking/Building from my source code, as it would greatly impact your ability to receive feature updates and bug fixes
- 2nd I will not support any repacks if its is causing conflict that I can't reproduce with the my published mod 
- 3rd YOU MUST PROVIDE CREDIT on the steam page and you must link to the Orginal Mod or the Source Code
- 4th Any repacks or builds can only be for personal use no redistributing my mod for public use, should only be for your own servers and players and you must be able to enfore this
- 5th Please ask for permission prior to repacking, almost all request will be approved as long as you have a valid reason to repack
- 6th Also note that the Source Code is the activly developing version so it may not work as it sits here right now so just be warnned.
- 7th Must include the NOTICE file in side the mod with out modification to my text
