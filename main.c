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

signed long money = 10000;

/**
 * Main entry point of game
 *
 * @param	na
 * @author	sbebbington
 * @date	21 Aug 20171
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
 *
 * @param	na
 * @author	sbebbington
 * @date	21 Aug 20171
 * @version	1.0
 */
unsigned char startGame()
{
	unsigned char yn[2];
	unsigned char _manager[16];
	prompt("please enter your name\n(max 16 characters, no spaces)", 8);
	_manager[0] = CLEAR;
	gets(_manager);
	if(!_manager[0])
	{
		main();
	}
	c = 0;
	while(_manager[c])
	{
		manager[c] = _manager[c];
		c++;
	}
	manager[c] = CLEAR;
	cls();
	printf("welcome %s\n", manager);
	prompt("would you like instructions Y/N?",0);
	gets(yn);
	if(yn[0] == 121)
	{
		cls();
		preSeasonPrompt();
	}
	while(money)
	{
		// game here
		money -= 5;
	}
}

/**
 * Basic instructions, probably typos therein
 *
 * @param	na
 * @author	sbebbington
 * @date	18 Aug 20171
 * @version	1.0
 */
void preSeasonPrompt()
{
	unsigned char ret = CLEAR;
	printf("welcome to one of\nthe toughest jobs in football.\nyour task is simple, to build\na new team for the ARSENIC\nCHEMICALS LTD. 2nd division and\ntake them to the ARSENIC\nCHEMICALS LTD. PRO LEAGUE.\nthere is also the sweet fa\nchallenge cup sponsored by\nBATRACHOTOXIN DRINKS CO which\ncould see your new team head\nall the way to the national\nstadium.\nyou start with £10,000 in cash,pre-season, you must sign\nplayers and establish a fan\nbase by playing friendlies. thenthe big season kicks off with\na mid-season transfer window to\ntake advantage of. if you are\nnot bankrupt by the end of the\nseason, you can do it all again\nwith your established team so\nthings should be easier.\ngood luck. press enter\n");
	prompt("",0);
	gets(ret);
}

/**
 * This sets the fast text output
 * by passing the already defined
 * ZX80 char array to the global
 * used in the printAt() function
 *
 * @param	na
 * @author	sbebbington
 * @date	21 Aug 20171
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
 * @date	20 Aug 20171
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
 * @date	18 Aug 2017
 * @version	1.0
 */
unsigned char cls()
{
	#asm
	exx
	ld hl,($400c)
	ld bc,$0300
	ld d,$21
	inc hl
	CLS:
		dec d
		jp z,NEWLINE
		ld (hl),$00
	DECC:
		inc hl
		dec c
		jp z,DECB
		jp CLS
	DECB:
		dec b
		jp z,EXIT
		jp CLS
	NEWLINE:
		ld (hl),$76
		ld d,$21
		jp DECC
	EXIT:
	call $0747
	exx
	#endasm
}

/**
 * At last, the fast printAt function works
 * does a look-up on the text global above
 * to work out which character or string
 * to write to the DFILE and at what position
 *
 * @param	unsigned char, unsigned char
 * @author	sbebbington
 * @date	21 Aug 2017
 * @version	1.2
 */
unsigned char printAt(unsigned short xy) __z88dk_fastcall
{
	#asm
	ld b,h
	ld c,l
	ld hl,($400c)
	inc hl
	add hl,bc
	ld bc,_text
	CHAROUT:
		ld a,(bc)
		cp $ff
		jr z,RETURN
		ld (hl),a
		inc bc
		inc hl
		jp CHAROUT
	RETURN:
	#endasm
}
