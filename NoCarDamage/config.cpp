class CfgPatches
{
	class NoCarDamage
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Scripts"};
	};
};
class CfgMods
{
	class NoCarDamage
	{
		dir = "NoCarDamage";
		name = "NoCarDamage";
		type = "mod";
		inputs = "NoCarDamage/data/inputs.xml";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"NoCarDamage/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"NoCarDamage/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"NoCarDamage/scripts/5_Mission"};
			};
		};
	};
};
