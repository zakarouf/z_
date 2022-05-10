#include "../../src/types/obj.h"
#include "../../src/imp/test.h"

#define TEST_SUITE types_obj
#define TEST(name) z__test_def(TEST_SUITE, name)

typedef
    struct {
        int x, y;
        /* Data Related to player */
} Player;

typedef
    struct {
        int x, y;
        /* Data Related to enemy */
} Enemy;

static
z__objfn_defcl(Enemy, Actor, Move, void, int x, int y)
{
    z__objfn_clself(Enemy);
    self->x += x;
    self->y += y;
}

static
z__objfn_defcl(Player, Actor, Move, void, int x, int y)
{
    z__objfn_clself(Player);
    self->x += x;
    self->y += y;
}

z__objcl(Actor, (), (Move, void, int, int));
z__objcl_impl(Actor, Player, Move);
z__objcl_impl(Actor, Enemy, Move);

TEST(obj_check)
{
    Player p = { .x = 10, .y = 50 };
    Enemy e = { .x = 10, .y = 50 };

    Actor actor[2];
    z__objcl_set(&actor[0], Actor, &p, Player);
    z__objcl_set(&actor[1], Actor, &e, Enemy);

    z__objcl_call(&actor[0], Move, 10, 23);
    z__objcl_call(&actor[1], Move, -3, 20);

    z__test_assert((p.x == 20 && p.y == 73), "");
    z__test_assert((e.x == 7 && e.y == 70), "");

    z__test_done();
}

z__test_impl(TEST_SUITE, obj_check);

