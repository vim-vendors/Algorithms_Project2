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

vector<Item> items;
vector<Item> branch_items;
//vector<Item> brute_items;

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

//sort item vector by ratio
bool compareRatio(Item i1, Item i2);

//for use with priority queue in branch and bound
bool compareBound(Item a, Item b);

//BACKTRACKING ALGORITHM-----//

void knapsack(int index, int profit, int weight);

bool promising(int index, int profit, int weight);

void set_best();
//-----END BACKTRACKING ALGORITHM-----//


//Branch and Bound

void knapsack3 ();
double bound (Item node_u);

//end branch and bound

//test code
void my_pause();


int main()
{
    int dummy_input = 0;
    vector<int> profits;
    vector<int> weights;


//    cout << "How many items are there to potentially take? ";
//    cin >> ::item_no;
//
//    cout << "What is the max weight that the bag can hold? ";
//    cin >>  ::max_weight;
//
//    cout << "Max weight is " << ::max_weight << " the Number of items is " << ::item_no << "\n";
//
//    cout << "Please input a set of profits for all " << ::item_no << " items : \n";
//    for (int index=0; index < item_no; index++){
//        cout << "Profit " << index + 1 << ": ";
//        cin >> dummy_input;
//        //cout << "Profit " << index + 1 <<" is " << dummy_input << "\n";
//        profits.push_back(dummy_input);
//    }
//
//    cout << "Please input a set of matching weights for all " << ::item_no << " items : \n";
//    for (int index=0; index < item_no; index++){
//        cout << "Weight " << index + 1 << ": ";
//        cin >> dummy_input;
//        //cout << "Weight " << index + 1 <<" is " << dummy_input << "\n";
//        weights.push_back(dummy_input);
//    }

    ::max_weight = 16;
    ::item_no = 4;

    //Enter these values to test program
    int test_profits[5] = {40, 30, 50, 10} ;
    int test_weights[5] = {2, 5, 10, 5};

    for (int index=0; index < 4; index++){
        profits.push_back(test_profits[index]);
        weights.push_back(test_weights[index]);
    }

    //test for algorithm 1
    /*
    //push into vector of items
    pushItems(profits, weights, items);
    //sort nodes by non-increasing ratio
    sort(items.begin(), items.end(), compareRatio);
    //needed to insert dummy node into sorted items vector
    Item dummy_node(0, 0);
    items.insert(items.begin(), dummy_node);
    cout << "Your set of items is :\n";
    displaySet(items);
    //call the knapsack method
    knapsack(0, 0, 0);
    cout << "The final amount of profit is $" << ::max_profit << "\n";
    cout << "The final set of items in the knapsack is : \n";
    displaySet(best_set);
    cout << node_counter << " nodes were visited in the state space tree using the backtrack algorithm.\n";
    cout << "\n";
     */
    //push into vector of items
    pushItems(profits, weights, branch_items);
    //sort nodes by non-increasing ratio
    sort(branch_items.begin(), branch_items.end(), compareRatio);
    //needed to insert dummy node into sorted items vector
    Item dummy_node(0, 0);
    branch_items.insert(branch_items.begin(), dummy_node);
    cout << "Your set of items is :\n";
    displaySet(branch_items);
    //call the knapsack method
    knapsack3();
    cout << "The final amount of profit is $" << ::max_profit << "\n";

    cout << "The final set of items in the knapsack is : \n";
    displaySet(priority_queue);
    cout << branch_counter << " nodes were visited in the state space tree using the backtrack algorithm.\n";
    cout << "\n";

    return 0;
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
             it->getProfit() << ", Ratio: " << it->getRatio() << ", Bound: " << it->getBound() << ", Level: " << it->getLevel() << "\n";
    }
    cout << endl;
}

//sort vectors by nonincreasing ratio
bool compareRatio(Item a, Item b)
{
    return (a.getRatio() > b.getRatio());
}

bool compareBound(Item a, Item b)
{
    return (a.getBound() > b.getBound());
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
        cout << "Displaying queue\n";
        displaySet(priority_queue);
        priority_queue.erase (priority_queue.begin()); //remove (PQ, v); // remove unexpanded node with best bound
        cout << "Displaying queue post-erasure\n";
        displaySet(priority_queue);
        if (node_v.getBound() > ::max_profit){
            node_u.setLevel(node_v.getLevel() + 1);

            node_u.setWeight(node_v.getWeight() + branch_items.at(node_u.getLevel()).getWeight());
            node_u.setProfit(node_v.getProfit() + branch_items.at(node_u.getLevel()).getProfit());
            node_u.setRatio();//testing
            node_u.setBound(bound(node_u));
            if (node_u.getWeight() <= ::max_weight && node_u.getProfit() > ::max_profit){
                ::max_profit = node_u.getProfit();

                cout << "From knapsack while IF#2: Max profit is  " << ::max_profit <<"\n";

            }
            if (node_u.getBound() > ::max_profit){
                priority_queue.insert(priority_queue.begin(), node_u);
                sort(priority_queue.begin(), priority_queue.end(), compareBound); //sort priority queue
                cout << "From knapsack while IF#3: display queue\n";
                displaySet(priority_queue);
            }
            node_u.setWeight(node_v.getWeight());
            node_u.setProfit(node_v.getProfit());
            node_u.setRatio();//testing
            node_u.setBound(bound(node_u));
            if (node_u.getBound() > ::max_profit){
                priority_queue.insert(priority_queue.begin(), node_u);
                sort(priority_queue.begin(), priority_queue.end(), compareBound); //sort priority queue
                cout << "From knapsack while IF#4: display queue\n";
                displaySet(priority_queue);
            }
            cout << "From knapsack while IF#1: Node u level is  " << node_u.getLevel() <<"\n";
        } // see if node is still promising

    }

}

double bound (Item node_u){

    int j_index, k_index;
    int totweight;
    double result;

    cout << " Bound pre-if: Node u weight is " << node_u.getWeight() << ", Max weight is " << ::max_weight << "\n";

    if (node_u.getWeight() >= ::max_weight){
        cout << " Returning zero from bound IF #1 \n";

        return 0.0;
    }



    else{
        result = node_u.getProfit();
        j_index = node_u.getLevel() + 1; // j = the first unconsidered item
        totweight = node_u.getWeight();

        cout << "In bound else: Result is " << result << ", J index is " << j_index <<  ", Total weight is " << totweight << "\n";

        while (j_index < branch_items.size() && totweight + branch_items.at(j_index).getWeight() <= ::max_weight){ // greedily grab as many items as possible
            totweight = totweight + branch_items.at(j_index).getWeight();
            result = result + branch_items.at(j_index).getProfit();
            j_index++;

            cout << "In bound while: Result is " << result << ", J index is " << j_index <<  ", Total weight is " << totweight << ", branch size is " << branch_items.size() <<"\n";
            my_pause();

        }
    }
    k_index = j_index;
    if (k_index < branch_items.size()){
        result += ((::max_weight - totweight) * (branch_items.at(k_index).getRatio()));
        cout << "In last bound if for result: Result is " << result <<"\n";

    }
    return result;
}
//----------END BRANCH AND BOUND METHOD-------------//


void my_pause(){
    cin.ignore(1024, '\n');
    cout << "Press enter to continue...";
    cin.get();
}











