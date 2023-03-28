#include "./file_working_functions.h"

int main(int argc, char *argv[]){
    std::vector<director_and_his_films> mass_of_directors_and_their_films;    //массив из структур "режиссер-фильмы", который мы меняем в функциях, написанных ниже
  
    all_directors(argv[1], mass_of_directors_and_their_films, argv[5] );
    all_directors_and_all_their_films(argv[2],mass_of_directors_and_their_films);
    all_directors_and_all_their_films_without_series(argv[3], mass_of_directors_and_their_films);
    all_directors_and_all_their_films_without_series_not_adult_in_russian(argv[4], mass_of_directors_and_their_films);
    print_all_directors_and_all_their_films_without_series_not_adult_in_russian(mass_of_directors_and_their_films, argv[5]);

    return 0;
}