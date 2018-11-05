
# Precise Native

*Precise written in C++*

## Compiling With Tensorflow

Due to how tensorflow C bindings work, the only way to compile the project is by compiling it within the tensorflow source code. Steps to build:

 - Follow [Tensorflow source instructions](https://www.tensorflow.org/install/source)
 - Clone precise into `tensorflow/tensorflow/cc/precise` (where first tensorflow is the clone)

```bash
cd <PATH_TO_TENSORFLOW>
git clone https://github.com/mycroftai/precise-native tensorflow/cc/precise
bazel run //tensorflow/cc/precise
```

## Compiling Without Tensorflow

You can build the code with tensorflow library functions mocked out (for faster + simpler compilation) by using cmake:

```bash
mkdir build
cd build
cmake ..
make
./precise_demo
```


