#pragma once

#include <string>

#include "drake/common/drake_copyable.h"
#include "drake/solvers/mathematical_program.h"

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

  struct SolveStatusInfo {
      double reported_runtime;
      double current_objective;
      double best_objective;
      double best_bound;
      int explored_node_count;
      int feasible_solutions_count;
  };

  // This passes the model and model environment to a
  // an external 
  typedef void (*mipNodeCallbackFunction)(const MathematicalProgram&, const SolveStatusInfo& callback_info, void *, Eigen::VectorXd&, VectorXDecisionVariable&);
  void addMIPNodeCallback(mipNodeCallbackFunction fnc, void * usrdata){
  	mip_node_callback_ = fnc;
  	mip_node_callback_usrdata_ = usrdata;
  }
  typedef void (*mipSolCallbackFunction)(const MathematicalProgram&, const SolveStatusInfo& callback_info, void *);
  void addMIPSolCallback(mipSolCallbackFunction fnc, void * usrdata){
  	mip_sol_callback_ = fnc;
  	mip_sol_callback_usrdata_ = usrdata;
  }

  SolutionResult Solve(MathematicalProgram& prog) const override;

  SolverType solver_type() const override { return SolverType::kGurobi; }

  std::string SolverName() const override { return "Gurobi"; }

  double get_best_bound() const { return best_bound_; }

 private:
  mipNodeCallbackFunction mip_node_callback_ = NULL;
  mipSolCallbackFunction mip_sol_callback_ = NULL;
  void * mip_node_callback_usrdata_ = NULL;
  void * mip_sol_callback_usrdata_ = NULL;
  double best_bound_ = -1.0;
};

}  // end namespace solvers
}  // end namespace drake
