class CfgPatches
{
	class ReduceVehicleDamage
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={};
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
	    dependencies[]={ "World" };
	    class defs
	    {
	        class worldScriptModule
            {
                value="";
                files[]={ "ReduceVehicleDamage/scripts/4_world" };
            };
        };
    };
};
