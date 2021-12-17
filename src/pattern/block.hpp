#pragma once

#define KB(x) ((size_t) (x) << 10);
#define MB(x) ((size_t) (x) << 20);
#define GB(x) ((size_t) (x) << 30);

class Block {
    public:
        static long double parseblockSize(const std::string& block){ 

            std::string numString = "";
            std::string unitString = "";
            
            for(const auto& c: block){
                if(isdigit(c) || c == '.') numString.push_back(c);
                else if(c != ' ') unitString.push_back(c);
            }

            if (numString == "") throw std::invalid_argument("Block size must include a size.");
            std::string::size_type sz;
            long double num = stoi (numString, &sz);

            if (unitString == "KB"){
                num = KB(num);
            } else if (unitString == "MB") {
                num = MB(num);
            } else if (unitString == "GB"){
                num = GB(num);
            } else if (unitString != "B"){
                throw std::invalid_argument("Block size must include a valid unit (B, KB, MB, GB).");
            }

            return num;
        }
};