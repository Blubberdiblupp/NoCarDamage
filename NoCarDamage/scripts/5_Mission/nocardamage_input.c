bool NCD_IsFlipInputPressed()
{
	UAInputAPI api = GetUApi();
	if (!api)
		return false;

	UAInput flipInput = api.GetInputByName("UANCDFlipVehicle");
	return (flipInput && flipInput.LocalPress());
}
