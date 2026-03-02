modded class MissionGameplay
{
	protected static int g_NCD_LastFlipRequestMS = 0;

	override void OnInit()
	{
		super.OnInit();
		NCD_RegisterKeybinds();
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		if (!g_Game || !g_Game.IsClient())
			return;

		if (NCD_AutoFlipButtonEnabled() == 0)
			return;

		if (!NCD_IsFlipInputPressed())
			return;

		if (g_Game.GetUIManager() && g_Game.GetUIManager().GetMenu())
			return;

		PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player)
			return;

		HumanCommandVehicle cmd = player.GetCommand_Vehicle();
		if (!cmd)
			return;

		Transport t = cmd.GetTransport();
		if (!t)
			return;

		if (t.CrewDriver() != player)
			return;

		int nowMS = g_Game.GetTime();
		if ((nowMS - g_NCD_LastFlipRequestMS) < 250)
			return;
		g_NCD_LastFlipRequestMS = nowMS;

		player.RPCSingleParam(NCD_RPC_FLIP, null, true);
	}
}
