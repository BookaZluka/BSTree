#include "bstree.h"
using namespace std;
using namespace BSTree;

auto Menu (Tree *&) -> void;

int main (int argc, char * argv [])
{
    Tree *tree = new Tree;
    int* array= new int [argc-1];
    for (int i=1 ; i< argc; i++)
    {
        array[i-1]= atoi(argv[i]);
    };
    for (int i=0; i<argc-1; i++) {
        for (int j=i+1; j<argc-1; j++) {
            if (array[i]==array[j]) {
                for (int k=j; j< argc-1; j++) array[j]= array[j+1];
                argc--;
            };
        }
    };
    for (int i=0; i<argc-1; i++) {
        tree->Insert(array[i]);
    }
    delete []array;
    Menu (tree);
    delete tree;
}

auto Menu (Tree *& tree)->void {
    string Exit;
    char CharChoise;
    int Choise;
    while ((Exit != "y") && (Exit != "yes") && (Exit != "Y") && (Exit != "Yes") &&
           (Exit != "YES")) {
        cout << "Выберите одну из операций:" << endl
             << "1. Вывести дерево на экран" << endl
             << "2. Вывести список узлов дерева" << endl
             << "3. Добавить узел в дерево" << endl
             << "4. Удалить узел из дерева" << endl
             << "5. Сохранить дерево в файл" << endl
             << "6. Загрузить дерево из файла" << endl
             << "7. Проверить наличие узла" << endl
             << "8. Завершить работу программы" << endl;
        cin >> Choise;
        switch (Choise) {
            case 1:
                tree->Print();
                break;
            case 2:
                if (!tree->Empty()) {
                    cout << "a. Прямой обход" << endl;
                    cout << "b. Поперечный обход" << endl;
                    cout << "c. Обратный обход" << endl;
                    cin>> CharChoise;
                    switch (CharChoise) {
                        case 'a':
                            tree->Print(traversal_order::pre);
                            cout<<endl;
                            break;
                        case 'b':
                            tree->Print(traversal_order::in);
                            cout<<endl;
                            break;
                        case 'c':
                            tree->Print(traversal_order::post);
                            cout<<endl;
                            break;
                    }
                    break;
                }
                else cout << "Дерево не содержит элементов!"<< endl;
                break;
            case 3:
                cout << "Введите значение для нового узла:" << endl;
                int Value;
                cin.clear();
                cin.get();
                cin>> Value;
                if (cin)
                    tree->Add(Value);
                else cerr<< "Ошибка!" << endl;
                break;
            case 4:
                if (!tree->Empty()) {
                    cout << "Введите значение удаляемого узла:" << endl;
                    int ValueF;
                    cin.clear();
                    cin.get();
                    cin>> ValueF;
                    if (cin) {
                        if (tree->Remove(ValueF))
                            std::cout<< "Узел был успешно удален"<<std::endl;
                        else std::cout<< "Узел не найден"<<std::endl;
                    }
                    else
                                                                                       cerr<<"Ошибка!"<<endl;
                }
                else cout << "Дерево не содержит элементов"<< endl;
                break;
            case 5:
                if (!tree->Empty()) {
                    string FileName;
                    cout << "Введите имя файла:" << endl;
                    cin >> FileName;
                    if (tree->Save(FileName)) cout << "Дерево было успешно сохранено" << endl;
                }
                else cout << "Дерево не содержит элементов" << endl;
                break;
            case 6:
                if (tree->Empty()) {
                    string FileName;
                    cout << "Введите имя файла:" << endl;
                    cin >> FileName;
                    if (tree->Load(FileName)) cout << "Дерево было успешно загружено" << endl;
                    else cerr << "Файл не найден!" << endl;
                }
                else cerr << "Дерево уже существует!" << endl;
                break;
            case 7:
                if (!tree->Empty()) {
                    int value;
                    cout<< "Введите значение для поиска:" << endl;
                    cin>> value;
                    if(tree->Exists(value)) cout<< "Такой узел есть в дереве"<< endl;
                    else cout<< "Узел не найден!"<<endl;
                }
                else cerr<< "Дерево не содержит элементов!"<<endl;
                break;
            case 8:
                cout << "Вы хотите выйти из программы? ( yes/no )" << endl;
                cin >> Exit;
                if ((Exit == "y") || (Exit == "yes") || (Exit == "Y") ||
                    (Exit == "Yes") || (Exit == "YES"))
                    cout << "До свидания!"<<endl;
                break;
        }
    }
}
