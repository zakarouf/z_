#ifndef ZAKAROUF__ZPREP_EVAL_H
#define ZAKAROUF__ZPREP_EVAL_H

#define zpp__PRIV__EVAL0(...) __VA_ARGS__
#define zpp__PRIV__EVAL1(...) zpp__PRIV__EVAL0(zpp__PRIV__EVAL0(zpp__PRIV__EVAL0(__VA_ARGS__)))
#define zpp__PRIV__EVAL2(...) zpp__PRIV__EVAL1(zpp__PRIV__EVAL1(zpp__PRIV__EVAL1(__VA_ARGS__)))
#define zpp__PRIV__EVAL3(...) zpp__PRIV__EVAL2(zpp__PRIV__EVAL2(zpp__PRIV__EVAL2(__VA_ARGS__)))
#define zpp__PRIV__EVAL4(...) zpp__PRIV__EVAL3(zpp__PRIV__EVAL3(zpp__PRIV__EVAL3(__VA_ARGS__)))
#define zpp__PRIV__EVAL(...)  zpp__PRIV__EVAL4(zpp__PRIV__EVAL4(zpp__PRIV__EVAL4(__VA_ARGS__)))

#define zpp__eval(...)      zpp__PRIV__EVAL(__VA_ARGS__)


#endif
