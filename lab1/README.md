# Лабораторная работа №1.
## Обработка деревьев с помощью динамических структур.
## Задача:
Реализовать упорядоченное двоичное дерево со следующими функциями:
1. Добавление нового узла согласно порядку.
2. Вывод дерева на экран с учётом глубины каждого узла (регулируется количестовм отступов), каждый узел на отдельной строке.
3. Удаление узла с сохранением порядка, также корректное освобождение памяти.
4. Вычисление глубины двоичного дерева.
## Решение:
реализована структура узла с левым и правым ребёнком. Левый потомок всегда меньше узла, а правый больше. При удалении узла, имеющего двух потомков, происходит балансировка путём поиска минимального элемента в правом поддереве и замена его на удаляемый. Вывод узлов дерева реализован с помощью единичных отступов. Вычисление глубины дерева происходит рекурсивно.
### Запуск программы:
Чтобы запустить встроенный CLI, используйте данную команду в папке lab1. При запуске CLI автоматически производится тестирование.
```terminaloutput
make main
```
Отдельный запуск тестов
```terminaloutput
make test
```
### Пример работы
```terminaloutput
Hello, It is binary tree!
You have this actions to build your tree and check its depth:
1. Add new node, at first you don't have nodes in your tree
2. print your tree on screen
3. delete node with data
4. depth of your tree
5. exit
Your choice: 1
Enter data:5
Your choice: 1
Enter data:4
Your choice: 1
Enter data:6
Your choice: 1
Enter data:3
Your choice: 1
Enter data:6
Your choice: 2
5
 4
  3
 6

Your choice: 3
Enter data: 6
Your choice: 2
5
 4
  3

Your choice: 4
3
Your choice: 1
Enter data:6
Your choice: 4
3
Your choice: 1
Enter data:8
Your choice: 4
3
Your choice: 1
Enter data:10
Your choice: 1
Enter data:11
Your choice: 4
5
Your choice: 5
```

## Вывод
Создали упорядоченное бинарное дерево с функциями добавления, удаления элементов, вывода на экран и подсчёта глубины с помощью языка Си.