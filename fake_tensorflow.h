#pragma once

#include <vector>
#include <string>

namespace tensorflow {
    class Status {
    public:
        bool ok() {
            return true;
        }
        std::string ToString(){return "";}
    };
    class Tensor;
    class GraphDef {

    };
    class Session {
    public:
        Status Close() {
            return Status();
        }
        Status Create(GraphDef d) {
            return Status();
        }
        Status Run(std::vector <std::pair<std::string, Tensor>> inputs, std::vector<std::string> outputsNames, std::vector<int> other, std::vector<Tensor> *outputs) {
            if (outputs->size() < 1) {
                outputs->emplace_back();
            }
            return Status();
        }
    };

    namespace Env {
        int Default() {
            return 0;
        }
    }
    int ModelOptions() {
        return 0;
    }
    Status ReadBinaryProto(int env, const std::string &filename, const GraphDef *def) {
        return Status();
    }
    int SessionOptions() {
        return 0;
    }
    Status NewSession(int options, Session **session) {
        return Status();
    }
    const int DT_FLOAT = 0;
    struct TensorShape {
        int x, y, z;
    };

    class InputMapper {
        float num;
    public:
        float &operator()(int a, int b, int c) {
            return num;
        }
    };

    class TensorScalar {
    public:
        float operator()() {
            return 0.f;
        }
    };

    class Tensor {
    public:
        Tensor() = default;
        Tensor(int flags, TensorShape shape) {}

        template<typename T, size_t N>
        InputMapper tensor() {
            return InputMapper();
        }
        template<typename T>
        TensorScalar scalar() {
            return TensorScalar();
        }
    };


}
