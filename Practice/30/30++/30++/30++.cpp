// 30++.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

# include <iostream>
# include <vector>
# include <cstdlib>
# include <ctime>
# include <algorithm>
# include <string>

struct Coin {
    int count;
};

struct Rune {
    enum class Element { FIRE, WATER, EARTH, AIR } element;
    int level;
};

std::string to_string(Rune::Element& element);

struct Weapon {
    int damage;
    int critical;
    int durability;
};

struct Armor {
    int guard;
    int durability;
};

struct Item;
Item generateItem();

struct Item
{
    enum class ItemType { COIN, RUNE, WEAPON, ARMOR } type;
    union Value { Coin coin; Rune rune; Weapon weapon; Armor armor; } value;

    Item& operator++()
    {
        *this = generateItem();
        return *this;
    }
};

Item GetCoin(int count);

Item GetRune(Rune::Element element, int level);
Item GetFireRune(int level);
Item GetWaterRune(int level);
Item GetEarthRune(int level);
Item GetAirRune(int level);

Item GetWeapon(int damage, int critical, int durability);
Item GetArmor(int guard, int durability);

template<class T, class S>
struct Pair
{
    T first;
    S second;
};

std::vector<Pair<Item, double>> chances{
    {GetCoin(1000), 50.0},
    {GetFireRune(1), 6.0},
    {GetWaterRune(1), 13.0},
    {GetEarthRune(1), 7.0},
    {GetAirRune(1), 14.0},
    {GetFireRune(5), 0.6},
    {GetWaterRune(5), 1.3},
    {GetEarthRune(5), 0.7},
    {GetAirRune(5), 1.4},
    {GetFireRune(5), 0.06},
    {GetWaterRune(5), 0.13},
    {GetEarthRune(5), 0.07},
    {GetAirRune(5), 0.14},
    {GetWeapon(100, 0, 100), 1.4},
    {GetWeapon(75, 50, 100), 1.4},
    {GetArmor(50, 100), 2.8},
};

const int precision = 100;  // Точность до сотых в шансах
double count_total_chance() {
    double sum = 0;
    for (auto& pair : chances) {
        sum += pair.second;
    }
    return sum * precision;
}

const double total_chance = count_total_chance();  // сумма всех шансов

using LootBox = std::vector<Item>;

LootBox generateLootBox();

LootBox& operator<<(LootBox& lootbox, Item& item);

std::ostream& operator<<(std::ostream& out, Item& item);

std::ostream& operator<<(std::ostream& out, LootBox& lootbox);

// std::string toLowerCase(std::string str);

// std::string toLowerCase(std::string data) {
//     return std::transform(data.begin(), data.end(), data.begin(),
//     [](unsigned char c){ return std::tolower(c); });
// }

LootBox& operator<<(LootBox& lootbox, Item item) {
    lootbox.push_back(item);
    return lootbox;
}

Item generateItem() {
    double r = double(rand() % int(total_chance)) / 100; // [0.00; 100.00)
    double current_sum = 0;

    for (auto& elem : chances) {
        if (current_sum <= r and r < current_sum + elem.second) {
            return elem.first;
        }
        current_sum += elem.second;
    }
    return chances[0].first;
}

LootBox generateLootBox() {
    LootBox box;
    std::srand(std::time(0));

    for (int i = 0; i < 3; ++i) {
        box << generateItem();
    }
    return box;
}

std::ostream& operator<<(std::ostream& out, Item& item) {
    Item::ItemType& type = item.type;

    if (type == Item::ItemType::COIN) {
        out << item.value.coin.count << " gold";
    }
    else if (type == Item::ItemType::RUNE) {
        Rune& rune = item.value.rune;
        out << "Rune of " << to_string(rune.element)
            << " level " << rune.level;
    }
    else if (type == Item::ItemType::WEAPON) {
        Weapon& weapon = item.value.weapon;
        out << "Weapon {damage: " << weapon.damage
            << ", critical: " << weapon.critical
            << ", durability: " << weapon.durability
            << "}";
    }
    else if (type == Item::ItemType::ARMOR) {
        Armor& armor = item.value.armor;
        out << "Armor {guard: " << armor.guard
            << ", durability: " << armor.durability
            << "}";
    }
    out << std::flush;
    return out;
}

std::ostream& operator<<(std::ostream& out, LootBox& lootbox) {
    for (auto& elem : lootbox) {
        out << elem << "\n" << std::flush;
    }
    return out;
}

std::string to_string(Rune::Element& element) {
    std::string result;

    switch (element) {
    case Rune::Element::FIRE:
        result = "fire";
        break;
    case Rune::Element::WATER:
        result = "water";
        break;
    case Rune::Element::EARTH:
        result = "earth";
        break;
    case Rune::Element::AIR:
        result = "air";
        break;
    }

    return result;
}

Item GetCoin(int count) {
    return {
        Item {
            Item::ItemType::COIN,
            Item::Value {.coin = Coin{count}}
        }
    };
}
Item GetRune(Rune::Element element, int level) {
    return {
        Item {
            Item::ItemType::RUNE,
            Item::Value {
                .rune = Rune {
                    element,
                    level
                }
            }
        }
    };
}
Item GetFireRune(int level) {
    return GetRune(Rune::Element::FIRE, level);
}
Item GetWaterRune(int level) {
    return GetRune(Rune::Element::WATER, level);
}
Item GetEarthRune(int level) {
    return GetRune(Rune::Element::EARTH, level);
}
Item GetAirRune(int level) {
    return GetRune(Rune::Element::AIR, level);
}
Item GetWeapon(int damage, int critical, int durability) {
    return {
        Item {
            Item::ItemType::WEAPON,
            Item::Value{.weapon = Weapon{damage, critical, durability}}
        }
    };
}
Item GetArmor(int guard, int durability) {
    return {
        Item {
            Item::ItemType::ARMOR,
            Item::Value{.armor = Armor{guard, durability}}
        }
    };
}

using namespace std;
int main()
{
    setlocale(0, "");
    string line;
    cout << "Открыть лутбокс? Yes/No" << endl;
    cin >> line;
    if (line == "Y" or line == "yes" or line == "y" or line == "YES" or line == "Yes")
    {
        cout << "Молодес" << endl;
        return main();
    }
    else if (line == "NO" or line == "N" or line == "n" or line == "no" or line == "No")
    {
        return 0;
    }
    else
    {
        return main();
    }
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл