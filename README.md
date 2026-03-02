# NoCarDamage
This is a DayZ Mod that aims to make vehicles customizable

You can disable or fine-tune damage for vehicles and players while inside vehicles.
Stop vehicles from taking crash damage, bullet damage, explosion damage, and more — and protect passengers and vehicle attachments as well.

The mod generates a config file on first start, so you can quickly enable/disable features globally and override them per vehicle class.
If you want player not drown from water damage, change Vanilla drown settings in cfggameplaysettings.json.
_______________________________________________________________


How the config works

On first run the mod generates:
$profile:NoCarDamage\NoCarDamage_Config.json

You can:
- Set global rules (apply to all vehicles)
- Enable VehicleOverrides to override rules per vehicle class
- Use AutoExtendVehicleOverrides to automatically populate overrides for new vehicles, do your changes and set it to 0 and it will delete all unneeded entries, to reduce impact on server perfomance.

Override values:
1 = enabled
0 = disabled
-1 = inherit the global setting
_______________________________________________________________


Installation / Server Notes

Load it on the server like any other Workshop mod.

Works with vanilla vehicles and modded vehicles (using class names).
After the first start it generates a config file.
Change the settings how you like and restart the server.

Monetization
You are allowed to use this mod on monetized severs, as long as you follow BI rules. No pay to win.

Repack, unpack, change, etc. is allowed

You are not allowed to sell any part of this code.
