#include <iostream>
#include <string>
#include <limits>
#include <Windows.h>
#define OFFSET 3
using namespace std;

class Member
{
private:
    string name;
    char group;
    string habitat;
    int population;
public:
    string GetName()
    {
        return name;
    }

    void SetName(string value)
    {
        if(value != "")
         name = value;
    }

    char GetGroup()
    {
        return group;
    }

    void SetGroup(char value)
    {
        if (value != ' ')
            group = value;
    }

    string GetHabitat()
    {
        return habitat;
    }

    void SetHabitat(string value)
    {
        if (value != "")
            habitat = value;
    }

    int GetPopulation()
    {
        return population;
    }

    void SetPopulation(int value)
    {
        if (value >= 0)
            population = value;
    }

    void Show()
    {
        cout << "Имя: " << name;
        cout << "Группа: " << group;
        cout << "Место обитания: " << habitat;
        cout << "Популяция: " << population;
    }

    friend istream& operator >>(istream& is, Member& m)
    {
        while (true)
        {
            is >> m.name >> m.group >> m.habitat >> m.population;

            if (is.fail())
            {
                cout << "Ошибка ввода данных, попробуйте еще раз\n";
                is.clear();
                is.ignore(INT16_MAX, '\n');
                continue;
            }
            break;
        }
        return is;
    }
};

void DrawLine(int width);
void DrawMember(string text, int width);
void FindWidth(Member* members, int membersSize, int& first, int& third, int& fourth);
void DrawNote(string note, int totalWidth);


int main()
{
    setlocale(LC_ALL, "Russian");

    int size;
    string name = "Название", group = "Группа", habitat = "Место обитания", population = "Популяция", note = "Групи: А - настоящие антилопы, B - коровьи антилопы, H - лошадиные антилопи";
    int firstMemberWidth = name.size(), secondMemberWidth = group.size(), thirdMemberWidth = habitat.size(), fourthMemberWidth = population.size();
    cout << "Введите количество элементов:\n";
    while (true)
    {
        cin >> size;

        if (cin.fail())
        {
            cout << "Ошибка ввода данных, попробуйте еще раз\n";
            cin.clear();
            cin.ignore(INT16_MAX, '\n');
            continue;
        }
        break;
    }

    Member* members = new Member[size];

    for (int i = 0; i < size; ++i)
    {
        cout << i + 1 << ". Введите данные -> Имя -> Группа -> Место обитания -> Популяция:\n";
        cin >> members[i];
    }

    FindWidth(members, size, firstMemberWidth, thirdMemberWidth, fourthMemberWidth);

    int totalWidth = firstMemberWidth + secondMemberWidth + thirdMemberWidth + fourthMemberWidth;
    int noteSize = note.size();

    totalWidth = totalWidth < noteSize ? noteSize : totalWidth;

    fourthMemberWidth = totalWidth - (firstMemberWidth + secondMemberWidth + thirdMemberWidth);

    DrawLine(totalWidth);
    cout << '|';
    DrawMember(name, firstMemberWidth);
    DrawMember(group, secondMemberWidth);
    DrawMember(habitat, thirdMemberWidth);
    DrawMember(population, fourthMemberWidth);
    cout << '\n';

    for (int i = 0; i < size; ++i)
    {
        DrawLine(totalWidth);
        cout << '|';
        DrawMember(members[i].GetName(), firstMemberWidth);
        DrawMember(string(1, members[i].GetGroup()), secondMemberWidth);
        DrawMember(members[i].GetHabitat(), thirdMemberWidth);
        DrawMember(to_string(members[i].GetPopulation()), fourthMemberWidth);
        cout << '\n';
    }

    DrawNote(note, totalWidth);

    return 0;
}

void FindWidth(Member* members, int membersSize, int& first, int& third, int& fourth)
{
    for (int i = 0; i < membersSize; ++i)
    {
        if (members[i].GetName().size() > first)
            first = members[i].GetName().size();
    }

    for (int i = 0; i < membersSize; ++i)
    {
        if (members[i].GetHabitat().size() > third)
            third = members[i].GetHabitat().size();
    }

    for (int i = 0; i < membersSize; ++i)
    {
        if (to_string(members[i].GetPopulation()).size() > fourth)
            fourth = to_string(members[i].GetPopulation()).size();
    }
}

void DrawMember(string text, int width)
{
    cout << text;
    for (int i = 0; i < width - text.size(); i++)
        cout << ' ';

    cout << '|';
}

void DrawLine(int width)
{
    cout << '|';
    width += OFFSET;
    for (int i = 0; i < width; ++i)
        cout << '=';

    cout << "|\n";
}

void DrawNote(string note, int totalWidth)
{
    DrawLine(totalWidth);
    cout << '|' << note;
    for (int i = 0; i < totalWidth - note.size() + OFFSET; i++)
        cout << ' ';
    cout << "|\n";
    DrawLine(totalWidth);

}