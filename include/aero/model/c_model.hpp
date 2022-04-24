#ifndef AERO_C_MODEL_HPP
#define AERO_C_MODEL_HPP

#include <aero/model/model.hpp>

namespace aero {

/// This model subclass allows access to models implemented in C
class CModel: public Model {
public:
  CModel(CModel&& other);
  CModel(void *c_model);
  ~CModel();
  CModel& operator=(CModel&& other);
  std::string name() const override;
  aero::State* create_state() const override;
  const aero::Grid& optics_grid() const override;
  void compute_optics(const aero::State& state,
                      aero::Array& od,
                      aero::Array& od_ssa,
                      aero::Array& od_asym) const override;

private:
  void *c_ptr_; // pointer to C model implementation
};
