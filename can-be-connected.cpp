#include <iostream>
#include <string>
#include <regex>
#include <memory>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>

/**
				D--E--F -- H
	    /			 \
	A--B        G     I--J--K
	    \
	     C
	tests:
 				1. A,B: true
 				2. A,F: true
 				3. C,H: true
 				4. E,G: true
 				5. B,K: false
*/

using namespace std;
struct Node;
bool can_be_connected(Node& n1, Node& n2);

static unordered_map<string,shared_ptr<Node> > all_nodes;

struct Node {

	private:
		unordered_set<shared_ptr<Node> > neighbors;
	public:
		string id;

		explicit Node(const string id):id(id){}

		bool canBeConnected(shared_ptr<Node> &other){
			return ::can_be_connected(*this, *other);
		}
		bool addFrriend(shared_ptr<Node> &other){
			if(other->id.compare(this->id) != 0){
				auto result = neighbors.insert(other);
				return result.second;
			}
			return false;
		}

		friend bool add_friend(shared_ptr<Node> &n1, shared_ptr<Node> &n2);
		friend bool can_be_connected(Node &n1, Node &n2);

};

bool add_friend(shared_ptr<Node> &n1, shared_ptr<Node> &n2){
	return n1->addFrriend(n2) && n2->addFrriend(n1);
}

//implement BFS Search
bool can_be_connected(Node& n1, Node& n2){

	queue<string> q;
	unordered_set<string> visited;
	q.push(n1.id);
	while(!q.empty()){
		auto &temp = q.front();
		if(temp.compare(n2.id) == 0){
			return true;
		}
		visited.insert(temp);
		for(const auto& neighbour:all_nodes[temp]->neighbors){
			if (visited.find(neighbour->id) == visited.end()) {
				q.push(neighbour->id);
			}
		}
		q.pop();
	}
	return false;
}

int main(int argc,char** argv){

	/**
				D--E--F -- H
	    /			 \
	A--B        G     I--J--K
	    \
	     C

	tests:
 				1. A,B: true
 				2. A,F: true
 				3. C,H: true
 				4. E,G: false
 				5. B,K: false
*/
	all_nodes["A"] = make_shared<Node>("A");
	all_nodes["B"] = make_shared<Node>("B");
	all_nodes["C"] = make_shared<Node>("C");
	all_nodes["D"] = make_shared<Node>("D");
	all_nodes["E"] = make_shared<Node>("E");
	all_nodes["F"] = make_shared<Node>("F");
	all_nodes["G"] = make_shared<Node>("G");
	all_nodes["H"] = make_shared<Node>("H");
	all_nodes["I"] = make_shared<Node>("I");
	all_nodes["J"] = make_shared<Node>("J");
	all_nodes["K"] = make_shared<Node>("K");

	bool graph_created =
		add_friend(all_nodes["A"],all_nodes["B"]) &&
		add_friend(all_nodes["B"],all_nodes["D"]) &&
		add_friend(all_nodes["B"],all_nodes["C"]) &&
		add_friend(all_nodes["D"],all_nodes["E"]) &&
		add_friend(all_nodes["E"],all_nodes["F"]) &&
		add_friend(all_nodes["F"],all_nodes["G"]) &&
		add_friend(all_nodes["F"],all_nodes["H"]) &&
		add_friend(all_nodes["I"],all_nodes["J"]) &&
		add_friend(all_nodes["J"],all_nodes["K"]);

	if(!graph_created){
		cerr << "Something went wrong! Could not generate graph!\n";
		exit(1);
	}
	cout << "Graph is generated!\n";
	bool result =
		all_nodes["A"]->canBeConnected(all_nodes["B"]) &&
		all_nodes["A"]->canBeConnected(all_nodes["F"]) &&
		all_nodes["C"]->canBeConnected(all_nodes["H"]) &&
		all_nodes["E"]->canBeConnected(all_nodes["G"]) &&
		!all_nodes["B"]->canBeConnected(all_nodes["K"]);

	if(!result){
		cerr << "Something went wrong! BFS not working properly!\n";
		exit(1);
	}
	cout << "BFS works just fine!\n";

	return 0;
}