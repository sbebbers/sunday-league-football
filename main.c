#include <stdio.h>

#ifndef SCRLOC(X,Y)
	#define SCRLOC(X,Y)	(X<<8|Y)
#endif

#ifndef INVERSE(A)
	#define INVERSE(A)	(0x80 | A)
#endif

int main();
int prompt();
int cls();
int printAt(short xy, char string[32]);

//				"012345678901234567890123456789012"
char title[] =	"       Monument Microgames\n      and Donkeysoft MMXVII\n\n         P R E S E N T S\n\n sunday league football manager\n   *** concept by: Shaun B\n   *** testing by: Graz R\n   *** greetings to all ZX fanz\n     P R E S S  A N Y  K E Y\n";

char teams[256] = "team1,team2,team3";

char i[];
char x,y;
short z, _z;
char c;

/**
 * Main entry point of application
 *
 * @param	na
 * @author	sbebbington
 * @date	18 Aug 2017
 * @version	1.0
 * @return	int
 */
int main()
{
	cls();
	printf(title);
	prompt();
	gets(i);
	cls();
	prompt();
	x=10;
	y=10;
	printAt("hello", SCRLOC(x,y));
	gets(i);
	return 0;
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
		jr CLS
	DECB:
		dec b
		jp z,EXIT
		jr CLS
	NEWLINE:
		ld (hl),$76
		ld d,$21
		jr DECC
	EXIT:
	call $0747
	exx
	#endasm
	return 0;
}

/**
 * This should use HB/LB in a 16-bit word
 * to determine the X and Y co-ordinates
 * of the screen
 * printAt is limited to 32 characters per
 * call
 *
 * @param	short, char[]
 * @author	sbebbington
 * @date	18 Aug 2017
 * @version	1.0
 * @return	int
 */
int printAt(short xy, char string[32])
{
	#asm
	exx
	ld hl,$0002
	add hl,sp
	ld b,(hl)
	inc l
	jp z,INCH
	CONT:
		ld c,(hl)
		jr OUTPUT
	INCH:
		inc h
		jp CONT
	OUTPUT:
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; So we chould have x and y in the register
	;; pair BC, we now need to go C down and B
	;; across or something like that
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	exx
	#endasm
	
	printf(string);
	printf("%d",xy);
	return 0;
}
