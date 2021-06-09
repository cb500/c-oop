#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Block.h>
#include "oop.h"

int main()
{
    object_t *person = NEW(person, "Maria Joaquina", 'F', 32);
    object_t *car = NEW(car, "Panamera", "Yellow", "Porsche", 125000.00);
    object_t *dog = NEW(animal, "Dog", "Black", 7);

    printf("------------------------------------------\n");
    person->print();
    printf("------------------------------------------\n");
    car->print();
    printf("------------------------------------------\n");
    dog->print();
    printf("------------------------------------------\n");

    return 0;
}