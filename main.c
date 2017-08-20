#include <stdio.h>

#define SCRLOC(X,Y)	(((Y<<5)+Y)+X)
#define INVERSE(A)	(0x80 | A)
#define NL			0x76
#define EOF			0xff

int main();
int zx80Init();
int prompt();
int cls();
unsigned short printAt(unsigned short xy);

//				"012345678901234567890123456789012"
char title[] =	"       Monument Microgames\n      and Donkeysoft MMXVII\n\n         P R E S E N T S\n\n sunday league football manager\n   *** concept by: Shaun B\n   *** testing by: Graz R\n   *** greetings to all ZX fanz\n     P R E S S  A N Y  K E Y\n";

char teams[256] = "team1,team2,team3";

char c;

unsigned char text[32];

/**
 * Main entry point of application
 *
 * @param	na
 * @author	sbebbington
 * @date	18 Aug 20171
 * @version	1.0
 * @return	int
 */
int main()
{
	zx80Init();
	for(c=12;c>=0;c--)
	{
		printAt(SCRLOC(c,c));
	}
	gets(text);
//	
//	gets(i);
//	printf(title);
//	prompt();
//	gets(i);
//	cls();
//	prompt();
//	x=10;
//	y=10;
//	printAt("hello", SCRLOC(x,y));
//	gets(i);
	return 0;
}

int zx80Init()
{
	for(c=24;c>=0;c--)
	{
		printf("                                \n");
	}
	return cls();
}


/**
 * Outputs the prompt
 *
 * @param	na
 * @author	sbebbington
 * @date	18 Aug 2017
 * @version	1.0
 * @return	int
 */
int prompt()
{
	printf("c:>");
	return 0;
}

/**
 * Clears the screen
 *
 * @param	na
 * @author	sbebbington
 * @date	18 Aug 2017
 * @version	1.0
 * @return	int
 */
int cls()
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
 * At the moment, this is a test function that
 * will generate a single character at x,y position
 * change:
 *		ld c,$26
 * to the desired character to output, or change the
 * following line
 *
 * @param	unsigned short
 * @author	sbebbington
 * @date	20 Aug 2017
 * @version	1.2
 * @return	int
 */
unsigned char __FASTCALL__ printAt(unsigned short xy)
{
	#asm
	push bc
	ld b,h
	ld c,l
	ld hl,($400c)
	inc hl
	add hl,bc
	ld c,$26
	ld (hl),c
	pop bc
	#endasm
}
