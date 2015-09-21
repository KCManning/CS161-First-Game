//----------------------------------------------------------------------------------
//Project:			Lab 3
//Title:			Bright New World
//FileName:			CS 161 Lab 4 Alpha.sln
//IDE Program used: Visual Studio 2012 Ultimate
//Date Completed:	03/16/2015
//
//Author:			Kevin Manning | Josh Manion | Abraham Nunez | Lazarus Logan
//Class:			CS 161, Winter 2015
//
//Description:		An old school beat 'em up scroller
//----------------------------------------------------------------------------------
//Known Bugs:
//Changing directions after firing a bolt changes the direction of the bolt
//Game seems laggy on some systems, but not others
//White boarder around most objects with opacity == 0
//----------------------------------------------------------------------------------
#include "Inclusion.h"

//-----------------------------------------------------------------------------
//Builds the window
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(NULL, 125, cintFULL_OPACITY));;
	wc.lpszClassName = "MainWindow";

	RegisterClassEx(&wc);

	frmHWND = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		"MainWindow",
		"CS 161 Lab Three",
		WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		cintWIDTH,
		cintHEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(frmHWND, nCmdShow);

	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwFlags = KEYEVENTF_UNICODE; // Specify the key as a unicode character
	ip.ki.wScan = 0x3A-40; // Which keypress to simulate
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;

	MSG msg;

	while(GetMessage(&msg, NULL, NULL, NULL))
	{
		Sleep(3);
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		sCheckGameState();

	}
	GdiplusShutdown(gdiplusToken);

	return msg.wParam;
}

//-----------------------------------------------------------------------------
//Handles the messeages input to the window
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND frmHWND, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_CREATE:
		sOnCreate(frmHWND);
		sDrop();
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		if(booOnLoad == FALSE)
		{
			hdc = BeginPaint(pnlPlayZone, &ps);
			sSprite();
			EndPaint(pnlPlayZone, &ps);
			SendInput(1, &ip, sizeof(INPUT));
		}
		else
		{
			booOnLoad = FALSE;
			sIntro();
			sControls();
		}
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case 'D':
			sMoveRight();
			break;

		case 'A':
			sMoveLeft();
			break;

		case 'S':
			sShoot();
			break;

		case ' ':
		case 'W':
			sJump();
			break;

		case 'I':
			sControls();
			break;

		default:
			break;
		}

		sDrop();
		InvalidateRect(frmHWND, &rect, FALSE);

		break;

	case WM_KEYUP:
		switch(wParam)
		{
		case 0x1B:
			MessageBox(frmHWND,
				"Thanks for playing!\nWe hope to see you again soon!",
				NULL, NULL);
			PostQuitMessage(NULL);
			return NULL;
			break;

		default:
			break;
		}

		sDrop();
		InvalidateRect(frmHWND, &rect, FALSE);
		break;

	default: 
		sDrop();
		InvalidateRect(frmHWND, &rect, FALSE);
		break;
	}

	return DefWindowProc (frmHWND, message, wParam, lParam);
}

//-----------------------------------------------------------------------------
//Tells the player the story of the game
//-----------------------------------------------------------------------------
void sIntro()
{	
	MessageBox(frmHWND,
		"Welcome to Bright New World!\n"
		"The story thus far:\n\n"
		"The light has won.\n"
		"Darkness is defeated.\n"
		"The end of times is nigh.\n\n"
		"The great heroes of Milchang rose up against the tyrant Erkiln and his undead hordes. In a fit of arrogance "
		"and rage, Erkiln called forth a Pillar of Shadow and gave it mortal form. This new being, calling itself "
		"Hubris, was defeated after months of battle. The heroes, now aware of the existence of the Pillars hunted them "
		"across the planes until they were destroyed. For a moment, all was peace.\n\n"
		"However, the planes existed on a concept of balance. Good opposing Evil. Hope against Suffering. Light versus "
		"Darkness. Without these forces driving one another, all reality has begun to unravel. The resulting cascade of "
		"light has begun to erase world after world. However, one vestige of darkness remains.\n\n"
		"Just as there was a moment when Light began in the Universe there was a moment for Darkness. Though it has "
		"subsided into little more than an echo, this First Darkness will not go silently into the Light. It"
		"has manifested in mortal form as the Darkling, and now hunts for the remnants of the Pillars of Shadow"
		"to return balance.\n\n"
		"This is your story.",
		NULL, NULL);
}

//-----------------------------------------------------------------------------
//Shows the player the control scheme
//-----------------------------------------------------------------------------
void sControls()
{	
	MessageBox(frmHWND, "Game Controls:\n"
		"Press 'D' to move right.\n"
		"Press 'A' to move left.\n"
		"Press 'S' to throw Darkness Bolt*.\n"
		"Press 'W' or 'SPACE' to jump.\n"
		"Press 'I' to see these controls again.\n"
		"Press 'ESC' to quit.\n\n"
		"*Using the Darkness Bolt costs 500 Darkness.\n"
		"Defeat enemies to recharge Darkness and reach the Pillar of Shadow!"
		, NULL, NULL);
}

//-----------------------------------------------------------------------------
//Looks for victory or defeat
//-----------------------------------------------------------------------------
void sCheckGameState()
{
	const char* soundVictory = ("..\\Assets\\Victory.wav");;

	if(rectSprite.getHealth() < 1)
	{
		MessageBox(frmHWND,
			"You're the Coke Zero of darkness in the universe.\n"
			"Zero health is not how you win!",
			NULL, NULL);

		sResetGameState();
	}
	else if(pillar.intersects(rectSprite) && shtScreen == 4)
	{
		PlaySound(soundVictory, NULL, SND_ASYNC);

		MessageBox(frmHWND,
			"Congratulations on brining a little darkness back into the world!\n"
			"We hope to see you again soon!",
			NULL, NULL);

		sResetGameState();
	}
}

//-----------------------------------------------------------------------------
//Sets game back to initial state for second playthrough
//-----------------------------------------------------------------------------
void sResetGameState()
{
	shtScreen = 0;	
	shtAttack = 0;
	shtStepping = 0;
	intScore = 3000;

	booEnemyOne = TRUE;
	booEnemyTwo = TRUE;
	booEnemyBoss = TRUE;
	booPillar = TRUE;
	booBossAttacking = FALSE;
	booBossProjectile = TRUE;

	rectSprite = CRectangle(cintBUTTON_HEIGHT * 2, NULL, cintBUTTON_LENGTH, cintBUTTON_LENGTH, 1, 3);
	projectile = CRectangle(0,0,0,0);
	enemyOne = CRectangle(700, 275, cintBUTTON_LENGTH, cintBUTTON_LENGTH, NULL, 2);
	enemyTwo = CRectangle(700, 275, cintBUTTON_LENGTH, cintBUTTON_LENGTH, NULL, 2);
	enemyBoss = CRectangle(600, 175, cintBUTTON_LENGTH * 2, cintBUTTON_LENGTH * 2, NULL, 4);
	bossProjectile = CRectangle(enemyBoss.getX(), ground.getY() - 10, 5, 10);
}