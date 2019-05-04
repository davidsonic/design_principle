#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <tuple>
using namespace std;
using namespace boost;


// A. High-level should not depend on low-level module
// B. Abstract should not depend on details

// don't want dependency on storage or implementation,  only on interface or abstractions

enum class Relationship{
    parent,
    child,
    sibling
};


struct Person{
    string name;
};

struct Relations{ //low-level module
    vector<tuple<Person, Relationship, Person>> relations;
    void add_parent_child(const Person&parent, const Person&child){
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }
};

struct RelationshipBrowser{
    virtual vector<Person>find_all_children_of(const string&name)=0;
};

struct Relations2:RelationshipBrowser{
    vector<tuple<Person, Relationship, Person>> relations;
    void add_parent_child(const Person&parent, const Person&child){
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    vector<Person> find_all_children_of(const string &name) override {
        vector<Person> res;
        for(auto && [first, rel, second]:relations){
            if(first.name==name && rel==Relationship::parent){
                res.push_back(second);
            }
        }
        return res;
    }
};

struct Research{ // high-level module
//    Research(Relations & relations){
//        auto & relation = relations.relations;
//        // auto&& works for proxy objects
//        for(auto && [first, rel, second]: relation){
//            if(first.name=="John" && rel==Relationship::parent){
//                cout<<"John has a child called "<<second.name<<endl;
//            }
//        }
//    }

    Research(RelationshipBrowser & browser){
        for(auto &child: browser.find_all_children_of("John"))
            cout<<"John has a child called "<<child.name<<endl;
    }
};


int main(){
    Person parent{"John"};
    Person child1{"Chris"}, child2{"Marry"};

    Relations relation;
    relation.add_parent_child(parent, child1);
    relation.add_parent_child(parent, child2);

//    Research _(relation);

    Relations2 relation2;
    relation2.add_parent_child(parent, child1);
    relation2.add_parent_child(parent, child2);

    Research _(relation2);

    return 0;
}

