/**
 * @file Pattern.hpp
 * @author Jesse McKinzie (Jesse.McKinzie@axleinfo.com)
 * @brief Parent class of FilePattern and ExternalFilePattern
 * @version 0.1
 * @date 2021-12-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <regex>
#include <map>
#include "Variables.hpp"

class Pattern {
    
    protected:
        std::regex regexExpression; // Regex expression
        std::string filePattern; // Pattern to match files to
        std::string regexFilePattern; // Pattern with capture groups
        std::vector<std::string> variables; // Store the names of variables from the pattern


    public:
        std::vector<Tuple> validFiles; // Store files that match given regex
        std::vector<std::vector<Tuple>> validGroupedFiles;

        /**
         * @brief Convert to pattern to regex.
         * 
         * Creates a version of the pattern with regex to match files to. For example, 
         * if the pattern contains {variable:d}, this is changed to [0-9] in the regex pattern.
         */
        void filePatternToRegex();

        /**
         * @brief Get the mapping of variables to values for a matching file. Used with a recursive directory iterator. 
         * 
         * Uses the regex version of the pattern from filePatternToRegex() to extract capture groups from
         * a basename. Returns a tuple of variable matched to capture group and the file path if no file with 
         * the same basename has already been matched and an empty tuple otherwise. In the later case, the 
         * basename is appending to the second member of the existing tuple.
         * 
         * @param filePattern filePath that matches the pattern
         * @param sm captured groups
         * @return Tuple A tuple with the mapping in first and the file path in second. An empty tuple is returned
         * if the basename of filePath has already been matched
         */
        Tuple getVariableMapMultDir(const std::string& filePath, const std::smatch& sm);


         /**
         * @brief Get the mapping of variables to values for a matching file. Used with a directory iterator.
         * 
         * Uses the regex version of the pattern from filePatternToRegex() to extract capture groups from
         * a basename. Returns a tuple of variable matched to capture group.
         * 
         * @param filePattern filePath that matches the pattern
         * @param sm captured groups
         * @return Tuple A tuple with the mapping in first and the file path in second 
         */
        Tuple getVariableMap(const std::string& filePath, const std::smatch& sm);

        /**
         * @brief Get the pattern to match files to.
         * 
         * @return std::string The pattern that files are matched to
         */
        std::string getPattern();

        /**
         * @brief Set the pattern.
         * 
         * @param pattern New pattern
         */
        void setPattern(const std::string& pattern);

        /**
         * @brief Get the pattern with regex capture groups
         * 
         * @return std::string The pattern with regex capture groups
         */
        std::string getRegexPattern();
        
        /**
         * @brief Get the variable names
         * 
         * @return std::vector<std::string> Vector of variable names
         */
        std::vector<std::string> getVariables();

        /**
         * @brief Prints the variables to the console.
         * 
         */
        void printVariables();
};