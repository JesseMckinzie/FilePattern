#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include "Pattern.hpp"
#include "FilePattern.hpp"
#include "StringPattern.hpp"
#include "ExternalPattern.hpp"
#include "ExternalFilePattern.hpp"

namespace py = pybind11;

//PYBIND11_MAKE_OPAQUE(std::vector<std::vector<Tuple>>);

PYBIND11_MODULE(backend, m){

    py::class_<Pattern>(m, "Pattern")
        .def("printValidFiles", &Pattern::printValidFiles)
        .def("filePatternToRegex", &Pattern::filePatternToRegex)
        .def("groupBy", &Pattern::groupBy)
        .def("split", &Pattern::split)
        .def("getMatching", &Pattern::getMatching)
        .def("printValidFiles", &Pattern::printValidFiles)
        .def("getValidFiles", &Pattern::getValidFiles)
        .def("getPattern", &Pattern::getPattern)
        .def("getRegexPattern", &Pattern::getRegexPattern)
        .def("getVariables", &Pattern::getVariables)
        .def("__iter__", [](const Pattern &v){ 
            return py::make_iterator(v.validFiles.begin(), v.validFiles.end());}, 
            py::keep_alive<0, 1>()); /* Keep vector alive while iterator is used */

    py::class_<FilePattern, Pattern>(m, "FilePattern")
        .def(py::init<const std::string &, const std::string &, bool>())
        .def("matchFiles", &FilePattern::matchFiles)
        .def("printFiles", &FilePattern::printFiles);

    py::class_<StringPattern, Pattern>(m, "StringPattern")
        .def(py::init<const std::string &, const std::string &>())
        .def("matchFiles", &StringPattern::matchFiles)
        .def("printFiles", &StringPattern::readFile);

    py::class_<ExternalPattern>(m, "ExternalPattern")
        //.def("invalidFilePath", &ExternalPattern::invalidFilePath)
        .def("filePatternToRegex", &ExternalPattern::filePatternToRegex)
        .def("split", &ExternalPattern::split)
        .def("printValidFiles", &ExternalPattern::printValidFiles)
        .def("getPattern", &ExternalPattern::getPattern)
        .def("getRegexPattern", &ExternalPattern::getRegexPattern)
        .def("setGroup", &ExternalPattern::setGroup);

    py::class_<ExternalFilePattern, ExternalPattern>(m, "ExternalFilePattern")
        .def(py::init<const std::string&, const std::string&, const std::string&, bool>())
        .def("matchFiles", &ExternalFilePattern::matchFiles)
        .def("printFiles", &ExternalFilePattern::printFiles)
        //.def("getMatching", &ExternalFilePattern::getMatching)
        .def("getValidFilesBlock", &ExternalFilePattern::getValidFilesBlock)
        .def("groupBy", &ExternalFilePattern::groupBy)
        .def("currentBlockLength", &ExternalFilePattern::currentBlockLength)
        .def("__iter__", [](ExternalFilePattern &v){ 
            v.next();
            return py::make_iterator(v.currentBlock.begin(), v.currentBlock.end());}, 
            py::keep_alive<0, 1>());
}
