#include "list.h"

int main(int argc, char** argv) {
    List list = create_list(10);
    print_list(list);
    getchar();

//    list = reverse(list);
    list = reverse_recursive(list, nullptr);
    print_list(list);

    getchar();
    delete_list(list);
    return 0;
}
