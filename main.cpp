#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <string>

const int holidays[12][2] = {
  {1, 0},
  {23, 0},
  {8, 0},
  {0, 0},
  {1, 9},
  {0, 0},
  {0, 0},
  {21, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {31, 0}
};

using namespace sf;

int is_leap(int y);
int day_of_week(int d, int m, int y, int first_date);
int space(int s);
int days_in_month(int m, int y);
void draw_month(int x, int y, int first_day_of_week, int days_number, RenderWindow& window, Text& display_text, const int holidays[2]);
void display_calendar(int year, RenderWindow& window, Text& display_text, Sprite& s, int first_date);

int is_leap(int y)
{
    if (y%4 != 0)
        return 0;
    else if (y%100 == 0 && y%400 != 0)
        return 0;
    else
        return 1;
}

int day_of_week(int d, int m, int y, int first_date){
    int amount_of_days = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400 + d;
    for (int i = 1; i < m; ++i){
        amount_of_days += days_in_month(i, y);
    }
    int ans = (first_date + (amount_of_days - 1) % 7);
    if (ans <= 0)
        ans += 7;
    return ans;
}

int space(int s)
{
    if (s < 9)
        return 37;
    else
        return 33;
}

int days_in_month(int m, int y)
{
    switch(m)
    {
        case 1: return 31; break;
        case 2: return 28 + is_leap(y); break;
        case 3: return 31; break;
        case 4: return 30; break;
        case 5: return 31; break;
        case 6: return 30; break;
        case 7: return 31; break;
        case 8: return 31; break;
        case 9: return 30; break;
        case 10: return 31; break;
        case 11: return 30; break;
        case 12: return 31; break;
    }
}

void draw_month(int x, int y, int first_day_of_week, int days_number, RenderWindow& window, Text& display_text, const int holidays[2])
{
    int count_days = 0;
    int count_weeks = 0;

    for (int j = 1; j <= 6; j++)
    {
        for (int i = 0; i <= 7-first_day_of_week; i++)
        {
            if (i + first_day_of_week >= 6)
                display_text.setColor(Color::Red);
            if ((count_days + count_weeks + 1 == holidays[0]) || (count_days + count_weeks + 1 == holidays[1]))
                display_text.setColor(Color::Blue);
            display_text.setString(std::to_string(i + count_weeks + 1));
            display_text.setPosition(x + space(count_days + count_weeks) + (i+first_day_of_week-1)*34, 99+(j+y)*17);
            window.draw(display_text);
            count_days++;
            display_text.setColor(Color::Black);
            if(count_days + count_weeks == days_number)
                break;
        }

        if (count_days + count_weeks == days_number)
            break;

        count_weeks += count_days;
        count_days = 0;
        first_day_of_week = 1;
    }
}

void display_calendar(int year, RenderWindow& window, Text& display_text, Sprite& s, int first_date)
{
    window.clear(Color(Color::White));

    window.draw(s);

    display_text.setCharacterSize(30);
    display_text.setString(std::to_string(year));
    display_text.setPosition(515, 20);
    window.draw(display_text);

    display_text.setCharacterSize(14);

    draw_month(0, -1, day_of_week(1, 1, year, first_date), days_in_month(1, year), window, display_text, holidays[0]);
    draw_month(272, -1, day_of_week(1, 2, year, first_date), days_in_month(2, year), window, display_text, holidays[1]);
    draw_month(544, -1, day_of_week(1, 3, year, first_date), days_in_month(3, year), window, display_text, holidays[2]);
    draw_month(816, -1, day_of_week(1, 4, year, first_date), days_in_month(4, year), window, display_text, holidays[3]);
    draw_month(0, 8, day_of_week(1, 5, year, first_date), days_in_month(5, year), window, display_text, holidays[4]);
    draw_month(272, 8, day_of_week(1, 6, year, first_date), days_in_month(6, year), window, display_text, holidays[5]);
    draw_month(544, 8, day_of_week(1, 7, year, first_date), days_in_month(7, year), window, display_text, holidays[6]);
    draw_month(816, 8, day_of_week(1, 8, year, first_date), days_in_month(8, year), window, display_text, holidays[7]);
    draw_month(0, 17, day_of_week(1, 9, year, first_date), days_in_month(9, year), window, display_text, holidays[8]);
    draw_month(272, 17, day_of_week(1, 10, year, first_date), days_in_month(10, year), window, display_text, holidays[9]);
    draw_month(544, 17, day_of_week(1, 11, year, first_date), days_in_month(11, year), window, display_text, holidays[10]);
    draw_month(816, 17, day_of_week(1, 12, year, first_date), days_in_month(12, year), window, display_text, holidays[11]);

    window.display();
}

int main()
{
    int year;
    int first_date = 1 - (2019 * 365 + 13 + 2019 / 4 - 2019 / 100 + 2019 / 400 - 1) % 7;
    if (first_date <= 0)
        first_date += 7;

    setlocale(0,"");
    std::cout << "Введите год ";
    std::cin >> year;

    RenderWindow window(VideoMode(1100, 550), "CALENDAR!");
    window.setVerticalSyncEnabled(true);

    Texture calendar_template;
    calendar_template.loadFromFile("C:/study/cppProgects/Календарь.PNG");
    Sprite s;
    s.setTexture(calendar_template);
    s.setPosition(10, 50);

    Text display_text;
    Font font;

    font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");
    display_text.setFont(font);

    display_text.setColor(Color::Black);

    display_calendar(year, window, display_text, s, first_date);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::D)
                {
                    ++year;
                    display_calendar(year, window, display_text, s, first_date);
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    if(year > 1)
                    {
                        --year;
                        display_calendar(year, window, display_text, s, first_date);
                    }
                }
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

    }

    return 0;
}
