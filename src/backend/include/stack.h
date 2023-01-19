#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#include "defines.h"

/**
@brief Функции для создания и работы со стэком. Поддерживает разные типы.
*/

/**
@brief Юнион для хранения разных типов.
@detailed Нужно для универсальности стека.
*/

union stack_data {
    double var_d;
    void* var_vp;
    char var_c;
    int var_i;
};

/**
@brief Структура описывающая стек.
@detailed Содержит: текущий размер, количество памяти, хранимый тип, указатель на юнион(памяти
выделяется размером с наибольший тип).
*/

typedef struct {
    size_t m_top;
    size_t m_capacity;
    enum eType m_type;
    union stack_data* m_data;
} stack;

/**
@brief Инициализирует стек.
*/

enum eError create_stack(stack* st_new, const size_t st_size, const enum eType st_type);

/**
@brief Очищает стек.
*/

void destroy_stack(stack* st);

/**
@brief Помещает элемент на верхушку стека.
*/

enum eError push_stack(stack* const st, ...);

/**
@brief Убирает элемент с верхушки стека.
*/

enum eError pop_stack(stack* const st, void* elem);

/**
@brief Возвращает элемент с верхушки стека типа char.
@detailed Вспомогательная функция для перевода в обратную польскую нотацию. Типизирована
*/

char get_char_top(stack* const st);

/**
@brief Проверяет стек на пустоту.
*/

bool is_empty_stack(const stack* st);

#endif
