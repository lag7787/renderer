class MyClass {
    public:
// explicit_specialization.cpp
        template<typename T> void f(T t)
        {
        };

        // Explicit specialization of f with 'char' with the
        // template argument explicitly specified:
        //
        template<> void f<char>(char c)
        {
        }

        // Explicit specialization of f with 'double' with the
        // template argument deduced:
        //
        template<> void f(double d)
        {
        }
}