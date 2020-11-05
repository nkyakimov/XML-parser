#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

class Node
{
private:
    string field_name="";
    string id_name="";
    string id_value="";
    string property="";
    vector<Node*>children;
public:
    Node();
    Node(string,string,string,string);
    ~Node();

    string get_id_name() const;
    void set_id_name(const string);
    string get_id_val() const;
    void set_id_val(const string);
    string get_prop()const;
    void set_prop(const string);
    string get_field_name() const;
    void set_field_name(const string);
    void print(int) const;
    void add_child(Node*);
    void prettyfy_prop();

    void print_by_id(const string) const;

    void del();

    void fill_up(ifstream&,vector<string>&,vector<Node*>&);
    void fill_data(const string,vector<string>&);
    int size() const;
    const Node* get_by(const bool,const string) const;
    Node* get_by_tag_and_id(const string tag,const string id);

    Node& operator = (const Node& t);

    void console_fill();
    void get_all(vector<Node*>&);
    Node* get_child(unsigned int i);
    bool get_prop_by_id(string,string) const;
    void print_in_file(ofstream&,int) const;
    bool remove(const Node*);
};


#endif // NODE_H_INCLUDED
