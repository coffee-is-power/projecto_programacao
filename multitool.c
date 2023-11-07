#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
#include <raylib.h>
void clear_screen()
{
    printf("\033[2J\033[1;1H");
}
void move_cursor_to(int x, int y)
{
    printf("\033[%d;%dH", x, y);
}
void loading_screen()
{
    // Tela de loading (criar animação com cores diferentes)
    for (int i = 0; i < 10; i++)
    {
        printf("\n\tCarregando o programa e obtendo informações do utilizador. Aguarde %d0%%", i);
        for (int j = 0; j < 40; j++)
        {
            printf(".");
            Sleep(10);
        }
        clear_screen();
    }
}

void menu_principal()
{
    int op_menu_principal;

    printf("\n\t\t\t1 - Ferramentas de limpeza");
    printf("\n\t\t\t2 - Ferramentas de optimização");
    printf("\n\t\t\t3 - Ver Informações de sistema");
    printf("\n\t\t\t4 - Ver configurações de ip");
    printf("\n\t\t\t0 - Sair");
    printf("\n\t\t\tInsira uma opção: ");
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
        printf("Selecione uma opção válida!");
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
    printf("\n\t\t\t2 - Limpeza ficheiros temporários");
    printf("\n\t\t\t3 - Limpeza da RAM");
    printf("\n\t\t\t4 - Limpeza arquivos desnecessários");
    printf("\n\t\t\t0 - Menu anterior");
    printf("\n\t\t\tInsira uma opção: ");
    scanf("%d", &op_ferramentas_limpeza);

    switch (op_ferramentas_limpeza)
    {
    case 0:
        printf("\033[2J\033[H");
        menu_principal();
        break;

    case 1:
        printf("Insira o letra da unidade de disco que pretende limpar: ");
        char letra_unidade_disco = getchar();
        char comando[] = "cleanmgr /d  :";
        comando[12] = letra_unidade_disco;
        scanf("%c", &letra_unidade_disco);
        clear_screen();
        int exit_code = system(comando);
        clear_screen();
        printf("\n\t\t\tLimpeza do disco");
        printf("\n\t\t\tAguarde enquanto limpamos o disco");
        sleep(2);
        printf(".");
        sleep(2);
        printf(".");
        sleep(2);
        printf(".");
        sleep(2);
        printf(".");
        if (exit_code != 0)
        {
            printf("Limpeza do disco concluida com sucesso!");
        }
        else
        {
            printf("Erro ao limpar o disco!"); 
        }
        Sleep(2);
        ferramentas_limpezas();

    default:
        printf("Selecione uma opção válida!");
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
    printf("Insira uma opção: ");
    scanf("%d", &op_ferramentas_otimizacao);

    switch (op_ferramentas_otimizacao)
    {
    case 0:
        clear_screen();
        menu_principal();
        break;

    default:
        printf("Selecione uma opção válida!");
        sleep(3);
        clear_screen();
        break;
    }
}

void info_sistema()
{
    int op_info_sistema;

    printf("\n\n\t\t1 - Informações básicas");
    printf("\n\t\t\t2 - Informações detalhadas");
    printf("\n\t\t\t0 - Menu anterior");
    printf("Insira uma opção: ");
    scanf("%d", &op_info_sistema);

    switch (op_info_sistema)
    {
    case 0:
        printf("\033[2J\033[H");

        break;

    default:
        printf("Selecione uma opção válida!");
        sleep(3);
        clear_screen();
        break;
    }
}

void info_ip()
{
    printf("\n\t\t\t1 - Informações de rede");
    printf("\n\t\t\t2 - Informações de rede sem fio");
    printf("\n\t\t\t0 - Menu anterior");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

#ifdef _WIN32
    clear_screen();
    move_cursor_to(6, 30);
    printf("Sistema operativo Windows detectado. O programa será iniciado.");
    Sleep(2000);
#else
    printf("\n\t\t\tSistema operativo Windows não detectado.");
    printf("\n\t\t\tA parar o programa");
    sleep(1)
        printf(".");
    sleep(1)
        printf(".");
    sleep(1)
        printf(".") return 1; // Encerre o programa se nÃƒÂ£o for Windows
#endif
    clear_screen();

    printf("\n\t\t\tBem vindo ao MultiTool. Por favor, forneça as permissões de administrador para continuar.");
    Sleep(2);
    system(".\\request_admin.bat");

    loading_screen();

    // buscar username windows
    char username[256];
    DWORD usernameSize = sizeof(username);

    if (GetUserName(username, &usernameSize))
    {
        printf("\n\t\t\tUtilizador: %s", username);
    }
    else
    {
        printf("Erro ao obter o nome de usuário.");
    }

    // buscar data e hora
    SYSTEMTIME st;
    GetLocalTime(&st);

    printf("\n\t\t\tData: %02d/%02d/%d", st.wDay, st.wMonth, st.wYear); // buscar data
    printf("\n\t\t\tHora: %02d:%02d", st.wHour, st.wMinute);            // buscar hora

    printf("\n\n\t\t\tAguarde enquanto carregamos as opções :)");
    sleep(2);
    clear_screen();

    if (GetUserName(username, &usernameSize))
    {
        printf("\n\t\t\tUtilizador: %s", username);
    }
    else
    {
        printf("Erro ao obter o nome de usuário.");
    }

    printf("\n\t\t\tData: %02d/%02d/%d", st.wDay, st.wMonth, st.wYear); // buscar data
    printf("\n\t\t\tHora: %02d:%02d", st.wHour, st.wMinute);            // buscar hora
    puts("");
    menu_principal();
}