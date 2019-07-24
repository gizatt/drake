# pragma once

#include "drake/systems/framework/diagram.h"

namespace drake {
namespace manipulation {
namespace robot_plan_runner {

/*
 * A system that takes in current robot state (q, v, tau_external) and a "plan"
 * (defined by PlanData), and calculates commands to be sent to the robot based
 * on the given plan.
 *
 * If control_period_sec is non-zero, a ZeroOrderHold with the same period is
 * added before the output of this system, which makes the entire system
 * discrete-time.
 *
 * Note that TaskSpacePlan always needs a non-zero control_period, because it
 * calculates the joint angle reference at the next time step as
 *  q_next = q_current + control_period * v_desired.
 */
class RobotPlanRunner : public systems::Diagram<double> {
 public:
  DRAKE_NO_COPY_NO_MOVE_NO_ASSIGN(RobotPlanRunner);
  /*
   * If is_discrete is true, A ZOH with period control_period_sec is
   * added. Otherwise the system is stateless.
   *
   * control_period_sec is passed to the controller subsystems regardless of
   * whether is_discrete is true of false. How it is
   * used in different plans is documented in controller_system.h
   */
  explicit RobotPlanRunner(
      bool is_discrete, double control_period_sec = 0.005);
};

}  // namespace robot_plan_runner
}  // namespace manipulation
}  // namespace drake