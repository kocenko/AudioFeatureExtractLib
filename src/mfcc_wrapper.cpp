#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "mfcc.h"

namespace py = pybind11;

PYBIND11_MODULE(mfcc, m) {
    py::class_<MFCC>(m, "MFCC")
        .def(py::init<>())
        .def("process_audio_segment", &MFCC::process_audio_segment);
}