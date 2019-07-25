#include <iostream>
#include <string.h>
#include <unordered_map>

static constexpr int invalid_index = -1;

const char* raw_str = "ajefsafehrawdfvt";
//const char* raw_str = "aabaaaaaa";
std::unordered_map<char, int> g_char_index;

int dup_index(char new_c, int new_i) {
    if (g_char_index.find(new_c) != g_char_index.end()) {
        int old_index = g_char_index[new_c];
        g_char_index[new_c] = new_i;
        return old_index;
    }

    g_char_index[new_c] = new_i;
    return invalid_index;
}

int main(int argc, char** argv) {
    int tmp_start_i = 0;
    int tmp_end_i = 0;
    int max_substr_len = 1;
    int start_i = tmp_start_i;
    int end_i = tmp_end_i;
    int str_len = strlen(raw_str);

    while (tmp_end_i < str_len) {
        int prev_index = dup_index(raw_str[tmp_end_i], tmp_end_i);
        if (prev_index == invalid_index) {
            int tmp_max_substr_len = tmp_end_i - tmp_start_i + 1;
            if (tmp_max_substr_len > max_substr_len) {
                max_substr_len = tmp_max_substr_len;
                start_i = tmp_start_i;
                end_i = tmp_end_i;
            }
            ++tmp_end_i;
        }
        else if (prev_index >= tmp_start_i) {
            tmp_start_i = prev_index + 1;
            ++tmp_end_i;
        }
        else {
            ++tmp_end_i;
        }
    }

    
    char* substr = (char*)malloc(max_substr_len + 1);
    memset(substr, 0, sizeof(max_substr_len + 1));
    strncpy(substr, raw_str + start_i, max_substr_len);
    std::cout << "the longest substr without repeatable char. start_i = " << start_i
              << "end_i = " << end_i
              << "substr = " << substr
              << std::endl;
    free(substr);

    std::cout << "press any key to continue..." << std::endl;
    getchar();
    return 0;
}
