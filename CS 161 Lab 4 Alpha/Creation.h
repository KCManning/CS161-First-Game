//-----------------------------------------------------------------------------
//Builds the objects on the window
//-----------------------------------------------------------------------------
void sOnCreate(HWND frmHWND)
{
	int intXCord = cintPADDING;
	int intYCord = cintPADDING;

	pnlPlayZone = CreateWindow("STATIC", "", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		intXCord, intYCord,
		cintPNL_WIDTH, cintPNL_HEIGHT,
		frmHWND, NULL, NULL, NULL);

	intYCord += cintPNL_HEIGHT;

	lblInformation = CreateWindow("STATIC",
		"   Project Manager: Josh Manion | CS 161 - Lab 3, 'Bright New World' | Artist: Abraham Nunez\n"
		"   Lead Tester: Lazarus Logan     |                                                          | "
		"Code and Story: Kevin Manning", 
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		intXCord, intYCord,
		cintPNL_WIDTH, (cintBUTTON_HEIGHT * 2) - cintPADDING,
		frmHWND, NULL, NULL, NULL);

	rect.left = cintPADDING;
	rect.top = cintPADDING;
	rect.right = cintPNL_WIDTH + cintPADDING;
	rect.bottom = cintPNL_HEIGHT + cintPADDING;
}
