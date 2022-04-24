#ifndef AERO_FORTRAN_MODEL_HPP
#define AERO_FORTRAN_MODEL_HPP

#include <aero/model/model.hpp>

namespace aero {

/// This model subclass allows access to models implemented in Fortran
class FortranModel: public Model {
public:
  FortranModel(void *fortran_model);
  ~FortranModel();
  FortranModel& operator=(FortranModel&& other);
  std::string name() const override;
  aero::State* create_state() const override;
  const aero::Grid& optics_grid() const override;
  void compute_optics(const aero::State& state,
                      aero::Array& od,
                      aero::Array& od_ssa,
                      aero::Array& od_asym) const override;

private:
  void *f_ptr_; // pointer to Fortran model implementation
};
