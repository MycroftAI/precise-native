#include "ModelRunner.hpp"
#include <iostream>


using namespace tensorflow;


void ModelRunner::checkError(Status status) {
    if (!status.ok()) {
        std::cerr << "FATAL ERROR:" << status.ToString() << "\n";
        throw "Error";
    }
}

ModelRunner::ModelRunner(const std::string &filename) {
    checkError(NewSession(SessionOptions(), &session));
    checkError(ReadBinaryProto(Env::Default(), filename, &graph_def));
    checkError(session->Create(graph_def));
}

ModelRunner::~ModelRunner() {
    session->Close();
}

float ModelRunner::run(float *mfccs) {
    Tensor mfccTensor(DT_FLOAT, TensorShape({1, NUM_MFCCS, MFCC_SIZE}));

    auto inputMap = mfccTensor.tensor<float, 3>();
    for (int i = 0; i < NUM_MFCCS; ++i) {
        for (int j = 0; j < MFCC_SIZE; ++j) {
            inputMap(0, i, j) = mfccs[i * MFCC_SIZE + j];
        }
    }

    std::vector <std::pair<std::string, tensorflow::Tensor>> inputs = {
            {"net_input", mfccTensor}
    };

    // The session will initialize the outputs
    std::vector <tensorflow::Tensor> outputs;

    // Run the session, evaluating our "c" operation from the graph
    checkError(session->Run(inputs, {"net_output"}, {}, &outputs));
    auto output_c = outputs[0].scalar<float>();

    // (There are similar methods for vectors and matrices here:
    // https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/public/tensor.h)
    return output_c();
}


