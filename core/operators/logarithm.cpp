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

#include "core/operators/logarithm.h"

#include "core/utils/convert_util.h"
#include "core/utils/feature_internal.h"
namespace perception_feature {
// const double EPS = 1e-320;
Logarithm::Logarithm() : UnaryOperator() {}

Logarithm::Logarithm(const std::string& feature_name)
    : UnaryOperator(feature_name) {
  children_.emplace_back(std::make_shared<Variable>(feature_name));
  init_status_ = true;
}

int Logarithm::Evaluate(const FeatureMap& feature_map,
                        std::shared_ptr<Feature>& feature) {
  feature = std::make_shared<Feature>();
  std::shared_ptr<Feature> child;
  if (opa_num_ != 1 || children_[0] == nullptr) {
    return ERR_OP_STATUS_FAILED;
  }
  if (children_[0]->Evaluate(feature_map, child) != STATUS_OK) {
    return ERR_OP_STATUS_FAILED;
  }
  double d_res;
  auto var = std::dynamic_pointer_cast<Variable>(children_[0]);
  ConvertUtil::ToDouble(*child, d_res);
  //  if (fabs(d_res) < EPS) {
  //    LOG(WARNING) << "the value of feature " << var->GetKey() << " is near
  //    zero"; return ERR_INVALID_VALUE;
  //  }
  GetFeatureValues<double>(feature.get())->Add(log(d_res));
  return STATUS_OK;
}
std::shared_ptr<BaseOperator> Logarithm::Clone() const {
  return std::make_shared<Logarithm>();
}

}  // namespace perception_feature
