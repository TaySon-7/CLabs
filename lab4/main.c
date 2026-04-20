#include "func.c"


int main(int argc, char *argv[]) {
    if (argc == 3) {
        printf("Сейчас будут выполенны команды из файла %s и записаны в %s\n", argv[1], argv[2]);
        if (!freopen(argv[1], "r", stdin)) {
            printf("Ошибка открытия файла\n");
        }
        if (!freopen(argv[2], "w", stdout)) {
            printf("Ошибка открытия файла\n");
        }
    }
    else {
        printf("Запущен CLI с AVL-деревом\n");
        printf("Достпуны следующие команды:\n");
        printf("1. Добавление узла к дереву по ключу.\n");
        printf("2. Удаление узла из дерева по ключу.\n");
        printf("3. Печать дерева.\n");
        printf("4. Поиск значения элемента по заданному ключу.\n");
        printf("5. Выход.\n");
    }
    char* line = NULL;;
    size_t len = 0;
    Node* root = NULL;
    char command = '5';
    double data = 0;
    int stage = 0;
    char* endptr;
    while (1) {
        size_t symbols = getline(&line, &len, stdin);
        if (symbols == -1) {
            printf("Работа завершена\n");
            break;
        }
        stage = 1;
        int index = 0;
        char* key = (char*)malloc(sizeof(char) * 7);
        for (int i = 0; i < symbols; i++) {
            if (line[i] == '\n') {
                break;
            }
            if (stage == 1 && line[i] != ' ') {
                command = line[i];
                stage = 2;
                continue;
            }
            if (line[i] == ' ' && stage == 2) {
                index = i + 1;
                continue;
            }
            if (line[i] != ' ' && stage == 2) stage = 3;
            if (stage == 3 && line[i] != ' ') {
                key[i - index] = line[i];
                continue;
            }
            if (stage == 3 && line[i] == ' ') {
                key[i - index] = '\0';
                stage = 4;
                continue;
            }
            if (stage == 4 && line[i] != ' ') {
                char* double_line = &line[i];
                data = strtod(double_line, &endptr);
                if (endptr == double_line) {
                    printf("Ошибка чтения вещественного числа\n");
                }
                break;
            }
        }
        if (command == '5') {
            break;
        }
        if (command == '1') {
            if (key[0] == '\0' || data == 0) {
                printf("Недостаточно значений для операции\n");
                continue;
            }
            root = add_node(root, key, data);
            printf("1 Узел с ключом %s и значением %.5lf добавлен\n", key, data);
        }
        if (command == '2') {
            if (key[0] == '\0') {
                printf("Недостаточно значений для операции\n");
                continue;
            }
            root = delete_node(root, key);
            printf("2 узел с ключем %s удалён\n", key);
        }
        if (command == '3') {
            printf("3\n");
            print_tree(root, 0);
        }
        if (command == '4') {
            if (key[0] == '\0') {
                printf("Недостаточно значений для операции\n");
                continue;
            }
            printf("4 %s ", key);
            double node_data = search(root, key);
            if (node_data == -404) {
                continue;
            }
            printf("значение %.5lf\n", node_data);
        }
        free(key);
    }
    free(line);
    free_tree(root);
}
