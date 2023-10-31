#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
void clear_screen() {
    printf("\033[2J\033[1;1H");
}
void move_cursor_to(int x, int y) {
    printf("\033[%d;%dH", x, y);
}
int main()
{
    setlocale (LC_ALL, "Portuguese");

    #ifdef _WIN32
    printf("\n\n\t\t\tSistema operativo Windows detectado. O programa ser� iniciado.");
    Sleep(2);
    #else
    printf("\n\t\t\tSistema operativo Windows n�o detectado.");
    printf("\n\t\t\tA parar o programa");
    sleep(1)
    printf(".");
    sleep(1)
    printf(".");
    sleep(1)
    printf(".")
    return 1;  // Encerre o programa se nÃ£o for Windows
    #endif  
    // Tela de loading
    for (int i = 0; i < 10; i++)
    {
        printf("\n\tCarregando o programa e obtendo informa��es do utilizador. Aguarde %d0%%", i);
        for (int j = 0; j < 40; j++)
        {
            printf(".");
            Sleep(10);
        }
        clear_screen();
    }
    // buscar username windows
    char username[256];
    DWORD usernameSize = sizeof(username);

    if (GetUserName(username, &usernameSize)) 
    {
        printf("\n\t\t\tUtilizador: %s", username);
    } else {
        printf("Erro ao obter o nome de usu�rio.");
    }

    // buscar data e hora
    SYSTEMTIME st;
    GetLocalTime(&st);

    printf("\n\t\t\tData: %02d/%02d/%d", st.wDay, st.wMonth, st.wYear); //buscar data
    printf("\n\t\t\tHora: %02d:%02d", st.wHour, st.wMinute); //buscar hora

    printf("\n\n\t\t\tAguarde enquanto carregamos as op��es :)");
    sleep(2);
    clear_screen();

    if (GetUserName(username, &usernameSize)) 
    {
        printf("\n\t\t\tUtilizador: %s", username);
    } else {
        printf("Erro ao obter o nome de usu�rio.");
    }

    printf("\n\t\t\tData: %02d/%02d/%d", st.wDay, st.wMonth, st.wYear); //buscar data
    printf("\n\t\t\tHora: %02d:%02d", st.wHour, st.wMinute); //buscar hora
    puts("");
    menu_principal();
}

void menu_principal()
{
    int op_menu_principal;

    printf("\n\t\t\t1 - Feramentas de limpeza");
    printf("\n\t\t\t2 - Ferramentas de optimiza��o");
    printf("\n\t\t\t3 - Ver Informa��es de sistema");
    printf("\n\t\t\t4 - Ver configura��es de ip");
    printf("\n\t\t\t0 - Sair");
    printf("\n\t\t\tInsira uma op��o: ");
    scanf("%d", &op_menu_principal);


    switch (op_menu_principal)
    {

    case 0:
        printf("\n\t\t\tSaindo");
        sleep(1);
        printf(".");
        sleep(1);
        printf(".");
        sleep(1);
        printf(".");
        exit(0);
    case 1:
        ferramentas_limpeza();
    break;

    case 2:
        ferramentas_otimizacao();
    break;

    case 3:
        info_sistema();
    break;

    default:
        printf("Selecione uma op��o v�lida!");
        sleep(3);
        clear_screen();
    break;
    }

    return 0;
}


void ferramentas_limpeza()
{
    printf("\033[2J\033[H");
    
    int op_ferramentas_limpeza;

    printf("\n\t\t\t1 - Limpeza do disco");
    printf("\n\t\t\t2 - Limpeza ficheiros tempor�rios");
    printf("\n\t\t\t3 - Limpeza da RAM");
    printf("\n\t\t\t4 - Limpeza arquivos desnecess�rios");
    printf("\n\t\t\t0 - Menu anterior");
    printf("\n\t\t\tInsira uma op��o: ");
    scanf("%d", &op_ferramentas_limpeza);
    
    switch (op_ferramentas_limpeza)
    {
    case 0:
        printf("\033[2J\033[H");
        menu_principal();
    break;
    
    default:
        printf("Selecione uma op��o v�lida!");
        sleep(3);
        clear_screen();
    break;
    }

}

void ferramentas_otimizacao()
{
    clear_screen();

    int op_ferramentas_otimizacao;
    
    printf("\n\t\t\t1 - **");
    printf("\n\t\t\t2 - **");
    printf("\n\t\t\t3 - **");
    printf("\n\t\t\t0 - Menu anterior");
    printf("Insira uma op��o: ");
    scanf("%d", &op_ferramentas_otimizacao);

    switch (op_ferramentas_otimizacao)
    {
    case 0:
        clear_screen();
        menu_principal();
    break;
    
    default:
        printf("Selecione uma op��o v�lida!");
        sleep(3);
        clear_screen();
    break;
    }
}

void info_sistema()
{
    int op_info_sistema;
    
    printf("\n\n\t\t1 - Informa��es b�sicas");
    printf("\n\t\t\t2 - Informa��es detalhadas");
    printf("\n\t\t\t0 - Menu anterior");
    printf("Insira uma op��o: ");
    scanf("%d", &op_info_sistema);
    
    switch (op_info_sistema)
    {
    case 0:
        printf("\033[2J\033[H");
        
    break;
    
    default:
        printf("Selecione uma op��o v�lida!");
        sleep(3);
        clear_screen();
    break;
    }
}

void info_ip()
{
    printf("\n\t\t\t1 - Informa��es de rede");
    printf("\n\t\t\t2 - Informa��es de rede sem fio");
    printf("\n\t\t\t0 - Menu anterior");
}