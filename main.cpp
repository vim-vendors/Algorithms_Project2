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

    //getter
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
    this->ratio = (profit * 1.0) / (weight* 1.0) ;
}

int Item::setProfit(int profit){
    this->profit = profit;
    setRatio();
}

int Item::setWeight(int weight){
    this->weight = weight;
    setRatio();
}

int Item::setRatio(){
    int temp_profit = getProfit();
    int temp_weight = getWeight();
    this->ratio = (temp_profit * 1.0) / (temp_weight* 1.0) ;
}
//-----END CLASS METHODS-----//


//-----global variables-----//
int max_weight = 0;
vector<Item> items;

//-----Program Methods-----//
void mainMenu();

//-----getters-----//
int getNumber();
string getUserString();

//-----setters-----//

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

//void knapsack(int index, int profit, int weight);

//bool promising();

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
/*    cout << "How many items are there to potentially take? ";
    int item_no = getNumber();

    //get weights in string convert to array

    cout << "What is the max weight that the bag can hold? ";
    int max_weight = getNumber();

    cout << "Max weight is " << max_weight << " the Number of items is " << item_no << "\n";



    //build function to push array into vector list
    cout << "Please input a set of profits for all " << item_no << " items : ";*/


    //    TEST CODE
    cout << "Please input a set of profits for all 6 items : \n";
    //body of function
    //get strings, push values into existing vector <int>
    int test[6] = {1,2, 3, 4, 5, 6} ;

    for (int index=0; index < 6; index++){
        cout << test[index] << " ";
    }
    cout << "\n";

    //    END TEST CODE

    //build function sort vector by some criteria

    //build knapsack
    //build promise



/*    Item newItem(20, 6);
    cout << "Weight: " << newItem.getWeight() << ", Profit: " <<
    newItem.getProfit() << ", Ratio: " << newItem.getRatio() <<"\n";

    items.push_back(newItem);
    newItem.setProfit(20);
    newItem.setWeight(40);
    cout << "Weight: " << newItem.getWeight() << ", Profit: " <<
         newItem.getProfit() << ", Ratio: " << newItem.getRatio() <<"\n";
    items.push_back(newItem);

    displaySet(items);*/

    //get profits in string convert to array
    //get max weight bag can hold as string and convert into integer
}

//-----getters-----//
//----------------//

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

//BACKTRACKING ALGORITHM-----//

    /*void knapsack(int index, int profit, int weight){
        if (weight <= )
    }*/

//bool promising(){}
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

















