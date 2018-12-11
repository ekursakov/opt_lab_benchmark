# opt_lab_benchmark

## Задание
Написать бенчмарк `L2 miss L3 hit -> L2 hit`  

## Описание задачи
В качестве примера выбрана задача умножения матриц.
С ростом размерности матриц они перестают помещаться в кэш и производительность снижается.
Решением этой проблемы является использование блочной схемы умножения матриц.
Но при слишком большом размере блока он может не поместиться в L2 кэш.

В блочном умножении во внутреннем цикле идет ображение к 3м подматрицам размера `block_size * block_size`.
Таким образом чтобы эффективно использовать L2 кэш надо `block_size`, чтобы туда одновременно могли поместиться все 3 блока.

У моего процессора размер L2 кэша 256kb на ядро, поэтому для оптимизации я поставил размер блока `128 * 128`. Вычисления происходят в 32 битных int, поэтому требуемый обьем `128 * 128 * 4 * 3 = 196 kb`.

Для демонстрации замедления при постоянных промахах мимо L2 кэша был выставлен размер блока `256 * 256`.

## Результаты и выводы
Уменьшение количества промахов увеличило производительность данной прогаммы примерно на 16%.
Доступ к L2 кэшу по сравнению с L3 быстрее в 2-4 раза. 
## Оборудование
Intel i5-3350P  
L2 cache: 4 * 256 kb  
L3 cache: 6 mb
