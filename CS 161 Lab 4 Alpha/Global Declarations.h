//-----------------------------------------------------------------------------
//Stores the vraiables, constants, and prototypes for the game
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//Defines the constants
//-----------------------------------------------------------------------------
const int cintPNL_HEIGHT = 400;
const int cintPNL_WIDTH = 800;
const int cintBORDER_PADDING = 20;
const int cintPADDING = 10;
const int cintBUTTON_LENGTH = 100;
const int cintBUTTON_HEIGHT = 25;
const short cintFULL_OPACITY = 255;
const int cintHEIGHT = 500;
const int cintWIDTH = cintPNL_WIDTH + cintBORDER_PADDING + cintBORDER_PADDING;

//-----------------------------------------------------------------------------
//Global variables
//-----------------------------------------------------------------------------
short shtScreen = 0;	
short shtAttack = 0;
short shtBossAttack = 0;
short shtStepping = 0;

int intScore = 3000;

bool booOnLoad = TRUE;
bool booSlideForward = FALSE;
bool booSlideBackward = FALSE;
bool booAttacking = FALSE;
bool booProjectile = FALSE;
bool booEnemyOne = TRUE;
bool booEnemyTwo = TRUE;
bool booEnemyBoss = TRUE;
bool booPillar = TRUE;
bool booBossAttacking = FALSE;
bool booBossProjectile = TRUE;

//-----------------------------------------------------------------------------
//Global class constructions
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND frmHWND,
							UINT message,
							WPARAM wParam,
							LPARAM lParam);

INPUT ip;

HWND frmHWND, pnlPlayZone, lblInformation, lblCharInfo, btnPause;

HDC hdc;

RECT rect;

CRectangle rectSprite(cintBUTTON_HEIGHT * 2, NULL, cintBUTTON_LENGTH, cintBUTTON_LENGTH, 1, 3);
CRectangle ground(NULL, 375, cintPNL_WIDTH, cintBUTTON_HEIGHT);
CRectangle projectile(NULL,NULL,NULL,NULL);
CRectangle enemyOne(700, 275, cintBUTTON_LENGTH, cintBUTTON_LENGTH, NULL, 2);
CRectangle enemyTwo(700, 275, cintBUTTON_LENGTH, cintBUTTON_LENGTH, NULL, 2);
CRectangle enemyBoss(600, 175, cintBUTTON_LENGTH * 2, cintBUTTON_LENGTH * 2, NULL, 3);
CRectangle bossProjectile(enemyBoss.getX(), ground.getY() - 10, 5, 10);
CRectangle pillar(600, 175, cintBUTTON_LENGTH, cintBUTTON_LENGTH * 2, NULL);

//-----------------------------------------------------------------------------
//Prototypes
//-----------------------------------------------------------------------------
void DoEvents();
void sBackground();
void sIntro();
void sControls();
void sCheckGameState();
void sResetGameState();
void sSprite();
void sMoveRight();
void sMoveLeft();
void sJump();
void sShoot();
void sDrop();