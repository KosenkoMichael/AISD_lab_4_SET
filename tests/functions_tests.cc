#include <gtest/gtest.h>

#include <functions/functions.h>

using namespace std;
using namespace set;
using namespace rnd;

TEST(test_SET, test) {
    MySet set;
    set.insert(41);
    set.insert(90);
    set.insert(20);
    set.print();
    cout << boolalpha << set.contains(999)<<endl;
    cout << boolalpha << set.contains(41) << endl;
    set.erase(41);
    cout << boolalpha << set.contains(41) << endl;
    set.print();

    MySet set_2 = set;
    MySet set_3(set_2);
    set_2.print();
    set_3.print();
}

TEST(test_RAND, test) {
    Rand seed(3, 0, 1000);
    cout << seed.generate_random_number() << endl;
    cout << seed.generate_random_number() << endl;
}