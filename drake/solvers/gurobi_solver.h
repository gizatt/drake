#pragma once

#include <string>

#include "drake/common/drake_copyable.h"
#include "drake/solvers/mathematical_program_solver_interface.h"

namespace drake {
namespace solvers {

class GurobiSolver : public MathematicalProgramSolverInterface {
 public:
  DRAKE_NO_COPY_NO_MOVE_NO_ASSIGN(GurobiSolver)

  GurobiSolver() = default;
  ~GurobiSolver() override = default;

  // This solver is implemented in various pieces depending on if
  // Gurobi was available during compilation.
  bool available() const override;

  // This passes the model and model environment to a
  // an external 
  typedef std::pair<
    const Eigen::Ref<const Eigen::VectorXd>&,
    const Eigen::Ref<const VectorXDecisionVariable>&
  > mipSolCallbackReturn;
  typedef mipSolCallbackReturn (*mipSolCallbackFunction)(const MathematicalProgram&, void *);
  void addMIPSolCallback(mipSolCallbackFunction fnc, void * usrdata){
  	mip_sol_callback_ = fnc;
  	mip_sol_callback_usrdata_ = usrdata;
  }

  SolutionResult Solve(MathematicalProgram& prog) const override;

  SolverId solver_id() const override;

  /// @return same as MathematicalProgramSolverInterface::solver_id()
  static SolverId id();

 private:
  mipSolCallbackFunction mip_sol_callback_ = NULL;
  void * mip_sol_callback_usrdata_ = NULL;
};

}  // end namespace solvers
}  // end namespace drake
