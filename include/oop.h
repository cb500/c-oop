#ifndef __OOP_H
#define __OOP_H

#define NEW(CLASS_T, ...) new_ ## CLASS_T(__VA_ARGS__)
typedef void (^dispatch_block_t)(void);

typedef struct _PRINT_T print_t;
struct _PRINT_T
{
    void (* print)(const void *);
};

typedef struct _OBJECT object_t;
struct _OBJECT
{
    dispatch_block_t print;
    void *data;
};

typedef struct  _PERSON person_t;
struct  _PERSON
{
//    void (* print)();
    char *name;
    char gender;
    int age;
};

typedef struct  _CAR car_t;
struct  _CAR
{
//    void (* print)();
    char *name;
    char *color;
    char *brand;
    double value;
};

typedef struct  _ANIMAL animal_t;
struct  _ANIMAL 
{
//    void (* print)();
    char *type;
    char *color;
    int weight;
};

// Print facility
dispatch_block_t print_factory(object_t *obj, void (*print_callback)(const void *));

//void *new_f(void *obj, void *(*constructor)(void));
object_t *new_obj(void *data, void (* print_callback)(const void *));
object_t *new_person(char *name, char gender, int age);
object_t *new_car(char *name, char *color, char *brand, double value);
object_t *new_animal(char *type, char *color, int weight);
void print_person(const void *person);
void print_car(const void *car);
void print_animal(const void *animal);

#endif