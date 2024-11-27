#include <iostream>
#include <fstream>

std::string split_to_chunks(std::string str, const int chunck_size) {
    std::string out;
    for (size_t i = 0; i < str.size(); i += chunck_size) {
        out += str.substr(i, chunck_size);
        out += '\n';
    }
    return out;
}

std::string remove_whitespaces(std::string str){
    std::string out;
    for (int i = 0; i < str.length(); i+=1){
        if (str[i] != '-' and str[i] != '.'){
            out += str[i];
        }
    }
    return out;
}

std::string modify_filename(const std::string& filepath, const std::string& suffix) {
    size_t dot_pos = filepath.find_last_of('.');

    if (dot_pos == std::string::npos) {
        std::cout << filepath + suffix << std::endl;
        return filepath + suffix;
    }

    return filepath.substr(0, dot_pos) + suffix + filepath.substr(dot_pos);
}

void write_files(std::string& str_long, std::string& str_short, const std::string& filename){
    std::ofstream(modify_filename(filename, "_long")) << str_long;
    std::ofstream(modify_filename(filename, "_short")) << str_short;
}

void read_file_with_spaces(const std::string& filename, const int threshold) {
    int name_cnt = 0;
    std::ifstream file(filename);
    std::string line;
    std::string no_white;
    std::string out_long;
    std::string out_short;
    std::string sequence;
    std::string sequence_name[10000];

    while (std::getline(file, line)) {
        if (line[0] == '>'){
            sequence_name[name_cnt] = line;

            sequence = split_to_chunks(no_white, 80);

            if (sequence.size() < threshold && !sequence.empty()){
                out_short += sequence_name[name_cnt-1] + '\n' + sequence;
            }

            if (sequence.size() > threshold && !sequence.empty()){
                out_long += sequence_name[name_cnt-1] + '\n' + sequence;
            }

            no_white.clear();
            name_cnt +=1;
        }
        else{
            no_white += remove_whitespaces(line);
        }
    }
    sequence = split_to_chunks(no_white, 80);
    if (sequence.size() < threshold && !sequence.empty()){
        out_short += sequence_name[name_cnt-1] + '\n' + sequence;
    }
    if (sequence.size() > threshold && !sequence.empty()){
        out_long += sequence_name[name_cnt-1] + '\n' + sequence;
    }

    file.close();
    write_files(std::ref(out_long), std::ref(out_short), filename);
}



int main(int argc, char* argv[]) {
    try{
        std::string filename = argv[1];
        read_file_with_spaces(filename, 10 * 80);
        return 0;
    }
    catch (...){
        return 1;
    }
}
