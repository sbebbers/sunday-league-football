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
#define STRBFSIZE	0x1d

/**
 * Function prototypes
 */
int main();
void zx80Init();
void cls();
void startGame();
void gameManager();
void preSeasonOptions(unsigned char actionNumber, unsigned char weekNumber);
void scoutForPlayers();
void trainingSession();
void purchaseMinibus();
void rentGround();
void viewSquad();
unsigned char prompt(unsigned char txt[32], unsigned char lineNumber);
unsigned char printAt(unsigned short xy);
unsigned char setText(unsigned char txt[33], unsigned char x, unsigned char y, unsigned char inv);

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
/**
 * Game prompts
 */
unsigned char optionOnePreSeasonMsg[] =
{
	ONE, CBRACKET, CLEAR, _C, _H, _O, _O, _S, _E, CLEAR, _T, _E, _A, _M, CLEAR, _N, _A, _M, _E, EOF
};
unsigned char optionTwoPreSeasonMsg[] =
{
	TWO, CBRACKET, CLEAR, _S, _C, _O, _U, _T, CLEAR, _F, _O, _R, CLEAR, _P, _L, _A, _Y, _E, _R, _S, EOF
};
unsigned char optionThreePreSeasonMsg[] =
{
	THREE, CBRACKET, CLEAR, _V, _I, _E, _W, CLEAR, _C, _U, _R, _R, _E, _N, _T, CLEAR, _S, _Q, _U, _A, _D, EOF
};
unsigned char optionFourPreSeasonMsg[] =
{
	FOUR, CBRACKET, CLEAR, _C, _A, _L, _L, CLEAR, _T, _R, _A, _I, _N, _I, _N, _G, CLEAR, _S, _E, _S, _S, _I, _O, _N, EOF
};
unsigned char optionFivePreSeasonMsg[] =
{
	FIVE, CBRACKET, CLEAR, _B, _U, _Y, CLEAR, _K, _I, _T, EOF
};
unsigned char optionSixPreSeasonMsg[] =
{
	SIX, CBRACKET, CLEAR, _B, _U, _Y, CLEAR, _S, _Q, _U, _A, _D, CLEAR, _M, _I, _N, _I, _B, _U, _S, EOF
};
unsigned char optionSevenPreSeasonMsg[] =
{
	SEVEN, CBRACKET, CLEAR, _C, _H, _O, _O, _S, _E, CLEAR, _H, _O, _M, _E, CLEAR, _G, _R, _O, _U, _N, _D, EOF
};

/**
 * Sign players prompt
 */
unsigned char signKeeper[] =
{
	_S, _I, _G, _N, CLEAR,	_G, _O, _A, _L, CLEAR, _K, _E, _E, _P, _E, _R, EOF
};
unsigned char signDefender[] =
{
	_D, _E, _F, _E, _N, _D, _E, _R, CLEAR, CLEAR, CLEAR, EOF
};
unsigned char signMidFielder[] =
{
	_M, _I, _D, _F, _I, _E, _L, _D, _E, _R, CLEAR, EOF
};
unsigned char signStriker[] =
{
	_S, _T, _R, _I, _K, _E, _R, CLEAR, CLEAR, CLEAR, CLEAR, EOF
}

/**
 * Mini bus purchase prompt
 */
unsigned char miniBusOne[] =
{
	ONE, CBRACKET, CLEAR, _B, _A, _S, _I, _C, CLEAR, ONE, SIX, CLEAR, _S, _E, _A, _T, _E, _R, CLEAR, POUND, TWO, FIVE, ZERO, ZERO, EOF
};
unsigned char miniBusTwo[] =
{
	TWO, CBRACKET, CLEAR, _M, _I, _D, DASH, _R, _A, _N, _G, _E, CLEAR, ONE, EIGHT, CLEAR, _S, _E, _A, _T, _E, _R, CLEAR, POUND, THREE, THREE, NINE, FIVE, EOF
};
unsigned char miniBusThree[] =
{
	THREE, CBRACKET, CLEAR, _D, _E, _L, _U, _X, _E, CLEAR, _C, _L, _A, _S, _S, CLEAR, TWO, FOUR, CLEAR,  _S, _E, _A, _T, _E, _R, CLEAR, POUND, FIVE, FOUR, NINE, FIVE, EOF
};

/**
 * String buffers
 */
unsigned char text[33];
unsigned char manager[16];
unsigned char teamName[16];

/**
 * Game variables
 */
signed long money				= 1;
unsigned char year;
unsigned char league;
unsigned short entropy			= 1;

unsigned char numberOfPlayers	= 0;
unsigned char noOfGoalKeepers	= 0;
unsigned char noOfDefenders		= 0;
unsigned char noOfMidFielders	= 0;
unsigned char noOfStrikers		= 0;
unsigned char defenceRating		= 0;
unsigned char midfieldRating	= 0;
unsigned char attackRating		= 0;
unsigned char homeGroundRent	= 0;

unsigned char leaguePosition	= 0;
unsigned char cupRun			= 0;
unsigned char kitPurchased		= 0;
unsigned char minibusPurchased	= 0;

unsigned short income			= 0;
unsigned short expenses			= 0;
unsigned short matchAppearanceFee;

/**
 * Dictionary look-up to save bytes
 */
unsigned char the[]			= "the";
unsigned char you[]			= "you";
unsigned char and[]			= "and";

/**
 * Players
 */
unsigned char playerNames[]	= 
{
	EOF, _A, _N, _D, _R, _E, _W, _S, EOF, _J, _O, _H, _N, _S, EOF, _S, _M, _I, _T, _H, EOF, _A, _D, _L, _I, _M, EOF, _B, _A, _C, _O, _N, EOF, _H, _U, _L, _L, EOF, _C, _O, _N, _A, _N, EOF, _D, _A, _V, _I, _S, EOF, _J, _O, _H, _N, _S, _O, _N, EOF, _P, _I, _K, _E, EOF, _S, _M, _Y, _T, _H, EOF, _L, _E, _S, _T, _E, _R, EOF, _W, _E, _S, _T, _L, _Y, EOF, _Z, _E, _D, _D, _Y, EOF, _Y, _O, _U, _N, _G, EOF, _K, _R, _I, _L, _L, EOF,
	_M, _A, _R, _T, _Y, _N, EOF, _N, _I, _C, _H, _O, _L, _L, _S, EOF, _A, _D, _D, _E, _R, _S, EOF, _S, _C, _O, _T, _T, EOF, _S, _A, _N, _D, _B, _A, _C, _H, EOF, _R, _I, _C, _H, _A, _R, _D, _S, EOF, _D, _E, _N, _N, _I, _S, EOF, _J, _A, _M, _E, _S, _O, _N, EOF, _B, _O, _B, _S, EOF, _C, _A, _U, _L, _D, _W, _E, _L, _L, EOF, _V, _I, _V, EOF, _R, _U, _T, _T, _E, _R, EOF, _B, _E, _N, _N, _E, _T, _T, EOF, _R, _O, _Y, _L, _E,
	EOF, _P, _I, _N, _D, _E, _R, EOF, _L, _Y, _O, _N, _S, EOF, _O, _N, _I, _O, _N, _S, EOF, _F, _I, _F, _E, EOF, _R, _A, _N, _D, _S, EOF, _S, _T, _A, _R, _R, EOF, _G, _O, _R, _D, _O, _N, EOF, _C, _L, _I, _V, _E, EOF
};
unsigned char transferNames[] =
{
	EOF, _S, _I, _N, _C, _L, _A, _I, _R, EOF, _X, _Y, _L, _O, _N, EOF, _C, _U, _L, _L, _E, _N, EOF, _B, _R, _A, _N, _D, _S, EOF, _H, _A, _N, _T, _S,
};

/**
 * Team builders
 */
unsigned char teamKeepers[32]	= 
{
	EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF
};
unsigned char teamDefenders[53] =
{
	EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF,
	EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF,
	EOF
};
unsigned char teamMidFielders[53] = 
{
	EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF,
	EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF,
	EOF
};
unsigned char teamStrikers[26] =
{
	EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF
};

unsigned char teamRatings[17] =
{
	ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, EOF
};


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
void startGame()
{
	unsigned char _strBuffer[STRBFSIZE];
	unsigned char y = EOF;
	prompt("enter your name", 8);
	gets(_strBuffer);
	if(!_strBuffer[0])
	{
		main();
	}
	
	while(_strBuffer[++y])
	{
		manager[y] = _strBuffer[y];
	}
	entropy			+= srand(manager[0])%8;
	manager[y]		= 0;
	cls();
	
	printf("lets get started %s\n", manager);
	gets(_strBuffer);
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
	unsigned long weekNumber = 1;
	
	while(money)
	{
		if(gameBegins)
		{
			gameBegins--;
			numberOfPlayers	= 0;
			expenses		= 0;
			year			= 1;
			league			= 4;
			teamName[0]		= EOF;
			money			= 12500;
		}
		
		if(weekNumber < 7)
		{
			preSeasonOptions(5, weekNumber);
			weekNumber++;
		}
		money -= expenses;
	}
}

/**
 * Shows the available pre-season options
 *
 * @param	na
 * @author	sbebbington
 * @date	26 Aug 2017
 * @version	1.0
 */
void preSeasonOptions(unsigned char actionNumber, unsigned char weekNumber)
{
	while(actionNumber)
	{
		unsigned char _strBuffer[STRBFSIZE];
		unsigned char inverse;
		unsigned char y	= 5;
		cls();
		printf("PRE-SEASON week: %d\nnumber of players: %d\nmoney £%ld", weekNumber, numberOfPlayers, money);
		
		if(teamName[0] == EOF)
		{
			setText(optionOnePreSeasonMsg, 0, ++y, (++inverse)%2);
		}
		else
		{
			printf("\nteam name: %s", teamName);
		}
		if(numberOfPlayers < 18)
		{
			setText(optionTwoPreSeasonMsg, 0, ++y, (++inverse)%2);
		} 
		if(numberOfPlayers)
		{
			setText(optionThreePreSeasonMsg, 0, ++y, (++inverse)%2);
			setText(optionFourPreSeasonMsg, 0, ++y, (++inverse)%2);
		}
		if(!kitPurchased)
		{
			setText(optionFivePreSeasonMsg, 0, ++y, (++inverse)%2);
		}
		if(!minibusPurchased)
		{
			setText(optionSixPreSeasonMsg, 0, ++y, (++inverse)%2);
		}
		if(!homeGroundRent)
		{
			setText(optionSevenPreSeasonMsg, 0, ++y, (++inverse)%2);
		}
		prompt("choose your option", ++y);
		gets(_strBuffer);
		cls();
		
		y	= _strBuffer[0]-48;
		if(y == 1 && teamName[0] == EOF)
		{
			prompt("enter your team name", 1);
			gets(_strBuffer);
			y = EOF;
			while(_strBuffer[++y])
			{
				teamName[y] = _strBuffer[y];
			}
			teamName[y]	= CLEAR;
		}
		if(y == 2)
		{
			scoutForPlayers();
			actionNumber--;
		}
		if(y == 3 && numberOfPlayers)
		{
			viewSquad();
		}
		if(y == 4 && numberOfPlayers)
		{
			trainingSession();
			actionNumber = 0;
		}
		if(y == 5 && !kitPurchased)
		{
			kitPurchased++;
			money		-= 500;
			expenses	+= y;
			printf("kit purchased for full squad\nhome and away for £500\nweekly kit maintenance is £5");
			prompt("",1);
			gets(_strBuffer);
			actionNumber--;
		}
		if(y == 6 && !minibusPurchased)
		{
			purchaseMinibus();
			actionNumber--;
		}
		if(y == 7 && !homeGroundRent)
		{
			rentGround();
			actionNumber--;
		}
		entropy += y;
	}
}

/**
 * Sets up teams by signing players
 *
 * @param	na
 * @author	sbebbington
 * @date	27 Aug 2017
 * @version	1.2
 */
void scoutForPlayers()
{	
	unsigned char _strBuffer[STRBFSIZE];
	unsigned char x, y;
	unsigned char playerName[12];
	
	playerName[0]	= _A + srand(++entropy)%25;
	playerName[1]	= CLEAR;
	if(noOfGoalKeepers < 3)
	{
		y = srand(entropy)%239;
		x = 2;
		while(playerNames[y++] != EOF){}
		
		while(playerNames[y] != EOF)
		{
			playerName[x++]	= playerNames[y++];
		}
		playerName[x]		= EOF;
		setText(signKeeper, 0, 0, 0);
		setText(playerName, 18, 0, 1);
		x = 10 + srand(entropy)%240;
		while(++x%5){}
		printf("for £%d Y/N", x);
		prompt("", 1);
		gets(_strBuffer);
		if(_strBuffer[0] == 121)
		{
			money -= x;
			numberOfPlayers++;
			noOfGoalKeepers++;
			y = 0;
			for(x = 0; x < noOfGoalKeepers; x++)
			{
				while(teamKeepers[y++] != EOF){}
			}
			x = 0;
			while(playerName[x] != EOF)
			{
				teamKeepers[y++]	= playerName[x++];
			}
		}
	}
	if(noOfDefenders < 5)
	{
		y = srand(++entropy)%239;
		x = 2;
		while(defenders[y++] != EOF){}
		
		while(playerNames[y] != EOF)
		{
			playerName[x++]	= defenders[y++];
		}
		playerName[x]		= EOF;
		setText(signKeeper, 0, 0, 0);
		setText(playerName, 18, 0, 1);
		x = 10 + srand(entropy)%240;
		while(++x%5){}
		printf("for £%d Y/N", x);
		prompt("", 1);
		gets(_strBuffer);
		if(_strBuffer[0] == 121)
		{
			money -= x;
			numberOfPlayers++;
			noOfGoalKeepers++;
			y = 0;
			for(x = 0; x < noOfGoalKeepers; x++)
			{
				while(teamKeepers[y++] != EOF){}
			}
			x = 0;
			while(playerName[x] != EOF)
			{
				teamKeepers[y++]	= playerName[x++];
			}
		}
	}
}

/**
 * Runs a training session to improve
 * player ratings
 *
 * @param	na
 * @author	sbebbington
 * @date	27 Aug 2017
 * @version	1.1
 */
void trainingSession()
{
	unsigned char _strBuffer[STRBFSIZE], x;
	x = numberOfPlayers;
 	for(x; x > 0; x--)
	{
		if(teamRatings[x-1] < SEVEN && x)
		{
			teamRatings[x-1] += srand(++entropy)%2;
		}
	}
	x = srand(entropy) % 128;
	while(++x%5){}
	printf("the training session cost £%d\n\nview squad to see which players have improved",x);
	money -= x;
	prompt("",1);
	gets(_strBuffer);
}

/**
 * Buy your minibus here
 *
 * @param	na
 * @author	sbebbington
 * @date	28 Aug 2017
 * @version	1.0
 */
void purchaseMinibus()
{
	unsigned char _strBuffer[STRBFSIZE];
	unsigned char inverse, y;
	
	setText(miniBusOne, 0, ++y, (++inverse)%2);
	setText(miniBusTwo, 0, ++y, (++inverse)%2);
	setText(miniBusThree, 0, ++y, (++inverse)%2);
	prompt("select your team bus",++y);
	gets(_strBuffer);
	y	= _strBuffer[0]-48;
	
	if(y < 1 || y > 3)
	{
		return;
	}
	if(y == 1)
	{
		money -= 2500;
	}
	else if(y == 2)
	{
		money -= 3595;
	}
	else
	{
		money -= 5495;
	}
	minibusPurchased++;
	expenses	+= 15;
}

/**
 * Adds in a ground rent logic
 *
 * @param	na
 * @author	sbebbington
 * @date	28 Aug 2017
 * @version	1.0
 */
void rentGround()
{
	unsigned char _strBuffer[STRBFSIZE];
	unsigned char y;
	y	= INVERSE(srand(++entropy)%248);
	while(++y%10){}
	printf("a local rugby league club has\noffer a ground share for £%d\nwith weekly expenses of £25",y);
	prompt("Y/N?",1);
	gets(_strBuffer);
	if(_strBuffer[0] == 121)
	{
		money		-= y;
		expenses	+= 25;
		homeGroundRent++;
	}
}

/**
 * Shows the current squad of players
 *
 * @param	na
 * @author	sbebbington
 * @date	27 Aug 2017
 * @version	1.1
 */
void viewSquad()
{
	unsigned char _strBuffer[STRBFSIZE], x, y, p, inverse, z;
	y = 1;
	if(noOfGoalKeepers){
		p = 1;
		printf("goal keepers:   rating:");
		for(x = noOfGoalKeepers; x > 0; x--)
		{
			z = 0;
			while(teamKeepers[p] != EOF)
			{
				_strBuffer[z++]	= teamKeepers[p++];
			}
			_strBuffer[z]	= EOF;
			p++;
			setText(_strBuffer, 0, ++y, (++inverse)%2);
			_strBuffer[0]	= teamRatings[y-2];
			_strBuffer[1]	= EOF;
			setText(_strBuffer, 16, y, inverse%2);
			printf("\n");
		}
	}
	++entropy;
	prompt("press new line", ++y);
	gets(_strBuffer);
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
	unsigned char c = 0;
	while(txt[c] != EOF)
	{
		++entropy;
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
void zx80Init()
{
	unsigned char y;
	text[0] = EOF;
	for(y = 24; y > 0; y--)
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
	unsigned char y;
	if(lineNumber)
	{
		++entropy;
		for(y = lineNumber; y > 0; y--)
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
 */
void cls()
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
	++entropy;
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
