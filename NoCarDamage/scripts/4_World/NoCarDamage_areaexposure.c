modded class AreaExposureMdfr
{
	override void OnActivate(PlayerBase player)
	{
		if (!NCD_IsAnyToxicProtectionEnabled())
		{
			super.OnActivate(player);
			return;
		}

		Transport t = NCD_GetPlayerTransport(player);
		if (t && NCD_ShouldSuppressContaminatedAreaForPlayer(player, t))
			return;

		super.OnActivate(player);
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
		if (!NCD_IsAnyToxicProtectionEnabled())
		{
			super.OnTick(player, deltaT);
			return;
		}

		Transport t = NCD_GetPlayerTransport(player);
		if (t && NCD_ShouldSuppressContaminatedAreaForPlayer(player, t))
			return;

		super.OnTick(player, deltaT);
	}
};
