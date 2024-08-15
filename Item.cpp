#include "Item.h"
#include <string>


Item::Item(const std::string& name, const int& itemPrice, const double& scrapMultiplier,
    const double& explorerSurvivalMult, const double& operatorSurvivalMult,
    const double& saveChance, const double& lootMult, const bool& bought)
    : _itemName(name), _itemPrice(itemPrice), _scrapValueMultiplier(scrapMultiplier),
    _explorerSurvivalChanceMultiplier(explorerSurvivalMult),
    _operatorSurvivalChanceMultiplier(operatorSurvivalMult),
    _explorerSaveChance(saveChance), _lootRecoveryMultiplier(lootMult), _bought(bought) {}


// Getters

const std::string& Item::getItemName() const{
    return _itemName;
}

const int& Item::getItemPrice() const {
    return _itemPrice;
}

const bool& Item::getBought() const {
    return _bought;
}

const double& Item::getScrapValueMultiplier() const {
    return _scrapValueMultiplier;
}

const double& Item::getExplorerSurvivalChanceMultiplier() const {
    return _explorerSurvivalChanceMultiplier;
}
const double& Item::getOperatorSurvivalChanceMultiplier() const {
    return _operatorSurvivalChanceMultiplier;
}

const double& Item::getExplorerSaveChance() const {
    return _explorerSaveChance;
}

const double& Item::getLootRecoveryMultiplier() const {
    return _lootRecoveryMultiplier;
}


// Setters 
void Item::setBought(const bool& value) {
    _bought = value;
}

