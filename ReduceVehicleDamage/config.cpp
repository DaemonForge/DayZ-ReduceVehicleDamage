class CfgPatches
{
	class ReduceVehicleDamage
	{
		requiredVersion=0.1;
		requiredAddons[]={
			"DayZExpansion_Scripts"
		};
	};
};

class CfgMods
{
	class ReduceVehicleDamage
	{
		dir="ReduceVehicleDamage";
        picture="";
        action="";
        hideName=1;
        hidePicture=1;
        name="ReduceVehicleDamage";
        credits="DaemonForge";
        author="DaemonForge";
        authorID="0";
        version="0.1";
        extra=0;
        type="mod";
	    dependencies[]={ "Game","World" };
	    class defs
	    {
			class gameScriptModule
            {
                value="";
                files[]={"ReduceVehicleDamage/scripts/3_Game"};
            };
	        class worldScriptModule
            {
                value="";
                files[]={ "ReduceVehicleDamage/scripts/4_world" };
            };
        };
    };
};
