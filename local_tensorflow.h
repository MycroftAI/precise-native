#pragma once

#ifdef REAL_TF
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/platform/env.h"
#else
#include "fake_tensorflow.h"
#endif
