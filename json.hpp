#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <regex>

class json{
    public:
        json();
        json(std::string f_name);
        void Parse(std::string f_name);
    private:
        std::map<std::string, std::string> id_crypto_dict;
};

json::json(std::string f_name){
    // открытие файла
    std::ifstream in(f_name);
    // проверка открытия
    if(in.is_open()){
        // считывание информации из файла и добавление всего в переменную
        std::string text_from_file, line;
        while (in >> line)
        {
            text_from_file +=line;
        }
        // отладочная информация
        std::cout << text_from_file <<"\n";
        
        // удаление лишней информации
        text_from_file.erase(text_from_file.find('{'), 1);
        text_from_file.erase(text_from_file.find('}'), 1);

        std::regex re("\"");
        text_from_file = std::regex_replace(text_from_file, re, "");

        std::regex rep(",");
        text_from_file = std::regex_replace(text_from_file, rep, " ");

        // проверка на правильность обработки
        std::cout << text_from_file << "\n";

        char text_splited[text_from_file.length()];

        strcpy(text_splited, text_from_file.c_str());

        // создание словоря со всеми id и названием
        // переменные которые используються для создания словаря
        std::string key;
        std::string value;
        bool flag = 1;
        for(int i = 0; i < text_from_file.length(); i++){
            // проверка на пробел
            if (text_splited[i] != ' '){
                // проверка на изменение значения с ключа на значение 
                if (text_splited[i] == ':'){
                    flag = !flag;
                    continue;
                }
                if (flag){
                    key+=text_splited[i];
                }   else    {
                    value+=text_splited[i];
                }
            } else {
                // добавление данных в словарь
                id_crypto_dict[key] = value;
                // отладочная информация
                std::cout << id_crypto_dict[key]<<std::endl;


                // обнуление пере новым цыклом
                key = "";
                value = "";
                flag = !flag;
            }
        }



    }
    in.close();
}
void Parse(std::string f_nmae){

}