#include "ItemManager.h"
#include "Item.h"
#include "Game.h"
#include "util.h"
#include <string>
#include <iostream>

ItemManager::ItemManager() {}

const std::vector<Item*>& ItemManager::getItemsList() const {
    return _itemsList;
}


void ItemManager::registerItem(Item* item) {
    _itemsList.push_back(item);
}

void ItemManager::showInventory(const Game& g) const {
    std::cout << "\nThe following items are available." << std::endl;
    std::cout << "---------------------------------------\n" << std::endl;

    bool noItems = true;

    // User has items bought
    for (const auto& item : _itemsList) {
        if (item->getBought()) {
            noItems = false;
            std::cout << "* " << item->getItemName() << std::endl;
        }
    }

    // User doesn't have any items bought
    if (noItems) {
        std::cout << "(Empty)\n" << std::endl;
    }

    std::cout << "\nBalance: $" << g.getBalance() << " (quota is $" << g.getQuota() << ")" << std::endl;
    std::cout << "Cargo value: $" << g.getCargoValue() << std::endl;
}

void ItemManager::showStoreItems(const Game& g) const {
    std::cout << "\nWelcome to the Corporation store." << std::endl;
    std::cout << "Use the word BUY on any item.\n ---------------------------------------\n" << std::endl;

    for (const auto& itemPtr : _itemsList) {
        
        if (itemPtr->getBought()) {
            // Show bought if the item is already bought by the user
            std::cout << "* " << itemPtr->getItemName() << " // Bought " << std::endl;

        } else {
            std::cout << "* " << itemPtr->getItemName() << " // Price: $" << itemPtr->getItemPrice() << std::endl;
        }
    }

    std::cout << "\nBalance: $" << g.getBalance() << std::endl;

}

void ItemManager::buyItem(const std::string& itemName, Game& g) {

    for (auto& itemPtr : _itemsList) {

        std::string item = itemPtr->getItemName();

        util::lower(item);

        if (item == itemName) {
            
            // User already owns the item
            if (itemPtr->getBought() == true) {
                std::cout << "\nYou already own a " << itemName << "." << std::endl;
                return;
            }

            if (itemPtr->getItemPrice() > g.getBalance()) {
                std::cout << "\nInsufficient balance to buy " << itemName << "." << std::endl;
                return;
            }
            
            g.setBalance(g.getBalance() - itemPtr->getItemPrice());

            std::cout << "\nSuccessfully bought " << itemName << "." << std::endl;
            itemPtr->setBought(true);

            return;
        }
    }
    std::cout << "\nUnknown item '" << itemName << "'." << std::endl;


}

ItemManager::~ItemManager() {

    // Deletes the items inside the itemsList 
    for (Item* item : _itemsList) {
        delete item;
    }

    // Deletes the itemlist itself 
    _itemsList.clear();
}