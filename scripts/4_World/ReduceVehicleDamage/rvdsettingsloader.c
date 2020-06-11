static string ReduceVehicleDamageDIR = "$profile:ReduceVehicleDamage";
static string ReduceVehicleDamagePATH = ReduceVehicleDamageDIR + "\\config.json";

class ReduceVehicleDamageSettings
{
    private static bool initialized = false;
    private static ref ReduceVehicleDamageSettings settings;

	//Default Values
        float dmgModifier = 0.8;
	float mindmg = 1350;
	bool subtractmindmg = true;
	bool nodmgifoff = false;
	bool perventcarruined = false;
	
        float helidmgModifier = 0.7;
	float helimindmg = 1300;
	bool noexplodeifoff = false;
	
	bool debugLogs = false;

	
    static ref ReduceVehicleDamageSettings Get()
    {
        if (initialized)
        {
            return settings;
        }

        ref ReduceVehicleDamageSettings data = new ref ReduceVehicleDamageSettings;
		
        if (FileExist(ReduceVehicleDamagePATH)) //If config file exsit load the file
        {
            JsonFileLoader<ReduceVehicleDamageSettings>.JsonLoadFile(ReduceVehicleDamagePATH, data);
            initialized = true;
		if (!data.helidmgModifier){ //Update settings file with now settings
			data.perventcarruined = false;
			data.helidmgModifier = data.dmgModifier;
		        data.helimindmg = data.mindmg;
			data.noexplodeifoff = false;
			data.debugLogs = false;
             		JsonFileLoader<ReduceVehicleDamageSettings>.JsonSaveFile(ReduceVehicleDamagePATH, data);
		}
        }
        else //If config file doesn't exsit create the file
        {
			
            if (GetGame().IsServer() || !GetGame().IsMultiplayer())
            {
                MakeDirectory(ReduceVehicleDamageDIR);
                JsonFileLoader<ReduceVehicleDamageSettings>.JsonSaveFile(ReduceVehicleDamagePATH, data);
            }
        }

        settings = data;

        return settings;
    }
}
