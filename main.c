#include <stdio.h>

int main();
int prompt();
int cls();

//				"012345678901234567890123456789012"
char title[] =	"       Monument Microgames\n      and Donkeysoft MMXVII\n\n         P R E S E N T S\n\n sunday league football manager\n   *** concept by: Shaun B\n   *** testing by: Graz R\n   *** greetings to all ZX fanz\n     P R E S S  A N Y  K E Y\n";



char teams[] = "";

unsigned int i;

int main()
{
	printf(title);
	prompt();
	gets(i);
	cls();
	printf("and we're done, for now\n");
	prompt();
	gets(i);
	return 0;
}

int prompt()
{
	printf("c:>");
	return 0;
}

int cls()
{
//	for(i=23; i>0; i--)
//	{
//		printf("\n");
//	}
//	#asm
//		call 0x0747
//	#endasm
//	return 0;
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
