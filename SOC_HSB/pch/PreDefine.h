//
//  PreDefine.h
//  Created by SungBin_Hong on 13. 10. 13..
//  Copyright (c) 2013 years Teraphonia. All rights reserved.
//

#pragma once

#undef SAFE_DELETE
#define SAFE_DELETE(x) { if ( (x) != nullptr ) { delete (x); (x) = nullptr; } }

#define SAFE_FREE(x) { if ( (x) != nullptr ) { free(x); (x) = nullptr; } }