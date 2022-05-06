#ifndef ZAKAROUF__ZTYPES_TYPES__BITF_H
#define ZAKAROUF__ZTYPES_TYPES__BITF_H


#define z__BitFieldIndex__PRIV__gen(x) x

#define z__BitField_idTagIn(Tag, in) zpp__CAT(z__BitField_idTag(Tag), in)
#define z__BitField_idTag(Tag) BF_##Tag##_

#define z__BitField_id(Tag, ...)\
        enum{ zpp__Args_maplist_fn_Pattern(z__BitFieldIndex__PRIV__gen, z__BitField_idTag(Tag),, __VA_ARGS__) }

#define z__bitf_set(b, offset)       b |= 1 << (offset)
#define z__bitf_clear(b, offset)     b &= ~(1 << (offset))
#define z__bitf_toggle(b, offset)    b ^= 1 << (offset)
#define z__bitf_is(b, offset)        b & (1 << (offset))
#define z__bitf_has(b, offset)       (((b) >> (offset))&1)
#define z__bitf_iseq(b, offset)      ((b)&(offset) == offset)
//#define z__bitf(method, b, offset)   zpp__CAT(z__bitf_, method)(b, offset)   

#define z__BitField_set(of, tag, bitIndex)      z__bitf_set(of, z__BitField_idTagIn(tag, bitIndex))
#define z__BitField_clear(of, tag, bitIndex)    z__bitf_clear(of, z__BitField_idTagIn(tag, bitIndex))
#define z__BitField_toggle(of, tag, bitIndex)   z__bitf_toggle(of, z__BitField_idTagIn(tag, bitIndex))
#define z__BitField_is(of, tag, bitIndex)       z__bitf_is(of, z__BitField_idTagIn(tag, bitIndex))
#define z__BitField_iseq(of, tag, bitIndex)     z__bitf_iseq(of, z__BitField_idTagIn(tag, bitIndex))



#endif

