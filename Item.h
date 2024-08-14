#include <string>
#ifndef ITEM_H
#define ITEM_H

class Item {

private:
    std::string _itemName;
    int _itemPrice;
    bool _bought;
    double _scrapValueMultiplier;
    double _explorerSurvivalChanceMultiplier;
    double _operatorSurvivalChanceMultiplier;
    double _explorerSaveChance;
    double _lootRecoveryMultiplier;

public:
    Item (const std::string& name, const int& itemPrice, const double& scrapMultiplier,
        const double& explorerSurvivalMult, const double& operatorSurvivalMult,
        const double& saveChance, const double& lootMult, const bool& bought = false);

    const std::string& getItemName() const;
    const int& getItemPrice() const;
    const bool& getBought() const;

    const double& getScrapValueMultiplier() const;
    const double& getExplorerSurvivalChanceMultiplier() const;

    const double& getOperatorSurvivalChanceMultiplier() const;
    const double& getExplorerSaveChance() const;
    const double& getLootRecoveryMultiplier() const;

    void setBought(const bool& value);

};


#endif // ITEM_H
