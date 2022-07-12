.. title:: clang-tidy - bugprone-enum-to-int

bugprone-enum-to-int
====================

This check diagnoses instances where an enum is implicitly converted to an
integer. In C++11, enums can be defined as ``enum class`` which will prevent
such implicit conversion, however, ``enum`` provides no such guarantess to
prevent bugs. There can be many reasons why ``enum`` cannot be replaced with
``enum class`` such as compatibility with C or legacy libraries.

This check will diagnose similiar implicit conversions whne using ``enum`` to
find the same class of bugs. Currently it will only warn on function or
constructor calls as such conversions are not clear to the usr, but this
could be expanded in the future.

Examples:

.. code-block:: c++

    void foo(int i);
    void f() {
        foo(e1); // e1 is implictly converted to an int
    }
