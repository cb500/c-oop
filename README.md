# c-oop
This repo is just for fun while playing with some OOP constructions in C. As it is not intended to be of any OOP reference of implementation it is still useful to review some concepts like pointer to functions (callbacks), polymorphism, lazy call, etc.

## Implementation
We've started with a simpler approach having the child inside the parent structure (pseudo class) like:
```c
// Parent struct "object_t"
struct object_t
{
    dispatch_block_t print;

    // Note how the parent has a pointer to the child object, which isn't the appropriated approach to say the least ;)
    void *child;
};

// Child struct person_t
struct  person_t
{
    char *name;
    char gender;
    int age;
};

// Parent constructor
// Here the constructor receives a pointer to the child
// It also "overloads" with the appropriated "print" method from each child object
object_t *new_obj(void *child, void (* print_callback)(const void *))
{
    object_t *parent = (object_t *)calloc(1, sizeof(object_t));
    parent->child = child;
    parent->print = print_factory(parent->_dataPtr, print_callback);
    return parent;
}

// Child constructor
// After the child is created it calls the parent constructor passing its own reference and returns the parent object
//      which is not the correct approach either
object_t *new_person(char *name, char gender, int age)
{
    person_t *child = (person_t *)cmalloc(1, sizeof(person_t));
    child->name = copy_char(name);
    child->gender = gender;
    child->age = age;

    return new_obj(child, print_person);
}

```
This way is easier to start working as we can always construct the parent object and have a default interface (same method names for all children) without having to declare those methods inside each child. The problem is, this is not the way it is supposed to be. The parent should not know anything about child objects but it worked as a good POC.

Now, we have the "inheritance" working, even in a weird, non trivial way, it is working. Checking the code we found that it was pretty easy to start inverting the logic. We removed the child reference from the parent and added a reference to parent inside each child:
```c
struct object_t
{
    dispatch_block_t print;
};

struct  person_t
{
    struct object_t *parent;
    char *name;
    char gender;
    int age;
};

object_t *new_obj(void *data, void (* print_callback)(const void *))
{
    object_t *parent = (object_t *)calloc(1, sizeof(object_t));
    parent->print = print_factory(data, print_callback);
    return parent;
}

object_t *new_person(char *name, char gender, int age)
{
    person_t *child = (person_t *)calloc(1, sizeof(person_t));
    child->parent = new_obj(child, print_person);
    child->name = copy_char(name);
    child->gender = gender;
    child->age = age;

    return child->parent;
}
```
The child constructor is still returning the parent object, which is wrong, but we at least inverted the references and now the child has a reference to its parent and not the other way around.

The next step is to make the child return the correct object, create some grandchildren to test the inheritance propagation and start fixing the delegation of responsibilities, for example, in the above code the parent's constructor still receive a child's reference to correctly build the "print" method. It's not the parent's responsibility but the child's one. The parent may have its own "print" method but if the child wants to specialize it it has to overload the method.

## Dependencies
I use *Block Type*[1] here, so this project depends on:
- clang >= 12 (It may work with older version but was tested with clang version 12.0.0 on OpenSuse)
- libBlocksRuntime
- libdispatch
- libdispatch-devel

*NOTE*: For whatever reason that I'm not willing to investigate the above libs didn't update my "pkg-config" configuration and I had to add it on the Makefile manually. You may need to review bot *CFLAG_BLOCKS* and *LDFLAGS* to adjust accordingly to your setup :\

[1] https://clang.llvm.org/docs/BlockLanguageSpec.html