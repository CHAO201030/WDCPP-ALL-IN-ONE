#include"./include/Config.h"

using namespace std;

int main()
{
    unique_ptr<int> p = make_unique<int>(2);
    cout << *p << "\n";
    return 0;
}