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

Config Options Explained

Vehicle (damage taken by the vehicle)
"Vehicle_BlockBullets": 1, // Blocks bullet damage to vehicles.
"Vehicle_BlockExplosions": 1, // Blocks explosion damage to vehicles.
"Vehicle_BlockMelee": 1, // Blocks melee damage to vehicles.
"Vehicle_AllowGlassDamage": 0, // Allows vehicle glass to still take damage.
"Vehicle_DisableCrashDamage": 1, // Disables collision/crash damage on vehicles.
"Vehicle_DisableWaterDamage": 1, // Prevents water from damaging vehicles.
"Vehicle_BlockContaminated": 0, // Protects vehicles from contaminated/gas damage.
"Vehicle_DisableRedlineDamage": 1, // Prevents engine damage from over-revving/redline.
"Vehicle_BlockCrewCrashDamage": 1, // Prevents crash damage to vehicle occupants.
"Vehicle_EnableCrashSounds": 1, // Keeps normal crash sound effects enabled.
"Vehicle_NoDamageToZombies": 0, // Vehicles do not damage zombies on impact.
"Vehicle_NoDamageToAnimals": 0, // Vehicles do not damage animals on impact.
"Vehicle_NoDamageToPlayers": 0, // Vehicles do not damage players on impact.
"Vehicle_NoDamageToExpansionAI": 0, // Vehicles do not damage Expansion AI/NPCs on impact.
"Vehicle_AutoFlip": 0, // Automatically flips overturned vehicles upright.
"Vehicle_AutoFlipWithButton": 0, // Allows vehicles to be flipped with a key/button default H.
"Protect_AttachmentsOnVehicle": 1 // Protects attached vehicle parts from damage (when applicable).

Player (damage taken by players inside vehicles)
"Player_BlockContaminatedWhileInVehicle": 0, // Protects players from gas while inside vehicles.
"Player_DoorOpenDisablesProtectionInContaminated": 1, // Disables gas protection for players if a vehicle door is open.
"Player_NoDamageWhileInVehicle": 1, // Enables Player crash protection while inside vehicles.
"Player_BlockAllDamageWhileInVehicle": 0, // Blocks all damage to players while inside vehicles.
"Player_BlockBulletsWhileInVehicle": 0, // Blocks bullet damage to players while inside vehicles.
"Player_BlockExplosionsWhileInVehicle": 0, // Blocks explosion damage to players while inside vehicles.
"Player_BlockMeleeWhileInVehicle": 0, // Blocks melee damage to players while inside vehicles.
"Player_NoDamageAfterJumpFromVehicle": 0, // Protects players from damage shortly after jumping out.

Expansion AI NPC(damage taken by players inside vehicles)
"ExpansionAI_NoDamageWhileInVehicle": 0, // Enables Expansion AI/NPC protection while inside vehicles.
"ExpansionAI_BlockAllDamageWhileInVehicle": 0, // Blocks all damage to Expansion AI/NPCs while inside vehicles.
"ExpansionAI_BlockBulletsWhileInVehicle": 0, // Blocks bullet damage to Expansion AI/NPCs while inside vehicles.
"ExpansionAI_BlockExplosionsWhileInVehicle": 0, // Blocks explosion damage to Expansion AI/NPCs while inside vehicles.
"ExpansionAI_BlockMeleeWhileInVehicle": 0, // Blocks melee damage to Expansion AI/NPCs while inside vehicles.
"ExpansionAI_BlockContaminatedWhileInVehicle": 0, // Protects Expansion AI/NPCs from gas while inside vehicles.
"ExpansionAI_DoorOpenDisablesProtectionInContaminated": 0, // Disables AI/NPC gas protection if a vehicle door is open.
"ExpansionAI_NoDamageAfterJumpFromVehicle": 0, // Protects Expansion AI/NPCs from damage shortly after jumping out.

Vehicle Overrides

"EnableVehicleOverrides": 1 = Enables per-vehicle override rules.
"AutoExtendVehicleOverrides": 1 = Auto-adds missing vehicle classes into your override list (useful for modded vehicle packs).
AutoExtendVehicleOverrides needs to be set to 0 after you have done your changes, this will reduce the average tick time
If your server needs to read a big config at the start, it will have a high average tick time.
Set AutoExtendVehicleOverrides to 0 after you have done your changes. Your server will have a high tick time after the next restart, because it had to read the config and delete all unneeded entries.
Restart your server again with to gain a minimal average tick time.


Example: Per-vehicle override
{
"ClassName": "Nissan_Skyline_White",
"Vehicle_BlockBullets": 1,
"Vehicle_BlockExplosions": 1,
"Vehicle_BlockMelee": 1,
"Vehicle_AllowGlassDamage": 1,
"Vehicle_DisableCrashDamage": 1,
"Vehicle_DisableWaterDamage": 1,
"Vehicle_BlockContaminated": 1,
"Player_BlockContaminatedWhileInVehicle": 1,
"Player_DoorOpenDisablesProtectionInContaminated": 1,
"Vehicle_DisableRedlineDamage": -1,
"Vehicle_BlockCrewCrashDamage": -1,
"Vehicle_EnableCrashSounds": -1,
"Vehicle_NoDamageToZombies": -1,
"Vehicle_NoDamageToAnimals": -1,
"Vehicle_NoDamageToPlayers": -1,
"Vehicle_NoDamageToExpansionAI": -1,
"Vehicle_AutoFlip": -1,
"Player_NoDamageWhileInVehicle": 1,
"Player_BlockAllDamageWhileInVehicle": 1,
"Player_BlockBulletsWhileInVehicle": 1,
"Player_BlockExplosionsWhileInVehicle": 1,
"Player_BlockMeleeWhileInVehicle": 1,
"ExpansionAI_NoDamageWhileInVehicle": -1,
"ExpansionAI_BlockAllDamageWhileInVehicle": -1,
"ExpansionAI_BlockBulletsWhileInVehicle": -1,
"ExpansionAI_BlockExplosionsWhileInVehicle": -1,
"ExpansionAI_BlockMeleeWhileInVehicle": -1,
"ExpansionAI_BlockContaminatedWhileInVehicle": -1,
"ExpansionAI_DoorOpenDisablesProtectionInContaminated": -1,
"ExpansionAI_NoDamageAfterJumpFromVehicle": -1,
"Protect_AttachmentsOnVehicle": 1
},

-1 means this vehicle uses the global values.
Change a setting to 0 or 1 to force it for this vehicle, even if the global setting is 0.

_______________________________________________________________

Installation / Server Notes

Load it on the server like any other Workshop mod.

Works with vanilla vehicles and modded vehicles (using class names).
After the first start it generates a config file.
Change the settings how you like and restart the server.

Github
https://github.com/Blubberdiblupp/NoCarDamage

Monetization
You are allowed to use this mod on monetized severs, as long as you follow BI rules. No pay to win.

Repack, unpack, change, etc. is allowed

You are not allowed to sell any part of this code.
