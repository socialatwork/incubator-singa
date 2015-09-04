#include "hidden_layer.h"

#include "mshadow/tensor.h"
#include "mshadow/cxxnet_op.h"

namespace singa {
using namespace mshadow;
using mshadow::cpu;
using mshadow::Shape1;
using mshadow::Shape2;

inline Tensor<cpu, 2> NewTensor2(Blob<float>* blob) {
  const vector<int>& shape = blob->shape();
  Tensor<cpu, 2> tensor(blob->mutable_cpu_data(),
      Shape2(shape[0], blob->count() / shape[0]));
  return tensor;
}

inline Tensor<cpu, 1> NewTensor1(Blob<float>* blob) {
  Tensor<cpu, 1> tensor(blob->mutable_cpu_data(), Shape1(blob->count()));
  return tensor;
}


HiddenLayer::~HiddenLayer() {
  delete weight_;
  delete bias_;
}

void HiddenLayer::Setup(const LayerProto& proto, int npartitions) {
  Layer::Setup(proto, npartitions);
  CHECK_EQ(srclayers_.size(), 1);
  const auto& src = srclayers_[0]->data(this);
  batchsize_ = src.shape()[0];

  // please add code for setup this layer
}

void HiddenLayer::ComputeFeature(int flag, Metric* perf) {
  auto data = NewTensor2(&data_);
  auto src = NewTensor2(srclayers_[0]->mutable_data(this));
  auto weight = NewTensor2(weight_->mutable_data());
  auto bias = NewTensor1(bias_->mutable_data());
  // please add code for computing the hidden feature
}

void HiddenLayer::ComputeGradient(int flag, Metric* perf) {
  auto data = NewTensor2(&data_);
  auto src = NewTensor2(srclayers_[0]->mutable_data(this));
  auto grad = NewTensor2(&grad_);
  auto weight = NewTensor2(weight_->mutable_data());
  auto gweight = NewTensor2(weight_->mutable_grad());
  auto gbias = NewTensor1(bias_->mutable_grad());

  // please add code for computing the gradients

  if (srclayers_[0]->mutable_grad(this) != nullptr) {
    auto gsrc = NewTensor2(srclayers_[0]->mutable_grad(this));
    gsrc = dot(grad, weight);
  }
}
}