#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Block.h>
#include "oop.h"

char *copy_char(const char *val)
{
    char *ret;
    ret = (char *)malloc(strlen(val) + 1);
    strcpy(ret, val);
    return ret;
}

object_t *new_obj(void *dataPtr, void (* print_callback)(const void *))
{
    object_t *obj = (object_t *)calloc(1, sizeof(object_t));
    obj->_dataPtr = dataPtr;
    obj->print = print_factory(obj->_dataPtr, print_callback);
    return obj;
}

object_t *new_person(char *name, char gender, int age)
{
    person_t *person = (person_t *)malloc(sizeof(person_t));
    memset(person, 0, sizeof(person_t));
    person->name = copy_char(name);
    person->gender = gender;
    person->age = age;

    person->parent = new_obj(person, print_person);
    return person->parent;
}

object_t *new_car(char *name, char *color, char *brand, double value)
{
    car_t *car = (car_t *)malloc(sizeof(car_t));
    memset(car, 0, sizeof(car_t));
    car->name = copy_char(name);
    car->color = copy_char(color);
    car->brand = copy_char(brand);
    car->value = value;

    car->parent = new_obj(car, print_car);
    return car->parent;
}

object_t *new_animal(char *type, char *color, int weight)
{
    animal_t *animal = (animal_t *)malloc(sizeof(animal_t));
    memset(animal, 0, sizeof(animal_t));
    animal->type = copy_char(type);
    animal->color = copy_char(color);
    animal->weight = weight;

    animal->parent = new_obj(animal, print_animal);
    return animal->parent;
}

void print_person(const void *person)
{
    person_t *data = (person_t *)person;
    printf("Name: %s\nGender: %c\nAge: %d\n", data->name, data->gender, data->gender);
}

void print_car(const void *car)
{
    car_t *data = (car_t *)car;
    printf("Name: %s\nColor: %s\nBrand: %s\nValue: $%0.2f\n", data->name, data->color, data->brand, data->value);
}

void print_animal(const void *animal)
{
    animal_t *data = (animal_t *)animal;
    printf("Type: %s\nColor: %s\nWeight: %d\n", data->type, data->color, data->weight);
}

dispatch_block_t print_factory(object_t *obj, void (*print_callback)(const void *))
{
    __block object_t *_obj = obj;
    return (void *) Block_copy(^
    {
        print_callback(_obj);
    });
}