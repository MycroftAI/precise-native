#pragma once

#include "local_tensorflow.h"
#include <cstring>
#include <vector>

#define MFCC_SIZE (13)
#define NUM_MFCCS (29)

 class ModelRunner {
    tensorflow::Session *session;
    tensorflow::GraphDef graph_def;
    void checkError(tensorflow::Status status);
public:
    ModelRunner(const std::string &filename);
    ~ModelRunner();

    float run(float *mfccs);
};
