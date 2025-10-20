class Bar
{
public:
    Bar (int& ref) : ref (ref) {};
    int& ref;
};

int main()
{

    int x = 1;
    int y = 1;

    Bar a{x};
    Bar b{y};

    a = b; // erro!
    return 0;
}
