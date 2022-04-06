#pragma once
#include "internal_pattern.hpp"
#include "../util/vector_parser.hpp"
#include "../util/util.hpp"


class VectorPattern: public InternalPattern {

    public:
        std::string path; // path to stitching vector
        std::regex STITCH_REGEX; // regex to match stitching vector line
        std::vector<std::string> STITCH_VARIABLES; // variable names for stitching vector 
        std::ifstream infile; // stream to read in stitching vector

        /**
         * @brief Constructor of VectorPattern.
         * 
         * @param path Path to stitching vector
         * @param pattern Pattern to match filename to
         */
        VectorPattern(const std::string& path, const std::string& pattern, bool suppressWarnings);

        /**
         * @brief Match filenames to the pattern.
         * 
         * Compares the filename from each line of the stitching vector to the provided pattern.
         * Each variable from the line of the stitching vector is extracted and added to the variable value 
         * map. Each variable from the named groups in the pattern are also added to the mapping. The matching
         * files are stored in memory in the validFiles vector.
         */
        void matchFiles();

        /**
         * @brief Makes a guess of the pattern given a stitching vector.
         * 
         * Reads in the filenames from the stitching vector and makes a guess of the pattern.
         * 
         * @param path Path to the stitching vector.
         * @param variables Name of variables. Optional
         * @return std::string Guess of the pattern
         */
        static std::string inferPattern(const std::string& path, std::string& variables);
};