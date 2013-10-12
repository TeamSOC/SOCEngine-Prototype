//
//  MacroDefine.h
//  Created by SungBin_Hong on 13. 10. 13..
//  Copyright (c) 2013 years Teraphonia. All rights reserved.
//

#pragma once

// This is overflow check macro
// and this is about *unsigned int*
// Calculating to overflowed memory is...the way is a lot.
// for instance, *SUB* overflow check
/*
	unsigned int x1 = 0;
	unsigned int x2 = 4;

	if (OVERFLOWCHECK_SUB(x1, x2))
	{
		unsigned int maxuint = std::numeric_limits<unsigned int>::max();
		printf("current : %u \noverflowed %u\n", x1, maxuint - (x1 - x2) +1 );
	}

	// here is 4 byte overflowed.
*/
#define OVERFLOWCHECK_ADD(x, size) (((x) + (size) < (x)) ? true : false) 
#define OVERFLOWCHECK_SUB(x, size) (((x) - (size) > (x)) ? true : false) 
#define OVERFLOWCHECK_MUL(x1, x2) (( ((x2) != 0) && ((((x1) * (x2)) / (x2)) != (x1)) ) ? true : false)
#define OVERFLOWCHECK_DIV(x1, x2) () // Overflow by division is no exist