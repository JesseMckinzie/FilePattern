#pragma once

#include <set>

#include "util/util.hpp"

class PatternObject {
    public:
        std::vector<Tuple> valid_files_; // Store files that match given regex
        
        std::vector<std::pair<std::vector<std::pair<std::string, Types>> , std::vector<Tuple>>> valid_grouped_files_; // 2D vector to store grouped files
        std::vector<std::string> group_; // current groupBy variable

        std::vector<std::string> variables_; // Store the names of variables from the pattern
        std::map<std::string, std::map<Types, int>> variable_occurrences_; // store the number of times a variable value occurs
        std::map<std::string, std::set<Types>> unique_values_; // store each unique value for every variable

        std::vector<std::string> named_groups_;
        std::vector<std::string> tmp_directories_; // store paths to all temporary directories used

        virtual std::vector<Tuple> getMatching(const std::vector<std::tuple<std::string, std::vector<Types>>>& variables) = 0;

        virtual std::map<std::string, std::map<Types, int>> getOccurrences(const std::vector<std::tuple<std::string, std::vector<Types>>>& mapping) = 0;

        virtual std::map<std::string, std::set<Types>> getUniqueValues(const std::vector<std::string>& mapping) = 0;

        virtual std::string outputName(std::vector<Tuple>& vec) = 0;
       
        virtual std::vector<std::string> getVariables() = 0;
       
        virtual void getNewNaming(std::string& pattern, bool suppressWarnings) = 0;

        virtual std::string swSearch(std::string& pattern, std::string& filename, const std::string& variables) = 0;
};

 