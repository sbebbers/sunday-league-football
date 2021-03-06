/**
 * Repurposed ZX81 header for the ZX80
 *
 * @author:     Shaun B
 * @version:    1.0.4 - 2017-08-21
 *
 */

/// Pre-processor symbols:
#define CLEAR 		  0x00
#define QUOTE   		0x01
#define LEFT    		0x02
#define BOTTOM      0x03
#define TL    			0x04
#define TR    			0x05
#define BL    			0x06
#define BR  	  		0x07
#define BLTR    		0x08
#define CHESSBOARD	0x09
#define CHESSBTM  	0x0a
#define CHESSTOP  	0x0b
#define POUND   		0x0c
#define DOLLAR  		0x0d
#define COLON   		0x0e
#define QM    			0x0f
#define OBRACKET  	0x10
#define CBRACKET  	0x11
#define DASH    		0x12
#define PLUS    		0x13
#define STAR    		0x14
#define SLASH   		0x15
#define EQUALS  		0x16
#define GT    			0x17
#define LT     			0x18
#define SEMI    		0x19
#define COMMA   		0x1a
#define DOT   			0x1b
#define ZERO    		0x1c
#define ONE   			0x1d
#define TWO   			0x1e
#define THREE   		0x1f
#define FOUR    		0x20
#define FIVE    		0x21
#define SIX   			0x22
#define SEVEN   		0x23
#define EIGHT   		0x24
#define NINE    		0x25
#define	_A    			0x26
#define _B    			0x27
#define _C    			0x28
#define _D    			0x29
#define _E    			0x2a
#define _F    			0x2b
#define _G    			0x2c
#define _H    			0x2d
#define _I    	 		0x2e
#define _J    			0x2f
#define _K    			0x30
#define _L    			0x31
#define _M    			0x32
#define _N    			0x33
#define _O    			0x34
#define _P    			0x35
#define _Q    			0x36
#define _R    			0x37
#define _S    			0x38
#define _T    			0x39
#define _U    			0x3a
#define _V    			0x3b
#define _W    			0x3c
#define _X    			0x3d
#define _Y    			0x3e
#define _Z    			0x3f
#define SCRLOC(X,Y)	(((Y<<5)+Y)+X)
#define INVERSE(A)	(0x80 | A)
#define NL    			0x76
#define EOF   			0xff
#define DFILE   		$400c
#define STRBFSIZE 	0x18
