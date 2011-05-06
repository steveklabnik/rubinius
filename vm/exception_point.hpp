#ifndef RBX_EXCEPTION_POINT_HPP
#define RBX_EXCEPTION_POINT_HPP

#include <setjmp.h>

#include "windows_compat.h"

namespace rubinius {
  class NativeMethodEnvironment;

  class ExceptionPoint {
    bool jumped_to_;
    ExceptionPoint* previous_;

  public:
    jmp_buf __jump_buffer;

  public:
    ExceptionPoint(NativeMethodEnvironment* env);

    bool jumped_to() {
      return jumped_to_;
    }

    void reset() {
      jumped_to_ = false;
    }

    void return_to(NativeMethodEnvironment* env);

    void unwind_to_previous(NativeMethodEnvironment* env) {
      previous_->return_to(env);
    }

    void pop(NativeMethodEnvironment* env);
  };
}

#ifdef __xomb__
#define PLACE_EXCEPTION_POINT(ep) setjmp(ep.__jump_buffer)
#define _setjmp(x)       set_jump(x)
#define _longjmp(x, y)   long_jump(x, y)
#else
#define PLACE_EXCEPTION_POINT(ep) _setjmp(ep.__jump_buffer)
#endif

#endif
