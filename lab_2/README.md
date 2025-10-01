# Тема: Структуры
## Задача 1 - создать структуру с указателем на функцию

### Постановка задачи
Создайте структуру, одно из полей которой является указателем на функцию. Вызовите эту функцию через имя переменной структуры и поле указателя на функцию.

### Математическая модель
- В языке C указатель на функцию позволяет хранить адрес функции и вызывать её через этот указатель.  
- Структура может содержать такой указатель как поле.  
- Это позволяет гибко менять поведение программы, назначая разные функции одной и той же структуре.  

### Список идентификаторов  

| Имя переменной | Тип данных        | Описание |
|----------------|-------------------|----------|
| action         | int (*)(int, int) | Указатель на функцию, принимающую два `int` и возвращающую `int` |
| s              | struct Sample     | Экземпляр структуры с указателем на функцию |
| add            | функция           | Складывает два числа |
| mul            | функция           | Умножает два числа |

### Код программы  
```c
#include <stdio.h>

struct Sample {
    int (*action)(int, int);  
};

int add(int a, int b) {
    return a + b;
}

int mul(int a, int b) {
    return a * b;
}

int main(void) {
    struct Sample s;

    s.action = add;
    printf("Результат сложения: %d\n", s.action(3, 4));

    s.action = mul;
    printf("Результат умножения: %d\n", s.action(3, 4));

    return 0;
}
```
### Результаты работы программы
![result 1](./img/task1.png) 
---

## Задача 2 - структура для вектора в трёхмерном пространстве

### Постановка задачи
Реализуйте структуру для вектора в 3D пространстве и добавьте следующие функции:
• Скалярное умножение векторов;
• Векторное произведение;
• Модуль вектора;
• Распечатка вектора.
В структуре также должно быть поле для хранения имени вектора.

### Математическая модель
Пусть векторы заданы как:  
```
A = (x1, y1, z1)  
B = (x2, y2, z2)
```  

1. Скалярное произведение: 
```
A · B = x1·x2 + y1·y2 + z1·z2
```  

2. Векторное произведение: 
```
A × B = (y1·z2 – z1·y2, z1·x2 – x1·z2, x1·y2 – y1·x2)
```  

3. Модуль вектора: 
```
|A| = √(x1² + y1² + z1²)
```  

### Список идентификаторов  

| Имя переменной | Тип данных       | Описание |
|----------------|------------------|----------|
| name           | char[]           | Имя вектора |
| x, y, z        | double           | Координаты вектора |
| dot_product    | функция          | Скалярное произведение |
| cross_product  | функция          | Векторное произведение |
| magnitude      | функция          | Модуль вектора |
| print_vector   | функция          | Печать вектора |

### Код программы  

```c
#include <stdio.h>
#include <math.h>
#include <string.h>

struct Vector3D {
    char name[20];
    double x, y, z;
};

double dot_product(struct Vector3D a, struct Vector3D b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

struct Vector3D cross_product(struct Vector3D a, struct Vector3D b, const char* name) {
    struct Vector3D result;
    strncpy(result.name, name, sizeof(result.name));
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

double magnitude(struct Vector3D v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

void print_vector(struct Vector3D v) {
    printf("%s = (%.2f, %.2f, %.2f)\n", v.name, v.x, v.y, v.z);
}

int main(void) {
    struct Vector3D A = {"A", 1.0, 2.0, 3.0};
    struct Vector3D B = {"B", 4.0, 5.0, 6.0};

    print_vector(A);
    print_vector(B);

    printf("Скалярное произведение: %.2f\n", dot_product(A, B));

    struct Vector3D C = cross_product(A, B, "C");
    print_vector(C);

    printf("Модуль вектора %s: %.2f\n", A.name, magnitude(A));
    printf("Модуль вектора %s: %.2f\n", B.name, magnitude(B));

    return 0;
}
```

### Результаты работы программы  
![result 2](./img/task2.png) 
---

## Задача 3 - вычисление комплексной экспоненты

### Постановка задачи
Используя структуру для представления комплексного числа, вычислите комплексную экспоненту `e^z` для числа `z ∈ ℂ`.  
Формула экспоненты:  
```
exp(z) = 1 + z + z^2/2! + z^3/3! + … + z^n/n!
```  

### Математическая модель  
Комплексное число имеет вид:  
```
z = a + bi
```  
где `a` — действительная часть, `b` — мнимая часть.  

Основные операции:  
- Сложение:  
```
(a + bi) + (c + di) = (a + c) + (b + d)i
```  
- Умножение:  
```
(a + bi)(c + di) = (ac – bd) + (ad + bc)i
```  
- Возведение в степень: последовательное умножение.  
- Умножение на скаляр:  
```
λ(a + bi) = (λa) + (λb)i
```  

Экспонента аппроксимируется частичной суммой ряда до n-го члена.  

### Список идентификаторов  

| Имя переменной | Тип данных      | Описание |
|----------------|-----------------|----------|
| a, b           | double          | Действительная и мнимая части комплексного числа |
| Complex        | struct          | Структура для комплексного числа |
| add            | функция         | Сложение двух комплексных чисел |
| multiply       | функция         | Умножение двух комплексных чисел |
| power          | функция         | Возведение числа в степень |
| scalar_mult    | функция         | Умножение на скаляр |
| exp_complex    | функция         | Вычисление экспоненты |
| print_complex  | функция         | Печать комплексного числа |

### Код программы  

```c
#include <stdio.h>

struct Complex {
    double a; 
    double b; 
};

struct Complex add(struct Complex z1, struct Complex z2) {
    struct Complex res = {z1.a + z2.a, z1.b + z2.b};
    return res;
}

struct Complex multiply(struct Complex z1, struct Complex z2) {
    struct Complex res = {z1.a * z2.a - z1.b * z2.b, z1.a * z2.b + z1.b * z2.a};
    return res;
}

struct Complex scalar_mult(struct Complex z, double k) {
    struct Complex res = {z.a * k, z.b * k};
    return res;
}

struct Complex power(struct Complex z, int n) {
    struct Complex res = {1.0, 0.0};
    for (int i = 0; i < n; i++) {
        res = multiply(res, z);
    }
    return res;
}

struct Complex exp_complex(struct Complex z, int terms) {
    struct Complex sum = {1.0, 0.0}; 
    for (int n = 1; n <= terms; n++) {
        struct Complex term = power(z, n);

        double fact = 1.0;
        for (int i = 1; i <= n; i++) fact *= i;

        term = scalar_mult(term, 1.0 / fact);
        sum = add(sum, term);
    }
    return sum;
}

void print_complex(struct Complex z) {
    if (z.b >= 0)
        printf("%.4f + %.4fi\n", z.a, z.b);
    else
        printf("%.4f - %.4fi\n", z.a, -z.b);
}

int main(void) {
    struct Complex z = {1.0, 1.0}; 

    printf("Вычисление exp(z) для z = ");
    print_complex(z);

    struct Complex result = exp_complex(z, 15); 
    printf("exp(z) ≈ ");
    print_complex(result);

    return 0;
}
```

### Результаты работы программы  
![result 3](./img/task3.png) 

### Информация о студенте  
Полторацкая Анастасия, 1 курс, группа `1об_ПОО/25`
