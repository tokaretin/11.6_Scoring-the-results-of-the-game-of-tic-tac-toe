﻿/** /*Задание 4. Оценка результатов игры в крестики-нолики
Что нужно сделать
Петя и Вася играли в крестики-нолики и не стёрли результаты 
своей игры. Теперь перед вами табличка 3 × 3, которая осталась 
после их поединка. Вы хотите понять, выиграл ли кто-то из них или 
они не доиграли.
На вход программе даётся три строки, кодирующие верхнюю, среднюю 
и нижнюю строчки игрового поля. Крестик обозначается символом X 
(английская заглавная буква X), нолик — символом O (заглавная 
английская буква O), пустая клетка — точкой.
Если ввод некорректен, то есть такая таблица не могла получиться 
в ходе настоящей игры, то надо написать в ответ слово Incorrect.
Если таблица корректна и выиграли крестики, то нужно вывести в 
ответ слова Petya won, если нолики — Vanya won, иначе (то есть 
они не доиграли или сыграли вничью) надо написать Nobody.
Примеры
X.. 
OXO 
OOO 
Ответ: Incorrect (потому что ноликов в конце игры не может 
быть больше, чем крестиков).
X.. 
.X. 
OO. 
Ответ: Nobody (потому что они не доиграли).
XXO 
OOX 
XOX 
Ответ: Nobody (потому что это ничья).
XO. 
XO. 
X.O 
Ответ: Incorrect (крестики уже победили, и ноликов не может 
быть столько же).
OX. 
XOX 
X.O 
Ответ: Incorrect (потому что нолики выиграли за три хода, и 
на поле за это время не могло успеть появиться четыре крестика).
..X 
OX. 
X.O 
Ответ: Petya won.
0.. 
... 
... 
Ответ: Incorrect (потому что допускаются только символы X, O и 
точка, а цифра 0 не является допустимым символом).
Рекомендации
Активно используйте оператор индексации строки str[i], но 
помните, что индексы начинаются с нуля, а не с единицы.
Чтобы обращаться к элементам игрового поля, стоит написать 
отдельную функцию получения элемента поля по его координатам (x, y). 
В таком случае часть алгоритмов поиска победителя можно обобщить.
Функции проверки поля на корректность можно отделить от функций и 
алгоритмов проверки победителя.
При достаточной модульности функций некоторые операции можно 
реализовать через уже существующие процедуры. К примеру, если 
уже есть проверка победителя в строке и имеется функция получения
колонки по индексу, то функцию поиска победителя в колонке можно 
реализовать через обе процедуры.
Проход по диагонали поля можно осуществить в цикле, используя 
счётчик цикла в качестве обоих координат элемента. Для второй 
диагонали нужно обратить одну из координат (2 − x или 2 − y).
Общие условия некорректности поля таковы:
выявлено несколько победителей одновременно;
нолики победили, а крестиков больше, чем ноликов;
крестики победили, а ноликов столько же или больше;
нолики и крестики победили несколько раз;
на поле есть невалидные символы.
Для упрощения лучше создать отдельные функции для проверки 
победителя в строке или столбце, которые на вход принимают 
строку, а на выходе выдают символ победителя. То есть ‘X’, ‘O’ 
или ‘.’.*/
#include <iostream>
#include <string>

using namespace std;

const int fieldSize = 9;

string initial();
bool isCorrectStringLength(string str);
bool isCorrectDataType(string str);
int checkCount(string str, char ch);
bool checkCol(string str, char ch);
bool checkRow(string str, char ch);
bool checkDiag(string str, char ch);
bool isWin(string str, char ch);

/*Эта функция main() представляет основную логику программы. 
Она сначала вызывает функцию initial(), которая запрашивает 
у пользователя 3 строки ввода и объединяет их в одну строку, 
представляющую игровое поле крестики-нолики. Затем программа 
проверяет, соответствует ли длина введенной строки ожидаемой 
длине поля (9 символов) с помощью функции isCorrectStringLength(). 
Если это так, программа проверяет, что каждый символ в строке 
является допустимым значением поля (X, O или .) с помощью функции
isCorrectDataType(). Если обе проверки проходят успешно, программа 
продолжает проверку, может ли данное поле представлять корректную 
конфигурацию игры в крестики-нолики с помощью следующих проверок:

Проверка, что количество символов X и O в поле различается не 
более чем на 1 с помощью функций checkCount() и сравнения.

Проверка, что только один игрок может быть победителем с помощью 
функции isWin() и проверок выигрышных комбинаций.

Если все проверки проходят успешно, программа определяет победителя, 
если такой есть, и выводит соответствующее сообщение. Если поле не 
представляет корректную конфигурацию игры в крестики-нолики, 
программа выводит сообщение "Incorrect". Если поле не является 
корректной конфигурацией игры, то есть не выполняется ни одна из 
двух проверок (1) или (2), программа также выводит сообщение 
"Incorrect".*/
int main() {
    string field;
    field = initial();
    if (isCorrectStringLength(field) && isCorrectDataType(field))
    {
        int countX = checkCount(field, 'X');
        int countO = checkCount(field, 'O');

        if ((countX - countO == 0) || (countX - countO == 1))
        {
            bool winX = isWin(field, 'X');
            bool winO = isWin(field, 'O');

            if ((winX && winO) ||
                (winO && (countX - countO == 1)) ||
                (winX && (countX - countO == 0)))
                cout << "Incorrect" << '\n';
            else
                if (!winX && !winO)
                    cout << "Nobody" << '\n';
                else
                    cout << (winX ? "Kate won" : "Joy won") << '\n';
        }
        else
            cout << "Incorrect" << '\n';
    }
    else
        cout << "Incorrect" << '\n';
}

/*Данная функция initial() запрашивает у пользователя 
три ввода, каждый из которых представляет собой строку 
из трех символов 'X', 'O' или '.', которые представляют 
собой игровое поле для игры в крестики-нолики. После каждого 
ввода пользователь должен нажать клавишу "Enter".

Далее, каждая из трех введенных строк конкатенируется в
одну строку field, которая является результирующим полем. 
В конце функция возвращает эту строку field.

Вот как пример взаимодействия с пользователем может 
выглядеть в ходе выполнения данной функции:

mathematica
Copy code
Input 1 row (X, O, '.'): X..
Input 2 row (X, O, '.'): .O.
Input 3 row (X, O, '.'): ..X

После этого функция возвращает строку "X...O...X", 
которая представляет собой полученное игровое поле.*/
string initial()
{
    string field;
    for (int i = 1; i < 4; i++)
    {
        cout << "Input " << i << " row (X, O, '.'): ";
        string temp;
        cin >> temp;
        field += temp;
    }
    return field;
}

/*Функция isCorrectStringLength принимает строку str в 
качестве аргумента и возвращает true, если длина этой 
строки равна fieldSize, который объявлен в начале программы 
и имеет значение 9. Иначе функция возвращает false.

Таким образом, эта функция используется для проверки 
правильности длины строки str, которая содержит игровое 
поле крестики-нолики. Если длина строки не равна 9, то 
поле задано некорректно и игра не может быть запущена.*/
bool isCorrectStringLength(string str)
{
    return (str.length() == fieldSize);
}

/*Функция isCorrectDataType проверяет, соответствуют ли 
символы в строке str требованиям игрового поля к типу 
символов. В данном случае игровое поле должно содержать 
только символы 'X', 'O' или '.'.

Функция перебирает символы в строке str с помощью цикла 
for. Если находит символ, который не соответствует условию, 
то сразу возвращает false, означающее, что строка не 
удовлетворяет требованиям. Если же все символы корректны, 
то функция возвращает true.

Таким образом, эта функция используется для проверки 
корректности введенного пользователем поля. Если поле 
содержит недопустимые символы, программа выведет сообщение 
об ошибке и завершится.*/
bool isCorrectDataType(string str)
{
    for (int i = 0; i < fieldSize; i++)
        if (str[i] != 'X' && str[i] != 'O' && str[i] != '.')
            return false;
    return true;
}

/*Функция checkCount принимает два аргумента: строку 
str и символ ch, и возвращает количество вхождений символа 
ch в строке str.

Она используется в программе для подсчета количества фишек 
'X' и 'O' на игровом поле.

Внутри функции объявляется переменная count, которая используется 
для подсчета вхождений символа ch. Затем выполняется цикл по 
всем символам строки str. Если очередной символ равен ch, то 
увеличивается счетчик count.

По окончании цикла функция возвращает значение счетчика count. 
Если str не содержит символа ch, то возвращается 0.*/
int checkCount(string str, char ch)
{
    int count = 0;
    for (int i = 0; i < fieldSize; i++)
        if (str[i] == ch)
            count++;
    return count;
}

/*Эта функция проверяет, есть ли в столбце игрового поля 
символ ch (X или O) на всех трех позициях столбца.

Функция принимает два аргумента: str - строку, представляющую 
текущее состояние игрового поля, и ch - символ, который нужно 
найти в столбце.

Далее, функция проходит по каждому столбцу игрового поля и 
проверяет, есть ли в столбце три символа ch подряд. Если такой 
столбец найден, функция возвращает true, иначе - false.

Для этого используется цикл for, который проходит по индексам 
0, 1 и 2 (т.е. индексам первого столбца), затем 3, 4 и 5 (индексы 
второго столбца) и 6, 7 и 8 (индексы третьего столбца).

Для проверки, что в столбце есть три символа ch подряд, функция 
проверяет, что значение str[i] равно ch, что значение str[i + 3] 
равно ch, и что значение str[i + 6] равно ch. Если все три условия 
выполнены, то функция возвращает true, иначе - false.

Например, если передать строку "XOXOX.O..", а вторым аргументом 
символ 'X', то функция вернет true, так как первый и третий столбцы 
содержат три символа 'X' подряд. Если же вторым аргументом передать 
символ 'O', то функция вернет false, так как ни в одном столбце нет 
трех символов 'O' подряд.*/
bool checkCol(string str, char ch)
{
    for (int i = 0; i < 3; i++)
        if ((str[i] == str[i + 3]) && 
            (str[i + 3] == str[i + 6]) && str[i] == ch)
            return true;
    return false;
}

/*Эта функция проверяет, содержит ли заданная строка символы 
в одном и том же ряду (горизонтали).

Алгоритм работы функции:

Функция перебирает 3 ряда (i = 0, 1, 2) в строке, каждый 
из которых состоит из трех символов (i + 2 * i, (i + 1) + 2 * i, 
(i + 2) + 2 * i) в формате "012", "345", "678".
Затем функция проверяет, являются ли символы в ряду одинаковыми 
и равны заданному символу 'ch'.
Если символы в ряду одинаковые и равны заданному символу 'ch', 
функция возвращает значение true, иначе она продолжает перебирать ряды.
Если функция переберет все ряды и не найдет ни одного ряда с 
одинаковыми символами, она возвращает значение false.
Например, если вызвать функцию checkRow("XOXOOX.X.", 'O'), она 
вернет true, потому что символы 'O' в строке находятся в одном и 
том же ряду.*/
bool checkRow(string str, char ch)
{
    for (int i = 0; i < 3; i++)
        if (((str[i + 2 * i]) == str[(i + 1) + 2 * i]) &&
            ((str[(i + 1) + 2 * i]) == str[(i + 2) + 2 * i]) &&
            str[i + 2 * i] == ch)
            return true;
    return false;
}

/*Эта функция проверяет, есть ли на диагоналях 
крестики или нолики. Она начинает с проверки главной 
диагонали (от левого верхнего угла до правого нижнего), 
проверяя, совпадает ли значение в ячейках 0, 4 и 8 (это 
главная диагональ) и равно ли оно переданному символу ch. 
Если это так, функция возвращает true. Затем функция проверяет 
побочную диагональ (от правого верхнего угла до левого нижнего), 
проверяя, совпадает ли значение в ячейках 2, 4 и 6 (это 
побочная диагональ) и равно ли оно переданному символу ch. 
Если это так, функция возвращает true. Если ни одна из 
диагоналей не содержит переданный символ ch, функция возвращает false.*/
bool checkDiag(string str, char ch)
{
    if ((((str[0] == str[4]) && (str[4] == str[8])) ||
        ((str[2] == str[4]) && (str[4] == str[6]))) &&
        (str[4] == ch))
        return true;
    return false;
}

/*Эта функция проверяет, является ли заданный символ 
(X или O) победным символом в строке, переданной в качестве 
аргумента. Функция использует три другие функции, checkCol, 
checkRow и checkDiag, чтобы проверить, есть ли победные символы 
в столбцах, строках или диагоналях поля.

Если хотя бы одна из этих функций возвращает true, то функция 
isWin также вернет true, что означает, что заданный символ 
является победным символом в переданной строке. Если все три 
функции возвращают false, то функция isWin также вернет false, 
что означает, что заданный символ не является победным символом 
в переданной строке.*/
bool isWin(string str, char ch)
{
    return (checkCol(str, ch) ||
        checkRow(str, ch) ||
        checkDiag(str, ch));
}

/*Этот код - это программа, которая проверяет, кто
победил в игре крестики-нолики и выводит результат 
в консоль. Он использует несколько функций, чтобы 
проверить поле игры на соответствие правилам и определить 
победителя.

Вот более подробное описание каждой функции:

initial() - функция запрашивает у пользователя ввод 
трех строк (3 рядов в игре крестики-нолики) и возвращает 
их в виде строки, объединенной в одну.

isCorrectStringLength(std::string str) - функция проверяет, 
что длина строки соответствует ожидаемой (равной 9 символам).

isCorrectDataType(std::string str) - функция проверяет, 
что все символы в строке являются допустимыми (это может 
быть X, O или точка).

checkCount(std::string str, char ch) - функция возвращает 
количество символов ch (X или O) в строке.

checkCol(std::string str, char ch) - функция проверяет, 
есть ли выигрышная комбинация символов ch в одном из столбцов 
игрового поля.

checkRow(std::string str, char ch) - функция проверяет, 
есть ли выигрышная комбинация символов ch в одной из строк 
игрового поля.

checkDiag(std::string str, char ch) - функция проверяет, 
есть ли выигрышная комбинация символов ch в одной из диагоналей 
игрового поля.

isWin(std::string str, char ch) - функция проверяет, выиграл 
ли символ ch.

В main() функции сначала вызываются initial(), 
isCorrectStringLength(), isCorrectDataType(), 
checkCount(), isWin() и проверяется, была ли 
успешна каждая проверка. Если все проверки были 
пройдены успешно, программа определяет победителя 
и выводит результат в консоль. Если какая-то из проверок 
не прошла, программа выводит "Incorrect".




*/