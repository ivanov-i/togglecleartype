extern "C" int SystemParametersInfoW( unsigned  uiAction, unsigned  uiParam, void* pvParam, unsigned fWinIni);
extern "C" unsigned long GetLastError();

extern "C" int __stdcall  main()
{
	auto SPI_GETFONTSMOOTHING = 0x004A;
	auto SPI_SETFONTSMOOTHING = 0x004B;
	auto SPI_GETFONTSMOOTHINGTYPE = 0x200A;
	auto SPI_SETFONTSMOOTHINGTYPE = 0x200B;
	auto SPIF_UPDATEINIFILE = 1;
	auto SPIF_SENDCHANGE = 2;
	auto FE_FONTSMOOTHINGSTANDARD = 1;
	auto FE_FONTSMOOTHINGCLEARTYPE = 2;

	int enabled;
	auto result = SystemParametersInfoW(SPI_GETFONTSMOOTHING, 0, &enabled, 0);
	if (!result)
	{
		return GetLastError();
	}

	if (!enabled)
	{
		return 0;
	}

	unsigned smoothingType;
	result = SystemParametersInfoW(SPI_GETFONTSMOOTHINGTYPE, 0, &smoothingType, 0);
	if (!result)
	{
		return GetLastError();
	}

	if (smoothingType == FE_FONTSMOOTHINGCLEARTYPE)
	{
		smoothingType = FE_FONTSMOOTHINGSTANDARD;
	}
	else
	{
		smoothingType = FE_FONTSMOOTHINGCLEARTYPE;
	}

	auto updateAndNotify = SPIF_UPDATEINIFILE | SPIF_SENDCHANGE;
	result = SystemParametersInfoW(SPI_SETFONTSMOOTHINGTYPE, 0, (void*)(unsigned long long)smoothingType, updateAndNotify);
	if (!result)
	{
		return GetLastError();
	}

	return 0;
}