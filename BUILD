load("//tensorflow:tensorflow.bzl", "tf_cc_binary")

cc_library(
    name = "sdl2",
    hdrs = glob(["include/SDL2/*.h"]),
    defines = ["_REENTRANT"],
    includes = ["include/SDL2"],
    linkopts = ["-lSDL2"],
    visibility = ["//visibility:public"],
)

tf_cc_binary(
    name = "precise",
    srcs = [
    "precise.cc", "ModelRunner.cc", "ModelRunner.hpp",
    "kissfft/kissfft.hh", "mfcc/Mfcc.cpp", "mfcc/Mfcc.h",
    "RealtimeProcessor.hpp", "RealtimeProcessor.cpp",
    "AudioManager.cpp", "AudioManager.hpp"
    ],
    deps = [
        "//tensorflow/cc:cc_ops",
        "//tensorflow/cc:client_session",
        "//tensorflow/core:tensorflow",
        "sdl2"
    ],
    defines = ["REAL_TF"],
    linkopts = ["-lportaudio", "-lportaudiocpp", "-lSDL2", "-larriz"],
    copts = ["-fexceptions"]
)

