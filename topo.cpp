#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

// Nodes
enum NodeType { HOST, SWITCH };

// class for base node
class Node {
public:
    string name;
    NodeType type;

    Node(string n, NodeType t) : name(n), type(t) {}
};

// class for topology
class Topology {
private:
    map<string, Node*> nodes;
    vector<pair<string, string> > links;   

public:
    // host addition
    string addHost(const string& name) {
        nodes[name] = new Node(name, HOST);
        return name;
    }

    // switch addition
    string addSwitch(const string& name) {
        nodes[name] = new Node(name, SWITCH);
        return name;
    }

    // link addition between nodes
    void addLink(const string& n1, const string& n2) {
        links.push_back(make_pair(n1, n2));
    }

    // Print topology
    void printTopology() {
        cout << "Nodes in topology:" << endl;
        for (map<string, Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
            string name = it->first;
            Node* node = it->second;
            cout << " - " << name << " (" << (node->type == HOST ? "Host" : "Switch") << ")" << endl;
        }

        cout << "\nLinks in topology:" << endl;
        for (size_t i = 0; i < links.size(); i++) {
            cout << " - " << links[i].first << " <--> " << links[i].second << endl;
        }
    }

    ~Topology() {
        for (map<string, Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
            delete it->second;
        }
    }
};

// Custom topology
class MyTopo : public Topology {
public:
    MyTopo() {
        // Add hosts
        for (int i = 1; i <= 21; i++) {
            addHost("h" + intToString(i));
        }

        // Add switch
        string leftSwitch = addSwitch("s1");

        // Connect all hosts to the switch
        for (int i = 1; i <= 21; i++) {
            addLink("h" + intToString(i), leftSwitch);
        }
    }

private:
    
    string intToString(int num) {
        ostringstream ss;
        ss << num;
        return ss.str();
    }
};

int main() {
    MyTopo topo;
    topo.printTopology();
    return 0;
}

