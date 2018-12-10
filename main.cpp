#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//-----CLASS METHODS-----//
class Item {
private:
    int profit;
    int weight;
    double ratio;
    int level;
    double bound;
public:
    //constructor
    Item();
    Item(int profit, int weight);

    //getter (declared here)
    int getProfit() {return this->profit;};
    int getWeight() {return this->weight;};
    double getRatio() {return this->ratio;};
    int getLevel(){return this->level;};
    double getBound() {return this->bound;};

    //setter
    void setProfit(int profit);
    void setWeight(int weight);
    void setRatio();
    void setLevel(int level);
    void setBound(double bound);
};

Item::Item(){
    this->weight = 0;
    this->profit = 0;
    this->ratio = 0.0;
    this->level = 0;
    this->bound = 0.0;

}

Item::Item(int profit, int weight){
    this->weight = weight;
    this->profit = profit;
    this->level = 0;
    this->bound = 0.0;
    setRatio();
}


void Item::setProfit(int profit){
    this->profit = profit;
}

void Item::setWeight(int weight){
    this->weight = weight;
}

void Item::setLevel(int level) {
    this->level = level;
}

void Item::setBound(double bound) {
    this->bound = bound;
}
//sets ratio, in case of division of/by zero replaces nan with zero
void Item::setRatio(){
    int temp_profit = getProfit();
    int temp_weight = getWeight();
    if (temp_profit == 0 || temp_weight == 0)
        this->ratio = 0;
    else
        this->ratio = (temp_profit * 1.0) / (temp_weight* 1.0) ;
}


//-----END CLASS METHODS-----//


//-----global variables-----//
int item_no = 0;
int max_weight = 0;
int max_profit = 0;
int node_counter = 0;
int branch_counter = 0;
int brute_counter = 0;

vector<Item> items;
vector<Item> branch_items;
vector<Item> visited_branch;
vector<Item> brute_items;

vector<Item> priority_queue;
vector<Item> best_set;
vector<Item> include;

//-----getters-----//
double _getRatio(const int &index, vector<Item> node);

int _getProfit(const int &index, vector<Item> node);

int _getWeight(const int &index, vector<Item> node);

int _getLevel(const int &index, vector<Item> node);

//-----setters-----//
//push to items vector set
void pushItems(const vector<int> &profits, const vector<int> &weights, vector<Item> &node);

//pop item from items vector
void popItems(const int &index, vector<Item> &node);

//-----output-----//
void displaySet(vector <Item> &list);
void displayBranch(vector <Item> &list);

//sort item vector by ratio
bool compareRatio(Item i1, Item i2);

//for use with priority queue in branch and bound
bool compareBound(Item a, Item b);

//for use with displaying branch and bound
bool compareProfit(Item a, Item b);

void erase_duplicates(vector <Item> &list);

//BACKTRACKING ALGORITHM-----//

void knapsack(int index, int profit, int weight);

bool promising(int index, int profit, int weight);

void set_best();
//-----END BACKTRACKING ALGORITHM-----//


//Branch and Bound

void knapsack3 ();
double bound (Item node_u);

//--------BRUTE FORCE ALGORITHM-----------//

void brute_knapsack(int index, int profit, int weight);
//------END BRUTE FORCE ALGORITHM-------//



//end branch and bound
void algo_one(const vector<int> &profits, const vector<int> &weights);
void algo_two(const vector<int> &profits, const vector<int> &weights);
void algo_three(const vector<int> &profits, const vector<int> &weights);

//test code
void my_pause();
void main_menu();

int main()
{
    main_menu();
    return 0;
}

void main_menu(){
    int p,w = 0;
    vector<int> profits;
    vector<int> weights;


    cout << "How many items are there to potentially take? ";
    cin >> ::item_no;

    cout << "What is the max weight that the bag can hold? ";
    cin >>  ::max_weight;

    cout << "Max weight is " << ::max_weight << " the Number of items is " << ::item_no << "\n";

    cout << "Please input a set of profits and matching weights for all " << ::item_no << " items : \n";
    for (int index=0; index < item_no; index++){
        cout << "Profit " << index + 1 << ": ";
        cin >> p;
        cout << "Weight " << index + 1 << ": ";
        cin >> w;
        profits.push_back(p);
        weights.push_back(w);
    }

//    cout << "Please choose an algorithm:\n";
//    cout << "1) Brute Force Algorithm\n";
//    cout << "2) Backtracking Algorithm\n";
//    cout << "3) Branch and Bound Algorithm\n";
//    cout << "4) Exit\n";
//    char choice;
//    cin >> choice;
//    switch(choice)
//    {
//        case '1': cout << "Working on it\n";
//            break;
//        case '2': algo_two(profits, weights);
//            break;
//        case '3': algo_three(profits, weights);
//            break;
//        case '4': cout << "Goodbye.\n";
//            break;
//        default:
//            cout << "Incorrect choice.\n";
//            main_menu();
//    }
     algo_one(profits, weights);
     algo_two(profits, weights);
     algo_three(profits, weights);
}

void algo_two(const vector<int> &profits, const vector<int> &weights){
    ::max_profit = 0;
    //push into vector of items
    pushItems(profits, weights, ::items);
    //sort nodes by non-increasing ratio
    sort(::items.begin(), ::items.end(), compareRatio);
    //needed to insert dummy node into sorted items vector
    Item dummy_node(0, 0);
    ::items.insert(::items.begin(), dummy_node);
    cout << "Your set of items is :\n";
    displaySet(::items);
    //call the knapsack method
    knapsack(0, 0, 0);
    cout << "The final amount of profit is $" << ::max_profit << "\n";
    cout << "The final set of items in the knapsack is : \n";
    displaySet(::best_set);
    cout << ::node_counter << " nodes were visited in the state space tree using the backtrack algorithm.\n";
    cout << "\n";
    ::include.clear();
    ::best_set.clear();
    ::items.clear();
}

void algo_three(const vector<int> &profits, const vector<int> &weights){
    //push into vector of items
    pushItems(profits, weights, ::branch_items);
    //sort nodes by non-increasing ratio
    sort(::branch_items.begin(), ::branch_items.end(), compareRatio);
    //needed to insert dummy node into sorted items vector
    Item dummy_node(0, 0);
    ::branch_items.insert(::branch_items.begin(), dummy_node);
    cout << "Your set of items is :\n";
    displaySet(::branch_items);
    //call the knapsack method
    knapsack3();
    cout << "The final amount of profit is $" << ::max_profit << "\n";

    cout << "The final set of items in the knapsack is : \n";
    //clean data
    sort(::visited_branch.begin(), ::visited_branch.end(), compareProfit);
    erase_duplicates(::visited_branch);

    displayBranch(::visited_branch);
    cout << ::branch_counter << " nodes were visited in the state space tree using the branch and bound algorithm.\n";
    cout << "\n";
    ::visited_branch.clear();
    ::branch_items.clear();
}


//-----getters-----//
//----------------//
double _getRatio(const int &index, vector<Item> node){
    unsigned long temp = index;
    return node.at(temp).getRatio();
}

int _getProfit(const int &index, vector<Item> node){
    unsigned long temp = index;
    return node.at(temp).getProfit();
}

int _getWeight(const int &index, vector<Item> node){
    unsigned long temp = index;
    return node.at(temp).getWeight();
}

int _getLevel(const int &index, vector<Item> node){
    unsigned long temp = index;
    return node.at(temp).getLevel();
}
//-----setters-----//
//----------------//

//pushes nodes into items vector
void pushItems(const vector<int> &profits, const vector<int> &weights, vector<Item> &node){
    int size = profits.size();
    for (unsigned index=0; index < size; index++){
        int temp_profit = profits.at(index);
        int temp_weight = weights.at(index);
        Item temp(temp_profit, temp_weight);
        node.push_back(temp);
    }
}

//pop
void popItems(const int &index, vector<Item> &node){
    int size = node.size();
    if (size != 0)
        node.erase (node.begin()+index);
}

//-----output-----//

void displaySet(vector <Item> &list){
    auto _begin = list.begin();
    auto _end = list.end();

    for (auto it = _begin; it < _end; ++it) {
        cout << "Weight: " << it->getWeight() << ", Profit: " <<
             it->getProfit() << ", Ratio: " << it->getRatio() << /*", Bound: " << it->getBound() << ", Level: " << it->getLevel() << */"\n";
    }
    cout << endl;
}

void displayBranch(vector <Item> &list){
    auto index = list.begin();

    int temp_profit = ::max_profit;

    while (temp_profit > 0){
        cout << "Weight: " << index->getWeight() << ", Profit: " <<
             index->getProfit() << ", Ratio: " << index->getRatio()
             << /*", Bound: " << index->getBound() << ", Level: " << index->getLevel() <<*/ "\n";
        temp_profit -= index->getProfit();
        index++;
    }
    cout << endl;
}

//sort vectors by nonincreasing ratio
bool compareRatio(Item a, Item b){
    return (a.getRatio() > b.getRatio());
}

bool compareBound(Item a, Item b){
    return (a.getBound() > b.getBound());
}

//for use with displaying branch and bound
bool compareProfit(Item a, Item b){
    return (a.getProfit() > b.getProfit());
}

void erase_duplicates(vector <Item> &list){
    auto begin = list.begin();

    auto end = list.end();

    for (auto it = begin, next = it + 1; it < end; ++it) {
        if (it->getProfit() == next->getProfit() && it->getWeight() == next->getWeight()){
            list.erase(next);
        }
        next++;
    }

}

void algo_one(const vector<int> &profits, const vector<int> &weights){
    ::max_profit = 0;
    //push into brute force vector
    pushItems(profits, weights, ::brute_items);
    //sort nodes by profit <---I know this is a dirty trick but I ran out of time and need to study!
    sort(::brute_items.begin(), ::brute_items.end(), compareProfit);
    //insert dummy nodes
    Item dummy_node(0, 0);
    ::brute_items.insert(::brute_items.begin(), dummy_node);
    cout << "Your set of items is :\n";
    displaySet(::brute_items);
    //call brute force algorithm
    brute_knapsack(0,0,0);

    cout << "The final amount of profit is $" << ::max_profit << "\n";
    cout << "The final set of items in the knapsack is : \n";
    displaySet(::best_set);
    cout << ::brute_counter << " nodes were visited in the state space tree using the brute force algorithm.\n";
    cout << "\n";
    ::include.clear();
    ::best_set.clear();
    ::brute_items.clear();
}

//---------BRUTE FORCE ALGORITHM----------//

void brute_knapsack(int index, int profit, int weight){
    ::brute_counter++;
    if ((weight <= ::max_weight) && (profit >= ::max_profit)){
        ::max_profit = profit;
        //copy include into best_set
        set_best();
        unsigned int temp = index;
        if (index >= ::brute_items.size()-1)
            return;
        //push index + 1 node to includes
        include.push_back(brute_items.at(temp + 1));
        //recursive call to knapsack
        brute_knapsack(index + 1, profit + brute_items.at(temp + 1).getProfit(), weight + brute_items.at(temp + 1).getWeight());
        //pop index + 1 node from includes
        include.pop_back();
        //recursive call to knapsack
        brute_knapsack(index + 1, profit, weight);
    }
}


//BACKTRACKING ALGORITHM-----//
void knapsack(int index, int profit, int weight){
    ::node_counter++;
    if ((weight <= ::max_weight) && (profit > ::max_profit)){
        ::max_profit = profit;
        //copy include into best_set
        set_best();
    }
    if (promising(index, profit, weight)){
        unsigned int temp = index;
        //push index + 1 node to includes
        include.push_back(items.at(temp + 1));
        //recursive call to knapsack
        knapsack(index + 1, profit + items.at(temp + 1).getProfit(), weight + items.at(temp + 1).getWeight());
        //pop index + 1 node from includes
        include.pop_back();
        //recursive call to knapsack
        knapsack(index + 1, profit, weight);
    }
}

//don't use promising with brute-force...
bool promising(int index, int profit, int weight){
    int j_index, k_index, total_weight;
    double bound;

    if (weight >= ::max_weight)
        return false;
    else{
         j_index = index + 1;
         unsigned int temp = j_index;
         bound = profit;
         total_weight = weight;
         while ((j_index < items.size()) && (total_weight + items.at(temp).getWeight() <= ::max_weight)){
              total_weight += items.at(temp).getWeight();
              bound += items.at(temp).getProfit();
              temp++;
              j_index++;
         }
        k_index = j_index;

        if (k_index < items.size())
            bound += ((::max_weight - total_weight) *  items.at(temp).getRatio());

        return (bound > ::max_profit);
    }
 }

//copies includes into best
void set_best(){
    //clear best
    best_set.clear();
    //copy everything into best from includes
    for (unsigned index=0; index < include.size(); index++){
        best_set.push_back(include.at(index));
    }
}

//-----END BACKTRACKING ALGORITHM-----//

//----------BRANCH AND BOUND METHOD-------------//

void knapsack3 (){
    //    node u, v;
    Item node_u(0,0);
    Item node_v(0,0); //v.level = 0; v.profit = 0; v.weight = 0; // init v to be the root
    priority_queue.clear(); // Initialize global var PQ to be empty
    ::max_profit = 0;
    node_v.setBound(bound(node_v));
    //insert(PQ, v);
    priority_queue.insert(priority_queue.begin(), node_v);
    sort(priority_queue.begin(), priority_queue.end(), compareBound);
    while (priority_queue.size() != 0){

        //at some point refactor this into an overloaded assignment operator function
        //creating a temp node for the body of the while statement
        int temp_profit, temp_weight, temp_level;
        double temp_bound;
        temp_profit = priority_queue.at(0).getProfit();
        temp_weight = priority_queue.at(0).getWeight();
        temp_level = priority_queue.at(0).getLevel();
        temp_bound = priority_queue.at(0).getBound();
        Item temp_node;
        temp_node.setProfit(temp_profit);
        temp_node.setWeight(temp_weight);
        temp_node.setLevel(temp_level);
        temp_node.setRatio();
        temp_node.setBound(temp_bound);

        priority_queue.erase (priority_queue.begin()); //remove (PQ, v); // remove unexpanded node with best bound

        if (temp_node.getBound() > ::max_profit){// see if node is still promising
            node_u.setLevel(temp_node.getLevel() + 1);
            Item temp_branch(branch_items.at(node_u.getLevel()).getProfit(), branch_items.at(node_u.getLevel()).getWeight());
            visited_branch.push_back(temp_branch);
            node_u.setWeight(temp_node.getWeight() + branch_items.at(node_u.getLevel()).getWeight());
            node_u.setProfit(temp_node.getProfit() + branch_items.at(node_u.getLevel()).getProfit());
            node_u.setRatio();//testing
            node_u.setBound(bound(node_u));
            if (node_u.getWeight() <= ::max_weight && node_u.getProfit() > ::max_profit){
                ::max_profit = node_u.getProfit();
            }
            if (node_u.getBound() > ::max_profit){
                priority_queue.insert(priority_queue.begin(), node_u);
                sort(priority_queue.begin(), priority_queue.end(), compareBound); //sort priority queue
            }
            node_u.setWeight(temp_node.getWeight());
            node_u.setProfit(temp_node.getProfit());
            node_u.setRatio();//testing
            node_u.setBound(bound(node_u));
            if (node_u.getBound() > ::max_profit){
                priority_queue.insert(priority_queue.begin(), node_u);
                sort(priority_queue.begin(), priority_queue.end(), compareBound); //sort priority queue
            }
        }
    }
}

double bound (Item node_u){
    ::branch_counter++;
    int j_index, k_index;
    int totweight;
    double result;

    if (node_u.getWeight() >= ::max_weight){
        return 0.0;
    }
    else{
        result = node_u.getProfit();
        j_index = node_u.getLevel() + 1; // j = the first unconsidered item
        totweight = node_u.getWeight();
        while (j_index < branch_items.size() && totweight + branch_items.at(j_index).getWeight() <= ::max_weight){ // greedily grab as many items as possible
            totweight = totweight + branch_items.at(j_index).getWeight();
            result = result + branch_items.at(j_index).getProfit();
            j_index++;
        }
    }
    k_index = j_index;
    if (k_index < branch_items.size()){
        result += ((::max_weight - totweight) * (branch_items.at(k_index).getRatio()));
    }
    return result;
}
//----------END BRANCH AND BOUND METHOD-------------//


void my_pause(){
    cin.ignore(1024, '\n');
    cout << "Press enter to continue...";
    cin.get();
}









