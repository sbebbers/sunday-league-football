#include <stdio.h>
#include <stdlib.h>
#include "zx80s.h"

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
unsigned char sign[] = 
{
	_S, _I, _G, _N, EOF
};
unsigned char signKeeper[] =
{
	_G, _O, _A, _L, CLEAR, _K, _E, _E, _P, _E, _R, EOF
};
unsigned char signDefender[] =
{
	_D, _E, _F, _E, _N, _D, _E, _R, EOF
};
unsigned char signMidFielder[] =
{
	_M, _I, _D, _F, _I, _E, _L, _D, _E, _R, EOF
};
unsigned char signStriker[] =
{
	_S, _T, _R, _I, _K, _E, _R, EOF
};

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
unsigned short entropy;

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
unsigned long expenses			= 0;
unsigned short matchAppearanceFee;

/**
 * Players
 */
unsigned char playerNames[]	= 
{
	EOF, _A, _N, _D, _R, _E, _W, _S, EOF, _J, _O, _H, _N, _S, EOF, _S, _M, _I, _T, _H, EOF, _A, _D, _L, _I, _M, EOF, _B, _A, _C, _O, _N, EOF, _H, _U, _L, _L, EOF, _C, _O, _N, _A, _N, EOF, _D, _A, _V, _I, _S, EOF, _J, _O, _H, _N, _S, _O, _N, EOF, _P, _I, _K, _E, EOF, _S, _M, _Y, _T, _H, EOF, _L, _E, _S, _T, _E, _R, EOF, _W, _E, _S, _T, _L, _Y, EOF, _Z, _E, _D, _D, _Y, EOF, _Y, _O, _U, _N, _G, EOF, _K, _R, _I, _L, _L, EOF, _M, _A, _R, _T, _Y, _N, EOF, _N, _I, _C, _H, _O, _L, _L, _S, EOF, _A, _D, _D, _E, _R, _S, EOF, _S, _C, _O, _T, _T, EOF, _S, _A, _N, _D, _B, _A, _C, _H, EOF, _R, _I, _C, _H, _A, _R, _D, _S, EOF, _D, _E, _N, _N, _I, _S, EOF, _J, _A, _M, _E, _S, _O, _N, EOF, _B, _O, _B, _S, EOF, _C, _A, _U, _L, _D, _W, _E, _L, _L, EOF, _V, _I, _V, EOF, _R, _U, _T, _T, _E, _R, EOF, _B, _E, _N, _N, _E, _T, _T, EOF, _R, _O, _Y, _L, _E, EOF, _P, _I, _N, _D, _E, _R, EOF, _L, _Y, _O, _N, _S, EOF, _O, _N, _I, _O, _N, _S, EOF, _F, _I, _F, _E, EOF, _R, _A, _N, _D, _S, EOF, _S, _T, _A, _R, _R, EOF, _G, _O, _R, _D, _O, _N, EOF, _C, _L, _I, _V, _E, EOF
};
unsigned char transferNames[] =
{
	EOF, _S, _I, _N, _C, _L, _A, _I, _R, EOF, _X, _Y, _L, _O, _N, EOF, _C, _U, _L, _L, _E, _N, EOF, _B, _R, _A, _N, _D, _S, EOF, _H, _A, _N, _T, _S, EOF
};

/**
 * Team builders
 */
unsigned char teamKeepers[]	= 
{
	EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF
};
unsigned char teamDefenders[] =
{
	EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF,
	EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF,
	EOF
};
unsigned char teamMidFielders[] = 
{
	EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF,
	EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF,
	EOF
};
unsigned char teamStrikers[] =
{
	EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF, EOF
};

unsigned char teamRatings[] =
{
	ONE, ONE, ONE, ONE, ONE, ONE, ONE, ONE, ONE, ONE, ONE, ONE, ONE, ONE, ONE, ONE, EOF
};

unsigned char goalKeeper[] =
{
	_G, _K, EOF
};

unsigned char defender[] =
{
	_D, _F, EOF
};

unsigned char midfielder[] =
{
	_M, _D, EOF
};

unsigned char striker[] =
{
	_S, _K, EOF
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
 * @date	02 Sep 2017
 * @version	1.2
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
	
	while(_strBuffer[++y] && y < 16)
	{
		manager[y] = _strBuffer[y];
	}
	entropy			+= srand(manager[0])%8;
	manager[y]		= 0;
	cls();
	
	gameManager();
}

/**
 * This will work out at which point in the
 * season the player is and therefore call
 * the relevant functions or sub routines
 *
 * @param	na
 * @author	sbebbington
 * @date	02 Sep 2017
 * @version	1.1
 */
void gameManager()
{
	unsigned char _strBuffer[STRBFSIZE];
	unsigned char gameBegins = 1;
	unsigned long weekNumber = 1;
	
	while(money > expenses)
	{
		if(gameBegins)
		{
			gameBegins--;
			numberOfPlayers	= 0;
			noOfGoalKeepers	= 0;
			noOfDefenders	= 0;
			noOfMidFielders	= 0;
			noOfStrikers	= 0;
			expenses		= 0;
			year			= 1;
			league			= 4;
			teamName[0]		= EOF;
			money			= 12500;
		}
		
		while(weekNumber < 7)
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
		if(numberOfPlayers < 15)
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
			y	= EOF;
			while(_strBuffer[++y])
			{
				teamName[y] = _strBuffer[y];
			}
			teamName[y]	= CLEAR;
		}
		if(y == 2 && numberOfPlayers < 15)
		{
			scoutForPlayers();
			actionNumber--;
		}
		if(y == 3 && numberOfPlayers)
		{
			viewSquad();
			actionNumber--;
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
			prompt("", 1);
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
 * Scout for and sign players
 *
 * @param	na
 * @author	sbebbington
 * @date	02 Sep 2017
 * @version	1.3
 */
void scoutForPlayers()
{
	unsigned char _strBuffer[STRBFSIZE];
	unsigned char x, y, pass;
	unsigned char playerName[16];
	playerName[16]	= EOF;
	pass			= 4;
	
	while(pass)
	{
		playerName[0]	= _A + srand(++entropy)%25;
		playerName[1]	= CLEAR;
		
		y = srand(entropy)%239;
		x = 2;
		while(playerNames[y++] != EOF){}
		
		while(playerNames[y] != EOF)
		{
			playerName[x++]	= playerNames[y++];
		}
		playerName[x]		= EOF;
		cls();
		
		setText(sign, 0, 0, 0);
		setText(playerName, 18, 0, 1);
		x = 5 * (srand(entropy)%48) + 5;
		
		if(noOfGoalKeepers == 3)
		{
			pass = 3;
		}
		if(pass == 4)
		{
			setText(signKeeper, 5, 0, 0);
		}
		if(noOfDefenders == 5)
		{
			pass = 2;
		}
		if(pass == 3)
		{
			setText(signDefender, 5, 0, 0);
		}
		if(noOfMidFielders == 5)
		{
			pass = 1;
		}
		if(pass == 2)
		{
			setText(signMidFielder, 5, 0, 0);
		}
		if(pass == 1 && noOfStrikers < 3)
		{
			setText(signStriker, 5, 0, 0);
		}
		if(pass)
		{
			printf("for £%d Y/N", x);
			prompt("", 1);
			gets(_strBuffer);
			if(_strBuffer[0] == 121)
			{
				money -= x;
				if(x > 100){
					teamRatings[numberOfPlayers] = ONE + srand(x) % 3;
					if(x > 185)
					{
						teamRatings[numberOfPlayers]++;
					}
				}
				numberOfPlayers++;
				y = 0;
				if(pass == 4)
				{
					noOfGoalKeepers++;
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
				if(pass == 3)
				{
					noOfDefenders++;
					for(x = 0; x < noOfDefenders; x++)
					{
						while(teamDefenders[y++] != EOF){}
					}
					x = 0;
					while(playerName[x] != EOF)
					{
						teamDefenders[y++]	= playerName[x++];
					}
				}
				if(pass == 2)
				{
					noOfMidFielders++;
					for(x = 0; x < noOfMidFielders; x++)
					{
						while(teamMidFielders[y++] != EOF){}
					}
					x = 0;
					while(playerName[x] != EOF)
					{
						teamMidFielders[y++]	= playerName[x++];
					}
				}
				if(pass == 1)
				{
					noOfStrikers++;
					for(x = 0; x < noOfStrikers; x++)
					{
						while(teamStrikers[y++] != EOF){}
					}
					x = 0;
					while(playerName[x] != EOF)
					{
						teamStrikers[y++]	= playerName[x++];
					}
				}
			}
			pass--;
		}
	}
}

/**
 * Runs a training session to improve
 * player ratings - training cost is
 * now determined by the number of
 * players in squad and improvements
 * only happen when you have > 5
 * players
 *
 * @param	na
 * @author	sbebbington
 * @date	02 Sep 2017
 * @version	1.2
 */
void trainingSession()
{
	unsigned char _strBuffer[STRBFSIZE], x = numberOfPlayers;
	if(numberOfPlayers > 5)
	{
		for(x; x > 0; x--)
		{
			if(teamRatings[x-1] < SEVEN && x)
			{
				teamRatings[x-1] += srand(++entropy)%2;
			}
		}
	}
	x = (10 + numberOfPlayers) * 5;
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
 * @date	02 Sep 2017
 * @version	1.1
 */
void rentGround()
{
	unsigned char _strBuffer[STRBFSIZE];
	unsigned char y;
	y	= 10 * (srand(++entropy)%24);
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
 * @date	02 Sep 2017
 * @version	1.2a
 */
void viewSquad()
{
	unsigned char _strBuffer[STRBFSIZE], x, y, p, inverse, z;
	y = 1;
	if(noOfGoalKeepers){
		p = 1;
		printf("player       RATING  position");
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
			_strBuffer[0]	= teamRatings[inverse];
			_strBuffer[1]	= EOF;
			setText(_strBuffer, 16, y, inverse%2);
			setText(goalKeeper, 24, y, inverse%2);
		}
		y++;
	}
	if(noOfDefenders){
		p = 1;
		for(x = noOfDefenders; x > 0; x--)
		{
			z = 0;
			while(teamDefenders[p] != EOF)
			{
				_strBuffer[z++]	= teamDefenders[p++];
			}
			_strBuffer[z]	= EOF;
			p++;
			setText(_strBuffer, 0, ++y, (++inverse)%2);
			_strBuffer[0]	= teamRatings[inverse];
			_strBuffer[1]	= EOF;
			setText(_strBuffer, 16, y, inverse%2);
			setText(defender, 24, y, inverse%2);
		}
		y++;
	}
	if(noOfMidFielders)
	{
		p = 1;
		for(x = noOfMidFielders; x > 0; x--)
		{
			z = 0;
			while(teamMidFielders[p] != EOF)
			{
				_strBuffer[z++]	= teamMidFielders[p++];
			}
			_strBuffer[z]	= EOF;
			p++;
			setText(_strBuffer, 0, ++y, (++inverse)%2);
			_strBuffer[0]	= teamRatings[inverse];
			_strBuffer[1]	= EOF;
			setText(_strBuffer, 16, y, inverse%2);
			setText(midfielder, 24, y, inverse%2);
		}
		y++;
	}
	if(noOfStrikers)
	{
		p = 1;
		for(x = noOfStrikers; x > 0; x--)
		{
			z = 0;
			while(teamStrikers[p] != EOF)
			{
				_strBuffer[z++]	= teamStrikers[p++];
			}
			_strBuffer[z]	= EOF;
			p++;
			setText(_strBuffer, 0, ++y, (++inverse)%2);
			_strBuffer[0]	= teamRatings[inverse];
			_strBuffer[1]	= EOF;
			setText(_strBuffer, 16, y, inverse%2);
			setText(striker, 24, y, inverse%2);
		}
	}
	prompt("", y);
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
	entropy++;
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
