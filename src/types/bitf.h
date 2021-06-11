#ifndef ZAKAROUF__ZTYPES_TYPES__BITF_H
#define ZAKAROUF__ZTYPES_TYPES__BITF_H


#define z__BitFieldIndex__PRIV__gen(x) x

#define z__BitField_idTagIn(Tag, in) zpp__CAT(z__BitField_idTag(Tag), in)
#define z__BitField_idTag(Tag) BF_##Tag##_

#define z__BitField_id(Tag, ...)\
        enum{ zpp__Args_maplist_fn_Pattern(z__BitFieldIndex__PRIV__gen, z__BitField_idTag(Tag),, __VA_ARGS__) }

#define z__BitField_raw_set(of, bitIndex)       of |= 1 << (bitIndex)
#define z__BitField_raw_clear(of, bitIndex)     of &= ~(1 << (bitIndex))
#define z__BitField_raw_toggle(of, bitIndex)    of ^= 1 << (bitIndex)
#define z__BitField_raw_is(of, bitIndex)        of & (1 << (bitIndex))
#define z__BitField_raw_iseq(of, bitIndex)      ((of)&(bitIndex) == bitIndex)

#define z__BitField_set(of, tag, bitIndex)      z__BitField_raw_set(of, z__BitField_idTagIn(tag, bitIndex))
#define z__BitField_clear(of, tag, bitIndex)    z__BitField_raw_clear(of, z__BitField_idTagIn(tag, bitIndex))
#define z__BitField_toggle(of, tag, bitIndex)   z__BitField_raw_toggle(of, z__BitField_idTagIn(tag, bitIndex))
#define z__BitField_is(of, tag, bitIndex)       z__BitField_raw_is(of, z__BitField_idTagIn(tag, bitIndex))
#define z__BitField_iseq(of, tag, bitIndex)     z__BitField_raw_iseq(of, z__BitField_idTagIn(tag, bitIndex))



#endif

