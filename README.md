# ato
Airplane Tickets Office


1. Введение: 

Разработанный программный продукт предназначен для хранения и обработки данных в транспортной сфере: он создает базу данных о самолетах и авиарейсах между городами и имеет следующий функционал: хранение, добавление, удаление и изменение информации о полетах; подбор маршрута из одного города в другой c наименьшей стоимостью; подбор маршрута, при котором меньше всего времени тратится на пересадку.
Программа разработана под операционную систему Windows. Несмотря на то, что размер необходимой памяти зависит от количества хранимой в базе информации, для ее функционирования не требуется больших объемов памяти, так как одна единица информации (запись) в базе данных занимает 576 байт (при внесенных 10 авиарейсах). С большим запасом можно поставить ограничения в 100 Мб оперативной памяти и дискового пространства.

2. Задание на курсовое проектирование:

Задание 10. База данных "Авиакасса" 
• Пополнение базы. 
• Редактирование базы. 
• Удаление записей. 
• Подбор маршрута с наименьшим временем ожидания при пересадке. 
• Подбор маршрута с наименьшей стоимостью.

3. Технические характеристики и ограничения применения

Входная информация от пользователя ожидается только в текстовом формате. Выбор в меню организован с помощью списка чисел, одно из которых нужно ввести, чтобы привести в действие соответствующий функционал. В этом разделе программа обрабатывает возможные ошибки ввода, такие как символы, недопустимые числа. При ошибке ввода будет предложено снова сделать выбор. 
При заполнении базы данных пользователь должен следовать инструкциям, которые указывают на формат ввода. Программа позволяет добавлять сразу несколько записей в базу, например, для добавления записи о самолете и его пункте отправления необходимо перечислять наименования городов через пробел, табуляцию или символ перехода на новую строку. Несоответствие введенных данных не должно вызвать ошибку (одно исключение: ввод стоимости, которая обязана быть целым числом), но приведет к бессмысленному отображению информации. Важное требование: ввод должен завершаться признаком конца файла EOF (Cntr + Z), что также указыввается в инструкциях во время работы программы.

4. Структура данных
Использованная структура данных представляет собой динамический массив указателей на структуру, содержащую информацию о пункте отправления самолета, количестве авиарейсов в разные города. Также эта структура содержит вложенный массив указателей на другую структуру, в которой хранится имя пункта назначения, время отправления и прибытия, а также стоимость авиарейса.
Таким образом, программа использует модель графа (каждое наименование – его узел, каждый указатель в массиве во вложенной структуре – его ребро), которая необходима для реализации подбора маршрутов.
Размер наименований определяется константой и равен 40 байтам, следовательно, предполагается, что название города не превышает 40 символов.
Оба массива указателей динамические, память под массив перераспределяется, тем самым обеспечивается увеличение его порциями: при переполнении добавляется память под 5 указателей, число 5 определено константой.

5. Схема алгоритма
Для решения задачи были разработаны алгоритмы поиска через перебор массива указателей и проверки структур, на которые они указывают, по содержимому; записи в файл и чтения из файла, в котором сохраняются все данные базы в одинаковых непустых блоках при освобождении памяти во время завершения работы программы. 
Основная задача состояла в реализации подбора маршрутов, и для этого использовались известные алгоритмы Дейкстра и поиска в ширину. 
Алгоритм Дейкстра позволяет во взвешенном графе найти путь от одного узла до другого с наименьшим суммарным весом. Схема алгоритма изображена на рисунке 1.
Общий вид алгоритма:
1.	Найти узел с наименьшей стоимостью
2.	Обновить стоимости его соседних узлов
3.	Повторять пункт 1 и 2, пока не будут обработаны все узлы графа
4.	Вычислить итоговый путь
Алгоритм имеет ограничения, которые могут отразиться на корректности работы программы:
1.	алгоритм работает только с направленными ациклическими графами
2.	алгоритм не работает с отрицательным весом
Если в базе данных какая-нибудь из стоимостей авиарейсов будет отрицательной или, например, в ней будут записаны полеты из A в B и из B в A одновременно, то алгоритм не сработает, а поведение программы будет неопределенным. 
Алгоритм поиска в ширину находит путь из узла в узел с наименьшим количеством других узлов между ними, а также позволяет узнать, существует ли вообще путь между двумя узлами. Если формализовать задачу, считая, что время ожидания при пересадках всегда одинаковое, то наименьшее время ожидания будет при наименьшем количестве пересадок, поэтому этот алгоритм подходит для подбора такого маршрута. 
Схема алгоритма изображена на рисунке 2.
Общий вид алгоритма:
1.	Создать очередь, поместить в нее пункт отправления
2.	Извлечь элемент из очереди
3.	Проверить элемент на пункт назначения
4.	Если пункт назначения, завершить, иначе добавить все соседние элементы в очередь
5.	Повторять пункты 2–4, пока очередь не пуста
6.	Если очередь пуста, маршрута не существует
В отличии от алгоритма Дейкстра алгоритм поиска в ширину не имеет ограничений по видам графов, на которых он реализуется.

6. Инструкция по применению
Пользователю необходимо запустить испольняемый модуль с именем ato.exe, затем выбирать пункты меню, вводя число, отображенное напротив интересующего его пункта. Редактирование базы проходит в соответствии с выводящимися на экран консоли инструкциями, при подборе маршрута пользователю также нужно следовать инструкциям на экране: ввести наименования городов. Ввод при редактировании должен соответствовать указанному формату. Выход с сохранением возможен только в главном меню, во вложенных меню выход из программы не предусматривает сохранение всех изменений в файле.

7. Спецификация программы

Компилируемые файлы
header.h	Заголовочный файл содержит директивы препроцессора, объявления функций, внешних переменных, структур
select.h	Включает в себя объявления структур и функций, необходимых для реализации алгоритмов подбора маршрута
ato.c	Основной файл с функцией main()
start.c	Чтение файла и главное меню
manage.c	Меню редактирования базы данных
add_rec.c	Добавление данных в базу
chg_rec.c	Изменение данных в базе
del_rec.c 	Удаление данных в базе
select.c	Меню подбора маршрута
select_cost.c	Реализация алгоритма Дейкстра, подбор по наименьшей стоимости
select_time.c 	Реализация алгоритма поиска в ширину, подбор по наименьшему времени ожидания при пересадке
select_func.c	Содержит вспомогательные функции для реализации алгоритмов подбора маршрута
end.c	Запись в файл и освобождение памяти

10. Заключение
Разработанный программный продукт реализует простую базу данных, при учитывании ограничений корректно обрабатывает данные, решает поставленные задачи о нахождении маршрутов между городами, представляя данные в памяти компьютера как абстрактную модель графа.



##1. Introduction:

The developed software product is designed for storing and processing data in the transport sector: it creates a database of aircraft and flights between cities and has the following functionality: storing, adding, deleting and changing information about flights; selecting a route from one city to another with the lowest cost; selecting a route that takes the least time to transfer.
The program is designed for the Windows operating system. Despite the fact that the size of the required memory depends on the amount of information stored in the database, it does not require large amounts of memory for its operation, since one unit of information (record) in the database occupies 576 bytes (with 10 flights entered). With a large margin, you can set limits of 100 MB of RAM and disk space.

##2. Course design assignment:

* Replenishment of the database
* Edit the database
* Delete records
* Selection of the route with the shortest waiting time for a transfer
* Selection of the route with the lowest cost

##3. Technical specifications and application limitations

Input information from the user is expected only in text format. The selection in the menu is organized using a list of numbers, one of which must be entered to activate the corresponding functionality. In this section, the program handles possible input errors, such as characters, invalid numbers. If you enter an error, you will be prompted to make a selection again.
When filling in the database, the user must follow the instructions that indicate the input format. The program allows you to add several entries to the database at once, for example, to add a record about an airplane and its departure point, you need to list the names of cities separated by a space, tab, or a new line character. A mismatch of the entered data should not cause an error (one exception: entering a value that must be an integer), but will result in a meaningless display of the information. Important requirement: The input must end with the EOF file (Cntr + Z), which is also indicated in the instructions while the program is running.

##4. Data structure

The data structure used is a dynamic array of pointers to the structure containing information about the departure point of the aircraft, the number of flights to different cities. This structure also contains a nested array of pointers to another structure, which stores the name of the destination, the time of departure and arrival, as well as the cost of the flight.
Thus, the program uses a graph model (each name is its node, each pointer in the array in the nested structure is its edge), which is necessary for the implementation of route selection.
The size of the names is determined by a constant and is equal to 40 bytes, therefore, it is assumed that the name of the city does not exceed 40 characters.
Both arrays of pointers are dynamic, the memory for the array is reallocated, thereby increasing it in portions: when overflowing, memory for 5 pointers is added, the number 5 is defined by a constant.

##5. Algorithm diagram

To solve the problem, algorithms were developed for searching through an array of pointers and checking the structures they point to by their contents; writing to a file and reading from a file in which all the database data is stored in the same non-empty blocks when memory is freed during the program shutdown.
The main task was to implement route selection, and for this purpose, the well-known Dijkstra and breadth-first search algorithms were used.
Dijkstra's algorithm allows you to find the path from one node to another with the lowest total weight in a weighted graph.
General view of the algorithm:
1. Find the node with the lowest cost
2. Update the values of its neighboring nodes
3. Repeat steps 1 and 2 until all the nodes of the graph are processed
4. Calculate the final path
The algorithm has limitations that may affect the correctness of the program:
1. The algorithm works only with directed acyclic graphs
2. The algorithm does not work with negative weight
If any of the flight costs are negative in the database, or, for example, flights from A to B and from B to A are recorded in it at the same time, the algorithm will not work, and the behavior of the program will be undefined.
The breadth-first search algorithm finds the path from node to node with the fewest other nodes between them, and also lets you know if there is even a path between two nodes. If we formalize the problem by assuming that the waiting time for transfers is always the same, then the least waiting time will be for the least number of transfers, so this algorithm is suitable for selecting such a route.
General view of the algorithm:
1. Create a queue, place the departure point in it
2. Remove an item from the queue
3. Check the item for the destination
4. If the destination is complete, otherwise add all adjacent items to the queue
5. Repeat steps 2-4 until the queue is empty
6. If the queue is empty, the route does not exist
Unlike Dijkstra's algorithm, the breadth-first search algorithm has no restrictions on the types of graphs on which it is implemented.

##6. Instructions for use

The user needs to run the module being used with the name ato.exe, then select the menu items by entering the number displayed next to the item of interest. The database is edited in accordance with the instructions displayed on the console screen. When selecting a route, the user also needs to follow the instructions on the screen: enter the names of cities. The input during editing must match the specified format. Exit with saving is possible only in the main menu, in the nested menus, exit from the program does not provide for saving all changes in the file.

##7. Specification of the program

Compiled files
header.h 
- The header file contains preprocessor directives, function declarations, external variables, and select structures. h Includes declarations of structures and functions necessary for implementing the ato route selection algorithms
ato.c 
- The main file with the main()
start.c
- Reading the file and the main menu
manage.c 
- Database editing menu
add_rec.c 
- Adding data to the database
chg_rec.c 
- Changing data in the database
del_rec.c 
- Deleting data in the database
select.c 
- Route selection menu
select_cost.c 
- Implementation of the Dijkstra algorithm, selection at the lowest cost
select_time.c 
- Implementation of the algorithm for breadth-first search, selection by the shortest waiting time when transferring
select_func.c 
- Contains auxiliary functions for implementing the algorithms for route selection
end.c 
- Writing to a file and freeing memory

##8. Conclusion

The developed software product implements a simple database, takes into account the restrictions, correctly processes the data, solves the tasks of finding routes between cities, presenting the data in the computer memory as an abstract graph model.
