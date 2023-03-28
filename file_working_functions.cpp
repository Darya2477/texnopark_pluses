#include "./file_working_functions.h"

//ШАБЛОННАЯ ПРОЦЕДУРА ДЛЯ УДАЛЕНИЯ ЭЛЕМЕНТОВ ИЗ ВЕКТОРА
template <typename T>
void remove(std::vector<T>& v, int index) {
    v.erase(v.begin() + index);
};

//ПРОЦЕДУРА ДЛЯ НАХОЖДЕНИЯ ВСЕХ ЛЮДЕЙ ПО ДАННОМУ ИМЕНИ
void all_directors(std::string file_name, std::vector<director_and_his_films> &mass_of_results, std::string director_name){
    std::string director_number;
    std::string line;
    std::vector<std::string> empty_vector;
    std::ifstream name_basics(file_name);
    getline(name_basics,line);
     while (!name_basics.eof()){
        getline(name_basics,line,'\t');
        director_number=line;   //запоминаем номер введенного человека  
        getline(name_basics,line,'\t');
        if (director_name.compare(line)==0) mass_of_results.push_back({director_number,empty_vector});
        getline(name_basics,line);
    }
    name_basics.close();
}

//ПРОЦЕДУРА ДЛЯ ПРОВЕРКИ, ЯВЛЯЮТСЯ ЛИ ЭТИ ЛЮДИ ПРОДЮССЕРАМИ (ЕСЛИ ДА, ТО ЗАПОМНИМ ВСЕ КИНОКАРТИНЫ, КОТОРЫЕ ОНИ СПРОДЮССИРОВАЛИ)
void all_directors_and_all_their_films(std::string file_name, std::vector<director_and_his_films> &mass_of_results ){
    if (mass_of_results.size()==0){
     std::cout<<"В базе нет человека с таким именем."<<std::endl;
     exit(0);
    }
    else{
        std::string line;
        std::string current_film;
        std::vector<std::string> directors_vector;
        std::vector<std::string> director_films_vector;

        for (int i=0; i<(mass_of_results.size());i++){

            std::ifstream title_crew(file_name);
            getline(title_crew,line);

            while(!title_crew.eof()){
                getline(title_crew,line,'\t');
                current_film=line;      //запоминаем текущий фильм
                getline(title_crew,line,'\t');

                std::stringstream ss(line);
                std::string str;
                while(getline(ss,str,',')) directors_vector.push_back(str); //делаем вектор продюссеров из строки

                std::set<std::string> directors_set(directors_vector.begin(), directors_vector.end()); //делаем множество продюссеров из вектора

                if (directors_set.find((mass_of_results[i]).dir) != directors_set.end()) director_films_vector.push_back(current_film); //добавляем в вектор фильмы, которые отснял этот продюссер
                directors_vector.clear();
                getline(title_crew,line);
            }   
            if (director_films_vector.size()!=0) (mass_of_results[i]).films=director_films_vector;       //добавляем в массив структур продюссер-его фильмы запись
            director_films_vector.clear();
            title_crew.close();
        }
    }   
}

//ПРОЦЕДУРА ДЛЯ ИСКЛЮЧЕНИЯ ИЗ ОТСНЯТЫХ КИНОКАРТИН ЭПИЗОДЫ СЕРИАЛОВ/TV-ШОУ (ЧТОБЫ ОСТАЛИСЬ ТОЛЬКО ФИЛЬМЫ)

void all_directors_and_all_their_films_without_series(std::string file_name, std::vector<director_and_his_films> &mass_of_results){
    if (mass_of_results.size()==0){
       std::cout<<"Этот человек не является режиссером."<<std::endl;
       exit(0);
    }
    else{
        std::string line;
        std::string episode;
        std::string series;
        for (int i=0; i<(mass_of_results.size());i++){

            std::ifstream title_episode(file_name);
            getline(title_episode,line);

            while(!title_episode.eof()){
               int j=0;
               getline(title_episode,line,'\t');
               episode=line;       //запоминаем название эпизода                       
               getline(title_episode,line,'\t');
               series=line;                                      //запоминаем название сериала, из которого этот эпизод
               while(j<((mass_of_results[i]).films).size()){
                    if ((((mass_of_results[i]).films)[j]==episode) || (((mass_of_results[i]).films)[j]==series) ) remove((mass_of_results[i]).films,j);
                    else j++;
               }
               getline(title_episode,line);
            }
            title_episode.close();
        }

        int count=0;
        for (director_and_his_films i: (mass_of_results)){
            if (((i.films).size())==0) remove(mass_of_results, count);      //удаляем элементы из массива с директорами,если он снимал только сериалы
            else count++;
        }
    }

}

//ПРОЦЕДУРА ДЛЯ НАХОЖДЕНИЯ РУССКИХ НАЗВАНИЙ(ПРИ НАЛИЧИИ) ФИЛЬМОВ, КОТОРЫЕ ОТСНЯЛ ЭТОТ РЕЖИССЕР, ВОЗРАСТНОЕ ОГРАНИЧЕНИЕ КОТОРЫХ НЕ 18+

void all_directors_and_all_their_films_without_series_not_adult_in_russian(std::string file_name, std::vector<director_and_his_films> &mass_of_results){
    if (mass_of_results.size()==0){
        std::cout<<"Этот человек не снимал фильмы, он снимал сериалы."<<std::endl;
        exit(0);
    }
    else{
        std::string line;
        std::string current_film;
        std::string primary_title;
        std::string original_title;
        std::string age;

        for (int i=0; i<(mass_of_results.size()); i++){
            std::ifstream title_basics(file_name);
            getline(title_basics,line);

            while(!title_basics.eof()){
                int j=0;
                getline(title_basics,line,'\t');
                current_film=line;
                getline(title_basics,line,'\t');
                getline(title_basics,line,'\t'); 
                primary_title=line;
                getline(title_basics,line,'\t');
                original_title=line;
                getline(title_basics,line,'\t');
                age=line;
                while (j<((mass_of_results[i]).films).size()){
                    if (((mass_of_results[i]).films)[j]==current_film){
                        if (age=="1") remove((mass_of_results[i]).films,j);
                        else if (age=="0"){
                            
                            std::regex reg("[[:digit:][:space:][:alpha:]]+");  
                            std::vector <std::string> letters;
                            std::set<std::string> cirilliza{
                            "\xD0\x90","\xD0\x91","\xD0\x92","\xD0\x93","\xD0\x94","\xD0\x81","\xD0\x95","\xD0\x96","\xD0\x97","\xD0\x98","\xD0\x99","\xD0\x9A","\xD0\x9B","\xD0\x9C","\xD0\x9D","\xD0\x9E","\xD0\x9F",
                            "\xD0\xA0","\xD0\xA1","\xD0\xA2","\xD0\xA3","\xD0\xA4","\xD0\xA5","\xD0\xA6","\xD0\xA7","\xD0\xA8","\xD0\xA9","\xD0\xAA","\xD0\xAB","\xD0\xAC","\xD0\xAD","\xD0\xAE","\xD0\xAF",
                            "\xD0\xB0","\xD0\xB1","\xD0\xB2","\xD0\xB3","\xD0\xB4","\xD0\xB5","\xD1\x91","\xD0\xB6","\xD0\xB7","\xD0\xB8","\xD0\xB9","\xD0\xBA","\xD0\xBB","\xD0\xBC","\xD0\xBD","\xD0\xBE","\xD0\xBF",
                            "\xD1\x80","\xD1\x81","\xD1\x82","\xD1\x83","\xD1\x84","\xD1\x85","\xD1\x86","\xD1\x87","\xD1\x88","\xD1\x89","\xD1\x8A","\xD1\x8B","\xD1\x8C","\xD1\x8D","\xD1\x8E","\xD1\x8F"
                            };


                            std::string tmp_string = original_title;
                            tmp_string = std::regex_replace(tmp_string, reg, "");   //удаляем из названия пробелы, цифры и английские буквы 
                            while (tmp_string.size()!=0){
                                letters.push_back(tmp_string.substr(0,2));           //разбиваем оставшуюся строку на элементы по 2 байта, так как кириллица кодируется двумя байтами
                                tmp_string.erase(0,2);
                            }
                            for (int k=0; k<letters.size();k++){

                                if (cirilliza.find(letters[k]) != cirilliza.end()) {
                                    ((mass_of_results[i]).films)[j]=original_title;
                                    break;
                                };
                            }
                            if (((mass_of_results[i]).films)[j]!=original_title) ((mass_of_results[i]).films)[j]=primary_title;

                            j++;
                        }
                    }
                    else j++;
                }

                getline(title_basics,line);
            }
            title_basics.close();
        }

        int count=0;
        for (director_and_his_films i: (mass_of_results)){
            if (((i.films).size())==0) remove(mass_of_results, count);      //удаляем элементы из массива с директорами,если он снимал только сериалы
            else count++;
        }
    }
}

//ИТОГОВЫЙ ВЫВОД РЕЗУЛЬТАТОВ

void print_all_directors_and_all_their_films_without_series_not_adult_in_russian(std::vector<director_and_his_films> &mass_of_results, std::string director_name){
    if (mass_of_results.size()==0){
        std::cout<<"Среди фильмов этого режиссера нет фильмов с ограничением по возрасту меньше 18+."<<std::endl;
        exit(0);
    }    
    else{
        for (int i=0;i<(mass_of_results.size()); i++){
            std::cout<<"Фильмы, которые снял(a) "<<director_name<<": "<<std::endl;
            for (int j=0;j<(((mass_of_results[i]).films).size());j++){
                std::cout<<j+1<<") "<<((mass_of_results[i]).films)[j]<<std::endl;
            }
        }
    }
}