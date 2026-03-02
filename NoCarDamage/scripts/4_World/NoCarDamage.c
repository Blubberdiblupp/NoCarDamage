bool NCD_IsGlassZone(string dmgZone)
{
	if (dmgZone == "")
		return false;

	string dz = dmgZone;
	dz.ToLower();

	return (dz.IndexOf("glass") != -1) || (dz.IndexOf("window") != -1) || (dz.IndexOf("windscreen") != -1);
}

Transport NCD_GetPlayerTransport(PlayerBase p)
{
	if (!p) return null;

	HumanCommandVehicle cmd = p.GetCommand_Vehicle();
	if (cmd)
	{
		Transport cmdTransport = cmd.GetTransport();
		if (cmdTransport)
			return cmdTransport;
	}

	EntityAI root = EntityAI.Cast(p.GetHierarchyRoot());
	if (root && root != p && root.IsKindOf("Transport"))
		return Transport.Cast(root);

	return null;
}

bool NCD_IsPlayerInVehicle(PlayerBase p)
{
	return (NCD_GetPlayerTransport(p) != null);
}

bool NCD_IsHumanPlayer(PlayerBase player)
{
	if (!player)
		return false;
	if (NCD_IsExpansionAI(player))
		return false;
	return (player.GetIdentity() != null);
}

bool NCD_IsExpansionAI(PlayerBase player)
{
	return (player && player.IsKindOf("eAIBase"));
}

static const int NCD_PLAYER_KIND_NONE = 0;
static const int NCD_PLAYER_KIND_HUMAN = 1;
static const int NCD_PLAYER_KIND_EXPANSION_AI = 2;

int NCD_GetProtectedPlayerKind(PlayerBase player)
{
	if (NCD_IsExpansionAI(player))
		return NCD_PLAYER_KIND_EXPANSION_AI;

	if (NCD_IsHumanPlayer(player))
		return NCD_PLAYER_KIND_HUMAN;

	return NCD_PLAYER_KIND_NONE;
}

bool NCD_ShouldApplyHumanOrAIProtection(PlayerBase player, int humanEnabled, int aiEnabled)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);

	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return (humanEnabled == 1);

	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return (aiEnabled == 1);

	return false;
}


bool NCD_ShouldProtectJumpOutForPlayer(PlayerBase player)
{
	return NCD_ShouldApplyHumanOrAIProtection(player, NCD_Eff_Player_NoDamageAfterJumpFromVehicle(), NCD_Eff_ExpansionAI_NoDamageAfterJumpFromVehicle());
}

bool NCD_ShouldIgnoreTransportHitForPlayer(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return (NCD_Eff_Vehicle_NoDamageToPlayers(vt) == 1);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return (NCD_Eff_Vehicle_NoDamageToExpansionAI(vt) == 1);
	return false;
}

int NCD_Eff_Occupant_NoDmgInVehicle(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_NoDmgInVehicle(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_NoDmgInVehicle(vt);
	return 0;
}

int NCD_Eff_Occupant_BlockAllInVehicle(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_BlockAllInVehicle(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_BlockAllInVehicle(vt);
	return 0;
}

int NCD_Eff_Occupant_BlockBulletsInVehicle(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_BlockBulletsInVehicle(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_BlockBulletsInVehicle(vt);
	return 0;
}

int NCD_Eff_Occupant_BlockExplosionsInVehicle(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_BlockExplosionsInVehicle(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_BlockExplosionsInVehicle(vt);
	return 0;
}

int NCD_Eff_Occupant_BlockMeleeInVehicle(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_BlockMeleeInVehicle(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_BlockMeleeInVehicle(vt);
	return 0;
}

int NCD_Eff_Occupant_BlockContaminatedInVehicle(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_BlockContaminatedInVehicle(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_BlockContaminatedInVehicle(vt);
	return 0;
}

int NCD_Eff_Occupant_DoorOpenDisablesProtectionInContaminated(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_DoorOpenDisablesProtectionInContaminated(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_DoorOpenDisablesProtectionInContaminated(vt);
	return 0;
}

bool NCD_IsOccupantSealedForToxic(PlayerBase player, string vt)
{
	if (vt == "")
		return false;

	if (NCD_Eff_Vehicle_BlockContaminated(vt) == 1)
		return true;

	return (NCD_Eff_Occupant_BlockContaminatedInVehicle(player, vt) == 1);
}

bool NCD_ShouldSuppressContaminatedAreaForPlayer(PlayerBase player, Transport t)
{
	if (!player || !t)
		return false;

	string vt = t.GetType();
	if (!NCD_IsOccupantSealedForToxic(player, vt))
		return false;

	bool doorRule = false;
	if (NCD_Eff_Occupant_DoorOpenDisablesProtectionInContaminated(player, vt) == 1)
		doorRule = NCD_IsAnyDoorOpen(t);

	return !doorRule;
}

string NCD_PlayerKey(PlayerBase p)
{
	if (!p) return "";
	PlayerIdentity id = p.GetIdentity();
	if (id) return id.GetId();
	return p.ToString();
}

bool NCD_IsToxicAmmo(string ammo)
{
	if (ammo == "") return false;
	string am = ammo;
	am.ToLower();
	return (am.IndexOf("contamin") != -1) || (am.IndexOf("toxic") != -1) || (am.IndexOf("gas") != -1) || (am.IndexOf("chemical") != -1);
}

static ref map<string, ref array<string>> NCD_DoorSlotCache_W = new map<string, ref array<string>>();
static ref map<string, ref array<string>> NCD_DoorAnimCache_W = new map<string, ref array<string>>();
static ref map<string, int> NCD_DoorOpenCacheTime_W = new map<string, int>();
static ref map<string, bool> NCD_DoorOpenCacheVal_W = new map<string, bool>();
static const int NCD_DOOR_OPEN_CACHE_MS = 2000;

static bool NCD_IsDoorLikeName(string s)
{
	if (s == "") return false;
	string low = s;
	low.ToLower();

	if (low.IndexOf("door")   != -1) return true;
	if (low.IndexOf("doors")  != -1) return true;
	if (low.IndexOf("hatch")  != -1) return true;
	if (low.IndexOf("ramp")   != -1) return true;
	if (low.IndexOf("gate")   != -1) return true;
	if (low.IndexOf("hood")   != -1) return true;
	if (low.IndexOf("bonnet") != -1) return true;
	if (low.IndexOf("trunk")  != -1) return true;
	if (low.IndexOf("boot")   != -1) return true;
	if (low.IndexOf("canopy") != -1) return true;
	if (low.IndexOf("dver")   != -1) return true;
	return false;
}

static array<string> NCD_GetDoorSlotNames_W(string vt)
{
	if (vt == "") return null;

	ref array<string> cached;
	if (NCD_DoorSlotCache_W.Find(vt, cached))
		return cached;

	ref array<string> slots = new array<string>();

	string path = "CfgVehicles " + vt + " attachments";
	if (g_Game && g_Game.ConfigIsExisting(path))
	{
		ref array<string> tmp = new array<string>();
		g_Game.ConfigGetTextArray(path, tmp);
		for (int i = 0; i < tmp.Count(); i++)
		{
			string s = tmp[i];
			if (NCD_IsDoorLikeName(s))
				slots.Insert(s);
		}
	}

	NCD_DoorSlotCache_W.Set(vt, slots);
	return slots;
}

static array<string> NCD_GetDoorAnimSourceNames_W(string vt)
{
	if (vt == "") return null;

	ref array<string> cached;
	if (NCD_DoorAnimCache_W.Find(vt, cached))
		return cached;

	ref array<string> sources = new array<string>();

	string path = "CfgVehicles " + vt + " AnimationSources";
	if (g_Game && g_Game.ConfigIsExisting(path))
	{
		int c = g_Game.ConfigGetChildrenCount(path);
		for (int i = 0; i < c; i++)
		{
			string child;
			g_Game.ConfigGetChildName(path, i, child);
			if (NCD_IsDoorLikeName(child))
				sources.Insert(child);
		}
	}

	NCD_DoorAnimCache_W.Set(vt, sources);
	return sources;
}

static void NCD_SetDoorOpenCache(string key, bool val)
{
	if (key == "" || !g_Game) return;
	NCD_DoorOpenCacheVal_W.Set(key, val);
	NCD_DoorOpenCacheTime_W.Set(key, g_Game.GetTime());
}

static void NCD_InvalidateDoorCache(Transport t)
{
	if (!t) return;
	string key = t.ToString();
	if (key == "") return;
	NCD_DoorOpenCacheVal_W.Remove(key);
	NCD_DoorOpenCacheTime_W.Remove(key);
}

bool NCD_IsAnyDoorOpen(Transport t)
{
	if (!t) return false;

	string key = t.ToString();
	if (g_Game)
	{
		int last;
		bool cached;
		if (NCD_DoorOpenCacheTime_W.Find(key, last) && NCD_DoorOpenCacheVal_W.Find(key, cached))
		{
			if ((g_Game.GetTime() - last) < NCD_DOOR_OPEN_CACHE_MS)
				return cached;
		}
	}

	string vt = t.GetType();

	array<string> sources = NCD_GetDoorAnimSourceNames_W(vt);
	if (!sources)
	{
		NCD_SetDoorOpenCache(key, false);
		return false;
	}

	for (int k = 0; k < sources.Count(); k++)
	{
		string s = sources[k];
		if (s == "") continue;

		float ph = t.GetAnimationPhase(s);
		if (ph > 0.5)
		{
			NCD_SetDoorOpenCache(key, true);
			return true;
		}
	}

	NCD_SetDoorOpenCache(key, false);
	return false;
}

bool NCD_IsTransportFlipped(Transport t)
{
	if (!t) return false;

	vector mat[4];
	t.GetTransform(mat);
	vector up = mat[1];

	return (up[1] < 0.2);
}

void NCD_FlipTransportUpright(Transport t)
{
	if (!t) return;

	vector ori = t.GetOrientation();
	ori[0] = 0;
	ori[2] = 0;

	vector pos = t.GetPosition();
	pos[1] = pos[1] + 0.5;

	t.SetPosition(pos);
	t.SetOrientation(ori);
}

modded class CarScript
{
	protected float m_NCD_AutoFlipTimer = 0;
	protected float m_NCD_WaterCheckTimer = 0;
	protected float m_NCD_WaterCheckInterval = 0.5;
	protected bool m_NCD_WaterUnderwater = false;
	protected float m_NCD_WaterEngineBefore = 0;
	protected bool m_NCD_DoCrashDisable = false;
	protected bool m_NCD_DoCrashSounds = false;
	protected bool m_NCD_DoCrewCrashBlock = false;
	protected int m_NCD_LastCrashCacheClearMS = 0;
	protected int m_NCD_LastCrashIdleClearMS = 0;
	protected bool m_NCD_RuntimeFlagsInit = false;
	protected bool m_NCD_HasRuntimeWork = false;
	protected bool m_NCD_DoWaterProtection = false;
	protected bool m_NCD_DoPassiveAutoFlip = false;
	protected bool m_NCD_UseExpansionCrashWaterPath = false;
	protected string m_NCD_VehicleTypeCached = "";

	protected string NCD_GetVehicleTypeCached()
	{
		if (m_NCD_VehicleTypeCached == "")
			m_NCD_VehicleTypeCached = GetType();

		return m_NCD_VehicleTypeCached;
	}

	protected void NCD_InitRuntimeFlags()
	{
		if (m_NCD_RuntimeFlagsInit)
			return;

		m_NCD_RuntimeFlagsInit = true;

		if (!g_Game || !g_Game.IsServer())
			return;

		string vt = NCD_GetVehicleTypeCached();
		m_NCD_DoWaterProtection = (NCD_Eff_Vehicle_DisableWater(vt) == 1);
		m_NCD_DoPassiveAutoFlip = (NCD_Eff_Vehicle_AutoFlip(vt) == 1 && NCD_AutoFlipButtonEnabled() == 0);
		m_NCD_DoCrashDisable = (NCD_Eff_Vehicle_DisableCrash(vt) == 1);
		m_NCD_DoCrashSounds = (NCD_Eff_Vehicle_EnableCrashSounds(vt) == 1);
		m_NCD_DoCrewCrashBlock = (NCD_Eff_Vehicle_BlockCrewCrashDamage(vt) == 1);
		m_NCD_UseExpansionCrashWaterPath = NCD_IsExpansionVehicleDamageDisabled() && (m_NCD_DoCrashDisable || m_NCD_DoWaterProtection);

		if (m_NCD_UseExpansionCrashWaterPath)
		{
			m_NCD_DoCrashDisable = false;
			m_NCD_DoWaterProtection = false;
		}

		m_NCD_HasRuntimeWork = (m_NCD_DoWaterProtection || m_NCD_DoPassiveAutoFlip);
	}

	override void OnVehicleJumpOutServer(GetOutTransportActionData gotActionData)
	{
		PlayerBase jumpOutPlayer = null;
		if (gotActionData)
		{
			jumpOutPlayer = PlayerBase.Cast(gotActionData.m_Player);
			if (jumpOutPlayer)
				jumpOutPlayer.NCD_ArmNoJumpDamageWindow(gotActionData.m_CarSpeed);
		}

		super.OnVehicleJumpOutServer(gotActionData);
	}

	override void OnAnimationPhaseStarted(string animSource, float phase)
	{
		super.OnAnimationPhaseStarted(animSource, phase);

		if (NCD_IsDoorLikeName(animSource))
			NCD_InvalidateDoorCache(this);
	}

	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		string vt = NCD_GetVehicleTypeCached();

		if (damageType == DamageType.CUSTOM && ammo != "" && dmgZone == "Engine")
		{
			if (NCD_Eff_Vehicle_DisableRedlineDamage(vt) == 1 && EngineIsOn() && EngineGetRPM() >= EngineGetRPMRedline())
			{
				string am = ammo;
				am.ToLower();
				if (am.IndexOf("enviro") != -1)
					return false;
			}
		}

		if (NCD_Eff_Vehicle_BlockContaminated(vt) == 1 && NCD_IsToxicAmmo(ammo))
			return false;

		if (damageType == DamageType.FIRE_ARM && NCD_Eff_Vehicle_BlockBullets(vt) == 1)
		{
			if (NCD_Eff_Vehicle_AllowGlassDamage(vt) == 1 && NCD_IsGlassZone(dmgZone))
				return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
			return false;
		}

		if (damageType == DamageType.EXPLOSION && NCD_Eff_Vehicle_BlockExplosions(vt) == 1) return false;
		if (damageType == DamageType.CLOSE_COMBAT && NCD_Eff_Vehicle_BlockMelee(vt) == 1) return false;

		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}

	override void CheckContactCache()
	{
		NCD_InitRuntimeFlags();
		if (m_NCD_DoCrashDisable)
		{
			if (g_Game)
			{
				int nowMS = g_Game.GetTime();
				bool hasCrew = (CrewSize() > 0);
				bool engineOn = EngineIsOn();
				bool idle = (!hasCrew && !engineOn);

				if (idle)
				{
					if ((nowMS - m_NCD_LastCrashIdleClearMS) >= 15000)
					{
						m_NCD_LastCrashIdleClearMS = nowMS;
						m_ContactCache.Clear();
					}
					return;
				}

				if ((nowMS - m_NCD_LastCrashCacheClearMS) >= 4000)
				{
					m_NCD_LastCrashCacheClearMS = nowMS;
					m_ContactCache.Clear();
				}
			}
			else
			{
				m_ContactCache.Clear();
			}
			return;
		}

		super.CheckContactCache();
	}

	override void SynchCrashLightSound(bool play)
	{
		NCD_InitRuntimeFlags();
		if (!m_NCD_DoCrashSounds)
			return;
		super.SynchCrashLightSound(play);
	}

	override void SynchCrashHeavySound(bool play)
	{
		NCD_InitRuntimeFlags();
		if (!m_NCD_DoCrashSounds)
			return;
		super.SynchCrashHeavySound(play);
	}

	override void DamageCrew(float dmg)
	{
		NCD_InitRuntimeFlags();
		if (m_NCD_DoCrashDisable && m_NCD_DoCrewCrashBlock)
			return;

		super.DamageCrew(dmg);
	}

	override void OnUpdate(float dt)
	{
		NCD_InitRuntimeFlags();

		if (!g_Game || !g_Game.IsServer() || !m_NCD_HasRuntimeWork)
		{
			super.OnUpdate(dt);
			return;
		}

		bool hasCrew = (CrewSize() > 0);

		if (m_NCD_DoWaterProtection)
		{
			m_NCD_WaterCheckTimer += dt;
			if (m_NCD_WaterCheckTimer >= m_NCD_WaterCheckInterval)
			{
				m_NCD_WaterCheckTimer = 0;
				m_NCD_WaterUnderwater = (g_Game.GetWaterDepth(GetEnginePosWS()) > 0);
				if (m_NCD_WaterUnderwater)
				{
					m_NCD_WaterEngineBefore = GetHealth("Engine", "Health");
					m_NCD_WaterCheckInterval = 0.5;
				}
				else if (!hasCrew)
				{
					m_NCD_WaterCheckInterval = m_NCD_WaterCheckInterval + 1.0;
					if (m_NCD_WaterCheckInterval > 30.0)
						m_NCD_WaterCheckInterval = 30.0;
				}
				else
				{
					m_NCD_WaterCheckInterval = 0.5;
				}
			}
		}

		super.OnUpdate(dt);

		if (m_NCD_DoWaterProtection && m_NCD_WaterUnderwater)
		{
			float engineAfter = GetHealth("Engine", "Health");
			if (engineAfter < m_NCD_WaterEngineBefore)
				SetHealth("Engine", "Health", m_NCD_WaterEngineBefore);

			m_DrownTime = 0;
		}

		if (m_NCD_DoPassiveAutoFlip)
		{
			if (!hasCrew)
			{
				m_NCD_AutoFlipTimer = 0;
				return;
			}

			m_NCD_AutoFlipTimer += dt;
			if (m_NCD_AutoFlipTimer >= 5.0)
			{
				m_NCD_AutoFlipTimer = 0;

				if (GetSpeedometer() < 1.0 && NCD_IsTransportFlipped(this))
					NCD_FlipTransportUpright(this);
			}
		}
	}
};

modded class BoatScript
{
	override void OnVehicleJumpOutServer(GetOutTransportActionData data)
	{
		PlayerBase jumpOutPlayer = null;
		if (data)
		{
			jumpOutPlayer = PlayerBase.Cast(data.m_Player);
			if (jumpOutPlayer)
				jumpOutPlayer.NCD_ArmNoJumpDamageWindow(data.m_CarSpeed);
		}

		super.OnVehicleJumpOutServer(data);
	}
};


modded class ActionGetOutTransport
{
	override void OnEndServer(ActionData action_data)
	{
		GetOutTransportActionData gotActionData = GetOutTransportActionData.Cast(action_data);
		if (!gotActionData || !gotActionData.m_Player || !gotActionData.m_WasJumpingOut)
		{
			super.OnEndServer(action_data);
			return;
		}

		PlayerBase jumpOutPlayer = PlayerBase.Cast(gotActionData.m_Player);
		if (!jumpOutPlayer || !NCD_ShouldProtectJumpOutForPlayer(jumpOutPlayer))
		{
			super.OnEndServer(action_data);
			return;
		}

		jumpOutPlayer.OnJumpOutVehicleFinish(gotActionData.m_CarSpeed);

		if (gotActionData.m_Car)
		{
			CarScript car;
			if (Class.CastTo(car, gotActionData.m_Car))
				car.ForceUpdateLightsEnd();
		}
	}
};

modded class ItemBase
{
	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (damageType != DamageType.FIRE_ARM && damageType != DamageType.EXPLOSION && damageType != DamageType.CLOSE_COMBAT && damageType != DamageType.CUSTOM)
			return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		EntityAI root = EntityAI.Cast(GetHierarchyRoot());
		if (root && (root.IsKindOf("CarScript") || root.IsKindOf("Transport")))
		{
			string vt = root.GetType();

			if ((IsKindOf("SparkPlug") || IsKindOf("GlowPlug")) && damageType == DamageType.CUSTOM)
				return false;

			if (NCD_Eff_ProtectAttachments(vt) == 1)
			{
				if (damageType == DamageType.FIRE_ARM && NCD_Eff_Vehicle_BlockBullets(vt) == 1) return false;
				if (damageType == DamageType.EXPLOSION && NCD_Eff_Vehicle_BlockExplosions(vt) == 1) return false;
				if (damageType == DamageType.CLOSE_COMBAT && NCD_Eff_Vehicle_BlockMelee(vt) == 1) return false;
			}
		}

		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
};

modded class PlayerBase
{
	protected int m_NCD_NoJumpDamageUntilMS = 0;
	protected int m_NCD_LastFlipRpcMS = 0;

	void NCD_ArmNoJumpDamageWindow(float carSpeed)
	{
		if (!g_Game || !g_Game.IsServer())
			return;

		if (!NCD_ShouldProtectJumpOutForPlayer(this))
			return;

		if (carSpeed < 8.0)
			return;

		m_NCD_NoJumpDamageUntilMS = g_Game.GetTime() + 1500;
	}

	bool NCD_IsNoJumpDamageActive()
	{
		return (NCD_ShouldProtectJumpOutForPlayer(this) && m_NCD_NoJumpDamageUntilMS > 0 && g_Game && g_Game.GetTime() <= m_NCD_NoJumpDamageUntilMS);
	}

	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (NCD_IsNoJumpDamageActive())
		{
			if (!source)
				return false;

			if (damageType == DamageType.CUSTOM)
			{
				string am0 = ammo;
				am0.ToLower();
				if (am0 == "" || am0.IndexOf("fall") != -1 || am0.IndexOf("land") != -1 || am0.IndexOf("enviro") != -1 || am0.IndexOf("shock") != -1 || am0.IndexOf("bleed") != -1)
					return false;
			}
		}

		if (source && source.IsKindOf("Transport"))
		{
			string vtSrc = source.GetType();
			if (NCD_ShouldIgnoreTransportHitForPlayer(this, vtSrc))
				return false;
		}

		Transport t = NCD_GetPlayerTransport(this);
		if (t)
		{
			string vt = t.GetType();

			bool sealedForToxic = NCD_IsOccupantSealedForToxic(this, vt);
			bool doorRule = false;
			if (sealedForToxic && NCD_Eff_Occupant_DoorOpenDisablesProtectionInContaminated(this, vt) == 1)
				doorRule = NCD_IsAnyDoorOpen(t);

			if (!doorRule)
			{
				if (NCD_Eff_Occupant_NoDmgInVehicle(this, vt) == 1)
				{
					if (NCD_Eff_Occupant_BlockAllInVehicle(this, vt) == 1) return false;
					if (damageType == DamageType.FIRE_ARM && NCD_Eff_Occupant_BlockBulletsInVehicle(this, vt) == 1) return false;
					if (damageType == DamageType.EXPLOSION && NCD_Eff_Occupant_BlockExplosionsInVehicle(this, vt) == 1) return false;
					if (damageType == DamageType.CLOSE_COMBAT && NCD_Eff_Occupant_BlockMeleeInVehicle(this, vt) == 1) return false;
				}

				if (sealedForToxic && NCD_IsToxicAmmo(ammo))
					return false;
			}
		}

		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}

	override void OnJumpOutVehicleFinish(float carSpeed)
	{
		NCD_ArmNoJumpDamageWindow(carSpeed);
		super.OnJumpOutVehicleFinish(carSpeed);
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		if (!g_Game || !g_Game.IsServer())
			return;
		if (rpc_type != NCD_RPC_FLIP)
			return;
		int nowMS = g_Game.GetTime();
		if ((nowMS - m_NCD_LastFlipRpcMS) < 250)
			return;
		m_NCD_LastFlipRpcMS = nowMS;
		if (!sender || !GetIdentity() || sender.GetId() != GetIdentity().GetId())
			return;

		HumanCommandVehicle cmd = GetCommand_Vehicle();
		if (!cmd)
			return;

		Transport t = cmd.GetTransport();
		if (!t)
			return;

		if (t.CrewDriver() != this)
			return;

		string vt = t.GetType();
		if (NCD_AutoFlipButtonEnabled() == 0)
			return;

		if (!NCD_IsTransportFlipped(t))
			return;

		float speed = 0;
		CarScript cs = CarScript.Cast(t);
		if (cs)
			speed = cs.GetSpeedometer();
		else
		{
			vector vel = GetVelocity(t);
			speed = vel.Length();
		}

		if (speed > 1.0)
			return;

		NCD_FlipTransportUpright(t);
	}
};

modded class DayZPlayerImplementFallDamage
{
	override void HandleFallDamage(FallDamageData pData)
	{
		PlayerBase pb = PlayerBase.Cast(m_Player);
		if (pb && pb.NCD_IsNoJumpDamageActive())
			return;

		super.HandleFallDamage(pData);
	}
};

modded class ZombieBase
{
	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (source && source.IsKindOf("Transport"))
		{
			string vt = source.GetType();
			if (NCD_Eff_Vehicle_NoDamageToZombies(vt) == 1)
				return false;
		}

		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
};

modded class AnimalBase
{
	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (source && source.IsKindOf("Transport"))
		{
			string vt = source.GetType();
			if (NCD_Eff_Vehicle_NoDamageToAnimals(vt) == 1)
				return false;
		}

		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
};
