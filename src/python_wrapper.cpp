#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "mfcc.h"

namespace py = pybind11;

PYBIND11_MODULE(mfcc_python, m) {
    py::class_<MFCC>(m, "MFCC")
        .def(py::init<>())
        .def("process_audio_segment", &MFCC::process_audio_segment)
        .def_readwrite("twiddle", &MFCC::twiddle)
        .def_readwrite("frame", &MFCC::frame)
        .def_readwrite("hamming", &MFCC::hamming)
        .def_readwrite("mfcc", &MFCC::mfcc)
        .def_readwrite("power_spectrum", &MFCC::power_spectrum)
        .def_readwrite("log_mel_coefficients", &MFCC::log_mel_coefficients)
        .def_readwrite("filter_banks", &MFCC::filter_banks)
        .def_readwrite("dct", &MFCC::dct)
        .def_readwrite("mfcc_output", &MFCC::mfcc_output);
}
