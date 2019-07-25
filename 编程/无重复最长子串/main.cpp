#include <iostream>
#include <string.h>
#include <unordered_map>

static constexpr int invalid_index = -1;

const char* raw_str = "ajefsafehrawdfvd";
//const char* raw_str = "aabaaaaaa";
// 记录字符出现的索引
std::unordered_map<char, int> g_char_index;

//我们只需要判断新加入窗口的那个字符是否有重复即可
int dup_index(char new_c, int new_i) {
    // 如果有重复则返回上一个字符的索引，并且要更新该字符的最新索引
    if (g_char_index.find(new_c) != g_char_index.end()) {
        int old_index = g_char_index[new_c];
        g_char_index[new_c] = new_i;
        return old_index;
    }

    // 如果不存在，则新增该字符和索引，并返回invalid_index
    g_char_index[new_c] = new_i;
    return invalid_index;
}

int main(int argc, char** argv) {
    // 记录滑动窗口的头索引，一直在变
    int tmp_start_i = 0;
    // 记录滑动窗口的尾索引，一直在变
    int tmp_end_i = 0;
    // 记录每次判断后最长的无重复子串长度
    int max_substr_len = 1;
    // 记录最长无重复子串的开始索引。只有最长长度变化时才变
    int start_i = tmp_start_i;
    // 记录最长无重复子串的结束索引。只有最长长度变化时才变
    int end_i = tmp_end_i;
    int str_len = strlen(raw_str);

    // 循环结束条件，尾索引到达字符串末尾
    while (tmp_end_i < str_len) {
        // 获取新加入窗口的字符是否已经出现过
        int prev_index = dup_index(raw_str[tmp_end_i], tmp_end_i);
        // 如果没有出现过，则窗口头索引不变，尾索引加1。
        // 如果最长长度变化，则更新最长长度和开始索引、结束索引
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
            // 如果出现过，出现的索引大于等于窗口头索引时，头索引更新到出现索引的后一个位置。
            // 同时尾索引加1
            tmp_start_i = prev_index + 1;
            ++tmp_end_i;
        }
        else {
            // 如果出现过，但是出现的索引已经小于窗口的头索引时，头索引不变，尾索引加1
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
