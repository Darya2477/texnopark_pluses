#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <regex>

//СТРУКТУРА "РЕЖИССЕР-ФИЛЬМЫ"
struct director_and_his_films{
    std::string dir;
    std::vector<std::string> films;
};

//ПРОЦЕДУРА ДЛЯ НАХОЖДЕНИЯ ВСЕХ ЛЮДЕЙ ПО ДАННОМУ ИМЕНИ
void all_directors(std::string file_name, std::vector<director_and_his_films> &mass_of_results, std::string director_name);

//ПРОЦЕДУРА ДЛЯ ПРОВЕРКИ, ЯВЛЯЮТСЯ ЛИ ЭТИ ЛЮДИ ПРОДЮССЕРАМИ (ЕСЛИ ДА, ТО ЗАПОМНИМ ВСЕ КИНОКАРТИНЫ, КОТОРЫЕ ОНИ СПРОДЮССИРОВАЛИ)
void all_directors_and_all_their_films(std::string file_name, std::vector<director_and_his_films> &mass_of_results );

//ПРОЦЕДУРА ДЛЯ ИСКЛЮЧЕНИЯ ИЗ ОТСНЯТЫХ КИНОКАРТИН ЭПИЗОДЫ СЕРИАЛОВ/TV-ШОУ (ЧТОБЫ ОСТАЛИСЬ ТОЛЬКО ФИЛЬМЫ)
void all_directors_and_all_their_films_without_series(std::string file_name, std::vector<director_and_his_films> &mass_of_results);

//ПРОЦЕДУРА ДЛЯ НАХОЖДЕНИЯ РУССКИХ НАЗВАНИЙ(ПРИ НАЛИЧИИ) ФИЛЬМОВ, КОТОРЫЕ ОТСНЯЛ ЭТОТ РЕЖИССЕР, ВОЗРАСТНОЕ ОГРАНИЧЕНИЕ КОТОРЫХ НЕ 18+
void all_directors_and_all_their_films_without_series_not_adult_in_russian(std::string file_name, std::vector<director_and_his_films> &mass_of_results);

//ИТОГОВЫЙ ВЫВОД РЕЗУЛЬТАТОВ
void print_all_directors_and_all_their_films_without_series_not_adult_in_russian(std::vector<director_and_his_films> &mass_of_results, std::string director_name);