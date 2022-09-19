#include "filepattern.hpp"
#include <chrono>

using namespace std;

FilePatternObject::FilePatternObject(const string& path, const string& file_pattern, bool recursive, bool suppress_warnings) {
    std::cout << "constructor" << std::endl;
    this->setSuppressWarnings(suppress_warnings);

    if(file_pattern == ""){

        this->getPathFromPattern(path); // set path and file_pattern
        
        try {
            this->recursive_iterator_ = fs::recursive_directory_iterator(this->getPath());
            this->recursive_ = true;
            this->setJustPath(true);
        } catch (const std::runtime_error& e) {
            string error = "No directory found. Invalid path \"" + path + "\"."; 
            throw std::runtime_error(error);
        }
        std::cout << "constructor2" << std::endl;
    } else {

        std::cout << "constructor3" << std::endl;
        this->setJustPath(false);
        this->setPath(path); // store path to target directory
        this->setFilePattern(file_pattern); // cast input string to regex
        this->recursive_ = recursive; // Iterate over subdirectories
        std::cout << "constructor4" << std::endl;
        try {
            if(recursive){
                this->recursive_iterator_ = fs::recursive_directory_iterator(this->getPath());
            } else{ 
                this->iterator_ = fs::directory_iterator(this->getPath()); // store iterator for target directory
            }
        } catch (const std::runtime_error& e) {
            string error = "No directory found. Invalid path \"" + path + "\"."; 
            throw std::runtime_error(error);
        }
    }
    std::cout << "constructor5" << std::endl;
    this->setRegexFilePattern(""); // Regex version of pattern
    std::cout << "constructor6" << std::endl;

    this->matchFiles();
    std::cout << "constructor7" << std::endl;
    this->sortFiles();
    std::cout << "at end of constructor" << std::endl;
}

void FilePatternObject::printFiles(){
    for(const auto& file: this->iterator_){
        //cout << file << endl;
    }
}

void FilePatternObject::matchFilesOneDir(){
    Map mapping;
    vector<string> parsed_regex;

    int i, j;
    string s;
    string file, file_path;
    Tuple member;
    // Iterate over every file in directory
    regex pattern_regex = regex(this->getRegexFilePattern());
    smatch sm;
    for (const auto& entry : this->iterator_) {
        // Get the current file
        file_path = entry.path().string();
        replace(file_path.begin(), file_path.end(), '\\', '/');
        file = s::getBaseName(file_path);
        if(regex_match(file, sm, pattern_regex)){
            this->valid_files_.push_back(getVariableMap(file_path, sm)); // write to txt file
        }
    }
    /*
    if(valid_files.size() == 0){
        throw std::runtime_error("No files matched. Check that the pattern is correct.");
    }
    */
}

void FilePatternObject::matchFilesMultDir(){
    // Iterate over every file in directory
    regex pattern_regex = regex(this->getRegexFilePattern());
    Tuple tup;
    smatch sm;
    string file, file_path;
    // Iterate over directories and subdirectories
    for (const auto& entry : this->recursive_iterator_) {
        file_path = entry.path().string();
        replace(file_path.begin(), file_path.end(), '\\', '/');
        if(this->getJustPath()){
            file = s::eraseSubStr(file_path, this->getPath());
        } else {
            file = s::getBaseName(file_path);
        }
        
        if(regex_match(file, sm, pattern_regex)){
            if(this->getJustPath()) tup = getVariableMap(file_path, sm);
            else tup = getVariableMapMultDir(file_path, sm);
            if(get<0>(tup).size() > 0){
            this->valid_files_.push_back(tup); // write to txt file
            }
        }
    }
}

void FilePatternObject::matchFiles() {
    std::cout << "1" << std::endl;
    filePatternToRegex(); // Get regex of filepattern
    std::cout << "2" << std::endl;
    if(this->recursive_){
        std::cout << "3" << std::endl;
       this->matchFilesMultDir();
    } else {
        std::cout << "4" << std::endl;
        this->matchFilesOneDir();
    }
}
