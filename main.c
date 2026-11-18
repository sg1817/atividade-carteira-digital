#include <stdio.h>

int abrir_banco() {
    
    printf("abrir banco teste");
}

int consulta() {
    
    printf("consulta historico teste");
}

int sorteio() {
    
    printf("sorteio teste");
}

int main() {
    
    int menu;
    
    int index = 1;
    
    while (index) {
    
        printf("escolha uma das opções abaixo: \n1-abrir o banco\n2-consultar historico\n3-efetuar sorteio\n4-sair\n\n");
        scanf("%d", &menu);
        
        switch(menu) {
            
            case 1:
                abrir_banco();
                break;
                index = 0;
            
            case 2:
                consulta();
                break;
                index = 0;
                
            case 3:
                sorteio();
                break;                
                index = 0;
                
            case 4:
                break;            
                index = 0;
                
            default:
                
                printf("digite um número válido");
                continue;
        }
    
    }
    
}