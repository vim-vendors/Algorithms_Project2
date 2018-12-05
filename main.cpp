#include <iostream>
#include <vector>
#include <string>


//global variables
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

using namespace std;

void mainMenu();

//global variables
int max_weight = 0;
vector<Item> items;

int getNumber();
string getUserString();
int getStringNumber(const string &st);
bool validateStringInput(const string &st);
bool falseStart(int &test);

void displaySet(vector <Item> &list);

//void knapsack(int index, int profit, int weight){
//    if (weight <= )
//}



//possible deprecated methods
char getUserChar();
int getItemNumber(const char &c);
bool validateInput(const char &c);


int main(int argc, char const *argv[])
{
	mainMenu();
	return 0;
}


//main loop
void mainMenu(){
//    cout << "How many items are there to potentially take? ";
//    int item_no = getNumber();
//
//    //get weights in string convert to array
//
//    cout << "What is the max weight that the bag can hold? ";
//    int max_weight = getNumber();
//
//    cout << "Max weight is " << max_weight << " the Number of items is " << item_no << "\n";
    Item newItem(20, 6);
    cout << "Weight: " << newItem.getWeight() << ", Profit: " <<
    newItem.getProfit() << ", Ratio: " << newItem.getRatio() <<"\n";

    items.push_back(newItem);
    newItem.setProfit(20);
    newItem.setWeight(40);
    cout << "Weight: " << newItem.getWeight() << ", Profit: " <<
         newItem.getProfit() << ", Ratio: " << newItem.getRatio() <<"\n";
    items.push_back(newItem);

    displaySet(items);

    //get profits in string convert to array
    //get max weight bag can hold as string and convert into integer
}

//generic prompt, passes character to other functions
char getUserChar(){
	char choice;
	std::cin >> choice;
    choice = toupper(choice);
	return choice;
}

string getUserString(){
    string _choice;
    //cout << "this is bullshit " << _choice << "\n";
    getline(std::cin, _choice);
    return _choice;
}

//gets char value returns
int getItemNumber(const char &c){
	return c - '0';
}

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


int getNumber(){
    string num_items = getUserString();
    int num = (validateStringInput(num_items)) ? (getStringNumber(num_items)) : (-1);
    if (falseStart(num))//check if input is valid
        return -1;
    else
        return num;
}

void displaySet(vector <Item> &list){
    auto _begin = list.begin();
    auto _end = list.end();

    for (auto it = _begin; it < _end; ++it) {
        cout << "Weight: " << it->getWeight() << ", Profit: " <<
               it->getProfit() << ", Ratio: " << it->getRatio() <<"\n";
    }
    cout << endl;
}