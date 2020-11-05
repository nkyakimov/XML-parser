#include <iostream>
#include "XML_Tree.h"

using namespace std;

int main()
{
    Tree dd;
    dd.load_tree("demo.xml");
    dd.print();
    dd.get_prop_by_id("2_1","address");
    Tree c;
    c=dd;
    //c.print();
    c.delete_by_tag_and_id("hospital","");
    c.print();
    //dd.print_to_file("new.xml");
    return 0;
}
