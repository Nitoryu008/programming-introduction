#include <iostream>
#include <string>
using namespace std;

class AgeManager
{
private:
  string names[3];
  int ages[3];
  int size;

public:
  AgeManager()
      : names{"Taro", "Hana", "Jiro"},
        ages{26, 21, 17},
        size(3)
  {
  }

  void getAge(string &name)
  {
    bool found = false;
    for (int i = 0; i < size; i++)
    {
      if (names[i] == name)
      {
        cout << names[i] << "'s age is " << ages[i] << " years." << endl;
        found = true;
        break;
      }
    }

    if (!found)
    {
      cout << "No age information found for " << name << endl;
    }
  }
};

int main()
{
  AgeManager ageManager;
  string name;

  cout << "Please enter a name: ";
  cin >> name;

  ageManager.getAge(name);

  return 0;
}