#!/bin/bash

levenshtein() {
    local s="$1"
    local t="$2"
    local len_s=${#s}
    local len_t=${#t}

    local i j cost deletion insertion substitution min
    local -a prev curr

    for ((j = 0; j <= len_t; j++)); do
        prev[$j]=$j
    done

    for ((i = 1; i <= len_s; i++)); do
        curr[0]=$i

        for ((j = 1; j <= len_t; j++)); do
            if [ "${s:$((i - 1)):1}" = "${t:$((j - 1)):1}" ]; then
                cost=0
            else
                cost=1
            fi

            deletion=$((prev[$j] + 1))
            insertion=$((curr[$((j - 1))] + 1))
            substitution=$((prev[$((j - 1))] + cost))

            min=$deletion

            if [ "$insertion" -lt "$min" ]; then
                min=$insertion
            fi

            if [ "$substitution" -lt "$min" ]; then
                min=$substitution
            fi

            curr[$j]=$min
        done

        for ((j = 0; j <= len_t; j++)); do
            prev[$j]=${curr[$j]}
        done
    done

    echo "${prev[$len_t]}"
}

if [ "$#" -ne 3 ]; then
    echo "Использование: $0 <исходный_файл> <каталог_поиска> <максимальное_расстояние>"
    exit 1
fi

source_file="$1"
search_dir="$2"
max_distance="$3"

if [ ! -f "$source_file" ]; then
    echo "Ошибка: исходный файл не существует или не является обычным файлом"
    exit 1
fi

if [ ! -d "$search_dir" ]; then
    echo "Ошибка: указанный каталог не существует"
    exit 1
fi

if ! [[ "$max_distance" =~ ^[0-9]+$ ]]; then
    echo "Ошибка: максимальное расстояние должно быть неотрицательным целым числом"
    exit 1
fi

source_abs=$(realpath "$source_file")
source_name=$(basename "$source_file")

deleted_count=0

while IFS= read -r -d '' file; do
    file_abs=$(realpath "$file")

    if [ "$file_abs" = "$source_abs" ]; then
        continue
    fi

    file_name=$(basename "$file")
    distance=$(levenshtein "$source_name" "$file_name")

    if [ "$distance" -le "$max_distance" ]; then
        if rm -- "$file"; then
            echo "Удалён синоним: $file, расстояние Левенштейна: $distance"
            deleted_count=$((deleted_count + 1))
        fi
    fi
done < <(find "$search_dir" -type f -print0)

if [ "$deleted_count" -eq 0 ]; then
    echo "Синонимы файла не найдены"
else
    echo "Всего удалено синонимов: $deleted_count"
fi
