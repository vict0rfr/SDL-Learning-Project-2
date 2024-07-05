#ifndef UTILS
#define UTILS

#include <string>
#include <vector>

class Utils{
    public:
        static unsigned int split(const std::string &p_txt,
            std::vector<std::string> &p_strs, char p_ch){
                int pos = p_txt.find(p_ch);
                int initialPos = 0;
                p_strs.clear();
                while(pos != std::string::npos){
                    p_strs.push_back(p_txt.substr(initialPos, pos - initialPos + 1));
                    initialPos = pos + 1;
                    pos = p_txt.find(p_ch, initialPos);
                }
                p_strs.push_back(p_txt.substr(initialPos, std::min<int>(pos, p_txt.size() - (initialPos + 1))));

                return p_strs.size();
            }
    private:
};

#endif /* UTILS */
