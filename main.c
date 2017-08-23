#include <stdio.h>
#include <stdlib.h>

#define CLEAR		0x00
#define QUOTE		0x01
#define LEFT		0x02
#define BOTTOM		0x03
#define TL			0x04
#define TR			0x05
#define BL			0x06
#define BR			0x07
#define BLTR		0x08
#define CHESSBOARD	0x09
#define CHESSBTM	0x0a
#define CHESSTOP	0x0b
#define POUND		0x0c
#define DOLLAR		0x0d
#define COLON		0x0e
#define QM			0x0f
#define OBRACKET	0x10
#define CBRACKET	0x11
#define DASH		0x12
#define PLUS		0x13
#define STAR		0x14
#define SLASH		0x15
#define EQUALS		0x16
#define GT			0x17
#define LT			0x18
#define SEMI		0x19
#define COMMA		0x1a
#define DOT			0x1b
#define ZERO		0x1c
#define ONE			0x1d
#define TWO			0x1e
#define THREE		0x1f
#define FOUR		0x20
#define FIVE		0x21
#define SIX			0x22
#define SEVEN		0x23
#define EIGHT		0x24
#define NINE		0x25
#define	_A			0x26
#define _B			0x27
#define _C			0x28
#define _D			0x29
#define _E			0x2a
#define _F			0x2b
#define _G			0x2c
#define _H			0x2d
#define _I			0x2e
#define _J			0x2f
#define _K			0x30
#define _L			0x31
#define _M			0x32
#define _N			0x33
#define _O			0x34
#define _P			0x35
#define _Q			0x36
#define _R			0x37
#define _S			0x38
#define _T			0x39
#define _U			0x3a
#define _V			0x3b
#define _W			0x3c
#define _X			0x3d
#define _Y			0x3e
#define _Z			0x3f
#define SCRLOC(X,Y)	(((Y<<5)+Y)+X)
#define INVERSE(A)	(0x80 | A)
#define NL			0x76
#define EOF			0xff
#define DFILE		$400c
#define STRBFSIZE	0x20

/**
 * Function prototypes
 */
int main();
unsigned char zx80Init();
unsigned char prompt(unsigned char txt[32], unsigned char lineNumber);
unsigned char cls();
unsigned char printAt(unsigned short xy);
unsigned char setText(unsigned char txt[33], unsigned char x, unsigned char y, unsigned char inv);
unsigned char startGame();
void gameManager();
void preSeasonPrompt();

/**
 * Globals
 */
unsigned char donkeySoft[19] =
{
	_D, _O, _N, _K, _E, _Y, _S, _O, _F, _T, CLEAR, CLEAR, _M, _M, _X, _V, _I, _I, EOF
};
unsigned char microGames[25] = 
{
	_A, _N, _D, CLEAR, _M, _O, _N, _U, _M, _E, _N, _T, CLEAR, CLEAR, _M, _I, _C, _R, _O, _G, _A, _M, _E, _S, EOF
};
unsigned char presents[17] =
{
	STAR, STAR, STAR, CLEAR, _P, _R, _E, _S, _E, _N, _T, _S, CLEAR, STAR, STAR, STAR, EOF
};
unsigned char gameName[31] =
{
	_S, _U, _N, _D, _A, _Y, CLEAR , _L, _E, _A, _G, _U, _E, CLEAR, _F , _O, _O, _T, _B, _A, _L, _L, CLEAR, _M, _A, _N, _A, _G, _E, _R, EOF
};

unsigned char c;
unsigned char text[33];
unsigned char manager[16];

signed long money = 1;
unsigned char week;
unsigned char year;
unsigned char league;

unsigned char numberOfPlayers;
unsigned char leaguePosition;
unsigned char cupRun;

unsigned short numberOfFans;
unsigned short income;
unsigned short expenses;
unsigned short matchAppearanceFee;

/**
 * Dictionary look-up to save bytes
 */
unsigned char the[]			= "the";
unsigned char you[]			= "you";
unsigned char and[]			= "and";

/**
 * Main entry point of game
 *
 * @param	na
 * @author	sbebbington
 * @date	21 Aug 2017
 * @version	1.2
 */
int main()
{
	zx80Init();
	setText(donkeySoft, 7, 0, 1);
	setText(microGames, 4, 2, 1);
	setText(presents, 8, 4, 0);
	setText(gameName, 1, 6, 0);
	startGame();
}

/**
 * Game starts here, sets player's name
 * and also prompts for instructions
 * STRBFSIZE is used as a reasonable limiter
 * for the number of characters that the
 * user may enter; anything above this
 * and it will cause unpredictable
 * effects
 *
 * @param	na
 * @author	sbebbington
 * @date	23 Aug 2017
 * @version	1.1
 */
unsigned char startGame()
{
	unsigned char _strBuffer[STRBFSIZE];
	prompt("enter your name\n(max 16 characters)", 8);
	gets(_strBuffer);
	if(!_strBuffer[0])
	{
		main();
	}
	
	c = 15;
	while(c != EOF)
	{
		manager[c] = _strBuffer[c];
		c--;
	}
	manager[16]		= CLEAR;
	_strBuffer[0]	= CLEAR;
	cls();
	
	printf("welcome %s\n", manager);
	prompt("would you like instructions Y/N?", CLEAR);
	gets(_strBuffer);
	if(_strBuffer[0] == 121)
	{
		cls();
		preSeasonPrompt();
		prompt("",0);
		gets(_strBuffer);
	}
	gameManager();
}

/**
 * This will work out at which point in the
 * season the player is and therefore call
 * the relevant functions or sub routines
 *
 * @param	na
 * @author	sbebbington
 * @date	23 Aug 2017
 * @version	1.0
 */
void gameManager()
{
	unsigned char _strBuffer[STRBFSIZE];
	unsigned char gameBegins = 1;
	cls();
	while(money)
	{
		if(gameBegins)
		{
			gameBegins--;
			money	= 12500;
			week	= 1;
			year	= 1;
			league	= 4;
		}
		money--;
	}
}

/**
 * Basic instructions, probably typos therein
 * Now uses a dictionary look-up table to save
 * some bytes
 *
 * @param	na
 * @author	sbebbington
 * @date	23 Aug 2017
 * @version	1.1
 */
void preSeasonPrompt()
{
	printf("it's tough at %s top. %sr taskis to build a new team for %s\nARSENIC CHEMICALS LTD.\n3rd division %s take %sm all\n%s way to %s ARSENIC\nCHECMICALS LTD. PRO LEAGUE.\nas a member of this new division%s must scout for players,\nbuild a fan base, %s prepare\n%sr team for %s season ahead,\nwhich will include playing for\n%s BATHRACHOTOXIN DRINKS CO\nchallenge cup. %s will start\nwith £12,250 %s must prepare\nfor friendlies before %s big\nkick off. buy %s sell players\nwhen transfer windows are\nopen %s make lots of money.\ngood luck. PRESS ENTER\n", the, you, the, and, the, the, the, you, and, you, the, the, you, the, the, you, and, the, and, and);
}

/**
 * This sets the fast text output
 * by passing the already defined
 * ZX80 char array to the global
 * used in the printAt() function
 *
 * @param	na
 * @author	sbebbington
 * @date	21 Aug 2017
 * @version	1.0
 */
unsigned char setText(unsigned char txt[33], unsigned char x, unsigned char y, unsigned char inv)
{
	c = 0;
	while(txt[c] != EOF)
	{
		if(inv)
		{
			text[c] = INVERSE(txt[c]);
		}
		else
		{
			text[c] = txt[c];
		}
		c++;
	}
	text[c] = EOF;
	printAt(SCRLOC(x,y));
}

/**
 * This does the basic initialisation
 * for the game and for the ZX80 itself
 *
 * @param	na
 * @author	sbebbington
 * @date	20 Aug 2017
 * @version	1.0
 */
unsigned char zx80Init()
{
	text[0] = EOF;
	for(c = 24; c > 0; c--)
	{
		printf("                                \n");
	}
	cls();
}


/**
 * Outputs the prompt, also accepts
 * a string and on which line the
 * prompt should appear
 *
 * @param	unsigned char, unsigned char
 * @author	sbebbington
 * @date	21 Aug 2017
 * @version	1.1
 */
unsigned char prompt(unsigned char txt[32], unsigned char lineNumber)
{
	if(lineNumber)
	{
		for(c = lineNumber; c > 0; c--)
		{
			printf("\n");
		}
	}
	if(txt[0])
	{
		printf("%s\n",txt);
	}
	printf("c:>");
}

/**
 * Clears the screen
 *
 * @param	na
 * @author	sbebbington
 * @date	22 Aug 2017
 * @version	1.1a
 * @todo	Should be able to increase just the L
 * 			register of the DFILE
 */
unsigned char cls()
{
	__asm
	exx
	ld hl,($400c)
	ld bc,$0300
	ld d,$21
	inc l
	CLS:
		dec d
		jr z,NEWLINE
		ld (hl),$00
	DECC:
		inc hl
		dec c
		jr z,DECB
		jr CLS
	DECB:
		dec b
		jr z,EXIT
		jr CLS
	NEWLINE:
		ld (hl),$76
		ld d,$21
		jr DECC
	EXIT:
	call $0747
	exx
	__endasm;
}

/**
 * At last, the fast printAt function works
 * does a look-up on the text global above
 * to work out which character or string
 * to write to the DFILE and at what position
 *
 * @param	unsigned char, unsigned char
 * @author	sbebbington
 * @date	22 Aug 2017
 * @version	1.2b
 */
unsigned char printAt(unsigned short xy) __z88dk_fastcall
{
	__asm
	ld b,h
	ld c,l
	ld hl,($400c)
	inc l
	add hl,bc
	ld bc,_text
	CHAROUT:
		ld a,(bc)
		cp $ff
		jr z,RETURN
		ld (hl),a
		inc bc
		inc hl
		jr CHAROUT
	RETURN:
	__endasm;
}
