#include "filepattern.h"

FilePattern::FilePattern(const std::string& path, const std::string& filePattern, const std::string& block_size, bool recursive, bool suppressWarnings) {

    /*
    PatternInitializer pi;
    pi.block_size = block_size;
    pi.path = path;
    pi.file_pattern = filePattern;
    pi.recursive = recursive;
    pi.suppress_warnings = suppressWarnings;
    */

    std::cout << "here" << std::endl;
    FilePatternFactory fpf = FilePatternFactory();
    std::cout << "here1" << std::endl;
    this->fp_ = std::unique_ptr<PatternObject>(fpf.getObject(path, filePattern, block_size, recursive, suppressWarnings));
    std::cout << "here2" << std::endl;
}

std::vector<Tuple> FilePattern::getMatching(const std::vector<std::tuple<std::string, std::vector<Types>>>& variables) {
    return this->getMatching(variables);
    /*
    if (this->fp_->group_.size() == 0) {
        return this->fp_->getMatching(variables);
    } else {
        this->fp_->getMatching(variables);
        return this->fp_->getMatchingBlock();
    }
    */
}

void FilePattern::setGroup(std::string& groups){
    std::vector<std::string> group_vec = {groups};
    this->fp_->group_ = group_vec;
}

void FilePattern::setGroup(std::vector<std::string>& groups) {
    this->fp_->group_ = groups;
}

std::map<std::string, std::map<Types, int>> FilePattern::getOccurrences(const std::vector<std::tuple<std::string, std::vector<Types>>>& mapping) {
    return this->fp_->getOccurrences(mapping);
}

std::map<std::string, std::set<Types>> FilePattern::getUniqueValues(const std::vector<std::string>& mapping) {
    return this->fp_->getUniqueValues(mapping);
}

std::string FilePattern::outputName(std::vector<Tuple>& vec) {
    return this->fp_->outputName(vec);
}

std::vector<std::string> FilePattern::getVariables() {
    return this->fp_->getVariables();
}

void FilePattern::getNewNaming(std::string& pattern, bool suppressWarnings) {
    this->fp_->getNewNaming(pattern, suppressWarnings);
}

std::string FilePattern::swSearch(std::string& pattern, std::string& filename, const std::string& variables) {
    return this->fp_->swSearch(pattern, filename, variables);
}
