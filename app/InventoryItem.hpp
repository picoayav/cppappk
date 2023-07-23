#include "Blocks.hpp"
#include <iostream>
class InventoryItem {
public:
    Blocks getItem();
    int getCount();
private:
    Blocks block;
    int count;
};