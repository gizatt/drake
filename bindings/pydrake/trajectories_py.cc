#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "drake/bindings/pydrake/documentation_pybind.h"
#include "drake/bindings/pydrake/pydrake_pybind.h"
#include "drake/common/eigen_types.h"
#include "drake/common/trajectories/piecewise_polynomial.h"
#include "drake/common/trajectories/piecewise_quaternion.h"
#include "drake/common/trajectories/trajectory.h"

namespace drake {
namespace pydrake {

PYBIND11_MODULE(trajectories, m) {
  // NOLINTNEXTLINE(build/namespaces): Emulate placement in namespace.
  using namespace drake::trajectories;
  constexpr auto& doc = pydrake_doc.drake.trajectories;

  using T = double;

  py::class_<Trajectory<T>>(m, "Trajectory", doc.Trajectory.doc);

  py::class_<PiecewiseTrajectory<T>, Trajectory<T>>(
      m, "PiecewiseTrajectory", doc.PiecewiseTrajectory.doc)
      .def("get_number_of_segments",
          &PiecewiseTrajectory<T>::get_number_of_segments,
          doc.PiecewiseTrajectory.get_number_of_segments.doc)
      .def("start_time",
          overload_cast_explicit<double, int>(
              &PiecewiseTrajectory<T>::start_time),
          doc.PiecewiseTrajectory.start_time.doc)
      .def("end_time",
          overload_cast_explicit<double, int>(
              &PiecewiseTrajectory<T>::end_time),
          doc.PiecewiseTrajectory.end_time.doc)
      .def("duration", &PiecewiseTrajectory<T>::duration,
          doc.PiecewiseTrajectory.duration.doc)
      .def("start_time",
          overload_cast_explicit<double>(&PiecewiseTrajectory<T>::start_time),
          doc.PiecewiseTrajectory.start_time.doc)
      .def("end_time",
          overload_cast_explicit<double>(&PiecewiseTrajectory<T>::end_time),
          doc.PiecewiseTrajectory.end_time.doc)
      .def("get_segment_index", &PiecewiseTrajectory<T>::get_segment_index,
          doc.PiecewiseTrajectory.get_segment_index.doc)
      .def("get_segment_times", &PiecewiseTrajectory<T>::get_segment_times,
          doc.PiecewiseTrajectory.get_segment_times.doc);

  py::class_<PiecewisePolynomial<T>, PiecewiseTrajectory<T>>(
      m, "PiecewisePolynomial", doc.PiecewisePolynomial.doc)
      .def(py::init<>(), doc.PiecewisePolynomial.ctor.doc_0args)
      .def(py::init<const Eigen::Ref<const MatrixX<T>>&>(),
          doc.PiecewisePolynomial.ctor.doc_1args)
      .def_static("ZeroOrderHold",
          py::overload_cast<const Eigen::Ref<const Eigen::VectorXd>&,
              const Eigen::Ref<const MatrixX<T>>&>(
              &PiecewisePolynomial<T>::ZeroOrderHold),
          doc.PiecewisePolynomial.ZeroOrderHold.doc)
      .def_static("FirstOrderHold",
          py::overload_cast<const Eigen::Ref<const Eigen::VectorXd>&,
              const Eigen::Ref<const MatrixX<T>>&>(
              &PiecewisePolynomial<T>::FirstOrderHold),
          doc.PiecewisePolynomial.FirstOrderHold.doc)
      .def_static("Pchip",
          py::overload_cast<const Eigen::Ref<const Eigen::VectorXd>&,
              const Eigen::Ref<const MatrixX<T>>&, bool>(
              &PiecewisePolynomial<T>::Pchip),
          doc.PiecewisePolynomial.Pchip.doc)
      .def_static("Cubic",
          py::overload_cast<const Eigen::Ref<const Eigen::VectorXd>&,
              const Eigen::Ref<const MatrixX<T>>&,
              const Eigen::Ref<const VectorX<T>>&,
              const Eigen::Ref<const VectorX<T>>&>(
              &PiecewisePolynomial<T>::Cubic),
          py::arg("breaks"), py::arg("knots"), py::arg("knots_dot_start"),
          py::arg("knots_dot_end"),
          doc.PiecewisePolynomial.Cubic
              .doc_4args_breaks_knots_knots_dot_start_knots_dot_end)
      .def_static("Cubic",
          py::overload_cast<const Eigen::Ref<const Eigen::VectorXd>&,
              const Eigen::Ref<const MatrixX<T>>&,
              const Eigen::Ref<const MatrixX<T>>&>(
              &PiecewisePolynomial<T>::Cubic),
          py::arg("breaks"), py::arg("knots"), py::arg("knots_dot"),
          doc.PiecewisePolynomial.Cubic.doc_3args_breaks_knots_knots_dot)
      .def_static("Cubic",
          py::overload_cast<const Eigen::Ref<const Eigen::VectorXd>&,
              const Eigen::Ref<const MatrixX<T>>&, bool>(
              &PiecewisePolynomial<T>::Cubic),
          py::arg("breaks"), py::arg("knots"), py::arg("periodic_end"),
          doc.PiecewisePolynomial.Cubic
              .doc_3args_breaks_knots_periodic_end_condition)
      .def("value", &PiecewisePolynomial<T>::value,
          doc.PiecewisePolynomial.value.doc)
      .def("derivative", &PiecewisePolynomial<T>::derivative,
          doc.PiecewisePolynomial.derivative.doc)
      .def("rows", &PiecewisePolynomial<T>::rows,
          doc.PiecewisePolynomial.rows.doc)
      .def("cols", &PiecewisePolynomial<T>::cols,
          doc.PiecewisePolynomial.cols.doc)
      .def("slice", &PiecewisePolynomial<T>::slice,
          py::arg("start_segment_index"), py::arg("num_segments"),
          doc.PiecewisePolynomial.slice.doc)
      .def("shiftRight", &PiecewisePolynomial<T>::shiftRight, py::arg("offset"),
          doc.PiecewisePolynomial.shiftRight.doc);

  py::class_<PiecewiseQuaternionSlerp<T>, PiecewiseTrajectory<T>>(
      m, "PiecewiseQuaternionSlerp", doc.PiecewiseQuaternionSlerp.doc)
      .def(py::init<>(), doc.PiecewiseQuaternionSlerp.ctor.doc_0args)
      .def(py::init<const std::vector<double>&,
                    const std::vector<Quaternion<T>>&>(),
          py::arg("breaks"), py::arg("quaternions"),
          doc.PiecewiseQuaternionSlerp.ctor.doc_2args_breaks_quaternions)
      .def(py::init<const std::vector<double>&,
                    const std::vector<Matrix3<T>>&>(),
          py::arg("breaks"), py::arg("rot_matrices"),
          doc.PiecewiseQuaternionSlerp.ctor.doc_2args_breaks_rot_matrices)
      .def(py::init<const std::vector<double>&,
                    const std::vector<AngleAxis<T>>&>(),
          py::arg("breaks"), py::arg("ang_axes"),
          doc.PiecewiseQuaternionSlerp.ctor.doc_2args_breaks_ang_axes)
      .def("rows", &PiecewiseQuaternionSlerp<T>::rows,
          doc.PiecewiseQuaternionSlerp.rows.doc)
      .def("cols", &PiecewiseQuaternionSlerp<T>::cols,
          doc.PiecewiseQuaternionSlerp.cols.doc)
      .def("orientation", &PiecewiseQuaternionSlerp<T>::orientation,
          py::arg("t"), doc.PiecewiseQuaternionSlerp.orientation.doc)
      .def("value", &PiecewiseQuaternionSlerp<T>::value,
          py::arg("t"), doc.PiecewiseQuaternionSlerp.value.doc)
      .def("angular_velocity", &PiecewiseQuaternionSlerp<T>::angular_velocity,
          py::arg("t"), doc.PiecewiseQuaternionSlerp.angular_velocity.doc)
      .def("angular_acceleration", &PiecewiseQuaternionSlerp<T>::angular_acceleration,
          py::arg("t"), doc.PiecewiseQuaternionSlerp.angular_acceleration.doc)
      .def("get_quaternion_knots", &PiecewiseQuaternionSlerp<T>::get_quaternion_knots,
          doc.PiecewiseQuaternionSlerp.get_quaternion_knots.doc)
      .def("is_approx", &PiecewiseQuaternionSlerp<T>::is_approx,
          py::arg("other"), py::arg("tol"), doc.PiecewiseQuaternionSlerp.is_approx.doc);
}

}  // namespace pydrake
}  // namespace drake
