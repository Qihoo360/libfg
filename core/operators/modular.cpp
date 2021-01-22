/* Copyright (c) 2021, Qihoo, Inc.  All rights reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 ==============================================================================*/

#include "core/operators/modular.h"
namespace perception_feature {
Modular::Modular() : BinaryOperator() {}

Modular::Modular(const std::string& first_feature,
                 const std::string& second_feature)
    : BinaryOperator() {
  children_.emplace_back(std::make_shared<Variable>(first_feature));
  children_.emplace_back(std::make_shared<Variable>(second_feature));
  init_status_ = true;
}

int Modular::Evaluate(const FeatureMap& feature_map,
                      std::shared_ptr<Feature>& feature) {
  feature = std::make_shared<Feature>();
  double left = 0, right = 0;
  GetTreeValue(feature_map, left, right);
  if (right == 0) {
    return ERR_OP_STATUS_FAILED;
  }
  feature->mutable_int64_list()->add_value((int64_t)left % (int64_t)right);
  return STATUS_OK;
}

std::shared_ptr<BaseOperator> Modular::Clone() const {
  return std::make_shared<Modular>();
}

}  // namespace perception_feature
