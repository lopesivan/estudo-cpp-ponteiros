// 3. Passar o próprio objeto como argumento

class Comparador
{
public:
    void comparar (Comparador& outro)
    {
        if (this == &outro)
        {
            cout << "É o mesmo objeto!" << endl;
        }
        else
        {
            cout << "São objetos diferentes!" << endl;
        }
    }
};

int main()
{
    Comparador c1, c2;

    c1.comparar (c1); // É o mesmo objeto!
    c1.comparar (c2); // São objetos diferentes!
}
