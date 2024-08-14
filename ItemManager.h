#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <vector>
#include <string>

class Game;

class ItemManager {

private:
    std::vector<Item*> _itemsList;


public:

    ItemManager();
    ~ItemManager();

    void registerItem(Item* item);

    void showInventory(const Game& g) const;
    void showStoreItems(const Game& g) const;

    void buyItem(const std::string& itemName, Game& g);
    const std::vector<Item*>& getItemsList() const;

};



#endif // ITEMMANAGER_H
