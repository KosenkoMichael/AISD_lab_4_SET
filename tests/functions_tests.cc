#include <gtest/gtest.h>
#include <functions/functions.h>


using namespace std;
using namespace set;
using namespace rnd;

TEST(test_SET, test) {
    MySet<int> set;
    set.insert(41);
    set.insert(90);
    set.insert(20);
    set.print();
    cout << boolalpha << set.contains(999)<<endl;
    cout << boolalpha << set.contains(41) << endl;
    set.erase(41);
    cout << boolalpha << set.contains(41) << endl;
    set.print();

    MySet<int> set_2 = set;
    MySet<int> set_3(set_2);
    set_2.print();
    set_3.print();

    cout << boolalpha << set.insert(90) << endl;
}

TEST(test_RAND, test) {
    Rand seed(3, 0, 1000);
    cout << seed.generate_random_number() << endl;
    cout << seed.generate_random_number() << endl;
}

TEST(test_Problem, test) {
    MySet<int> first;
    MySet<int> second;
    first.insert(1);
    first.insert(2);
    first.insert(3);
    second.insert(2);
    second.insert(3);
    second.insert(4);
    first.print();
    second.print();
    cout << "or >> ";
    logic_or(first, second).print();
    cout << "xor >> ";
    logic_xor(first, second).print();
}

TEST(test_mytests, test) {
    MySet<int> s3;
    MySet<int> s4;
    MySet<int> s5;
    s3.fill(1000);
    s4.fill(10000);
    s5.fill(100000);
    cout << "time for fill >>\n\t1000 = " 
        << get_time_fill(1000)/1000 << " ms\n\t10000 = " 
        << get_time_fill(10000) / 1000 << " ms\n\t100000 = " 
        << get_time_fill(100000) / 1000 << " ms" << endl;
    cout << "time for contains >>\n\t1000 = " 
        << get_time_contains(s3, 1000) / 1000 << " ms\n\t10000 = "
        << get_time_contains(s4,10000) / 1000 << " ms\n\t100000 = " 
        << get_time_contains(s5,100000) / 1000 << " ms" << endl;
    cout << "time for insert >>\n\t1000 = " 
        << get_time_insert(s3, 1000) / 1000 << " ms\n\t10000 = " 
        << get_time_insert(s4,10000) / 1000 << " ms\n\t100000 = " 
        << get_time_insert(s5,100000) / 1000 << " ms" << endl;
    cout << "time for erase >>\n\t1000 = " 
        << get_time_erase(s3, 1000) / 1000 << " ms\n\t10000 = " 
        << get_time_erase(s4,10000) / 1000 << " ms\n\t100000 = " 
        << get_time_erase(s5,100000) / 1000 << " ms" << endl;
}