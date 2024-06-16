#include <iostream>

using namespace std;

class Tabuleiro
{
private:
    char **tab;
    int n;           // linha
    int m;           // coluna
    bool vez;        // se for 1 é jogador 1 se for 0 é jogador 2
    int colunaCheia; // nº de colunas cheias
    int p1;          // pontuação do jogador 1
    int p2;          // pontuação do jogador 2
protected:
    char **getTab()
    {
        return tab;
    }

public:
    Tabuleiro(int _m, int _n)
    {
        colunaCheia = 0;
        vez = 0;
        n = _n; // linha
        m = _m; // coluna
        p1 = 0;
        p2 = 0;
        tab = new char *[n];
        for (int i = 0; i < n; i++)
        {
            tab[i] = new char[m];
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                tab[i][j] = '.';
    }
    virtual ~Tabuleiro()
    {        
        for (int i = 0; i < n; i++)
        {
            delete tab[i];
        }
        delete[] tab;
    }
    void exibirTabuleiro()
    {
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j < m; j++)
                cout << tab[i][j];
            cout << endl;
        }
        for (int i = 1; i <= m; i++)
            cout << i;
        cout << endl;
    }
    void reiniciarTabuleiro()
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                tab[i][j] = '.';
    }
    void alternarVez(int erro = 0)
    {
        vez = !vez;
        int jogador = vez ? 1 : 2;
        if (!erro)
            cout << "Agora é a vez do jogador " << jogador << endl;
    };
    bool verificaJogada(int coluna)
    {
        if (coluna < m && coluna >= 0)
        {
            if (tab[n - 1][coluna] != '.')
            {
                cout << "Coluna totalmente preenchida" << endl;
                return 0; // não tá
            }
            return 1; // tá nos conformes
        }
        return 0; // não tá
    };
    int escolheColuna()
    {
        exibirTabuleiro();
        alternarVez();
        int coluna;
        cout << "Digite uma coluna: ";
        cin >> coluna;
        return coluna;
    }
    int realizaJogada(int coluna)
    {

        // int coluna = escolheColuna();

        if (verificaJogada(coluna - 1))
        {
            int aux = n;
            for (int i = n - 1; i >= 0; i--)
            {
                if (tab[i][coluna - 1] != '.')
                {
                    break;
                }
                aux--;
            }
            if (aux == n - 1)
            {
                colunaCheia++;
            }
            inserir(coluna - 1, aux);
            return coluna;
        }
        else
        {
            cout << "Jogada Inválida" << endl;
            alternarVez(1);
            return realizaJogada(escolheColuna());
        }
    };
    int getP1()
    {
        return p1;
    }
    int getP2()
    {
        return p2;
    }
    void setP1(int _p1)
    {
        p1 = _p1;
    }
    void setP2(int _p2)
    {
        p2 = _p2;
    }
    void resultadoHorizontal()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m - 3; j++)
            {
                if (tab[i][j] == 'X' && tab[i][j + 1] == 'X' && tab[i][j + 2] == 'X' && tab[i][j + 3] == 'X')
                    setP1(getP1() + 1);
                if (tab[i][j] == '0' && tab[i][j + 1] == '0' && tab[i][j + 2] == '0' && tab[i][j + 3] == '0')
                    setP2(getP2() + 1);
            }
        }
    }
    void resultadoVertical()
    {
        for (int j = 0; j < m; j++)
        {
            for (int i = 0; i < n - 3; i++)
            {
                if (tab[i][j] == 'X' && tab[i + 1][j] == 'X' && tab[i + 2][j] == 'X' && tab[i + 3][j] == 'X')
                    setP1(getP1() + 1);
                if (tab[i][j] == '0' && tab[i + 1][j] == '0' && tab[i + 2][j] == '0' && tab[i + 3][j] == '0')
                    setP2(getP2() + 1);
            }
        }
    }
    void resultadoDiagonal()
    {
        for (int i = 0; i < n - 3; i++)
        {
            for (int j = 0; j < m - 3; j++)
            {
                if (tab[i][j] == 'X' && tab[i + 1][j + 1] == 'X' && tab[i + 2][j + 2] == 'X' && tab[i + 3][j + 3] == 'X')
                    setP1(getP1() + 1);
                if (tab[i][j] == '0' && tab[i + 1][j + 1] == '0' && tab[i + 2][j + 2] == '0' && tab[i + 3][j + 3] == '0')
                    setP2(getP2() + 1);
                if (tab[n - i - 1][j] == 'X' && tab[n - i - 2][j + 1] == 'X' && tab[n - i - 3][j + 2] == 'X' && tab[n - i - 4][j + 3] == 'X')
                    setP1(getP1() + 1);
                if (tab[n - i - 1][j] == '0' && tab[n - i - 2][j + 1] == '0' && tab[n - i - 3][j + 2] == '0' && tab[n - i - 4][j + 3] == '0')
                    setP2(getP2() + 1);
            }
        }
    }
    void resultadoFinal()
    {
        resultadoHorizontal();
        resultadoVertical();
        resultadoDiagonal();
    };
    void gerenciaJogo()
    {
        cout << "O jogo começou" << endl;

        while (colunaCheia < m)
        {
            realizaJogada(escolheColuna());
        }
        exibirTabuleiro();
        resultadoFinal();
        cout << "O jogador 1 fez " << p1 << " pontos" << endl;
        cout << "O jogador 2 fez " << p2 << " pontos" << endl;
        if (p1 > p2)
            cout << "Jogador 1 venceu" << endl;
        else if (p2 > p1)
            cout << "Jogador 2 venceu" << endl;
        else
            cout << "Empate" << endl;
    };
    void inserir(int m, int n) // coluna, linha
    {
        char jogada = vez ? 'X' : '0';
        tab[n][m] = jogada;
    }
};

class Lig4 : public Tabuleiro
{
private:
    string jogadas;
    int *colunas;

public:
    Lig4() : Tabuleiro(7, 6)
    {
        jogadas = "";
        colunas = new int[7 - 1];
    }
    ~Lig4() override
    {        
        delete colunas;
    }
    int solver();
    int random();
    int resultadoFinal()
    {
        enum
        {
            Continua = 0,
            Vitoria_da_Cor1,
            Vitoria_da_Cor2,
            Empate
        };
        resultadoHorizontal();
        resultadoVertical();
        resultadoDiagonal();
        if (!getP1() && !getP2())
            return Continua;
        if (getP1() > getP2())
            return Vitoria_da_Cor1;
        else if (getP1() < getP2())
            return Vitoria_da_Cor2;
        else
            return Empate;
    }
    string atualizaTabuleiro(int coluna)
    {
        jogadas += '0' + coluna;
        // cout << jogadas << endl;
        return jogadas;
    }
    int *colunasPreenchidas()
    {
        int m = 7;
        char **tab = getTab();
        for (int i = 0; i < m; i++)
            if (tab[6 - 1][i] != '.')
                colunas[i] = 0;
            else
                colunas[i] = 1;
        return colunas;
    }
    void gerenciaJogo()
    {
        while (resultadoFinal() != 2)
        {
            setP1(0);
            setP2(0);
            jogadas = "";
            reiniciarTabuleiro();
            cout << "Lig 4 tradicional!!" << endl;
            cout << "O jogo começou" << endl;
            while (!resultadoFinal())
            {
                atualizaTabuleiro(
                    realizaJogada(escolheColuna()));
            }
            exibirTabuleiro();
            if (getP1())
                cout << "Jogador 1 venceu" << endl
                     << endl;
            else
                cout << "Jogador 2 venceu" << endl
                     << endl;
            alternarVez(1);
        }
    }
};

int main()
{
    // Tabuleiro t1 = Tabuleiro(4, 4);
    // t1.gerenciaJogo();

    Lig4 t2 = Lig4();
    t2.gerenciaJogo();

    return 0;
}

int Lig4::solver()
{
    return 1;
}

int Lig4::random()
{
    return 1;
}
