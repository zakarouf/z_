#ifndef ZAKAROUF__Z__UTF_H
#define ZAKAROUF__Z__UTF_H

#include "std/primitives.h"

z__bool z__utf8_is_valid(z__u8 const *str
					   , z__size size);
z__bool z__utf8_is_ascii(z__u8 const *str
					   , z__size size);
z__size z__utf8_get_len(z__u8 const *str
					  , z__size size);

#endif
