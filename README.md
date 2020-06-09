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
