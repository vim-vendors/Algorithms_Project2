#include <iostream>
#include <vector>
#include <string>

using namespace std;

//-----CLASS METHODS-----//
class Item {
private:
    int profit;
    int weight;
    double ratio;
public:
    //constructor
    Item();
    Item(int profit, int weight);

    //getter (declared here)
    int getProfit() {return this->profit;};
    int getWeight() {return this->weight;};
    double getRatio() {return this->ratio;};

    //setter
    int setProfit(int profit);
    int setWeight(int weight);
    int setRatio();
};

Item::Item(){
    this->weight = 0;
    this->profit = 0;
    this->ratio = 0.0;
}

Item::Item(int profit, int weight){
    this->weight = weight;
    this->profit = profit;
    setRatio();
}


int Item::setProfit(int profit){
    this->profit = profit;
}

int Item::setWeight(int weight){
    this->weight = weight;
}

//sets ratio, in case of division of/by zero replaces nan with zero
int Item::setRatio(){
    int temp_profit = getProfit();
    int temp_weight = getWeight();
    if (temp_profit == 0 || temp_weight == 0)
        this->ratio = 0;
    else
        this->ratio = (temp_profit * 1.0) / (temp_weight* 1.0) ;
}


//-----END CLASS METHODS-----//


//-----global variables-----//
int max_weight = 0;
int max_profit = 0;
vector<Item> items;
vector<Item> best_set;
vector<Item> include;

//-----Program Methods-----//
void mainMenu();

//-----getters-----//
double _getRatio(const int &index, vector<Item> node);

int _getProfit(const int &index, vector<Item> node);

int _getWeight(const int &index, vector<Item> node);


//-----setters-----//

int getNumber();
string getUserString();


//push to items vector set
void pushItems(const vector<int> &profits, const vector<int> &weights, vector<Item> &node);

//pop item from items vector
void popItems(const int &index, vector<Item> &node);

//need method to copy include vector to best_set vector for knapsack algorithm to work

//-----conversion-----//
int getStringNumber(const string &st);

//-----boolean-----//
bool validateStringInput(const string &st);
bool falseStart(int &test);
bool validateInput(const char &c);

//-----output-----//
void displaySet(vector <Item> &list);

//-----test code-----//




//BACKTRACKING ALGORITHM-----//

void knapsack(int index, int profit, int weight);

bool promising(int index, int profit, int weight);

void set_best();

//-----END BACKTRACKING ALGORITHM-----//



//-----deprecated code-----//
char getUserChar();
int getItemNumber(const char &c);



int main(int argc, char const *argv[])
{
	mainMenu();
	return 0;
}

//-----Program Methods-----//
//------------------------//


//main loop
void mainMenu(){
/*
    cout << "How many items are there to potentially take? ";
    int item_no = getNumber();

    //get weights in string convert to array

    cout << "What is the max weight that the bag can hold? ";
    int max_weight = getNumber();

    cout << "Max weight is " << max_weight << " the Number of items is " << item_no << "\n";
*/



    //build function to push array into vector list
    //cout << "Please input a set of profits for all " << item_no << " items : \n";

    //cout << "Please input a set of profits for all 6 items : \n";
    //body of function

    //get strings,
    //
    int test_profits[5] = {0, 40, 30, 50, 10} ;
    int test_weights[5] = {0, 2, 5, 10, 5} ;


    //push strings into vector, push into profits or weights variables
    vector<int> profits;
    vector<int> weights;

    for (int index=0; index < 5; index++){
        cout << test_profits[index] << " ";
        profits.push_back(test_profits[index]);
    }
    cout << "\n";
    for (int index=0; index < 5; index++){
        cout << test_weights[index] << " ";
        weights.push_back(test_weights[index]);
    }

    cout << "\n";

    pushItems(profits, weights, items);
    displaySet(items);
    ::max_weight = 16;

    knapsack(0, 0, 0);
    cout << "Final max profit is $" << ::max_profit << "\n";
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

int getNumber(){
    string num_items = getUserString();
    int num = (validateStringInput(num_items)) ? (getStringNumber(num_items)) : (-1);
    if (falseStart(num))//check if input is valid
        return -1;
    else
        return num;
}
string getUserString(){
    string _choice;
    //cout << "this is bullshit " << _choice << "\n";
    getline(std::cin, _choice);
    return _choice;
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


//-----conversion-----//
//-------------------//

//converts string into number
int getStringNumber(const string &st){
    try {
        //string temp = st;
        return  std::stoi (st);
    }
    catch (int e)
    {
        return -1;
    }
}


//-----boolean-----//
//----------------//

//if not numeric return  false
bool validateInput(const char &c){
    if (!isdigit(c))
        return false;
    else
        return true;
}

bool validateStringInput(const string &st){

    if (st == "")
        return false;

    for (int i=0;i<st.size();i++)
        if (!isdigit(st[i]))
            return false;
    return true;
}

//refactored boilerplate
bool  falseStart(int &test){
    if (test == -1){
        cout << "You have incorrectly entered a variable.\n";
        return true;
    }
    else
        return false;
}


//-----output-----//
//----------------//

void displaySet(vector <Item> &list){
    auto _begin = list.begin();
    auto _end = list.end();

    for (auto it = _begin; it < _end; ++it) {
        cout << "Weight: " << it->getWeight() << ", Profit: " <<
             it->getProfit() << ", Ratio: " << it->getRatio() <<"\n";
    }
    cout << endl;
}


//-----test code-----//
//------------------//

void knapsack(int index, int profit, int weight){
/*    cout << "Knapsack call\n";
    cout << "Max profit is " << ::max_profit << ", profit is "<< profit << "\n";
    cout << "Max weight is " << ::max_weight << ", weight is "<< weight << "\n";*/

    if ((weight <= ::max_weight) && (profit > ::max_profit)){
//        cout << "IF #1 call\n";
        ::max_profit = profit;
        //numBest = i;
        //copy include into best_set
        set_best();
    }
    if (promising(index, profit, weight)){
//        cout << "Node " << index << " from items set is promising\n";

        unsigned int temp = index;
        //push index + 1 node to includes
        include.push_back(items.at(temp + 1));

//        cout << "IF #2 include push call\n";
//        displaySet(include);

        //recursive call to knapsack
        knapsack(index + 1, profit + items.at(temp + 1).getProfit(), weight + items.at(temp + 1).getWeight());

//        cout << "Recursive drop 1 \n";

        //pop index + 1 node from includes
        include.pop_back();

/*        cout << "IF #2 include pop call\n";
        displaySet(include);
        cout << "Index + 1 is " << index + 1 << " \n";*/

        //recursive call to knapsack
        knapsack(index + 1, profit, weight);

//        cout << "Recursive drop 2 \n";

    }
}

//BACKTRACKING ALGORITHM-----//

bool promising(int index, int profit, int weight){
    int j_index, k_index, total_weight;
    double bound;

/*    cout << "Promising call\n";
    cout << "Max profit is " << ::max_profit << ", profit is "<< profit << "\n";
    cout << "Max weight is " << ::max_weight << ", weight is "<< weight << "\n";*/

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

//        cout << "K index is " << k_index << ", size is "<< items.size() << "\n";

        if (k_index < items.size())
            bound += ((::max_weight - total_weight) *  items.at(temp).getRatio());

//        cout << "Bound is " << bound << ", total weight is "<< total_weight << "\n";

        return (bound > ::max_profit);
    }
 }


void set_best(){


    //clear best
    best_set.clear();
    //copy everything into best from includes
    for (unsigned index=0; index < include.size(); index++){
        best_set.push_back(include.at(index));
    }

/*    cout << "Best set post-op call\n";
    displaySet(best_set);*/
}

//-----END BACKTRACKING ALGORITHM-----//



//-----deprecated code-----//
//------------------------//

//generic prompt, passes character to other functions
char getUserChar(){
    char choice;
    std::cin >> choice;
    choice = toupper(choice);
    return choice;
}

//gets char value returns
int getItemNumber(const char &c){
    return c - '0';
}

















