#include "Flower.h"
using namespace std;

int main() {
    Plant* plant = new Flower;

    plant -> tick();
    plant -> tick();

    (*plant) << cout;

    cout << endl;
    
    return 0;
}