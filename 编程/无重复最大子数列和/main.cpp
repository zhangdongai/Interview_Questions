#include <iostream>
#include <string.h>
#include <unordered_map>

static constexpr int invalid_index = -1;

const int raw_sequence[] = {3, 8, 3, -2, 56, 32, 7, -8, 42, -21};
//const int raw_sequence[] = {-1, 1, 2, 1, 1, 1, 1, 1, 1, -2};
//const char* raw_str = "aabaaaaaa";
// 记录字符出现的索引
std::unordered_map<int, int> g_figure_index;

//我们只需要判断新加入窗口的那个字符是否有重复即可
int dup_index(int new_figure, int new_i) {
    // 如果有重复则返回上一个字符的索引，并且要更新该字符的最新索引
    if (g_figure_index.find(new_figure) != g_figure_index.end()) {
        int old_index = g_figure_index[new_figure];
        g_figure_index[new_figure] = new_i;
        return old_index;
    }

    // 如果不存在，则新增该字符和索引，并返回invalid_index
    g_figure_index[new_figure] = new_i;
    return invalid_index;
}

int sub_sequence_sum(int start_i, int end_i) {
    if (start_i > end_i)
        return 0;
    return raw_sequence[start_i] + sub_sequence_sum(start_i + 1, end_i);
}

int main(int argc, char** argv) {
    // 记录滑动窗口的头索引，一直在变
    int tmp_start_i = 0;
    // 记录滑动窗口的尾索引，一直在变
    int tmp_end_i = 0;
    // 记录每次判断后最长的无重复子串长度
    int max_sub_sum = 0;
    // 记录最长无重复子串的开始索引。只有最长长度变化时才变
    int start_i = tmp_start_i;
    // 记录最长无重复子串的结束索引。只有最长长度变化时才变
    int end_i = tmp_end_i;
    int seq_len = sizeof(raw_sequence) / sizeof(int);

    // 循环结束条件，尾索引到达字符串末尾
    while (tmp_end_i < seq_len) {
        // 获取新加入窗口的字符是否已经出现过
        int prev_index = dup_index(raw_sequence[tmp_end_i], tmp_end_i);

        // 如果没有出现过，则窗口头索引不变，尾索引加1。
        // 如果最长长度变化，则更新最长长度和开始索引、结束索引
        if (prev_index == invalid_index) {
        }
        else if (prev_index >= tmp_start_i) {
            // 如果出现过，出现的索引大于等于窗口头索引时，头索引更新到出现索引的后一个位置。
            // 同时尾索引加1
            tmp_start_i = prev_index + 1;
        }
        else {
            // 如果出现过，但是出现的索引已经小于窗口的头索引时，头索引不变，尾索引加1
        }

        // 需要注意计算和更新最大和的时机，必须是对窗口进行判断后，且窗口尾索引加1前
        int tmp_max_sub_sum = sub_sequence_sum(tmp_start_i, tmp_end_i);
        if (tmp_max_sub_sum > max_sub_sum) {
            max_sub_sum = tmp_max_sub_sum;
            start_i = tmp_start_i;
            end_i = tmp_end_i;
        }
        // 任何情况下都会对尾索引加1
        ++tmp_end_i;
    }

    int int_size = end_i - start_i + 1;
    int byte_size = sizeof(int) * int_size;
    int* sub_seq = (int*)malloc(byte_size);
    memcpy(reinterpret_cast<char*>(sub_seq), reinterpret_cast<const char*>(raw_sequence + start_i), byte_size);
    std::cout << "the longest substr without repeatable char. start_i = " << start_i
              << "end_i = " << end_i << std::endl;
    std::cout << "sub sequence os ";
    for (int i = 0; i < int_size; ++i) 
        std::cout << sub_seq[i] << ", ";
    std::cout << "max sub sequence sum is " << max_sub_sum << std::endl;
    free(sub_seq);

    std::cout << "press any key to continue..." << std::endl;
    getchar();
    return 0;
}
