//
// Created by fss on 23-1-23.
//
#include <gtest/gtest.h>
#include "layer/abstract/param_layer.hpp"

TEST(test_param_layer, set_weight1) {
  using namespace kuiper_infer;
  ParamLayer param_layer("param");
  uint32_t weight_count = 4;
  std::vector<std::shared_ptr<ftensor >> weights;
  for (uint32_t w = 0; w < weight_count; ++w) {
    std::shared_ptr<ftensor> weight = std::make_shared<ftensor>(3, 32, 32);
    weights.push_back(weight);
  }
  param_layer.set_weights(weights);
  const auto &weights_ = param_layer.weights();
  ASSERT_EQ(weights.size(), weight_count);

  for (uint32_t w = 0; w < weight_count; ++w) {
    const auto &weight_ = weights_.at(w);
    const auto &weight = weights.at(w);
    ASSERT_EQ(weight->size(), weight_->size());
    for (uint32_t i = 0; i < weight->size(); ++i) {
      ASSERT_EQ(weight->index(i), weight_->index(i));
    }
  }
}

TEST(test_param_layer, set_bias1) {
  using namespace kuiper_infer;
  ParamLayer param_layer("param");
  uint32_t bias_count = 4;
  std::vector<std::shared_ptr<ftensor >> biases;
  for (uint32_t w = 0; w < bias_count; ++w) {
    std::shared_ptr<ftensor> bias = std::make_shared<ftensor>(1, 32, 1);
    biases.push_back(bias);
  }
  param_layer.set_bias(biases);
  const auto &biases_ = param_layer.bias();
  ASSERT_EQ(biases.size(), biases_.size());

  for (uint32_t w = 0; w < bias_count; ++w) {
    const auto &bias_ = biases_.at(w);
    const auto &bias = biases.at(w);
    ASSERT_EQ(bias->size(), bias_->size());
    for (uint32_t i = 0; i < bias->size(); ++i) {
      ASSERT_EQ(bias->index(i), bias_->index(i));
    }
  }
}

TEST(test_param_layer, set_weight2) {
  using namespace kuiper_infer;
  ParamLayer param_layer("param");
  uint32_t weight_count = 9;
  std::vector<float> weights;
  for (int i = 0; i < weight_count; ++i) {
    weights.push_back(float(i));
  }
  std::vector<std::shared_ptr<ftensor >> weights_;
  std::shared_ptr<ftensor> weight = std::make_shared<ftensor>(1, 3, 3);
  weights_.push_back(weight);
  param_layer.set_weights(weights_);

  param_layer.set_weights(weights);
  weights_ = param_layer.weights();
  for (int i = 0; i < weights_.size(); ++i) {
    const auto weight_ = weights_.at(i);
    int index = 0;
    for (int r = 0; r < 3; ++r) {
      for (int c = 0; c < 3; ++c) {
        ASSERT_EQ(weight_->at(0, r, c), index);
        index += 1;
      }
    }
  }
}

TEST(test_param_layer, set_bias2) {
  using namespace kuiper_infer;
  ParamLayer param_layer("param");
  uint32_t weight_count = 9;
  std::vector<float> biases;
  for (int i = 0; i < weight_count; ++i) {
    biases.push_back(float(i));
  }
  std::vector<std::shared_ptr<ftensor >> biases_;
  std::shared_ptr<ftensor> bias = std::make_shared<ftensor>(1, 9, 1);
  biases_.push_back(bias);
  param_layer.set_bias(biases_);

  param_layer.set_bias(biases);
  biases_ = param_layer.bias();
  for (int i = 0; i < biases_.size(); ++i) {
    const auto bias_ = biases_.at(i);
    int index = 0;
    for (int r = 0; r < 9; ++r) {
      ASSERT_EQ(bias_->at(0, r, 0), index);
      index += 1;
    }
  }
}
